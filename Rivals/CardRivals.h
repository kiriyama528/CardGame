#pragma once

/**
 * @brief カードゲーム「R-Rivals」のカード
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

#include <string>

#include "Card.h"

class CardRivals : public Card {
private:
	// カード情報の要素文字列。csvによって区切られた要素数
	const int n_elems = 4;

protected:
	// カードの強さ
	unsigned int power;

public:
	CardRivals();
	// カード情報読み込み付き
	CardRivals(const string plane_text);
	virtual ~CardRivals();

	/**
	 * @brief R-Rivalsのカード情報を読み込む
	 * @param plane_text csv形式のカード情報文字列
	 * @return (true) 正常終了 / 異常発生 (false)
	 **/
	virtual bool load(string plane_text);

	/**
	 * @brief カードの強さを取得する
	 * @return カードの強さ
	 **/
	unsigned int get_power() const { return power; }

};