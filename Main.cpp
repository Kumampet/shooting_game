#include <DxLib.h>
#include "Shooting.h"

Actor player;// プレイヤー
Actor shot[SHOT_NUM];// 弾丸
Actor enemy[ENEMY_NUM];// 敵

int mode;//ゲームモード管理用変数

//ゲーム全体の流れを構成していく
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(true);
	SetMainWindowText("Shooting");
	SetWindowSizeChangeEnableFlag(false);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);
	SetWindowSizeExtendRate(1);
	if(DxLib_Init() == -1) return-1;
	SetOutApplicationLogValidFlag(false);
	SetDrawScreen(DX_SCREEN_BACK);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
	SetFontSize(30);

	int t0;
	mode = GAME;

	init();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		t0 = GetNowCount();
		ClearDrawScreen();

		switch (mode) {
		case TITLE:	// タイトル画面
			break;
		case GAME:	// ゲーム画面
			draw();
			movePlayer();
			moveShot();
			moveEnemy();
			break;
		case OVER:	// ゲームオーバー画面
			break;
		default:
			break;
		}

		while ((GetNowCount() - t0) <= (1000 / 60));
		ScreenFlip();
	}
	DxLib_End(); 
	return 0;
}