#include "Header.h"
#include <egrome/Painter>
#include <egrome/App>
#include <egrome/Color>

void Header::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);

    if (!this->header.isNull())
    {
        PixelMap mask{painter.rect().width(), painter.rect().height()};
        // 创建蒙版
        auto &maskPainter = mask.beginPaint();
        maskPainter.setBrushColor(0xffffff_rgb);
        maskPainter.drawFillCircle(
            painter.rect().center(), painter.rect().width() / 2);
        mask.endPaint();
        // 屏幕图像 = 屏幕图像 AND (NOT 蒙版)
        painter.drawPixelMap(
            painter.rect(), mask, BlendMode::DSna);
        PixelMap printPixmap{this->header};
        // 打印图像 = 源图像 AND 蒙版
        auto &printPainter = printPixmap.beginPaint();
        printPainter.drawPixelMap(
            printPainter.rect(), mask, BlendMode::DSa);
        printPixmap.endPaint();
        // 屏幕图像 = 打印图像 OR 屏幕图像
        painter.drawPixelMap(
            painter.rect(), printPixmap, BlendMode::DSo);
    }
    if (!this->nickname.empty())
    {
        painter.setPenColor(0x111111_rgb);
        painter.setTextAlign(TextHAlign::Center, TextVAlign::Top);
        painter.setFont(L"黑体", 22);
        painter.drawText(
            Rect{
                painter.rect().left(),
                painter.rect().bottom() + 2,
                painter.rect().width(),
                16,
            },
            this->nickname);
    }

    event.endPaint();
}

Header::Header(const Rect &rect, Block *parent)
    : Block(rect, parent)
{
    App::windowCreate.connect(
        [this]()
        {
            this->header = PixelMap::FromFile(this->headerPath);
            this->appCreated = true;
        });
}

Header::~Header()
{
}

void Header::setHeaderPath(const std::wstring &path)
{
    this->headerPath = path;
    if (this->appCreated)
    {
        this->header = PixelMap::FromFile(this->headerPath);
    }
}

void Header::setNickname(const std::wstring &nickname)
{
    this->nickname = nickname;
}
