#ifndef TOKENS_LIST_H
#define TOKENS_LIST_H

#include "tokens.h"


namespace token_list {
    struct node {
        token::Token* token;
        node* next;
    };

    struct decriptor {
        node* first;
        node* last;
    };


}

#endif