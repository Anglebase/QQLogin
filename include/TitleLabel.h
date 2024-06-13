#pragma once

#include <egrome/Label>
#include <string>

class TitleLabel : public Label
{
protected:
    void paintEvent(const PaintEvent &event) override;

public:
    TitleLabel(const std::wstring &rect, Block *parent = nullptr);
    ~TitleLabel() override = default;
};