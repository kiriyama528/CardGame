#pragma once

/**
 * @brief �J�[�h�Q�[���uR-Rivals�v�̃J�[�h
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

#include <string>

#include "Card.h"

class CardRivals : public Card {
private:
	// �J�[�h���̗v�f������Bcsv�ɂ���ċ�؂�ꂽ�v�f��
	const int n_elems = 4;

protected:
	// �J�[�h�̋���
	unsigned int power;

public:
	CardRivals();
	// �J�[�h���ǂݍ��ݕt��
	CardRivals(const string plane_text);
	virtual ~CardRivals();

	/**
	 * @brief R-Rivals�̃J�[�h����ǂݍ���
	 * @param plane_text csv�`���̃J�[�h��񕶎���
	 * @return (true) ����I�� / �ُ픭�� (false)
	 **/
	virtual bool load(string plane_text);

	/**
	 * @brief �J�[�h�̋������擾����
	 * @return �J�[�h�̋���
	 **/
	unsigned int get_power() const { return power; }

};