#include <iostream>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <sstream>
//#include <bits/stdc++.h>
using  namespace std ;

/*
 cd source\repos\Laboratorna3\cmake-build-debug\
 */


class stack
{
public:
    stack (char*);
    stack();
    ~stack ();

    char show_last();
    char pop();
    void push_back(char);
    int size();

private:
    char* tokens;
    int stack_current_size;
};


void reverseStr(string& );
bool operatorCheck(char );
float vse_na_sviti (string);

void read_args(int, char**, char*);
string shuntingYard(const string& input);
unsigned op_preced(const char ch);
bool is_number(char ch);
bool is_operator(char ch);


//---Main function---

int main(int argc, char* argv[])
{

    char expresion[100] = "";

    if(argc > 1) {
        read_args(argc, argv, expresion);
        cout << "Your expresion: " << expresion << endl; // GET RID OF in release!
    }else{
        cout << "Run program from console!\n";
        return 1;
    }

    string input(expresion);
    string output;
    output = shuntingYard(input);
    cout << "Polish notation: " << output << endl;

    float res = vse_na_sviti("1.0 + 1.0");
    cout<<"Result : "<<res<<endl;
    return 0;
}

//---realizations---

stack::stack (char * input_string)
{
    // input string will be reversed:
    // char {H,e,l,l,o} --> stack {o,l,l,e,H}

    int n = strlen(input_string);

    tokens = new char[n];

    stack_current_size = 0;

    for (size_t i = 0; i < n; i++, stack_current_size++)
    {
        tokens[stack_current_size] = input_string[n - 1 - i];
    }
}

stack::stack()
{
    stack_current_size = 0;
    tokens = new char[100];
}

stack::~stack ()
{
    delete[] tokens;
}

char stack::show_last()
{
    return tokens[stack_current_size-1];
}

char stack::pop()
{
    stack_current_size--;
    return tokens[stack_current_size];
}

void stack::push_back(char symbol)
{
    tokens[stack_current_size] = symbol;
    stack_current_size++;
}

int stack::size()
{
    return stack_current_size;
}

void read_args(int argc, char** argv, char* expr){
    for (int i = 1; i < argc; ++i) {
        strcat(expr, argv[i]);
    }
}

//алгоритм сортувальної станції
string shuntingYard(const string& input)
{
    stack operators;
    string output("");
    unsigned length = input.length();
    for (unsigned i = 0; i < length; ++i)
    {
        //перевірка чи вхідний символ є частиною числа(врахування унарного  '-')
        if (is_number(input[i]) || (input[i] == '-' && i == 0) || (i > 0 && input[i-1] == '(' && input[i] == '-'))
        {
            //перевірка це останній символ числа,щоб поставити після нього пробіл
            if(i + 1 == length || is_operator(input[i+1]) || input[i+1] == '(' || input[i+1] == ')')
            {
                output = output + input[i] + ' ';
            }
            else
            {
                output = output + input[i];
            }
        }
        else if (input[i] == '(')
        {
            operators.push_back('(');
        }
        else if (input[i] == ')')
        {
            while (operators.show_last() != '(')
            {
                output = output + operators.pop()+ ' ';
            }
            operators.pop();
        }
        else if (is_operator(input[i]))
        {
            while (!operators.size()==0 && (op_preced(operators.show_last()) >= op_preced(input[i])))
            {
                output = output + operators.pop() + ' ';
            }
            operators.push_back(input[i]);
        }
        else
        {
            //помилка вхідних даних
            throw "Помилка вхідних даних";
        }
    }
    //виводимо символи що залишились у стеку
    unsigned stackSize = operators.size();
    if (stackSize > 0)
    {
        for (unsigned i = 0; i < stackSize - 1; ++i)
        {
            output = output + operators.pop() + ' ';
        }
        output = output + operators.pop();
    }
    return output;
}


unsigned op_preced(const char ch)
{
    switch(ch)
    {
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
    }
    // бля випадку вхідного символу '('
    return 0;
}

bool is_number(char ch)
{
    return (('0' <= ch) && (ch <= '9')) || (ch == '.');
}

bool is_operator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^');
}


bool operatorCheck(char ch){
    if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^' )
        return true;
    return false;
}

void reverseStr(string& str)
{
    int n = str.length();

    // Swap character starting from two
    // corners
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}


