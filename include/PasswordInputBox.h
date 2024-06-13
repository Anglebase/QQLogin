#pragma once

#include <egrome/LineEdit>
#include <egrome/SignalSlots>

class PasswordInputBox : public LineEdit
{
private:
    std::wstring placeholder_;
    bool showPlaneText_{false};

public:
    struct StyleSheet
    {
        Color placeholderColor{Color::Gray};
    } style;
signals:
    Signal<void()> TabPressed;

protected:
    void paintEvent(const PaintEvent &event) override;
    void mousePressEvent(const Point &pos, MouseButton button) override;
    void mouseReleaseEvent(const Point &pos, MouseButton button) override;
    void mouseMoveEvent(const Point &pos) override;
    void keyPressEvent(Key key, KeyFlag flag) override;
    void InputTextEvent(wchar_t c) override;

public:
    PasswordInputBox(const Rect &rect, Block *parent = nullptr);
    ~PasswordInputBox() override = default;

    void setPlaceholder(const std::wstring &placeholder);
    const std::wstring &placeholder() const;
};