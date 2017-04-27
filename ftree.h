//
// Created by admarkov on 27.04.17.
//

#include <string>
#include <vector>
using namespace std;

class fNode {
    void push_var(string var) {
        varlist.push_back(var);
        vallist.push_back(nullptr);
    }
public:
    string type;
    string name;
    vector<string> varlist;
    vector<fNode*> vallist;
    fNode() {}
    fNode* clone(fNode* f) {
        type=f->type;
        name=f->name;
        for (string v: f->varlist) {
            push_var(v);
        }
    }
};