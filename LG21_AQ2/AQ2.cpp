#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedList_struct.h"
void createtxtfile(char name[]) {
	FILE* inp = fopen(name, "w");
	int num;
	int add,i=0;
	printf("\nHow many numbers do you want to produce: ");
	scanf("%d", &num);

	for (i = 0 ; i < num;i++) {
		add = rand() % 100 + 1;
		printf("%d ", add);
		fprintf(inp, "%d ", add);
	}
	fclose(inp);
	printf("File %s has been created\n", name);

}
void displaylist(node_t* a) {
	node_t* temp = a;
	LType arr;
	while (temp != NULL) {
		arr = temp->data;
		printf("%d-> ", arr);
		temp = temp->next;
	}
	printf("NULL\n");
}
node_t* mergelist(node_t* first, node_t* sec) {
	node_t* p,*take;
	if (first->data > sec->data) {
		p = sec;
		take = first;
	}
	else {
		p = first;
		take = sec;
	}
	node_t* dummy;
	dummy = p;
	while (dummy->next != NULL && take != NULL) {
		if (dummy->next->data < take->data) {
			dummy = dummy->next;
		}
		else {
			addAfter(dummy, take->data);
			take = take->next;
		}
	}
	if (dummy == NULL) {
		dummy = take;
	}
	return(p);



	
	
}
int main(void) {
	node_t* a = NULL,* b=NULL;
	char name[50],name2[50];
	srand(time(NULL));
	printf("Enter the first file name: ");
	scanf("%s", name);
	createtxtfile(name);

	printf("Enter the second file name: ");
	scanf("%s", name2);
	createtxtfile(name2);

	FILE* inp1 = fopen(name, "r"),* inp2=fopen(name2,"r");
	LType arr;
	fscanf(inp1, "%d", &arr);
	a=addBeginning(a, arr);
	node_t* temp =a;
	while (fscanf(inp1, "%d", &arr) != EOF) {
		addAfter(temp, arr);
		temp = temp->next;
	}
	fclose(inp1);

	fscanf(inp2, "%d", &arr);
	b=addBeginning(b, arr);
	temp = b;
	while (fscanf(inp2, "%d ", &arr) != EOF) {
		temp = b;
		if (arr < temp->data) {
			b=addBeginning(b, arr);
		}
		else {
			while (temp ->next!=NULL&&temp->next->data<=arr) {
				temp = temp->next;
				}
			if (temp->data != arr) {
				addAfter(temp, arr);
			}
				
			}
		}

	
	fclose(inp2);

	//sortlists
	node_t* sort = a;
	int sorted=0;
	LType temp1;
	while (sorted == 0) {
		sorted = 1;
		sort = a;
		while (sort != NULL && sort->next != NULL) {

			if (sort->data > sort->next->data) {
				temp1= sort->data;
				sort->data = sort->next->data;
				sort->next->data = temp1;
				
				sorted = 0;
			}
			
				sort = sort->next;

		}
	}
	sort = a;
	while (sort != NULL && sort->next != NULL) {
		if (sort->data == sort->next->data) {
			deleteAfter(sort, &arr);

		}
		sort = sort->next;
	}
	displaylist(a);

	
	displaylist(b);



	b=mergelist(a, b);
	printf("Lists have been merged: ");
	displaylist(b);

}