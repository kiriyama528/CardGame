#pragma once

#include <vector>

#include "Card.h"
#include "CardRivals.h"

using namespace std;

class FieldRivals {
private:
#define N_PLAYERS 2
protected:
	// 使用履歴。先頭はNULL。後ろに追加していく
	vector<CardRivals*> card_his_p1;
	vector<CardRivals*> card_his_p2;

	int power_up[N_PLAYERS]; 

public:
	FieldRivals();
	~FieldRivals();

	unsigned int playCards(CardRivals * c1, CardRivals * c2);

	// 前のカードの効果を適用した強さを記録
	bool enchantment(const CardRivals *c1, const CardRivals *c2);

	// カードの効果を発動。かつ能力残留
	bool ability(const CardRivals *c1, const CardRivals *c2);

};
