#include "CloseButton.h"
#include <egrome/Painter>
#include <egrome/App>

void CloseButton::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);

    painter.setBrushColor(this->colorAnimation->value());
    painter.drawFillRect(painter.rect());
    painter.setPenColor(this->style.fontColor);
    painter.setPenWidth(2);
    painter.drawLine(Point(10, 10),
                     Point(painter.rect().width() - 10, painter.rect().height() - 10));
    painter.drawLine(Point(10, painter.rect().height() - 10),
                     Point(painter.rect().width() - 10, 10));
    event.endPaint();
}

CloseButton::CloseButton(const Rect &rect, Block *parent)
    : Button(rect, parent)
{
    using namespace std::chrono_literals;
    this->Button::style.backgroundColor = Color::LightBlue;
    this->Button::style.hoverColor = Color::Red;
    this->colorAnimation = new Animation<Color>{
        Animation<Color>::Args{
            .startValue = this->Button::style.backgroundColor,
            .endValue = this->Button::style.hoverColor,
            .duration = 200ms,
            .function = Color::lerp,
        },
    };

    this->onEnter.connect(
        [this]()
        { this->colorAnimation->run(); });
    this->onLeave.connect(
        [this]()
        { this->colorAnimation->run(true); });
    this->onClicked.connect(
        [this]()
        {
            App::quit(0);
        });
}

CloseButton::~CloseButton()
{
    delete this->colorAnimation;
}
