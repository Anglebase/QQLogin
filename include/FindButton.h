#pragma once

#include <egrome/Block>
#include <egrome/Color>

class FindButton : public Block
{
private:
    std::wstring text_;

public:
    struct Stylesheet
    {
        Color textColor{Color::Gray};
        std::wstring fontName{L"黑体"};
        int fontSize{16};
    } style;

protected:
    void paintEvent(const PaintEvent &event) override;

public:
    FindButton(const Rect &rect, Block *parent = nullptr);
    ~FindButton() override;

    void setText(const std::wstring &text);
    const std::wstring &text() const;
};