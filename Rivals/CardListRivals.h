#pragma once

/**
 * @brief カードゲーム「R-Rivals」のカードリストを読み込むクラス
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

#include <string>

#include "CardList.h"
#include "CardRivals.h" // TODO: いらないかも、要チェック


// TODO : わざわざ継承してoverrideする必要はないのでは？
//        親クラスをインターフェースにしたほうがよいかも
class CardListRivals : public CardList {
private:
	// カードリスト1行を読み込むバッファサイズ
#define BUFFER_SIZE 2048 

	// カードのクラスタグ
	// TODO : 親クラスでも同盟のenum定義があって危険
	//        もう少し適切な記述方法があるはず
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
	// TODO : 別クラスにするなどしてpublicメソッドにする
	//        テストを書くために。
	//        カードブランチ機能自体は、将来実装するものも分類してよいのでは？
	CARD_CLASS cardClassBranch(const char* str);

public:
	CardListRivals();
	// カードリストの読み込み付き
	CardListRivals(string filename);
	virtual ~CardListRivals();

	/**
	 * @brief ファイルからカード情報郡を読み込み実態を生成する
	 * @param filename カードリストのファイル名
	 * @return (true) 正常終了 / 異常発生 (false)
	 **/
	virtual bool load(string filename);

	// HACK: 汚いので、よりキレイなコードに書き直す
	// 操作用のリストを生成する
	virtual const vector<CardRivals*> rivals_shadow() const;

};