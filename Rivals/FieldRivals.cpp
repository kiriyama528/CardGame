

#include "Card.h"
#include "FieldRivals.h"
#include "CardRivals.h"

FieldRivals::FieldRivals() {
	card_his_p1.push_back(NULL);
	card_his_p2.push_back(NULL);

	power_up[0] = 0;
	power_up[1] = 0;
}

FieldRivals::~FieldRivals() {
	card_his_p1.clear();
	card_his_p2.clear();
}

unsigned int FieldRivals::playCards(CardRivals *c1, CardRivals *c2) {
	unsigned int winner_idx = 0; // 0 or 1

	// 前のカードの効果を適用した強さを記録
	enchantment(c1, c2); // making

	// カードの効果を発動。かつ能力残留
	ability(c1, c2); // making


	card_his_p1.emplace_back(c1);
	card_his_p2.emplace_back(c2);

	//winner_idx = ??

	return winner_idx;
}


bool FieldRivals::enchantment(const CardRivals *c1, const CardRivals *c2) {


	

	return true;
}


bool FieldRivals::ability(const CardRivals *c1, const CardRivals *c2) {

	// power_up[0] += ??

	return true;
}
