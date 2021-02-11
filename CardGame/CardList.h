#pragma once

#include "Card.h"

/**
 * @brief �J�[�h�S�̐����ƁA�J�[�h�̎��Ԃ��Ǘ�����B
 *        �K�v�ȃJ�[�h�͍ŏ��ɑS���������Ă��܂��B�r������J�[�h����������͂��Ȃ��B
 *        ���̃N���X�̔j�����ɁA�J�[�h���Ԃ����ׂĔj������B�Q�[���I�����ɔj�����邱�ƁB
 * @date 2019/09/04
 * @author kiriyama tomoya
 **/

class CardList {
protected:
	// FIX ME ���Ƃ��Ƃ�public�������B������������o�O�邩���B�B�B
	typedef enum {
		CARD,
		UNKNOWN  // ���m��class �������͖��w��
	} CARD_CLASS;

	// *card[N] ���ꂼ��̃J�[�h���w���|�C���^�̔z��B
	// ���ԊǗ��p�B�������Ȃ����A���삵�Ȃ��B
	vector<Card*> cards;

	virtual CARD_CLASS cardClassBranch(const char* str) const;
	
public:
	CardList();
	//�f�b�L�ǂݍ��ݕt��
	CardList(const string filename);

	// �J�[�h�S�̎��Ԃ�j��
	virtual ~CardList();

	// �t�@�C������J�[�h���S��ǂݍ��݃f�b�L�𐶐�����
	virtual bool load(const string filename);

	// ����p�̃��X�g�𐶐�����
	virtual const vector<Card*> shadow() const;
};