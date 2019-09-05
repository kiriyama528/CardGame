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
	// plane_textの形式: card_name,ability_text,img_name
	char *cols[MAX_COLS];
	char *str_p = new char[plane_text.size() + 1];
	strcpy_s(str_p, plane_text.size() + 1, plane_text.c_str());
	int n_cols = split_plane(str_p, cols);
	if (n_cols != n_elems) {
		fprintf(stderr, " ERROR > カード生成時の要素が不適切です。\n"
			            "         %d要素読み込みの予定が%d要素あります。\n"
		                "         string : %s\n", n_elems, n_cols, plane_text.c_str());
		delete[] str_p;
		return false;
	}
	name = cols[0];          // fix me idとかは今後ずれる可能性もあるので、柔軟性をあげたい
	ability_text = cols[1];  // fix me idとかは今後ずれる可能性もあるので、柔軟性をあげたい
	string img_name = cols[2];
	
	delete[] str_p;

	if (!loadImage(img_name)) {
		fprintf(stderr, " WARNING > 指定された画像が読み込めません。\n"
                        "            filename : %s\n", img_name.c_str());
		// エラーではない。画像は読み込めなくともよい。
	}

	return true;
}

void Card::show(SHOW_TYPE type) {
	cout << "name : " << name << endl;
	cout << "ability : " << ability_text << endl;
	
	// 画像も表示するか
	if (type == SHOW_IMG_TEXT) {
		cv::imshow(name, img);
		cv::waitKey(0);
		cv::destroyWindow(name); // fix me いったん表示するって感じで
	}
}


/**
 * @brief 文字を分割しcolsで指す。今のところ区切り文字は ','に固定
 **/
int split_plane(char *plane_text, char **cols) {
	int cnt = 0;
	cols[0] = plane_text;
	cnt++;
	while (*plane_text) {
		// fix me 区切り文字は','。決めうちはよくない。柔軟にしよう
		if (*plane_text == ',') {
			*plane_text = '\0';
			// 最後に ',' が入っているような特殊な状況であれば
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
	img = cv::imread(filename, 1); // RGB読み込み
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