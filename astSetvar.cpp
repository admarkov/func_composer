//
// Created by admarkov on 09.05.17.
//

#include "mapping.h"
#include "ftree.h"
#include "mapping.h"

void Node::setvar(Node* Root, Node *val, string varname, fNode* func) {
    if (left!=nullptr) {
        if (left->type=="variable") {
            if (left->data==varname && left->root==Root) {
                string varname = left->data;
                left = left->hangTree(val);
                RootToFunction[left] = func->clone(RootToFunction[Root]);
                RootToFunction[Root]->setvar(varname, RootToFunction[left]);
                FunctionToRoot[RootToFunction[left]]=left;
            }
        }
        else left->setvar(Root, val, varname, func);
    }
    if (right!=nullptr) {
        if (right->type=="variable") {
            if (right->data==varname && right->root==Root) {
                string varname = right->data;
                right = right->hangTree(val);
                RootToFunction[right] = func->clone(RootToFunction[Root]);
                RootToFunction[Root]->setvar(varname, RootToFunction[right]);
                FunctionToRoot[RootToFunction[right]]=right;
            }
        }
        else right->setvar(Root, val, varname, func);
    }
}

