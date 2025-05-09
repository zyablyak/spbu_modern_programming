#include "menu_functions.hpp"
#include "menu.hpp"
#include <iostream>
#include <cstdlib>

const IBusko::MenuItem* IBusko::show_menu(const MenuItem* current) {
    std::cout << "обучайка приветствует тебя" << std::endl;
    for (int i = 0; i < current->children_count; i++) {
        std::cout << current->children[i]->title << std::endl;
    }
    std::cout << "обучайка > ";

    int user_input;
    std::cin >> user_input;
    std::cout << std::endl;

    return current->children[user_input];
}

const IBusko::MenuItem* IBusko::exit(const MenuItem* current) {
    std::exit(0);
    return nullptr;
}

const IBusko::MenuItem* IBusko::study_summ(const MenuItem* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->parent;
}

const IBusko::MenuItem* IBusko::study_substract(const MenuItem* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->parent;
}

const IBusko::MenuItem* IBusko::study_multiply(const MenuItem* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->parent;
}

const IBusko::MenuItem* IBusko::study_divide(const MenuItem* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->parent;
}

const IBusko::MenuItem* IBusko::study_go_back(const MenuItem* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->parent->parent;
}
