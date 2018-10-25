#include <iostream>
#include <stack>
#include <sstream>
#include <math.h>
#include <ctype.h>
#include <string>

using namespace std;

double runOperate(double a, double b, char operate);
int precedence(char operate);
bool isOperator(char character);

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
                operand.pop();

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

        else if(isOperator(str[0])){
            if(operate.empty()){
                operate.push(str[0]);
            }
            else{

            int pres = precedence(str[0]);

            while(precedence(operate.top()) > pres) {

                char oper = operate.top();
                operate.pop();

                if(operand.empty())
                {
                    cout<<"invalid input"<<endl;
                    exit(7);
                }

                double a = operand.top();
                operand.pop();

                if(operand.empty())
                {
                    cout<<"invalid input"<<endl;
                    exit(8);
                }

                double b = operand.top();
                operand.pop();

                operand.push(runOperate(b, a, oper));

                if(operate.empty()) break;
            }

            operate.push(str[0]);
            }



        }



    }

    while(!operate.empty()){


                char oper = operate.top();
                operate.pop();

                if(operand.empty())
                {
                    cout<<"invalid input"<<endl;
                    exit(3);
                }
                double a = operand.top();
                operand.pop();

                if(operand.empty())
                {
                    cout<<"invalid input"<<endl;
                    exit(3);
                }

                double b = operand.top();
                operand.pop();

                operand.push(runOperate(b, a, oper));


    }
    double answer;
    if(operand.empty()){

        cout << "error" << endl;
        exit(4);
    }
    else{
        answer = operand.top();
        operand.pop();

    }

    /*if(!operand.empty()){

        cout <<"invalid input" << endl;
        exit(5);
    }

    else{*/

        cout << argv[1] << " = " << answer << endl;

    //}

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
        x = 1;
        break;
    case '*':
    case '/':
        x = 1;
        break;
    case '^':
        x = 3;
        break;
    case '(':
           x = 0;
        break;
    default :
        x = -1;
        break;
    }

    return x;
}

bool isOperator(char character){
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
