#include "pch.h"
#include "CardListRivals.h"
#include "FieldRivals.h"

class DummyCardRivals : public CardRivals {
	/* ����
	string name;         // �J�[�h�̖��O
	string ability_text; // �J�[�h���ʂ̃e�L�X�g��
	cv::Mat img;         // �J�[�h�̉摜
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
		"����Ɏ����z��",
		"���q�Ȃ�Q�[���ɏ���",
		"����͑�����J",
		"���㔽�]",
		"�Q��",
		"������",
		"����́{�Q",
		"��Ώ���",
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