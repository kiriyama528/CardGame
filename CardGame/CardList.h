#pragma once

#include "Card.h"

/**
 * @brief カード郡の生成と、カードの実態を管理する。
 *        必要なカードは最初に全部生成してしまう。途中からカードが増えたりはしない。
 *        このクラスの破棄時に、カード実態もすべて破棄する。ゲーム終了時に破棄すること。
 * @date 2019/09/04
 **/
class CardList {
	typedef enum {
		CARD,
		RIVALS,
		UNKNOWN  // 未知のclass もしくは未指定
	} CARD_CLASS;
protected:
	// *card[N] それぞれのカードを指すポインタの配列。
	// 実態管理用。増減しないし、操作しない。
	vector<Card*> cards;
	
	CARD_CLASS cardClassBranch(const char* str);

public:
	CardList();
	//デッキ読み込み付き
	CardList(string filename);

	// カード郡の実態を破棄
	~CardList();

	// ファイルからカード情報郡を読み込みデッキを生成する
	virtual bool load(string filename);

	// 操作用のリストを生成する
	const vector<Card*> shadow();
};