/*
AUTHOR: Chunye Gong
Time: 20190212
Description: translate full matrix to Sparse Matrix CSR format

*/

#include <stdio.h>
#include <stdlib.h>

const int m = 8;// number of column, can change
const int n = 7;// number of row, can change

void main()
{
	printf("Create Matrix for example******************\n");
	int mat[n][m],mat1[n][m];
	int i, j, iOK;
	
	for (j=0; j<n; j++)
		for (i=0; i<m; i++)
		{
			mat[j][i]=0;
			mat1[j][i]=0;
		}
	
	srand((int)time(0));
	for (j=0; j<n; j++)
		for (i=0; i<m; i++)
		{
			if(rand()*1.0/RAND_MAX>0.8){mat[j][i]=(rand()*0.0001+1);}// 20% are not zero
			if(i==j) mat[j][i]=i;
		}
	mat[0][0]=7;

	for (j=0; j<n; j++)
	{
		for (i=0; i<m; i++)
		{
			printf("%d ",mat[j][i]);
		}
		printf("\n");
	}
	
	printf("matrix to csr******************\n");
	int totalSize=m*n;// not need so big, can pre-compute or guess a more suitable value
	int csr[totalSize], csrIndex[totalSize], csrOffset[n+1];// commonly not need such big memory.
	for (i=0; i<m*n; i++)
	{
		csr[i]=0;
		csrIndex[i]=0;
	}
	int totolElement=0;
	for (j=0; j<n; j++)
	{
		csrOffset[j]=totolElement;
		for (i=0; i<m; i++)
		{
			if(mat[j][i]!=0)
			{
				csr[totolElement]=mat[j][i];
				csrIndex[totolElement]=i;				
				totolElement++;
			}
		}
	}
	csrOffset[n]=totolElement;
	
	
	printf("results******************\n");
	for (i=0; i<n+1; i++) printf("%d ",csrOffset[i]);
	printf("\n");
	for (i=0; i<totolElement; i++) printf("%d ",csrIndex[i]);
	printf("\n");
	for (i=0; i<totolElement; i++) printf("%d ",csr[i]);
	printf("\n");
	
	printf("recover matrix******************\n");
	for (j=0; j<n; j++)
	{
		for(i=csrOffset[j];i<csrOffset[j+1];i++)
		{
			mat1[j][csrIndex[i]]=csr[i];
		}
	}
	
	printf("recovered matrix******************\n");
	for (j=0; j<n; j++)
	{
		for (i=0; i<m; i++)
		{
			printf("%d ",mat1[j][i]);
		}
		printf("\n");
	}
	
	printf("check******************\n");
	iOK=1;
	for (j=0; j<n; j++)
	{
		for (i=0; i<m; i++)
		{
			if(mat[j][i]!=mat1[j][i])
			{
				printf("%d!=%d,%d,%d",mat[j][i],mat1[j][i],j,i);
				iOK=0;
			};
		}
	}
	if(iOK==1)
		printf("OK!\n");
	else
		printf("FAILED!\n");

}
