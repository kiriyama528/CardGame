#pragma once

/**
 * @brief カードゲーム「R-Rivals」のカード効果を処理する場
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/


#include <vector>

#include "Card.h"
#include "CardRivals.h"

using namespace std;

class FieldRivals {
private:
#define N_PLAYERS 2
#define PRINCE_POWER_UP 10

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

	// Index参照に使う
	typedef enum {
		P1 = 0,
		P2
	} PLAYER_NUMBER;

	FieldRivals();
	~FieldRivals();

	/**
	 * @brief カードをプレイする。カードの勝敗を決める
	 * @param c1 PLAYER1 のカードを示すポインタ
	 * @param c2 PLAYER2 のカードを示すポインタ
	 * @param p1_wins 今回の勝負によるPLAYER1 の勝ち星
	 * @param p2_wins 今回の勝負によるPLAYER2 の勝ち星
	 * @return (true) 正常に終了 / 能力解決時に問題発生 (false)
	 **/
	bool playCards(
		CardRivals * c1,
		CardRivals * c2,
		unsigned int &p1_wins,
		unsigned int &p2_wins);

	// @return ひとつでも見つかれば true. 詳細は引数へ
	/**
	 * @brief 次回の勝負でカードを公開するプレイヤーがいるか。いるなら誰か。
	 * @param reveal_flag カード公開フラグのリスト。trueなら公開する
	 *         [0]：PLAYER1
	 *         [1]：PLAYER2
	 * @return (true) カード公開処理が必要 / カード公開処理は不必要 (false)
	 **/
	bool isReveal(bool reveal_flag[N_PLAYERS]);

public:  // protected。テストのためにアクセス制限をpublcへ変更
	// 使用履歴。先頭はNULL。後ろに追加していく
	vector<CardRivals*> card_his_p1;
	vector<CardRivals*> card_his_p2;

	// 今回の勝負のカードの強さ
	int powers[N_PLAYERS];

	// 加算されるpower
	int power_up[N_PLAYERS];
	
	// カード公開フラグ
	// このフラグがたっているプレイヤーは次回カード公開
	bool reveal[N_PLAYERS];

	// 引き分け勝負の記録。勝利時、勝数に加算
	unsigned int draw_storage[N_PLAYERS];

	// 今回の勝負による勝数。出力するたびに0になる
	unsigned int wins[N_PLAYERS];

	/**
	 * @brief 能力を分類してタグ付けする
	 * @param c 分類したいRカードのポインタ
	 * @return cカードのタグ
	 **/
	ABILITY_TAG branchAbility(const CardRivals *c);

	/**
	 * @brief 0：道化の効果、強制引き分け
	 * @return trueのみ
	 **/
	void abilityDraw();

	/**
	 * @brief 1：姫の効果、相手が王子ならゲームに勝利
	 * @param p 自分のPLAYER番号
	 * @param you_tag 対戦相手のRカードタグ
	 * @return true/false 特殊勝利/効果なし
	 **/
	bool abilityPrincess(PLAYER_NUMBER p, ABILITY_TAG you_tag);

	/**
	 * @brief 2：密偵の効果、次回相手はカードを公開してプレイ
	 * @param p 自分のPLAYER番号
	 **/
	void abilitySpy(PLAYER_NUMBER p);

	/**
	 * @brief 3：暗殺者の効果、強弱反転
	 **/
	void abilityReverse();

	/**
	 * @brief 4：大臣の効果、勝てば2勝利となるように引き分けストックを調整
	 * @param p 自分のPLAYER番号
	 **/
	void abilityDouble(PLAYER_NUMBER p);

	// 5：魔術師の効果は、処理中に解決、関数化できない（メモ）

	/**
	 * @brief 6：将軍の効果、次回の勝負で数字が+2される
	 * @param p 自分のPLAYER番号
	 **/
	void abilityPowerUp(PLAYER_NUMBER p, int up);

	/**
	 * @brief 7：王子の効果、ほぼ勝利できる
	 * @param p 自分のPLAYER番号
	 **/
	void abilityWin(PLAYER_NUMBER p);

	/**
	 * @brief 前のカードの効果を適用した強さを記録
	 * @param c1 今回のPLAYER1 のカードへのポインタ
	 * @param c2 今回のPLAYER2 のカードへのポインタ
	 * @return (true) 正常終了 / 異常発生 (false)
	 **/
	bool enchantment(const CardRivals *c1, const CardRivals *c2);

	/**
	 * @brief カードの効果を発動
	 * @param c1 今回のPLAYER1 のカードへのポインタ
	 * @param c2 今回のPLAYER2 のカードへのポインタ
	 * @return (true) 正常終了 / 異常発生 (false)
	 **/
	bool ability(const CardRivals *c1, const CardRivals *c2);

};
