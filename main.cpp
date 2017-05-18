#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>
#include "tokens.h"
#include "ast.h"
#include "ftree.h"
#include "tree_builder.h"
#include "test.h"
#include "mapping.h"
using namespace std;

int main ()
{
    test();
    fstream input("input");
    fstream output("output");
    string e;
    getline(input, e);
    Node* Expr = buildAST(TokenStream(e));
    list<ast> fTreesList;
    list<functionTree> fList;
    string s;
    while (getline(input, s)) {
        string name="";
        string expr="";
        int pos=0;
        while (s[pos]!='(') name+=s[pos], pos++;
        fList.push_back(new fNode("function", name));
        pos++;
        while (s[pos]!=')') {
            string var="";
            while (s[pos]!=')' && s[pos]!=',') var+=s[pos], pos++;
            fList.back()->push_var(var);
            if (s[pos]==',') pos++;
        }
        pos+=2;
        while (pos<s.length()) expr+=s[pos], pos++;
        fTreesList.push_back(buildAST(TokenStream(expr)));
    }
    list<ast> states;

    list<fNode*>::iterator f=fList.begin();
    list<Node*>::iterator ftree=fTreesList.begin();
    for (; f!=fList.end(); f++, ftree++) {
        auto F = (*ftree);
        if (F->type=="variable" && (Expr->type=="variable" || Expr->type=="constant")) {
            states.push_back(F->clone());
            states.back() = states.back()->hangTree(new Node(Expr->data));
            fNode* clonedFunc = (*f)->clone();
            RootToFunction[states.back()]=clonedFunc;
            FunctionToRoot[clonedFunc]=states.back();
            RootToFunction[states.back()]->setvar(F->data, new fNode("constant", Expr->data));
        }
        else {
            if (F->type==Expr->type && F->data==Expr->data) {
                states.push_back(F->cloneTree());
                fNode* clonedFunc = (*f)->clone();
                RootToFunction[states.back()]=clonedFunc;
                FunctionToRoot[clonedFunc]=states.back();
            }
        }
    }

    map<Node*, bool> used;
    used[nullptr] = true;
    Node* pos = Expr;
    int it=1;
    while (pos != nullptr && states.size()>0) {
        used[pos] = true;
        list<Node*>::iterator tree = states.begin();
        int sz=states.size();
        while (sz--) {
            bool del = false;
            if (*tree == nullptr) {
                tree = states.erase(tree);
                del = true;
            }
            else {
                if ((*tree)->type != "variable") {
                    if ((*tree)->type != pos->type || (*tree)->data != pos->data) {
                        tree = states.erase(tree);
                        del = true;
                    }
                }
                else {
                    if (pos->type=="variable" || pos->type=="constant") {
                        (*tree)->root->setvar((*tree)->root, new Node("constant", pos->data), (*tree)->data, new fNode("constant", pos->data));
                    }
                    else {
                        f = fList.begin();
                        ftree = fTreesList.begin();
                        for (; f != fList.end(); f++, ftree++) {
                            if ((*ftree)->type!="variable") {
                                if (pos->type == (*ftree)->type && pos->data == (*ftree)->data) {
                                    (*tree)->cloneTree();
                                    Node *copy = NodeToItsCopy[(*tree)];

                                    fNode *F = RootToFunction[(*tree)->root];
                                    while (F->parent != nullptr) F = F->parent;
                                    F->clone();

                                    copy->root->setvar(copy->root, (*ftree), copy->data, *f);
                                    copy = NodeToItsCopy[(*tree)];
                                    states.push_back(copy);
                                }
                            }
                        }
                        tree = states.erase(tree);
                        del=true;
                    }
                }
            }
            if (!del) {
                tree++;
            }
        }

        if (!used[pos->left]) {
            for (Node* &n : states) {
                n = n->left;
            }
            pos = pos->left;
        }
        else if (!used[pos->right]) {
            for (Node* &n : states) {
                n = n->right;
            }
            pos = pos->right;
        }
        else {
            pos = pos->parent;
            if (pos!=nullptr)
                for (Node* &n : states) {
                    n = n->parent;
                }
        }


        cout<<it<<":\n";
        list<ast>::iterator state = states.begin();
        while (state!=states.end()) {
            fNode* f = RootToFunction[(*state)->root];
            while (f->parent!=nullptr) f=f->parent;
            f->print();
            cout<<endl;
            state++;
        }
        cout<<"--------------------------\n";
        it++;
    }
    list<Node*>::iterator tree = states.begin();
    bool found=false;
    while (tree!=states.end() && !found) {
        Node* t = (*tree);
        while (t->parent!=nullptr) t = t->parent;
        if (Node::equal(Expr, t)) {
            RootToFunction[t]->print(output);
            found=true;
        }
        tree++;
    }
    if (!found) output<<"Impossible";
}