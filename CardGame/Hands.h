#pragma once

#include <vector>

#include "Card.h"

using namespace std;

class Hands {
protected:
	vector<Card*> cards_shadow;

public:
	Hands();
	Hands(const vector<Card*> _shadow);
	~Hands();

	/**
	 * @return ��D�̖���
	 **/
	int load(const vector<Card*> _shadow);

	/**
	 * @brief ��D��S������
	 **/
	void show(Card::SHOW_TYPE show_type = Card::SHOW_IMG_TEXT);

	/**
	 * @brief ����̎�D������
	 *        ( 0 <= idx < cards_shadow.size() )
	 **/
	void show(int idx, Card::SHOW_TYPE show_type = Card::SHOW_IMG_TEXT);
	
	/**
	 * @return ��D�̖���
	 **/
	int in(Card* cs);

	/**
	 * @return ��菜������D�Bidx���s�K�؂Ȃ�NULL

	 **/
	Card* out(int idx);

	void sort();
};