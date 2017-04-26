//
// Created by admarkov on 26.04.17.
//

#ifndef FUNC_COMPOSER_TREE_BUILDER_H
#define FUNC_COMPOSER_TREE_BUILDER_H

#include "ast.h"
#include "tokens.h"

Node* buildAST(TokenStream stream, Node* root = nullptr, Node* p = nullptr);

#endif //FUNC_COMPOSER_TREE_BUILDER_H
