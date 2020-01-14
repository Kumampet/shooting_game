//�K�v�ȕϐ���֐���錾���Ă���
#pragma once
#ifndef _SHOOTING
#define _SHOOTING
#define WINDOW_WIDTH 640// �E�B���h�E�̉��̒���
#define WINDOW_HEIGHT 480// �E�B���h�E�̏c�̒���

#define TITLE 1// �^�C�g�����
#define GAME 2// �Q�[�����
#define OVER 3// �Q�[���I�[�o�[���

#define SHOT_NUM 20// �e�ۂ̐�
#define ENEMY_NUM 20// �G�̐�

typedef struct{
	int x, y;// ���W
	int width, height;// ���̒����A�c�̒���
	int acc;// �ړ����x
	int life;// ���C�t
	int graph;// �摜
}Actor;

extern Actor player;// �v���C���[
extern Actor shot[SHOT_NUM];// �e��
extern Actor enemy[ENEMY_NUM];// �G

extern int mode;// �Q�[�����[�h�Ǘ��p�ϐ�

void init();// �������֐�
void draw();// �`��֐�
void movePlayer();// �v���C���[�̈ړ��֐�
void moveShot();// �e�ۂ̈ړ��֐�
void moveEnemy();// �G�̈ړ��֐�

#endif
