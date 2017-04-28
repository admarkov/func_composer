//
// Created by admarkov on 28.04.17.
//

#include <iostream>
#include <vector>
#include <string>
#include "tokens.h"

using namespace std;

struct verdict {
    enum result {fail, ok} res;
    string msg="";
    verdict(result r, string s="") : res(r), msg(s) {};
};


verdict token_stream_building_1() {
    string input="x^25^(3+var)+7";
    string output=TokenStream(input).str();
    string answer = "{[variable: x], [operator: ^], [constant: 25], [operator: ^], [function: (], [constant: 3], [operator: +], [variable: var], [function: )], [operator: +], [constant: 7]}";
    if (output!=answer) return verdict(verdict::fail);
    else return verdict(verdict::ok);
}

verdict token_stream_building_2() {
    string input="var";
    string output=TokenStream(input).str();
    string answer = "{[variable: var]}";
    if (output!=answer) return verdict(verdict::fail);
    else return verdict(verdict::ok);
}

verdict token_stream_building_3() {
    string input="239";
    string output=TokenStream(input).str();
    string answer = "{[constant: 239]}";
    if (output!=answer) return verdict(verdict::fail);
    else return verdict(verdict::ok);
}

verdict token_stream_building_4() {
    string input="sin(239^(5+t)^x*8*cos(x)+25*ln(e+8-sin(x+9)*cos(y*8*x)))";
    string output=TokenStream(input).str();
    string answer = "{[function: sin], [function: (], [constant: 239], [operator: ^], [function: (], [constant: 5], [operator: +], [variable: t], [function: )], [operator: ^], [variable: x], [operator: *], [constant: 8], [operator: *], [function: cos], [function: (], [variable: x], [function: )], [operator: +], [constant: 25], [operator: *], [function: ln], [function: (], [variable: e], [operator: +], [constant: 8], [operator: -], [function: sin], [function: (], [variable: x], [operator: +], [constant: 9], [function: )], [operator: *], [function: cos], [function: (], [variable: y], [operator: *], [constant: 8], [operator: *], [variable: x], [function: )], [function: )], [function: )]}";
    if (output!=answer) return verdict(verdict::fail);
    else return verdict(verdict::ok);
}

verdict ts_findinflection_1() {
    TokenStream input("x^25^(3+var)+7");
    int output=input.findInflection();
    int answer=10;
    if (output!=answer) return verdict(verdict::fail, to_string(output));
    else return verdict(verdict::ok);
}

verdict ts_findinflection_2() {
    TokenStream input("var");
    int output=input.findInflection();
    int answer=-1;
    if (output!=answer) return verdict(verdict::fail, to_string(output));
    else return verdict(verdict::ok);
}

verdict ts_findinflection_3() {
    TokenStream input("sin(239+s)");
    int output=input.findInflection();
    int answer=-1;
    if (output!=answer) return verdict(verdict::fail);
    else return verdict(verdict::ok);
}

verdict ts_findinflection_4() {
    TokenStream input("239^(5+t)^x*8*cos(x)+25*ln(e+8-sin(x+9)*cos(y*8*x))+5");
    int output=input.findInflection();
    int answer=17;
    if (output!=answer) return verdict(verdict::fail);
    else return verdict(verdict::ok);
}

verdict ts_findinflection_5() {
    TokenStream input("239^(5+t)^x*8");
    int output=input.findInflection();
    int answer=10;
    if (output!=answer) return verdict(verdict::fail);
    else return verdict(verdict::ok);
}

verdict ts_findinflection_6() {
    TokenStream input("239^(5+t)^x");
    int output=input.findInflection();
    int answer=8;
    if (output!=answer) return verdict(verdict::fail);
    else return verdict(verdict::ok);
}

verdict ts_split_1() {
    TokenStream l, r;
    Token m;
    TokenStream input("239^(5+t)^x*8*cos(x)+25*ln(e+8-sin(x+9)*cos(y*8*x))+5");
    string answer_l = TokenStream("239^(5+t)^x*8*cos(x)").str();
    string answer_m = Token("operator", "+").str();
    string answer_r=TokenStream("25*ln(e+8-sin(x+9)*cos(y*8*x))+5").str();
    input.split(m, l, r);
    if (answer_l==l.str() && answer_r==r.str() && answer_m==m.str()) return verdict(verdict::ok);
    else return verdict(verdict::fail);
}

verdict ts_split_2() {
    TokenStream l, r;
    Token m;
    TokenStream input("239^(5+t)^x");
    string answer_l = TokenStream("239^(5+t)").str();
    string answer_m = Token("operator", "^").str();
    string answer_r="{[variable: x]}";
    input.split(m, l, r);
    if (answer_l==l.str() && answer_r==r.str() && answer_m==m.str()) return verdict(verdict::ok);
    else return verdict(verdict::fail);
}

verdict ts_split_3() {
    TokenStream l, r;
    Token m;
    TokenStream input("239^(5+t)^x*8*cos(x)*25*ln(e+8-sin(x+9)*cos(y*8*x))*5");
    string answer_l = TokenStream("239^(5+t)^x").str();
    string answer_m = Token("operator", "*").str();
    string answer_r=TokenStream("8*cos(x)*25*ln(e+8-sin(x+9)*cos(y*8*x))*5").str();
    input.split(m, l, r);
    if (answer_l==l.str() && answer_r==r.str() && answer_m==m.str()) return verdict(verdict::ok);
    else return verdict(verdict::fail);
}

verdict ts_break_brackets_1() {
    TokenStream input("(239^(5+t)^x*8*cos(x)+25*ln(e+8-sin(x+9)*cos(y*8*x))+5)");
    input.breakBrackets();
    string output=input.str();
    string answer=TokenStream("239^(5+t)^x*8*cos(x)+25*ln(e+8-sin(x+9)*cos(y*8*x))+5").str();
    if (output!=answer) return verdict(verdict::fail);
    else return verdict(verdict::ok);
}

verdict ts_break_brackets_2() {
    TokenStream input("((239^(5+t)^x*8*cos(x)+25*ln(e+8-sin(x+9)*cos(y*8*x))+5))");
    input.breakBrackets();
    string output=input.str();
    string answer=TokenStream("(239^(5+t)^x*8*cos(x)+25*ln(e+8-sin(x+9)*cos(y*8*x))+5)").str();
    if (output!=answer) return verdict(verdict::fail);
    else return verdict(verdict::ok);
}

verdict ts_break_brackets_3() {
    TokenStream input("sin(239^(5+t)^x*8*cos(x)+25*ln(e+8-sin(x+9)*cos(y*8*x))+5)");
    input.breakBrackets();
    string output=input.str();
    string answer=TokenStream("239^(5+t)^x*8*cos(x)+25*ln(e+8-sin(x+9)*cos(y*8*x))+5").str();
    if (output!=answer) return verdict(verdict::fail);
    else return verdict(verdict::ok);
}

verdict __test(string name, verdict(*f)()) {
    cout<<name<<": ";
    verdict res = f();
    if (res.res==verdict::ok) cout<<"OK";
    else cout<<"FAIL";
    if (res.msg.length()>0) cout<<" ["<<res.msg<<"]";
    cout<<endl;
    return res;
}

void testTokenStream() {
    __test("TokenStream.constructor #1", token_stream_building_1);
    __test("TokenStream.constructor #2", token_stream_building_2);
    __test("TokenStream.constructor #3", token_stream_building_3);
    __test("TokenStream.constructor #4", token_stream_building_4);
    __test("TokenStream.findInflection #1", ts_findinflection_1);
    __test("TokenStream.findInflection #2", ts_findinflection_2);
    __test("TokenStream.findInflection #3", ts_findinflection_3);
    __test("TokenStream.findInflection #4", ts_findinflection_4);
    __test("TokenStream.findInflection #5", ts_findinflection_5);
    __test("TokenStream.findInflection #6", ts_findinflection_6);
    __test("TokenStream.split #1", ts_split_1);
    __test("TokenStream.split #2", ts_split_2);
    __test("TokenStream.split #3", ts_split_3);
    __test("TokenStream.breakBrackets #1", ts_break_brackets_1);
    __test("TokenStream.breakBrackets #2", ts_break_brackets_2);
    __test("TokenStream.breakBrackets #3", ts_break_brackets_3);
}

void test() {
    cout<<"Testing...\n";

    testTokenStream();

    cout<<"-------------------\n\n";
}