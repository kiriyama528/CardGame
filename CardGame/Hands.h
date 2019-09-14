#pragma once

/**
 * @brief �J�[�h�̎�D�Ƃ��Ďg���N���X�B�J�[�h�̎��Ԃ�CardList�N���X���Ǘ����Ă���B
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

#include <vector>

#include "Card.h"

using namespace std;

class Hands {
protected:
	// ��D
	vector<Card*> cards_shadow;

	// ��D��\�����Ă���E�B���h�E�̖��O�S
	vector<string> window_names;

public:
	Hands();
	Hands(const vector<Card*> _shadow);
	~Hands();

	/**
	 * @brief �J�[�h�S����D�Ƃ��Đݒ肷��
	 * @param _shadow ��D�ɂ������J�[�h�|�C���^�S
	 * @return ��D�̖���
	 **/
	int load(const vector<Card*> _shadow);

	/**
	 * @brief ��D���P�����A�S���\������BCard��show�ɏ]��
	 * @param show_type �J�[�h�\���`�����w�肷��
	 **/
	void show(Card::SHOW_TYPE show_type = Card::SHOW_IMG_TEXT);

	/**
	 * @brief ����̎�D��1���\������BCard��show�ɏ]��
	 * @param idx ��D�ԍ� ( 0 <= idx < cards_shadow.size() )
	 * @param show_type �J�[�h�\���`�����w�肷��
	 **/
	void show(int idx, Card::SHOW_TYPE show_type = Card::SHOW_IMG_TEXT);

	/**
	 * @brief ��D����ׂĂ��ׂĕ\������B����̍��W��X�P�[�����w��
	 * @param title_head �E�B���h�E�^�C�g���ɕ\�����铪����(�� P1:)
	 * @param upper �n�_ y���W
	 * @param left �n�_ x���W
	 * @param scale �ǂݍ��݉摜�ɑ΂���\���{��
	 * @param is_wait �E�B���h�E�\�����waitKey()���邩�ǂ���
	 * �����FdestroyAllWindows() �ŃE�B���h�E��������
	 **/
	void showLineUp(string title_head, unsigned int upper, unsigned int left, float scale, bool is_wait=false);

	// 
	/**
	 * @brief �\�����Ă����D(�E�B���h�E)�����ׂĕ���
	 *         showLineUp()�֐��g�p��ɌĂяo�� �Ƒz��
	 **/
	void destroyAllWindows();

	/**
	 * @brief ��D�ɂP���J�[�h��ǉ�����
	 * @return ��D�̖���
	 **/
	int in(Card* cs);

	/**
	 * @brief ��D����J�[�h��1���o��
	 * @param idx ��D�ԍ�
	 * @return ��菜������D�Bidx���s�K�؂Ȃ�NULL
	 **/
	Card* out(int idx);

	/**
	 * @brief ��D�𖼑O��(����)�Ƀ\�[�g����
	 **/
	void sort();
};