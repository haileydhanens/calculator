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




