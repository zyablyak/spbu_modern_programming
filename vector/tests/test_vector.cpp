#include "vector.hpp"
#include <gtest/gtest.h>
#include <string>

using biv::Vector;

class VectorTest : public ::testing::Test {
protected:
	Vector<int> int_vec;
	Vector<std::string> str_vec;

	void SetUp() override {
		int_vec.push_back(1);
		int_vec.push_back(2);
		int_vec.push_back(3);

		str_vec.push_back("hello");
		str_vec.push_back("world");
	}
};

TEST_F(VectorTest, InitialSize) {
	Vector<int> v;
	ASSERT_EQ(v.get_size(), 0);
}

TEST_F(VectorTest, PushBack) {
	Vector<int> v;
	v.push_back(10);
	ASSERT_EQ(v.get_size(), 1);
	v.push_back(20);
	ASSERT_EQ(v.get_size(), 2);
}

TEST_F(VectorTest, HasItem) {
	ASSERT_TRUE(int_vec.has_item(2));
	ASSERT_FALSE(int_vec.has_item(5));

	ASSERT_TRUE(str_vec.has_item("hello"));
	ASSERT_FALSE(str_vec.has_item("test"));
}

TEST_F(VectorTest, Insert) {
	ASSERT_TRUE(int_vec.insert(1, 5));
	ASSERT_EQ(int_vec.get_size(), 4);
	ASSERT_TRUE(int_vec.has_item(5));

	ASSERT_FALSE(int_vec.insert(10, 5));
}

TEST_F(VectorTest, RemoveFirst) {
	ASSERT_TRUE(int_vec.remove_first(2));
	ASSERT_EQ(int_vec.get_size(), 2);
	ASSERT_FALSE(int_vec.has_item(2));

	ASSERT_FALSE(int_vec.remove_first(5));
}

TEST_F(VectorTest, CapacityExpansion) {
	Vector<int> v;
	for (int i = 0; i < 15; ++i) {
		v.push_back(i);
	}
	ASSERT_EQ(v.get_size(), 15);
	ASSERT_TRUE(v.has_item(10));
}

TEST_F(VectorTest, InsertAtEnd) {
	ASSERT_TRUE(int_vec.insert(3, 4));
	ASSERT_EQ(int_vec.get_size(), 4);
	ASSERT_TRUE(int_vec.has_item(4));
}

TEST_F(VectorTest, RemoveNonExisting) {
	ASSERT_FALSE(str_vec.remove_first("test"));
	ASSERT_EQ(str_vec.get_size(), 2);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
