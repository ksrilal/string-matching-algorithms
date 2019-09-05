#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LPS(char *pat, int m, int *lps)
{
	int len = 0;
	lps[0] = 0;
	
	int i = 1;
	
	while(i<m)
	{
		if(pat[i]==pat[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else
		{
			if(len!=0)
			{
				len = lps[len-1];
			}
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
	
}


void KMP(char *pat, char *txt)
{
	int m = strlen(pat);
	int n = strlen(txt);
	
	int lps[m];
	
	LPS(pat, m, lps);
	
	int i = 0;
	int j = 0;
	
	while(i<n)
	{
		if(pat[j]==txt[i])
		{
			j++;
			i++;
		}
		
		if(j==m)
		{
			printf("Found pattern at index %d\n",i-j);
			j = lps[j-1];
		}
		else if(i<n && pat[j]!=txt[i])
		{
			if(j != 0)
				j = lps[j-1];
			else
				i = i+1;
		}
	}
}


int main()
{
	char pat[100];
	char txt[100];
	
	printf("Enter text: ");
	gets(txt);
	
	printf("Enter pattern: ");
	gets(pat);
	
	KMP(pat, txt);
	
	return 0;
}
