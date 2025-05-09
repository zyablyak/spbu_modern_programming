#include "menu_items.hpp"
#include "menu_functions.hpp"
#include <cstddef>

const IBusko::MenuItem IBusko::STUDY_SUMM = {
    "1 - хочу научиться складывать",
    IBusko::study_summ,
    &IBusko::STUDY,
    nullptr,
    0
};

const IBusko::MenuItem IBusko::STUDY_SUBSTRACT = {
    "2 - хочу научиться вычитать",
    IBusko::study_substract,
    &IBusko::STUDY,
    nullptr,
    0
};

const IBusko::MenuItem IBusko::STUDY_MULTIPLY = {
    "3 - хочу научиться умножать",
    IBusko::study_multiply,
    &IBusko::STUDY,
    nullptr,
    0
};

const IBusko::MenuItem IBusko::STUDY_DIVIDE = {
    "4 - хочу научиться делить",
    IBusko::study_divide,
    &IBusko::STUDY,
    nullptr,
    0
};

const IBusko::MenuItem IBusko::STUDY_GO_BACK = {
    "0 - выйти в главное меню",
    IBusko::study_go_back,
    &IBusko::STUDY,
    nullptr,
    0
};

namespace {
    const IBusko::MenuItem* const study_children[] = {
        &IBusko::STUDY_GO_BACK,
        &IBusko::STUDY_SUMM,
        &IBusko::STUDY_SUBSTRACT,
        &IBusko::STUDY_MULTIPLY,
        &IBusko::STUDY_DIVIDE
    };
    const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

const IBusko::MenuItem IBusko::STUDY = {
    "1 - хочу учиться математике",
    IBusko::show_menu,
    &IBusko::MAIN,
    study_children,
    study_size
};

const IBusko::MenuItem IBusko::EXIT = {
    "0 - лучше пойду полежу",
    IBusko::exit,
    &IBusko::MAIN,
    nullptr,
    0
};

namespace {
    const IBusko::MenuItem* const main_children[] = {
        &IBusko::EXIT,
        &IBusko::STUDY
    };
    const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const IBusko::MenuItem IBusko::MAIN = {
    nullptr,
    IBusko::show_menu,
    nullptr,
    main_children,
    main_size
};
