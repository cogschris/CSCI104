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

TEST(AListInt, AddNomial) {
	AListInt test;
	EXPECT_EQ(test.empty(), true);
	test.insert(0, 5);
	test.insert(1, 3);
	test.insert(0, 4);
	test.insert(3, 30);
	test.insert(4, 10);
	test.insert(5, 44);
	test.insert(6, 77);
	test.insert(6, 66);

	EXPECT_EQ(test.get(0), 4);
	EXPECT_EQ(test.get(1), 5);
	EXPECT_EQ(test.get(2), 3);
	EXPECT_EQ(test.get(3), 30);
	EXPECT_EQ(test.get(4), 10);
	EXPECT_EQ(test.get(5), 44);
	EXPECT_EQ(test.get(6), 66);
	EXPECT_EQ(test.get(7), 77);

}

TEST(AListInt, RemoveNomial) {
	AListInt test;
	test.insert(0, 5);
	test.insert(0, 1);
	EXPECT_EQ(test.size(), 2);
	test.remove(0);
	EXPECT_EQ(test.size(), 1);
	EXPECT_EQ(test.get(0), 5);
	test.remove(0);
	EXPECT_EQ(test.empty(), true);
}

TEST(AListInt, Adding) {
	AListInt test1;
	AListInt test2;
	AListInt test3;

	test1.insert(0, 5);
	test1.insert(1, 6);
	test1.insert(2, 3);

	test2.insert(0, 3);
	test2.insert(1, 4);

	EXPECT_EQ(test1.size(), 3);
	EXPECT_EQ(test2.size(), 2);
	EXPECT_EQ(test3.empty(), true);

	test3 = test1 + test2;

	EXPECT_EQ(test3.size(), 5);
	EXPECT_EQ(test3.get(0), 5);
	EXPECT_EQ(test3.get(3), 3);
}

TEST(AListInt, SetNomial) {
	AListInt test1;
	for (int i = 0; i < 5; i++) {
		test1.insert(i, i + 1);
	}

	AListInt test2(test1);
	for (int i = 0; i < 5; i++) {
		EXPECT_EQ(test2.get(i), i + 1);
	}

	for (int i = 0; i < 5; i++) {
		test2.set(i, i + 2);
	}
	for (int i = 0; i < 5; i++) {
		EXPECT_EQ(test2.get(i), i + 2);
	}
}