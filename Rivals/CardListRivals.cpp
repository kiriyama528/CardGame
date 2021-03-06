/**
* @brief カードゲーム「R-Rivals」のカードリストを読み込むクラス
* @date 2019/09/13
* @author kiriyama tomoya
**/

#include <fstream>

#include "CardListRivals.h"
#include "CardRivals.h"

CardListRivals::CardListRivals() : CardList()
{

}


CardListRivals::CardListRivals(string filename)
{
	load(filename);
}


CardListRivals::~CardListRivals()
{
	// do nothing
}


CardListRivals::CARD_CLASS CardListRivals::cardClassBranch(const char* str) {
	if (strcmp(str, "Card") == 0) {
		return CARD;
	}
	else if (strcmp(str, "CardRivals") == 0) {
		return RIVALS;
	}
	else {
		return UNKNOWN;
	}
}


// fix me 親クラスを利用してtemplateクラス作れば、差分だけで表現できそう
bool CardListRivals::load(string filename) {
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
		case RIVALS:
			cards.emplace_back(new CardRivals(buffer));
			break;
		default:
			fprintf(stderr, " ERROR : カードリストファイルで読み込みカードクラスが指定されていません\n");
			break;
		}
	}

	ifs.close();

	return true;
}

const vector<CardRivals*> CardListRivals::rivals_shadow() const{
	// HACK : もっといい方法があると思う
	vector<Card*> card = CardList::shadow();
	int n_card = card.size();
	vector<CardRivals*> card_rivals(n_card);
	for (int i = 0; i < n_card; i++) {
		card_rivals[i] = dynamic_cast<CardRivals*>(card[i]);
	}
	return card_rivals;
}