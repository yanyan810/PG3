#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <functional>
#include <string>
#include <sstream> 
#include <cctype>

using namespace std;

//int main() {
//
//	//====================
//	//整列 (sort)
//	//====================
//
//	//int型の動的配列a (要素数:5)
//	vector<int> a = { -10,321,-3,50,1 };
//
//	cout << "全要素を表示します\n" << endl;
//
//	//全要素を表示
//	for (int i = 0; i < a.size(); i++) {
//		cout << a[i] << endl;
//
//	}
//
//	//昇順に並べ替え
//	sort(a.begin(), a.end());
//	cout << "全要素を表示します\n" << endl;
//
//	//全要素を表示
//	for (int i = 0; i < a.size(); i++) {
//		cout << a[i] << endl;
//
//	}
//
//	//====================
//	//探索する(find)
//	//====================
//
//	cout << "\n探索\n" << endl;
//
//	//探索したいvector用のイテレータ
//	vector<int>::iterator it;
//	//指定した値を探索する
//	it = find(a.begin(), a.end(), -3);
//	//指定した値が存在すれば
//	if (it != a.end()) {
//		cout << *it << endl;
//	}
//
//	//指定した値を探索する
//	it = find(a.begin(), a.end(), 99999);
//	//指定した値が存在すれば
//	if (it != a.end()) {
//		cout << *it << endl;
//	}
//
//
//	//逆順に並べ替え
//	reverse(a.begin(), a.end());
//	cout << "\n逆順にする\n" << endl;
//	for (int i = 0; i < a.size(); i++) {
//		cout << a[i] << endl;//昇順ソートしたやつを逆順にしてる
//	}
//
//	return 0;
//
//}

////===================
////要素数を得る
////===================
//int main(int argc, char const* argv[]) {
//	bool b_array[] = { true,false,true,true };
//
//	size_t n_count = std::count(b_array, b_array + (sizeof(b_array)), true);//<- trueの要素数を得る
//	std::cout << n_count << std::endl;
//
//	return 0;
//
//}

////===================
////置き換える
////===================
//int main(int argc, char const* argv[]) {
//
//	auto dump = [](auto a) {
//		for (auto i : a) {
//
//			std::cout << i << " ";
//
//		}
//
//		std::cout << std::endl;
//		};
//
//	std::array<int, 5> a1{ 1,2,3,4,5 };
//	std::array<int, 5> a2{ 1,2,2,2,5 };
//
//	std::replace(a1.begin(), a1.end(), 3, 0);//2を99に置き換える
//
//	std::replace(a2.begin(), a2.end(), 3, 0);//2を99に置き換える
//
//	dump(a1);
//	dump(a2);
//
//
//	return 0;
//
//}

////===================
////逐次実行
////===================
//
//void display(int i) { cout << i << endl; }
//
//int main(int argc, char const* argv[]) {
//
//	int i_array[] = { 1,2,3 };
//	for_each(begin(i_array), end(i_array), display);
//
//
//	for_each(std::begin(i_array), std::end(i_array), [](int i) {cout << i << endl; });
//
//	return 0;
//
//}

// 数値部分を抽出して整数として返す関数
int ExtractStudentNumber(const string& mail) {
    string digits;
    for (char c : mail) {
        if (isdigit(c)) digits += c;//で数字蓼抜き出す
    }
	return stoi(digits);//数字文字列を整数に変換して返す
}

int main() {

	string text = { "k024g1017@g.neec.ac.jp,k024g0033@g.neec.ac.jp,k024g0057@g.neec.ac.jp,"
        "k024g0020@g.neec.ac.jp,k024g0109@g.neec.ac.jp,k024g1031@g.neec.ac.jp,"
        "k024g0004@g.neec.ac.jp,k024g0027@g.neec.ac.jp,k024g0058@g.neec.ac.jp,"
        "k022g0113@g.neec.ac.jp,k024g0007@g.neec.ac.jp,k024g0083@g.neec.ac.jp,"
        "k024g0110@g.neec.ac.jp,k024g0066@g.neec.ac.jp,k023g0029@g.neec.ac.jp,"
        "k024g1030@g.neec.ac.jp,k024g0106@g.neec.ac.jp,k024g0089@g.neec.ac.jp,"
        "k024g0101@g.neec.ac.jp,k024g0035@g.neec.ac.jp,k024g1025@g.neec.ac.jp,"
        "k024g0059@g.neec.ac.jp,k024g0006@g.neec.ac.jp,k023g0122@g.neec.ac.jp,"
        "k024g0028@g.neec.ac.jp,k024g1024@g.neec.ac.jp,k024g0108@g.neec.ac.jp,"
        "k024g0061@g.neec.ac.jp,k024g0104@g.neec.ac.jp,k024g0038@g.neec.ac.jp,"
        "k024g0032@g.neec.ac.jp,k024g0026@g.neec.ac.jp,k024g0001@g.neec.ac.jp,"
        "k024g0009@g.neec.ac.jp,k024g0112@g.neec.ac.jp,k024g0011@g.neec.ac.jp,"
        "k024g0085@g.neec.ac.jp,k024g0111@g.neec.ac.jp,k024g0045@g.neec.ac.jp,"
        "k024g0103@g.neec.ac.jp,k024g1002@g.neec.ac.jp,k024g0078@g.neec.ac.jp,"
        "k024g0044@g.neec.ac.jp,k024g0008@g.neec.ac.jp,k024g0075@g.neec.ac.jp,"
        "k024g0091@g.neec.ac.jp,k024g0064@g.neec.ac.jp,k024g0051@g.neec.ac.jp,"
        "k024g0093@g.neec.ac.jp,k024g0024@g.neec.ac.jp"};

    // カンマ区切りで分割
    vector<string> mails;
    stringstream ss(text);
    string mail;
    while (getline(ss, mail, ',')) {
        if (!mail.empty()) {
            if (mail.front() == ' ') mail.erase(mail.begin());
            if (mail.back() == ' ') mail.pop_back();
            mails.push_back(mail);
        }
    }

    // 数値部分で昇順ソート
    sort(mails.begin(), mails.end(),
        [](const string& a, const string& b) {
            return ExtractStudentNumber(a) < ExtractStudentNumber(b);
        });

    // 結果出力
    for (auto& m : mails) {
        cout << '"' << m << '"' << "," << endl;
    }
	return 0;

}