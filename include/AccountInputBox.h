#pragma once

#include <egrome/LineEdit>
#include <egrome/SignalSlots>

class AccountInputBox : public LineEdit
{
private:
    std::wstring placeholder_;

public:
    struct StyleSheet
    {
        Color placeholderColor{Color::Gray};
    } style;
signals:
    Signal<void()> TabPressed;

protected:
    void paintEvent(const PaintEvent &event) override;
    void keyPressEvent(Key key, KeyFlag flag) override;
    void InputTextEvent(wchar_t c) override;

public:
    AccountInputBox(const Rect &rect, Block *parent = nullptr);
    ~AccountInputBox() override = default;

    void setPlaceholder(const std::wstring &placeholder);
    const std::wstring &placeholder() const;
};