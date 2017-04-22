//
// Created by admarkov on 22.04.17.
//

#ifndef FUNC_COMPOSER_LEXICAL_ANALYZER_H
#define FUNC_COMPOSER_LEXICAL_ANALYZER_H

#include "frame.h"
#include <string>
#include <vector>
using namespace std;

typedef unsigned int index;

struct token {
    enum token_type {constant, variable, plus, minus, mult, div, power, opening_bracket, closing_bracket, trig};
    string name;
    token_type type;
    int priority() {

    }
    token(token_type t) : type(t) {};
    token(token_type t, string n) : type(t), name(n) {
        if (type!=variable) crash();
    }
};

class token_stream {
    vector<token> stream;
    bool indexCorrect(index i) {
        if (i>=1 && i<=size()) return true;
        else return false;
    }
public:
    size_t size() {
        return stream.size();
    }
    void push(token t) {
        stream.push_back(t);
    }
    token get(index i)
    {
        if (!indexCorrect(i)) crash();
        else return stream[i-1];
    }
    token_stream() {}
    token_stream leftsplit(int pos) {
        token_stream res;
        for (int i=1; i<pos; i++) res.push(get(i));
        return res;
    }
    token_stream rightsplit(int pos) {
        token_stream res;
        pos++;
        while (pos<=size()) res.push(get(pos));
        return res;
    }
    index get_inflection() {
        index res=1;
        for (index i=1; i<=size(); i++) {
            if (get(i).priority()<get(res).priority()) res=i;
        }
        return res;
    }
    void split(token &inflection, token_stream &l, token_stream &r) {
        index inf_index = get_inflection();
        inflection = get(inf_index);
        l = leftsplit(inf_index);
        r = rightsplit(inf_index);
    }
};

#endif //FUNC_COMPOSER_LEXICAL_ANALYZER_H
