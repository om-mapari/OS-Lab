#include <stdio.h>
#include <stdlib.h>

//print matrix
void print(int x[][10], int n, int m)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		printf("\n");
		for (j = 0; j < m; j++)
		{
			printf("%d\t", x[i][j]);
		}
	}
}

//Resource Request algorithm
void resource_request_algo(int A[10][10], int N[10][10], int AV[10][10], int pid, int m)
{
	int request[1][10];
	int i;
	printf("\n Enter additional request :- \n");
	for (i = 0; i < m; i++)
	{
		printf(" Request for resource %d : ", i + 1);
		scanf("%d", &request[0][i]);
	}

	for (i = 0; i < m; i++)
		if (request[0][i] > N[pid][i])
		{
			printf("\n Error encountered.\n");
			exit(0);
		}

	for (i = 0; i < m; i++)
		if (request[0][i] > AV[0][i])
		{
			printf("\n Resources unavailable.\n");
			exit(0);
		}

	for (i = 0; i < m; i++)
	{
		AV[0][i] -= request[0][i];
		A[pid][i] += request[0][i];
		N[pid][i] -= request[0][i];
	}
}

//Safety algorithm
int safety(int A[][10], int N[][10], int AV[1][10], int n, int m, int safeSequence[])
{

	int i, j, k, x = 0;
	int F[10], avaliable[1][10];
	int count = 0, flag = 0;

	for (i = 0; i < n; i++)
		F[i] = 0;
	for (i = 0; i < m; i++)
		avaliable[0][i] = AV[0][i]; // copy of avaliable

	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			if (F[i] == 0) // not finished 
			{
				flag = 0;
				for (j = 0; j < m; j++)
				{
					if (N[i][j] > avaliable[0][j])
						flag = 1; // need is more so break
				}
				
				if (flag == 0 && F[i] == 0)
				{
					for (j = 0; j < m; j++)
						avaliable[0][j] += A[i][j];
					F[i] = 1;
					count++;
					safeSequence[x++] = i; // add in safe seq
				}
			}
		}
		if (count == n)
			return 1;
	}
	return 0;
}

//INPUT
void take_input(int A[][10], int N[][10], int M[10][10], int AV[1][10], int *n, int *m)
{
	int i, j;
	printf("\n ENTER TOTAL NO OF PROCESSES : ");
	scanf("%d", n);
	printf("\n ENTER TOTAL NO OF RESOURCES : ");
	scanf("%d", m);
    
   printf("\n\nRESOURCE ALLOCATION MATRIX : ");
    for (i = 0; i < *n; i++)
    {
        printf("\nFOR PROCESS %d : ", i + 1);
        for (j = 0; j < *m; j++)
            scanf("%d", &A[i][j]);
    }
    printf("\n\nMAXIMUM NEED MATRIX : ");
    for (i = 0; i < *n; i++)
    {
        printf("\nFOR PROCESS %d : ", i + 1);
        for (j = 0; j < *m; j++)
            scanf("%d", &M[i][j]);
    }

	printf("\n AVAILABLE RESOURCES : \n");
	for (i = 0; i < *m; i++)
	{
		printf(" Resource %d : ", i + 1);
		scanf("%d", &AV[0][i]);
	}

	for (i = 0; i < *n; i++)
		for (j = 0; j < *m; j++)
			N[i][j] = M[i][j] - A[i][j];

	printf("\n Allocation Matrix");
	print(A, *n, *m);
	printf("\n Maximum Requirement Matrix");
	print(M, *n, *m);
	printf("\n Need Matrix");
	print(N, *n, *m);
}

//Banker
int banker(int A[][10], int N[][10], int AV[1][10], int n, int m)
{
	int j, i, safeSequence[10];
	j = safety(A, N, AV, n, m, safeSequence);
	if (j != 0)
	{
		printf("\n\n");
		for (i = 0; i < n; i++)
			printf(" P%d  ", safeSequence[i]);
		printf("\n A safety sequence has been detected.\n");
		return 1;
	}
	else
	{
		printf("\n Deadlock has occured.\n");
		return 0;
	}
}

int main()
{
	int safetyAlgo;
	int A[10][10],M[10][10],N[10][10],AV[1][10];
	int n, m, pid, ch;

	printf("\n DEADLOCK AVOIDANCE USING BANKER'S ALGORITHM\n");
	take_input(A, N, M, AV, &n, &m);
	safetyAlgo = banker(A, N, AV, n, m);

	if (safetyAlgo != 0)
	{
		printf("\n Do you any additional request ? ( 1 = Yes | 0 = No ) >> ");
		scanf("%d", &ch);
		if (ch == 1)
		{
			printf("\n Enter process no. for which you wanna request : ");
			scanf("%d", &pid);
			resource_request_algo(A, N, AV, pid - 1, m);
			safetyAlgo = banker(A, N, AV, n, m);
			if (safetyAlgo == 0)
				exit(0);
		}
	}
	else
		exit(0);
	return 0;
}

// The system is in a safe state!!
// Safe Sequence : < 1 3 4 0 2 >

// 5
// 3
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2

// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3

// 3 3 2

