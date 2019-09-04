#pragma once

//#include <iostream>
#include <string>
#include <vector>

//#include <algorithm>

#include "Card.h"

using namespace std;

/**
 * @brief カード郡の生成と、カードの実態を管理する。カードは基本的にポインターで使用され、この実態にアクセスする。
 *         std::vector<> 使用したほうが管理が簡単かもしれない
 *        必要なカードは最初に全部生成してしまう予定。途中からカードが増えたりはしない。
 * @date 2019/09/04
 **/
class Deck {
	typedef enum {
		CARD,
		RIVALS,
		UNKNOWN  // 未知のclass もしくは未指定
	} CARD_CLASS;
protected:
	// *card[N] それぞれのカードを指すポインタの配列。
	// 実態管理用。増減しないし、操作しない。
	vector<Card*> cards;

	// 配ったりする見かけ上のカードポインタ。操作用。増減する
	vector<Card*> cards_shadow;

	CARD_CLASS cardClassBranch(const char* str);

public:
	Deck();
	//デッキ読み込み付き
	Deck(string filename);
	~Deck();

	// ファイルからカード情報郡を読み込みデッキを生成する
	virtual bool load(string filename);

	/**
	 * @return カードが引けない場合は NULL
	 **/
	Card* draw();

	/**
	 * @return 残りの山札の枚数
	 **/
	int shuffle();

	/**
	 * @return 残りの山札の枚数
	 **/
	int putTop(Card *c);

	/**
	 * @return 残りの山札の枚数
	 **/
	int putBottom(Card *c);

};
