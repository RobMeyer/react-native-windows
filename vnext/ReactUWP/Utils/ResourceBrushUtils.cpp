// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"

#include "ResourceBrushUtils.h"
#include "StandardControlResourceKeyNames.h"

#include <winrt/Windows.UI.Xaml.h>

namespace winrt {
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
} // namespace winrt

namespace react {
namespace uwp {

void UpdateResourceBrush(
    const winrt::FrameworkElement &element,
    const std::wstring &resourceName,
    const winrt::Brush brush) {
  const auto resources = element.Resources();
  if (resources != nullptr) {
    if (brush != nullptr) {
      resources.Insert(winrt::box_value(resourceName), brush);
    } else {
      resources.Remove(winrt::box_value(resourceName));
    }
  }
}

void UpdateComboBoxBackgroundResourceBrushes(const winrt::ComboBox &comboBox, const winrt::Brush brush) {
  UpdateResourceBrush(comboBox, c_comboBoxBackground, brush);
  UpdateResourceBrush(comboBox, c_comboBoxBackgroundPointerOver, brush);
  UpdateResourceBrush(comboBox, c_comboBoxBackgroundPressed, brush);
  UpdateResourceBrush(comboBox, c_comboBoxBackgroundDisabled, brush);
  UpdateResourceBrush(comboBox, c_comboBoxBackgroundUnfocused, brush);

  UpdateResourceBrush(comboBox, c_comboBoxDropDownBackground, brush);

  // This resource is used to control colors of the TextBox internally used
  // by a ComboBox with IsEditable=true
  UpdateResourceBrush(comboBox, c_textControlBackgroundFocused, brush);
}

void UpdateTextControlForegroundResourceBrushes(const winrt::FrameworkElement element, const winrt::Brush brush);

 void UpdateComboBoxForegroundResourceBrushes(const winrt::ComboBox &comboBox, const winrt::Brush brush) {
  UpdateResourceBrush(comboBox, c_comboBoxForeground, brush);
  UpdateResourceBrush(comboBox, c_comboBoxForegroundDisabled, brush);
  UpdateResourceBrush(comboBox, c_comboBoxForegroundFocused, brush);
  UpdateResourceBrush(comboBox, c_comboBoxForegroundFocusedPressed, brush);

  UpdateResourceBrush(comboBox, c_comboBoxDropDownGlyphForeground, brush);
  UpdateResourceBrush(comboBox, c_comboBoxDropDownGlyphForegroundDisabled, brush);
  UpdateResourceBrush(comboBox, c_comboBoxDropDownGlyphForegroundFocused, brush);
  UpdateResourceBrush(comboBox, c_comboBoxDropDownGlyphForegroundFocusedPressed, brush);
  UpdateResourceBrush(comboBox, c_comboBoxEditableDropDownGlyphForeground, brush);
  // This resource is used to control colors of the TextBox internally used
  // by a ComboBox with IsEditable=true
  UpdateTextControlForegroundResourceBrushes(comboBox, brush);
 }

void UpdateComboBoxBorderResourceBrushes(const winrt::ComboBox &comboBox, const winrt::Brush brush) {
  UpdateResourceBrush(comboBox, c_comboBoxBorderBrush, brush);
  UpdateResourceBrush(comboBox, c_comboBoxBorderBrushPointerOver, brush);
  UpdateResourceBrush(comboBox, c_comboBoxBorderBrushPressed, brush);
  UpdateResourceBrush(comboBox, c_comboBoxBorderBrushDisabled, brush);

  // ? c_comboBoxBackgroundBorderBrushFocused
  // ? c_comboBoxBackgroundBorderBrushUnfocused

  UpdateResourceBrush(comboBox, c_comboBoxDropDownBorderBrush, brush);
}

void UpdateComboBoxItemBackgroundResourceBrushes(const winrt::ComboBoxItem &comboBoxItem, const winrt::Brush brush) {
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBackground, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBackgroundPointerOver, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBackgroundPressed, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBackgroundDisabled, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBackgroundSelected, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBackgroundSelectedUnfocused, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBackgroundSelectedPointerOver, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBackgroundSelectedPressed, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBackgroundSelectedDisabled, brush);
}

void UpdateComboBoxItemForegroundResourceBrushes(const winrt::ComboBoxItem &comboBoxItem, const winrt::Brush brush) {
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemForeground, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemForegroundPointerOver, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemForegroundPressed, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemForegroundDisabled, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemForegroundSelected, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemForegroundSelectedUnfocused, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemForegroundSelectedPointerOver, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemForegroundSelectedPressed, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemForegroundSelectedDisabled, brush);
}

void UpdateComboBoxItemBorderResourceBrushes(const winrt::ComboBoxItem &comboBoxItem, const winrt::Brush brush){
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBorderBrush, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBorderBrushPointerOver, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBorderBrushPressed, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBorderBrushDisabled, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBorderBrushSelected, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBorderBrushSelectedUnfocused, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBorderBrushSelectedPointerOver, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBorderBrushSelectedPressed, brush);
  UpdateResourceBrush(comboBoxItem, c_comboBoxItemBorderBrushSelectedDisabled, brush);
}

void UpdateTextControlBackgroundResourceBrushes(const winrt::FrameworkElement &element, const winrt::Brush brush) {
  UpdateResourceBrush(element, c_textControlBackground, brush);
  UpdateResourceBrush(element, c_textControlBackgroundPointerOver, brush);
  UpdateResourceBrush(element, c_textControlBackgroundFocused, brush);
  UpdateResourceBrush(element, c_textControlBackgroundDisabled, brush);

  UpdateResourceBrush(element, c_textControlButtonForegroundPressed, brush);
}

void UpdateTextControlForegroundResourceBrushes(const winrt::FrameworkElement element, const winrt::Brush brush) {
  UpdateResourceBrush(element, c_textControlForeground, brush);
  UpdateResourceBrush(element, c_textControlForegroundPointerOver, brush);
  UpdateResourceBrush(element, c_textControlForegroundFocused, brush);
  UpdateResourceBrush(element, c_textControlForegroundDisabled, brush);

  UpdateResourceBrush(element, c_textControlButtonForeground, brush);
  UpdateResourceBrush(element, c_textControlButtonForegroundPointerOver, brush);
  UpdateResourceBrush(element, c_textControlButtonBackgroundPressed, brush);
}

void UpdateTextControlBorderResourceBrushes(const winrt::FrameworkElement &element, const winrt::Brush brush) {
  UpdateResourceBrush(element, c_textControlBorderBrush, brush);
  UpdateResourceBrush(element, c_textControlBorderBrushPointerOver, brush);
  UpdateResourceBrush(element, c_textControlBorderBrushFocused, brush);
  UpdateResourceBrush(element, c_textControlBorderBrushDisabled, brush);
}

void UpdateToggleSwitchBorderResourceBrushes(const winrt::ToggleSwitch &toggleSwitch, const winrt::Brush brush) {
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchStrokeOff, brush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchStrokeOffPointerOver, brush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchStrokeOffPressed, brush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchStrokeOffDisabled, brush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchStrokeOn, brush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchStrokeOnPointerOver, brush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchStrokeOnPressed, brush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchStrokeOnDisabled, brush);
}

void UpdateToggleSwitchThumbResourceBrushes(const winrt::ToggleSwitch &toggleSwitch, const winrt::Brush thumbBrush) {
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchKnobFillOff, thumbBrush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchKnobFillOffPointerOver, thumbBrush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchKnobFillOffPressed, thumbBrush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchKnobFillOffDisabled, thumbBrush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchKnobFillOn, thumbBrush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchKnobFillOnPointerOver, thumbBrush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchKnobFillOnPressed, thumbBrush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchKnobFillOnDisabled, thumbBrush);
}

void UpdateToggleSwitchTrackResourceBrushes(
    const winrt::ToggleSwitch &toggleSwitch,
    const winrt::Brush onTrackBrush,
    const winrt::Brush offTrackBrush) {
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchFillOn, onTrackBrush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchFillOnPointerOver, onTrackBrush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchFillOnPressed, onTrackBrush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchFillOnDisabled, onTrackBrush);

  UpdateResourceBrush(toggleSwitch, c_toggleSwitchFillOff, offTrackBrush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchFillOffPointerOver, offTrackBrush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchFillOffPressed, offTrackBrush);
  UpdateResourceBrush(toggleSwitch, c_toggleSwitchFillOffDisabled, offTrackBrush);
}

bool IsObjectATextControl(const winrt::DependencyObject &object) {
  return object.try_as<winrt::TextBox>() != nullptr || object.try_as<winrt::PasswordBox>() != nullptr ||
      object.try_as<winrt::RichEditBox>() != nullptr || object.try_as<winrt::AutoSuggestBox>() != nullptr;
}

void UpdateControlBackgroundResourceBrushes(
    const winrt::Windows::UI::Xaml::FrameworkElement &element,
    const winrt::Media::Brush brush) {
  if (IsObjectATextControl(element)) {
    UpdateTextControlBackgroundResourceBrushes(element, brush);
  } else if (const auto comboBox = element.try_as<winrt::ComboBox>()) {
    UpdateComboBoxBackgroundResourceBrushes(comboBox, brush);
  } else if (const auto comboBoxItem = element.try_as<winrt::ComboBoxItem>()) {
    UpdateComboBoxItemBackgroundResourceBrushes(comboBoxItem, brush);
  }
}

void UpdateControlForegroundResourceBrushes(
    const winrt::Windows::UI::Xaml::DependencyObject object,
    const winrt::Media::Brush brush) {
  if (IsObjectATextControl(object)) {
    const auto element = object.try_as<winrt::FrameworkElement>();
    UpdateTextControlForegroundResourceBrushes(element, brush);
  } else if (const auto comboBox = object.try_as<winrt::ComboBox>()) {
    UpdateComboBoxForegroundResourceBrushes(comboBox, brush);
  } else if (const auto comboBoxItem = object.try_as<winrt::ComboBoxItem>()) {
    UpdateComboBoxItemForegroundResourceBrushes(comboBoxItem, brush);
  }
}

void UpdateControlBorderResourceBrushes(
    const winrt::Windows::UI::Xaml::FrameworkElement &element,
    const winrt::Media::Brush brush) {
  if (IsObjectATextControl(element)) {
    UpdateTextControlBorderResourceBrushes(element, brush);
  } else if (const auto toggleSwitch = element.try_as<winrt::ToggleSwitch>()) {
    UpdateToggleSwitchBorderResourceBrushes(toggleSwitch, brush);
  } else if (const auto comboBox = element.try_as<winrt::ComboBox>()) {
    UpdateComboBoxBorderResourceBrushes(comboBox, brush);
  }else if (const auto comboBoxItem = element.try_as<winrt::ComboBoxItem>()) {
    UpdateComboBoxItemBorderResourceBrushes(comboBoxItem, brush);
  }
}

} // namespace uwp
} // namespace react
