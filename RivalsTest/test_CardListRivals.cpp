#include "pch.h"
#include "CardListRivals.h"

class UnitTestCardListRivals : public ::testing::Test {
protected:
	virtual void SetUp() {
		// do nothing
	}

	virtual void TearDown() {
		// do nothing
	}

};

TEST_F(UnitTestCardListRivals, CardListRivals) {
	// do nothing
}

// 存在しないファイルの読み込みテスト
TEST_F(UnitTestCardListRivals, load_not_exist) {
	CardListRivals list_rivals;

	const string error_filename = "nothing";
	EXPECT_FALSE(list_rivals.load(error_filename));
}

// ヘッダーの記述されていないファイルの読み込みテスト
TEST_F(UnitTestCardListRivals, load_heder_less) {
	CardListRivals list_rivals;

	const string error_filename = "../../test_data/CardListRivalsTest/input/card_rival_list_hedder_less.txt";
	EXPECT_FALSE(list_rivals.load(error_filename));
}

// 正常なファイル読み込みのテスト
TEST_F(UnitTestCardListRivals, load_success) {
	CardListRivals list_rivals;
	const string filename = "../../test_data/CardListRivalsTest/input/card_rival_list.txt";
	EXPECT_TRUE(list_rivals.load(filename));
	vector<CardRivals*> cards = list_rivals.rivals_shadow();
	{
		int actual = cards.size();
		int expected = 4;
		EXPECT_EQ(expected, actual);
	}

	{
		const char* exp_names[] = {
			"title1",
			"title2",
			"title3",
			"title4"
		};
		const char* exp_abilitys[] = {
			"ability1",
			"ability2",
			"ability3",
			"ability4"
		};
		/* 現時点では画像名は記録していないのでチェック不可
		const char* exp_imgname[] = {
			"img1.png",
			"img2.png",
			"img3.png",
			"img4.png"
		};
		*/
		const int exp_power[] = {
			1,2,3,4
		};

		for (int i = 0; i < cards.size(); i++) {
			EXPECT_STREQ(exp_names[i], cards[i]->get_name().c_str());
			EXPECT_STREQ(exp_abilitys[i], cards[i]->get_ability().c_str());
			EXPECT_EQ(exp_power[i], cards[i]->get_power());
			// 現時点では、画像名は記録していない
			//EXPECT_STREQ(exp_imgname[i], cards[i]->ge().c_str());
		}
	}
}

// making Privateメソッドのテストはどうやったらいいかな
// → privateであることが間違い。クラスを分離してpublic化するなどする
TEST_F(UnitTestCardListRivals, cardClassBranch) {
	CardListRivals list_rivals;
	EXPECT_TRUE(false);
}
