//
// Created by admarkov on 09.05.17.
//

#ifndef FUNC_COMPOSER_MAPPING_H
#define FUNC_COMPOSER_MAPPING_H

#include <map>
#include "ast.h"
#include "ftree.h"

extern map<ast, ast> NodeToItsCopy;
extern map<ast, ast> CopyToClonedNode;
extern map<ast, functionTree> RootToFunction;
extern map<functionTree, ast> FunctionToRoot;
extern map<ast, ast> VarToVal;

#endif //FUNC_COMPOSER_MAPPING_H
