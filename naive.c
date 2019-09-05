#include <stdio.h>
#include <stdlib.h>



int main(){
	
	char T[100];
	char P[100];
	
	int i = 0;
	int j = 0;
	int count = 0;
	
	printf("Enter text:");
	gets(T);
	printf("Enetr pattern:");
	gets(P);
	
	int n = strlen(T);
	int m = strlen(P);
	
	for(i=0;i<=n-m;i++)
	{
		while(j<m && T[i+j]==P[j])
		{
			j++;
			if(j==m)
			{
				count++;
				printf("Matching in index: %d",i);				
			}
		}
	}
	
	if(count == 0) printf("Not found matching!");
	
	
	
	
	return 0;
}
