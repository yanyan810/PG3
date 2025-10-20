#include <iostream>
using namespace std;

int main() {
    const int normalWage = 1226;  // 一般的な時給
    int recursiveWage = 100;      // 再帰的な最初の時給
    int totalNormal = 0;
    int totalRecursive = 0;
    int hour = 20;

  for(int i=0;i<hour;i++){

        // 一般的な賃金体系
        totalNormal += normalWage;

        // 再帰的な賃金体系
        totalRecursive += recursiveWage;

        //// 比較
        //if (totalRecursive > totalNormal) {
        //    cout << "→ " << hour << "時間働くと再帰的な賃金体系の方が得です！" << endl;
        //    break;
        //}

        // 次の時給を計算（前の時給×2 - 50）
        recursiveWage = recursiveWage * 2 - 50;
    }

    cout << "一般的な賃金体系の合計: " << totalNormal << "円" << endl;
    cout << "再帰的な賃金体系の合計: " << totalRecursive << "円" << endl;

    return 0;
}
