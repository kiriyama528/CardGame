/**
 * @brief �J�[�h�Q�[�� R-Rivals 
 * @date 2019/09/13
 * @author kiriyama tomoya
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

//#define DEBUG  // for debug
#define IMG_SCALE 0.5


/**
 * @brief �J�[�h�I�����v���C���[�ɑ����A�I��������
 * @param �I��Ώۂ̎�D
 * @return �I�΂ꂽ��D
 **/
Card *selectCard(Hands &hand) {
	Card *card = NULL;
	do {
		printf("Select card idx.\n > ");
		int idx;
		if (cin >> idx) {
			// ������Ɛ������������ꍇ
			card = hand.out(idx);
		}
		
	} while (card == NULL);

	return card;
}


int main_test(void) {
	// �e�X�g�R�[�h�Bmain()�ƍ����ւ��Ďg�p����

	CardListRivals card_list("card_rival_list.txt");
	const vector<Card *> cards = card_list.shadow(); // ����Ȃ���D
	FieldRivals field;

#if 0
	// �O��
	const vector<int> p1_idx   = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3};
	const vector<int> p2_idx   = { 0, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 2, 3, 4, 5, 6, 7, 3, 4, 5, 6, 7};
	const unsigned int ans_p1[] ={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4, 0, 2, 0, 0, 0, 0, 0, 2, 0, 1, 0};
	const unsigned int ans_p2[] ={ 0, 0, 0, 0, 0, 7, 0, 0, 0, 4, 0, 2, 1, 1, 0, 0, 0, 2, 1, 1, 1, 0, 0, 1, 0, 1};
#elif 0
	// �㔼
	const vector<int> p1_idx    = { 4, 4, 4, 4, 5, 5, 5, 6, 6, 7, 7};
	const vector<int> p2_idx    = { 4, 5, 6, 7, 5, 6, 7, 6, 7, 7, 1};
	const unsigned int ans_p1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
	const unsigned int ans_p2[] = { 0, 3, 1, 1, 0, 2, 1, 0, 2, 0, 4};
	
#elif 0
	// �v���ӊm�F
	const vector<int> p1_idx    = { 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 4};
	const vector<int> p2_idx    = { 0, 1, 2, 3, 4, 5, 6, 4, 7, 7, 2};
	const unsigned int ans_p1[] = { 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 3};
	const unsigned int ans_p2[] = { 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0};

	// 5�͂��ׂĂ̌��ʂ𖳌�������

#elif 1
	// �v���ӊm�F
	const vector<int> p1_idx    = { 6, 1, 6, 1, 6, 2, 6, 3, 6, 4};
	const vector<int> p2_idx    = { 7, 2, 7, 3, 7, 3, 7, 3, 7, 5};
	const unsigned int ans_p1[] = { 0, 1, 0, 0, 0, 0, 0, 1, 0, 1};
	const unsigned int ans_p2[] = { 1, 0, 1, 0, 2, 1, 1, 0, 1, 0};

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

	printf("�S���I��\n");

	// �ꎞ��~
	getchar();

	return 0;
}




int main(void) {
	CardListRivals card_list("card_rival_list.txt");
	Hands hands_p1(card_list.shadow()), hands_p2(card_list.shadow());
	FieldRivals field;

	int wins[2] = { 0, 0 }; // ������

	while (wins[0] < 4 && wins[1] < 4) {
		// ��D�̕\��
		printf(" -- Player 1 hands -- \n");
		hands_p1.showLineUp("P1", 0, 0, IMG_SCALE, false);
		printf(" -- Player 2 hands -- \n");
		hands_p2.showLineUp("P2", 500, 0, IMG_SCALE, true);
		
		CardRivals *card_p1 = NULL;  // �������Ŏg�p����J�[�h
		CardRivals *card_p2 = NULL;  // �������Ŏg�p����J�[�h

		// ����̌��ʂŌ��J���K�v�ȏꍇ
		bool is_rev[2] = { false, false };
		if (field.isReveal(is_rev)) {
			// �ǂ��炩�Ŗ���̌��ʂ��������Ă���
			if (is_rev[0]) {
				printf(" �B�҂̌��ʂɂ��A PLAYER 1 �̓J�[�h�����J���ăv���C���Ă�������\n");
				card_p1 = dynamic_cast<CardRivals*>(selectCard(hands_p1));
				card_p1->show();
			}
			else {
				printf(" �B�҂̌��ʂɂ��A PLAYER 2 �̓J�[�h�����J���ăv���C���Ă�������\n");
				card_p2 = dynamic_cast<CardRivals*>(selectCard(hands_p2));
				card_p2->show();
			}
		}

		// ��D�I��
		if (!card_p1) {
			printf(" ��D�̑I���FPLAYER 1\n");
			card_p1 = dynamic_cast<CardRivals*>(selectCard(hands_p1));
		}
		if (!card_p2) {
			printf(" ��D�̑I���FPLAYER 2\n");
			card_p2 = dynamic_cast<CardRivals*>(selectCard(hands_p2));
		}
		if (card_p1 == NULL || card_p2 == NULL) {
			// Error
			fprintf(stderr, " ERROR: ��D�I�����ɑz��O�̌^���Ԃ���܂���.\n");
			exit(1);
		}

		// ��D�\���̏I��
		hands_p1.destroyAllWindows();
		hands_p2.destroyAllWindows();

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

		printf(" ���ʂ��m�F�����H Enter�L�[\n");
		getchar();
		getchar();
	}

	printf("Game set!\n Score : %d - %d\n", wins[0], wins[1]);
	
	// �ꎞ��~
	getchar();

	return 0;
}