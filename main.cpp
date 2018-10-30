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
    //calculate each inputted equation
    for(int i = 1; i < argc; i++)
    {
        calculator(argv[i]);
    }


}

int calculator(char* argument)
{

    stack<char> operate;            //holds operators
    stack<double> operand;          //holds operands
    int num;
    string strings(argument);       //will be used to hold formatted equation
    string str;                     //will be used to hold tokens

   //format string for tokenization
   stringstream stream(formatString(strings));

    //while there are still tokens left...
    while(getline(stream, str, ' '))
    {

        double value;
        try
        {
            value = std::stod(str, NULL); // if value cant be converted to decimal
            num = 1;
        }
        catch(std::exception& e)
        {
            num =  0;
        }

        //if the number is able to be converted to a double put it on the operand stack
        if(num)
        {
            operand.push(value);
        }

        //if the token is a open parenthesis push it onto the operator stack. It will have the least priority
        else if(str[0] == '(')
        {
            operate.push('(');
        }

        //if the token is closed parenthesis, perform operations until close parenthesis is found, an pop it from the stack
        else if(str[0] == ')')
        {
            //if there are no operators to be popped, then the input was not formatted correctly.
            if(operate.empty())
            {
                cout<<"invalid input"<<endl;
                exit(1);
            }

            //continue to pop and compute with operators until the open parenthesis is found.
            while(operate.top() != '(')
            {
                //if there are no operators to be popped, then the input was not formatted correctly.
                if(operate.empty())
                {
                    cout<<"invalid input"<<endl;
                    return(1);
                }

                char oper = operate.top();
                operate.pop();

                //if there are operators, but nothing to operate on the equation isn't formatted right.
                if(operand.empty())
                {
                    cout<<"invalid input"<<endl;
                    return(1);
                }
                double a = operand.top();
                operand.pop();

                //if there are operators, but nothing to operate on the equation isn't formatted right.
                if(operand.empty())
                {
                    cout<<"invalid input"<<endl;
                    return(1);
                }

                double b = operand.top();
                operand.pop();

                //if we can get the operators and operands we need
                //perform the operation, and the push the result onto the operand stack
                operand.push(runOperate(b, a, oper));

            }
            //pop the open parenthesis from the stack
            operate.pop();

        }

        //check if the token is an operator
        else if(isOperator(str[0]))
        {

            //if there are no operators on the operator stack
            //push the current token
            if(operate.empty())
            {
                operate.push(str[0]);
            } //endif

            else
            {
                //if there are operators on the stack,
                //we will need to compare precedences
                int pres = precedence(str[0]);

                //while the precedence of the operator on top of the operate stack is greater than the token's
                //perform the operations in the stack
                while(precedence(operate.top()) > pres)
                {

                    char oper = operate.top();
                    operate.pop();

                    //if there are no operands to operate on, then the input wasnt correctly formatted
                    if(operand.empty())
                    {
                        cout<<"invalid input"<<endl;
                        return(7);
                    }

                    double a = operand.top();
                    operand.pop();

                    //if there are no operands to operate on, then the input wasnt correctly formatted
                    if(operand.empty())
                    {
                        cout<<"invalid input"<<endl;
                        return(8);
                    }

                    double b = operand.top();
                    operand.pop();

                    //if we can get all the operands, perform the operation, and push it onto the operand stack
                    operand.push(runOperate(b, a, oper));

                    //if we reach the bottom of the stack, break from the loop so we can push the token
                    if(operate.empty()) break;
                }

                //push the token
                operate.push(str[0]);
            }
        }
    }

    //when we are all out of tokens, perform the remaining operations on the stacks.
    while(!operate.empty())
    {

        char oper = operate.top();
        operate.pop();

        //if there are no operands to operate on, then the input wasnt correctly formatted
        if(operand.empty())
        {
            cout<<"invalid input"<<endl;
            return(3);
        }
        double a = operand.top();
        operand.pop();

        //if there are no operands to operate on, then the input wasnt correctly formatted
        if(operand.empty())
        {
            cout<<"invalid input"<<endl;
            return(3);
        }

        double b = operand.top();
        operand.pop();

        //perform operation and push back onto stack
        operand.push(runOperate(b, a, oper));


    }
    double answer;
    if(operand.empty())
    {
        //if there are no operands left on the stack, then there is an error.
        cout << "error" << endl;
        return(4);
    }
    else
    {
        //get the answer from the top of the stack after all operations are performed
        answer = operand.top();
        operand.pop();

    }

    if(!operand.empty())
    {

        //if there is still something left on the stack after all operations are performed and answer is retrieved
        //the input was not formatted correctly

        cout <<"invalid input" << endl;
        return(5);
    }

    else
    {

        cout << argument << " = " << answer << endl;

    }

    return 0;

}

//run given operation "operate" on a and b
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
        //if what was inputted wasnt an operand, exit the code
        cout<<"invalid argument" << endl;
        exit(2);
        break;
    }

}

//get the precedence of the operator
int precedence(char operate)
{
    int x;

    switch(operate)
    {
    case '+':           // addition and subtraction have the least precedence
    case '-':
        x = 1;
        break;
    case '*':
    case '/':
        x = 1;
        break;
    case '^':
        x = 3;          //exponentiation has the most precedence
        break;
    case '(':
        x = 0;
        break;
    default :           //open parentheses it technically not an operator, and has zero precedence
        x = -1;         //if it is a non mathmatical symbol, give negative precedence at an error indicator
        break;
    }

    return x;
}

//check if the character is an operator
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


//return a string that is formatted with spaces so it can be tokenized using a space as the delimiter
string formatString(string str)
{
    string newString = "";

    for(int i = 0; i <(int) str.length(); i++)
    {

        char c = str.at(i);
        //if it is an operator, add it to the string padded with spaces
        if(c == '+' || c == '/' || c == '*' || c == '^' || c == '(' || c == ')')
        {

            newString = newString + ' ' + c + ' ';

        }

        // if a '-' is inputted it could be either a negative sign or a minus, so we have to figure out which it might be
        else if(str.at(i) == '-')
        {
            //if the hyphen is the first character it is a negative, unless the equation isnt formatted right, in which case,
            //it will be dealt with later
            if(i == 0){


                newString = newString + '-';
            }
            else if(i < (int) str.length()-1)
            {
                //if the character before it is not a digit, and the thing after it is a digit, it must be a minus
                if(!isdigit(str.at(i-1)) && isdigit(str.at(i+1)))
                {

                    newString = newString + ' ' + '-';

                }
                //if the char before it is a digit and the char after it is a digit or another hyphen or a space, it is a minus
                else if(isdigit(str.at(i-1)) &&( (isdigit(str.at(i + 1)) || str.at(i+1)== '.')|| str.at(i+1)=='-' || str.at(i+1) == ' '))
                {

                    newString = newString + ' ' + '-' + ' ';

                }

            }//if the characters before and after it are spaces, it is a minus
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
