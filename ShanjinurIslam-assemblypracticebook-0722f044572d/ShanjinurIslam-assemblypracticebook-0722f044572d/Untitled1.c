#include<stdio.h>
int main()
{
    int j=100;
    int sum=0;
    while(j>=5)
    {
        sum=sum+j;
        j=j-5;
    }
    printf("\n%d",sum);

    return 0;
}
