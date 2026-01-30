#include<stdio.h>
int main()
{
    float amount,rate,payment,balance;
    printf("Enter amout of loan:");
    scanf("%f",&amount);
    printf("Enter interest rate:");
    scanf("%f",&rate);
    printf("Enter monthly payment:");
    scanf("%f",&payment);
    balance=amount-payment+amount*(rate/100/12);
    printf("Balance remaining after first payment: $%.2f\n",balance);
    balance=balance-payment+balance*(rate/100/12);
    printf("Balance remaining after second payment: $%.2f\n",balance);
    balance=balance-payment+balance*(rate/100/12);
    printf("Balance remaining after third payment: $%.2f\n",balance);

}