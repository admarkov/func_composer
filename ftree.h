//
// Created by admarkov on 22.04.17.
//

#ifndef FUNC_COMPOSER_FTREE_H
#define FUNC_COMPOSER_FTREE_H

#include <string>

struct node {
    node *parent, *left, *right;
    std::string data;
    node(node* p = nullptr, std::string d="", node* l = nullptr, node* r = nullptr) : parent(p), data(d), left(l), right(r) {}
    virtual node* clone(node* p = nullptr) {
        node *n = new node (p, data, nullptr, nullptr);
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
    ~node() {
        del();
    }
};

struct var : node {
    std::string name;
    node *root;
    var(std::string n, node* r, node* p = nullptr) : name(n), root(r), node(p) {}
};

#endif //FUNC_COMPOSER_FTREE_H
