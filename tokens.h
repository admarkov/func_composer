//
// Created by admarkov on 22.04.17.
//

#ifndef FUNC_COMPOSER_LEXICAL_ANALYZER_H
#define FUNC_COMPOSER_LEXICAL_ANALYZER_H

#include <iostream>
#include <string>
#include <deque>
#include <vector>
using namespace std;

class Token {
public:
    string type;
    string data;

    Token(string t="", string d="") : type(t), data(d) {}

    Token* operator=(Token b) {
        type=b.type;
        data=b.data;
    }

    int priority() {
        if (data=="+" || data=="-") return 3;
        else if (data=="*" || data=="/") return 2;
        else if (data=="^") return 1;
        else return 0;
    }
    void print() {
        cout<<"["<<type<<": "<<data<<"]";
    }
};

class TokenStream {
    deque<Token> tokens;
public:
    size_t size() {
        return tokens.size();
    }
    Token get(int i) {
        return tokens[i-1];
    }
    void push(Token t) {
        tokens.push_back(t);
    }

    void refactor(string &s) {
        for (int i=0; i<s.length(); i++) {
            if (s[i]==' ' || s[i]=='    ') s.erase(i,1);
//            if (s[i]>='A' && s[i]<='Z') s[i]-=('A'-'a');
        }
    }

    TokenStream(string s) {
        refactor(s);
        int pos = 0;
        while (pos<s.length()) {
            if (s[pos]=='+') push(Token("operator", "+")), pos++;
            if (s[pos]=='-') push(Token("operator", "-")), pos++;
            if (s[pos]=='*') push(Token("operator", "*")), pos++;
            if (s[pos]=='/') push(Token("operator", "/")), pos++;
            if (s[pos]=='^') push(Token("operator", "^")), pos++;
            if (s[pos]=='(') push(Token("function", "(")), pos++;
            if (s[pos]==')') push(Token("function", ")")), pos++;
            if (isdigit(s[pos])) {
                string c="";
                while (pos<s.length() && isdigit(s[pos])) {
                    c+=s[pos];
                    pos++;
                }
                push(Token("constant", c));
            }
            else if (isalpha(s[pos])) {
                string x="";
                while (pos<s.length() && isalpha(s[pos])) {
                    x+=s[pos];
                    pos++;
                }
                if (pos<s.length() && s[pos]=='(') {
                    push(Token("function", x));
                }
                else {
                    push(Token("variable", x));
                }
            }
        }
    }

    TokenStream() {

    }
    int findInflection() {
        int res=-1;
        int p=0;
        int brackets=0;
        for (int i=1; i<=size(); i++) {
            Token t = get(i);
            if (t.data=="(") brackets++;
            else if (t.data==")") brackets--;
            else if (brackets==0 && t.type=="operator" && (t.priority()>p || t.priority()==1 && p==1)) {
                res=i;
                p=t.priority();
            }
        }
        return res;
    }

    TokenStream leftSplit(int pos) {
        TokenStream res;
        for (int i=1; i<pos; i++) res.push(get(i));
        return res;
    }

    TokenStream rightSplit(int pos) {
        TokenStream res;
        pos++;
        while (pos<=size()) res.push(get(pos)), pos++;
        return res;
    }

    bool split(Token &t, TokenStream &left, TokenStream &right) {
        int inflection = findInflection();
        if (inflection==-1) return false;
        t = get(inflection);
        left=leftSplit(inflection);
        right=rightSplit(inflection);
        return true;
    }

    void breakBrackets() {
        if (get(1).data!="(") tokens.pop_front();
        tokens.pop_front();
        tokens.pop_back();
    }

    void print() {
        cout<<"{";
        for (int i=1; i<size(); i++) {
            get(i).print();
            cout<<", ";
        }
        get(size()).print();
        cout<<"}"<<endl;
    }

    TokenStream* operator=(TokenStream b) {
        while (!tokens.empty()) tokens.pop_back();
        for (int i=1; i<=b.size(); i++) push(b.get(i));
    }

    ~TokenStream() {

    }
};

#endif //FUNC_COMPOSER_LEXICAL_ANALYZER_H
