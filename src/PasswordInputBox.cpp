#include "PasswordInputBox.h"
#include <egrome/Painter>
#include <egrome/App>

void PasswordInputBox::paintEvent(const PaintEvent &event)
{
    LineEdit::paintEvent(event);
    auto &painter = event.beginPaint(this);
    if (this->text().empty())
    {
        painter.setTextAlign(TextHAlign::Left, TextVAlign::Middle);
        painter.setPenColor(this->style.placeholderColor);
        painter.drawText(painter.rect().adjusted(5, 0, 0, 0),
                         this->placeholder_);
    }
    event.endPaint();
}

void PasswordInputBox::mousePressEvent(const Point &pos, MouseButton button)
{
    if (pos.x() > this->rect().right() - 25)
        return;
    return LineEdit::mousePressEvent(pos, button);
}

void PasswordInputBox::mouseReleaseEvent(const Point &pos, MouseButton button)
{
    if (pos.x() > this->rect().right() - 25)
        return;
    return LineEdit::mouseReleaseEvent(pos, button);
}

void PasswordInputBox::mouseMoveEvent(const Point &pos)
{
    return LineEdit::mouseMoveEvent(pos);
}

void PasswordInputBox::keyPressEvent(Key key, KeyFlag flag)
{
    if ((key == Key::C && flag == KeyFlag::Ctrl) ||
        (key == Key::X && flag == KeyFlag::Ctrl))
        return;
    if (key == Key::Tab)
    {
        if (App::getFocusBlock() == this)
            this->TabPressed.emit();
        return;
    }
    return LineEdit::keyPressEvent(key, flag);
}

void PasswordInputBox::InputTextEvent(wchar_t c)
{
    if (this->text().length() >= 16)
        return;
    if (std::isprint(c))
        return LineEdit::InputTextEvent(c);
}

PasswordInputBox::PasswordInputBox(const Rect &rect, Block *parent)
    : LineEdit(rect, parent), placeholder_(L"请输入密码") {}

void PasswordInputBox::setPlaceholder(const std::wstring &placeholder)
{
    this->placeholder_ = placeholder;
}

const std::wstring &PasswordInputBox::placeholder() const
{
    return this->placeholder_;
}
