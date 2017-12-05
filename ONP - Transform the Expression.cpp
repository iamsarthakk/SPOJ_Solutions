/*ONP - Transform the Expression
#stack
Transform the algebraic expression with brackets into RPN form (Reverse Polish Notation). Two-argument operators: +, -, *, /, ^ (priority from the lowest to the highest), brackets ( ). Operands: only letters: a,b,...,z. Assume that there is only one RPN form (no expressions like a*b*c).

Input
t [the number of expressions <= 100]
expression [length <= 400]
[other expressions]
Text grouped in [ ] does not appear in the input file.

Output
The expressions in RPN form, one per line.
Example
Input:
3
(a+(b*c))
((a+b)*(z+x))
((a+t)*((b+(a+c))^(c+d)))

Output:
abc*+
ab+zx+*
at+bac++cd+^* */
#include <bits/stdc++.h>
 
    #define max1(x,y) (x)>(y)?(x):(y)
     
    #define s(n) scanint(n)
    #define sc(n) scanf(" %c",&n)
     #define sl(n) scanf("%ld",&n)
    #define sll(n) scanf("%lld",&n)
    #define sf(n) scanf("%lf",&n)
    #define ss(n) scanf("%s",n)
    #define INF (int)1e9
    #define EPS 1e-9
    #define bitcount __builtin_popcount
    #define gcd __gcd
    #define forall(i,a,b) for(int i=a;i<b;i++)
    #define all(a) a.begin(), a.end()
    #define pb push_back
    #define sz(a) ((int)(a.size()))
    #define mp make_pair
    #define checkbit(n,b) ( (n >> b) & 1)
    #define gc getchar_unlocked
    #define l long
  
    using namespace std ;

    inline void scanint(int &x)
    {
    register int c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
    }
  // Function to convert Infix expression to postfix 
string InfixToPostfix(string expression);

// Function to verify whether an operator has higher precedence over other
int HasHigherPrecedence(char operator1, char operator2);

// Function to verify whether a character is operator symbol or not. 
bool IsOperator(char C);

// Function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not. 
bool IsOperand(char C);

int main() 
{
 string expression; 
 
 int t;
 s(t);
 while(t--){
 getline(cin,expression);
 string postfix = InfixToPostfix(expression);
 cout<<postfix<<"\n";
 }
}

// Function to evaluate Postfix expression and return output
string InfixToPostfix(string expression)
{
 // Declaring a Stack from Standard template library in C++. 
 stack<char> S;
 string postfix = ""; // Initialize postfix as empty string.
 for(int i = 0;i< expression.length();i++) {

  // Scanning each character from left. 
  // If character is a delimitter, move on. 
  if(expression[i] == ' ' || expression[i] == ',') continue; 

  // If character is operator, pop two elements from stack, perform operation and push the result back. 
  else if(IsOperator(expression[i])) 
  {
   while(!S.empty() && S.top() != '(' && HasHigherPrecedence(S.top(),expression[i]))
   {
    postfix+= S.top();
    S.pop();
   }
   S.push(expression[i]);
  }
  // Else if character is an operand
  else if(IsOperand(expression[i]))
  {
   postfix +=expression[i];
  }

  else if (expression[i] == '(') 
  {
   S.push(expression[i]);
  }

  else if(expression[i] == ')') 
  {
   while(!S.empty() && S.top() !=  '(') {
    postfix += S.top();
    S.pop();
   }
   S.pop();
  }
 }

 while(!S.empty()) {
  postfix += S.top();
  S.pop();
 }

 return postfix;
}

// Function to verify whether a character is english letter or numeric digit. 
// We are assuming in this solution that operand will be a single character
bool IsOperand(char C) 
{
 if(C >= '0' && C <= '9') return true;
 if(C >= 'a' && C <= 'z') return true;
 if(C >= 'A' && C <= 'Z') return true;
 return false;
}

// Function to verify whether a character is operator symbol or not. 
bool IsOperator(char C)
{
 if(C == '+' || C == '-' || C == '*' || C == '/' || C== '^')
  return true;

 return false;
}

// Function to verify whether an operator is right associative or not. 
int IsRightAssociative(char op)
{
 if(op == '^') return true;
 return false;
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence. 
int GetOperatorWeight(char op)
{
 int weight = -1; 
 switch(op)
 {
 case '+':
 case '-':
  weight = 1;
 case '*':
 case '/':
  weight = 2;
 case '^':
  weight = 3;
 }
 return weight;
}

// Function to perform an operation and return output. 
int HasHigherPrecedence(char op1, char op2)
{
 int op1Weight = GetOperatorWeight(op1);
 int op2Weight = GetOperatorWeight(op2);

 // If operators have equal precedence, return true if they are left associative. 
 // return false, if right associative. 
 // if operator is left-associative, left one should be given priority. 
 if(op1Weight == op2Weight)
 {
  if(IsRightAssociative(op1)) return false;
  else return true;
 }
 return op1Weight > op2Weight ?  true: false;
}
