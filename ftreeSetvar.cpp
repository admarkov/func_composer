//
// Created by admarkov on 17.05.17.
//

#include "ftree.h"
#include "mapping.h"

fNode* fNode::setvar(string var, fNode* f){
    int pos = 0;
    while (varlist[pos]!=var) pos++;
    vallist[pos] = f;
    return vallist[pos];
}