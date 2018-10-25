#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

double operate(double a, double b, char operate);
int precedence(char operate);

int main(int argc, char** argv){

    stack<char> operate;
    stack<double> operand;
    stringstream stream(argv[1]);

    string str;
    while(getline(check1, str, ' ')){

    }




    return 0;
}


double operate(double a, double b, char operate);
int precedence(char operate);
