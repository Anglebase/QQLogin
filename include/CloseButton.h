#pragma once

#include <egrome/Button>
#include <egrome/Color>
#include <egrome/Animation>

class CloseButton : public Button
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
    CloseButton(const Rect &rect, Block *parent = nullptr);
    ~CloseButton() override;
};