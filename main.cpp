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
using namespace std;

int main ()
{
    test();
    fstream input("input");
    fstream output("output");
    string e;
    getline(input, e);
    ast e_tree = buildAST(TokenStream(e));
    list<ast> fTreesList;
    list<functionTree> fList;
    map<ast, string> fname;
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
            while (s[pos]!=')' && pos!=',') var+=s[pos], pos++;
            fList.back()->push_var(var);
        }
        pos+=2;
        while (pos<s.length()) expr+=s[pos], pos++;
        fTreesList.push_back(buildAST(TokenStream(expr)));
    }
    
}
