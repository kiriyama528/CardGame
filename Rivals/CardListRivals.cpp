/**
* @brief �J�[�h�Q�[���uR-Rivals�v�̃J�[�h���X�g��ǂݍ��ރN���X
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


// fix me �e�N���X�𗘗p����template�N���X���΁A���������ŕ\���ł�����
bool CardListRivals::load(string filename) {
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
		case RIVALS:
			cards.emplace_back(new CardRivals(buffer));
			break;
		default:
			fprintf(stderr, " ERROR : �J�[�h���X�g�t�@�C���œǂݍ��݃J�[�h�N���X���w�肳��Ă��܂���\n");
			break;
		}
	}

	ifs.close();

	return true;
}

const vector<CardRivals*> CardListRivals::rivals_shadow() const{
	// HACK : �����Ƃ������@������Ǝv��
	vector<Card*> card = CardList::shadow();
	int n_card = card.size();
	vector<CardRivals*> card_rivals(n_card);
	for (int i = 0; i < n_card; i++) {
		card_rivals[i] = dynamic_cast<CardRivals*>(card[i]);
	}
	return card_rivals;
}