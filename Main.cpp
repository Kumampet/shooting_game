#include <DxLib.h>
#include "Shooting.h"

Actor player;// �v���C���[
Actor shot[SHOT_NUM];// �e��
Actor enemy[ENEMY_NUM];// �G

int mode;//�Q�[�����[�h�Ǘ��p�ϐ�

//�Q�[���S�̗̂�����\�����Ă���
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
		case TITLE:	// �^�C�g�����
			break;
		case GAME:	// �Q�[�����
			draw();
			movePlayer();
			moveShot();
			moveEnemy();
			break;
		case OVER:	// �Q�[���I�[�o�[���
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