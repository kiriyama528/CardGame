#include "pch.h"
#include "CardRivals.h"

class UnitTestCardRivals : public ::testing::Test {
protected:
	virtual void SetUp() {
		// do nothing
	}

	virtual void TearDown() {
		// do nothing
	}

};

TEST_F(UnitTestCardRivals, CardRivals) {
	CardRivals rivals;
	int exp_power = 0;
	int act_power = rivals.get_power();
	EXPECT_EQ(exp_power, act_power);
}

TEST_F(UnitTestCardRivals, load) {
	CardRivals rivals;
	char str[128];
	int exp_power = 7;
	sprintf(str, "sample_name,sample_ability,sample_img,%d", exp_power);
	rivals.load(str);
	int act_power = rivals.get_power();
	EXPECT_EQ(exp_power, act_power);
}

