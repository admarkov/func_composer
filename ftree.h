//
// Created by admarkov on 27.04.17.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class fNode {
public:
    string type;
    string name;
    vector<string> varlist;
    vector<fNode*> vallist;
    fNode() {}
    fNode(string t, string n): type(t), name(n) {};
    void push_var(string var) {
        varlist.push_back(var);
        vallist.push_back(nullptr);
    }
    fNode(fNode* f) {
        type=f->type;
        name=f->name;
        for (string v: f->varlist) {
            push_var(v);
        }
    }

    void setvar(string var, fNode* f) {
        int i=0;
        while (varlist[i]!=var) i++;
        vallist[i]=new fNode(f);
    }
    void print() {
        if (type=="function") {
            cout<<name<<"(";
            for (int i=0; i<varlist.size(); i++) {
                if (vallist[i]!=nullptr) vallist[i]->print();
                if (i!=vallist.size()-1) cout<<",";
            }
            cout<<")";
        }
        else {
            cout<<name;
        }
    }
    ~fNode() {
        for (fNode* f: vallist) {
            delete f;
        }
    }
};

typedef fNode* functionTree;