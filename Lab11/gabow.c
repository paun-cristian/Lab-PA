#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int v;
    struct Node* next;
} Node;

// implement a stack using an array
typedef struct Stack {
	int size;
    int top;
    int* stack; 
} Stack;

void initialize_stack(Stack *s, int V) {
	s->size = V;
	s->top = -1;
	s->stack = (int*)calloc(V, sizeof(int));
}

int in_stack(Stack *s, int x) {
	// check if an item x is found on the stack
	int i, found = 0;
	for (i=0; i<s->size; i++)
		if (s->stack[i] == x) {
			found = 1;
			break;
		}
	return found;
}

void add_edge(Node* graph[], int u, int v) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->v = v;
    new_node->next = graph[u];
    graph[u] = new_node;
}

void make_graph(Node* graph[]){
	// large cycle
    add_edge(graph, 0, 1); 
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 3); 	 
    add_edge(graph, 3, 4); 
    add_edge(graph, 4, 5); 
    add_edge(graph, 5, 0); 
    
    // small cycle
	add_edge(graph, 7, 6);
    add_edge(graph, 8, 7); 
    add_edge(graph, 6, 8); 
    
    // rays
    add_edge(graph, 4, 7); 
    add_edge(graph, 7, 2); 
    add_edge(graph, 6, 0); 
    
    // tail
    add_edge(graph, 2, 9); 
    add_edge(graph, 3, 10);
    add_edge(graph, 9, 10); 
}

void gabow(Node* graph[], int u, int time[], int* time_index, Stack* depth, Stack *roots) {
    time[u] = (*time_index)++;

	// add current node 'u' both on depth and roots stack
	// TO DO!!! complete the code to push the node to the stacks
	depth->stack[++depth->top] = u;
	roots->stack[++roots->top] = u;
	// loop through all neighbors of node u
	Node* p;
    for (p = graph[u]; p; p = p->next) {
        int v = p->v;
        if ((time)[v] == -1) { 		     // neighbor has not been visited yet, proceed to visit it
            gabow(graph, v, time, time_index, depth, roots); 
        } else if (in_stack(depth, v)) { // there's a cycle in the graph
        	// TO DO!!! we now need to pop from root_stack all the nodes in the loop, excluding the
			// first. these nodes all have higher visit time than the neighbor we are visiting 
			// complete the following while loop to pop these nodes
            while (roots->stack[roots->top] != v && time[roots->stack[roots->top]] > time[v]) {
				//printf("%d ", roots->stack[roots->top]);
				roots->top--;
            }
        }
    }

    if (roots->stack[roots->top] == u) { // reached the root of a connected component
        printf("strongly connected component nodes: ");
        int v;
        do {							 // pop all connected component nodes from DFS stack
            v = depth->stack[(depth->top)--];  		   
            printf("%c ", 'A' + v); 	 // print the actual letter
        } while (v != u);
        
        (roots->top)--;					 // pop the root of the connected component 
        printf("\n");
    }
}


int main() {
	int V = 11; // number of nodes
	
	// if the graph is represented by the adjacency list
	// the algorithm will run in O(V+E) time
	// implement it as an array of linked linked lists
	Node* graph[V];
	int i;
	for (i=0;i<V;i++) graph[i] = NULL;
	// create the graph
	make_graph(graph);
	
	// create the two stacks
	Stack *depth, *roots;
	depth = (Stack*)malloc(sizeof(Stack));
	initialize_stack(depth, V);
	roots = (Stack*)malloc(sizeof(Stack));
	initialize_stack(roots, V);
	
	// keep track of nodes visit order
	int time_index = 0;
	int time[V];
    for (i = 0; i< V; i++) time[i] = -1;
    
    for (i = 0; i < V; i++) {
    	// start component search from each univisited graph node
        if (time[i] == -1)
            gabow(graph, i, time, &time_index, depth, roots);
    }
    return 0;
}

