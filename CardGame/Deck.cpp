
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
	// �����Fvector<Card> cards
	for (unsigned int i = 0; i < cards.size(); i++) {
		delete cards[i]; // ���Ԃ̍폜
	}
	cards.clear(); // �|�C���^vector�̏�����

	// �����Fshadow�͖{�̂Ɠ������Ԃ��w�����́B����p�Ȃ̂Ń|�C���^�����������ł悢
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


// #class Card    <- �ǂݍ��� class�B�w�b�_�[�͐擪��#
// card_name1,ability1,img_name1
// card_name2,ability2,img_name2
// card_name3,ability3,img_name3

bool Deck::load(string filename) {
#define BUFFER_SIZE 2048
	ifstream ifs(filename);

	// �t�@�C���`�F�b�N
	if (ifs.fail()) {
		fprintf(stderr, " Error > �J�[�h���X�g�t�@�C�����ǂݍ��߂܂���\n"
			"          filename : %s\n", filename.c_str());
		return false;
	}

	char buffer[BUFFER_SIZE];
	CARD_CLASS card_class;
	while (ifs.getline(buffer, BUFFER_SIZE)) {
		// �w�b�_�[����
		if (buffer[0] == '#') {
			if (strstr(buffer, "#class")) {
				card_class = cardClassBranch(&buffer[7]);
			}
			continue;
		}

		// �J�[�h�ǂݍ��ݏ���
		switch (card_class) {
		case CARD:
			cards.emplace_back(new Card(buffer));
			break;
		case RIVALS:
			// �� �܂�Rivals�N���X�͍���ĂȂ��̂ŃR�����g�A�E�g
			// cards.emplace_back(new Rivals(buffer));
			break;
		default:
			fprintf(stderr, " ERROR : �J�[�h���X�g�t�@�C���œǂݍ��݃J�[�h�N���X���w�肳��Ă��܂���\n");
			break;
		}
	}

	ifs.close(); // fix me ? �����������炢��Ȃ�����

	// ����p�Ƃ���shadow���쐬
	copy(cards.begin(), cards.end(), back_inserter(cards_shadow));

	return true;
}

Card* Deck::draw() {
	if (cards_shadow.empty()) return NULL;

	// �R�D�́�(Top) �� vector��[0]
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