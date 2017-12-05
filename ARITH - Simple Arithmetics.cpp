/*ARITH - Simple Arithmetics
no tags 
One part of the new WAP portal is also a calculator computing expressions with very long numbers. To make the output look better, the result is formated the same way as is it usually used with manual calculations.

Your task is to write the core part of this calculator. Given two numbers and the requested operation, you are to compute the result and print it in the form specified below. With addition and subtraction, the numbers are written below each other. Multiplication is a little bit more complex: first of all, we make a partial result for every digit of one of the numbers, and then sum the results together.

Input
There is a single positive integer T on the first line of input (equal to about 1000). It stands for the number of expressions to follow. Each expression consists of a single line containing a positive integer number, an operator (one of +, - and *) and the second positive integer number. Every number has at most 500 digits. There are no spaces on the line. If the operation is subtraction, the second number is always lower than the first one. No number will begin with zero.

Output
For each expression, print two lines with two given numbers, the second number below the first one, last digits (representing unities) must be aligned in the same column. Put the operator right in front of the first digit of the second number. After the second number, there must be a horizontal line made of dashes (-).

For each addition or subtraction, put the result right below the horizontal line, with last digit aligned to the last digit of both operands.

For each multiplication, multiply the first number by each digit of the second number. Put the partial results one below the other, starting with the product of the last digit of the second number. Each partial result should be aligned with the corresponding digit. That means the last digit of the partial product must be in the same column as the digit of the second number. No product may begin with any additional zeros. If a particular digit is zero, the product has exactly one digit -- zero. If the second number has more than one digit, print another horizontal line under the partial results, and then print the sum of them.

There must be minimal number of spaces on the beginning of lines, with respect to other constraints. The horizontal line is always as long as necessary to reach the left and right end of both numbers (and operators) directly below and above it. That means it begins in the same column where the leftmost digit or operator of that two lines (one below and one above) is. It ends in the column where is the rightmost digit of that two numbers. The line can be neither longer nor shorter than specified.

Print one blank line after each test case, including the last one.

Example
Sample Input:

4
12345+67890
324-111
325*4405
1234*4

Sample Output:

 12345
+67890
------
 80235

 324
-111
----
 213

    325
  *4405
  -----
   1625
     0
 1300
1300
-------
1431625

1234
  *4
----
4936
*/
#include <iostream>  
#include <stdlib.h>  
#include <string.h>  
#define END_LINE system("pause")  
void calc(char op);  
void calc_plus(char op);  
void calc_mulity();  
int num[2][512];  
int result[2048];  
int len[3];  
int mul_result[512][512];  
int mul_len[512];  
  
void zero_memory() {  
    memset(num,0,sizeof(num));  
    memset(len,0,sizeof(len));  
    memset(result,0,sizeof(result));  
    memset(mul_result,0,sizeof(mul_result));  
    memset(mul_len,0,sizeof(mul_len));  
}  
  
int main() {  
    char expression[1024],op;  
    int n,i,ex_len,tlen;  
    //freopen("d:\\stdin.txt","r",stdin);  
    //freopen("d:\\stdout.txt","w",stdout);  
    scanf("%d",&n);  
    getchar();  
    while( n-- ) {  
        zero_memory();  
        scanf("%s",expression);  
        ex_len = strlen(expression);  
        i = ex_len - 1;  
        tlen = 0;  
        while(expression[i] >= '0' && expression[i] <= '9') {  
            num[1][tlen++] = expression[i]-'0';  
            i--;  
        }  
        len[1] = tlen;  
        op = expression[i--];  
        tlen = 0;  
        while( i>= 0 ) {  
            num[0][tlen++] = expression[i--]-'0';  
        }  
        len[0] = tlen;  
        calc(op);  
        printf("\n");  
    }  
    END_LINE;  
    return 0;  
}  
  
void calc(char op) {  
    if( op == '+' || op == '-' ) {  
        calc_plus(op);  
    } else {  
        calc_mulity();  
    }  
}  
  
void calc_plus(char op) {  
    int max_len = len[0] > (len[1]+1) ? len[0] : (len[1]+1);  
    int tlen = max_len - len[0];  
    int i,j,t,ti,flag = 0;  
      
    i = j = ti = 0;  
    if( op == '+') {  
        while( i < len[0] || j < len[1] ) {  
            t = num[0][i] + num[1][j];  
            result[ti] += t;  
            flag = result[ti] / 10;  
            result[ti] %= 10;  
            if( flag > 0 ) {  
                result[ti+1] ++;  
            }  
            i++,j++;  
            ti++;  
        }  
        if( result[ti] > 0 ) ti++;  
    } else {  
        while( i < len[0] || j < len[1] ) {  
            t = num[0][i] - num[1][j];  
            result[ti] += t;  
            flag = result[ti] < 0;  
            if( flag ) {  
                result[ti] = 10 + result[ti];  
                result[ti+1] --;  
            }  
            i++,j++;  
            ti++;  
        }  
        while( result[ti-1] == 0 && ti > 0 ) ti--;  
    }  
    len[2] = ti;  
    max_len = max_len > len[2] ? max_len : len[2];  
    tlen = max_len - len[0];  
    while(tlen--) {  
        printf(" ");  
    }  
    for(i=len[0] - 1; i >= 0; i--) {  
        printf("%d",num[0][i]);  
    }  
    printf("\n");  
    tlen = max_len - (len[1]+1);  
    while(tlen--) printf(" ");  
    printf("%c",op);  
    for(i=len[1]-1; i >= 0; i--) {  
        printf("%d",num[1][i]);  
    }  
    printf("\n");  
  
    j = len[2] > (len[1]+1) ? len[2] : (len[1]+1);  
    tlen = max_len - j;  
    while(tlen--)printf(" ");  
    for(i=0;i<j;i++)printf("-");  
    printf("\n");  
  
      
    tlen = max_len - len[2];  
    while( tlen --  ) printf(" ");  
    for(i=len[2]-1;i>=0;i--) {  
        printf("%d",result[i]);  
    }  
    printf("\n");  
  
}  
  
void calc_mulity() {  
    int i,j,step,t,tlen;  
    int flag;  
    int max_len,max_len2;  
    int zeroflag;  
    for(j=0; j < len[1]; j++){  
        tlen = 0;  
        flag = 0;  
        zeroflag = true;  
        for(i=0;i< len[0]; i++) {  
            t = num[0][i] * num[1][j];  
            mul_result[j][tlen] += t;  
            flag = mul_result[j][tlen] / 10;  
            mul_result[j][tlen] %= 10;  
            if( mul_result[j][tlen] > 0 ) zeroflag = false;  
            if( flag ) {  
                mul_result[j][tlen + 1] += flag;  
            }  
            tlen ++;  
        }  
        if( zeroflag && !flag) {  
            tlen = 1;  
        }  
        if(flag){  
            tlen++;  
        }  
        mul_len[j] = tlen;  
    }  
    tlen = 0;  
    for(step=0;step<len[1]+mul_len[len[1]-1]-1;step++) {  
        for(i=0;i<=step;i++) {  
            result[step] += mul_result[i][step-i];  
        }  
        flag = result[step] / 10;  
        result[step] %= 10;  
        j = step+1;  
        if ( flag > 0 )  
        {  
            result[j] += flag;  
            flag /= 10;  
            j++;  
        }  
        while(flag >= 10){  
            result[j] += flag % 10;  
            flag = flag /10;  
            j++;  
        }  
    }  
    len[2] = j;  
    max_len = len[2] > (len[1]+1) ? len[2] : (len[1] + 1);  
    max_len2 = len[0] > (len[1]+1) ? len[0] : (len[1] + 1);  
    tlen = max_len - len[0];  
    while(tlen--)printf(" ");  
    for(i=len[0]-1;i>=0;i--)printf("%d",num[0][i]);  
    printf("\n");  
      
    tlen = max_len - len[1] - 1;  
    while(tlen--)printf(" ");  
    printf("*");  
    for(i=len[1]-1;i>=0;i--)printf("%d",num[1][i]);  
    printf("\n");  
      
    j    = ( len[1] + 1 ) > mul_len[0] ? (len[1]+1) : mul_len[0];  
    tlen = max_len - j;  
    while(tlen--)printf(" ");  
    for(i=0;i<j;i++)printf("-");  
  
    printf("\n");  
    for(step = 0;step<len[1];step++) {  
        tlen = max_len - mul_len[step] - step;  
        while(tlen--) printf(" ");  
        for(i=mul_len[step]-1;i>=0;i--) {  
            printf("%d",mul_result[step][i]);  
        }  
        printf("\n");  
    }  
    if( len[1] > 1 ) {  
        j = len[2] > mul_len[len[1]-1] ? len[2] : mul_len[len[1]-1];  
        tlen = max_len - len[2];  
        while(tlen--) printf(" ");  
        for(i=0;i<j;i++)  
        {  
            printf("-");  
        }  
        printf("\n");  
        tlen = max_len - len[2];  
        while(tlen--) printf(" ");  
        for(i=len[2]-1;i>=0;i--)printf("%d",result[i]);  
        printf("\n");  
    }  
      
}  
