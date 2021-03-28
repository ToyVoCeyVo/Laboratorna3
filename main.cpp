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

