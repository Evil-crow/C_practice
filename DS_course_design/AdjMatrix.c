#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdjMatrix.h"
#include "queue.h"

int dfs_visited[MAXNUM];

int bfs_visited[MAXNUM];

int path[MAXNUM][MAXNUM];

int length[MAXNUM];

void matrix_init(AdjMatrix **G)
{
    FILE *fp;
    char filename[100];
    char pos_name[MAXNUM];
    char character;
    (*G) = (AdjMatrix *)malloc(sizeof(AdjMatrix));

    // get file name
    printf("Please input the file path: ");
    scanf("%s",filename);
    getchar( );

    // file operation
    fp = fopen(filename,"r+");
    if (fp == NULL) {
        printf("Can't open the file!\n");
        exit(0);
    }

    // judge empty file
    character = fgetc(fp);
    if(character == EOF) {
        printf("The file is empty!\n");
        fclose(fp);
        return ;
    }
    fseek(fp, 0L, 0);

    // get vex_number and arc_number
    fscanf(fp, "%d %d", &((*G)->vexnum), &((*G)->arcnum));

    // get place name
    for (int i = 0; i < (*G)->vexnum; i++) {
        fscanf(fp, "%s", pos_name);
        strcpy((*G)->vex[i], pos_name);
    }

    // get place path
    for (int i = 0; i < (*G)->vexnum; i++)
        for (int j = 0; j < (*G)->vexnum; j++)
            fscanf(fp, "%d", &((*G)->arcs[i][j]));
    fclose(fp);

    printf("Get the file OK!\n");
    print_graph(*G);
}

int matrix_locate(AdjMatrix *G, char *str)
{
    if (G->vexnum == 0) {
        printf("The graph is empty.\n");
        return -2;
    }
    for (int i = 0; i < G->vexnum; i++) {
        if (strcmp(G->vex[i], str) == 0)
            return i;
    }

    return -1;
}

void print_graph(AdjMatrix *G)
{
    printf("vexnum:%d , arcnum:%d\n",G->vexnum,G->arcnum);

    for (int i = 0; i < G->vexnum; i++)
        printf("1. %s ",G->vex[i]);
    printf("\n");

    for (int i = 0; i < G->vexnum; i++) {
        for(int j = 0; j < G->vexnum; j++)
            printf("%d ",G->arcs[i][j]);
        printf("\n");
    }
}

void DFS(AdjMatrix *G, int cur_vex)
{
    int next_vex;

    printf("%s\n",(*G).vex[cur_vex]);
    dfs_visited[cur_vex] = 1;
    next_vex = matrix_get_next_adjvex(G, cur_vex, 0);
    while (next_vex != -1) {
        if (!dfs_visited[next_vex]) {
            DFS(G, next_vex);
        }
        next_vex = matrix_get_next_adjvex(G, cur_vex, next_vex);
    }
}

void BFS(AdjMatrix *G, int cur_vex)
{
    int next_vex;
    Queue *Q;

    queue_init(&Q);
    printf("%s\n",G->vex[cur_vex]);
    bfs_visited[cur_vex] = 1;
    queue_push_in(Q, cur_vex);

    while (!queue_empty(Q)) {
        queue_pop_out(Q, &cur_vex);
        next_vex = matrix_get_next_adjvex(G, cur_vex, 0);
        while (next_vex != -1) {
            if (!bfs_visited[next_vex]) {
                printf("%s\n",G->vex[next_vex]);
                bfs_visited[next_vex] = 1;
                queue_push_in(Q, next_vex);
            }
            next_vex = matrix_get_next_adjvex(G, cur_vex, next_vex);
        }
    }
}

int matrix_get_next_adjvex(AdjMatrix *G, int cur_vex, int next_vex)
{
    for (int i = next_vex+1; i < G->vexnum; i++) {
        if (G->arcs[cur_vex][i] > 0)
            return i;
    }

    return -1;
}

void matrix_Prim(AdjMatrix *G, int start)
{
    struct record closedge[MAXNUM];
    int pos = 0;
    int temp;
    int result[MAXNUM];

    closedge[start].value = 0;
    result[pos++] = start;

    for (int i = 0; i < G->vexnum; i++) {
        closedge[i].adjvex = start;
        closedge[i].value = G->arcs[start][i];
    }
    for (int t = 0; t < G->vexnum - 1; t++) {
        int min = INFINITY;
        for (int i = 0; i < G->vexnum; i++) {
            if (closedge[i].value > 0 && closedge[i].value < min) {
                temp = i;
                min = closedge[i].value;
            }
        }
        closedge[temp].value = 0;
        result[pos++] = temp;

        // Update closedge[MAXSUM]
        for (int i = 0; i < G->vexnum; i++) {
            if (i != temp && (closedge[i].value > G->arcs[temp][i])) {
                closedge[i].adjvex = temp;
                closedge[i].value = G->arcs[temp][i];
            }
        }

    }
    for (int i = 0; i < pos; i++)
        printf("%s ",G->vex[result[i]]);
    printf("\n");
}

void matrix_Dijkstra(AdjMatrix *G, int start, int **path, int *length)
{
    int k, min, temp;

    // init array
    for (int i = 0; i < G->vexnum; i++) {
        length[i] = G->arcs[start][i];
        if (G->vex[start][i] != INFINITY) {
            path[i][1] = start;
        }
    }
    path[start][0] = 1;                            // flag: V-S
    printf("Dijkstra init OK!\n");
    // loop (vexnum-1)
    for (int i = 0; i < G->vexnum - 1; i++) {
        min = INFINITY;

        for (int j = 0; j < G->vexnum; j++)
            if (!path[j][0] && length[j] < min) {
                temp = j;
                min = length[temp];
            }
        printf("temp = %d, min = %d\n", temp, min);
        if (min == INFINITY)
            return ;
        path[temp][0] = 1;                         //flag: add flag

        // Update length[]
        for (int j = 0; j < G->vexnum; j++) {
            if (!path[j][0] && G->arcs[temp][j] != INFINITY && (length[temp] + G->arcs[temp][j] < length[j])) {
                length[j] = length[temp] + G->arcs[temp][j];

                for (k = 1; path[j][k] != 0; k++)
                    path[j][k] = path[temp][k];
                path[j][k++] = temp;
                path[j][k] = 0;
                printf("k = %d\n",k);
            }
        }
        for(int i = 0; i < G->vexnum; i++) {
            for (int j = 0; j < G->vexnum; j++)
                printf("%d ",path[i][j]);
            printf("\n");
        }
        printf("Dijkstra Update OK!\n");
    }
}
