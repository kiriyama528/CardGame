#pragma once

/**
 * @brief �J�[�h�Q�[���uR-Rivals�v�̃J�[�h���ʂ����������
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/


#include <vector>

#include "Card.h"
#include "CardRivals.h"

using namespace std;

class FieldRivals {
private:
#define N_PLAYERS 2
#define PRINCE_POWER_UP 10

public:
	typedef enum {
		DRAW = 0,	// 0: ����Ɏ����z��
		PRINCESS,	// 1: ���q�Ȃ�Q�[���ɏ���
		SPY,		// 2: ����͑�����J
		REVERSE,	// 3: ���㔽�]
		DOUBLE,		// 4: �Q��
		INVALID,	// 5: ������
		POWER_2,	// 6: �����+2
		WIN,		// 7: ��Ώ���
		UNKNOWN
	} ABILITY_TAG;

	// Index�Q�ƂɎg��
	typedef enum {
		P1 = 0,
		P2
	} PLAYER_NUMBER;

	FieldRivals();
	~FieldRivals();

	/**
	 * @brief �J�[�h���v���C����B�J�[�h�̏��s�����߂�
	 * @param c1 PLAYER1 �̃J�[�h�������|�C���^
	 * @param c2 PLAYER2 �̃J�[�h�������|�C���^
	 * @param p1_wins ����̏����ɂ��PLAYER1 �̏�����
	 * @param p2_wins ����̏����ɂ��PLAYER2 �̏�����
	 * @return (true) ����ɏI�� / �\�͉������ɖ�蔭�� (false)
	 **/
	bool playCards(
		CardRivals * c1,
		CardRivals * c2,
		unsigned int &p1_wins,
		unsigned int &p2_wins);

	// @return �ЂƂł�������� true. �ڍׂ͈�����
	/**
	 * @brief ����̏����ŃJ�[�h�����J����v���C���[�����邩�B����Ȃ�N���B
	 * @param reveal_flag �J�[�h���J�t���O�̃��X�g�Btrue�Ȃ���J����
	 *         [0]�FPLAYER1
	 *         [1]�FPLAYER2
	 * @return (true) �J�[�h���J�������K�v / �J�[�h���J�����͕s�K�v (false)
	 **/
	bool isReveal(bool reveal_flag[N_PLAYERS]);

public:  // protected�B�e�X�g�̂��߂ɃA�N�Z�X������publc�֕ύX
	// �g�p�����B�擪��NULL�B���ɒǉ����Ă���
	vector<CardRivals*> card_his_p1;
	vector<CardRivals*> card_his_p2;

	// ����̏����̃J�[�h�̋���
	int powers[N_PLAYERS];

	// ���Z�����power
	int power_up[N_PLAYERS];
	
	// �J�[�h���J�t���O
	// ���̃t���O�������Ă���v���C���[�͎���J�[�h���J
	bool reveal[N_PLAYERS];

	// �������������̋L�^�B�������A�����ɉ��Z
	unsigned int draw_storage[N_PLAYERS];

	// ����̏����ɂ�鏟���B�o�͂��邽�т�0�ɂȂ�
	unsigned int wins[N_PLAYERS];

	/**
	 * @brief �\�͂𕪗ނ��ă^�O�t������
	 * @param c ���ނ�����R�J�[�h�̃|�C���^
	 * @return c�J�[�h�̃^�O
	 **/
	ABILITY_TAG branchAbility(const CardRivals *c);

	/**
	 * @brief 0�F�����̌��ʁA������������
	 * @return true�̂�
	 **/
	void abilityDraw();

	/**
	 * @brief 1�F�P�̌��ʁA���肪���q�Ȃ�Q�[���ɏ���
	 * @param p ������PLAYER�ԍ�
	 * @param you_tag �ΐ푊���R�J�[�h�^�O
	 * @return true/false ���ꏟ��/���ʂȂ�
	 **/
	bool abilityPrincess(PLAYER_NUMBER p, ABILITY_TAG you_tag);

	/**
	 * @brief 2�F����̌��ʁA���񑊎�̓J�[�h�����J���ăv���C
	 * @param p ������PLAYER�ԍ�
	 **/
	void abilitySpy(PLAYER_NUMBER p);

	/**
	 * @brief 3�F�ÎE�҂̌��ʁA���㔽�]
	 **/
	void abilityReverse();

	/**
	 * @brief 4�F��b�̌��ʁA���Ă�2�����ƂȂ�悤�Ɉ��������X�g�b�N�𒲐�
	 * @param p ������PLAYER�ԍ�
	 **/
	void abilityDouble(PLAYER_NUMBER p);

	// 5�F���p�t�̌��ʂ́A�������ɉ����A�֐����ł��Ȃ��i�����j

	/**
	 * @brief 6�F���R�̌��ʁA����̏����Ő�����+2�����
	 * @param p ������PLAYER�ԍ�
	 **/
	void abilityPowerUp(PLAYER_NUMBER p, int up);

	/**
	 * @brief 7�F���q�̌��ʁA�قڏ����ł���
	 * @param p ������PLAYER�ԍ�
	 **/
	void abilityWin(PLAYER_NUMBER p);

	/**
	 * @brief �O�̃J�[�h�̌��ʂ�K�p�����������L�^
	 * @param c1 �����PLAYER1 �̃J�[�h�ւ̃|�C���^
	 * @param c2 �����PLAYER2 �̃J�[�h�ւ̃|�C���^
	 * @return (true) ����I�� / �ُ픭�� (false)
	 **/
	bool enchantment(const CardRivals *c1, const CardRivals *c2);

	/**
	 * @brief �J�[�h�̌��ʂ𔭓�
	 * @param c1 �����PLAYER1 �̃J�[�h�ւ̃|�C���^
	 * @param c2 �����PLAYER2 �̃J�[�h�ւ̃|�C���^
	 * @return (true) ����I�� / �ُ픭�� (false)
	 **/
	bool ability(const CardRivals *c1, const CardRivals *c2);

};
