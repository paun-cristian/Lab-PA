#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE {
	int val;
	struct NODE *next;
} NODE;

NODE *create_node(int val) {
	NODE *node = (NODE *)malloc(sizeof(NODE));
	if (!node) {
		exit(-1);
	}
	node->next = NULL;
	node->val = val;
	return node;
}

NODE *create_list(int n) {
	int i = 1;
	NODE *head = create_node(i++);
	NODE *second = create_node(i++);
	head->next = second;

	for (i; i <= 14; ++i) {
		NODE *tmp = create_node(i);
		second->next = tmp;
		second = tmp;
	}

	return head;
}

void show_list(NODE *head) {
	for (NODE *i = head; i != NULL; i = i->next) {
		printf("%d ", i->val);
	}
	printf("\n");

}

void free_list(NODE *head) {
	NODE *aux = head;
	while (aux != NULL) {
		aux = aux->next;
		free(head);
		head = NULL;
		head = aux;
	}
}

void star_transpositions(NODE **head) {
	if (*head == NULL || (*head)->next == NULL) return;

	int poz = rand() % 14;
	if (poz == 0) return;

	NODE *prev = *head;
	int j = 1;

	while (j < poz - 1 && prev->next->next != NULL) {
		prev = prev->next;
		j++;
	}

	NODE *next = prev->next; // copie la cel mutat
	NODE *aux_head = *head; // copie la head
	if (next == NULL) return;

	NODE *temp_after_next = next->next; //copie dupa cel mutat
	next->next = aux_head->next; //1. cel mutat pointeaza la al 2 lea
	prev->next = aux_head; // 2. cel de dinainte de cel mutat pointeaza la head
	aux_head->next = temp_after_next; //3. head-ul pointeaza la urmatorul de dupa cel mutat
	*head = next; //head ul devine cel mutat
}


void r2r(NODE **head) {
	if (*head == NULL || (*head)->next == NULL) return;

	int poz1 = rand() % 14;
	NODE *extracted = NULL;

	if (poz1 == 0) {
		extracted = *head;
		*head = (*head)->next;
	}
	else {
		NODE *prev = *head;
		int j = 1;
		while (j < poz1 && prev->next != NULL) {
			prev = prev->next;
			j++;
		}
		extracted = prev->next;
		if (extracted != NULL) {
			prev->next = extracted->next;
		}
	}

	if (extracted == NULL) return;
	extracted->next = NULL;

	int poz2 = rand() % 14;
	if (poz2 == 0) {
		extracted->next = *head;
		*head = extracted;
	} 
	else {
		NODE *prev = *head;
		int j = 1;
		while (j < poz2 && prev->next != NULL) {
			prev = prev->next;
			j++;
		}
		extracted->next = prev->next;
		prev->next = extracted;
	}
}


int main(void) {
	srand(time(NULL));
	NODE *head = create_list(14);
	//star_transpositions(&head);
	r2r(&head);
	show_list(head);
	free_list(head);

	return 0;
}