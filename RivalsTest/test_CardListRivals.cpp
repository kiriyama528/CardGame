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

// ���݂��Ȃ��t�@�C���̓ǂݍ��݃e�X�g
TEST_F(UnitTestCardListRivals, load_not_exist) {
	CardListRivals list_rivals;

	const string error_filename = "nothing";
	EXPECT_FALSE(list_rivals.load(error_filename));
}

// �w�b�_�[�̋L�q����Ă��Ȃ��t�@�C���̓ǂݍ��݃e�X�g
TEST_F(UnitTestCardListRivals, load_heder_less) {
	CardListRivals list_rivals;

	const string error_filename = "../../test_data/CardListRivalsTest/input/card_rival_list_hedder_less.txt";
	EXPECT_FALSE(list_rivals.load(error_filename));
}

// ����ȃt�@�C���ǂݍ��݂̃e�X�g
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
		/* �����_�ł͉摜���͋L�^���Ă��Ȃ��̂Ń`�F�b�N�s��
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
			// �����_�ł́A�摜���͋L�^���Ă��Ȃ�
			//EXPECT_STREQ(exp_imgname[i], cards[i]->ge().c_str());
		}
	}
}

// making Private���\�b�h�̃e�X�g�͂ǂ�������炢������
// �� private�ł��邱�Ƃ��ԈႢ�B�N���X�𕪗�����public������Ȃǂ���
TEST_F(UnitTestCardListRivals, cardClassBranch) {
	CardListRivals list_rivals;
	EXPECT_TRUE(false);
}
