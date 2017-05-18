//
// Created by admarkov on 17.05.17.
//

#include "ast.h"
#include "mapping.h"

Node* Node::hangTree(Node* Tree) {
    Node* r = Tree->cloneTree(r);
    r->root = r;
    r->parent = parent;
    if (parent!=nullptr) {
        if (parent->left==this) parent->left = r;
        else parent->right = r;
    }
    CopyToClonedNode[r] = CopyToClonedNode[this];
    NodeToItsCopy[CopyToClonedNode[this]] = r;
    return r;
}