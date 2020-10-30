// 以下の関数をCardDummyに作ったので、showLineUpをテストする
// virtual string show(const string _title, float _scale, unsigned int _upper, unsigned int _left, bool _is_wait) override {
// virtual char *getShowParam(float &_scale, unsigned int &_upper, unsigned int &_left, bool &_is_wait) {

#include "pch.h"
#include "Hands.h"

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1なので

namespace testHand {

	class HandsDummy : public Hands {
	public:
		vector<Card*> getCardsShadow() {
			return cards_shadow;
		}

		vector<string> &getWindowNames(){
			return window_names;
		}

	};

	class HandsDummy_showAll : public HandsDummy {
	public:
		// show関数をこのクラスで再定義しているので、usingがないと親のshow関数が参照できない
		using Hands::show;
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

		virtual bool show(Card::SHOW_TYPE show_type = Card::SHOW_IMG_TEXT) override {
			return Hands::show(show_type);
		}

		bool show(int idx, Card::SHOW_TYPE show_type) override {
			called_idx.push_back(idx);
			called_show_type.push_back(show_type);
			return true;
		}
	};

	class CardDummy : public Card {
	public:
		static const char* NOT_CALLED;
		char called_title_head[128];
		Card::SHOW_TYPE called_show_type = Card::SHOW_IMG_TEXT;
		float scale = -1;
		unsigned int upper = 0;
		unsigned int left = 0;
		bool is_wait = true;
		const int IMG_COLS = 10;
		const int IMG_ROWS = 20;

		CardDummy() : Card() {
			// do nothing
		}

		CardDummy(string plane_text) : Card(plane_text) {
			strcpy(called_title_head, NOT_CALLED);
		}

		char* getTitleHead() {
			return called_title_head;
		}

		Card::SHOW_TYPE getShowType() {
			return called_show_type;
		}

		virtual bool show(const string title_head, SHOW_TYPE type = SHOW_IMG_TEXT) override {
			strcpy(called_title_head, title_head.c_str());
			called_show_type = type;
			return true;
		}

		virtual string show(const string _title, float _scale, unsigned int _upper, unsigned int _left, bool _is_wait) override {			strcpy(called_title_head, _title.c_str());
			strcpy(called_title_head, _title.c_str());
			scale = _scale;
			upper = _upper;
			left = _left;
			is_wait = _is_wait;
			return called_title_head;
		}

		virtual char *getShowParam(float &_scale, unsigned int &_upper, unsigned int &_left, bool &_is_wait) {
			_scale = scale;
			_upper = upper;
			_left = left;
			_is_wait = is_wait;
			return called_title_head;
		}

		virtual bool getImgSize(unsigned int *rows, unsigned int *cols) const override{
			*rows = IMG_ROWS;
			*cols = IMG_COLS;
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

	class UnitTestCardDummy : public ::testing::Test {
	protected:
		virtual void SetUp() {
			// do nothing
		}

		virtual void TearDown() {
			// do nothing
		}
	};

	TEST_F(UnitTestCardDummy, show) {
		string card_csv = "title,ability,sample.png";
		CardDummy card_dummy(card_csv);

		const char* expected = CardDummy::NOT_CALLED;
		const char* actual = card_dummy.getTitleHead();
		EXPECT_STREQ(expected, actual);

		Card::SHOW_TYPE exp_show_type = Card::SHOW_TEXT;
		const string exp_title = "show_title";
		card_dummy.show(exp_title, exp_show_type);
		Card::SHOW_TYPE act_show_type = card_dummy.getShowType();
		const string act_title = card_dummy.getTitleHead();
		EXPECT_EQ(exp_show_type, act_show_type);
		EXPECT_EQ(exp_title, act_title);

	}

	TEST_F(UnitTestCardDummy, show_with_CardDummy) {
		string card_csv = "title,ability,sample.png";
		CardDummy* card_dummy = new CardDummy(card_csv);

		const char* expected = CardDummy::NOT_CALLED;
		const char* actual = card_dummy->getTitleHead();
		EXPECT_STREQ(expected, actual);

		Card::SHOW_TYPE exp_show_type = Card::SHOW_TEXT;
		const string exp_title = "show_title";
		(*card_dummy).show(exp_title, exp_show_type);
		Card::SHOW_TYPE act_show_type = (*card_dummy).getShowType();
		const string act_title = (*card_dummy).getTitleHead();
		EXPECT_EQ(exp_show_type, act_show_type);
		EXPECT_EQ(exp_title, act_title);

	}

	TEST_F(UnitTestCardDummy, show_with_Card) {
		string card_csv = "title,ability,sample.png";
		CardDummy* card_dummy;
		card_dummy = new CardDummy(card_csv);

		Card::SHOW_TYPE exp_show_type = Card::SHOW_TEXT;
		const string exp_title = "show_title";
		card_dummy->show(exp_title, exp_show_type);
		Card::SHOW_TYPE act_show_type = card_dummy->getShowType();
		const string act_title = card_dummy->getTitleHead();
		EXPECT_EQ(exp_show_type, act_show_type);
		EXPECT_EQ(exp_title, act_title);

	}

	TEST_F(UnitTestHands, load) {
		HandsDummy hands;
		EXPECT_EQ(N_CARDS, hands.load(cards));
		vector<Card*> actual = hands.getCardsShadow();
		vector<Card*> expected = cards;
		for (int i = 0; i < expected.size(); i++) {
			EXPECT_EQ(expected[i], actual[i]);
		}

	}

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

		// showを呼び出し前の値を確認
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

	TEST_F(UnitTestHands, show_all) {
		HandsDummy_showAll hands;
		EXPECT_EQ(N_CARDS, hands.load(cards));

		hands.show((Card::SHOW_TYPE)Card::SHOW_TEXT);

		vector<int> act_idx = hands.getIdx();
		vector<Card::SHOW_TYPE> act_show_type = hands.getShowType();
		for (int i = 0; i < N_CARDS; i++) {
			EXPECT_EQ(act_idx[i], i);
			EXPECT_EQ(act_show_type[i], Card::SHOW_TEXT);
		}

	}

	TEST_F(UnitTestHands, showLineUp) {
		HandsDummy hands;
		vector<CardDummy*> cards_dummy(N_CARDS);
		vector<Card*> cards(N_CARDS);  // hands.load()で参照するよう
		for (int i = 0; i < N_CARDS; i++) {
			CardDummy* tmp = new CardDummy(card_str[i]);
			cards_dummy[i] = tmp;
			cards[i] = tmp;
		}
		EXPECT_EQ(N_CARDS, hands.load(cards));

		char title_head[64] = "test_title";
		int upper = 10;
		int left = 20;
		float scale = 2.0;
		bool is_wait = false;
		hands.showLineUp(title_head, upper, left, scale, is_wait);
			
		// showが呼び出されたか確認
		for (int i = 0; i < N_CARDS; i++) {
			char exp_title[256];
			sprintf(exp_title, "%shands[%d]", title_head, i);
			
			int exp_x = left + cards_dummy[i]->IMG_COLS * scale * i;
			float act_scale;
			unsigned int act_upper, act_left;
			bool act_is_wait;
			const char* act_title = cards_dummy[i]->getShowParam(act_scale, act_upper, act_left, act_is_wait);
			EXPECT_EQ(exp_x, act_left);
			EXPECT_EQ(upper, act_upper);
			EXPECT_EQ(scale, act_scale);
			EXPECT_EQ(is_wait, act_is_wait);
			EXPECT_STREQ(exp_title, act_title);
		}

	}

	TEST_F(UnitTestHands, destroyAllWindows) {
		// 下記のようなテストコードを書こうとしたが、
		// Windowの生成などが発生するのでテストにふさわしくない
		//   do nothing
		/*
		HandsDummy hands;
		EXPECT_EQ(N_CARDS, hands.load(cards));
		int expected = 3;
		int actual = hands.getWindowNames().size();
		EXPECT_EQ(expected, actual);

		hands.showLineUp();
		hands.destroyAllWindows();
		expected = 0;
		actual = hands.getWindowNames().size();
		EXPECT_EQ(expected, actual);
		*/
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

}