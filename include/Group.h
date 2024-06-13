#pragma once

#include "SettingBox.h"
#include "FindButton.h"

class Group : public Block
{
    SettingBox *rememberBox;
    SettingBox *autoLoginBox;

    FindButton *findButton;

public:
    Group(const Rect &rect, Block *parent = nullptr);
    ~Group() override;
};