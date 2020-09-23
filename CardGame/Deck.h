#pragma once

/**
 * @brief �J�[�h�̎R�D�Ƃ��Ďg���N���X�B�J�[�h�̎��Ԃ�CardList�N���X���Ǘ����Ă���B
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

#include <string>
#include <vector>

#include "Card.h"
#include "CardList.h"

using namespace std;

class Deck {
protected:
	// �z�����肷�錩������̃J�[�h�|�C���^�B����p
	vector<Card*> cards_shadow;

public:
	Deck();

	// �J�[�h�S�̓ǂݍ��ݕt��
	Deck(const vector<Card*> _cards_shadow);

	// �����ς݂̃J�[�h���X�g�̒��g�����ׂăf�b�L�ɓǂݍ���
	Deck(CardList &cl);

	~Deck();

	/**
	 * @brief �J�[�h�S�̓ǂݍ��݁B��荞��
	 * @param _cards_shadow ��舵���J�[�h�|�C���^�[�S
	 * @return �R�D�̖���
	 **/
	virtual int load(const vector<Card*> _cards_shadow);

	/**
	 * @brief �R�D�̏ォ��P���̃J�[�h������
	 * @return �������J�[�h�B�J�[�h�������Ȃ��ꍇ�� NULL
	 **/
	virtual Card* draw();

	/**
	 * @brief �R�D���V���b�t������
	 * @return �c��̎R�D�̖���
	 **/
	virtual int shuffle();

	/**
	 * @brief �R�D�̏�ɃJ�[�h��u��(�����)
	 * @param c �Ώۂ̃J�[�h�|�C���^
	 * @return �c��̎R�D�̖���
	 **/
	virtual int putTop(Card *c);

	/**
	 * @brief �R�D�̒�ɃJ�[�h��u��(�����)
	 * @param c �Ώۂ̃J�[�h�|�C���^
	 * @return �c��̎R�D�̖���
	 **/
	virtual int putBottom(Card *c);

	/**
	 * @brief �R�D�̖������擾����
	 * @return �R�D�̖���
	 **/
	virtual int get_num() { return cards_shadow.size(); }
	
	/**
	 * @brief �R�D���������̖��O�̃J�[�h��T����index��Ԃ�
	 *        �p�r�F����̃J�[�h���o��܂Ńh���[����Ƃ�
	 * @return index ��Ԃ��B������Ȃ���� -1
	 **/
	virtual int searchIdx(const string _name) const ;

	/**
	 * @brief ����̃J�[�h��T�����o���B
	 * @return �T�����J�[�h�B������Ȃ����NULL
	 **/
	virtual Card* searchDraw(string _name);
};
