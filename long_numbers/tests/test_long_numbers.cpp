#include <gtest/gtest.h>
#include "main.hpp"

using biv::LongNumber;

// Тесты для операций сравнения
TEST(Comparisons, Equal) {
    EXPECT_TRUE(LongNumber("123") == LongNumber("123"));
    EXPECT_FALSE(LongNumber("123") == LongNumber("-123"));
    EXPECT_FALSE(LongNumber("123") == LongNumber("1234"));
}

TEST(Comparisons, NotEqual) {
    EXPECT_TRUE(LongNumber("123") != LongNumber("-123"));
    EXPECT_FALSE(LongNumber("123") != LongNumber("123"));
}

TEST(Comparisons, Greater) {
    EXPECT_TRUE(LongNumber("1000") > LongNumber("999"));
    EXPECT_FALSE(LongNumber("999") > LongNumber("1000"));
    EXPECT_TRUE(LongNumber("-999") > LongNumber("-1000"));
}

TEST(Comparisons, Less) {
    EXPECT_TRUE(LongNumber("999") < LongNumber("1000"));
    EXPECT_FALSE(LongNumber("1000") < LongNumber("999"));
    EXPECT_TRUE(LongNumber("-1000") < LongNumber("-999"));
}

TEST(Comparisons, GreaterOrEqual) {
    EXPECT_TRUE(LongNumber("1000") >= LongNumber("999"));
    EXPECT_TRUE(LongNumber("1000") >= LongNumber("1000"));
    EXPECT_FALSE(LongNumber("999") >= LongNumber("1000"));
}

TEST(Comparisons, LessOrEqual) {
    EXPECT_TRUE(LongNumber("999") <= LongNumber("1000"));
    EXPECT_TRUE(LongNumber("1000") <= LongNumber("1000"));
    EXPECT_FALSE(LongNumber("1000") <= LongNumber("999"));
}

// Тесты для арифметических операций
TEST(Arithmetic, Addition) {
    EXPECT_EQ(LongNumber("999") + LongNumber("1"), LongNumber("1000"));
    EXPECT_EQ(LongNumber("-999") + LongNumber("-1"), LongNumber("-1000"));
    EXPECT_EQ(LongNumber("999") + LongNumber("-1"), LongNumber("998"));
}

TEST(Arithmetic, Subtraction) {
    EXPECT_EQ(LongNumber("1000") - LongNumber("1"), LongNumber("999"));
    EXPECT_EQ(LongNumber("-1000") - LongNumber("-1"), LongNumber("-999"));
    EXPECT_EQ(LongNumber("999") - LongNumber("-1"), LongNumber("1000"));
}

TEST(Arithmetic, Multiplication) {
    EXPECT_EQ(LongNumber("123") * LongNumber("2"), LongNumber("246"));
    EXPECT_EQ(LongNumber("123") * LongNumber("-2"), LongNumber("-246"));
    EXPECT_EQ(LongNumber("0") * LongNumber("123"), LongNumber("0"));
}

TEST(Arithmetic, Division) {
    EXPECT_EQ(LongNumber("100") / LongNumber("10"), LongNumber("10"));
    EXPECT_EQ(LongNumber("100") / LongNumber("-10"), LongNumber("-10"));
    EXPECT_EQ(LongNumber("-100") / LongNumber("10"), LongNumber("-10"));
    EXPECT_EQ(LongNumber("-100") / LongNumber("-10"), LongNumber("10"));
}

TEST(Arithmetic, Modulo) {
    // Положительные числа
    EXPECT_EQ(LongNumber("10") % LongNumber("3"), LongNumber("1"));
    EXPECT_EQ(LongNumber("10") % LongNumber("-3"), LongNumber("-2"));
    EXPECT_EQ(LongNumber("-10") % LongNumber("3"), LongNumber("2"));
    EXPECT_EQ(LongNumber("-10") % LongNumber("-3"), LongNumber("-1"));

    // Крайние случаи
    EXPECT_EQ(LongNumber("5") % LongNumber("5"), LongNumber("0"));
    EXPECT_EQ(LongNumber("0") % LongNumber("5"), LongNumber("0"));
    EXPECT_EQ(LongNumber("3") % LongNumber("7"), LongNumber("3"));
}

TEST(Arithmetic, EdgeCases) {
    // Деление на 1
    EXPECT_EQ(LongNumber("123456789") / LongNumber("1"), LongNumber("123456789"));

    // Деление числа на само себя
    EXPECT_EQ(LongNumber("123456789") / LongNumber("123456789"), LongNumber("1"));

    // Остаток от деления на 1
    EXPECT_EQ(LongNumber("123456789") % LongNumber("1"), LongNumber("0"));

    // Умножение на 0
    EXPECT_EQ(LongNumber("123456789") * LongNumber("0"), LongNumber("0"));
}

TEST(Arithmetic, LargeNumbers) {
    // Проверка работы с большими числами
    LongNumber big1("12345678901234567890");
    LongNumber big2("98765432109876543210");

    EXPECT_EQ(big1 + big2, LongNumber("111111111011111111100"));
    EXPECT_EQ(big2 - big1, LongNumber("86419753208641975320"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
