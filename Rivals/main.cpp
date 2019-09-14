/**
 * @brief カードゲーム R-Rivals 
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1なので
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
 * @brief カード選択をプレイヤーに促し、選択させる
 * @param 選択対象の手札
 * @return 選ばれた手札
 **/
Card *selectCard(Hands &hand) {
	Card *card = NULL;
	do {
		printf("Select card idx.\n > ");
		int idx;
		if (cin >> idx) {
			// きちんと数字が入った場合
			card = hand.out(idx);
		}
		
	} while (card == NULL);

	return card;
}


int main_test(void) {
	// テストコード。main()と差し替えて使用する

	CardListRivals card_list("card_rival_list.txt");
	const vector<Card *> cards = card_list.shadow(); // 消費しない手札
	FieldRivals field;

#if 0
	// 前半
	const vector<int> p1_idx   = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3};
	const vector<int> p2_idx   = { 0, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 2, 3, 4, 5, 6, 7, 3, 4, 5, 6, 7};
	const unsigned int ans_p1[] ={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4, 0, 2, 0, 0, 0, 0, 0, 2, 0, 1, 0};
	const unsigned int ans_p2[] ={ 0, 0, 0, 0, 0, 7, 0, 0, 0, 4, 0, 2, 1, 1, 0, 0, 0, 2, 1, 1, 1, 0, 0, 1, 0, 1};
#elif 0
	// 後半
	const vector<int> p1_idx    = { 4, 4, 4, 4, 5, 5, 5, 6, 6, 7, 7};
	const vector<int> p2_idx    = { 4, 5, 6, 7, 5, 6, 7, 6, 7, 7, 1};
	const unsigned int ans_p1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
	const unsigned int ans_p2[] = { 0, 3, 1, 1, 0, 2, 1, 0, 2, 0, 4};
	
#elif 0
	// 要注意確認
	const vector<int> p1_idx    = { 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 4};
	const vector<int> p2_idx    = { 0, 1, 2, 3, 4, 5, 6, 4, 7, 7, 2};
	const unsigned int ans_p1[] = { 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 3};
	const unsigned int ans_p2[] = { 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0};

	// 5はすべての効果を無効化した

#elif 1
	// 要注意確認
	const vector<int> p1_idx    = { 6, 1, 6, 1, 6, 2, 6, 3, 6, 4};
	const vector<int> p2_idx    = { 7, 2, 7, 3, 7, 3, 7, 3, 7, 5};
	const unsigned int ans_p1[] = { 0, 1, 0, 0, 0, 0, 0, 1, 0, 1};
	const unsigned int ans_p2[] = { 1, 0, 1, 0, 2, 1, 1, 0, 1, 0};

#endif

	for (int i = 0; i < p1_idx.size(); i++) {
		printf("\ridx:%d", i);
		// 今勝負で使用するカード
		CardRivals *card_p1 = dynamic_cast<CardRivals*>(cards[p1_idx[i]]);
		CardRivals *card_p2 = dynamic_cast<CardRivals*>(cards[p2_idx[i]]);
			
		
		// 手札のプレイ winner= 0 or 1
		unsigned int p1_wins, p2_wins;
		if (!field.playCards(card_p1, card_p2, p1_wins, p2_wins)) {
			// 能力解決時に問題発生
			fprintf(stderr, " ERROR:カード能力解決時に問題発生\n 終了します\n");
			// 選択した手札の公開
			card_p1->show("p1:");
			card_p2->show("p2:");
			getchar();
			getchar();
			getchar();
			exit(1);
		}

		if (ans_p1[i] != p1_wins || ans_p2[i] != p2_wins) {
			printf(" index[%d] のとき(card[%d] - card[%d])予想と違う結果となりました。\n", i, p1_idx[i], p2_idx[i]);
			printf(" 予想：　(P1) %d - %d (P2)\n", ans_p1[i], ans_p2[i]);
			printf(" 結果：　(P1) %d - %d (P2)\n", p1_wins, p2_wins);
			printf("\n");
		}
	}

	printf("全部終了\n");

	// 一時停止
	getchar();

	return 0;
}




int main(void) {
	CardListRivals card_list("card_rival_list.txt");
	Hands hands_p1(card_list.shadow()), hands_p2(card_list.shadow());
	FieldRivals field;

	int wins[2] = { 0, 0 }; // 勝利数

	while (wins[0] < 4 && wins[1] < 4) {
		// 手札の表示
		printf(" -- Player 1 hands -- \n");
		hands_p1.showLineUp("P1", 0, 0, IMG_SCALE, false);
		printf(" -- Player 2 hands -- \n");
		hands_p2.showLineUp("P2", 500, 0, IMG_SCALE, true);
		
		CardRivals *card_p1 = NULL;  // 今勝負で使用するカード
		CardRivals *card_p2 = NULL;  // 今勝負で使用するカード

		// 密偵の効果で公開が必要な場合
		bool is_rev[2] = { false, false };
		if (field.isReveal(is_rev)) {
			// どちらかで密偵の効果が発動している
			if (is_rev[0]) {
				printf(" 隠者の効果により、 PLAYER 1 はカードを公開してプレイしてください\n");
				card_p1 = dynamic_cast<CardRivals*>(selectCard(hands_p1));
				card_p1->show();
			}
			else {
				printf(" 隠者の効果により、 PLAYER 2 はカードを公開してプレイしてください\n");
				card_p2 = dynamic_cast<CardRivals*>(selectCard(hands_p2));
				card_p2->show();
			}
		}

		// 手札選択
		if (!card_p1) {
			printf(" 手札の選択：PLAYER 1\n");
			card_p1 = dynamic_cast<CardRivals*>(selectCard(hands_p1));
		}
		if (!card_p2) {
			printf(" 手札の選択：PLAYER 2\n");
			card_p2 = dynamic_cast<CardRivals*>(selectCard(hands_p2));
		}
		if (card_p1 == NULL || card_p2 == NULL) {
			// Error
			fprintf(stderr, " ERROR: 手札選択時に想定外の型が返されました.\n");
			exit(1);
		}

		// 手札表示の終了
		hands_p1.destroyAllWindows();
		hands_p2.destroyAllWindows();

		// 選択した手札の公開
		card_p1->show();
		card_p2->show();

		// 手札のプレイ winner= 0 or 1
		unsigned int p1_wins, p2_wins;
		if ( !field.playCards(card_p1, card_p2, p1_wins, p2_wins)) {
			// 能力解決時に問題発生
			fprintf(stderr, " ERROR:カード能力解決時に問題発生\n 終了します\n");
			getchar();
			getchar();
			getchar();
			exit(1);
		}
		wins[0] += p1_wins;
		wins[1] += p2_wins;

		// 現在の勝敗
		printf("(P1) %d - %d (P2)\n", wins[0], wins[1]);

		printf(" 結果を確認した？ Enterキー\n");
		getchar();
		getchar();
	}

	printf("Game set!\n Score : %d - %d\n", wins[0], wins[1]);
	
	// 一時停止
	getchar();

	return 0;
}