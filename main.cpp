#include <iostream>
#include <cstring>
#include <sstream>

using  namespace std ;

/*
 cd source\repos\Laboratorna3\cmake-build-debug\
 */


class stack
{
public:
    stack();
    ~stack ();

    char show_last();
    char pop();
    void push_back(char);
    int size();

private:
    char* tokens;
    int stack_current_size;
    int max_size;

    void expend();
};

float type_of_oper(string one,string two,char oper);
void reverseStr(string& );
bool operatorCheck(char );
float vse_na_sviti (string);

void read_args(int, char**, char*);
string to_pn(string);
bool is_num(char);
bool is_oper(char);
int oper_prec(char);


//---Main function---

int main(int argc, char* argv[])
{


    char expresion[100] = "";
    if(argc > 1) {
        read_args(argc, argv, expresion);
    }else{
        cout << "Run program from console!\n";
        return 1;
    }

    string input(expresion);
    string output = to_pn(input);

    cout << "Polish notation: " << output << endl;
    float res = vse_na_sviti(output);
    cout<<"Result : "<<res<<endl;
    return 0;
}

//---realizations---

stack::stack()
{
    stack_current_size = 0;
    max_size = 3;
    tokens = new char[max_size];
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
    if(stack_current_size > 0.8 * max_size){
        expend();
    }
}

int stack::size()
{
    return stack_current_size;
}

void stack::expend() {
    char *temp;
    max_size*=2;

    temp = new char[max_size];

    for (int i = 0; i < stack_current_size; ++i) {
        temp[i]=tokens[i];
    }

    delete[] tokens;
    tokens = temp;
}

void read_args(int argc, char** argv, char* expr){
    for (int i = 1; i < argc; ++i) {
        strcat(expr, argv[i]);
    }
}

string to_pn(string input){
    stack opers;
    string output ="";
    char c_token;

    for (auto token = input.begin(); token != input.end(); ++token) {
        cout << *token << "\t| " << output << "\t| " << opers.show_last() <<endl;
        if(is_num(*token) || (token!= input.begin() && *(token-1) == '(' && *token == '-') || (token == input.begin() && *token == '-')){
            if(*token == '-' && output.size()==2 && output[0]=='-'){
                output.clear();
            }else if((token+1) == input.end() || *(token+1) == '(' || *(token+1) == ')' || is_oper(*(token+1))){
                output = output + *token + ' ';
            }else{
                output = output + *token;
            }
        } else if(is_oper(*token)){
            while(opers.size()
            && ( oper_prec(opers.show_last()) > oper_prec(*token) || (oper_prec(opers.show_last()) == oper_prec(*token) && *token != '^'))
            && opers.show_last() != '('){
                output = output + opers.pop() + ' ';
            }
            opers.push_back(*token);
        } else if((*token) == '('){
            opers.push_back(*token);
        } else if((*token) == ')'){
            while(opers.show_last() != '('){
                output = output + opers.pop() + ' ';
            }
            opers.pop();
        }
    }
    while(opers.size()){
        output = output + opers.pop();
        if (opers.size())
            output = output + ' ';
    }
    return output;
}

bool is_num(char c){
    if(isdigit(c) || c == '.') return 1;
    return 0;
}

bool is_oper(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^') return 1;
    return 0;
}

int oper_prec(char c){
    switch (c) {
        case '-':
            return 1;
        case '+':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return 0;
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

float type_of_oper(string temp1,string temp2,char oper){
    float res;
    switch (oper) {
        case '*':
            res = stof(temp2) * stof(temp1);
            break;
        case '-':
            res = stof(temp2) - stof(temp1);
            break;
        case '+':
            res = stof(temp2) + stof(temp1);
            break;
        case '/':
            res = stof(temp2) / stof(temp1);
            break;
        case '^':
            res = pow(stof(temp2), stof(temp1));
            break;
    }
    return res;
}

float vse_na_sviti(string input) {

    bool flag=true;
    while (flag) {
        string temp1 = "", temp2 = "";
        int end_ind, start_ind;
        float res;
        char oper;
        int number_of_chars = 0, number_of_spaces = 0;
        int n_ch;
        flag=false;
        for(int i = 0; i < input.size(); i++) {
            if (operatorCheck(input[i]) && (input[i+1]==' ' || i==input.size()-1)) {
                oper = input[i];
                flag=true;
                break;

            }
            number_of_chars++;
        }

        if(flag==false)
            break;

        end_ind = number_of_chars;
        number_of_chars -= 2;
        n_ch = number_of_chars;

        for (int i = number_of_chars; i > 0; i--) {
            if (input[i] != ' ') {
                temp1 += input[i];
                n_ch--;
            } else {
                n_ch--;
                break;
            }
        }
        reverseStr(temp1);
        number_of_chars = n_ch;

        for (int i = number_of_chars; i >= 0; i--) {
            if (input[i] != ' ') {
                temp2 += input[i];
                n_ch--;
            } else {

                break;
            }
        }

        start_ind=n_ch+1;
        reverseStr(temp2);

        res = type_of_oper(temp1, temp2, oper);

        input=input.substr(0,start_ind)+input.substr(end_ind+1);
        //input.erase(input.start()+start_ind,end_ind);
        std::ostringstream ss;
        ss<<res;
        string s(ss.str());
        input.insert(start_ind,s);
    }/**/
    return stof(input);//res;
}
