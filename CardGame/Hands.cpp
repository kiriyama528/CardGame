/**
 * @brief 手札管理クラス
 **/

#include <vector>
#include <algorithm>  // for sort

#include "Card.h"
#include "Hands.h"

Hands::Hands() {
	// do nothing
}

Hands::Hands(const vector<Card*> _shadow) {
	load(_shadow);
}

Hands::~Hands() {
	cards_shadow.clear();
}

int Hands::load(const vector<Card*> _shadow) {
	copy(_shadow.begin(), _shadow.end(), back_inserter(cards_shadow));

	return cards_shadow.size();
}

void Hands::show(Card::SHOW_TYPE show_type) {
	for (unsigned int i = 0; i < cards_shadow.size(); i++) {
		show(i, show_type);
	}
}

void Hands::show(int idx, Card::SHOW_TYPE show_type) {
	cards_shadow[idx]->show("", show_type);
}

int Hands::in(Card* cs) {
	cards_shadow.push_back(cs);
	return cards_shadow.size();
}

Card* Hands::out(int idx) {
	// Error
	if (idx < 0 || cards_shadow.size() <= idx) {
		return NULL;
	}

	Card *c = cards_shadow[idx];
	cards_shadow.erase(cards_shadow.begin() + idx);

	return c;
}

void Hands::sort() {
	// test 本当にうまくいくかどうか
	std::sort(
		cards_shadow.begin()
		, cards_shadow.end()
		, [](const Card* x, const Card* y) {return *x < *y; });
}
