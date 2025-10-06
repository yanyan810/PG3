#include <stdlib.h>
#include <vector>
#include <iostream>
#include <list>
using namespace std;

int main() {

	const char* base1970[] = {
	  "Tokyo","Kanda","Akihabara","Okachimachi","Ueno","Uguisudani",
	  "Nippori", /* (1971にNishi-Nipporiが追加) */
	  "Tabata","Komagome","Sugamo","Otsuka","Ikebukuro","Mejiro",
	  "Takadanobaba","Shin-Okubo","Shinjuku","Yoyogi","Harajuku","Shibuya",
	  "Ebisu","Meguro","Gotanda","Osaki","Shinagawa",
	  /* (2020にTakanawaGatewayが追加) */
	  "Tamachi","Hamamatsucho","Shimbashi","Yurakucho"
	};

	list<const char*> y1970(begin(base1970), end(base1970));

	auto y2019 = y1970;

	for (auto it = y2019.begin(); it != y2019.end(); ++it) {
		if (strcmp(*it, "Nippori") == 0) {
			y2019.insert(next(it), "Nishi-Nippori");    // 直後に挿入

		}
	}

	auto y2022 = y2019;

	for (auto it = y2022.begin(); it != y2022.end(); ++it) {
		if (strcmp(*it, "Tamachi") == 0) {
			y2022.insert(next(it), "Takanawa Gateway");    // 直後に挿入

		}
	}

	printf("%s (%d stations)\n", "1970", (int)y1970.size());
	for (auto s : y1970) printf("%s |", s);
	printf("\n\n");

	printf("%s (%d stations)\n", "2019", (int)y2019.size());
	for (auto s : y2019) printf("%s |", s);
	printf("\n\n");

	printf("%s (%d stations)\n", "1970", (int)y2022.size());
	for (auto s : y2022) printf("%s |", s);
	printf("\n\n");

	////float型の可変長配列 c (要素数:3)
	//vector<float> c = { 0.0f,1.0f,2.0f };

	//printf("%f\n", c[1]);

	//c[1] = -1.5f;

	//printf("%f\n", c[1]);

	////int型の可変長配列
	//vector<int> d;

	//d.push_back(10);

	//int size = d.size();

	//for (int i = 0; i < size; i++) {
	//	printf("%d\n", d[i]);
	//}

	////vectorの使用法
	//vector<int> e = { 1,2,3};

	//vector<int>::iterator it;

	//it = e.begin();

	//cout << *it << endl;

	//it++;

	//cout << *it << endl;

	////string型の可変長配列
	//vector<string> f = { "ローソン","ファミマ","セブン" };

	//for (vector<string>::iterator it = f.begin(); it != f.end(); it++) {
	//	cout << *it << endl;
	//}

	////要素の削除

	////intがたの可変長配列
	//vector<int> g = { 1,2,3 };

	//g.erase(g.begin()+1);

	//g.pop_back();


	////残りの要素数が出てくる
	//for (int v : g) {
	//	cout << v << " ";
	//}
	//cout << endl;

	//====================
	//namespaceでstdを省略
	//==================== 

	//list<int> lst(33, 4);//要素数33、初期値4で初期化

	//list<int> lst2{114, 514, 364};//要素数3、114,514,364で初期化

	//// --- lst の出力 ---
	//cout << "lst:" << endl;
	//for (int v : lst) {
	//	cout << v << " ";
	//}
	//cout << endl;

	//// --- lst2 の出力 ---
	//cout << "lst2:" << endl;
	//for (int v : lst2) {
	//	cout << v << " ";
	//}
	//cout << endl;


	//list<int>::iterator itr;

	//itr = lst2.begin();
	//cout << *itr << endl;
	//itr = lst2.end();
	//cout << *itr << endl;
	//itr--;
	//cout << *itr << endl;
	//itr--;
	//cout << *itr << endl;

	////全ての要素を参照する
	//for (itr = lst.begin(); itr != lst.end(); itr++) {
	//	cout << *itr << "\n";
	//}

	//list<int>list3{ 1,2,3 };
	//auto it2 = list3.begin();//0番目の要素
	//cout << *it2;//1が出る
	//*it2 = 9;//0番目の要素を9に変更
	//cout << *it2;//9が出る
	//it2++;//1番目の要素
	//*it2 = 10;//1番目の要素を8に変更
	//cout << *it2;//10が出る
	////要素の追加
	//list3.push_front(0);//先頭に0を追加
	//list3.push_back(20);//末尾に20を追加

	//// --- lst3 の出力 ---
	//cout << "\nlst3:" << endl;
	//for (int v : list3) {
	//	cout << v << " ";
	//}
	//cout << endl;

	//list<int> lst4{ 1,3,5,7,10 };
	//for (list<int>::iterator it = lst4.begin(); it != lst4.end(); ++it) {

	//	if (*it == 3) {

	//		it = lst4.insert(it, 0);//3の前に2を挿入
	//		++it;//0を1に変更
	//	}
	//}

	//// 出力
	//for (int v : lst4) {
	//	cout << v << " ";
	//}
	//cout << endl;



	return 0;
}