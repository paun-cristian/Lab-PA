#include <stdio.h>
#include "graph.h"

int main(void) {
	GRAPH graph;
	new_graph(&graph, NODE_NR);
	generate_adjacent_matrix(&graph);
	show_adj_matrix(graph);

	check_isolated_nodes(graph);
	printf("NUMARUL DE MUCHII: %ld\n", graph.edge_nr);
	show_pair_nodes(graph);
	free_graph(&graph);
	return 0;
}