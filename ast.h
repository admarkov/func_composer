//
// Created by admarkov on 22.04.17.
//

#ifndef FUNC_COMPOSER_AST_H
#define FUNC_COMPOSER_AST_H

#include <string>
#include "tokens.h"
#include "ftree.h"

struct Node {
    Node *parent, *left, *right;
    Node *root;
    string type;
    std::string data;
    Node(Node* p = nullptr, Node* rt=nullptr, string t="", std::string d="", Node* l = nullptr, Node* r = nullptr) : parent(p), type(t), root(rt), data(d), left(l), right(r) {}

    Node(string t, string d, Node*p = nullptr) : parent(p), left(nullptr), right(nullptr), root(nullptr), type(t), data(d) {}

    Node* clone(Node* r=nullptr, Node* p = nullptr);

    Node* cloneSubtree(Node* Root=nullptr);

    Node* cloneTree(bool Rooted = false) {
        Node* n = this;
        while (n->parent!=nullptr) n = n->parent;
		if (Rooted) return n->cloneSubtree(n);
		else return n->cloneSubtree();
    }

    Node* hangTree(Node* Tree);

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

    void setvar(Node* Root, Node *val, string varname, fNode* func);

    static bool equal(Node* a, Node* b) {
        if (a->type!=b->type && !(a->type=="variable" && b->type=="constant" || b->type=="variable" && a->type=="constant")) return false;
        if (a->data!=b->data) return false;
        if (a->left==nullptr && b->left!=nullptr) return false;
        if (a->left!=nullptr && b->left==nullptr) return false;
        if (a->right==nullptr && b->right!=nullptr) return false;
        if (a->right!=nullptr && b->right==nullptr) return false;
        bool res=1;
        if (a->left!=nullptr) res*=equal(a->left, b->left);
        if (res && a->right!=nullptr) res*=equal(a->right, b->right);
        return res;
    }

    ~Node() {
        del();
    }
};

typedef Node* ast;

#endif //FUNC_COMPOSER_AST_H
