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
	// making
	EXPECT_TRUE(false);
}


TEST_F(UnitTestFieldRivals, abilityDraw)
{
	// making
	EXPECT_TRUE(false);
}


TEST_F(UnitTestFieldRivals, isReveal)
{
	// making
	EXPECT_TRUE(false);
}


TEST_F(UnitTestFieldRivals, abilityPrincess)
{
	// making
	EXPECT_TRUE(false);
}


TEST_F(UnitTestFieldRivals, abilitySpy)
{
	// making
	EXPECT_TRUE(false);
}


TEST_F(UnitTestFieldRivals, abilityReverse)
{
	// making
	EXPECT_TRUE(false);
}


TEST_F(UnitTestFieldRivals, abilityDouble)
{
	// making
	EXPECT_TRUE(false);
}


TEST_F(UnitTestFieldRivals, abilityPowerUp)
{
	// making
	EXPECT_TRUE(false);
}


TEST_F(UnitTestFieldRivals, abilityWin)
{
	// making
	EXPECT_TRUE(false);
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