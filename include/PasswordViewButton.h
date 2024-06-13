#pragma once

#include <egrome/Block>
#include <egrome/SignalSlots>

class PasswordViewButton : public Block
{
private:
    bool isPasswordVisible_{false};
signals:
    Signal<void(bool)> stateChanged;

protected:
    void paintEvent(const PaintEvent &event) override;
    void mousePressEvent(const Point &pos, MouseButton button) override;
    void mouseReleaseEvent(const Point &pos, MouseButton button) override;

public:
    PasswordViewButton(const Rect &rect, Block *parent = nullptr);
    ~PasswordViewButton() override = default;

    void setPasswordVisible(bool visible);
    bool isPasswordVisible() const;
};