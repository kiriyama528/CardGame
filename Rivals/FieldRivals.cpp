/**
 * @brief カードゲーム「R-Rivals」のカード効果を処理する場
 * @date 2019/09/13
 * @author kiriyama tomoya
 **/

#include "Card.h"
#include "FieldRivals.h"
#include "CardRivals.h"


FieldRivals::FieldRivals() {
	card_his_p1.push_back(NULL);
	card_his_p2.push_back(NULL);

	power_up[P1] = 0;
	power_up[P2] = 0;

	powers[P1] =
	powers[P2] = 0;

	reveal[P1] =
	reveal[P2] = false;

	draw_storage[P1] =
	draw_storage[P2] = 0;
}


FieldRivals::~FieldRivals() {
	card_his_p1.clear();
	card_his_p2.clear();
}


 bool FieldRivals::playCards(
			CardRivals * c1,
			CardRivals * c2,
			unsigned int &p1_wins,
			unsigned int &p2_wins)
	{
	 wins[P1] = wins[P2] = 0;

	// 前のカードの効果を適用した強さを記録
	enchantment(c1, c2);

	// カードの効果を発動。かつ能力残留
	if (!ability(c1, c2)) {
		// 能力解決時に問題発生
		return false;
	}

	card_his_p1.emplace_back(c1);
	card_his_p2.emplace_back(c2);

	// 能力解決により勝利数が変化していたら
	if (wins[P1] != 0 || wins[P2] != 0) {
		p1_wins = wins[P1];
		p2_wins = wins[P2];
		return true;
	}
	else { // 普通に勝敗勝負
		if (powers[P1] == powers[P2]) {
			draw_storage[P1] += 1;
			draw_storage[P2] += 1;
		}
		else if (powers[P1] > powers[P2]) {
			wins[P1] = 1 + draw_storage[P1];
			draw_storage[P1] =
			draw_storage[P2] = 0;
		}
		else {
			wins[P2] = 1 + draw_storage[P2];
			draw_storage[P1] =
			draw_storage[P2] = 0;
		}

		p1_wins = wins[P1];
		p2_wins = wins[P2];
		return true;
	}
}


bool FieldRivals::enchantment(const CardRivals *c1, const CardRivals *c2) {
	// fix me falseになるエラー処理があるなら追加
	powers[P1] = c1->get_power() + power_up[P1];
	powers[P2] = c2->get_power() + power_up[P2];

	power_up[P1] = power_up[P2] = 0;
	reveal[P1] = reveal[P2] = false;

	return true;
}


FieldRivals::ABILITY_TAG FieldRivals::branchAbility(const CardRivals *c) {
	const string txt = c->get_ability();
	const string template_txt[] = {
		"次回に持ち越し",
		"王子ならゲームに勝利",
		"次回は相手公開",
		"強弱反転",
		"２勝",
		"無効化",
		"次回は＋２",
		"絶対勝利"
	};
	
	unsigned int n_template = sizeof(template_txt) / sizeof(template_txt[0]);
	for (int i = 0; i < n_template; i++) {
		if (txt == template_txt[i]) {
			return (ABILITY_TAG)i;
		}
	}

	return UNKNOWN;
}


void FieldRivals::abilityDraw() {
	powers[P1] =
		powers[P2] = 0;
}


bool FieldRivals::abilityPrincess(PLAYER_NUMBER p, ABILITY_TAG you_tag) {
	if (you_tag == WIN) {
		wins[p] += 4;
		return true;
	}

	return false;
}


void FieldRivals::abilitySpy(PLAYER_NUMBER p) {
	
	// 自分も公開しないといけない状態ならば
	if (reveal[p]) {
		// お互い公開しない
		reveal[P1] = reveal[P2] = false;
		return;
	}

	reveal[N_PLAYERS-1 - p] = true;
}


void FieldRivals::abilityReverse() {
	powers[P1] = -powers[P1];
	powers[P2] = -powers[P2];
}


void FieldRivals::abilityDouble(PLAYER_NUMBER p) {
	draw_storage[p] += 1;
}


void FieldRivals::abilityPowerUp(PLAYER_NUMBER p, int up) {
	power_up[p] = up;
}


void FieldRivals::abilityWin(PLAYER_NUMBER p) {
	// パワーアップにより擬似的に処理
	// 王子同士や将軍の効果も考慮できる
	powers[p] += PRINCE_POWER_UP;
}


bool FieldRivals::ability(const CardRivals *c1, const CardRivals *c2) {
	const CardRivals *cc[N_PLAYERS] = { c1, c2 };
	//	void (*fpfunc[N_PLAYERS])(CardRivals*); // 使いたかったが不適
	ABILITY_TAG abi_tag[N_PLAYERS];

	for (int i = 0; i < N_PLAYERS; i++) {
		abi_tag[i] = branchAbility(cc[i]);
	}
	
	// 能力実行
	if (abi_tag[P1] == UNKNOWN || abi_tag[P2] == UNKNOWN) {
		// ERROR
		return false;
	}

	/// 強制終了: 5
	if (abi_tag[P1] == INVALID || abi_tag[P2] == INVALID) {
		// お互いに能力を発動せずに終了
		return true;
	}

	/// 直接影響を及ぼさない系: 2, 4, 6
	for (int i = 0; i < N_PLAYERS; i++) {
		switch (abi_tag[i]) {
		case SPY:
			abilitySpy((PLAYER_NUMBER)i);
			break;
		case DOUBLE:
			abilityDouble((PLAYER_NUMBER)i);
			break;
		case POWER_2:
			abilityPowerUp((PLAYER_NUMBER)i, 2);
			break;
		default:
			break;
		}
	}

	/// 相手によって効果が変化: 1
	for (int i = 0; i < N_PLAYERS; i++) {
		if ( abi_tag[i] == PRINCESS) {
			if (abilityPrincess((PLAYER_NUMBER)i, abi_tag[N_PLAYERS - 1 - i])) {
				return true;
			}
		}
	}

	/// 反転: 3
	for (int i = 0; i < N_PLAYERS; i++) {
		if (abi_tag[i] == REVERSE) {
			abilityReverse();
		}
	}

	/// 勝利 7
	for (int i = 0; i < N_PLAYERS; i++) {
		if (abi_tag[i] == WIN) {
			abilityWin((PLAYER_NUMBER)i);
		}
	}

	/// 最後に発動: 0
	for (int i = 0; i < N_PLAYERS; i++) {
		if (abi_tag[i] == DRAW) {
			abilityDraw();
		}
	}

	return true;
}


bool FieldRivals::isReveal(bool reveal_flag[N_PLAYERS]) {
	bool tmp = false;
	for (int i = 0; i < N_PLAYERS; i++) {
		reveal_flag[i] = reveal[i];
		tmp = tmp || reveal_flag[i];
	}

	return tmp;
}
