

#include <stdio.h>
#include <stdlib.h>


typedef struct node{
	int children[50];
	int number_of_children;
	int height;
	int parent;
	int time;
}NODE;

int main(){

	int n;
	NODE *nodes;
	int i, j, k, num, actual, parent;
	int h;
	int max;
	int *array;

	while (scanf("%d", &n) == 1){
		nodes = (NODE*)malloc(n*sizeof(NODE));
		for (i = 0; i < n; i++) {
			nodes[i].number_of_children = 0;
			nodes[i].time = -1;
		}

		for (i = 0; i < n; i++){
			scanf("%d", &num);
			if (num == -1){						//initializing starting node
				nodes[0].parent = -1;
				nodes[0].time = -1;
				nodes[0].height = 0;
			}
			else {								//other nodes
				nodes[i].parent = num;
				nodes[i].height = 0;
				nodes[num].children[nodes[num].number_of_children] = i;
				nodes[num].number_of_children++;
				actual = i;
				parent = num;
				while (actual != -1){
					if (nodes[parent].height < nodes[actual].height + 1) {
						nodes[parent].height = nodes[actual].height + 1;
					}
					actual = parent;
					parent = nodes[parent].parent;
				}
			}
		}

		/*for (i = 0; i < n; i++){
		printf("Node %d :\nparent: %d, height: %d, children: %d\n", i, nodes[i].parent, nodes[i].height, nodes[i].number_of_children);
		}*/

		h = 0;
		while (nodes[0].time == -1){
			for (i = 0; i < n; i++){
				if (nodes[i].height == h){
					if (h == 0){
						nodes[i].time = 0;
					}
					else {
						//printf("Calculating height.\n");
						array = (int*)malloc(nodes[i].number_of_children*sizeof(int));
						for (j = 0; j < nodes[i].number_of_children; j++) array[j] = nodes[nodes[i].children[j]].time;

						/*printf("Children loaded.\n");
						for (j = 0; j < nodes[i].number_of_children; j++) printf("%d ",array[j]);
						putchar('\n');*/

						for (j = 0; j < nodes[i].number_of_children; j++){
							max = j;
							for (k = j; k < nodes[i].number_of_children; k++){
								if (array[max] < array[k]) max = k;
							}
							num = array[max];
							array[max] = array[j];
							array[j] = num;
						}

						for (j = 0; j < nodes[i].number_of_children; j++) array[j] = array[j] + j;

						/*printf("Children edited.\n");
						for (j = 0; j < nodes[i].number_of_children; j++) printf("%d ", array[j]);
						putchar('\n');*/

						for (j = 0; j < nodes[i].number_of_children; j++){
							max = j;
							for (k = j; k < nodes[i].number_of_children; k++){
								if (array[max] < array[k]) max = k;
							}
							num = array[max];
							array[max] = array[j];
							array[j] = num;
						}

						/*printf("Array in final state.\n");
						for (j = 0; j < nodes[i].number_of_children; j++) printf("%d ", array[j]);
						putchar('\n');*/

						nodes[i].time = array[0] + 1;
						//free(array);
					}
				}
			}
			h++;
		}
		/*for (i = 0; i < n; i++){
		printf("Node %d :\nparent: %d, height: %d, children: %d, time: %d\n",i,nodes[i].parent,nodes[i].height,nodes[i].number_of_children,nodes[i].time);
		}*/
		printf("%d\n", nodes[0].time);

	}


	return 0;
}
