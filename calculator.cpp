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

int status; //1 for numbers, 2 for others

};

bool isNumber(char a){ // checks if char is number and returns bool
switch(a){
    case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '0':
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

//12+5*6/2+21+(21+5)*2
Token compute(vector<Token> expression){
int answer=1;
for(int i=0;i<expression.size();++i){
    Token token=expression[i];
switch(checkToken(token)){
    case 0: //number
    answer*=token.intVal;
    break;

    case 1:// operation
    switch(token.op){
        case '*':
        answer *= expression[++i].intVal;
        break;
        case '/':
        answer /= expression[++i].intVal;
        break;
    }
}
}
Token retoken;
retoken.intVal=answer;
retoken.isNumber=true;
return retoken;             //tokenise answer and return
}

vector<Token> eliminater(vector<Token> tokens){ // ifadeni sadelesdirir vurma bolme () leri hesablayir 1+2*3+6/2+5
vector<Token> finalTokens=tokens;
int insertIndex;
for(int i=0;i<tokens.size();++i){
    Token token=tokens[i];
    if(checkToken(token)==1){ //is operation
        insertIndex=i-1; // determining where to insert answer of expression 2
        if(token.op=='*'|token.op=='/'){
            
            cout<<"\n IN"<<token.op<<"OPOP"<<i;
            vector<Token> expression;
            for(int a=i-1;a<tokens.size();++a){ //izolate * / equation and calculate then insert
            cout<<"\n G "<<a;
            if(tokens[a].op=='+'||tokens[a].op=='-'){
                // compute expression and insert
                cout<<"\n computed expression "<<compute(expression).intVal<<" "<<insertIndex;
                finalTokens.insert(finalTokens.begin()+ insertIndex,compute(expression));

                for(Token token:finalTokens){ //1+6+1
        
            cout<<"\n FINALtokens"<<token.intVal<<" "<<token.op;
        
    }
                // eliminater(finalTokens); 
                return finalTokens;
                
            }else{
            expression.push_back(tokens[a]);
            finalTokens.erase(finalTokens.begin()+ insertIndex);// erasing expression BUGG silinen zaman listin olcusu deyisir
            cout<<"\n AAAAASSSSSerased index";
            }


            }

            }
    }
}
cout<<"\n insert index"<<insertIndex;


}
int calculate(vector<Token> tokens){
    int sum=0;
    //call eliminater then just add and subtrack here
    for(Token token:tokens){
        
            //cout<<"\n CHECK "<<token.intVal<<" "<<token.op<<" "<<tokens.size();
        
    }

    for(int i=0;i<tokens.size();++i){        // 1+6+1
        
        Token token=tokens[i];
        //cout<<"Token check "<<token.op<<" "<<token.intVal<<" "<<tokens.size();
        switch(checkToken(token)){
            case 0: //number
            //cout<<"\n tokenVal : "<<token.intVal;
            sum+=token.intVal;
            break;
            case 1: //Operator
            //cout<<"\n tokenOp : "<<token.op;
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
bool checkForExpression(vector<Token> tokens){ // returns true if given token vector contains any * / operation
    for(Token token:tokens){
        if(token.isop){
            if(token.op=='*'||token.op=='/'){
                return true;
            }
        }
    }

}

int main(){ // MAINNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

    vector<Token> tokens;
    char ch;

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

//vector<Token> tokenVector=tokens;
while(true){
    if(checkForExpression(tokens)){
tokens=eliminater(tokens);
}else break;
}

cout<<"\n ="<<calculate(tokens)<<"= ";  //vurma bolme expressionlari hell olunub yerine salindiqdan sonra toplama cixma calculate gonderilir

for(Token token:tokens){
        
            cout<<"\n tokens"<<token.intVal<<" "<<token.op;
        
    }




}
