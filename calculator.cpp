#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Token
{
public:
    int intVal;
    bool isNumber = false;

    char op;
    bool isop = false;
};

bool isNumber(char a)
{ // checks if char is number and returns bool
    switch (a)
    {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
        return true;
    }
    return false;
}

int chartoInt(char digit)
{ // in->char out->int
    return (int)(digit - '0');
}

int chartoInt(vector<char> digits)
{ // Takes char vector transforms to int value '1','2' to 12
    if (digits.size() == 1)
        return (int)(digits[0] - '0');
    int digit = 0;
    for (int i = 0; i < digits.size(); ++i)
    {
        digit += chartoInt(digits[i]) * pow(10, digits.size() - i - 1);
    }
    return digit;
}

Token tokeniseNumber(char number)
{ // Takes char value of int and tokenises it as int and returns token
    Token token;
    vector<char> charDigits;
    int intVal;

    charDigits.push_back(number);
    while (true)
    {
        //cout<<isNumber(cin.peek());
        if (isNumber(cin.peek()))
        {

            charDigits.push_back(cin.get());
        }
        else
        {
            break;
        }
    }
    intVal = chartoInt(charDigits);
    token.isNumber = true;
    token.intVal = intVal;
    return token;
}

Token tokeniseOperator(char op)
{ // takes char and tokenises it as operator and returns token
    Token token;
    token.op = op;
    token.isop = true;
    return token;
}

int checkToken(Token token)
{
    if (token.isNumber)
        return 0;
    if (token.isop)
        return 1;
}

//12+5*6/2+21+(21+5)*2
Token computeMD(vector<Token> expression)
{ // only computes multiplaction an division
    int answer = 1;
    for (int i = 0; i < expression.size(); ++i)
    {
        Token token = expression[i];
        switch (checkToken(token))
        {
        case 0: //number
            answer *= token.intVal;
            break;

        case 1: // operation
            switch (token.op)
            {
            case '*':
                answer *= expression[++i].intVal;
                break;
            case '/':
                if (expression[++i].intVal == 0)
                { //added divide zero checker
                    cout << " NO DIVIDE TO ZERO";
                    exit(1);
                }
                answer /= expression[++i].intVal;
                break;
            }
        }
    }
    Token retoken;
    retoken.intVal = answer;
    retoken.isNumber = true;

    return retoken; //tokenise answer and return
}

vector<Token> eliminateOneMD(vector<Token> tokens)
{ // ifadeni sadelesdirir vurma bolme () leri hesablayir 1+2*3+6/2+5 2*3
    vector<Token> finalTokens = tokens;
    int insertIndex;
    for (int i = 0; i < tokens.size(); ++i)
    {
        Token token = tokens[i];
        if (checkToken(token) == 1)
        {                        //is operation
            insertIndex = i - 1; // determining where to insert answer of expression 2
            if (token.op == '*' | token.op == '/')
            {

                vector<Token> expression;

                for (int a = i - 1; a < tokens.size(); ++a)
                { //izolate * / equation and computePM then insert

                    if (tokens[a].op == '+' | tokens[a].op == '-' | a == tokens.size() - 1)
                    {
                        // computeMD expression and insert
                        if (a == tokens.size() - 1)
                        {
                            expression.push_back(tokens[a]);
                            finalTokens.erase(finalTokens.begin() + insertIndex);
                        }

                        finalTokens.insert(finalTokens.begin() + insertIndex, computeMD(expression));

                        return finalTokens;
                    }
                    else
                    {
                        expression.push_back(tokens[a]);
                        finalTokens.erase(finalTokens.begin() + insertIndex); // erasing expression BUGG silinen zaman listin olcusu deyisir
                    }
                }
            }
        }
    }
}

int computePM(vector<Token> tokens)
{ // only computes plus and minus expressions
    int sum = 0;
    //call eliminateOneMD then just add and subtrack here

    for (int i = 0; i < tokens.size(); ++i)
    { // 1+6+1

        Token token = tokens[i];
        if (tokens.size() == 0)
        {
            sum = tokens[i].intVal;
            return sum;
        }
        //cout<<"Token check "<<token.op<<" "<<token.intVal<<" "<<tokens.size();
        switch (checkToken(token))
        {
        case 0: //number
            //cout<<"\n tokenVal : "<<token.intVal;
            sum += token.intVal;
            break;
        case 1: //Operator
            //cout<<"\n tokenOp : "<<token.op;
            switch (token.op)
            {
            case '+':
                sum += tokens[++i].intVal;
                break;
            case '-':
                sum -= tokens[++i].intVal;
                break;
            }
        }
    }

    return sum;
}

bool checkForMDOperation(vector<Token> tokens)
{ // returns true if given token vector contains any * / operation
    for (Token token : tokens)
    {
        if (token.isop)
        {
            if (token.op == '*' || token.op == '/')
            {
                return true;
            }
        }
    }
}
vector<Token> eliminateAllMD(vector<Token> tokens)
{ // Eliminates all multiplaction and division operations on expression
    vector<Token> finaltokens = tokens;
    while (checkForMDOperation(finaltokens))
    {
        finaltokens = eliminateOneMD(finaltokens);
    }
    return finaltokens;
}

vector<Token> eliminateOneP(vector<Token> tokens, int parantheseIndex);

int searchTokenVector(vector<Token> tokens, int a, int b)
{ //not optimised. Search list for ( operator and return index from a to b | [a,b]
    for (int i = a; i < b; ++i)
    {
        Token t = tokens[i];
        if (t.op == '(')
        {

            return i;
        }
    }
}

vector<Token> eliminateOneP(vector<Token> tokens, int parantheseIndex)
{ //1+(2+3)*2=11      1+(2*(2+4)*4)=49

    vector<Token> expressionTokens;
    vector<Token> finaltokens = tokens;
    int insertIndex;
    for (int i = parantheseIndex; i < tokens.size(); ++i)
    {
        if (checkToken(tokens[i]) == 1)
        { //enters if operator

            if (tokens[i].op == '(')
            {

                insertIndex = i;

                finaltokens.erase(finaltokens.begin() + insertIndex); //deleted first paranthese (

                for (int a = i + 1; a < tokens.size(); ++a)
                {

                    if (tokens[a].op == '(')
                    { // if new paranthes then compute it and return
                        return eliminateOneP(tokens, searchTokenVector(tokens, a, tokens.size()));
                    }

                    if (tokens[a].op == ')')
                    {

                        finaltokens.erase(finaltokens.begin() + insertIndex); //deleted last paranthese )

                        expressionTokens = eliminateAllMD(expressionTokens); // expression is clear from * / operators
                        int answer = computePM(expressionTokens);            // calculated expression inside parantheses
                        Token tokenA;
                        tokenA.intVal = answer;
                        tokenA.isNumber = true;
                        finaltokens.insert(finaltokens.begin() + insertIndex, tokenA);

                        return finaltokens;
                    }
                    else
                    {
                        expressionTokens.push_back(tokens[a]);                // adding tokens inside parantheses to expressionTokens list
                        finaltokens.erase(finaltokens.begin() + insertIndex); // erasing from tokens after adding. Planning to insert int value of erased expression
                    }
                }
            }
        }
    }
}

bool checkForP(vector<Token> tokens)
{ // checks if token vector contains any ( )
    for (Token token : tokens)
    {
        if (token.isop)
        {
            if (token.op == '(')
                return true;
        }
    }
    return false;
}

vector<Token> eliminateAllP(vector<Token> tokens)
{ // solves all paranthese expression and inserts it at right place then returns vector
    vector<Token> finaltokens = tokens;
    while (checkForP(finaltokens))
    { //checking for paranthese operator
        finaltokens = eliminateOneP(finaltokens, searchTokenVector(finaltokens, 0, finaltokens.size()));
    }
    return finaltokens;
}

int calculateExpression(vector<Token> tokens)
{ // calculates Expressions of all kind
    vector<Token> finalTokens = tokens;
    finalTokens = eliminateAllP(finalTokens);
    finalTokens = eliminateAllMD(finalTokens);
    return computePM(finalTokens);
}

int main()
{ // MAINNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

    vector<Token> tokens;
    char ch;

    // tokenising starts
    while (cin >> ch)
    { // if number, if bugger, if operation +-/*
        if (ch == 'x')
            break;
        switch (ch)
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            tokens.push_back(tokeniseNumber(ch)); //adding number to token list
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
            tokens.push_back(tokeniseOperator(ch)); //adding operator to token list
        }
        //tokenising ends time to computePM
    }

    // for(Token token:tokens){

    //             cout<<"\n TTokens"<<token.intVal<<" "<<token.op;

    //     }

    cout << "\n =" << calculateExpression(tokens) << "= "; //vurma bolme expressionlari hell olunub yerine salindiqdan sonra toplama cixma computePM gonderilir
}
