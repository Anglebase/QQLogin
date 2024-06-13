#include "ErrorMsgLabel.h"
#include <egrome/Painter>
#include <egrome/Color>

void ErrorMsgLabel::paintEvent(const PaintEvent &event)
{
    if (errorMsg_.empty())
        return;
    auto &painter = event.beginPaint(this);
    painter.setPenColor(Color::Red);
    painter.setFont(L"宋体", 16);
    painter.drawText(0, 0, this->errorMsg_);
    event.endPaint();
}

ErrorMsgLabel::ErrorMsgLabel(const Rect &rect, Block *parent)
    : Block(rect, parent) {}

ErrorMsgLabel::~ErrorMsgLabel() {}

void ErrorMsgLabel::setErrorMsg(const std::wstring &errorMsg)
{
    this->errorMsg_ = errorMsg;
}

void ErrorMsgLabel::clearErrorMsg()
{
    this->errorMsg_.clear();
}
