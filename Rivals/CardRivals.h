#pragma once

#include <string>

#include "Card.h"

class CardRivals : public Card {
private:
	const int n_elems = 4;

protected:
	unsigned int power;

public:
	CardRivals();
	CardRivals(const string plane_text);
	~CardRivals();

	virtual bool load(string plane_text);
	unsigned int get_power() const { return power; }

};