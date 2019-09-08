#pragma once

#include <string>

#include "CardList.h"

class CardListRivals : public CardList {
private:
	typedef enum {
		CARD,
		RIVALS,
		UNKNOWN  // 未知のclass もしくは未指定
	} CARD_CLASS;
	CARD_CLASS cardClassBranch(const char* str);

protected:
	

public:
	CardListRivals();
	CardListRivals(string filename);
	~CardListRivals();


	// ファイルからカード情報郡を読み込みデッキを生成する
	virtual bool load(string filename);

};