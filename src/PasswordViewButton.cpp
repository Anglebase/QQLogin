#include "PasswordViewButton.h"
#include <egrome/Painter>
#include <egrome/Color>
#include <egrome/Size>

void PasswordViewButton::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);

    if (this->isPasswordVisible_)
    {
        painter.setPenColor(0x75b2eb_rgb);
        painter.setPenWidth(2);
    }
    else
    {
        painter.setPenColor(Color::Gray);
        painter.setPenWidth(1);
    }
    painter.drawEllipse(painter.rect().centerWith({18, 10}));
    painter.drawCircle(painter.rect().center(), 4);
    event.endPaint();
}

void PasswordViewButton::mousePressEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left)
    {
        if (this->rect().contains(pos))
        {
            this->isPasswordVisible_ = true;
            this->stateChanged.emit(this->isPasswordVisible_);
        }
    }
    return Block::mousePressEvent(pos, button);
}

void PasswordViewButton::mouseReleaseEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left)
    {
        this->isPasswordVisible_ = false;
        this->stateChanged.emit(this->isPasswordVisible_);
    }
    return Block::mouseReleaseEvent(pos, button);
}

PasswordViewButton::PasswordViewButton(const Rect &rect, Block *parent)
    : Block(rect, parent)
{
}

void PasswordViewButton::setPasswordVisible(bool visible)
{
    this->isPasswordVisible_ = visible;
}

bool PasswordViewButton::isPasswordVisible() const
{
    return this->isPasswordVisible_;
}
