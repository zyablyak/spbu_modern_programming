// test_doubly_linked_list.cpp
#include <gtest/gtest.h>
#include "doubly_linked_list.hpp"
#include <string>

using biv::DoublyLinkedList;

class DoublyLinkedListTest : public ::testing::Test {
protected:
    DoublyLinkedList<int> int_list;
    DoublyLinkedList<std::string> str_list;

    void SetUp() override {
        int_list.push_back(1);
        int_list.push_back(2);
        int_list.push_back(3);

        str_list.push_back("hello");
        str_list.push_back("world");
    }
};

TEST_F(DoublyLinkedListTest, InitialSize) {
    DoublyLinkedList<int> list;
    ASSERT_EQ(list.get_size(), 0);
}

TEST_F(DoublyLinkedListTest, PushBack) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    ASSERT_EQ(list.get_size(), 1);
    list.push_back(20);
    ASSERT_EQ(list.get_size(), 2);
}

TEST_F(DoublyLinkedListTest, HasItem) {
    ASSERT_TRUE(int_list.has_item(2));
    ASSERT_FALSE(int_list.has_item(5));

    ASSERT_TRUE(str_list.has_item("hello"));
    ASSERT_FALSE(str_list.has_item("test"));
}

TEST_F(DoublyLinkedListTest, RemoveFirst) {
    ASSERT_TRUE(int_list.remove_first(2));
    ASSERT_EQ(int_list.get_size(), 2);
    ASSERT_FALSE(int_list.has_item(2));

    ASSERT_FALSE(int_list.remove_first(5));
}

TEST_F(DoublyLinkedListTest, RemoveFirstFromEmpty) {
    DoublyLinkedList<int> empty_list;
    ASSERT_FALSE(empty_list.remove_first(1));
}

TEST_F(DoublyLinkedListTest, RemoveFirstLastElement) {
    DoublyLinkedList<int> list;
    list.push_back(42);
    ASSERT_TRUE(list.remove_first(42));
    ASSERT_EQ(list.get_size(), 0);
}

TEST_F(DoublyLinkedListTest, StringOperations) {
    ASSERT_TRUE(str_list.remove_first("hello"));
    ASSERT_EQ(str_list.get_size(), 1);
    ASSERT_FALSE(str_list.has_item("hello"));
}

TEST_F(DoublyLinkedListTest, Destruction) {
    {
        DoublyLinkedList<int> temp_list;
        temp_list.push_back(1);
        temp_list.push_back(2);
    } // Проверка, что деструктор корректно очищает память
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
