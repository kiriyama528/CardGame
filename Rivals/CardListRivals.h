#pragma once

/**
 * @brief �J�[�h�Q�[���uR-Rivals�v�̃J�[�h���X�g��ǂݍ��ރN���X
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

#include <string>

#include "CardList.h"
#include "CardRivals.h" // TODO: ����Ȃ������A�v�`�F�b�N


// TODO : �킴�킴�p������override����K�v�͂Ȃ��̂ł́H
//        �e�N���X���C���^�[�t�F�[�X�ɂ����ق����悢����
class CardListRivals : public CardList {
private:
	// �J�[�h���X�g1�s��ǂݍ��ރo�b�t�@�T�C�Y
#define BUFFER_SIZE 2048 

	// �J�[�h�̃N���X�^�O
	// TODO : �e�N���X�ł�������enum��`�������Ċ댯
	//        ���������K�؂ȋL�q���@������͂�
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
	// TODO : �ʃN���X�ɂ���Ȃǂ���public���\�b�h�ɂ���
	//        �e�X�g���������߂ɁB
	//        �J�[�h�u�����`�@�\���̂́A��������������̂����ނ��Ă悢�̂ł́H
	CARD_CLASS cardClassBranch(const char* str);

public:
	CardListRivals();
	// �J�[�h���X�g�̓ǂݍ��ݕt��
	CardListRivals(string filename);
	virtual ~CardListRivals();

	/**
	 * @brief �t�@�C������J�[�h���S��ǂݍ��ݎ��Ԃ𐶐�����
	 * @param filename �J�[�h���X�g�̃t�@�C����
	 * @return (true) ����I�� / �ُ픭�� (false)
	 **/
	virtual bool load(string filename);

	// HACK: �����̂ŁA���L���C�ȃR�[�h�ɏ�������
	// ����p�̃��X�g�𐶐�����
	virtual const vector<CardRivals*> rivals_shadow() const;

};