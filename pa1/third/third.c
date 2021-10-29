#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int num, temp, n , v;
   	
	char row[1000], function[500];
         
	char *filename = argv[1];

   	FILE *file = fopen(filename,"r");
	
	if (file == NULL)
	{ 
		printf("Error, Cannot find this file!\n");
	}
        fgets(row, 999, file);
  
	sscanf(row, "%d", &num);   
   	
	while(fgets(row, 999, file))
   	{
       		sscanf(row, "%s %d %d", function, &n, &v); 
       		switch(function[0])           
       		{
			
           		case 'g': temp = 1 << n;  
                       	  	  printf("%d\n",(num&temp) && 1);
                       	  	  break;
			case 'c': temp = 1 << n; 
                       	  	  num = num^temp;   
                       	  	  printf("%d\n",num);
                       	  	  break;
			case 's': temp = 1 << n;    
                       	  	  if(v)
                       		  {
                            	  	num = num | temp;
                       		  }
                       		  else
                       		  {
 					temp = ~temp;
                           		num = num & temp;
                       		  }
                       			printf("%d\n",num);
                       			break;
           	
		
			default: printf("Default!\n");
       		}
   	}
   	return 0;
}


