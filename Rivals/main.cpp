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
#if 0
	CardList card_list("card_rival_list.txt");
	Hands hands_p1(card_list.shadow()), hands_p2(card_list.shadow());
	FieldRivals field;

	int wins[2] = { 0, 0 }; // ������

	while (wins[0] < 4 || wins[1] < 4) {
		// ��D�I�� making
		Card *card_p1 = selectCard(hands_p1);
		Card *card_p2 = selectCard(hands_p2);
		/*
		// ��D�̃v���C winner= 0 or 1
		int winner = field.playCards(card_p1, card_p2); 
		wins[winner]++;
		*/
	}

	printf("Game set!\n Score : %d - %d\n", wins[0], wins[1]);
	
	// �ꎞ��~
	getchar();

#endif
	return 0;
}