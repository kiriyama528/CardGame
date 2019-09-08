#pragma once

#include <vector>

#include "Card.h"
#include "CardRivals.h"

using namespace std;

class FieldRivals {
public:
	typedef enum {
		DRAW = 0,	// 0: ����Ɏ����z��
		PRINCESS,	// 1: ���q�Ȃ�Q�[���ɏ���
		SPY,		// 2: ����͑�����J
		REVERSE,	// 3: ���㔽�]
		DOUBLE,		// 4: �Q��
		INVALID,	// 5: ������
		POWER_2,	// 6: �����+2
		WIN,		// 7: ��Ώ���
		UNKNOWN
	} ABILITY_TAG;

	// Index �Q�ƂɎg��
	typedef enum {
		P1 = 0,
		P2
	} PLAYER_NUMBER;

private:
#define N_PLAYERS 2
protected:
	// �g�p�����B�擪��NULL�B���ɒǉ����Ă���
	vector<CardRivals*> card_his_p1;
	vector<CardRivals*> card_his_p2;

	int power_up[N_PLAYERS];
	int powers[N_PLAYERS];
	bool reveal[N_PLAYERS]; // ���̃t���O�������Ă���v���C���[�͎���J�[�h���J
	unsigned int draw_storage[N_PLAYERS];
	unsigned int wins[N_PLAYERS]; // �o�͂��邽�т�0�ɂ���

	// �\�͂𕪗ނ��ă^�O�t������
	ABILITY_TAG branchAbility(const CardRivals *c);


	// 0
	bool abilityDraw();

	// 1
	bool abilityPrincess(PLAYER_NUMBER p, ABILITY_TAG you_tag);

	// 2
	bool abilitySpy(PLAYER_NUMBER p);

	// 3
	bool abilityReverse();

	// 4
	bool abilityDouble(PLAYER_NUMBER p);

	// 6
	bool abilityPowerUp(PLAYER_NUMBER p, int up);

	// 7
	bool abilityWin(PLAYER_NUMBER p);

	// �O�̃J�[�h�̌��ʂ�K�p�����������L�^
	bool enchantment(const CardRivals *c1, const CardRivals *c2);

	// �J�[�h�̌��ʂ𔭓��B���\�͎c��
	bool ability(const CardRivals *c1, const CardRivals *c2);

public:
	FieldRivals();
	~FieldRivals();

	bool playCards(
			CardRivals * c1,
			CardRivals * c2,
			unsigned int &p1_wins,
			unsigned int &p2_wins);

	// @return �ЂƂł�������� true. �ڍׂ͈�����
	bool isReveal(bool * reveal_flag);


};
