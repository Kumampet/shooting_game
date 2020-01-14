//必要な変数や関数を宣言していく
#pragma once
#ifndef _SHOOTING
#define _SHOOTING
#define WINDOW_WIDTH 640// ウィンドウの横の長さ
#define WINDOW_HEIGHT 480// ウィンドウの縦の長さ

#define TITLE 1// タイトル画面
#define GAME 2// ゲーム画面
#define OVER 3// ゲームオーバー画面

#define SHOT_NUM 20// 弾丸の数
#define ENEMY_NUM 20// 敵の数

typedef struct{
	int x, y;// 座標
	int width, height;// 横の長さ、縦の長さ
	int acc;// 移動速度
	int life;// ライフ
	int graph;// 画像
}Actor;

extern Actor player;// プレイヤー
extern Actor shot[SHOT_NUM];// 弾丸
extern Actor enemy[ENEMY_NUM];// 敵

extern int mode;// ゲームモード管理用変数

void init();// 初期化関数
void draw();// 描画関数
void movePlayer();// プレイヤーの移動関数
void moveShot();// 弾丸の移動関数
void moveEnemy();// 敵の移動関数

#endif
