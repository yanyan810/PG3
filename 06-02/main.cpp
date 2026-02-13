#include <Novice.h>
#include <cstring>
#include "MapChipFiled.h"

const char kWindowTitle[] = "LE2B_26_ミヤザワ_ハルヒ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// マップチップ
	MapChipField map;
	map.StartLoadMapChipCsvAsync("resources/map.csv"); 

	// 描画用（画面上のタイルサイズ）
	const int tilePx = 24;
	const int offX = 32;
	const int offY = 64;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		  // 読み込み完了してたら確定（メインスレッド）
		map.ApplyLoadedIfReady();

		// Rで再読み込み（確認用）
		if (preKeys[DIK_R] == 0 && keys[DIK_R] != 0) {
			map.StartLoadMapChipCsvAsync("resources/map.csv");
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		for (uint32_t y = 0; y < map.GetNumBlockVirtical(); ++y) {
			for (uint32_t x = 0; x < map.GetNumBlockHorizontal(); ++x) {
				auto t = map.GetMapChipTypeByIndex(x, y);

				int px = offX + (int)x * tilePx;
				int py = offY + (int)y * tilePx;

				if (t == MapChipField::MapChipType::kBlock) {
					Novice::DrawBox(px, py, tilePx, tilePx, 0.0f, 0xFFFFFFFF, kFillModeSolid);
				}
			}
		}

		//if (map.IsLoading()) {
		//	Novice::ScreenPrintf(32, 16, "Loading CSV... (async)");
		//}
		//else {
		//	Novice::ScreenPrintf(32, 16, "Loaded. Press R to reload.");
		//}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
