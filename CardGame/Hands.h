#pragma once

#include <vector>

#include "Card.h"

using namespace std;

class Hands {
protected:
	vector<Card*> cards_shadow;

public:
	Hands();
	Hands(const vector<Card*> _shadow);
	~Hands();

	/**
	 * @return èD‚Ì–‡”
	 **/
	int load(const vector<Card*> _shadow);

	/**
	 * @brief èD‚ğ‘S•”Œ©‚é
	 **/
	void show(Card::SHOW_TYPE show_type = Card::SHOW_IMG_TEXT);

	/**
	 * @brief “Á’è‚ÌèD‚ğŒ©‚é
	 *        ( 0 <= idx < cards_shadow.size() )
	 **/
	void show(int idx, Card::SHOW_TYPE show_type = Card::SHOW_IMG_TEXT);

	// èD‚ğ•À‚×‚Ä‚·‚×‚Ä•\¦‚·‚é
	void showLineUp(unsigned int upper, unsigned int left, float scale);

	/**
	 * @return èD‚Ì–‡”
	 **/
	int in(Card* cs);

	/**
	 * @return æ‚èœ‚¢‚½èDBidx‚ª•s“KØ‚È‚çNULL

	 **/
	Card* out(int idx);

	void sort();
};