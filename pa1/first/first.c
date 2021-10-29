#include<stdio.h>
void sortArray(int *arr, int size, int ptr)
{
	int i, j, temp;
   	
	for(i = 0; i < size - 1 ; i++)
	{
       		for(j = i + 1; j < size; j++)
		{
           		if((ptr == 1) && (arr[i] < arr[j]))
			{
               			temp = arr[i];
               			arr[i] = arr[j];
                		arr[j] = temp;
            		}
			else if((ptr == 0) && (arr[i] > arr[j]))
			{
 				temp = arr[i];
               			arr[i] = arr[j];
                		arr[j] = temp;
			}
       		}

   	}
}

int main(int argc, char *argv[])
{
   	int size, num, i;
   	
	char *filename = argv[1];

   	FILE *file = fopen(filename,"r");

	if (file == NULL)
	{
		printf("Error! Cannot find this file.\n");
		return 0;
	}
	fscanf(file, "%d" , &size);

        int array[size], odd[size], even[size];
   	int countOfOdd = 0, countOfEven = 0;
   	
	while(fscanf(file, "%d", &num) == 1)
	{
       		if(num%2 == 0)
		{
			even[countOfEven] = num;
			countOfEven++;
		}	
      		else
		{
  			odd[countOfOdd] = num;
			countOfOdd++;
		}
   	}
  	sortArray(even, countOfEven, 1);
   	sortArray(odd, countOfOdd, 0);
   	
	for(i = 0; i < countOfOdd; i++)
	{	
       		array[i] = odd[i];
		printf("%d\t", array[i]);	
	}
       	for(i = countOfOdd; i < size; i++)	
	{	
		array[i] = even[i - countOfOdd];
		printf("%d\t", array[i]);	
   	}
	printf("\n");
   	return 0;

}
 
