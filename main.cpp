#include <iostream>
#include <cstring>
#include <iomanip>

using  namespace std ;

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

int main() {
    char word[] = "Hello!";
    stack ch_stack(word);

    cout << ch_stack.show_last() << endl;

    return 0;
}


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
