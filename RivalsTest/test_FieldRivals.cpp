#include "pch.h"
#include "CardListRivals.h"
#include "FieldRivals.h"

class DummyCardRivals : public CardRivals {
	/* メモ
	string name;         // カードの名前
	string ability_text; // カード効果のテキスト文
	cv::Mat img;         // カードの画像
	unsigned int power;
	*/
public:
	DummyCardRivals() {
		// do nothing
	}

	DummyCardRivals(
		const char* _name,
		const char* _ability_text,
		unsigned int _power)
	{
		name = _name;
		ability_text = _ability_text;
		power = _power;
	}

	virtual ~DummyCardRivals() {
		// do nothing
	}

	void SetAbility(const char *str) {
		ability_text = str;
	}

	void SetPower(unsigned int inp_power) {
		power = inp_power;
	}
};

class UnitTestFieldRivals : public ::testing::Test {
protected:
	FieldRivals *field_;
	virtual void SetUp() {
		field_ = new FieldRivals;
	}

	virtual void TearDown() {
		delete field_;
	}

};


TEST_F(UnitTestFieldRivals, branchAbility)
{
	const int test_num = 9;
	const char* ability_txt[] = {
		"次回に持ち越し",
		"王子ならゲームに勝利",
		"次回は相手公開",
		"強弱反転",
		"２勝",
		"無効化",
		"次回は＋２",
		"絶対勝利",
		"Unknown"
	};

	FieldRivals::ABILITY_TAG expect[] = {
		FieldRivals::DRAW,
		FieldRivals::PRINCESS,
		FieldRivals::SPY,
		FieldRivals::REVERSE,
		FieldRivals::DOUBLE,
		FieldRivals::INVALID,
		FieldRivals::POWER_2,
		FieldRivals::WIN,
		FieldRivals::UNKNOWN
	};

	for (int i = 0; i < test_num; i++) {
		DummyCardRivals card_rival;
		card_rival.SetAbility(ability_txt[i]);
		FieldRivals::ABILITY_TAG actual;
		actual = field_->branchAbility(&card_rival);
		EXPECT_EQ(actual, expect[i]);
	}

}


TEST_F(UnitTestFieldRivals, abilityDraw)
{
	field_->powers[FieldRivals::P1] = -1;  // set dummy
	field_->powers[FieldRivals::P2] = -1;  // set dummy

	field_->abilityDraw();

	int actual_p1 = field_->powers[FieldRivals::P1];
	int expected_p1 = 0;
	EXPECT_EQ(actual_p1, expected_p1);

	int actual_p2 = field_->powers[FieldRivals::P2];
	int expected_p2 = 0;
	EXPECT_EQ(actual_p2, expected_p2);
}


TEST_F(UnitTestFieldRivals, abilityPrincess)
{
	/// 王子以外との戦闘
	const int n_opponent_card_tag = 8;
	FieldRivals::ABILITY_TAG opponent_card_tag[] = {
		FieldRivals::DRAW,
		FieldRivals::PRINCESS,
		FieldRivals::SPY,
		FieldRivals::REVERSE,
		FieldRivals::DOUBLE,
		FieldRivals::INVALID,
		FieldRivals::POWER_2,
		FieldRivals::UNKNOWN
	};

	field_->wins[FieldRivals::P1] = 0;
	int expected_wins = 0;
	for (int i = 0; i < n_opponent_card_tag; i++) {
		EXPECT_FALSE(field_->abilityPrincess(FieldRivals::P1, opponent_card_tag[i]));
		EXPECT_EQ(field_->wins[FieldRivals::P1], expected_wins);
	}

	/// 王子との戦闘
	EXPECT_TRUE(field_->abilityPrincess(FieldRivals::P1, FieldRivals::WIN));
	expected_wins = 4;
	EXPECT_EQ(field_->wins[FieldRivals::P1], expected_wins);
}


TEST_F(UnitTestFieldRivals, abilitySpy)
{
	field_->abilitySpy(FieldRivals::P1);
	EXPECT_FALSE(field_->reveal[FieldRivals::P1]);
	EXPECT_TRUE(field_->reveal[FieldRivals::P2]);

	field_->reveal[0] = false;
	field_->reveal[1] = false;
	field_->abilitySpy(FieldRivals::P2);
	EXPECT_TRUE(field_->reveal[FieldRivals::P1]);
	EXPECT_FALSE(field_->reveal[FieldRivals::P2]);

	field_->reveal[0] = false;
	field_->reveal[1] = false;
	field_->abilitySpy(FieldRivals::P2);
	field_->abilitySpy(FieldRivals::P1);
	EXPECT_FALSE(field_->reveal[FieldRivals::P1]);
	EXPECT_FALSE(field_->reveal[FieldRivals::P2]);
}


TEST_F(UnitTestFieldRivals, abilityReverse)
{
	field_->powers[FieldRivals::P1] = 1;
	field_->powers[FieldRivals::P2] = 2;
	field_->abilityReverse();
	int expected = -1;
	EXPECT_EQ(expected, field_->powers[FieldRivals::P1]);
	expected = -2;
	EXPECT_EQ(expected, field_->powers[FieldRivals::P2]);
}


TEST_F(UnitTestFieldRivals, abilityDouble)
{
	field_->draw_storage[FieldRivals::P1] = 0;
	field_->abilityDouble(FieldRivals::P1);
	int expected = 1;
	EXPECT_EQ(expected, field_->draw_storage[FieldRivals::P1]);
}


TEST_F(UnitTestFieldRivals, abilityPowerUp)
{
	field_->power_up[FieldRivals::P1] = 0;
	int expected = 2;
	field_->abilityPowerUp(FieldRivals::P1, expected);
	EXPECT_EQ(expected, field_->power_up[FieldRivals::P1]);
}


TEST_F(UnitTestFieldRivals, abilityWin)
{
	field_->power_up[FieldRivals::P1] = 0;
	field_->abilityWin(FieldRivals::P1);
	int expected = PRINCE_POWER_UP;
	EXPECT_EQ(expected, field_->powers[FieldRivals::P1]);
}


TEST_F(UnitTestFieldRivals, enchantment)
{
	DummyCardRivals card_rival[2];
	card_rival[0].SetPower(1);
	card_rival[1].SetPower(2);

	field_->powers[0] = 0;
	field_->powers[1] = 0;
	field_->power_up[0] = 1;
	field_->power_up[1] = 2;
	field_->reveal[0] = true;
	field_->reveal[1] = false;

	EXPECT_TRUE(field_->enchantment(&card_rival[0], &card_rival[1]));

	int expected_powers[2] = { 2, 4 };
	int *actual_powers = field_->powers;
	EXPECT_EQ(expected_powers[0], actual_powers[0]);
	EXPECT_EQ(expected_powers[1], actual_powers[1]);
	EXPECT_EQ(0, field_->power_up[0]);
	EXPECT_EQ(0, field_->power_up[1]);
	EXPECT_FALSE(field_->reveal[0]);
	EXPECT_FALSE(field_->reveal[1]);
	EXPECT_EQ(0, field_->power_up[1]);
}


TEST_F(UnitTestFieldRivals, isReveal)
{
	const int test_num = 4;
	bool reveals[4][2] = {
		{ true, true},
		{ true, false},
		{false, true},
		{false, false}
	};
	bool expected[4] = { true, true, true, false };
	
	for (int i = 0; i < test_num; i++) {
		field_->reveal[0] = reveals[i][0];
		field_->reveal[1] = reveals[i][1];
		bool actual_aug[2];
		bool actual_ret = field_->isReveal(actual_aug);
		EXPECT_EQ(actual_aug[0], reveals[i][0]);
		EXPECT_EQ(actual_aug[1], reveals[i][1]);
		EXPECT_EQ(expected[i], actual_ret);
	}
}


TEST_F(UnitTestFieldRivals, ability)
{
	// making
	const int test_num = 9;
	const char* ability_txt[] = {
		"次回に持ち越し",
		"王子ならゲームに勝利",
		"次回は相手公開",
		"強弱反転",
		"２勝",
		"無効化",
		"次回は＋２",
		"絶対勝利",
		"Unknown"
	};

	enum CARD_IDX{
		DRAW = 0,
		PRINCESS,
		SPY,
		REVERSE,
		DOUBLE,
		INVALID,
		POWER_2,
		WIN,
		UNKNOWN
	};
	
	bool expected_table[test_num][test_num] = {
		// 0 ,   1   ,   2  ,   3  ,   4  ,   5  ,   6  ,   7  , UNKNOWN
		{     1,     1,     1,     1,     1,     1,     1,     1, false},  // DRAW
		{     1,     1,     1,     1,     1,     1,     1,     1, false},  // PRINCESS
		{     1,     1,     1,     1,     1,     1,     1,     1, false},  // SPY
		{     1,     1,     1,     1,     1,     1,     1,     1, false},  // REVERSE
		{     1,     1,     1,     1,     1,     1,     1,     1, false},  // DOUBLE
		{     1,     1,     1,     1,     1,     1,     1,     1, false},  // INVALID
		{     1,     1,     1,     1,     1,     1,     1,     1, false},  // POWER_2
		{     1,     1,     1,     1,     1,     1,     1,     1, false},  // WIN
		{ false, false, false, false, false, false, false, false, false}   // UNKNOWN
	};

	DummyCardRivals card_rival[test_num];
	for (int i = 0; i < test_num; i++) {
		card_rival[i].SetAbility(ability_txt[i]);
	}

	for (int i = 0; i < test_num; i++) {
		for (int j = 0; j < test_num; j++) {
			printf(" i:%d, j:%d\n", i, j);  // for debug
			EXPECT_EQ(expected_table[i][j], field_->ability(&card_rival[i], &card_rival[j]));
		}
	}
}


TEST_F(UnitTestFieldRivals, playCards)
{
	DummyCardRivals p1_card("p1_card", "p1_ability", 4);
	DummyCardRivals p2_card("p1_card", "p1_ability", 6);
	unsigned int p1_wins = 0;
	unsigned int p2_wins = 0;
	field_->playCards(&p1_card, &p2_card, p1_wins, p2_wins);

	// making
	EXPECT_TRUE(false);
}