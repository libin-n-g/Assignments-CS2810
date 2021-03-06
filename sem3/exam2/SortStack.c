
/*AUTHOR:LIBIN N GEORGE
 * ROLL NO :111501015
 * Lab Interim Evaluation 1 - Q2
 * Recursion Elimination by Stack
 * Program for sorting numbers
 */
#include<stdio.h>
#include<stdlib.h>

struct snapshot
{
    int nStage;
    int n,n1;            //n1 is used as the return value at each call of function
    struct snapshot* link;
};

typedef struct snapshot* Snapshot;

int sort(int *, int);
Snapshot AllocateMemory();

int main()
{

   int n, a[50], i, result;
   printf("Give n \n");
   scanf("%d", &n);
   printf("Give array elements \n");
   for(i=0; i<n;i++)
        scanf("%d", &a[i]);
   result=sort(a, n);
   printf("Sorted List is \n");
   for(i=0; i<n;i++)
        printf("%d ", a[i]);
   printf("\nNumber of comparisions done is %d \n", result);
   return 0;
}

int sort(int *a, int n)
{
   int i,t,RetVal;
   Snapshot CurrentSnapshot,NewSnapshot,Stacktop;

   CurrentSnapshot = AllocateMemory();

   CurrentSnapshot->n=n;
   CurrentSnapshot->nStage=0;
   CurrentSnapshot->n1=0;
   CurrentSnapshot->link=NULL;

   Stacktop=CurrentSnapshot;

   while(Stacktop!=NULL)
   {
       CurrentSnapshot=Stacktop;
       Stacktop=CurrentSnapshot->link;

       switch (CurrentSnapshot->nStage)
       {
       case 0:                 //upto calling of Recursive function
           if(CurrentSnapshot->n<=1)
           {
               CurrentSnapshot->n1=0;
               RetVal=CurrentSnapshot->n1; //n1 is Return value after each call
               free(CurrentSnapshot);
               continue;
           }
           else
           {
               CurrentSnapshot->nStage=1;

               NewSnapshot=AllocateMemory();

               NewSnapshot->n=CurrentSnapshot->n-1;
               NewSnapshot->nStage=0;
               NewSnapshot->n1=0;
               NewSnapshot->link=CurrentSnapshot;

               Stacktop=NewSnapshot;
               continue;
           }
           break;
       case 1:                                  //After returning from function
           CurrentSnapshot->n1=RetVal+CurrentSnapshot->n1;

           t=a[CurrentSnapshot->n-1];
           i=CurrentSnapshot->n-1;
           for (i=CurrentSnapshot->n-1;i>0;i--)
           {
                CurrentSnapshot->n1++;
                if (a[i-1]>t)
                    a[i]=a[i-1];
                else
                    break;
           }
           a[i]=t;

           RetVal=CurrentSnapshot->n1;

           Stacktop=CurrentSnapshot->link;
           free(CurrentSnapshot);

           continue;
           break;
       default:
           break;
       }
   }
   return RetVal;
}
//allocate memory for structure
Snapshot AllocateMemory()
{
    Snapshot pointer;
    pointer=(Snapshot)malloc(sizeof (struct snapshot));
    if(pointer!=NULL)
    {
        return pointer;
    }
    else
    {
        printf("ERROR:MEMORY NOT ALLOCATED\n");
        return NULL;
    }
}
