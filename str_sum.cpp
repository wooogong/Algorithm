#include<iostream>

using namespace std;

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

void str_sum(char* s1, char* s2, char* out){
    stk stk1;
    stk stk2;
    stk ans;

    bool minus = false;

//    if(*s1 == '-' and *s2 != '-'){
//        s1++;
//        return str_sub(s2, s1, out);
//    }
//    
//    if(*s1 != '-' and *s2 == '-'){
//        s2++;
//        return str_sub(s1, s2, out);
//    }

    if(*s1 == '-' and *s2 == '-'){
        s1++; s2++; minus = true;
    }

    while(*s1 != 0)
        stk1.push(*s1++ - '0');

    while(*s2 != 0)
        stk2.push(*s2++ - '0');

    int carry = 0;
    while(!stk1.isempty() and !stk2.isempty()){
        int num1 = stk1.pop();
        int num2 = stk2.pop();
        int tmp = num1 + num2 + carry;
        if(tmp >= 10){
            carry = 1;
            tmp -= 10;
        }
        else{
            carry =0;
        }
        ans.push(tmp);
    }

    while(!stk1.isempty()){
        int tmp = stk1.pop() + carry;
        if(tmp >= 10){
            carry = 1;
            tmp -= 10;
        }
        else
            carry = 0;
        ans.push(tmp);
    }

    while(!stk2.isempty()){
        int tmp = stk2.pop() + carry;
        if(tmp >= 10){
            carry = 1;
            tmp -= 10;
        }
        else
            carry = 0;
        ans.push(tmp);
    }

    if(carry) ans.push(carry);
    if(minus) *out++ = '-';

    while(!ans.isempty())
        *out++ = ans.pop()+'0';
    *out = 0;
}

int main(void){
    char s1[] = "-1234678901234567890";
    char s2[] = "-2345";
    char out[1000];

    str_sum(s1, s2, out);

    cout<<out<<endl;
    return 0;
}
