//�֐��̒�`�����Ă���
#include <DxLib.h>
#include "Shooting.h"

// �������֐�
void init() {
	// �X�R�A
	score = 0;

	// �v���C���[
	player.x= 100;
	player.y= 200;
	player.height= 50;
	player.width= 50;
	player.acc= 8;
	player.life= 5;

	// �e��
	for(int i = 0; i < SHOT_NUM; i++) {
		shot[i].x = 0;
		shot[i].y = 0;
		shot[i].height = 10;
		shot[i].width = 10;
		shot[i].acc = 10;
		shot[i].life = 0;
	}

	// �G
	for(int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].x = 0;
		enemy[i].y = 0;
		enemy[i].height = 50;
		enemy[i].width = 50;
		enemy[i].acc = 5;
		enemy[i].life = 0;
	}
}

// �`��֐�
void draw() {
	// �v���C���[�̕`��
	DrawBox(player.x, player.y, player.x+ player.width, player.y+ player.height, GetColor(255, 0, 0), TRUE);
	DrawFormatString(player.x, player.y, GetColor(0, 0, 0), "%d", player.life);

	// �e�ۂ̕`��
	for(int i = 0; i < SHOT_NUM; i++) {
		if(shot[i].life > 0)
			DrawBox(shot[i].x, shot[i].y, shot[i].x + shot[i].width, shot[i].y + shot[i].height, GetColor(255, 255, 255), TRUE);
	}

	// �G�̕`��
	for(int i = 0; i < ENEMY_NUM; i++) {
		if(enemy[i].life > 0) {
			DrawBox(enemy[i].x, enemy[i].y, enemy[i].x + enemy[i].width, enemy[i].y + enemy[i].height, GetColor(0, 0, 255), TRUE);
			DrawFormatString(enemy[i].x, enemy[i].y, GetColor(0, 0, 0), "%d", enemy[i].life);
		}
	}

	// �X�R�A�̕`��
	DrawFormatString(420, 10, GetColor(255, 255, 255), "SCORE: %6d", score);
}

//�v���C���[�̈ړ��֐�
void movePlayer() {
	// �E�ֈړ�
	if(CheckHitKey(KEY_INPUT_RIGHT) > 0) {
		player.x += player.acc;
		// ��ʊO�֍s���Ȃ��悤�ɂ���
		if(player.x + player.width > WINDOW_WIDTH) {
			player.x = WINDOW_WIDTH - player.width;
		}
	}
	// ���ֈړ�
	if(CheckHitKey(KEY_INPUT_LEFT) > 0) {
		player.x -= player.acc;
		// ��ʊO�֍s���Ȃ��悤�ɂ���
		if(player.x < 0) {
			player.x= 0;
		}
	}
	// ���ֈړ�
	if(CheckHitKey(KEY_INPUT_DOWN) > 0) {
		player.y += player.acc;
		// ��ʊO�֍s���Ȃ��悤�ɂ���
		if(player.y + player.height > WINDOW_HEIGHT) {
			player.y = WINDOW_HEIGHT - player.height;
		}
	}
	// ��ֈړ�
	if(CheckHitKey(KEY_INPUT_UP) > 0) {
		player.y -= player.acc;
		// ��ʊO�֍s���Ȃ��悤�ɂ���
		if(player.y < 0) {
			player.y = 0;
		}
	}

	// �v���C���[�ƓG�̓����蔻��
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy[i].life > 0) {
			if (hit(player, enemy[i]) == 1) {
				player.life--;
				enemy[i].life = 0;
				// �Q�[���I�[�o�[����
				if (player.life == 0)
					mode = OVER;
			}
		}
	}
}

// �e�ۂ̈ړ��֐�
void moveShot() {
	static int lug = 10; // �Ԋu
	
	lug--;
	
	// Z��������Ă���A���Ԋu���󂢂Ă���
	if(CheckHitKey(KEY_INPUT_Z) > 0 && lug <= 0) {
		// �܂����˂��Ă��Ȃ��e�ۂ𔭎˂���
		for(int i = 0; i < SHOT_NUM; i++) {
			if(shot[i].life == 0) {
				shot[i].life = 1;
				shot[i].x = player.x + player.width;
				shot[i].y = player.y + player.height / 2;
				lug = 10; break;
			}
		}
	}
	
	// �e�ۂ̈ړ�
	for(int i = 0; i < SHOT_NUM; i++) {
		if(shot[i].life == 1) {
			shot[i].x += shot[i].acc;
			// ��ʊO�ɏo����A���C�t��0�ɂ���(��ʂɕ`�悵�Ȃ�)
			if(shot[i].x + shot[i].width > WINDOW_WIDTH) {
				shot[i].x = 0;
				shot[i].y = 0;
				shot[i].life = 0;
			}
		}
	}
}

// �G�̈ړ��֐�
void moveEnemy() {
	// �G�̏o��
	for(int i = 0; i < ENEMY_NUM; i++) {
		if(GetRand(100) == 0) {
			if(enemy[i].life == 0) {
				enemy[i].life = 5;
				enemy[i].x = WINDOW_WIDTH;
				enemy[i].y = GetRand(WINDOW_HEIGHT - enemy[i].height);
				break;
			}
		}
	}
	// �G�̈ړ�
	for(int i = 0; i < ENEMY_NUM; i++) {
		if(enemy[i].life > 0) {
			enemy[i].x -= enemy[i].acc;
			// �G�ƒe�ۂ̓����蔻��
			for (int j = 0; j < SHOT_NUM; j++) {
				if (shot[j].life > 0) {
					if (hit(enemy[i], shot[j]) == 1) {
						enemy[i].life--;
						shot[j].life = 0;
						// �G��|������X�R�A���Z
						if (enemy[i].life == 0)
							score += 1000;
					}
				}
			}
			// ��ʊO�ɏo���烉�C�t��0�ɂ���(�`�悵�Ȃ�)
			if(enemy[i].x + enemy[i].width < 0) {
				enemy[i].x = 0;
				enemy[i].y = 0;
				enemy[i].life = 0;
			}
		}
	}
}

// �����蔻��
int hit(Actor a1, Actor a2) {
	// �Ԃ����Ă���
	if (a1.x < a2.x + a2.width && a2.x < a1.x + a1.width && a1.y < a2.y + a2.height && a2.y < a1.y + a1.height)
		return 1;
	// �Ԃ����Ă��Ȃ�
	else
		return 0;
}

// �^�C�g�����
void title() {
	DrawFormatString(100, 100, GetColor(255, 255, 255), "�^�C�g��");
	// Z�L�[�������ꂽ��A�Q�[�����J�n����
	if (CheckHitKey(KEY_INPUT_Z) > 0) {
		init();
		mode = GAME;
	}
}

// �Q�[�����
void game() {
	movePlayer();
	moveShot();
	moveEnemy();
	draw();
}

// �Q�[���I�[�o�[���
void over() {
	DrawFormatString(100, 100, GetColor(255, 255, 255), "�Q�[���I�[�o�[");
	DrawFormatString(100, 150, GetColor(255, 255, 255), "�X�y�[�X�L�[�Ń^�C�g���ɖ߂�");
	// Space�L�[�������ꂽ��A�^�C�g����ʂֈړ�����
	if (CheckHitKey(KEY_INPUT_SPACE) > 0) {
		mode = TITLE;
	}
}

