/**
 * @brief �J�[�h�Q�[�� R-Rivals 
 **/

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1�Ȃ̂�
#pragma comment(lib, "CardGame")


#include <iostream>

#include "CardList.h"
#include "Deck.h"
#include "Hands.h"
#include "Card.h"
#include "FieldRivals.h"

using namespace std;


/**
 * @brief �J�[�h�I�����v���C���[�ɑ����A�I��������
 **/
Card *selectCard(Hands &hand) {
	Card *card;
	do {
		printf("Select card idx.\n");
		int idx;
		cin >> idx;
		card = hand.out(idx);
	} while (card != NULL);

	return card;
}


int main(void) {
	CardList card_list("card_rival_list.txt");
	Hands hands_p1(card_list.shadow()), hands_p2(card_list.shadow());
	FieldRivals field;

	int wins[2] = { 0, 0 }; // ������

	while (wins[0] < 4 || wins[1] < 4) {
		CardRivals *card_p1 = NULL;  // �������Ŏg�p����J�[�h
		CardRivals *card_p2 = NULL;  // �������Ŏg�p����J�[�h

		// ����̌��ʂŌ��J���K�v�ȏꍇ
		bool is_rev[2] = { false, false };
		if (field.isReveal(is_rev)) {
			// �ǂ��炩�Ŗ���̌��ʂ��������Ă���
			if (is_rev[0]) {
				card_p1 = dynamic_cast<CardRivals*>(selectCard(hands_p1));
				card_p1->show();
			}
			else {
				card_p2 = dynamic_cast<CardRivals*>(selectCard(hands_p2));
				card_p2->show();
			}
		}


		// ��D�I�� making
		if (!card_p1) {
			card_p1 = dynamic_cast<CardRivals*>(selectCard(hands_p1));
		}
		if (!card_p2) {
			card_p2 = dynamic_cast<CardRivals*>(selectCard(hands_p2));
		}
		if (card_p1 == NULL || card_p2 == NULL) {
			// Error
			fprintf(stderr, " ERROR: ��D�I�����ɑz��O�̌^���Ԃ���܂���.\n");
			exit(1);
		}

		// �I��������D�̌��J
		card_p1->show();
		card_p2->show();
		
		// ��D�̃v���C winner= 0 or 1
		unsigned int p1_wins, p2_wins;
		field.playCards(card_p1, card_p2, p1_wins, p2_wins); 
		wins[0] += p1_wins;
		wins[1] += p2_wins;
	}

	printf("Game set!\n Score : %d - %d\n", wins[0], wins[1]);
	
	// �ꎞ��~
	getchar();

	return 0;
}