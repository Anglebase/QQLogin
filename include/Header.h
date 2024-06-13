#pragma once

#include <egrome/Block>
#include <egrome/PixelMap>

class Header : public Block
{
private:
    bool appCreated{false};
    PixelMap header;
    std::wstring headerPath;

    std::wstring nickname;

protected:
    void paintEvent(const PaintEvent &event) override;

public:
    Header(const Rect &rect, Block *parent = nullptr);
    ~Header() override;

    void setHeaderPath(const std::wstring &path);
    void setNickname(const std::wstring &nickname);
};