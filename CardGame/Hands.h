#pragma once

#include <vector>

#include "Card.h"

using namespace std;

class Hands {
protected:
	vector<Card*> cards_shadow;

public:
	Hands();
	Hands(const vector<Card*> _shadow);
	~Hands();

	/**
	 * @return 手札の枚数
	 **/
	int load(const vector<Card*> _shadow);

	/**
	 * @brief 手札を全部見る
	 **/
	void show(Card::SHOW_TYPE show_type = Card::SHOW_IMG_TEXT);

	/**
	 * @brief 特定の手札を見る
	 *        ( 0 <= idx < cards_shadow.size() )
	 **/
	void show(int idx, Card::SHOW_TYPE show_type = Card::SHOW_IMG_TEXT);

	// 手札を並べてすべて表示する
	void showLineUp(unsigned int upper, unsigned int left, float scale);

	/**
	 * @return 手札の枚数
	 **/
	int in(Card* cs);

	/**
	 * @return 取り除いた手札。idxが不適切ならNULL

	 **/
	Card* out(int idx);

	void sort();
};