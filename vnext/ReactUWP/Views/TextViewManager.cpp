// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"

#include "TextViewManager.h"

#include <Views/ShadowNodeBase.h>

#include <Utils/PropertyUtils.h>
#include <Utils/ValueUtils.h>

#include <winrt/Windows.UI.Xaml.Documents.h>

namespace winrt {
using namespace Windows::UI::Xaml::Documents;
} // namespace winrt

namespace react {
namespace uwp {

class TextShadowNode : public ShadowNodeBase {
  using Super = ShadowNodeBase;

 public:
  TextShadowNode() = default;
  bool ImplementsPadding() override {
    return true;
  }

  winrt::FrameworkElement::SizeChanged_revoker m_sizeChangedRevoker{};
};

TextViewManager::TextViewManager(
    const std::shared_ptr<IReactInstance> &reactInstance)
    : Super(reactInstance) {}

facebook::react::ShadowNode *TextViewManager::createShadow() const {
  return new TextShadowNode();
}

const char *TextViewManager::GetName() const {
  return "RCTText";
}

XamlView TextViewManager::CreateViewCore(int64_t tag) {
  auto textBlock = winrt::TextBlock();
  textBlock.TextWrapping(
      winrt::TextWrapping::Wrap); // Default behavior in React Native
  return textBlock;
}

class TextStyleShadowProps {
 public:
  TextStyleShadowProps()
      : isUndefined(true),
        textShadowOffsetWidth(1.0f),
        textShadowOffsetHeight(1.0f),
        textShadowRadius(2.0f),
        textShadowColor({0xC0, 0x00, 0x00, 0x00}) {}

  bool IsUndefined() {
    return isUndefined;
  }

  float TextShadowOffsetWidth() {
    return textShadowOffsetWidth;
  }

  void TextShadowOffsetWidth(float value) {
    textShadowOffsetWidth = value;
    isUndefined = false;
  }

  float TextShadowOffsetHeight() {
    return textShadowOffsetHeight;
  }

  void TextShadowOffsetHeight(float value) {
    textShadowOffsetHeight = value;
    isUndefined = false;
  }

  float TextShadowRadius() {
    return textShadowRadius;
  }

  void TextShadowRadius(float value) {
    textShadowRadius = value;
    isUndefined = false;
  }

  winrt::Windows::UI::Color TextShadowColor() {
    return textShadowColor;
  }

  void TextShadowColor(winrt::Windows::UI::Color value) {
    textShadowColor = value;
    isUndefined = false;
  }

 private:
  bool isUndefined;
  float textShadowOffsetWidth;
  float textShadowOffsetHeight;
  float textShadowRadius;
  winrt::Windows::UI::Color textShadowColor;
};

void TextViewManager::UpdateProperties(
    ShadowNodeBase *nodeToUpdate,
    const folly::dynamic &reactDiffMap) {
  auto textBlock = nodeToUpdate->GetView().as<winrt::TextBlock>();
  if (textBlock == nullptr)
    return;

  TextStyleShadowProps textStyleShadowProps;

  for (const auto &pair : reactDiffMap.items()) {
    const std::string &propertyName = pair.first.getString();
    const folly::dynamic &propertyValue = pair.second;

    if (TryUpdateForeground(textBlock, propertyName, propertyValue)) {
      continue;
    } else if (TryUpdateFontProperties(
                   textBlock, propertyName, propertyValue)) {
      continue;
    } else if (TryUpdatePadding(
                   nodeToUpdate, textBlock, propertyName, propertyValue)) {
      continue;
    } else if (TryUpdateTextAlignment(textBlock, propertyName, propertyValue)) {
      continue;
    } else if (TryUpdateTextTrimming(textBlock, propertyName, propertyValue)) {
      continue;
    } else if (TryUpdateTextDecorationLine(
                   textBlock, propertyName, propertyValue)) {
      continue;
    } else if (TryUpdateCharacterSpacing(
                   textBlock, propertyName, propertyValue)) {
      continue;
    } else if (propertyName == "numberOfLines") {
      if (propertyValue.isNumber())
        textBlock.MaxLines(static_cast<int32_t>(propertyValue.asDouble()));
      else if (propertyValue.isNull())
        textBlock.ClearValue(winrt::TextBlock::MaxLinesProperty());
    } else if (propertyName == "lineHeight") {
      if (propertyValue.isNumber())
        textBlock.LineHeight(static_cast<int32_t>(propertyValue.asDouble()));
      else if (propertyValue.isNull())
        textBlock.ClearValue(winrt::TextBlock::LineHeightProperty());
    } else if (propertyName == "selectable") {
      if (propertyValue.isBool())
        textBlock.IsTextSelectionEnabled(propertyValue.asBool());
      else if (propertyValue.isNull())
        textBlock.ClearValue(
            winrt::TextBlock::IsTextSelectionEnabledProperty());
    } else if (propertyName == "allowFontScaling") {
      if (propertyValue.isBool())
        textBlock.IsTextScaleFactorEnabled(propertyValue.asBool());
      else
        textBlock.ClearValue(
            winrt::TextBlock::IsTextScaleFactorEnabledProperty());
    } else if (propertyName == "selectionColor") {
      if (IsValidColorValue(propertyValue)) {
        textBlock.SelectionHighlightColor(SolidColorBrushFrom(propertyValue));
      } else
        textBlock.ClearValue(
            winrt::TextBlock::SelectionHighlightColorProperty());
    } else if (propertyName == "textShadowOffset") {
      if (propertyValue.isObject()) {
        for (const auto &kvp : propertyValue.items()) {
          float value = static_cast<float>(
              kvp.second.isInt() ? kvp.second.asInt() : kvp.second.asDouble());

          if (kvp.first == "width") {
            textStyleShadowProps.TextShadowOffsetWidth(value);
          } else if (kvp.first == "height") {
            textStyleShadowProps.TextShadowOffsetHeight(value);
          }
        }
      }
    } else if (propertyName == "textShadowColor") {
      if (propertyValue.isInt()) {
        textStyleShadowProps.TextShadowColor(ColorFrom(propertyValue));
      }
    } else if (propertyName == "textShadowRadius") {
      if (propertyValue.isInt() || propertyValue.isDouble()) {
        textStyleShadowProps.TextShadowRadius(static_cast<float>(
            propertyValue.isInt() ? propertyValue.asInt()
                                  : propertyValue.asDouble()));
      }
    }
  }

  if (!textStyleShadowProps.IsUndefined()) {
    auto childVisual = winrt::Windows::UI::Xaml::Hosting::
        ElementCompositionPreview::GetElementChildVisual(textBlock);
    if (childVisual == nullptr) {
      auto visual = winrt::Windows::UI::Xaml::Hosting::
          ElementCompositionPreview::GetElementVisual(textBlock);

      auto compositor = visual.Compositor();

      auto spriteVisual = compositor.CreateSpriteVisual();
      spriteVisual.Brush(compositor.CreateColorBrush({0x0, 0x0, 0x0, 0x0}));
      spriteVisual.Size({static_cast<float>(textBlock.ActualWidth()),
                         static_cast<float>(textBlock.ActualHeight())});

      auto shadow = compositor.CreateDropShadow();
      shadow.Offset(winrt::Windows::Foundation::Numerics::float3(
          textStyleShadowProps.TextShadowOffsetWidth(),
          textStyleShadowProps.TextShadowOffsetHeight(),
          0));
      shadow.BlurRadius(textStyleShadowProps.TextShadowRadius());
      shadow.Color(textStyleShadowProps.TextShadowColor());
      shadow.Mask(textBlock.GetAlphaMask());
      spriteVisual.Shadow(shadow);

      winrt::Windows::UI::Xaml::Hosting::ElementCompositionPreview::
          SetElementChildVisual(textBlock, spriteVisual);

      auto *pTextShadowNode = static_cast<TextShadowNode *>(nodeToUpdate);
      pTextShadowNode->m_sizeChangedRevoker = textBlock.SizeChanged(
          winrt::auto_revoke,
          [textBlock, spriteVisual](const auto &, const auto &) {
            spriteVisual.Size({static_cast<float>(textBlock.ActualWidth()),
                               static_cast<float>(textBlock.ActualHeight())});
          });
    }
  }

  Super::UpdateProperties(nodeToUpdate, reactDiffMap);
}

void TextViewManager::AddView(XamlView parent, XamlView child, int64_t index) {
  auto textBlock(parent.as<winrt::TextBlock>());
  auto childInline(child.as<winrt::Inline>());
  textBlock.Inlines().InsertAt(static_cast<uint32_t>(index), childInline);
}

void TextViewManager::RemoveAllChildren(XamlView parent) {
  auto textBlock(parent.as<winrt::TextBlock>());
  textBlock.Inlines().Clear();
}

void TextViewManager::RemoveChildAt(XamlView parent, int64_t index) {
  auto textBlock(parent.as<winrt::TextBlock>());
  return textBlock.Inlines().RemoveAt(static_cast<uint32_t>(index));
}

YGMeasureFunc TextViewManager::GetYogaCustomMeasureFunc() const {
  return DefaultYogaSelfMeasureFunc;
}

} // namespace uwp
} // namespace react
