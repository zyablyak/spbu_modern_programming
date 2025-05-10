#include "vector.hpp"
#include <iostream>
#include <stdexcept>

using biv::Vector;

template<typename T>
const std::size_t Vector<T>::START_CAPACITY = 10;

template<typename T>
Vector<T>::Vector() : capacity(START_CAPACITY), size(0) {
	arr = new T[START_CAPACITY];
}

template<typename T>
Vector<T>::~Vector() {
	delete[] arr;
	arr = nullptr;
	size = 0;
	capacity = START_CAPACITY;
}

template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
	return size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
	for (std::size_t i = 0; i < size; ++i) {
		if (arr[i] == value) {
			return true;
		}
	}
	return false;
}

template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
	if (position > size) {
		return false;
	}

	if (size == capacity) {
		capacity *= 2;
		T* new_arr = new T[capacity];
		for (std::size_t i = 0; i < position; ++i) {
			new_arr[i] = arr[i];
		}
		new_arr[position] = value;
		for (std::size_t i = position; i < size; ++i) {
			new_arr[i + 1] = arr[i];
		}
		delete[] arr;
		arr = new_arr;
	} else {
		for (std::size_t i = size; i > position; --i) {
			arr[i] = arr[i - 1];
		}
		arr[position] = value;
	}
	++size;
	return true;
}

template<typename T>
void Vector<T>::print() const noexcept {
	for (std::size_t i = 0; i < size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
	if (size == capacity) {
		capacity *= 2;
		T* new_arr = new T[capacity];
		for (std::size_t i = 0; i < size; ++i) {
			new_arr[i] = arr[i];
		}
		delete[] arr;
		arr = new_arr;
	}
	arr[size++] = value;
}

template<typename T>
bool Vector<T>::remove_first(const T& value) {
	for (std::size_t i = 0; i < size; ++i) {
		if (arr[i] == value) {
			for (std::size_t j = i; j < size - 1; ++j) {
				arr[j] = arr[j + 1];
			}

			--size;

			if (size <= capacity / 4 && capacity > START_CAPACITY) {
				capacity /= 2;
				T* new_arr = new T[capacity];
				for (std::size_t k = 0; k < size; ++k) {
					new_arr[k] = arr[k];
				}
				delete[] arr;
				arr = new_arr;
			}

			return true;
		}
	}
	return false;
}
