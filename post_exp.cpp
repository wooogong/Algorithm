#include<iostream>

using namespace std;

#define SEP '.'

struct stk{
    stk():ptr(0){}
    void push(char c){
        buf[ptr++] = c;
    }

    char pop(void){
        return buf[--ptr];
    }

    char front(void){
        return buf[ptr-1];
    }

    bool isempty(void){
        return ptr == 0;
    }

    int size(void){
        return ptr;
    }

    char buf[1000];
    int ptr;
};

struct que{
    que():head(0), tail(0){}

    void push(char c){
        buf[head++] = c;
    }

    char pop(void){
        return buf[tail++];
    }

    bool isempty(void){
        return head == tail;
    }

    int size(void){
        return head - tail;
    }

    char buf[1000];
    int tail;
    int head;
};

void convpostexp(char* exp, char* out){
    int idx = 0;
    stk opstk;
    que postexp;

    while(exp[idx] != 0){
        if(exp[idx] == ' '){
            idx++;
            continue;
        }

        if(exp[idx] >= '0' and exp[idx] <= '9'){
            while(exp[idx] >= '0' and exp[idx] <= '9'){
                postexp.push(exp[idx++]);
            }
            postexp.push(SEP);
            continue;
        }

        if(exp[idx] == ')'){
            while(!opstk.isempty() and opstk.front() != '('){
                postexp.push(opstk.pop());
                postexp.push(SEP);
            }
            opstk.pop();
            idx++;
        }
        else if(exp[idx] == '('){
            opstk.push(exp[idx++]);
        }
        else if(exp[idx] == '/'){
            opstk.push(exp[idx++]);
        }
        else if(exp[idx] == '*'){
            while(!opstk.isempty() and opstk.front() == '/'){
                postexp.push(opstk.pop());
                postexp.push(SEP);
            }
            opstk.push(exp[idx++]);
        }
        else if(exp[idx] == '+'){
            while(!opstk.isempty() and opstk.front() != '(' and opstk.front() != '+'){
                postexp.push(opstk.pop());
                postexp.push(SEP);
            }
            opstk.push(exp[idx++]);
        }
        else if(exp[idx] == '-'){
            while(!opstk.isempty() and opstk.front() != '(' and opstk.front() != '-'){
                postexp.push(opstk.pop());
                postexp.push(SEP);
            }
            opstk.push(exp[idx++]);
        }
        else
            throw "op error";
    }

    while(!opstk.isempty()){
        postexp.push(opstk.pop());
        postexp.push(SEP);
    }

    while(!postexp.isempty()){
        *out++ = postexp.pop();
    }
    *out = 0;
}

int main(void){
    char exp[] = "5 * ( 2 + 3 ) / 4 + ( 3 - 1 )"; 
    char post[1000];
    convpostexp(exp, post);

    cout<<post<<endl;

    return 0;
}
