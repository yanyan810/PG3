#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

//void PrintHellowWorld(void) {
//
//	printf("HellowWorld\n");
//
//}
//
//int main(void) {
//
//	//関数ポインタを宣言
//	void(*pfunc)();
//
//	pfunc = PrintHellowWorld;
//
//	printf("PrintHellowWorldのアドレス=%p\n", PrintHellowWorld);
//	printf("pfuncの内容=%p\n", pfunc);
//	pfunc();
//	//printf("main =%p\n", main);
//
//	return 0;
//
//}

//int add(int a, int b) {
//
//	return a + b;
//
//}
//
//int sub(int a, int b) {
//
//	return a - b;
//
//}
//
//int main() {
//
//	int l = 114;
//	int h = 514;
//
//	int(*calc)(int, int);
//	calc = add;
//	printf("%d\n", calc(l, h));
//
//
//	calc = sub;
//	printf("%d\n",calc(l, h));
//
//	return 0;
//
//}

void ShowResult(int roll, int userGuess) {
    printf("出目は %d でした。\n", roll);

    int isOdd = roll % 2;  // 奇数なら1、偶数なら0
    if (isOdd == userGuess) {
        printf("正解！\n");
    } else {
        printf("不正解…\n");
    }
}

void DelayReveal(void (*fn)(int, int), unsigned int delayMs, int roll, int userGuess) {
    printf("判定中...\n");

    Sleep(delayMs);  // ミリ秒待つ（Windows）

    fn(roll, userGuess);  // ← ShowResult(roll, userGuess) を呼ぶ
}

int main(void) {

    srand((unsigned int)time(NULL)); // 乱数初期化

    int userGuess;
    printf("奇数(1) か 偶数(0) か予想してください : ");
    scanf_s("%d", &userGuess);

    int roll = rand() % 6 + 1;   // 1〜6 を生成

    // 3秒後に結果表示
    DelayReveal(ShowResult, 1500, roll, userGuess);

    return 0;
}