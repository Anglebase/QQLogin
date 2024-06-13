#include "Group.h"
#include <egrome/Size>

Group::Group(const Rect &rect, Block *parent)
    : Block(rect, parent)
{
    Rect layoutRect{0, 0, 100, 20};
    this->rememberBox = new SettingBox(layoutRect, this);
    this->rememberBox->setText(L"记住密码");
    this->rememberBox->setCursorType(CursorType::Hand);
    layoutRect.offset(layoutRect.width() + 10, 0);
    this->autoLoginBox = new SettingBox(layoutRect, this);
    this->autoLoginBox->setText(L"自动登录");
    this->autoLoginBox->setCursorType(CursorType::Hand);
    this->rememberBox->CheckBox::style.borderColor =
        this->autoLoginBox->CheckBox::style.borderColor = Color::Gray;
    this->rememberBox->CheckBox::style.textColor =
        this->autoLoginBox->CheckBox::style.textColor = Color::Gray;
    this->rememberBox->CheckBox::style.boxSize =
        this->autoLoginBox->CheckBox::style.boxSize = 10;
    this->rememberBox->CheckBox::style.checkColor =
        this->autoLoginBox->CheckBox::style.checkColor = 0x5797d4_rgb;

    this->autoLoginBox->checkedChanged.connect(
        [this](bool checked)
        {
            if (checked)
            {
                this->rememberBox->setChecked(true);
            }
        });
    this->rememberBox->checkedChanged.connect(
        [this](bool checked)
        {
            if (!checked)
            {
                this->autoLoginBox->setChecked(false);
            }
        });
    layoutRect.offset({this->autoLoginBox->rect().width() + 10, 0});
    layoutRect.setSize({60, 20});
    this->findButton = new FindButton(layoutRect, this);
    this->findButton->setText(L"找回密码");
    this->findButton->setCursorType(CursorType::Hand);
    this->findButton->onClicked.connect(
        [this]()
        {
            std::cout << "Find password" << std::endl;
        });
}

Group::~Group()
{
    delete this->rememberBox;
    delete this->autoLoginBox;
    delete this->findButton;
}
