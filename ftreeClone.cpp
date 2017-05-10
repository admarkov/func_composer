//
// Created by admarkov on 09.05.17.
//

#include "mapping.h"

fNode* fNode::clone(fNode* p) {
    fNode* f = new fNode(type, name, p);
    for (string v: varlist) {
        f->varlist.push_back(v);
    }
    for (fNode* val: vallist) {
        if (val==nullptr) f->vallist.push_back(nullptr);
        else f->vallist.push_back(val->clone(f));
    }
    FunctionToRoot[f] = NodeToItsCopy[FunctionToRoot[this]];
    RootToFunction[NodeToItsCopy[FunctionToRoot[this]]] = f;
    return f;
}