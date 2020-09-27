/**
 * @brief カード郡の生成と、カードの実態を管理する。
 *        必要なカードは最初に全部生成してしまう。途中からカードが増えたりはしない。
 *        このクラスの破棄時に、カード実態もすべて破棄する。ゲーム終了時に破棄すること。
 * @date 2019/09/04
 * @author kiriyama tomoya
 **/


#include <fstream>
#include <string>
#include <vector>

#include "Card.h"
#include "CardList.h"


CardList::CARD_CLASS CardList::cardClassBranch(const char* str) const {
	if (strcmp(str, "Card") == 0) {
		return CARD;
	}
	else {
		return UNKNOWN;
	}
}


CardList::CardList() {
	// do nothing
}


CardList::CardList(const string filename) {
	load(filename);
}


CardList::~CardList() {
	// メモ：vector<Card> cards
	for (unsigned int i = 0; i < cards.size(); i++) {
		delete cards[i]; // 実態の削除
	}
	cards.clear(); // ポインタvectorの初期化
}


// #class Card    <- 読み込む class。ヘッダーは先頭に#
// card_name1,ability1,img_name1
// card_name2,ability2,img_name2
// card_name3,ability3,img_name3

bool CardList::load(const string filename) {
#define BUFFER_SIZE 2048
	ifstream ifs(filename);

	// ファイルチェック
	if (ifs.fail()) {
		fprintf(stderr, " Error > カードリストファイルが読み込めません\n"
			"          filename : %s\n", filename.c_str());
		return false;
	}

	char buffer[BUFFER_SIZE];
	CARD_CLASS card_class;
	while (ifs.getline(buffer, BUFFER_SIZE)) {
		// ヘッダー処理
		if (buffer[0] == '#') {
			if (strstr(buffer, "#class")) {
				card_class = cardClassBranch(&buffer[7]);
			}
			continue;
		}

		// カード読み込み処理
		switch (card_class) {
		case CARD:
			cards.emplace_back(new Card(buffer));
			break;
		default:
			fprintf(stderr, " ERROR : カードリストファイルで読み込みカードクラスが指定されていません\n");
			ifs.close();
			return false;
		}
	}

	ifs.close();

	return true;
}


const vector<Card*> CardList::shadow() const {
	return cards;
}