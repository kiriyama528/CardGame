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
#include "Field.h"

using namespace std;


int main(void) {
	
	string plane_text = "card_name,ability_text,KT82_ume.jpg";
	
	// �O���t�@�C������̓ǂݍ��݂��s������

	//Card card();
	Card card(plane_text);
	card.show();

	// for debug �ꎞ��~
	getchar();

	return 0;
}