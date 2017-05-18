//
// Created by admarkov on 27.04.17.
//

#ifndef FUNC_COMPOSER_FTREE_H
#define FUNC_COMPOSER_FTREE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class fNode {
public:
    string type;
    string name;
    fNode* parent;
    vector<string> varlist;
    vector<fNode*> vallist;
    fNode() {}
    fNode(string t, string n, fNode* p=nullptr): type(t), name(n), parent(p) {};
    void push_var(string var) {
        varlist.push_back(var);
        vallist.push_back(nullptr);
    }

    fNode* clone(fNode* p = nullptr);

    fNode* setvar(string var, fNode* f);
    void print(ostream &out = cout) {
        if (type=="function") {
            out<<name<<"(";
            for (int i=0; i<varlist.size(); i++) {
                if (vallist[i]!=nullptr) vallist[i]->print(out);
                if (i!=vallist.size()-1) out<<",";
            }
            out<<")";
        }
        else {
            out<<name;
        }
    }
    ~fNode() {
        for (fNode* f: vallist) {
            delete f;
        }
    }
};

typedef fNode* functionTree;

#endif //FUNC_COMPOSER_FTREE_H