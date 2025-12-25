#include "Circle.h"
#include "Rectangle.h"

int main() {
    IShape* shapes[] = {
        new Circle(5.0f),
        new Rectangle(4.0f, 3.0f)
    };

    for (IShape* s : shapes) {
        s->Draw();   // ← 実体ごとに処理が変わる
    }

    for (IShape* s : shapes) {
        delete s;
    }

    return 0;
}
