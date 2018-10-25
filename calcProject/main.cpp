#include <iostream>
#include <stack>
#include <sstream>
#include <math.h>
#include <ctype.h>
#include <string>

using namespace std;

double runOperate(double a, double b, char operate);
int precedence(char operate);
bool isOperand(char character);

int main(int argc, char** argv)
{

    stack<char> operate;
    stack<double> operand;
    stringstream stream(argv[1]);

    string str;
    while(getline(stream, str, ' '))
    {
        if(isdigit(str[0]))
        {
            //if a number, push onto the operand stack
            operand.push(stod(str, NULL));
        }
        else if(str[0] == '(')
        {
            operate.push('(');
        }
        else if(str[0] == ')')
        {
            if(operate.empty())
            {
                cout<<"invalid input"<<endl;
                exit(1);
            }
            while(operate.top() != '(')
            {

                if(operate.empty())
                {
                    cout<<"invalid input"<<endl;
                    exit(1);
                }
                char oper = operate.top();
                operate.pop();

                if(operand.empty())
                {
                    cout<<"invalid input"<<endl;
                    exit(1);
                }
                double a = operand.top();
                operand.top();

                if(operand.empty())
                {
                    cout<<"invalid input"<<endl;
                    exit(1);
                }

                double b = operand.top();
                operand.pop();

                operand.push(runOperate(b, a, oper));

            }
            operate.pop();

        }



    }



    return 0;
}


double runOperate(double a, double b, char operate)
{
    switch(operate)
    {
    case '+':
        return a + b;
        break;
    case '-':
        return a - b;
        break;
    case '*':
        return a * b;
        break;
    case '/':
        return a / b;
        break;
    case '^':
        return pow(a, b);
        break;
    default :
        cout<<"invalid arguement" << endl;
        exit(2);
        break;
    }

}
int precedence(char operate)
{
    int x;

    switch(operate)
    {
    case '+':
    case '-':
        x = 0;
        break;
    case '*':
    case '/':
        x = 1;
        break;
    case '^':
        x = 2;
        break;
    case '(':
    case ')':
        x = 3;
        break;
    default :
        x = -1;
        break;
    }

    return x;
}

bool isOperand(char character){
switch(character)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
        return true;
        break;
    default :
        return false;
        break;
    }
}
