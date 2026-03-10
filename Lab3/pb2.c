#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LMAT 5

void free_matrix(int **matrix) {
	for (int i = 0; i < LMAT; i++) {
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;
}


void init_matrix() {
	int **matrix = (int **)malloc(LMAT * sizeof(int *));
	if (matrix == NULL)
		exit(-1);

	for (int i = 0; i < LMAT; i++) {
		matrix[i] = (int *)malloc(LMAT * sizeof(int));
		if (matrix[i] == NULL)
			exit(-1);
	}

	for (int i = 0; i < LMAT; i++) {
		int medium = 0;
		for (int j = 0; j < LMAT; j++) {
			matrix[i][j] = rand() % 100;
			medium += matrix[i][j];
		}

		medium /= LMAT;
		printf("Media pe linia %d inainte de a scadea: %d\n", i, medium);

		for (int j = 0; j < LMAT; j++)
			matrix[i][j] -= medium;
		medium = 0;

		for (int j = 0; j < LMAT; j++)
			medium += matrix[i][j];

		printf("Media pe linia %d dupa scadere: %d\n", i, medium / LMAT);
	}
	free_matrix(matrix);
}

int main(void) {

	init_matrix();

	return 0;
}