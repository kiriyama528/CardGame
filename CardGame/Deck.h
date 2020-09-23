#pragma once

/**
 * @brief カードの山札として使うクラス。カードの実態はCardListクラスが管理している。
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

#include <string>
#include <vector>

#include "Card.h"
#include "CardList.h"

using namespace std;

class Deck {
protected:
	// 配ったりする見かけ上のカードポインタ。操作用
	vector<Card*> cards_shadow;

public:
	Deck();

	// カード郡の読み込み付き
	Deck(const vector<Card*> _cards_shadow);

	// 生成済みのカードリストの中身をすべてデッキに読み込む
	Deck(CardList &cl);

	~Deck();

	/**
	 * @brief カード郡の読み込み。取り込み
	 * @param _cards_shadow 取り扱うカードポインター郡
	 * @return 山札の枚数
	 **/
	virtual int load(const vector<Card*> _cards_shadow);

	/**
	 * @brief 山札の上から１枚のカードを引く
	 * @return 引いたカード。カードが引けない場合は NULL
	 **/
	virtual Card* draw();

	/**
	 * @brief 山札をシャッフルする
	 * @return 残りの山札の枚数
	 **/
	virtual int shuffle();

	/**
	 * @brief 山札の上にカードを置く(入れる)
	 * @param c 対象のカードポインタ
	 * @return 残りの山札の枚数
	 **/
	virtual int putTop(Card *c);

	/**
	 * @brief 山札の底にカードを置く(入れる)
	 * @param c 対象のカードポインタ
	 * @return 残りの山札の枚数
	 **/
	virtual int putBottom(Card *c);

	/**
	 * @brief 山札の枚数を取得する
	 * @return 山札の枚数
	 **/
	virtual int get_num() { return cards_shadow.size(); }
	
	/**
	 * @brief 山札中から特定の名前のカードを探してindexを返す
	 *        用途：特定のカードが出るまでドローするとか
	 * @return index を返す。見つからなければ -1
	 **/
	virtual int searchIdx(const string _name) const ;

	/**
	 * @brief 特定のカードを探し取り出す。
	 * @return 探したカード。見つからなければNULL
	 **/
	virtual Card* searchDraw(string _name);
};
