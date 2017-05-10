//
// Created by admarkov on 09.05.17.
//

#include "mapping.h"

void Node::setvar(Node* Root, Node *val, string varname) {
    if (left!=nullptr) {
        if (left->type=="variable") {
            if (left->data==varname && left->root==Root) {
                Node* v = val->clone(Root, this);
                VarToVal[left]=v;
                left = v;
            }
        }
        else left->setvar(Root, val, varname);
    }
    if (right!=nullptr) {
        if (right->type=="variable") {
            if (right->data==varname && left->root==Root) {
                Node* v = val->clone(Root, this);
                VarToVal[right] = v;
                right = v;
            }
        }
        right->setvar(Root, val, varname);
    }
}