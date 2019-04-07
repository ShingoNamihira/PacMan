/********************************************************************
** 第５章 ミニゲームをつくる（２）
** レース＆避けゲー
********************************************************************/
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
/***********************************************
* 変数の宣言
***********************************************/
int g_OldKey; // 前回の入力キー
int g_NowKey; // 今回の入力キー
int g_KeyFlg; // 入力キー情報
int g_GameState = 0; // ゲームモード
int g_TitleImage; // 画像用変数
int g_Menu, g_Cone, g_Help, g_End, g_Clear, g_Over; //メニュー画像変数

/***********************************************
* 関数のプロトタイプ宣言
***********************************************/
void GameInit(void); //ゲーム初期化処理
void GameMain(void); //ゲームメイン処理
void DrawGameTitle(void); //タイトル描画処理
void DrawGameOver(void); //ゲームオーバー画面描画処理
void DrawEnd(void); //ゲームエンド描画処理
void DrawHelp(void); //ゲームヘルプ描画処理
void DrawRanking(void); //ランキング描画処理
void InputRanking(void); //ランキング入力
int LoadImages(); // 画像読込み

/***********************************************
* プログラムの開始
***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("PacMan"); // タイトルを設定
	ChangeWindowMode(TRUE); // ウィンドウモードで起動
	if (DxLib_Init() == -1) return -1; // DX ライブラリの初期化処理
	SetDrawScreen(DX_SCREEN_BACK); // 描画先画面を裏にする
	if (LoadImages() == -1) return -1; // 画像読込み関数を呼び出し
									   // ゲームループ
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {
		// 入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;
		ClearDrawScreen(); // 画面の初期化
		switch (g_GameState) {
		case 0:
			DrawGameTitle(); //ゲームタイトル描画処理
			break;
		case 1:
			GameInit(); //ゲーム初期処理
			break;
		case 2:
			DrawRanking(); //ランキング描画処理
			break;
		case 3:
			DrawHelp(); //ゲームヘルプ描画処理
			break;
		case 4:
			DrawEnd(); //ゲームエンド描画処理
			break;
		case 5:
			GameMain(); //ゲームメイン処理
			break;
		case 6:
			DrawGameOver(); //ゲームオーバー描画処理
			break;
		case 7:
			InputRanking(); //ランキング入力処理
			break;
		}
		ScreenFlip(); // 裏画面の内容を表画面に反映
	}
	DxLib_End(); // DX ライブラリ使用の終了処理
	return 0; // ソフトの終了
}
/***********************************************
* ゲームタイトル表示（メニュー画面）
***********************************************/
void DrawGameTitle(void)
{
	static int MenuNo = 0;
	//メニューカーソル移動処理
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (++MenuNo > 3) MenuNo = 0;
	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (--MenuNo < 0) MenuNo = 3;
	}
	// Ｚキーでメニュー選択
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = MenuNo + 1;
	//タイトル画像表示
	DrawGraph(0, 0, g_TitleImage, FALSE);
	// メニュー
	//DrawGraph(120, 200, g_Menu, TRUE);
	// メニューカーソル
	DrawRotaGraph(90, 220 + MenuNo * 40, 0.7f, M_PI / 2, g_Cone, TRUE);

	DrawString(50, 50, "GameState" + MenuNo, GetColor(255, 255, 255));
	DrawString(0, 0, "Title", GetColor(255, 255, 255));
}
/***********************************************
* ゲーム初期処理
***********************************************/
void GameInit(void)
{


	// ゲームメイン処理へ
	g_GameState = 5;
}
/***********************************************
* ゲームランキング描画表示
***********************************************/
void DrawRanking(void)
{
	// Ｚキーでメニュー選択
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = 0;

	DrawString(0, 0, "Ranking", GetColor(255, 255, 255));
}
/***********************************************
* ゲームヘルプ描画処理
***********************************************/
void DrawHelp(void)
{
	//タイトル画像表示
	DrawGraph(0, 0, g_Help, FALSE);

	// Ｚキーでメニュー選択
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = 0;

	DrawString(0, 0, "Help", GetColor(255, 255, 255));
}
/***********************************************
* ゲームエンド描画処理
***********************************************/
void DrawEnd(void)
{
	DrawString(0, 0, "End", GetColor(255, 255, 255));
}
/***********************************************
* ゲームメイン
***********************************************/
void GameMain(void)
{
	// Ｚキーでメニュー選択
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = 0;

	DrawString(0, 0, "Main", GetColor(255, 255, 255));
}
/***********************************************
* ゲームオーバー画面描画処理
***********************************************/
void DrawGameOver(void)
{
	DrawString(0, 0, "GameOver", GetColor(255, 255, 255));
}
/***********************************************
* ランキング入力処理
***********************************************/
void InputRanking(void)
{
	DrawString(0, 0, "Input Ranking", GetColor(255, 255, 255));
}
/***********************************************
* 画像読込み
***********************************************/
int LoadImages()
{
	//タイトル
	if ((g_TitleImage = LoadGraph("images/title.png")) == -1) return -1;
	//メニュー
	if ((g_Menu = LoadGraph("images/menu.png")) == -1) return -1;
	//メニュー
	if ((g_Help = LoadGraph("images/help.png")) == -1) return -1;
	return 0;
}