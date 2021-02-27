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
	// making
	EXPECT_TRUE(false);
}


TEST_F(UnitTestFieldRivals, ability)
{
	// making
	EXPECT_TRUE(false);
}


TEST_F(UnitTestFieldRivals, isReveal)
{
	// making
	EXPECT_TRUE(false);
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