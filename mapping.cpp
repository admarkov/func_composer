//
// Created by admarkov on 09.05.17.
//

#include "mapping.h"

map<ast, ast> NodeToItsCopy;
map<ast, ast> CopyToClonedNode;
map<ast, functionTree> RootToFunction;
map<functionTree, ast> FunctionToRoot;
map<ast, ast> VarToVal;