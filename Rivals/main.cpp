/**
 * @brief カードゲーム R-Rivals 
 **/

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1なので
#pragma comment(lib, "CardGame")


#include <iostream>

#include "CardList.h"
#include "Deck.h"
#include "Hands.h"
#include "Card.h"
#include "FieldRivals.h"

using namespace std;


/**
 * @brief カード選択をプレイヤーに促し、選択させる
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

	int wins[2] = { 0, 0 }; // 勝利数

	while (wins[0] < 4 || wins[1] < 4) {
		CardRivals *card_p1 = NULL;  // 今勝負で使用するカード
		CardRivals *card_p2 = NULL;  // 今勝負で使用するカード

		// 密偵の効果で公開が必要な場合
		bool is_rev[2] = { false, false };
		if (field.isReveal(is_rev)) {
			// どちらかで密偵の効果が発動している
			if (is_rev[0]) {
				card_p1 = dynamic_cast<CardRivals*>(selectCard(hands_p1));
				card_p1->show();
			}
			else {
				card_p2 = dynamic_cast<CardRivals*>(selectCard(hands_p2));
				card_p2->show();
			}
		}


		// 手札選択 making
		if (!card_p1) {
			card_p1 = dynamic_cast<CardRivals*>(selectCard(hands_p1));
		}
		if (!card_p2) {
			card_p2 = dynamic_cast<CardRivals*>(selectCard(hands_p2));
		}
		if (card_p1 == NULL || card_p2 == NULL) {
			// Error
			fprintf(stderr, " ERROR: 手札選択時に想定外の型が返されました.\n");
			exit(1);
		}

		// 選択した手札の公開
		card_p1->show();
		card_p2->show();
		
		// 手札のプレイ winner= 0 or 1
		unsigned int p1_wins, p2_wins;
		field.playCards(card_p1, card_p2, p1_wins, p2_wins); 
		wins[0] += p1_wins;
		wins[1] += p2_wins;
	}

	printf("Game set!\n Score : %d - %d\n", wins[0], wins[1]);
	
	// 一時停止
	getchar();

	return 0;
}