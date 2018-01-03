#ifndef _ADJ_MATRIX_H
#define _ADJ_MATRIX_H

#define MAXNUM 20

#define INFINITY 9999

typedef struct matrix {
    int arcs[MAXNUM][MAXNUM];
    char vex[MAXNUM][MAXNUM];
    int vexnum;
    int arcnum;
} AdjMatrix;

struct record {
    int adjvex;
    int value;
};

void matrix_init(AdjMatrix **G);

void print_graph(AdjMatrix *G);

int matrix_locate(AdjMatrix *G, char *str);

int matrix_get_next_adjvex(AdjMatrix *G, int cur_vex, int cur_pos);

void BFS(AdjMatrix *G, int cur_vex);

void DFS(AdjMatrix *G, int cur_vex);

void matrix_Dijkstra(AdjMatrix *G, int start, int **path, int *length);

void matrix_Prim(AdjMatrix *G, int start);

#endif // _ADJ_MATRIX_H

