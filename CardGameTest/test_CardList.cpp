#include "pch.h"
#include "CardList.h"

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1‚È‚Ì‚Å

class UnitTestCardList : public ::testing::Test {
protected:
	virtual void SetUp() {
		// do nothing
	}

	virtual void TearDown() {
		// do nothing
	}
};

TEST_F(UnitTestCardList, sample) {
	Card card;

}
