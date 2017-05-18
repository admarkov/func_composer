//
// Created by admarkov on 17.05.17.
//

#include "ast.h"
#include "mapping.h"

Node* Node::cloneSubtree(Node* Root) {
    Node* copy = new Node(type, data);
    NodeToItsCopy[this] = copy;
    CopyToClonedNode[copy] = this;
    if (parent!=nullptr) copy->parent = NodeToItsCopy[parent];
    if (Root==nullptr) copy->root = NodeToItsCopy[root];
    else copy->root = Root;
    if (left!=nullptr) copy->left = left->cloneSubtree();
    if (right!=nullptr) copy->right = right->cloneSubtree();
    return copy;
}