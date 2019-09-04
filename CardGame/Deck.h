#pragma once

#include <string>
#include <vector>

#include "Card.h"
#include "CardList.h"

using namespace std;

/**
 * @brief ����p�J�[�h�S����舵���B���Ԃ͕ʂ̏ꏊ�iCardList�j�ɂ���
 * @date 2019/09/04
 **/
class Deck {
protected:
	// �z�����肷�錩������̃J�[�h�|�C���^�B����p
	vector<Card*> cards_shadow;

public:
	Deck();
	Deck(const vector<Card*> _cards_shadow);
	Deck(CardList &cl);
	~Deck();

	/**
	 * @return �R�D�̖���
	 **/
	int load(const vector<Card*> _cards_shadow);

	/**
	 * @return �J�[�h�������Ȃ��ꍇ�� NULL
	 **/
	Card* draw();

	/**
	 * @return �c��̎R�D�̖���
	 **/
	int shuffle();

	/**
	 * @return �c��̎R�D�̖���
	 **/
	int putTop(Card *c);

	/**
	 * @return �c��̎R�D�̖���
	 **/
	int putBottom(Card *c);

	int get_num() { return cards_shadow.size(); }
	
	/**
	 * @return ����̖��O�̃J�[�h�̏���(idx)��Ԃ��B������Ȃ���� -1
	 **/
	int searchIdx(string _name);

	/**
	 * @return �T�����J�[�h�B������Ȃ����NULL
	 **/
	Card* searchDraw(string _name);
};
