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
#include <cstdio>

#include "CardListRivals.h"
#include "Deck.h"
#include "Hands.h"
#include "Card.h"
#include "FieldRivals.h"

using namespace std;

#define DEBUG  // for debug


/**
 * @brief �J�[�h�I�����v���C���[�ɑ����A�I��������
 **/
Card *selectCard(Hands &hand) {
	Card *card;
	do {
		printf("Select card idx.\n");
		int idx;
		cin >> idx;  // fix me �����Ȃǂ̗\��O������ƃo�O��
		
		card = hand.out(idx);
	} while (card == NULL);

	return card;
}


int main(void) {
	// �e�X�g�R�[�h

	CardListRivals card_list("card_rival_list.txt");
	const vector<Card *> cards = card_list.shadow(); // ����Ȃ���D
	FieldRivals field;

#if 0
	const vector<int> p1_idx   = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3};
	const vector<int> p2_idx   = { 0, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 2, 3, 4, 5, 6, 7, 3, 4, 5, 6, 7};
	const unsigned int ans_p1[] ={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4, 0, 2, 0, 0, 0, 0, 0, 2, 0, 1, 0};
	const unsigned int ans_p2[] ={ 0, 0, 0, 0, 0, 7, 0, 0, 0, 4, 0, 2, 1, 1, 0, 0, 0, 2, 1, 1, 1, 0, 0, 1, 0, 1};
#else
	const vector<int> p1_idx = {};
	const vector<int> p2_idx = {};
	const unsigned int ans_p1[] = {};
	const unsigned int ans_p2[] = {};

#endif

	for (int i = 0; i < p1_idx.size(); i++) {
		printf("\ridx:%d", i);
		// �������Ŏg�p����J�[�h
		CardRivals *card_p1 = dynamic_cast<CardRivals*>(cards[p1_idx[i]]);
		CardRivals *card_p2 = dynamic_cast<CardRivals*>(cards[p2_idx[i]]);
			
		
		// ��D�̃v���C winner= 0 or 1
		unsigned int p1_wins, p2_wins;
		if (!field.playCards(card_p1, card_p2, p1_wins, p2_wins)) {
			// �\�͉������ɖ�蔭��
			fprintf(stderr, " ERROR:�J�[�h�\�͉������ɖ�蔭��\n �I�����܂�\n");
			// �I��������D�̌��J
			card_p1->show("p1:");
			card_p2->show("p2:");
			getchar();
			getchar();
			getchar();
			exit(1);
		}

		if (ans_p1[i] != p1_wins || ans_p2[i] != p2_wins) {
			printf(" index[%d] �̂Ƃ�(card[%d] - card[%d])�\�z�ƈႤ���ʂƂȂ�܂����B\n", i, p1_idx[i], p2_idx[i]);
			printf(" �\�z�F�@(P1) %d - %d (P2)\n", ans_p1[i], ans_p2[i]);
			printf(" ���ʁF�@(P1) %d - %d (P2)\n", p1_wins, p2_wins);
			printf("\n");
		}
	}

	//
	printf("�S���I��\n");

	// �ꎞ��~
	getchar();

	return 0;
}




int main_src(void) {
	CardListRivals card_list("card_rival_list.txt");
	Hands hands_p1(card_list.shadow()), hands_p2(card_list.shadow());
	FieldRivals field;

	int wins[2] = { 0, 0 }; // ������

	while (wins[0] < 4 && wins[1] < 4) {
		// ��D�̕\��
#ifdef DEBUG
		printf(" -- Player 1 hands -- \n");
		hands_p1.show(Card::SHOW_TEXT);
		printf(" -- Player 2 hands -- \n");
		hands_p2.show(Card::SHOW_TEXT);
#else
		printf(" -- Player 1 hands -- \n");
		hands_p1.show();
		printf(" -- Player 2 hands -- \n");
		hands_p2.show();
#endif
		
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
		if ( !field.playCards(card_p1, card_p2, p1_wins, p2_wins)) {
			// �\�͉������ɖ�蔭��
			fprintf(stderr, " ERROR:�J�[�h�\�͉������ɖ�蔭��\n �I�����܂�\n");
			getchar();
			getchar();
			getchar();
			exit(1);
		}
		wins[0] += p1_wins;
		wins[1] += p2_wins;

		// ���݂̏��s
		printf("(P1) %d - %d (P2)\n", wins[0], wins[1]);

		getchar();
		getchar();
	}

	printf("Game set!\n Score : %d - %d\n", wins[0], wins[1]);
	
	// �ꎞ��~
	getchar();

	return 0;
}