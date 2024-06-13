#include "AccountInputBox.h"
#include <egrome/Painter>
#include <egrome/App>

void AccountInputBox::paintEvent(const PaintEvent &event)
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

void AccountInputBox::keyPressEvent(Key key, KeyFlag flag)
{
    if (key == Key::Tab)
    {
        if (App::getFocusBlock() == this)
            this->TabPressed.emit();
        return;
    }
    return LineEdit::keyPressEvent(key, flag);
}

void AccountInputBox::InputTextEvent(wchar_t c)
{
    if (this->text().length() >= 15)
        return;
    if (std::isdigit(c))
        return LineEdit::InputTextEvent(c);
}

AccountInputBox::AccountInputBox(const Rect &rect, Block *parent)
    : LineEdit(rect, parent), placeholder_(L"请输入账号") {}

void AccountInputBox::setPlaceholder(const std::wstring &placeholder)
{
    this->placeholder_ = placeholder;
}

const std::wstring &AccountInputBox::placeholder() const
{
    return this->placeholder_;
}
