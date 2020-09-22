#pragma once

/**
 * @brief �J�[�h�ɑ΂���N���X
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

#include <string>
#include <opencv2/opencv.hpp>

using namespace std;


class Card {
private:
	const int n_elems = 3; // �ǂݍ��݃��X�g����ǂݍ��ޗ\��̗v�f��

protected:
#define MAX_COLS 15
	string name;         // �J�[�h�̖��O
	string ability_text; // �J�[�h���ʂ̃e�L�X�g��
	cv::Mat img;         // �J�[�h�̉摜

	/**
	 * @brief �摜�̓ǂݍ���
	 * @param filename �摜�t�@�C����
	 * @return ���� true / ���s false
	 **/
	bool loadImage(const string filename);

public:
	// �J�[�h�\�����̃��[�h
	typedef enum {
		SHOW_TEXT,
		SHOW_IMG_TEXT
	} SHOW_TYPE;

	Card();
	// �J�[�h�̓ǂݍ��ݕt��
	Card(string plane_text);
	~Card();

	/**
	 * @brief �J�[�h��ǂݍ���
	 * @param plane_text csv�P�s�ŏ����ꂽ�J�[�h���
	 * @return (true) �ǂݍ��ݏI�� / �ǂݍ��ݎ��s (false)
	 **/
	virtual bool load(const string plane_text);
 
	/**
	 * @param �J�[�h��\������
	 * @param img_head �E�B���h�E�̃^�C�g��
	 * @param type �\���`���̎w��
	 **/
	virtual bool show(const string title_head, SHOW_TYPE type=SHOW_IMG_TEXT);

	/**
	 * @brief �J�[�h���w��̏ꏊ��scale�ŕ\������
	 * @param title �E�B���h�E�̃^�C�g��
	 * @param scale �摜�̕\���{��
	 * @param upper �n�_ y���W
	 * @param left  �n�_ x���W
	 * @param is_wait �E�B���h�E�\����ɃL�[���͂�҂�
	 * @return window�̖��O��Ԃ��B�E�B���h�E�폜���ɎQ�Ƃ���
	 **/
	string show(const string title, float scale, unsigned int upper, unsigned int left, bool is_wait);

	virtual bool operator < (const Card obj) const;
	virtual bool operator > (const Card obj) const;
	virtual bool operator == (const Card obj) const;
	virtual bool operator != (const Card obj) const;
	virtual bool operator <= (const Card obj) const;
	virtual bool operator >= (const Card obj) const;

	// �J�[�h�̖��O��Ԃ�
	const string get_name() const { return name; }

	// �J�[�h�̌��ʃe�L�X�g��Ԃ�
	const string get_ability() const { return ability_text; }

	/**
	 * @brief target ���I�[�����ɗނ��镶�����ǂ���
	 * @param target �ΏۂƂ��镶��
	 * @return (true) �I�[���� / �����ł͂Ȃ� (false)
	 **/
	static bool endStr(char target);

	/**
	 * @brief �������",(�R���})"�ŗv�f������ɕ�������B�j��I�����񑀍�B
	 * @param plane_text ����������������
	 * @param cols �����������ꂼ��̗v�f������̐擪�����������|�C���^�z��
	 * @return ���������v�f��
	 **/
	static int split_plane(char *plane_text, char *cols[]);
	
	/**
	 * @brief �J�[�h�̉摜�T�C�Y���擾����
	 * @param rows (OUT)�s��
	 * @param cols (OUT)��
	 * @return (true) �擾���� / �摜������܂��� (false)
	 **/
	bool getImgSize(unsigned int *rows, unsigned int *cols) const {
		*rows = img.rows;
		*cols = img.cols;
		return !img.empty(); 
	}
};

