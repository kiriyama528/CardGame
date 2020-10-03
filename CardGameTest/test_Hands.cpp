#include "pch.h"
#include "Hands.h"

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1なので

class HandsDummy : public Hands {
public:
	vector<Card*> getCardsShadow() {
		return cards_shadow;
	}

};

class HandsDummy_showAll : public HandsDummy {
public:
	vector<int> called_idx;
	vector<Card::SHOW_TYPE> called_show_type;

	vector<int> getIdx() {
		return called_idx;
	}

	vector<Card::SHOW_TYPE> getShowType() {
		return called_show_type;
	}

	vector<Card*> getCardsShadow() {
		return cards_shadow;
	}

	bool show(int idx, Card::SHOW_TYPE show_type = Card::SHOW_IMG_TEXT) {
		called_idx.push_back(idx);
		called_show_type.push_back(show_type);
		return true;
	}
};

class CardDummy : public Card {
public:
	static const char* NOT_CALLED;
	char called_title_head[128];
	Card::SHOW_TYPE called_show_type;
	

	CardDummy(string plane_text) : Card(plane_text) {
		strcpy(called_title_head, NOT_CALLED);
	}

	char* getTitleHead() {
		return called_title_head;
	}

	Card::SHOW_TYPE getShowType() {
		return called_show_type;
	}

	virtual bool show(const string title_head, SHOW_TYPE type = SHOW_IMG_TEXT) {
		strcpy(called_title_head, title_head.c_str());
		called_show_type = type;
		return true;
	}

	
};

const char* CardDummy::NOT_CALLED = "not called";

class UnitTestHands : public ::testing::Test {
protected:
	#define N_CARDS 3
	const string card_list_name = "../../test_data/CardGameTest/input/card_list.txt";
	const char* card_str[N_CARDS] = {
		"title1, bility1, 1.png",
		"title2, bility2, 2.png",
		"title3, bility3, 3.png",
	};
	vector<Card*> cards;

	void setCards(vector<Card*> &_cards) {
		_cards.resize(N_CARDS);
		for (int i = 0; i < N_CARDS; i++) {
			_cards[i] = new Card(card_str[i]);
		}
	}

	virtual void SetUp() {
		setCards(cards);
	}

	virtual void TearDown() {
		for (int i = 0; i < N_CARDS; i++) {
			delete cards[i];
		}
	}
};

TEST_F(UnitTestHands, load) {
	HandsDummy hands;
	EXPECT_EQ(N_CARDS, hands.load(cards));
	vector<Card*> actual = hands.getCardsShadow();
	vector<Card*> expected = cards;
	for (int i = 0; i < expected.size(); i++) {
		EXPECT_EQ(expected[i], actual[i]);
	}

}

// making
TEST_F(UnitTestHands, show_text) {
	HandsDummy hands;
	vector<CardDummy*> cards_dummy(N_CARDS);
	vector<Card*> cards(N_CARDS);  // hands.load()で参照するよう
	for (int i = 0; i < N_CARDS; i++) {
		CardDummy* tmp = new CardDummy(card_str[i]);
		cards_dummy[i] = tmp;
		cards[i] = tmp;
	}
	EXPECT_EQ(N_CARDS, hands.load(cards));
	
	// showを呼び出しまえの値を確認
	for (int i = 0; i < N_CARDS; i++) {
		const char* expected = CardDummy::NOT_CALLED;
		const char* actual = cards_dummy[i]->getTitleHead();
		EXPECT_STREQ(expected, actual);
	}

	// showが呼び出されたか確認
	Card::SHOW_TYPE exp_show_type[] = { Card::SHOW_TEXT, Card::SHOW_IMG_TEXT, Card::SHOW_TEXT };
	for (int i = 0; i < N_CARDS; i++) {
		hands.show(i, exp_show_type[i]);
		const char* act_title = cards_dummy[i]->getTitleHead();
		Card::SHOW_TYPE act_show_type = cards_dummy[i]->getShowType();
		EXPECT_STREQ("", act_title);
		EXPECT_EQ(exp_show_type[i], act_show_type);
	}
	
	
}

// making 動作確認待ち
TEST_F(UnitTestHands, show_all) {
	HandsDummy_showAll hands;
	EXPECT_EQ(N_CARDS, hands.load(cards));
	hands.show(Card::SHOW_TEXT);

	vector<int> act_idx = hands.getIdx();
	vector<Card::SHOW_TYPE> act_show_type = hands.getShowType();
	for (int i = 0; i < N_CARDS; i++) {
		EXPECT_EQ(act_idx[i], i);
		EXPECT_EQ(act_show_type[i], Card::SHOW_TEXT);
	}

}

// making
TEST_F(UnitTestHands, showLineUp) {
	Hands hands;

}

// making
TEST_F(UnitTestHands, destroyAllWindows) {
	Hands hands;

}

// making
TEST_F(UnitTestHands, in) {
	Hands hands;

}

// making
TEST_F(UnitTestHands, out) {
	Hands hands;

}

// making
TEST_F(UnitTestHands, sort) {
	Hands hands;

}


