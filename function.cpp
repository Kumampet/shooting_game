//関数の定義をしていく
#include <DxLib.h>
#include "Shooting.h"

// 初期化関数
void init() {
	// プレイヤー
	player.x= 100;
	player.y= 200;
	player.height= 50;
	player.width= 50;
	player.acc= 8;
	player.life= 5;

	// 弾丸
	for(int i = 0; i < SHOT_NUM; i++) {
		shot[i].x = 0;
		shot[i].y = 0;
		shot[i].height = 10;
		shot[i].width = 10;
		shot[i].acc = 10;
		shot[i].life = 0;
	}

	// 敵
	for(int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].x = 0;
		enemy[i].y = 0;
		enemy[i].height = 50;
		enemy[i].width = 50;
		enemy[i].acc = 5;
		enemy[i].life = 0;
	}
}

// 描画関数
void draw() {
	// プレイヤーの描画
	DrawBox(player.x, player.y, player.x+ player.width, player.y+ player.height, GetColor(255, 0, 0), TRUE);
	DrawFormatString(player.x, player.y, GetColor(0, 0, 0), "%d", player.life);

	// 弾丸の描画
	for(int i = 0; i < SHOT_NUM; i++) {
		if(shot[i].life > 0)
			DrawBox(shot[i].x, shot[i].y, shot[i].x + shot[i].width, shot[i].y + shot[i].height, GetColor(255, 255, 255), TRUE);
	}

	// 敵の描画
	for(int i = 0; i < ENEMY_NUM; i++) {
		if(enemy[i].life > 0) {
			DrawBox(enemy[i].x, enemy[i].y, enemy[i].x + enemy[i].width, enemy[i].y + enemy[i].height, GetColor(0, 0, 255), TRUE);
			DrawFormatString(enemy[i].x, enemy[i].y, GetColor(0, 0, 0), "%d", enemy[i].life);
		}
	}
}

//プレイヤーの移動関数
void movePlayer() {
	// 右へ移動
	if(CheckHitKey(KEY_INPUT_RIGHT) > 0) {
		player.x += player.acc;
		// 画面外へ行かないようにする
		if(player.x + player.width > WINDOW_WIDTH) {
			player.x = WINDOW_WIDTH - player.width;
		}
	}
	// 左へ移動
	if(CheckHitKey(KEY_INPUT_LEFT) > 0) {
		player.x -= player.acc;
		// 画面外へ行かないようにする
		if(player.x < 0) {
			player.x= 0;
		}
	}
	// 下へ移動
	if(CheckHitKey(KEY_INPUT_DOWN) > 0) {
		player.y += player.acc;
		// 画面外へ行かないようにする
		if(player.y + player.height > WINDOW_HEIGHT) {
			player.y = WINDOW_HEIGHT - player.height;
		}
	}
	// 上へ移動
	if(CheckHitKey(KEY_INPUT_UP) > 0) {
		player.y -= player.acc;
		// 画面外へ行かないようにする
		if(player.y < 0) {
			player.y = 0;
		}
	}
}

// 弾丸の移動関数
void moveShot() {
	static int lug = 10; // 間隔
	
	lug--;
	
	// Zが押されている、かつ間隔が空いている
	if(CheckHitKey(KEY_INPUT_Z) > 0 && lug <= 0) {
		// まだ発射していない弾丸を発射する
		for(int i = 0; i < SHOT_NUM; i++) {
			if(shot[i].life == 0) {
				shot[i].life = 1;
				shot[i].x = player.x + player.width;
				shot[i].y = player.y + player.height / 2;
				lug = 10; break;
			}
		}
	}
	
	// 弾丸の移動
	for(int i = 0; i < SHOT_NUM; i++) {
		if(shot[i].life == 1) {
			shot[i].x += shot[i].acc;
			// 画面外に出たら、ライフを0にする(画面に描画しない)
			if(shot[i].x + shot[i].width > WINDOW_WIDTH) {
				shot[i].x = 0;
				shot[i].y = 0;
				shot[i].life = 0;
			}
		}
	}
}

// 敵の移動関数
void moveEnemy() {
	// 敵の出現
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
	// 敵の移動
	for(int i = 0; i < ENEMY_NUM; i++) {
		if(enemy[i].life > 0) {
			enemy[i].x -= enemy[i].acc;
			// 敵と弾丸の当たり判定
			for (int j = 0; j < SHOT_NUM; j++) {
				if (shot[j].life > 0) {
					if (hit(enemy[i], shot[j]) == 1) {
						enemy[i].life--;
						shot[j].life = 0;
					}
				}
			}
			// 画面外に出たらライフを0にする(描画しない)
			if(enemy[i].x + enemy[i].width < 0) {
				enemy[i].x = 0;
				enemy[i].y = 0;
				enemy[i].life = 0;
			}
		}
	}
}

// 当たり判定
int hit(Actor a1, Actor a2) {
	// ぶつかっている
	if (a1.x < a2.x + a2.width && a2.x < a1.x + a1.width && a1.y < a2.y + a2.height && a2.y < a1.y + a1.height)
		return 1;
	// ぶつかっていない
	else
		return 0;
}

