#pragma once

#include <egrome/CheckBox>

class SettingBox : public CheckBox
{
public:
    struct StyleSheet
    {
        std::wstring fontName{L"黑体"};
        int fontSize{16};
    } style;

public:
    void paintEvent(const PaintEvent &event) override;

public:
    SettingBox(const Rect &rect, Block *parent = nullptr);
    ~SettingBox() override = default;
};