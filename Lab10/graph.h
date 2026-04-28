#include <stdlib.h>
#include <stdbool.h>

#define NODE_NR 4

typedef struct GRAPH {
	size_t node_nr;
	size_t edge_nr;
	bool **adjacent;
} GRAPH;

void new_graph(GRAPH* new, size_t nodes);
void generate_adjacent_matrix(GRAPH* graph);
void show_adj_matrix(GRAPH graph);
void free_graph(GRAPH *graph);
void check_isolated_nodes(GRAPH graph);
void show_pair_nodes(GRAPH graph);
size_t get_rank(GRAPH graph, size_t node);
