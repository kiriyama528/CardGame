/**
 @ brief �J�[�h�Q�[�����s��
 @ date 2019/09/03
 @ author kiriyama
 **/

// �����J�[�̓��͂�ݒ�
// �f�o�b�O�ƃ����[�X�œ��͂���t�@�C�����قȂ�̂ł��̂悤�ɂ��Ă��܂��B

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1�Ȃ̂�


#include <string>

#include "Card.h"
#include "Deck.h"
#include "Hands.h"
#include "CardList.h"

using namespace std;


int main(void) {
	CardList card_list("card_list.txt");
	Deck deck(card_list);
	Hands hands;
	
	int num = deck.shuffle();
	deck.shuffle();

	for (int i = 0; i < num; i++) {
		Card *tmp = deck.draw();
		hands.in(tmp);
	}
	
	printf("--- before ---\n");
	hands.show(Card::SHOW_TEXT);
	hands.sort();
	printf("--- after  ---\n");
	hands.show(Card::SHOW_TEXT);

	// for debug �ꎞ��~
	printf("�I�����O\n");
	getchar();

	return 0;
}

