#include <iostream>
#include <string>

#include "Card.h"

#define MAX_COLS 15

using namespace std;

int split_plane(char *plane_text, char **cols);



bool endStr(char target) {
	const int n_end_chars = 3;
	char end_chars[n_end_chars] = { '\n', '\0', '\r'};
	for (int i = 0; i < n_end_chars; i++) {
		if (target == end_chars[i]) {
			return true;
		}
	}

	return false;
}


Card::Card() {
	name = "Nothing";
	ability_text = "Nothing";
}

Card::Card(string plane_text) {
	load(plane_text.c_str());
}

Card::~Card() {
	// do nothing
}

bool Card::load(string plane_text){
	// plane_text�̌`��: card_name,ability_text,img_name
	char *cols[MAX_COLS];
	char *str_p = new char[plane_text.size() + 1];
	strcpy_s(str_p, plane_text.size() + 1, plane_text.c_str());
	int n_cols = split_plane(str_p, cols);
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
	
	delete[] str_p;

	if (!loadImage(img_name)) {
		fprintf(stderr, " WARNING > �w�肳�ꂽ�摜���ǂݍ��߂܂���B\n"
                        "            filename : %s\n", img_name.c_str());
		// �G���[�ł͂Ȃ��B�摜�͓ǂݍ��߂Ȃ��Ƃ��悢�B
	}

	return true;
}

void Card::show(SHOW_TYPE type) {
	cout << "name : " << name << endl;
	cout << "ability : " << ability_text << endl;
	
	// �摜���\�����邩
	if (type == SHOW_IMG_TEXT) {
		cv::imshow(name, img);
		cv::waitKey(0);
		cv::destroyWindow(name); // fix me ��������\��������Ċ�����
	}
}


/**
 * @brief �����𕪊���cols�Ŏw���B���̂Ƃ����؂蕶���� ','�ɌŒ�
 **/
int split_plane(char *plane_text, char **cols) {
	int cnt = 0;
	cols[0] = plane_text;
	cnt++;
	while (*plane_text) {
		// fix me ��؂蕶����','�B���߂����͂悭�Ȃ��B�_��ɂ��悤
		if (*plane_text == ',') {
			*plane_text = '\0';
			// �Ō�� ',' �������Ă���悤�ȓ���ȏ󋵂ł����
			if (endStr(*(plane_text+1))){
				break;
			}
			else {
				plane_text++;
				cols[cnt] = plane_text;
				cnt++;
			}
		}

		plane_text++;
	}
	
	return cnt;
}

bool Card::loadImage(const string filename) {
	img = cv::imread(filename, 1); // RGB�ǂݍ���
	return !img.empty();
}

bool Card::operator< (const Card obj) const {
	return strcmp(name.c_str(), obj.name.c_str())<0;
}

bool Card::operator> (const Card obj) const {
	return strcmp(name.c_str(), obj.name.c_str()) > 0;
}

bool Card::operator== (const Card obj) const {
	return strcmp(name.c_str(), obj.name.c_str()) == 0;
}

bool Card::operator!= (const Card obj) const {
	return !(*this == obj);
}

bool Card::operator<= (const Card obj) const {
	return !(*this > obj);
}

bool Card::operator>= (const Card obj) const {
	return !(*this < obj);
}