#include <assert.h>
#include <vector>


// TODO : 適切な名前にする
void Test1() {
	CardListRivals card_list("card_rival_list.txt");
	const vector<Card *> cards = card_list.shadow(); // 消費しない手札
	FieldRivals field;

	const vector<int> p1_idx = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3 };
	const vector<int> p2_idx = { 0, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 2, 3, 4, 5, 6, 7, 3, 4, 5, 6, 7 };
	const unsigned int ans_p1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4, 0, 2, 0, 0, 0, 0, 0, 2, 0, 1, 0 };
	const unsigned int ans_p2[] = { 0, 0, 0, 0, 0, 7, 0, 0, 0, 4, 0, 2, 1, 1, 0, 0, 0, 2, 1, 1, 1, 0, 0, 1, 0, 1 };

	PlayAndExpect();
}


// TODO : 適切な名前にする
void Test2() {
	CardListRivals card_list("card_rival_list.txt");
	const vector<Card *> cards = card_list.shadow(); // 消費しない手札
	FieldRivals field;

	const vector<int> p1_idx = { 4, 4, 4, 4, 5, 5, 5, 6, 6, 7, 7 };
	const vector<int> p2_idx = { 4, 5, 6, 7, 5, 6, 7, 6, 7, 7, 1 };
	const unsigned int ans_p1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
	const unsigned int ans_p2[] = { 0, 3, 1, 1, 0, 2, 1, 0, 2, 0, 4 };

	PlayAndExpect();
}


// TODO : 適切な名前にする
void Test3() {
	CardListRivals card_list("card_rival_list.txt");
	const vector<Card *> cards = card_list.shadow(); // 消費しない手札
	FieldRivals field;

	// 要注意確認
	const vector<int> p1_idx = { 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 4 };
	const vector<int> p2_idx = { 0, 1, 2, 3, 4, 5, 6, 4, 7, 7, 2 };
	const unsigned int ans_p1[] = { 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 3 };
	const unsigned int ans_p2[] = { 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0 };

	// 5はすべての効果を無効化した

	PlayAndExpect();
}


// TODO : 適切な名前にする
void Test4() {
	CardListRivals card_list("card_rival_list.txt");
	const vector<Card *> cards = card_list.shadow(); // 消費しない手札
	FieldRivals field;

	// 要注意確認
	const vector<int> p1_idx = { 6, 1, 6, 1, 6, 2, 6, 3, 6, 4 };
	const vector<int> p2_idx = { 7, 2, 7, 3, 7, 3, 7, 3, 7, 5 };
	const unsigned int ans_p1[] = { 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 };
	const unsigned int ans_p2[] = { 1, 0, 1, 0, 2, 1, 1, 0, 1, 0 };

	PlayAndExpect();
}


// TODO : 適切な引数を入れる
// TODO : 関数名も適切な名前にしろ
// TODO : assert関数を入れろ
void PlayAndExpect(){
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
}


int main(void) {
	Test1();
	Test2();
	Test3();
	Test4();

	fprintf(stderr, "\t[[ %s SUCCESS!! ]]\n", __func__);
	return 0;
}
