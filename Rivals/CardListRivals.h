#pragma once

/**
 * @brief カードゲーム「R-Rivals」のカードリストを読み込むクラス
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

#include <string>

#include "CardList.h"

class CardListRivals : public CardList {
private:
	// カードリスト1行を読み込むバッファサイズ
#define BUFFER_SIZE 2048 

	// カードのクラスタグ
	typedef enum {
		CARD,
		RIVALS,
		UNKNOWN  // 未知のclass もしくは未指定
	} CARD_CLASS;

	/**
	 * @brief カードリストのカードクラスを分類する
	 * @param str カードクラス情報が書かれた文字列ポインタ
	 * @return カードのクラスタグ
	 **/
	CARD_CLASS cardClassBranch(const char* str);

public:
	CardListRivals();
	// カードリストの読み込み付き
	CardListRivals(string filename);
	~CardListRivals();

	/**
	 * @brief ファイルからカード情報郡を読み込み実態を生成する
	 * @param filename カードリストのファイル名
	 * @return (true) 正常終了 / 異常発生 (false)
	 **/
	virtual bool load(string filename);

};