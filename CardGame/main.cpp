/**
 @ brief カードゲームを行う
 @ date 2019/09/03
 @ author kiriyama
 **/

// リンカーの入力を設定
// デバッグとリリースで入力するファイルが異なるのでこのようにしています。

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1なので

#include <string>


#include "Card.h"
#include "Field.h"

using namespace std;


int main(void) {
	
	string plane_text = "card_name,ability_text,KT82_ume.jpg";
	
	// 外部ファイルからの読み込みを行いたい

	//Card card();
	Card card(plane_text);
	card.show();

	// for debug 一時停止
	getchar();

	return 0;
}