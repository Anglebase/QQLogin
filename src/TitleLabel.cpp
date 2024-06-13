#include "TitleLabel.h"
#include <egrome/Painter>

void TitleLabel::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);

    painter.setPenColor(this->style.textColor);
    painter.setFont(this->style.fontName, this->style.fontSize);
    painter.drawText({0, 0}, this->getText());

    event.endPaint();
}

TitleLabel::TitleLabel(const std::wstring &rect, Block *parent)
    : Label(Rect{0, 0, 0, 0}, parent)
{
    this->setText(rect);
}