#pragma once

//#include <iostream>
#include <string>
#include <vector>

//#include <algorithm>

#include "Card.h"

using namespace std;

/**
 * @brief �J�[�h�S�̐����ƁA�J�[�h�̎��Ԃ��Ǘ�����B�J�[�h�͊�{�I�Ƀ|�C���^�[�Ŏg�p����A���̎��ԂɃA�N�Z�X����B
 *         std::vector<> �g�p�����ق����Ǘ����ȒP��������Ȃ�
 *        �K�v�ȃJ�[�h�͍ŏ��ɑS���������Ă��܂��\��B�r������J�[�h����������͂��Ȃ��B
 * @date 2019/09/04
 **/
class Deck {
	typedef enum {
		CARD,
		RIVALS,
		UNKNOWN  // ���m��class �������͖��w��
	} CARD_CLASS;
protected:
	// *card[N] ���ꂼ��̃J�[�h���w���|�C���^�̔z��B
	// ���ԊǗ��p�B�������Ȃ����A���삵�Ȃ��B
	vector<Card*> cards;

	// �z�����肷�錩������̃J�[�h�|�C���^�B����p�B��������
	vector<Card*> cards_shadow;

	CARD_CLASS cardClassBranch(const char* str);

public:
	Deck();
	//�f�b�L�ǂݍ��ݕt��
	Deck(string filename);
	~Deck();

	// �t�@�C������J�[�h���S��ǂݍ��݃f�b�L�𐶐�����
	virtual bool load(string filename);

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

};
