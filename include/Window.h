#pragma once

#include <egrome/Block>
#include <egrome/Animation>
#include <optional>
#include "CloseButton.h"
#include "MinimizeButton.h"
#include "TitleLabel.h"
#include "AccountInputBox.h"
#include "PasswordInputBox.h"
#include "ErrorMsgLabel.h"
#include "Group.h"
#include "PasswordViewButton.h"
#include "Header.h"
#include <egrome/Button>

class Window : public Block
{
    Rect dragRect;
    bool isDragging{false};
    std::optional<Point> GlobalPos{std::nullopt};

    CloseButton *closeButton;
    MinimizeButton *minimizeButton;
    TitleLabel *titleLabel;

    AccountInputBox *accountInputBox;
    PasswordInputBox *passwordInputBox;
    PasswordViewButton *passwordViewButton;

    Button *loginButton;

    ErrorMsgLabel *errorMsgLabel;
    Group *settingGroup;

    Header *header;

protected:
    void paintEvent(const PaintEvent &event) override;
    void mousePressEvent(const Point &pos, MouseButton button) override;
    void mouseMoveEvent(const Point &pos) override;
    void mouseReleaseEvent(const Point &pos, MouseButton button) override;
    void keyPressEvent(Key key, KeyFlag flag) override;

public:
    Window(const Rect &rect);
    ~Window() override;

    void setUser(const std::wstring& username,const std::wstring& userheader);
};