#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define count 1000
struct hashEntry
{
	const char* key;
    	char* value;
    	struct hashEntry* next;
};

typedef struct hashEntry entry;

struct hashTable
{
    	entry bucket[count];  
};

typedef struct hashTable table;

void inHashTable(table* t)
{
    	int i;
    	if (t == NULL)return;

    	for (i = 0; i < count; ++i) 
	{
        	t->bucket[i].key = NULL;
        	t->bucket[i].value = NULL;
        	t->bucket[i].next = NULL;
    	}
}

int Index(const char* key)
{
    	int n = atoi(key);
    	return abs(n % count);
}

char* strDuplicate(const char* str)
{
    	int len;
    	char* ret;
    	if (str == NULL)return NULL;
	len = strlen(str);
	ret = (char*)malloc(len + 1);
    	
    	if (ret != NULL) 
	{
        memcpy(ret , str , len);
        ret[len] = '\0';
    	}
    	return ret;
}
int findValue(const table* t , const char* key)
{
    	int index;
    	const entry* e;
    	if (key == NULL || t == NULL) 
	{
	        return 0;
    	}
    	index = Index(key);
    	e = &(t->bucket[index]);
	
    	
	if (e->key == NULL) return 0;
    	while (e != NULL) 
	{
        	if (0 == strcmp(key , e->key)) 
		{
            		return 1;   
        	}
        	e = e->next;
    	}
    	return 0;
}

int insertEntry(table* t , const char* key , const char* value)
{
    	int index;
    	entry* e , *ep;

    	index = Index(key);
    	if (t->bucket[index].key == NULL) 
	{
        	t->bucket[index].value = strDuplicate(value);
		t->bucket[index].key = strDuplicate(key);
    	}
    	else 
	{
        	e = ep = &(t->bucket[index]);
        	while (e != NULL) 
		{ 
            		if (strcmp(e->key , key) == 0) 
			{
                		return 0;   
            		}
            		ep = e;
            		e = e->next;
        	} 

        	e = (entry*)malloc(sizeof (entry));
        	e->key = strDuplicate(key);
        	e->value = strDuplicate(value);
        	e->next = NULL;
        	ep->next = e;
    	}
    	return 1;
}

int main(int argc, char *argv[])
{
    	char *filename = argv[1];
    	FILE *file = fopen(filename,"r");
    	if (file == NULL)
    	{
        	printf("Error! Cannot find this file.\n");
        	return 0;
    	}
    	table ht;
    	inHashTable(&ht);
    	char opt[2], num[1000];
    	while (~fscanf(file, "%s%s", opt, num))
    	{
        	if (strcmp(opt, "s") == 0)
        	{
			if (findValue(&ht, num))
            		{
                		printf("present\n");
            		}
            		else printf("absent\n");
            		
        	}
            		
        	else if (strcmp(opt, "i") == 0)
        	{
			if (insertEntry(&ht, num, num))
			{
				printf("inserted\n");
			}
            		else printf("duplicate\n");
        	}

    	}
    	return 0;
}
