// doubly_linked_list.cpp
#include "doubly_linked_list.hpp"
#include <iostream>

using biv::DoublyLinkedList;

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node* current = begin;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
    std::size_t count = 0;
    Node* current = begin;
    while (current != nullptr) {
        ++count;
        current = current->next;
    }
    return count;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
    Node* current = begin;
    while (current != nullptr) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
    Node* current = begin;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    Node* new_node = new Node(value);
    if (end == nullptr) {
        begin = end = new_node;
    } else {
        new_node->prev = end;
        end->next = new_node;
        end = new_node;
    }
}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
    Node* current = begin;
    while (current != nullptr) {
        if (current->value == value) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                begin = current->next;
            }

            if (current->next) {
                current->next->prev = current->prev;
            } else {
                end = current->prev;
            }

            delete current;
            return true;
        }
        current = current->next;
    }
    return false;
}
