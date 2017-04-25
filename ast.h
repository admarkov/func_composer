//
// Created by admarkov on 22.04.17.
//

#ifndef FUNC_COMPOSER_FTREE_H
#define FUNC_COMPOSER_FTREE_H

#include <string>
#include "tokens.h"

struct Node {
    Node *parent, *left, *right;
    std::string data;
    Node(Node* p = nullptr, std::string d="", Node* l = nullptr, Node* r = nullptr) : parent(p), data(d), left(l), right(r) {}
    virtual Node* clone(Node* p = nullptr) {
        Node *n = new Node (p, data, nullptr, nullptr);
        n->left = left->clone(n);
        n->right = right->clone(n);
        return n;
    }
    virtual void del () {
        if (left!=nullptr) left->del();
        if (right!=nullptr) right->del();
        delete left;
        delete right;
    }
    ~Node() {
        del();
    }
};

struct var : Node {
    std::string name;
    Node *root;
    var(std::string n, Node* r, Node* p = nullptr) : name(n), root(r), Node(p) {}
};

#endif //FUNC_COMPOSER_FTREE_H
