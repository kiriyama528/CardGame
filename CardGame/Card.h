#pragma once

/**
 * @brief カードに対するクラス
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

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

	/**
	 * @brief 画像の読み込み
	 * @param filename 画像ファイル名
	 * @return 成功 true / 失敗 false
	 **/
	bool loadImage(const string filename);

public:
	// カード表示時のモード
	typedef enum {
		SHOW_TEXT,
		SHOW_IMG_TEXT
	} SHOW_TYPE;

	Card();
	// カードの読み込み付き
	Card(string plane_text);
	~Card();

	/**
	 * @brief カードを読み込む
	 * @param plane_text csv１行で書かれたカード情報
	 * @return (true) 読み込み終了 / 読み込み失敗 (false)
	 **/
	virtual bool load(const string plane_text);
 
	/**
	 * @param カードを表示する
	 * @param img_head ウィンドウのタイトル
	 * @param type 表示形式の指定
	 **/
	virtual bool show(const string title_head, SHOW_TYPE type=SHOW_IMG_TEXT);

	/**
	 * @brief カードを指定の場所とscaleで表示する
	 * @param title ウィンドウのタイトル
	 * @param scale 画像の表示倍率
	 * @param upper 始点 y座標
	 * @param left  始点 x座標
	 * @param is_wait ウィンドウ表示後にキー入力を待つか
	 * @return windowの名前を返す。ウィンドウ削除時に参照する
	 **/
	string show(const string title, float scale, unsigned int upper, unsigned int left, bool is_wait);

	virtual bool operator < (const Card obj) const;
	virtual bool operator > (const Card obj) const;
	virtual bool operator == (const Card obj) const;
	virtual bool operator != (const Card obj) const;
	virtual bool operator <= (const Card obj) const;
	virtual bool operator >= (const Card obj) const;

	// カードの名前を返す
	const string get_name() const { return name; }

	// カードの効果テキストを返す
	const string get_ability() const { return ability_text; }

	/**
	 * @brief target が終端文字に類する文字かどうか
	 * @param target 対象とする文字
	 * @return (true) 終端文字 / そうではない (false)
	 **/
	static bool endStr(char target);

	/**
	 * @brief 文字列を",(コンマ)"で要素文字列に分解する。破壊的文字列操作。
	 * @param plane_text 分解したい文字列
	 * @param cols 分解したそれぞれの要素文字列の先頭文字をさすポインタ配列
	 * @return 分解した要素数
	 **/
	static int split_plane(char *plane_text, char *cols[]);
	
	/**
	 * @brief カードの画像サイズを取得する
	 * @param rows (OUT)行数
	 * @param cols (OUT)列数
	 * @return (true) 取得成功 / 画像がありません (false)
	 **/
	bool getImgSize(unsigned int *rows, unsigned int *cols) const {
		*rows = img.rows;
		*cols = img.cols;
		return !img.empty(); 
	}
};

