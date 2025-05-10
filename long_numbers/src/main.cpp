#include "main.hpp"
#include <cstring>
#include <algorithm>
#include <stdexcept>

using biv::LongNumber;

namespace {
    void remove_leading_zeros(int* &numbers, int &length) {
        int leading_zeros = 0;
        while (leading_zeros < length - 1 && numbers[leading_zeros] == 0) {
            leading_zeros++;
        }

        if (leading_zeros > 0) {
            int new_length = length - leading_zeros;
            int* new_numbers = new int[new_length];
            std::copy(numbers + leading_zeros, numbers + length, new_numbers);
            delete[] numbers;
            numbers = new_numbers;
            length = new_length;
        }
    }

    bool is_absolute_less(const int* num1, int len1, const int* num2, int len2) {
        if (len1 != len2) {
            return len1 < len2;
        }

        for (int i = 0; i < len1; ++i) {
            if (num1[i] != num2[i]) {
                return num1[i] < num2[i];
            }
        }
        return false;
    }

    bool is_absolute_equal(const int* num1, int len1, const int* num2, int len2) {
        if (len1 != len2) {
            return false;
        }

        for (int i = 0; i < len1; ++i) {
            if (num1[i] != num2[i]) {
                return false;
            }
        }
        return true;
    }
}

LongNumber::LongNumber() : numbers(new int[1]{0}), length(1), sign(1) {}

LongNumber::LongNumber(const char* const str) {
    if (str == nullptr) {
        throw std::invalid_argument("Null pointer passed to constructor");
    }

    int str_len = strlen(str);
    if (str_len == 0) {
        numbers = new int[1]{0};
        length = 1;
        sign = 1;
        return;
    }

    int start = 0;
    if (str[0] == '-') {
        sign = -1;
        start = 1;
    } else if (str[0] == '+') {
        sign = 1;
        start = 1;
    } else {
        sign = 1;
    }

    int num_length = str_len - start;
    if (num_length == 0) {
        numbers = new int[1]{0};
        length = 1;
        sign = 1;
        return;
    }

    numbers = new int[num_length];
    length = num_length;

    for (int i = start; i < str_len; ++i) {
        if (str[i] < '0' || str[i] > '9') {
            delete[] numbers;
            throw std::invalid_argument("Invalid character in number string");
        }
        numbers[i - start] = str[i] - '0';
    }

    remove_leading_zeros(numbers, length);
    if (length == 1 && numbers[0] == 0) {
        sign = 1;
    }
}

LongNumber::LongNumber(const LongNumber& x) : numbers(new int[x.length]), length(x.length), sign(x.sign) {
    std::copy(x.numbers, x.numbers + x.length, numbers);
}

LongNumber::LongNumber(LongNumber&& x) : numbers(x.numbers), length(x.length), sign(x.sign) {
    x.numbers = nullptr;
    x.length = 0;
    x.sign = 1;
}

LongNumber::~LongNumber() {
    delete[] numbers;
}

LongNumber& LongNumber::operator=(const char* const str) {
    LongNumber temp(str);
    *this = std::move(temp);
    return *this;
}

LongNumber& LongNumber::operator=(const LongNumber& x) {
    if (this != &x) {
        int* new_numbers = new int[x.length];
        delete[] numbers;
        numbers = new_numbers;
        length = x.length;
        sign = x.sign;
        std::copy(x.numbers, x.numbers + x.length, numbers);
    }
    return *this;
}

LongNumber& LongNumber::operator=(LongNumber&& x) {
    if (this != &x) {
        delete[] numbers;
        numbers = x.numbers;
        length = x.length;
        sign = x.sign;
        x.numbers = nullptr;
        x.length = 0;
        x.sign = 1;
    }
    return *this;
}

bool LongNumber::operator==(const LongNumber& x) const {
    if (sign != x.sign) return false;
    return is_absolute_equal(numbers, length, x.numbers, x.length);
}

bool LongNumber::operator!=(const LongNumber& x) const {
    return !(*this == x);
}

bool LongNumber::operator>(const LongNumber& x) const {
    if (sign != x.sign) {
        return sign > x.sign;
    }

    bool absolute_less = is_absolute_less(numbers, length, x.numbers, x.length);
    bool absolute_equal = is_absolute_equal(numbers, length, x.numbers, x.length);

    if (sign == 1) {
        return !absolute_less && !absolute_equal;
    } else {
        return absolute_less;
    }
}

bool LongNumber::operator<(const LongNumber& x) const {
    if (sign != x.sign) {
        return sign < x.sign;
    }

    bool absolute_less = is_absolute_less(numbers, length, x.numbers, x.length);
    bool absolute_equal = is_absolute_equal(numbers, length, x.numbers, x.length);

    if (sign == 1) {
        return absolute_less;
    } else {
        return !absolute_less && !absolute_equal;
    }
}

bool LongNumber::operator>=(const LongNumber& x) const {
    return !(*this < x);
}

bool LongNumber::operator<=(const LongNumber& x) const {
    return !(*this > x);
}

LongNumber LongNumber::operator-() const {
    LongNumber result(*this);
    if (result.length != 1 || result.numbers[0] != 0) {
        result.sign *= -1;
    }
    return result;
}

LongNumber LongNumber::operator+(const LongNumber& x) const {
    if (sign != x.sign) {
        return *this - (-x);
    }

    int max_len = std::max(length, x.length) + 1;
    int* result = new int[max_len]{0};

    int carry = 0;
    int i = length - 1;
    int j = x.length - 1;
    int k = max_len - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 = (i >= 0) ? numbers[i--] : 0;
        int digit2 = (j >= 0) ? x.numbers[j--] : 0;
        int sum = digit1 + digit2 + carry;
        result[k--] = sum % 10;
        carry = sum / 10;
    }

    int result_length = max_len - (k + 1);
    int* final_result = new int[result_length];
    std::copy(result + k + 1, result + max_len, final_result);
    delete[] result;

    LongNumber sum;
    delete[] sum.numbers;
    sum.numbers = final_result;
    sum.length = result_length;
    sum.sign = sign;

    remove_leading_zeros(sum.numbers, sum.length);
    if (sum.length == 1 && sum.numbers[0] == 0) {
        sum.sign = 1;
    }

    return sum;
}

LongNumber LongNumber::operator-(const LongNumber& x) const {
    if (sign != x.sign) {
        return *this + (-x);
    }

    if (is_absolute_equal(numbers, length, x.numbers, x.length)) {
        return LongNumber("0");
    }

    bool absolute_less = is_absolute_less(numbers, length, x.numbers, x.length);
    const LongNumber* larger = absolute_less ? &x : this;
    const LongNumber* smaller = absolute_less ? this : &x;

    int max_len = larger->length;
    int* result = new int[max_len]{0};

    int borrow = 0;
    int i = larger->length - 1;
    int j = smaller->length - 1;
    int k = max_len - 1;

    while (i >= 0 || j >= 0) {
        int digit1 = (i >= 0) ? larger->numbers[i--] : 0;
        int digit2 = (j >= 0) ? smaller->numbers[j--] : 0;
        int diff = digit1 - digit2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result[k--] = diff;
    }

    int result_length = max_len - (k + 1);
    int* final_result = new int[result_length];
    std::copy(result + k + 1, result + max_len, final_result);
    delete[] result;

    LongNumber difference;
    delete[] difference.numbers;
    difference.numbers = final_result;
    difference.length = result_length;
    difference.sign = absolute_less ? -sign : sign;

    remove_leading_zeros(difference.numbers, difference.length);
    if (difference.length == 1 && difference.numbers[0] == 0) {
        difference.sign = 1;
    }

    return difference;
}

LongNumber LongNumber::operator*(const LongNumber& x) const {
    if ((length == 1 && numbers[0] == 0) || (x.length == 1 && x.numbers[0] == 0)) {
        return LongNumber("0");
    }

    int result_length = length + x.length;
    int* result = new int[result_length]{0};

    for (int i = length - 1; i >= 0; --i) {
        for (int j = x.length - 1; j >= 0; --j) {
            int product = numbers[i] * x.numbers[j];
            int sum = product + result[i + j + 1];

            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    remove_leading_zeros(result, result_length);

    LongNumber product;
    delete[] product.numbers;
    product.numbers = result;
    product.length = result_length;
    product.sign = sign * x.sign;

    return product;
}

LongNumber LongNumber::operator/(const LongNumber& x) const {
    if (x.length == 1 && x.numbers[0] == 0) {
        throw std::runtime_error("Division by zero");
    }

    if (is_absolute_less(numbers, length, x.numbers, x.length)) {
        return LongNumber("0");
    }

    LongNumber dividend(*this);
    dividend.sign = 1;
    LongNumber divisor(x);
    divisor.sign = 1;

    LongNumber quotient("0");
    LongNumber one("1");

    while (!is_absolute_less(dividend.numbers, dividend.length, divisor.numbers, divisor.length)) {
        LongNumber temp_divisor = divisor;
        LongNumber multiple("1");

        LongNumber temp = temp_divisor * LongNumber("10");
        while (!is_absolute_less(dividend.numbers, dividend.length, temp.numbers, temp.length)) {
            temp_divisor = temp;
            multiple = multiple * LongNumber("10");
            temp = temp_divisor * LongNumber("10");
        }

        while (!is_absolute_less(dividend.numbers, dividend.length, temp_divisor.numbers, temp_divisor.length)) {
            dividend = dividend - temp_divisor;
            quotient = quotient + multiple;
        }
    }

    quotient.sign = sign * x.sign;

    // Корректировка для отрицательных результатов (округление вниз)
    if (sign * x.sign == -1 && !(dividend.length == 1 && dividend.numbers[0] == 0)) {
        quotient = quotient - one;
    }

    if (quotient.length == 1 && quotient.numbers[0] == 0) {
        quotient.sign = 1;
    }

    return quotient;
}

LongNumber LongNumber::operator%(const LongNumber& x) const {
    if (x.length == 1 && x.numbers[0] == 0) {
        throw std::runtime_error("Division by zero");
    }

    // Вычисляем частное с округлением вниз
    LongNumber quotient = *this / x;

    // Вычисляем remainder = this - (quotient * x)
    LongNumber remainder = *this - (quotient * x);

    // Корректировка для отрицательных случаев
    if (remainder != LongNumber("0")) {
        if (x.is_negative() != remainder.is_negative()) {
            remainder = remainder + x;
        }
    }

    // Ноль всегда положительный
    if (remainder.length == 1 && remainder.numbers[0] == 0) {
        remainder.sign = 1;
    }

    return remainder;
}

int LongNumber::get_digits_number() const noexcept {
    return length;
}

int LongNumber::get_rank_number(const int rank) const {
    if (rank < 0 || rank >= length) {
        throw std::out_of_range("Invalid rank requested");
    }
    return numbers[rank];
}

bool LongNumber::is_negative() const noexcept {
    return sign == -1;
}

int LongNumber::get_length(const char* const str) const noexcept {
    return str ? strlen(str) : 0;
}

namespace biv {
    std::ostream& operator<<(std::ostream &os, const LongNumber& x) {
        if (x.is_negative()) {
            os << '-';
        }
        for (int i = 0; i < x.length; ++i) {
            os << x.numbers[i];
        }
        return os;
    }
}
