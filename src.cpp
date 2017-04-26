#include <iostream>
#include <string>
#include "tokens.h"
#include "ast.h"
#include "tree_builder.h"

using namespace std;

int main ()
{
    TokenStream f("x^2^(3+5)+7");
    TokenStream x("2*sin(t)");
    TokenStream c("8");
    Node* f_ast = buildAST(f);
    Node* x_ast = buildAST(x);
    Node* c_ast = buildAST(c);
    x_ast->setvar(x_ast, f_ast, "t");
    Node::print(x_ast);
}