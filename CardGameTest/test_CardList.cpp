#include "pch.h"
#include "CardList.h"

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1�Ȃ̂�

class CardListDummy : public CardList {
public:
	CARD_CLASS call_cardClassBranch(const char* str) const {
		return cardClassBranch(str);
	}

	CARD_CLASS getCardClass_CARD() const {
		return CARD_CLASS::CARD;
	}

	CARD_CLASS getCardClass_UNKNOWN() const {
		return CARD_CLASS::UNKNOWN;
	}

	vector<Card*> get_cards() const {
		return cards;
	}
};

class UnitTestCardList : public ::testing::Test {
protected:
	virtual void SetUp() {
		// do nothing
	}

	virtual void TearDown() {
		// do nothing
	}
};

TEST_F(UnitTestCardList, cardClassBranch) {
	CardListDummy card_list;
	const char* card_class_card = "Card";
	const char* card_class_unknown[] = {"CardRivals", "Nothing"};
	EXPECT_EQ(
		card_list.getCardClass_CARD(),
		card_list.call_cardClassBranch(card_class_card)
	);

	for (int i = 0; i < 2; i++) {
		printf("%d : %s\n", i, card_class_unknown[i]);
		EXPECT_EQ(
			card_list.getCardClass_UNKNOWN(),
			card_list.call_cardClassBranch(card_class_unknown[i])
		);
	}

}

// ���݂��Ȃ��t�@�C���̓ǂݍ��݃e�X�g
TEST_F(UnitTestCardList, load_not_exist) {
	CardList card_list;

	const string error_filename = "nothing";
	EXPECT_FALSE(card_list.load(error_filename));
}

// �w�b�_�[�̋L�q����Ă��Ȃ��t�@�C���̓ǂݍ��݃e�X�g
TEST_F(UnitTestCardList, load_heder_less) {
	CardList card_list;

	const string error_filename = "../../test_data/CardGameTest/input/card_list_header_less.txt";
	EXPECT_FALSE(card_list.load(error_filename));
}

// ����ȃt�@�C���ǂݍ��݂̃e�X�g
TEST_F(UnitTestCardList, load_success) {
	CardListDummy card_list;
	const string filename = "../../test_data/CardGameTest/input/card_list.txt";
	EXPECT_TRUE(card_list.load(filename));
	vector<Card*> cards = card_list.get_cards();
	{
		int actual = cards.size();
		int expected = 4;
		EXPECT_EQ(expected, actual);
	}
	
	{
		const char* exp_names[] = { "ki", "ri", "ya", "ma" };
		const char* exp_abilitys[] = {
			"ability of ki",
			"ability of ri",
			"ability of ya",
			"ability of ma"
		};
		/* �����_�ł͉摜���͋L�^���Ă��Ȃ��̂Ń`�F�b�N�s��
		const char* exp_imgname[] = {
			"ki.png",
			"ri.png",
			"ya.png",
			"ma.png"
		};
		*/

		for (int i = 0; i < cards.size(); i++) {
			EXPECT_STREQ(exp_names[i], cards[i]->get_name().c_str());
			EXPECT_STREQ(exp_abilitys[i], cards[i]->get_ability().c_str());
			// �����_�ł́A�摜���͋L�^���Ă��Ȃ�
			//EXPECT_STREQ(exp_imgname[i], cards[i]->ge().c_str());
		}
	}
}

// making
TEST_F(UnitTestCardList, shadow) {
	Card card;

}
