//関数の定義をしていく
#include <DxLib.h>
#include "Shooting.h"

// 初期化関数
void init() {
	// スコア
	score = 0;

	// プレイヤー
	player.x= 100;
	player.y= 200;
	player.height= 64;
	player.width= 64;
	player.acc= 8;
	player.life= 5;
	player.graph = LoadGraph("Data/graph/player.png");

	// 弾丸
	for(int i = 0; i < SHOT_NUM; i++) {
		shot[i].x = 0;
		shot[i].y = 0;
		shot[i].acc = 10;
		shot[i].life = 0;
		shot[i].graph = LoadGraph("Data/graph/shot.png"); 
		GetGraphSize(shot[i].graph, &shot[i].width, &shot[i].height);
	}

	// 敵
	for(int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].x = 0;
		enemy[i].y = 0;
		enemy[i].height = 64;
		enemy[i].width = 64;
		enemy[i].acc = 5;
		enemy[i].life = 0;
		enemy[i].graph = LoadGraph("Data/graph/enemy.png");
	}
}

// 描画関数
void draw() {
	// プレイヤーの描画
	DrawExtendGraph(player.x, player.y, player.x + player.width, player.y + player.height, player.graph, TRUE);
	DrawFormatString(player.x, player.y, GetColor(0, 0, 0), "%d", player.life);

	// 弾丸の描画
	for(int i = 0; i < SHOT_NUM; i++) {
		if(shot[i].life > 0)
			DrawGraph(shot[i].x, shot[i].y, shot[i].graph, TRUE);
	}

	// 敵の描画
	for(int i = 0; i < ENEMY_NUM; i++) {
		if(enemy[i].life > 0) {
			DrawExtendGraph(enemy[i].x, enemy[i].y, enemy[i].x + enemy[i].width, enemy[i].y + enemy[i].height, enemy[i].graph, TRUE);
			DrawFormatString(enemy[i].x, enemy[i].y, GetColor(0, 0, 0), "%d", enemy[i].life);
		}
	}

	// スコアの描画
	DrawFormatString(420, 10, GetColor(255, 255, 255), "SCORE: %6d", score);
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

	// プレイヤーと敵の当たり判定
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy[i].life > 0) {
			if (hit(player, enemy[i]) == 1) {
				player.life--;
				enemy[i].life = 0;
				// ゲームオーバー判定
				if (player.life == 0)
					mode = OVER;
			}
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
				shot[i].y = player.y;
				lug = 10; 
				break;
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
						// 敵を倒したらスコア加算
						if (enemy[i].life == 0)
							score += 1000;
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

// タイトル画面
void title() {
	DrawFormatString(100, 100, GetColor(255, 255, 255), "タイトル");
	// Zキーが押されたら、ゲームを開始する
	if (CheckHitKey(KEY_INPUT_Z) > 0) {
		init();
		mode = GAME;
	}
}

// ゲーム画面
void game() {
	movePlayer();
	moveShot();
	moveEnemy();
	draw();
}

// ゲームオーバー画面
void over() {
	DrawFormatString(100, 100, GetColor(255, 255, 255), "ゲームオーバー");
	DrawFormatString(100, 150, GetColor(255, 255, 255), "スペースキーでタイトルに戻る");
	// Spaceキーが押されたら、タイトル画面へ移動する
	if (CheckHitKey(KEY_INPUT_SPACE) > 0) {
		mode = TITLE;
	}
}

