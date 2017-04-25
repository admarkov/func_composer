//
// Created by admarkov on 25.04.17.
//

#include "ast.h"
#include "tokens.h"

Node* buildAST(TokenStream stream, Node* root = nullptr, Node* p = nullptr) {
    if (stream.findInflection()!=-1) {
        TokenStream left, right;
        Token inflection;
        stream.split(inflection,left,right);
        Node* n = new Node(p, inflection.data, nullptr, nullptr);
        if (root==nullptr) root=n;
        n->left=buildAST(left, root, n);
        n->right=buildAST(right, root, n);
        return n;
    }
    else {
        Token t = stream.get(1);
        if (t.data!="(") {
            if (t.type=="function") {
                Node *n = new Node(p, t.data, nullptr, nullptr);
                if (root == nullptr) root = n;
                stream.breakBrackets();
                n->left=buildAST(stream, root, n);
                return n;
            }
            if (t.type=="constant") {
                Node *n = new Node(p, t.data, nullptr, nullptr);
                if (root == nullptr) root = n;
                return n;
            }
            if (t.type=="variable") {
                var *n = new var(t.data, root, p);
                if (n->root==nullptr) n->root=n;
                return (Node*)n;
            }
        }
        else {
            stream.breakBrackets();
            return buildAST(stream, root, p);
        }
    }
}