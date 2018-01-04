#include <stdio.h>
#include <stdlib.h>
#include "operation.h"
#include "AdjMatrix.h"

void get_best_path(AdjMatrix *G)
{
    char start[20],end[20];
    int matrix_start, matrix_end;
    int *length, **path;

    // init path and length
    length = (int *)malloc(sizeof(int) * G->vexnum);
    path = (int **)malloc(sizeof(int *) * G->vexnum);
    for (int i = 0; i < G->vexnum; i++) {
        path[i] = (int *)malloc(sizeof(int) * G->vexnum);
    }

    for (int i = 0; i < G->vexnum; i++) {
        length[i] = 0;
        for (int j = 0; j < G->vexnum; j++)
            path[i][j] = -1;
    }

    printf("Please input the start: ");
    scanf("%s",start);
    getchar( );
    printf("Please input the end: ");
    scanf("%s",end);
    getchar( );
    matrix_start = matrix_locate(G, start);
    matrix_end = matrix_locate(G, end);

    if (matrix_start == -1 || matrix_end == -1) {
        printf("Can't find a path, someone doesn't exist!\n");
        return;
    }

    matrix_Dijkstra(G, matrix_start, path, length);

    for (int t = 1; path[matrix_end][t] != -1; t++)
        printf("%s--->",G->vex[path[matrix_end][t]]);
    printf("%s\n",G->vex[matrix_end]);

}

void get_small_tree(AdjMatrix *G)
{
    char place[20];
    int matrix_start;

    printf("Please input the start place: ");
    scanf("%s",place);
    getchar( );
    matrix_start = matrix_locate(G, place);

    if (matrix_start == -1) {
        printf("The place doesn't exist!\n");
        return ;
    }
    matrix_Prim(G, matrix_start);
}

void get_all_way(AdjMatrix *G)
{
    char start[20], end[20];
    int matrix_start, matrix_end;
    extern int pos, dfs_path[MAXNUM], dfs_visited[MAXNUM];

    for (int i = 0; i < MAXNUM; i++) {
        dfs_visited[i] = 0;
        dfs_path[i] = -1;
    }
    pos = 0;

    printf("Please input the start place: ");
    scanf("%s",start);
    getchar( );
    printf("Please input the end place: ");
    scanf("%s",end);
    getchar( );

    matrix_start = matrix_locate(G, start);
    matrix_end = matrix_locate(G, end);
    if (matrix_start == -1 || matrix_end == -1) {
        printf("Someone doesn't exist\n");
        return;
    }

    DFS(G, matrix_start, matrix_end);
}

void get_mininum_transfer_path(AdjMatrix *G)
{

}
