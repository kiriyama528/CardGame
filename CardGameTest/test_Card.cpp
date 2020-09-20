#include <string>

#include "pch.h"
#include "Card.h"

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1なので


class CardDummy : public Card {
public:
	void set_name(char* _name) {
		name = _name;
	}

	void set_ability(char* _ability_text) {
		ability_text = _ability_text;
	}
};


class UnitTestCard : public ::testing::Test {
protected:
	virtual void SetUp() {
		// do nothing
	}

	virtual void TearDown() {
		// do nothing
	}
};

// making
TEST_F(UnitTestCard, loadImage) {
	Card card;

	const string filename = "";  // TODO making テスト画像の配置

	// card.loadImage();  // protectedの関数だからどうやってテストしようか
}


// making
TEST_F(UnitTestCard, load) {
	
}


// making
TEST_F(UnitTestCard, show) {
	Card card;

}

TEST_F(UnitTestCard, get_name) {
	CardDummy card;

	char expected[] = "card_name";
	card.set_name(expected);
	
	const string actual = card.get_name();
	EXPECT_STREQ(expected, actual.c_str());
}

TEST_F(UnitTestCard, get_ability) {
	CardDummy card;

	char expected[] = "card_ability";
	card.set_ability(expected);

	const string actual = card.get_ability();
	EXPECT_STREQ(expected, actual.c_str());
}

TEST_F(UnitTestCard, endStr) {
	char c[] = { '\n', '\0', '\r' };
	for (int i = 0; i < sizeof(c); i++) {
		EXPECT_TRUE(Card::endStr(c[i]));
	}
}

TEST_F(UnitTestCard, endStr_false) {
	char c[] = { 'a', '9', '#' };
	for (int i = 0; i < sizeof(c); i++) {
		EXPECT_FALSE(Card::endStr(c[i]));
	}
}

TEST_F(UnitTestCard, split_plane) {
	char str[] = "sample1,ability is No.1,KT1.jpg";
	char* actual[5] = {NULL, NULL, NULL, NULL, NULL};

	EXPECT_EQ(3, Card::split_plane(str, actual));
	char* expected[] = { "sample1", "ability is No.1", "KT1.jpg", NULL, NULL};
	for (int i = 0; i < 5; i++) {
		EXPECT_STREQ(expected[i], actual[i]);
	}

}

// making
TEST_F(UnitTestCard, getImgSize) {
	Card card;
	unsigned int rows, cols;
	EXPECT_FALSE(card.getImgSize(&rows, &cols));

	/// 画像読み込み
	/// 目的の画像が読み込めているかチェック
}