#include <iostream>

#define INPUT_FILE "sample1"

using namespace std;

class Expression {
public:
    virtual void print() = 0;
    virtual Expression* clone() = 0;
    virtual ~Expression() {

    }
};

class Const : public Expression {
    double c;
public:
    Const() : c(0) {}
    Const(double x) : c(x) {}
    void print()
    {
        cout << c;
    }
    Expression* clone()
    {
        return new Const(c);
    }
};

class Var : public Expression {
public:
    void print()
    {
        cout << 'x';
    }
    Expression* clone()
    {
        return new Var();
    }
};

class Sum : public Expression {
    Expression *a, *b;
public:
    Sum(Expression* l, Expression* r) : a(l), b(r) {}
    void print()
    {
        a->print();
        cout << '+';
        b->print();
    }
    Expression* clone()
    {
        return new Sum(a, b);
    }
    ~Sum() {
        delete a;
        delete b;
    }
};

class Dif : public Expression {
    Expression *a, *b;
public:
    Dif(Expression* l, Expression* r): a(l), b(r) {}
    void print()
    {
        a->print();
        
        b->print();
    }
};

Expression* operator+(Expression f, Expression g)
{
    return new Sum(f, g);
}
Expression* operator-(Expression f, Expression g)
{
    return new Dif(f, g);
}

int main ()
{
    freopen(INPUT_FILE, "r", stdin);

}