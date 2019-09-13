#pragma once

/**
 * @brief �J�[�h�Q�[���uR-Rivals�v�̃J�[�h���X�g��ǂݍ��ރN���X
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

#include <string>

#include "CardList.h"

class CardListRivals : public CardList {
private:
	// �J�[�h���X�g1�s��ǂݍ��ރo�b�t�@�T�C�Y
#define BUFFER_SIZE 2048 

	// �J�[�h�̃N���X�^�O
	typedef enum {
		CARD,
		RIVALS,
		UNKNOWN  // ���m��class �������͖��w��
	} CARD_CLASS;

	/**
	 * @brief �J�[�h���X�g�̃J�[�h�N���X�𕪗ނ���
	 * @param str �J�[�h�N���X��񂪏����ꂽ������|�C���^
	 * @return �J�[�h�̃N���X�^�O
	 **/
	CARD_CLASS cardClassBranch(const char* str);

public:
	CardListRivals();
	// �J�[�h���X�g�̓ǂݍ��ݕt��
	CardListRivals(string filename);
	~CardListRivals();

	/**
	 * @brief �t�@�C������J�[�h���S��ǂݍ��ݎ��Ԃ𐶐�����
	 * @param filename �J�[�h���X�g�̃t�@�C����
	 * @return (true) ����I�� / �ُ픭�� (false)
	 **/
	virtual bool load(string filename);

};