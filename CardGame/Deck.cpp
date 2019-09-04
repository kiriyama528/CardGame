
#include <iostream>
#include <string>
#include <vector>

#include <algorithm>

#include "Card.h"
#include "Deck.h"



Deck::Deck() {
}

Deck::Deck(string filename) {
	load(filename);
}

Deck::~Deck() {
	// メモ：vector<Card> cards
	for (unsigned int i = 0; i < cards.size(); i++) {
		delete cards[i]; // 実態の削除
	}
	cards.clear(); // ポインタvectorの初期化

	// メモ：shadowは本体と同じ実態を指すもの。操作用なのでポインタを消すだけでよい
	cards_shadow.clear();

}



Deck::CARD_CLASS Deck::cardClassBranch(const char* str) {
	if (strcmp(str, "Card") == 0) {
		return CARD;
	}
	else if (strcmp(str, "Rivals") == 0) {
		return RIVALS;
	}
	else {
		return UNKNOWN;
	}
}


// #class Card    <- 読み込む class。ヘッダーは先頭に#
// card_name1,ability1,img_name1
// card_name2,ability2,img_name2
// card_name3,ability3,img_name3

bool Deck::load(string filename) {
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
		case RIVALS:
			// ↓ まだRivalsクラスは作ってないのでコメントアウト
			// cards.emplace_back(new Rivals(buffer));
			break;
		default:
			fprintf(stderr, " ERROR : カードリストファイルで読み込みカードクラスが指定されていません\n");
			break;
		}
	}

	ifs.close(); // fix me ? もしかしたらいらないかも

	// 操作用としてshadowを作成
	copy(cards.begin(), cards.end(), back_inserter(cards_shadow));

	return true;
}

Card* Deck::draw() {
	if (cards_shadow.empty()) return NULL;

	// 山札の↑(Top) は vectorの[0]
	Card *c = cards_shadow[0];
	cards_shadow.erase(cards_shadow.begin());

	return c;
}

int Deck::shuffle() {
	random_shuffle(cards_shadow.begin(), cards_shadow.end());

	return cards_shadow.size();
}

int Deck::putTop(Card *c) {
	cards_shadow.insert(cards_shadow.begin(), c);

	return cards_shadow.size();
}

int Deck::putBottom(Card *c) {
	cards_shadow.push_back(c);

	return cards_shadow.size();
}