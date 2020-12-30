#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

class Token{
public:

int intVal;
bool isNumber=false;

char op;
bool isop=false;

bool iscomplex=false;
vector<Token> ops;

int status; //1 for numbers, 2 for others

};

bool isNumber(char a){ // checks if char is number and returns bool
switch(a){
    case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '0':
    cout<<"\n "<<a<<" is number";
    return true;
    }
    return false;

}

int chartoInt(char digit){

return (int)(digit-'0');
}

int chartoInt(vector<char> digits){   // Takes char vector transforms to int value '1','2' to 12
if(digits.size()==1) return (int)(digits[0]-'0');
int digit=0;
for(int i=0;i<digits.size();++i){
digit+=chartoInt(digits[i])*pow(10,digits.size()-i-1);
}
return digit;
}

Token tokeniseNumber(char number){
    Token token;
    vector<char> charDigits;
    int intVal;
    
    charDigits.push_back(number);
    while(true){
         //cout<<isNumber(cin.peek());
    if(isNumber(cin.peek())){
        
        charDigits.push_back(cin.get());
        
    }else{break;}

    }
intVal=chartoInt(charDigits);
token.isNumber=true;
token.intVal=intVal;
return token;

}

Token tokeniseOperator(char op){
    Token token;
    token.op=op;
    token.isop=true;
    return token;

}
int checkToken(Token token){
    if(token.isNumber) return 0;
    if(token.isop) return 1;

}
int calculate(vector<Token> tokens){
    int sum=0;
    for(int i=0;i<tokens.size();++i){
        Token token=tokens[i];
        switch(checkToken(token)){
            case 0: //number
            sum+=token.intVal;
            break;
            case 1: //Operator
            switch(token.op){
                case '+':
                sum+=tokens[++i].intVal;
                break;
                case '-':
                sum-=tokens[++i].intVal;
                break;

            }


        }

    }
return sum;
}


int main(){ // MAINNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

    vector<Token> tokens;
    char ch;
    cout<<chartoInt({'1','2'})<<" baby ";
    
    // tokenising starts
    while(cin>>ch){ // if number, if bugger, if operation +-/*
    if(ch =='x') break;
    switch(ch){
        case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '0':
        tokens.push_back(tokeniseNumber(ch)); //adding number to token list
        break;
        case '+':case '-':case '*':case '/':case '(':case ')':
        tokens.push_back(tokeniseOperator(ch)); //adding operator to token list
}
//tokenising ends
//time to calculate


    
}
cout<<"\n ="<<calculate(tokens);
cout<<"\n out";
for(Token token:tokens){
        
            cout<<token.intVal<<"\n";
        
    }




}
