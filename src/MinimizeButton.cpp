#include "MinimizeButton.h"
#include <egrome/Painter>
#include <egrome/App>

void MinimizeButton::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);

    painter.setBrushColor(this->colorAnimation->value());
    painter.drawFillRect(painter.rect());
    painter.setPenColor(this->style.fontColor);
    painter.setPenWidth(2);
    painter.drawLine({10, painter.rect().height() / 2},
                     {painter.rect().width() - 10, painter.rect().height() / 2});
    event.endPaint();
}

MinimizeButton::MinimizeButton(const Rect &rect, Block *parent)
    : Button(rect, parent)
{
    using namespace std::chrono_literals;
    this->Button::style.backgroundColor = Color::LightBlue;
    this->Button::style.hoverColor = 0xeeeeff_rgb;
    this->style.fontColor = Color::White;
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
            this->colorAnimation->run(true);
            App::setMinimize();
        });
}

MinimizeButton::~MinimizeButton()
{
    delete this->colorAnimation;
}
