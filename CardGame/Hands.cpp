/**
 * @brief èDŠÇ—ƒNƒ‰ƒX
 **/

#include <vector>

#include "Card.h"
#include "Hands.h"

Hands::Hands() {
	// do nothing
}

Hands::Hands(const vector<Card*> _shadow) {
	load(_shadow);
}

int Hands::load(const vector<Card*> _shadow) {
	copy(_shadow.begin(), _shadow.end(), back_inserter(cards_shadow));

	return cards_shadow.size();
}

void Hands::show() {
	for (unsigned int i = 0; i < cards_shadow.size(); i++) {
		show(i);
	}
}

void Hands::show(int idx) {
	cards_shadow[idx]->show();
}

int Hands::in(Card* cs) {
	cards_shadow.push_back(cs);
	return cards_shadow.size();
}

Card* Hands::out(int idx) {
	Card *c = cards_shadow[idx];
	cards_shadow.erase(cards_shadow.begin() + idx);

	return c;
}
