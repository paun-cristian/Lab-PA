#include <stdio.h>
#include <time.h>
#include "graph.h"

void new_graph(GRAPH* new, size_t nodes) {
	new->node_nr = nodes;
	new->edge_nr = 0;
	new->adjacent = (bool** )malloc(nodes * sizeof(bool* ));
	if (!new->adjacent)
		exit(-1);

	for (size_t i = 0; i < nodes; ++i) {
		new->adjacent[i] = (bool* )malloc(nodes * sizeof(bool));
		if (!new->adjacent[i]) {
			free(new);
			exit(-1);
		}
	}
}

void generate_adjacent_matrix(GRAPH* graph) {
	srand(time(NULL));

	for (size_t curr_node = 0; curr_node < graph->node_nr / 2; ++curr_node) {
		size_t curr_node_rank = get_rank(*graph, curr_node);
		
		for (size_t adj_node = curr_node + 1; adj_node < graph->node_nr; ++adj_node) {
			if (curr_node_rank < 5) {
				graph->adjacent[curr_node][adj_node] = graph->adjacent[adj_node][curr_node] = rand() % 2;
				if (graph->adjacent[curr_node][adj_node] == 1) {
					graph->edge_nr++;
					curr_node_rank++;
				}	
			}
		}
	}
}

size_t get_rank(GRAPH graph, size_t node) {
	size_t rank = 0;
	for (size_t j = 0; j < graph.node_nr; ++j)
		if (graph.adjacent[node][j] == true)
			rank++;

	return rank;
}

void show_adj_matrix(GRAPH graph) {
	for (size_t i = 0; i < graph.node_nr; ++i) {
		for(size_t j = 0; j < graph.node_nr; ++j)
			printf("%d ", graph.adjacent[i][j]);
		printf("\n");
	}
}

void free_graph(GRAPH *graph) {
	for (size_t i = 0; i < graph->node_nr; ++i)
		free(graph->adjacent[i]);
	free(graph->adjacent);
}

void check_isolated_nodes(GRAPH graph) {
	printf("NODURI IZOLATE: ");
	for (size_t i = 0; i < graph.node_nr; ++i) {
		size_t curr_node_rank = get_rank(graph, i);
		if (curr_node_rank == 0)
			printf("%ld ", i);
	}
	printf("\n");
}

void show_pair_nodes(GRAPH graph) {
	printf("NODURI COMUNE:\n");
	for (size_t x = 0; x < graph.node_nr / 2; ++x) {
		for (size_t y = x + 1; y < graph.node_nr; ++y) {
			printf("PERECHEA %ld %ld: ", x, y);
			for (size_t k = 0; k < graph.node_nr; ++k)
				if (graph.adjacent[x][k] == graph.adjacent[y][k] && graph.adjacent[x][k] == 1)
					printf("%ld ", k);
			printf("\n");
		}
	}
}