/**
 * @brief 手札管理クラス
 **/

#include <vector>
#include <algorithm>  // for sort

#include "Card.h"
#include "Hands.h"

Hands::Hands() {
	// do nothing
}

Hands::Hands(const vector<Card*> _shadow) {
	load(_shadow);
}

Hands::~Hands() {
	cards_shadow.clear();
}

int Hands::load(const vector<Card*> _shadow) {
	copy(_shadow.begin(), _shadow.end(), back_inserter(cards_shadow));

	return cards_shadow.size();
}

bool Hands::show(Card::SHOW_TYPE show_type) {
	bool result = true;
	for (unsigned int i = 0; i < cards_shadow.size(); i++) {
		result = result && show(i, show_type);
	}
	return result;
}

bool Hands::show(int idx, Card::SHOW_TYPE show_type) {
	printf("  < %dth of hands >\n", idx);
	bool result = cards_shadow[idx]->show("", show_type);
	printf("\n");
	return result;
}

void Hands::showLineUp(const string title_head, unsigned int upper, unsigned int left, float scale, bool is_wait) {
	unsigned int x = left, y = upper;
	unsigned int rows = 0, cols = 0;
	for (unsigned int i = 0; i < cards_shadow.size(); i++) {
		// ウィンドウの表示
		char title[256];
		sprintf_s(title, "%shands[%d]", title_head.c_str(), i);
		string w_name = cards_shadow[i]->show(title, scale, y, x, false);
		window_names.push_back(w_name);
		
		// 次に表示するウィンドウの位置決め
		cards_shadow[i]->getImgSize(&rows, &cols);
		x += (unsigned int)(cols * scale);
	}

	if (is_wait)	cv::waitKey();
	
}

void Hands::destroyAllWindows() {
	for (int i = 0; i < window_names.size(); i++) {
		string name = window_names[i];
		if (name != "") {
			// ウィンドウが生成できなかったときは""となっているため
			cv::destroyWindow(name);
		}
	}
	
	window_names.clear();
}

int Hands::in(Card* cs) {
	cards_shadow.push_back(cs);
	return cards_shadow.size();
}

Card* Hands::out(int idx) {
	// Error
	if (idx < 0 || cards_shadow.size() <= idx) {
		return NULL;
	}

	Card *c = cards_shadow[idx];
	cards_shadow.erase(cards_shadow.begin() + idx);

	return c;
}

void Hands::sort() {
	std::sort(
		cards_shadow.begin(), cards_shadow.end()
		, [](const Card* x, const Card* y) {return *x < *y; });
}
