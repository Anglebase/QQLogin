#include "FindButton.h"
#include <egrome/Painter>

void FindButton::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);

    painter.setPenColor(this->style.textColor);
    painter.setFont(this->style.fontName, this->style.fontSize);
    painter.setTextAlign(TextHAlign::Left, TextVAlign::Middle);
    painter.drawText(painter.rect(), this->text_);

    event.endPaint();
}

FindButton::FindButton(const Rect &rect, Block *parent)
    : Block(rect, parent)
{
}

FindButton::~FindButton()
{
}

void FindButton::setText(const std::wstring &text)
{
    this->text_ = text;
}

const std::wstring &FindButton::text() const
{
    return this->text_;
}
