//Hailey dhanens

#define _GLIBCXX_USE_CXX11_ABI 0
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
int calculator(char* argument);
string formatString(string str);

int main(int argc, char** argv)
{

    for(int i = 1; i < argc; i++)
    {
        calculator(argv[i]);
    }


}

int calculator(char* argument)
{

    stack<char> operate;
    stack<double> operand;
    int num;
    string strings(argument);
    string str;

   stringstream stream(formatString(strings));

    while(getline(stream, str, ' '))
    {

        double value;
        try
        {
            value = std::stod(str, NULL); // if value cant be converted to decimal...
            num = 1;
        }
        catch(std::exception& e)
        {
            num =  0;
        }
        if(num)
        {
            //if a number, push onto the operand stack
            operand.push(value);
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
                    return(1);
                }

                char oper = operate.top();
                operate.pop();

                if(operand.empty())
                {
                    cout<<"invalid input"<<endl;
                    return(1);
                }
                double a = operand.top();
                operand.pop();

                if(operand.empty())
                {
                    cout<<"invalid input"<<endl;
                    return(1);
                }

                double b = operand.top();
                operand.pop();

                operand.push(runOperate(b, a, oper));

            }

            operate.pop();

        }

        else if(isOperator(str[0]))
        {
            if(operate.empty())
            {
                operate.push(str[0]);
            } //endif
            else
            {

                int pres = precedence(str[0]);

                while(precedence(operate.top()) > pres)
                {

                    char oper = operate.top();
                    operate.pop();

                    if(operand.empty())
                    {
                        cout<<"invalid input"<<endl;
                        return(7);
                    }

                    double a = operand.top();
                    operand.pop();

                    if(operand.empty())
                    {
                        cout<<"invalid input"<<endl;
                        return(8);
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

    while(!operate.empty())
    {

        char oper = operate.top();
        operate.pop();

        if(operand.empty())
        {
            cout<<"invalid input"<<endl;
            return(3);
        }
        double a = operand.top();
        operand.pop();

        if(operand.empty())
        {
            cout<<"invalid input"<<endl;
            return(3);
        }

        double b = operand.top();
        operand.pop();
        operand.push(runOperate(b, a, oper));


    }
    double answer;
    if(operand.empty())
    {

        cout << "error" << endl;
        return(4);
    }
    else
    {
        answer = operand.top();
        operand.pop();

    }

    if(!operand.empty())
    {

        cout <<"invalid input" << endl;
        return(5);
    }

    else
    {

        cout << argument << " = " << answer << endl;

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
        if(b != 0)
        {
            return a / b;
        }
        else
        {
            cout << "dividing by zero is undefined" << endl;
            exit(12);
        }
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

bool isOperator(char character)
{
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

string formatString(string str)
{
    string newString = "";

    for(int i = 0; i < str.length(); i++)
    {

        char c = str.at(i);

        if(c == '+' || c == '/' || c == '*' || c == '^' || c == '(' || c == ')')
        {

            newString = newString + ' ' + c + ' ';

        }
        else if(str.at(i) == '-')
        {

            if(i == 0){


                newString = newString + '-';
            }
            else if(i <  str.length()-1)
            {
                if(!isdigit(str.at(i-1)) && isdigit(str.at(i+1)))
                {

                    newString = newString + ' ' + '-';

                }

                else if(isdigit(str.at(i-1)) && (isdigit(str.at(i + 1)) || str.at(i+1)== '.')|| str.at(i+1)=='-' || str.at(i+1) == ' ')
                {

                    newString = newString + ' ' + '-' + ' ';

                }

            }
            else if(str.at(i+1) == ' ' && str.at(i - 1) == ' ')
            {

                newString = newString + ' ' + '-' + ' ';

            }




        }

        else
        {

            newString = newString + c;

        }


    }

    return newString;

}
