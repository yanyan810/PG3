#include "Dog.h"
#include "Cat.h"

int main() {
    Animal* animals[] = {
        new Dog(),
        new Cat()
    };

    for (Animal* a : animals) {
        a->Speak();   // ← 実体ごとに動作が変わる
    }

    for (Animal* a : animals) {
        delete a;
    }

    return 0;
}
