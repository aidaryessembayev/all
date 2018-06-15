//Program was created in collaboration of Tauyekel Kunzhol and Aidar Yessembayev

#include <stdio.h>
#include <stdlib.h>
#include <String.h>

//our struct for linked list
typedef struct _person_count {
   char *country;
   long females;
   long males;
   struct _person_count *link;
} person_count;

//this function prints each element in linked list
void printList(person_count *list)
{
	person_count *curr = list;

	while (1)
	{
		printf("%32s %10lu %10lu\n", curr->country, curr->females, curr->males);

		if (curr->link != NULL)
		{
			curr = curr->link;
		}
		else
		{
			break;
		}
	}
}

//this function frees memory of each element starting from last
void clearList(person_count *list)
{
	if (list->link != NULL)
	{
		clearList(list->link);
	}

	free(list);
}

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);

	FILE *input = fopen("SecondaryEd2005.txt", "r");

	//does not execute the program if fails opening file
	if (input == NULL)
	{
		printf("Error Opening File");

		return 1;
	}

	//starting point of our list
	person_count *first = NULL;
	_Bool sorted = 0;

	while (!feof(input))
	{
		//temporary variables
		char name[32];
		long maleCount;
		long femaleCount;

		//store data from list in temporary variables
		fscanf(input, "%s %lu %lu", name, &femaleCount, &maleCount);

		person_count *newNode = malloc(sizeof(person_count));

		//fill variables of our struct with values of temporary variables
		newNode->males = maleCount;
		newNode->females = femaleCount;
		newNode->country = malloc((strlen(name) + 1) * sizeof(char)); //allocate memory for country name(since, we're using pointers )
		strcpy(newNode->country, name);//load to the newly allocated memory
		newNode->link = NULL;//link is initially set to null

		//first stage of sort
		if (first == NULL)
		{
			first = newNode;
			sorted = 1; //this is needed to check if have sorted our new node already

		}
		//putting in first place
		else if ((first->males + first->females) < (newNode->males + newNode->females))
		{
			newNode->link = first;
			first = newNode;
			sorted = 1;
		}

		person_count *curr = first;//this pointer is used to go through each element in list, and locate new node

		//second stage of sort, it gets executed only if first fails(we don't need to sort twice)
		while (!sorted)
		{

			if (curr->link == NULL)
			{
				curr->link = newNode;//locates at the end of the list
				break;//breaks the loop if have located our new node
			}

			if ((newNode->males + newNode->females) < (curr->link->males + curr->link->females))
			{
				curr = curr->link;
				continue;//if total of new node is less than total of currently checking node, then we just proceed to the next node
			}
			else
			{
				newNode->link = curr->link;//putting new node in between two elements
				curr->link = newNode;
				break;
			}

		}

		sorted = 0;
	}

	printList(first); //we first print our linked list
	clearList(first);//then free up memory for list
	fclose(input);

	return 0;
}
