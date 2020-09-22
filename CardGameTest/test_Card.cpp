#include <string>

#include "pch.h"
#include "Card.h"

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1�Ȃ̂�


class CardDummy : public Card {
public:
	void set_name(char* _name) {
		name = _name;
	}

	void set_ability(char* _ability_text) {
		ability_text = _ability_text;
	}

	// loadImage()�֐���protected�Ȃ̂ŁA���̊֐�����Ăяo��
	bool call_loadImage(const string filename) {
		return loadImage(filename);
	}

};

class UnitTestCard : public ::testing::Test {
protected:
	const char* input_img = "../../test_data/CardGameTest/input/ki.png";
	const int img_rows = 70;
	const int img_cols = 51;

	virtual void SetUp() {
		// do nothing
	}

	virtual void TearDown() {
		// do nothing
	}
};

TEST_F(UnitTestCard, Card) {
	Card card;
	string act_name = card.get_name();
	char* exp_name = "Nothing";
	EXPECT_STREQ(exp_name, act_name.c_str());

	string act_ability = card.get_ability();
	char* exp_ability = "Nothing";
	EXPECT_STREQ(exp_ability, act_ability.c_str());
}

TEST_F(UnitTestCard, loadImage) {
	CardDummy card;

	const string error_filename = "not_exist_file.abc"; // ���݂��Ȃ��t�@�C��
	EXPECT_FALSE(card.call_loadImage(error_filename));

	const string filename = input_img;
	EXPECT_TRUE(card.call_loadImage(filename));
}

TEST_F(UnitTestCard, load) {
	// �摜�`��n�̃e�X�g�͂��Ȃ�
	CardDummy card;
	card.call_loadImage(input_img);
	char* name = "card_name";
	card.set_name(name);
	char* ability = "card_ability";
	card.set_ability(ability);

	string title_head = "title_head";
	// cout�����Ȃ��̂ŁA�Ƃ��Ƀe�X�g�͂Ȃ�
	EXPECT_TRUE(card.show(title_head, Card::SHOW_TEXT));

	// �摜�\���n�̃e�X�g�͂��Ȃ�
	//EXPECT_TRUE(card.show(title_head, Card::SHOW_IMG_TEXT));
}

TEST_F(UnitTestCard, show) {
	CardDummy card;
	string actual = card.show("nothing", 1.f, 0, 0, false);
	EXPECT_STREQ("", actual.c_str());

	/* �摜�`��n�̃e�X�g�͂��Ȃ��B
	card.call_loadImage(input_img);
	string expected = "input";
	actual = card.show(expected, 1.f, 0, 0, false);
	EXPECT_STREQ(expected.c_str(), actual.c_str());
	*/
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

TEST_F(UnitTestCard, getImgSize) {
	CardDummy card;
	unsigned int rows, cols;
	EXPECT_FALSE(card.getImgSize(&rows, &cols));

	card.call_loadImage(input_img);

	EXPECT_TRUE(card.getImgSize(&rows, &cols));
	EXPECT_EQ(img_rows, rows);
	EXPECT_EQ(img_cols, cols);
}