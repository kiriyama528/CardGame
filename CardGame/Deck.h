#pragma once

#include <string>
#include <vector>

#include "Card.h"
#include "CardList.h"

using namespace std;

/**
 * @brief 操作用カード郡を取り扱う。実態は別の場所（CardList）にある
 * @date 2019/09/04
 **/
class Deck {
protected:
	// 配ったりする見かけ上のカードポインタ。操作用
	vector<Card*> cards_shadow;

public:
	Deck();
	Deck(const vector<Card*> _cards_shadow);
	Deck(CardList &cl);
	~Deck();

	/**
	 * @return 山札の枚数
	 **/
	int load(const vector<Card*> _cards_shadow);

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

	int get_num() { return cards_shadow.size(); }

};
