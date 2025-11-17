#include <stdio.h>
#include <functional>
#include <Windows.h>
#include <time.h>

//
//int main(int argc, const char* argv[]) {
//
////	[]() {printf("lamda test"); }();
//
//
//	//auto fx = [](int i) {return i + 1; };
//
//	//printf("%d", fx(2));
//
//	//int num = 10;
//	//auto fx = [=](int i) {return num + i; };
//
//	//printf("%d", fx(2));
//
//	std::function<int(int)> fx = [](int i) {return i + 1; };
//	auto fx2 = [](int i) {return i + 1; ; };
//	printf("%d\n", fx(2));
//	printf("%d\n", fx2(2));
//
//	return 0;
//
//}

void DelayReveal(std::function<void()> fn, unsigned int delayMs) {
    printf("判定中...\n");
    Sleep(delayMs);
    fn(); // ← 引数なしで呼べる
}

int main(void) {

    srand((unsigned int)time(NULL)); // 乱数初期化

    int userGuess;
    printf("奇数(1) か 偶数(0) か予想してください : ");
    scanf_s("%d", &userGuess);

    int roll = rand() % 6 + 1;

    // ★ここがめっちゃシンプル
    DelayReveal([=]() {
        printf("出目は %d でした。\n", roll);

        int isOdd = roll % 2;
        printf(isOdd == userGuess ? "正解！\n" : "不正解…\n");
        }, 1500);

    return 0;
}