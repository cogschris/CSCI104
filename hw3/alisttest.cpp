#include "alistint.h"
#include "gtest/gtest.h"

TEST(AListInt, GetNominal) {
	AListInt test;
	for (int i = 0; i < 5; i++) {
		test.insert(i, i + 1);
	}

	for (int i = 0; i < 5; i++) {
		EXPECT_EQ(test.get(i), i + 1);
	}
}