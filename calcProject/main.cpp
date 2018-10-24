#include <iostream>
#include <stack>

using namespace std;

void inToPost(stack <int> myStack, char* str);
int calcPost(stack <int> myStack);

int main(int argc, char** argv){

    if(argc != 2){
        cout< < "invalid input" << endl;
        exit(1);
        }

    stack <int> s;
    char* str = argv[1];
    inToPost(s, str);

    return 0;
    }


void inToPost(stack <int> myStack, char* str){
    int i = 0;
    while(str[i] != '\0'){
        //infix to prefix algo: https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/
    }
}
int calcPost(stack <int> myStack){

    //dummy return
    return 5;
}
