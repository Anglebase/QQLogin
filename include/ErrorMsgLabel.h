#pragma once

#include <egrome/Block>

class ErrorMsgLabel : public Block
{
    std::wstring errorMsg_;

protected:
    void paintEvent(const PaintEvent &event) override;

public:
    ErrorMsgLabel(const Rect &rect, Block *parent = nullptr);
    ~ErrorMsgLabel() override;

    void setErrorMsg(const std::wstring &errorMsg);
    void clearErrorMsg();
};