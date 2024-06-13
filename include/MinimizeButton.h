#pragma once

#include <egrome/Button>
#include <egrome/Color>
#include <egrome/Animation>

class MinimizeButton : public Button
{
    Animation<Color> *colorAnimation{nullptr};

public:
    struct StyleSheet
    {
        Color fontColor{Color::White};
    } style;

protected:
    void paintEvent(const PaintEvent &event) override;

public:
    MinimizeButton(const Rect &rect, Block *parent = nullptr);
    ~MinimizeButton() override;
};