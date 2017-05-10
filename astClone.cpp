//
// Created by admarkov on 09.05.17.
//

#include "mapping.h"

Node* Node::clone(Node* r, Node* p) {
    Node *n = new Node (p, NodeToItsCopy[root], type, data, nullptr, nullptr);
    NodeToItsCopy[this] = n;
    CopyToClonedNode[n] = this;
    if (n->root==nullptr) n->root = n;
    if (left!=nullptr) n->left = left->clone(r,n);
    if (right!=nullptr) n->right = right->clone(r,n);
    return n;
}