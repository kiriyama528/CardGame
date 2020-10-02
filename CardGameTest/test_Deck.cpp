#include <vector>

#include "pch.h"
#include "Deck.h"


#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1なので

class DeckDummy : public Deck {
public:
	vector<Card*> getCardsShadow(){
		return cards_shadow;
	}

};

class UnitTestDeck : public ::testing::Test {
protected:
	#define N_CARDS 3
	const string card_list_name = "../../test_data/CardGameTest/input/card_list.txt";
	const char* card_str[N_CARDS] = {
		"title1, bility1, 1.png",
		"title2, bility2, 2.png",
		"title3, bility3, 3.png",
	};
	vector<Card*> cards;

	virtual void SetUp() {
		cards.resize(N_CARDS);
		for (int i = 0; i < N_CARDS; i++) {
			cards[i] = new Card(card_str[i]);
		}
	}

	virtual void TearDown() {
		for (int i = 0; i < N_CARDS; i++) {
			delete cards[i];
		}
	}
	
};

TEST_F(UnitTestDeck, load) {
	DeckDummy deck;
	EXPECT_EQ(N_CARDS, deck.load(cards));
	vector<Card*> actual = deck.getCardsShadow();
	EXPECT_EQ(actual.size(), cards.size());
	for (int i = 0; i < actual.size(); i++) {
		EXPECT_EQ(actual[i], cards[i]);
	}
	
}

TEST_F(UnitTestDeck, draw) {
	DeckDummy deck;
	// エラーチェック
	EXPECT_EQ(NULL, deck.draw());

	// 正常処理チェック
	EXPECT_EQ(N_CARDS, deck.load(cards));
	vector<Card*> expected = deck.getCardsShadow();
	for (int i = 0; i < expected.size(); i++) {
		Card* actual = deck.draw();
		EXPECT_EQ(expected[i], actual);
	}

}

TEST_F(UnitTestDeck, shuffle) {
	DeckDummy deck;
	EXPECT_NO_FATAL_FAILURE(deck.shuffle());  // TESTが適切ではないかも
	EXPECT_EQ(N_CARDS, deck.load(cards));
	vector<Card*> cards = deck.getCardsShadow();
	Card* expected[N_CARDS] = { cards[2], cards[0], cards[1] };

	srand(0);
	deck.shuffle();
	vector<Card*> actual = deck.getCardsShadow();
	for (int i = 0; i < actual.size(); i++) {
		EXPECT_EQ(expected[i], actual[i]);
	}

}

TEST_F(UnitTestDeck, putTop) {
	DeckDummy deck;
	EXPECT_EQ(N_CARDS, deck.load(cards));
	string card_text = "test_title,test_ability,img.png";
	Card in_card(card_text);
	deck.putTop(&in_card);

	vector<Card*> actual = deck.getCardsShadow();
	Card* expected[] = { &in_card, cards[0], cards[1], cards[2] };
	for (int i = 0; i < actual.size(); i++) {
		EXPECT_EQ(expected[i], actual[i]);
	}

}

TEST_F(UnitTestDeck, putBottom) {
	DeckDummy deck;
	EXPECT_EQ(N_CARDS, deck.load(cards));
	string card_text = "test_title,test_ability,img.png";
	Card in_card(card_text);
	deck.putBottom(&in_card);

	vector<Card*> actual = deck.getCardsShadow();
	Card* expected[] = { cards[0], cards[1], cards[2], &in_card };
	for (int i = 0; i < actual.size(); i++) {
		EXPECT_EQ(expected[i], actual[i]);
	}
}

TEST_F(UnitTestDeck, get_num) {	
	DeckDummy deck;
	int expected = 0;
	int actual = deck.get_num();
	EXPECT_EQ(expected, actual);

	EXPECT_EQ(N_CARDS, deck.load(cards));
	EXPECT_EQ(N_CARDS, deck.get_num());
}

TEST_F(UnitTestDeck, searchIdx) {
	DeckDummy deck;
	EXPECT_EQ(N_CARDS, deck.load(cards));
	string search_name[] = { "title2", "title3", "title1" };
	int expected[] = { 1, 2, 0 };
	for (int i = 0; i < deck.get_num(); i++) {
		int actual = deck.searchIdx(search_name[i]);
		EXPECT_EQ(expected[i], actual);
	}
	
}

TEST_F(UnitTestDeck, searchDraw) {
	DeckDummy deck;
	EXPECT_EQ(N_CARDS, deck.load(cards));
	string search_name[] = { "title2", "title3", "title1" };;
	Card* expected[] = { cards[1], cards[2], cards[0]};
	for (int i = 0; i < deck.get_num(); i++) {
		Card* actual = deck.searchDraw(search_name[i]);
		EXPECT_EQ(expected[i], actual);
	}
}