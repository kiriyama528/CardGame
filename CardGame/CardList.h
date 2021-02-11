#pragma once

#include "Card.h"

/**
 * @brief カード郡の生成と、カードの実態を管理する。
 *        必要なカードは最初に全部生成してしまう。途中からカードが増えたりはしない。
 *        このクラスの破棄時に、カード実態もすべて破棄する。ゲーム終了時に破棄すること。
 * @date 2019/09/04
 * @author kiriyama tomoya
 **/

class CardList {
protected:
	// FIX ME もともとはpublicだった。もしかしたらバグるかも。。。
	typedef enum {
		CARD,
		UNKNOWN  // 未知のclass もしくは未指定
	} CARD_CLASS;

	// *card[N] それぞれのカードを指すポインタの配列。
	// 実態管理用。増減しないし、操作しない。
	vector<Card*> cards;

	virtual CARD_CLASS cardClassBranch(const char* str) const;
	
public:
	CardList();
	//デッキ読み込み付き
	CardList(const string filename);

	// カード郡の実態を破棄
	virtual ~CardList();

	// ファイルからカード情報郡を読み込みデッキを生成する
	virtual bool load(const string filename);

	// 操作用のリストを生成する
	virtual const vector<Card*> shadow() const;
};