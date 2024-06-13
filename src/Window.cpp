#include "Window.h"
#include <egrome/Painter>
#include <egrome/Color>
#include <egrome/App>
#include <egrome/Size>

void Window::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);

    painter.clear(Color(255, 255, 255));
    painter.setBrushColor(Color::LightBlue);
    painter.drawFillRect(dragRect);

    event.endPaint();
    return Block::paintEvent(event);
}

void Window::mousePressEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left)
    {
        if (dragRect.contains(pos) &&
            // 无效区域
            !this->closeButton->rect().contains(pos) &&
            !this->minimizeButton->rect().contains(pos))
        {
            this->isDragging = true;
        }
    }
    return Block::mousePressEvent(pos, button);
}

void Window::mouseMoveEvent(const Point &pos)
{
    if (this->isDragging)
    {
        auto position = App::getMousePos();
        if (this->GlobalPos.has_value())
        {
            auto delta = position - GlobalPos.value();
            auto target = App::getWindowPos() + delta;
            App::setWindowPos(target);
        }
        GlobalPos = position;
    }
    return Block::mouseMoveEvent(pos);
}

void Window::mouseReleaseEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left)
    {
        this->isDragging = false;
        GlobalPos = std::nullopt;
    }
    return Block::mouseReleaseEvent(pos, button);
}

void Window::keyPressEvent(Key key, KeyFlag flag)
{
    if (key == Key::Tab && App::getFocusBlock() == this)
    {
        App::setFocusBlock(this->accountInputBox);
    }
    return Block::keyPressEvent(key, flag);
}

Window::Window(const Rect &rect)
    : Block(rect, nullptr), dragRect(0, 0, 0, 0)
{
    using namespace std::chrono_literals;
    this->dragRect = Rect{0, 0, rect.width(), rect.height() / 3};
    this->closeButton = new CloseButton{Rect{rect.width() - 30, 0, 30, 30}, this};
    this->minimizeButton = new MinimizeButton{Rect{rect.width() - 60, 0, 30, 30}, this};
    this->titleLabel = new TitleLabel{L"登录", this};
    this->titleLabel->style = TitleLabel::StyleSheet{
        .textColor = Color::White,
        .fontName = L"黑体",
        .fontSize = 24,
    };
    this->titleLabel->rect().setTopLeft(Point{5, 5});
    auto centerRect = this->rect().centerWith(Size{300, 40});
    centerRect.offset(Point{0, 25});
    this->accountInputBox = new AccountInputBox{centerRect, this};

    this->accountInputBox->LineEdit::style.textColor = Color::Black,
    this->accountInputBox->LineEdit::style.cursorColor = Color::Black,
    this->accountInputBox->LineEdit::style.backgroundColor = Color::White,
    this->accountInputBox->LineEdit::style.onFocusBorderColor = Color::DarkGray,
    this->accountInputBox->LineEdit::style.offFocusBorderColor = Color::LightGray,
    this->accountInputBox->LineEdit::style.fontName = L"黑体",
    this->accountInputBox->LineEdit::style.fontSize = 32,
    this->accountInputBox->LineEdit::style.borderRadius = 3,
    this->accountInputBox->AccountInputBox::style.placeholderColor = Color::Gray;

    centerRect.offset(Point{0, 55});
    this->passwordInputBox = new PasswordInputBox{centerRect, this};

    this->passwordInputBox->LineEdit::style.textColor = Color::Black,
    this->passwordInputBox->LineEdit::style.cursorColor = Color::Black,
    this->passwordInputBox->LineEdit::style.backgroundColor = Color::White,
    this->passwordInputBox->LineEdit::style.onFocusBorderColor = Color::DarkGray,
    this->passwordInputBox->LineEdit::style.offFocusBorderColor = Color::LightGray,
    this->passwordInputBox->LineEdit::style.fontName = L"黑体",
    this->passwordInputBox->LineEdit::style.fontSize = 32,
    this->passwordInputBox->LineEdit::style.borderRadius = 3,
    this->passwordInputBox->PasswordInputBox::style.placeholderColor = Color::Gray;

    this->passwordViewButton = new PasswordViewButton{
        Rect{centerRect.right() - 30, centerRect.top() + 10,
             20, centerRect.height() - 20},
        this,
    };
    this->passwordViewButton->stateChanged.connect(
        [this](bool show)
        {
            this->passwordInputBox->setShowPlainText(show);
        });

    this->passwordInputBox->setShowPlainText(false);

    this->accountInputBox->TabPressed.connect(
        [this]()
        { App::setFocusBlock(this->passwordInputBox); });

    this->passwordInputBox->TabPressed.connect(
        [this]()
        { App::setFocusBlock(this->accountInputBox); });

    auto loginButtonRect = this->rect().centerWith(Size{140, 50});
    loginButtonRect.offset(Point{0, 170});
    this->loginButton = new Button{loginButtonRect, this};

    this->loginButton->style = Button::StyleSheet{
        .textColor{Color::White},
        .backgroundColor{0x37f0da_rgb},
        .hoverColor{0x8ef0eb_rgb},
        .pressedColor{0xd3f0ef_rgb},
    };
    this->loginButton->setText(L"登录");
    this->loginButton->updateAnimations();

    centerRect.offset(Point{7, 45});
    this->settingGroup = new Group{centerRect, this};

    centerRect.offset(Point{0, 20});
    this->errorMsgLabel = new ErrorMsgLabel{centerRect, this};

    this->loginButton->clicked.connect(
        [this]()
        {
            if (this->accountInputBox->text().empty())
            {
                this->errorMsgLabel->setErrorMsg(L"请输入账号!");
                return;
            }
            if (this->passwordInputBox->text().empty())
            {
                this->errorMsgLabel->setErrorMsg(L"请输入密码!");
                return;
            }
            if (this->accountInputBox->text() != L"123456" ||
                this->passwordInputBox->text() != L"password123")
            {
                this->errorMsgLabel->setErrorMsg(L"账号或密码错误!");
                return;
            }
            std::cout << "Login Success!" << std::endl;
            this->setUser(L"聆.梦.", L"./res/Header.jpg");
            this->errorMsgLabel->clearErrorMsg();
        });
    this->header = new Header{
        Rect{
            this->rect().width() / 2 - 50,
            this->rect().height() / 3 - 50,
            100,
            100,
        },
        this};
    this->header->setHeaderPath(L"./res/default.jpg");
}

Window::~Window()
{
    delete this->closeButton;
    delete this->minimizeButton;
    delete this->titleLabel;
    delete this->accountInputBox;
    delete this->passwordInputBox;
    delete this->loginButton;
    delete this->errorMsgLabel;
    delete this->settingGroup;
    delete this->passwordViewButton;
    delete this->header;
}

void Window::setUser(const std::wstring &username, const std::wstring &userheader)
{
    if (this->header)
    {
        this->header->setNickname(username);
        this->header->setHeaderPath(userheader);
    }
}
