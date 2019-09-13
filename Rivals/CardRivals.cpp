/**
 * @brief Rivalsのカード設定
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
	// plane_textの形式: card_name,ability_text,img_name,(uint)power
	char *cols[MAX_COLS];
	char *str_p = new char[plane_text.size() + 1]; // 作業用文字列
	strcpy_s(str_p, plane_text.size() + 1, plane_text.c_str());

	// plane_text の要素分割
	int n_cols = split_plane(str_p, cols);
	
	// エラーチェック
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
	power = atoi(cols[3]);

	delete[] str_p;

	if (!loadImage(img_name)) {
		fprintf(stderr, " WARNING > 指定された画像が読み込めません。\n"
			"            filename : %s\n", img_name.c_str());
		// エラーではない。画像は読み込めなくともよい。
	}

	return true;
}
