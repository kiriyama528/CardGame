
#include "pch.h"
#include "Card.h"
#include "CardListRivals.h"
#include "FieldRivals.h"

#include <vector>

using namespace std;


class TestRivalsMain : public ::testing::Test {
protected:
	CardListRivals *card_list_;
	vector<Card *> cards_;
	FieldRivals *field_;

	virtual void SetUp() {
		card_list_ = new CardListRivals("../../test_data/RivalsTest/input/card_rival_list.txt");
		cards_ = card_list_->shadow(); // 消費しない手札
		field_ = new FieldRivals;
	}

	virtual void TearDown() {
		delete card_list_;
		delete field_;
	}

	void PlayAndIsExpected(
		const vector<int> &p1_idx,
		const vector<int> &p2_idx,
		const unsigned int *exp_p1,
		const unsigned int *exp_p2)
	{
		for (int i = 0; i < p1_idx.size(); i++) {
			printf("\ridx:%d, p1_idx:%d, p2_idx:%d\n", i, p1_idx[i], p2_idx[i]);
			// 今勝負で使用するカード
			CardRivals *card_p1 = dynamic_cast<CardRivals*>(cards_[p1_idx[i]]);
			CardRivals *card_p2 = dynamic_cast<CardRivals*>(cards_[p2_idx[i]]);


			// 手札のプレイ winner= 0 or 1
			unsigned int p1_wins, p2_wins;
			EXPECT_TRUE(field_->playCards(card_p1, card_p2, p1_wins, p2_wins));
			
			EXPECT_EQ(exp_p1[i], p1_wins);
			EXPECT_EQ(exp_p2[i], p2_wins);
		}
	}

};


// TODO : 適切な名前にする
TEST_F(TestRivalsMain, case1) {
	const vector<int> p1_idx    = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1};
	const vector<int> p2_idx    = { 0, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7};
	const unsigned int exp_p1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4};
	const unsigned int exp_p2[] = { 0, 0, 0, 0, 0, 7, 0, 0, 0, 4, 0, 2, 1, 1, 0};

	PlayAndIsExpected(p1_idx, p2_idx, exp_p1, exp_p2);
}


// TODO : 適切な名前にする
TEST_F(TestRivalsMain, case2) {
	const vector<int> p1_idx    = { 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3 };
	const vector<int> p2_idx    = { 2, 3, 4, 5, 6, 7, 3, 4, 5, 6, 7 };
	const unsigned int exp_p1[] = { 0, 2, 0, 0, 0, 0, 0, 2, 0, 1, 0 };
	const unsigned int exp_p2[] = { 0, 0, 2, 1, 1, 1, 0, 0, 1, 0, 1 };

	PlayAndIsExpected(p1_idx, p2_idx, exp_p1, exp_p2);
}


// TODO : 適切な名前にする
TEST_F(TestRivalsMain, case3) {
	const vector<int> p1_idx    = { 4, 4, 4, 4, 5, 5, 5, 6, 6, 7, 7 };
	const vector<int> p2_idx    = { 4, 5, 6, 7, 5, 6, 7, 6, 7, 7, 1 };
	const unsigned int exp_p1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
	const unsigned int exp_p2[] = { 0, 3, 1, 1, 0, 2, 1, 0, 2, 0, 4 };

	PlayAndIsExpected(p1_idx, p2_idx, exp_p1, exp_p2);
}


// TODO : 適切な名前にする
TEST_F(TestRivalsMain, careful1) {
	// 要注意確認
	const vector<int> p1_idx = { 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 4 };
	const vector<int> p2_idx = { 0, 1, 2, 3, 4, 5, 6, 4, 7, 7, 2 };
	const unsigned int exp_p1[] = { 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 3 };
	const unsigned int exp_p2[] = { 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0 };

	// 5はすべての効果を無効化した

	PlayAndIsExpected(p1_idx, p2_idx, exp_p1, exp_p2);
}


// TODO : 適切な名前にする
TEST_F(TestRivalsMain, careful2) {
	// 要注意確認
	const vector<int> p1_idx = { 6, 1, 6, 1, 6, 2, 6, 3, 6, 4 };
	const vector<int> p2_idx = { 7, 2, 7, 3, 7, 3, 7, 3, 7, 5 };
	const unsigned int exp_p1[] = { 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 };
	const unsigned int exp_p2[] = { 1, 0, 1, 0, 2, 1, 1, 0, 1, 0 };

	PlayAndIsExpected(p1_idx, p2_idx, exp_p1, exp_p2);
}
