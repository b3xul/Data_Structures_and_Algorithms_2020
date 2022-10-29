
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*void upcase(char *s)
{
    while (*s)
    {
        *s = toupper(*s);
        s++;
    }
}*/
void bar(int n){
    if(n<=2) return;
    if(n%2==0)
        printf("B");
    else
        printf("A");
    bar(n/2+((n+1*2%3==0)?1:0));

}

void foo(int** a){
    int i;
    for(i=0;i<3;i++)
        (*a)++;
}
void bar2(int* a){
    foo(&a);
    printf("%d\n",*(a+1));
}


int main(void)
{
    /*int sig;
    for (sig = 1; sig < NSIG; sig++)
    {
        char *str = strdup(sys_signame[sig]);
        if (!str)
            return -1;

        upcase(str);
        printf("%2d -> SIG%s\n", sig, str);

        free(str);
    }*/

    bar(24);

    int data[4]={ 1, 2, 3, 4 };
    bar2(data);

    //void* (*[10])(*x)(int);

    char b=1;
    while(b<127){
        //printf("%u\n", (unsigned int)b);
        b++;
    }

    const char* s="casa";
    unsigned cnt=0;

    //while (s[cnt++]);
    while (*s++) cnt++;
    //printf("%d",cnt);

    int i,k;
    float sum1,sum2;
    for(k=0, sum1=0, i=0;i<=2019;i++){
        sum1+=i;
        k++;
    }
    printf("k= %d sum = %f\n",k,(float)sum1/k);
    for(k=0, sum2=0, i=1;i<=4038;i++){
        sum2+=i;
        k++;
    }
    printf("k= %d sum = %f\n",k,(float)sum2/k);
    printf("sum = %f",(sum1/k+sum2/k)/2);
    return 0;
}
