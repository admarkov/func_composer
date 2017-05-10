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
    list<ast> statesTrees;
    list<functionTree> statesFunctions;

    list<fNode*>::iterator f=fList.begin();
    list<Node*>::iterator ftree=fTreesList.begin();
    for (; f!=fList.end(); f++, ftree++) {
        auto F = (*ftree);
        if (F->type=="variable" && (Expr->type=="variable" || Expr->type=="constant")) {
            statesTrees.push_back(F->clone());
            statesFunctions.push_back((*f)->clone());
            RootToFunction[statesTrees.back()]=statesFunctions.back();
            FunctionToRoot[statesFunctions.back()]=statesTrees.back();
            statesTrees.back()->setvar(statesTrees.back(), new Node(Expr->data), F->data);
            statesFunctions.back()->setvar(F->data, new fNode("constant", Expr->data));

        }
        else {
            if (F->type==Expr->type && F->data==Expr->data) {
                statesTrees.push_back(F->clone());
                statesFunctions.push_back((*f)->clone());
                RootToFunction[statesTrees.back()]=statesFunctions.back();
                FunctionToRoot[statesFunctions.back()]=statesTrees.back();
            }
        }
    }

    map<Node*, bool> used;
    used[nullptr] = true;
    Node*pos = Expr;
    int it=1;
    while (pos != nullptr && statesTrees.size()>0) {
        used[pos] = true;
        list<Node*>::iterator tree = statesTrees.begin();
        list<fNode*>::iterator func = statesFunctions.begin();
        int sz=statesTrees.size();
        while (sz--) {
            bool del = false;
            if (*tree == nullptr) {
                tree = statesTrees.erase(tree);
                func = statesFunctions.erase(func);
                del = true;
            }
            else {
                if ((*tree)->type != "variable") {
                    if ((*tree)->type != pos->type || (*tree)->data != pos->data) {
                        tree = statesTrees.erase(tree);
                        func = statesFunctions.erase(func);
                        del = true;
                    }
                }
                else {
                    f = fList.begin();
                    ftree = fTreesList.begin();
                    for (; f != fList.end(); f++, ftree++) {
                        /*if ((*ftree)->type == "variable") {
                            if (pos->type == "constant" || pos->type == "variable") {
                                (*tree)->root->setvar((*tree)->root, pos, (*tree)->data);
                                (*ftree)
                            }
                        }
                        else {*/
                            if (pos->type==(*ftree)->type && pos->data==(*ftree)->data) {
                                Node* c = (*tree);
                                while (c->parent!=nullptr) c = c->parent;
                                c->clone();
                                Node* ClonedTree = NodeToItsCopy[(*tree)];
                                statesTrees.push_back(ClonedTree);
                                fNode* cf = (*func);
                                while (cf->parent!=nullptr) cf=cf->parent;
                                cf->clone();
                                ClonedTree->setvar(ClonedTree->root, (*ftree), ClonedTree->data);

                                fNode* dbg = RootToFunction[ClonedTree->root];
                                dbg->setvar(ClonedTree->data, (*f)->clone());
                                statesFunctions.push_back(dbg);
//                                RootToFunction[ClonedTree->root]->setvar(ClonedTree->data, (*f)->clone());
                                ClonedTree = VarToVal[ClonedTree];
                            }
                      /* }*/
                    }
                    tree = statesTrees.erase(tree);
                    func = statesFunctions.erase(func);
                    del=true;
                }
            }
            if (!del) {
                tree++;
                func++;
            }
        }

        if (!used[pos->left]) {
            for (Node* &n : statesTrees) {
                n = n->left;
            }
            pos = pos->left;
        }
        else if (!used[pos->right]) {
            for (Node* &n : statesTrees) {
                n = n->right;
            }
            pos = pos->right;
        }
        else {
            pos = pos->parent;
            if (pos!=nullptr)
                for (Node* &n : statesTrees) {
                    n = n->parent;
                }
        }


        cout<<it<<":\n";
        func = statesFunctions.begin();
        while (func!=statesFunctions.end()) {
            (*func)->print();
            cout<<endl;
            func++;
        }
        cout<<"--------------------------\n";
        it++;
    }
    list<Node*>::iterator tree = statesTrees.begin();
    list<fNode*>::iterator func = statesFunctions.begin();
    while (tree!=statesTrees.end() && !Node::equal((*tree), Expr)) tree++, func++;
    if (tree!=statesTrees.end() && Node::equal((*tree), Expr)) (*func)->print();
    else output<<"Impossible";
}