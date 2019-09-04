#pragma once

#include <string>
#include <opencv2/opencv.hpp>

using namespace std;


class Card {
private:
	int n_elems = 3; // 読み込みリストから読み込む予定の要素数

protected:
	typedef enum {
		SHOW_TEXT,
		SHOW_IMG_TEXT
	} SHOW_TYPE;

	string name;         // カードの名前
	string ability_text; // カード効果のテキスト文
	cv::Mat img;         // カードの画像


	bool loadImage(const string filename);

public:
	Card();
	// カードの読み込みつき
	Card(string plane_text);
	~Card();

	// カードを読み込み
	virtual bool load(string plane_text);

	// カードを表示する
	virtual void show(SHOW_TYPE type=SHOW_IMG_TEXT);

};

