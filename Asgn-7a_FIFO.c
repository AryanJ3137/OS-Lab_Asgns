#include<stdio.h>

int main() {
  int page[50],frame[50];
  int n,f;
  int found;
  int pf=0,ph=0;
  int i,j,k=0;
  
  printf("Enter the number of pages: ");
  scanf("%d",&n);
  
  printf("Enter the values of the page:\n");
  for (i=0;i<n;i++) {
  	scanf("%d",&page[i]);
  }
  
  printf("Enter the frame size: ");
  scanf("%d",&f);
  
  for (i=0;i<f;i++) 
  	frame[i] = -1;	
  	
  printf("\nPages\tFrames\n");
  for (i=0;i<n;i++) {
  	found = 0;
  	for (j=0;j<f;j++) {
  		if (frame[j] == page[i])
  		{
  			found = 1;
  			break;
  		}
  	}
  	
  	if (found == 0) {
  		frame[k] = page[i];
  		k = (k+1) % f;
  		pf++;
  	}
  	else {
  		ph++;
  		}
  	
  	printf("%d\t",page[i]);
  	for (j=0;j<f;j++) {
  		if (frame[j] == -1)
  		   printf("-");
  		else
  		   printf("%d ",frame[j]);
  		   }
  	if (found == 0) {
  		printf(" Page Fault");
  		printf("\n");
  	} else {
  		printf(" Page Hit");
  		printf("\n");
  		}
  	}
  		   
  	printf("\nTotal Page Faults = %d\n",pf);
  	printf("Total Page Hits = %d\n",ph);
  	
  	return 0;
  }
