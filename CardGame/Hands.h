#pragma once

/**
 * @brief カードの手札として使うクラス。カードの実態はCardListクラスが管理している。
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

#include <vector>

#include "Card.h"

using namespace std;

class Hands {
protected:
	// 手札
	vector<Card*> cards_shadow;

	// 手札を表示しているウィンドウの名前郡
	vector<string> window_names;

public:
	Hands();
	Hands(const vector<Card*> _shadow);
	~Hands();

	/**
	 * @brief カード郡を手札として設定する
	 * @param _shadow 手札にしたいカードポインタ郡
	 * @return 手札の枚数
	 **/
	int load(const vector<Card*> _shadow);

	/**
	 * @brief 手札を１枚ずつ、全部表示する。Cardのshowに従う
	 * @param show_type カード表示形式を指定する
	 **/
	void show(Card::SHOW_TYPE show_type = Card::SHOW_IMG_TEXT);

	/**
	 * @brief 特定の手札を1枚表示する。Cardのshowに従う
	 * @param idx 手札番号 ( 0 <= idx < cards_shadow.size() )
	 * @param show_type カード表示形式を指定する
	 **/
	void show(int idx, Card::SHOW_TYPE show_type = Card::SHOW_IMG_TEXT);

	/**
	 * @brief 手札を並べてすべて表示する。左上の座標やスケールも指定
	 * @param title_head ウィンドウタイトルに表示する頭文章(例 P1:)
	 * @param upper 始点 y座標
	 * @param left 始点 x座標
	 * @param scale 読み込み画像に対する表示倍率
	 * @param is_wait ウィンドウ表示後にwaitKey()するかどうか
	 * メモ：destroyAllWindows() でウィンドウを消せる
	 **/
	void showLineUp(string title_head, unsigned int upper, unsigned int left, float scale, bool is_wait=false);

	// 
	/**
	 * @brief 表示している手札(ウィンドウ)をすべて閉じる
	 *         showLineUp()関数使用後に呼び出す と想定
	 **/
	void destroyAllWindows();

	/**
	 * @brief 手札に１枚カードを追加する
	 * @return 手札の枚数
	 **/
	int in(Card* cs);

	/**
	 * @brief 手札からカードを1枚出す
	 * @param idx 手札番号
	 * @return 取り除いた手札。idxが不適切ならNULL
	 **/
	Card* out(int idx);

	/**
	 * @brief 手札を名前順(昇順)にソートする
	 **/
	void sort();
};