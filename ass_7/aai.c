#include <stdio.h>

int n, f;
int seq[100];
int p[50];
int hit = 0;
int i, j, k;
int pfCount = 0;

void input()
{
	printf("\n\tEnter the length of page reference sequence :");
	scanf("%d", &n);
	
	printf("\n\tEnter the page reference sequence :");
	for(i = 0; i < n; i++)
		scanf("%d", &seq[i]);
		
	printf("\n\tEnter the no. of frames : ");
	scanf("%d", &f);
}

void initialize()
{
    pfCount=0;
    for(i=0; i<f; i++)
        p[i]=9999;
}

int isHit(int data)
{
    hit = 0;
    for(j = 0; j < f; j++)
    {
        if(p[j] == data)
        {
            hit=1;
            break;
        }
    }
    return hit;
}

int getHitIndex(int data)
{
    int hIndex;
    for(k = 0; k < f; k++)
    {
        if(p[k] == data)
        {
            hIndex = k;
            break;
        }
    }
    return hIndex;
}

void dispPages()
{
    for (k = 0; k < f; k++)
    {
        if(p[k] != 9999)
            printf("%d", p[k]);
    }
}

void dispPFCount()
{
    printf("\nTotal no of page faults:%d", pfCount);
}

void fifo()
{
    initialize();
    for(i=0; i<n; i++)
    {
        printf("\nFor %d :", seq[i]);
 
        if(isHit(seq[i]) == 0)
        {
 
            for(k = 0; k < f-1; k++)
                p[k]=p[k+1];
 
            p[k] = seq[i];
            pfCount++;
            dispPages();
        }
        else
            printf("No page fault");
    }
    dispPFCount();
}

void lru()
{
    initialize();
    int least[50];
    for(i = 0; i < n; i++)
    {
 
        printf("\nFor %d :", seq[i]);
 
        if(isHit(seq[i])==0)
        {
 
            for(j=0; j < f; j++)
            {
                int pg=p[j];
                int found=0;
                for(k = i-1; k >= 0; k--)
                {
                    if(pg == seq[k])
                    {
                        least[j] = k;
                        found = 1;
                        break;
                    }
                    else
                        found = 0;
                }
                if(!found)
                    least[j] = -9999;
            }
            int min=9999;
            int repindex;
            for(j = 0; j < f; j++)
            {
                if(least[j] < min)
                {
                    min = least[j];
                    repindex = j;
                }
            }
            p[repindex] = seq[i];
            pfCount++;
 
            dispPages();
        }
        else
            printf("No page fault!");
    }
    dispPFCount();
}

void optimal()
{
    initialize();
    int near[50];
    for(i = 0; i < n; i++)
    {
 
        printf("\nFor %d :", seq[i]);
 
        if(isHit(seq[i])==0)
        {
 
            for(j = 0; j < f; j++)
            {
                int pg=p[j];
                int found=0;
                for(k = i; k < n; k++)
                {
                    if(pg == seq[k])
                    {
                        near[j] = k;
                        found = 1;
                        break;
                    }
                    else
                        found = 0;
                }
                if(!found)
                    near[j] = 9999;
            }
            
            int max = -9999;
            int repindex;
            for(j = 0; j < f; j++)
            {
                if(near[j]>max)
                {
                    max = near[j];
                    repindex = j;
                }
            }
            p[repindex]=seq[i];
            pfCount++;
 
            dispPages();
        }
        else
            printf("No page fault");
    }
    dispPFCount();
}

int main()
{
    int choice;
    while(1)
    {
    	
        printf("\n\n\t\tPage Replacement Algorithms\n\t1.Enter data\n\t2.FIFO\n\t3.Optimal\n\t4.LRU\n\t5.Exit\n\tEnter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            input();
            break;
        case 2:
            fifo();
            break;
        case 3:
            optimal();
            break;
        case 4:
            lru();
            break;
        default:
            return 0;
            break;
        }
    }
}
