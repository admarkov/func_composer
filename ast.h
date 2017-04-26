//
// Created by admarkov on 22.04.17.
//

#ifndef FUNC_COMPOSER_FTREE_H
#define FUNC_COMPOSER_FTREE_H

#include <string>
#include "tokens.h"

struct Node {
    Node *parent, *left, *right;
    Node *root;
    string type;
    std::string data;
    Node(Node* p = nullptr, Node* rt=nullptr, string t="", std::string d="", Node* l = nullptr, Node* r = nullptr) : parent(p), type(t), root(rt), data(d), left(l), right(r) {}
    Node* clone(Node* r, Node* p = nullptr) {
        Node *n = new Node (p, r, type, data, nullptr, nullptr);
        if (left!=nullptr) n->left = left->clone(n);
        if (right!=nullptr) n->right = right->clone(n);
        return n;
    }
    void del () {
        if (left!=nullptr) left->del();
        if (right!=nullptr) right->del();
        delete left;
        delete right;
    }
    static void print(Node *r, int offset = 0)
    {
        if(r==nullptr) return;
        print(r->right, offset+3);
        for(int i = 0; i<offset; i++)
            cout<<' ';
        cout<<r->data<<endl;
        print(r->left, offset+3);
    }

    Node* setvar(Node* root, Node *val, string varname, Node* p) {
        if (type=="variable") {
            if (data==varname && root==root) {
                Node* n = clone(val);
                n->parent = p;
                return n;
            }
        }
        else {
            if (left!=nullptr) left->setvar(root, val, varname, this);
            if (right!=nullptr) right->setvar(root, val, varname, this);
            return this;
        }
    }

    ~Node() {
        del();
    }
};

#endif //FUNC_COMPOSER_FTREE_H
