#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
	char s1[100];
	char s2[100];
	char s3[200];
	int i,j;
	int k=0;
	int tf=1;
	int curr=0;
	printf("enter s1: ");
	scanf("%s",s1);
	printf("enter s2: ");
	scanf("%s",s2);
	printf("enter s3: ");
	scanf("%s",s3);
	int l1=strlen(s1);
	int l2=strlen(s2);
	int l3=strlen(s3);
	for(i=0;i<l1;i++){
		for(k=0;k<l3;k++){
			if(s1[i]==s3[k]){
				if(k<curr){
					tf=0;
					printf("false %d %d %d\n",i,k,curr);
					return 0;
			    }
				s3[k]=0;
				curr=k;
				goto A;
			}
		}
		A: k=0;
	}
	printf("aa\n");
	curr=0;
	for(j=0;j<l2;j++){
		for(k=0;k<l3;k++){
			if(s2[j]==s3[k]){
				if(k<curr){
					tf=0;
					printf("false\n");
					return 0;
			    }
				s3[k]=0;
				curr=k;
				goto B;
			}
		}
		B: k=0;
	}
	printf("true\n");
	return 0;
}