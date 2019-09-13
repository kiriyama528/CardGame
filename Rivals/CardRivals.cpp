/**
 * @brief Rivals�̃J�[�h�ݒ�
 * @date 2019/09/05
 * @author kiriyama tomoya
 **/

#include <string>

#include "CardRivals.h"

CardRivals::CardRivals() {
	power = 0;
}


CardRivals::CardRivals(const string plane_text) {
	load(plane_text);
}


CardRivals::~CardRivals() {
	// do nothing
}


bool CardRivals::load(const string plane_text) {
	// plane_text�̌`��: card_name,ability_text,img_name,(uint)power
	char *cols[MAX_COLS];
	char *str_p = new char[plane_text.size() + 1]; // ��Ɨp������
	strcpy_s(str_p, plane_text.size() + 1, plane_text.c_str());

	// plane_text �̗v�f����
	int n_cols = split_plane(str_p, cols);
	
	// �G���[�`�F�b�N
	if (n_cols != n_elems) {
		fprintf(stderr, " ERROR > �J�[�h�������̗v�f���s�K�؂ł��B\n"
			"         %d�v�f�ǂݍ��݂̗\�肪%d�v�f����܂��B\n"
			"         string : %s\n", n_elems, n_cols, plane_text.c_str());
		delete[] str_p;
		return false;
	}
	name = cols[0];          // fix me id�Ƃ��͍��ジ���\��������̂ŁA�_�����������
	ability_text = cols[1];  // fix me id�Ƃ��͍��ジ���\��������̂ŁA�_�����������
	string img_name = cols[2];
	power = atoi(cols[3]);

	delete[] str_p;

	if (!loadImage(img_name)) {
		fprintf(stderr, " WARNING > �w�肳�ꂽ�摜���ǂݍ��߂܂���B\n"
			"            filename : %s\n", img_name.c_str());
		// �G���[�ł͂Ȃ��B�摜�͓ǂݍ��߂Ȃ��Ƃ��悢�B
	}

	return true;
}
