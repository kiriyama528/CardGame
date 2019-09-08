#pragma once

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

	
	// �摜�̓ǂݍ��݁B���� true / ���s false
	bool loadImage(const string filename);

public:
	typedef enum {
		SHOW_TEXT,
		SHOW_IMG_TEXT
	} SHOW_TYPE;

	Card();
	// �J�[�h�̓ǂݍ��݂�
	Card(string plane_text);
	~Card();

	// �J�[�h��ǂݍ���
	virtual bool load(const string plane_text);

	// �J�[�h��\������
	virtual void show(string img_head="", SHOW_TYPE type=SHOW_IMG_TEXT);

	virtual bool operator < (const Card obj) const;
	virtual bool operator > (const Card obj) const;
	virtual bool operator == (const Card obj) const;
	virtual bool operator != (const Card obj) const;
	virtual bool operator <= (const Card obj) const;
	virtual bool operator >= (const Card obj) const;

	const string get_name() const { return name; }

	const string get_ability() const { return ability_text; }

	// �I�[�����ɗނ��镶�����ǂ��� true / false
	static bool endStr(char target);

	// ,(�R���}) �ŗv�f�𕪗ނ���Bplane_text�̕���p
	static int split_plane(char *plane_text, char **cols);

};

