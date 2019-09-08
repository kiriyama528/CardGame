#pragma once

#include <string>
#include <opencv2/opencv.hpp>

using namespace std;


class Card {
private:
	const int n_elems = 3; // 読み込みリストから読み込む予定の要素数

protected:
#define MAX_COLS 15
	string name;         // カードの名前
	string ability_text; // カード効果のテキスト文
	cv::Mat img;         // カードの画像

	
	// 画像の読み込み。成功 true / 失敗 false
	bool loadImage(const string filename);

public:
	typedef enum {
		SHOW_TEXT,
		SHOW_IMG_TEXT
	} SHOW_TYPE;

	Card();
	// カードの読み込みつき
	Card(string plane_text);
	~Card();

	// カードを読み込み
	virtual bool load(const string plane_text);

	// カードを表示する
	virtual void show(string img_head="", SHOW_TYPE type=SHOW_IMG_TEXT);

	virtual bool operator < (const Card obj) const;
	virtual bool operator > (const Card obj) const;
	virtual bool operator == (const Card obj) const;
	virtual bool operator != (const Card obj) const;
	virtual bool operator <= (const Card obj) const;
	virtual bool operator >= (const Card obj) const;

	const string get_name() const { return name; }

	const string get_ability() const { return ability_text; }

	// 終端文字に類する文字かどうか true / false
	static bool endStr(char target);

	// ,(コンマ) で要素を分類する。plane_textの分解用
	static int split_plane(char *plane_text, char **cols);

};

