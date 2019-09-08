#pragma once

#include <string>

#include "CardList.h"

class CardListRivals : public CardList {
private:
	typedef enum {
		CARD,
		RIVALS,
		UNKNOWN  // ���m��class �������͖��w��
	} CARD_CLASS;
	CARD_CLASS cardClassBranch(const char* str);

protected:
	

public:
	CardListRivals();
	CardListRivals(string filename);
	~CardListRivals();


	// �t�@�C������J�[�h���S��ǂݍ��݃f�b�L�𐶐�����
	virtual bool load(string filename);

};