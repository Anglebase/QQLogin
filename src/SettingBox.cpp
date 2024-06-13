#include "SettingBox.h"
#include <egrome/Painter>

void SettingBox::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);

    painter.setPenColor(this->CheckBox::style.borderColor);
    painter.setPenWidth(this->CheckBox::style.borderWidth);
    auto checkboxRect = Rect{
        0,
        (painter.rect().height() - this->CheckBox::style.boxSize) / 2,
        this->CheckBox::style.boxSize,
        this->CheckBox::style.boxSize,
    };
    painter.drawRect(checkboxRect);
    painter.setPenColor(this->CheckBox::style.textColor);
    painter.setFont(this->style.fontName, this->style.fontSize);
    painter.setTextAlign(TextHAlign::Left, TextVAlign::Middle);
    painter.drawText(
        painter.rect().adjusted(
            this->CheckBox::style.boxSize + 3,
            0, 0, 0),
        this->text_);
    if (this->isChecked())
    {
        painter.setPenColor(this->CheckBox::style.checkColor);
        painter.setPenWidth(3);
        std::vector<Point> points = {
            {0, this->CheckBox::style.boxSize / 2},
            {this->CheckBox::style.boxSize / 2, this->CheckBox::style.boxSize},
            {this->CheckBox::style.boxSize * 3 / 2, 0},
        };
        for (auto &point : points)
            point += checkboxRect.getTopLeft() +
                     Point{-this->CheckBox::style.boxSize / 4, -1};
        painter.drawPolyline(points);
    }
    event.endPaint();
}

SettingBox::SettingBox(const Rect &rect, Block *parent)
    : CheckBox(rect, parent)
{
}