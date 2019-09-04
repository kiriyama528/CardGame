#pragma once

#include <string>
#include <opencv2/opencv.hpp>

using namespace std;


class Card {
private:
	int n_elems = 3; // �ǂݍ��݃��X�g����ǂݍ��ޗ\��̗v�f��

protected:
	typedef enum {
		SHOW_TEXT,
		SHOW_IMG_TEXT
	} SHOW_TYPE;

	string name;         // �J�[�h�̖��O
	string ability_text; // �J�[�h���ʂ̃e�L�X�g��
	cv::Mat img;         // �J�[�h�̉摜


	bool loadImage(const string filename);

public:
	Card();
	// �J�[�h�̓ǂݍ��݂�
	Card(string plane_text);
	~Card();

	// �J�[�h��ǂݍ���
	virtual bool load(string plane_text);

	// �J�[�h��\������
	virtual void show(SHOW_TYPE type=SHOW_IMG_TEXT);

};

