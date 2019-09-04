#pragma once

#include "Card.h"

/**
 * @brief �J�[�h�S�̐����ƁA�J�[�h�̎��Ԃ��Ǘ�����B
 *        �K�v�ȃJ�[�h�͍ŏ��ɑS���������Ă��܂��B�r������J�[�h����������͂��Ȃ��B
 *        ���̃N���X�̔j�����ɁA�J�[�h���Ԃ����ׂĔj������B�Q�[���I�����ɔj�����邱�ƁB
 * @date 2019/09/04
 **/
class CardList {
	typedef enum {
		CARD,
		RIVALS,
		UNKNOWN  // ���m��class �������͖��w��
	} CARD_CLASS;
protected:
	// *card[N] ���ꂼ��̃J�[�h���w���|�C���^�̔z��B
	// ���ԊǗ��p�B�������Ȃ����A���삵�Ȃ��B
	vector<Card*> cards;
	
	CARD_CLASS cardClassBranch(const char* str);

public:
	CardList();
	//�f�b�L�ǂݍ��ݕt��
	CardList(string filename);

	// �J�[�h�S�̎��Ԃ�j��
	~CardList();

	// �t�@�C������J�[�h���S��ǂݍ��݃f�b�L�𐶐�����
	virtual bool load(string filename);

	// ����p�̃��X�g�𐶐�����
	const vector<Card*> shadow();
};