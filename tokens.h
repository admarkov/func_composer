//
// Created by admarkov on 22.04.17.
//

#ifndef FUNC_COMPOSER_LEXICAL_ANALYZER_H
#define FUNC_COMPOSER_LEXICAL_ANALYZER_H

#include <string>
#include <deque>
using namespace std;

class Token {
public:
    string type;
    string data;

    Token(string t="", string d="") : type(t), data(d) {}

    int priority() {
        if (data=="+" || data=="-") return 3;
        else if (data=="*" || data=="/") return 2;
        else if (data=="^") return 1;
        else return 0;
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
    TokenStream(string s) {
        //TODO: Lexical analyzer
    }
    TokenStream() {

    }
    int findInflection() {
        int res=-1;
        int p=5;
        int brackets=0;
        for (int i=1; i<=size(); i++) {
            Token t = tokens[i];
            if (t.data=="(") brackets++;
            else if (t.data==")") brackets--;
            else if (brackets==0 && t.type=="operator" && (t.priority()<p || t.priority()==1 && p==1)) {
                res=i;
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
        while (pos<=size()) res.push(get(pos));
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

    ~TokenStream() {

    }
};

#endif //FUNC_COMPOSER_LEXICAL_ANALYZER_H
