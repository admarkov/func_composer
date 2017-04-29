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
    Node* clone(Node* r=nullptr, Node* p = nullptr) {
        Node *n = new Node (p, r, type, data, nullptr, nullptr);
        if (n->root==nullptr) n->root = n;
        if (left!=nullptr) n->left = left->clone(r,n);
        if (right!=nullptr) n->right = right->clone(r,n);
        return n;
    }
    Node (string c) : type("constant"), data(c) {}
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

    void setvar(Node* Root, Node *val, string varname) {
        if (left!=nullptr) {
            if (left->type=="variable") {
                if (left->data==varname && left->root==Root)
                    left = val->clone(Root, this);
            }
            else left->setvar(Root, val, varname);
        }
        if (right!=nullptr) {
            if (right->type=="variable") {
                if (right->data==varname && left->root==Root) right = val->clone(Root, this);
            }
            right->setvar(Root, val, varname);
        }
    }

    ~Node() {
        del();
    }
};

typedef Node* ast;

#endif //FUNC_COMPOSER_FTREE_H
