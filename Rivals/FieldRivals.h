#pragma once

#include <vector>

#include "Card.h"
#include "CardRivals.h"

using namespace std;

class FieldRivals {
public:
	typedef enum {
		DRAW = 0,	// 0: 次回に持ち越し
		PRINCESS,	// 1: 王子ならゲームに勝利
		SPY,		// 2: 次回は相手公開
		REVERSE,	// 3: 強弱反転
		DOUBLE,		// 4: ２勝
		INVALID,	// 5: 無効化
		POWER_2,	// 6: 次回は+2
		WIN,		// 7: 絶対勝利
		UNKNOWN
	} ABILITY_TAG;

	// Index 参照に使う
	typedef enum {
		P1 = 0,
		P2
	} PLAYER_NUMBER;

private:
#define N_PLAYERS 2
protected:
	// 使用履歴。先頭はNULL。後ろに追加していく
	vector<CardRivals*> card_his_p1;
	vector<CardRivals*> card_his_p2;

	int power_up[N_PLAYERS];
	int powers[N_PLAYERS];
	bool reveal[N_PLAYERS]; // このフラグがたっているプレイヤーは次回カード公開
	unsigned int draw_storage[N_PLAYERS];
	unsigned int wins[N_PLAYERS]; // 出力するたびに0にする

	// 能力を分類してタグ付けする
	ABILITY_TAG branchAbility(const CardRivals *c);


	// 0
	bool abilityDraw();

	// 1
	bool abilityPrincess(PLAYER_NUMBER p, ABILITY_TAG you_tag);

	// 2
	bool abilitySpy(PLAYER_NUMBER p);

	// 3
	bool abilityReverse();

	// 4
	bool abilityDouble(PLAYER_NUMBER p);

	// 6
	bool abilityPowerUp(PLAYER_NUMBER p, int up);

	// 7
	bool abilityWin(PLAYER_NUMBER p);

	// 前のカードの効果を適用した強さを記録
	bool enchantment(const CardRivals *c1, const CardRivals *c2);

	// カードの効果を発動。かつ能力残留
	bool ability(const CardRivals *c1, const CardRivals *c2);

public:
	FieldRivals();
	~FieldRivals();

	bool playCards(
			CardRivals * c1,
			CardRivals * c2,
			unsigned int &p1_wins,
			unsigned int &p2_wins);

	// @return ひとつでも見つかれば true. 詳細は引数へ
	bool isReveal(bool * reveal_flag);


};
