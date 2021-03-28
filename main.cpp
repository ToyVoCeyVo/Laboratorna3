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

    return 0;
}


stack::stack (char * input_string)
{
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

stack ::~stack ()
{
    delete[] tokens;
}


