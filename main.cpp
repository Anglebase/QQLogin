#include <egrome/App>
#include <egrome/Size>
#include "Window.h"

int main()
{
    Rect rect{0, 0, 600, 450};
    Window window{rect};
    App app{&window, InitFlag::TopMost | InitFlag::NoBorder};
    app.windowCreate.connect(
        [=]()
        { App::setWindowPos(
              Rect{Point{0, 0},
                   App::getScreenSize()}
                  .centerWith(rect.getSize())
                  .getTopLeft()); });
    app.run();
    return 0;
}