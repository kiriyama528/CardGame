#pragma once

#include <vector>

#include "Card.h"
#include "CardRivals.h"

using namespace std;

class FieldRivals {
private:
#define N_PLAYERS 2
protected:
	// �g�p�����B�擪��NULL�B���ɒǉ����Ă���
	vector<CardRivals*> card_his_p1;
	vector<CardRivals*> card_his_p2;

	int power_up[N_PLAYERS]; 

public:
	FieldRivals();
	~FieldRivals();

	unsigned int playCards(CardRivals * c1, CardRivals * c2);

	// �O�̃J�[�h�̌��ʂ�K�p�����������L�^
	bool enchantment(const CardRivals *c1, const CardRivals *c2);

	// �J�[�h�̌��ʂ𔭓��B���\�͎c��
	bool ability(const CardRivals *c1, const CardRivals *c2);

};
