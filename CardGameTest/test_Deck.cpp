#include "pch.h"
#include "Deck.h"

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1‚È‚Ì‚Å

class UnitTestDeck : public ::testing::Test {
protected:
	virtual void SetUp() {
		// do nothing
	}

	virtual void TearDown() {
		// do nothing
	}
};

// making
TEST_F(UnitTestDeck, load) {
	Deck deck;
	
}

// making
TEST_F(UnitTestDeck, draw) {
	Card card;
	Deck deck;


}

// making
TEST_F(UnitTestDeck, shuffle) {
	Card card;
	Deck deck;


}


// making
TEST_F(UnitTestDeck, putTop) {
	Card card[2];
	Deck deck;
	deck.putTop(&card[0]);
	
	// deck.draw();
}

// making
TEST_F(UnitTestDeck, putBottom) {
	Card card[2];
	Deck deck;
	deck.putTop(&card[0]);

	// deck.draw();
}

// making
TEST_F(UnitTestDeck, get_num) {
	Deck deck;
	int expected = 0;
	int actual = deck.get_num();
	EXPECT_EQ(expected, actual);

	Card card[2];
	
	deck.putTop(&card[0]);

	// deck.draw();
}

// making
TEST_F(UnitTestDeck, searchIdx) {
	Card card[2];
	Deck deck;
	deck.putTop(&card[0]);

	// deck.draw();
}

// making
TEST_F(UnitTestDeck, searchDraw) {
	Card card[2];
	Deck deck;
	deck.putTop(&card[0]);

	// deck.draw();
}
