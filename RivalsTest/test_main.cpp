#include <assert.h>
#include <vector>


// TODO : �K�؂Ȗ��O�ɂ���
void Test1() {
	CardListRivals card_list("card_rival_list.txt");
	const vector<Card *> cards = card_list.shadow(); // ����Ȃ���D
	FieldRivals field;

	const vector<int> p1_idx = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3 };
	const vector<int> p2_idx = { 0, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 2, 3, 4, 5, 6, 7, 3, 4, 5, 6, 7 };
	const unsigned int ans_p1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4, 0, 2, 0, 0, 0, 0, 0, 2, 0, 1, 0 };
	const unsigned int ans_p2[] = { 0, 0, 0, 0, 0, 7, 0, 0, 0, 4, 0, 2, 1, 1, 0, 0, 0, 2, 1, 1, 1, 0, 0, 1, 0, 1 };

	PlayAndExpect();
}


// TODO : �K�؂Ȗ��O�ɂ���
void Test2() {
	CardListRivals card_list("card_rival_list.txt");
	const vector<Card *> cards = card_list.shadow(); // ����Ȃ���D
	FieldRivals field;

	const vector<int> p1_idx = { 4, 4, 4, 4, 5, 5, 5, 6, 6, 7, 7 };
	const vector<int> p2_idx = { 4, 5, 6, 7, 5, 6, 7, 6, 7, 7, 1 };
	const unsigned int ans_p1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
	const unsigned int ans_p2[] = { 0, 3, 1, 1, 0, 2, 1, 0, 2, 0, 4 };

	PlayAndExpect();
}


// TODO : �K�؂Ȗ��O�ɂ���
void Test3() {
	CardListRivals card_list("card_rival_list.txt");
	const vector<Card *> cards = card_list.shadow(); // ����Ȃ���D
	FieldRivals field;

	// �v���ӊm�F
	const vector<int> p1_idx = { 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 4 };
	const vector<int> p2_idx = { 0, 1, 2, 3, 4, 5, 6, 4, 7, 7, 2 };
	const unsigned int ans_p1[] = { 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 3 };
	const unsigned int ans_p2[] = { 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0 };

	// 5�͂��ׂĂ̌��ʂ𖳌�������

	PlayAndExpect();
}


// TODO : �K�؂Ȗ��O�ɂ���
void Test4() {
	CardListRivals card_list("card_rival_list.txt");
	const vector<Card *> cards = card_list.shadow(); // ����Ȃ���D
	FieldRivals field;

	// �v���ӊm�F
	const vector<int> p1_idx = { 6, 1, 6, 1, 6, 2, 6, 3, 6, 4 };
	const vector<int> p2_idx = { 7, 2, 7, 3, 7, 3, 7, 3, 7, 5 };
	const unsigned int ans_p1[] = { 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 };
	const unsigned int ans_p2[] = { 1, 0, 1, 0, 2, 1, 1, 0, 1, 0 };

	PlayAndExpect();
}


// TODO : �K�؂Ȉ���������
// TODO : �֐������K�؂Ȗ��O�ɂ���
// TODO : assert�֐�������
void PlayAndExpect(){
	for (int i = 0; i < p1_idx.size(); i++) {
		printf("\ridx:%d", i);
		// �������Ŏg�p����J�[�h
		CardRivals *card_p1 = dynamic_cast<CardRivals*>(cards[p1_idx[i]]);
		CardRivals *card_p2 = dynamic_cast<CardRivals*>(cards[p2_idx[i]]);


		// ��D�̃v���C winner= 0 or 1
		unsigned int p1_wins, p2_wins;
		if (!field.playCards(card_p1, card_p2, p1_wins, p2_wins)) {
			// �\�͉������ɖ�蔭��
			fprintf(stderr, " ERROR:�J�[�h�\�͉������ɖ�蔭��\n �I�����܂�\n");
			// �I��������D�̌��J
			card_p1->show("p1:");
			card_p2->show("p2:");
			getchar();
			getchar();
			getchar();
			exit(1);
		}

		if (ans_p1[i] != p1_wins || ans_p2[i] != p2_wins) {
			printf(" index[%d] �̂Ƃ�(card[%d] - card[%d])�\�z�ƈႤ���ʂƂȂ�܂����B\n", i, p1_idx[i], p2_idx[i]);
			printf(" �\�z�F�@(P1) %d - %d (P2)\n", ans_p1[i], ans_p2[i]);
			printf(" ���ʁF�@(P1) %d - %d (P2)\n", p1_wins, p2_wins);
			printf("\n");
		}
	}

	printf("�S���I��\n");

	// �ꎞ��~
	getchar();
}


int main(void) {
	Test1();
	Test2();
	Test3();
	Test4();

	fprintf(stderr, "\t[[ %s SUCCESS!! ]]\n", __func__);
	return 0;
}
