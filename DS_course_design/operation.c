#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void get_all_way(AdjMatrix *G)
{
    char start[20], end[20];
    int matrix_start, matrix_end;
    extern int dfs_pos, dfs_path[MAXNUM], dfs_visited[MAXNUM];

    for (int i = 0; i < MAXNUM; i++) {
        dfs_visited[i] = 0;
        dfs_path[i] = -1;
    }
    dfs_pos = 0;

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
    char start[20], end[20];
    int matrix_start, matrix_end;

    printf("Please input the start: ");
    scanf("%s",start);
    getchar( );
    printf("Please input the end: ");
    scanf("%s",end);
    getchar( );

    matrix_start = matrix_locate(G, start);
    matrix_end = matrix_locate(G, end);

    if (matrix_start == -1 || matrix_end == -1) {
        printf("Someone doesn't exist\n");
        return ;
    }

    BFS(G, matrix_start, matrix_end);
    printf("\n");
}

void get_small_tree(AdjMatrix *G)
{
    printf("\nlayout path:\n");
    for (int i = 0; i < G->vexnum; i++) {
        printf("%s: ",G->vex[i]);
        matrix_Prim(G, i);
        printf("\n");
    }
}

void add_vexnode(AdjMatrix *G)
{
    char place[20];
    char description[200];
    char path[100] = "D:\\information\\";

    printf("Please input the node you want to add: ");
    scanf("%s",place);
    getchar( );
    strcat(path, place);
    G->vexnum++;
    strcpy(G->vex[G->vexnum - 1], place);
    for (int i = 0; i < G->vexnum; i++) {
        G->arcs[i][G->vexnum - 1] = INFINITY;
        G->arcs[G->vexnum - 1][i] = INFINITY;
    }

    printf("Please input the description: \n");
    scanf("%s",description);
    getchar( );

    FILE *fp;
    fp = fopen(path, "a+");
    fprintf(fp, "%s", description);
    fclose(fp);

    printf("Add node succeed!\n");
}

void add_arcs(AdjMatrix *G)
{
    char start[20], end[20];
    int matrix_start, matrix_end, value;

    printf("Please input the start place you want to add: ");
    scanf("%s",start);
    getchar( );
    printf("Please input the end place you want to add: ");
    scanf("%s",end);
    getchar( );
    printf("Please input the length");
    scanf("%d",&value);
    getchar( );

    matrix_start = matrix_locate(G, start);
    matrix_end = matrix_locate(G, end);

    if (matrix_start == -1 || matrix_end == -1) {
        printf("Someone doesn't exist\n");
        return ;
    }

    G->arcnum++;
    G->arcs[matrix_start][matrix_end] = value;
    printf("Add path succeed!\n");
}

void del_vexnode(AdjMatrix *G)
{
    char place[20];
    int matrix_location;

    printf("Please input the place you want to del: ");
    scanf("%s",place);
    getchar( );
    matrix_location = matrix_locate(G, place);

    if (matrix_location == -1) {
        printf("The palce doesn't exist\n");
        return ;
    }

    int temp[MAXNUM][MAXNUM];
    for (int i = 0; i < matrix_location; i++) {
        for (int j = 0; j < matrix_location; j++) {
            temp[i][j] = G->arcs[i][j];
        }
    }

    for (int i = matrix_location + 1; i < G->vexnum; i++) {
        for (int j = 0; j < matrix_location; j++)
            temp[i-1][j-1] = G->arcs[i][j];
    }
}

void del_arcs(AdjMatrix *G)
{
    char start[20], end[20];
    int matrix_start, matrix_end;

    printf("Please input the start place you want to del: ");
    scanf("%s",start);
    getchar( );
    printf("Please input the end place you want to del: ");
    scanf("%s",start);
    getchar( );

    matrix_start = matrix_locate(G, start);
    matrix_end = matrix_locate(G, end);

    if (matrix_start == -1 || matrix_end == -1) {
        printf("Someone doesn't exist\n");
        return ;
    }

    G->arcnum--;
    G->arcs[matrix_start][matrix_end] = INFINITY;
    printf("Del path succeed!\n");
}

void save_file(AdjMatrix *G)
{
    char choice;
    char filename[20];

    if(G == NULL) {
        printf("The graph is NULL\n");
        return ;
    }

    printf("Do you want to save the graph?(y/N)");
    scanf("%c",&choice);
    if (choice == 'N')
        return ;
    FILE *fp = NULL;
    printf("Please input the filename to save file: ");
    scanf("%s",filename);
    fp = fopen(filename, "w+");
    if (fp == NULL) {
        printf("open file error\n");
        return ;
    }
    fprintf(fp, "%d %d\n", G->vexnum, G->arcnum);
    for (int i = 0; i < G->vexnum; i++)
        fprintf(fp, "%s ", G->vex[i]);
    fprintf(fp, "\n");
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++)
            fprintf(fp, "%d ", G->arcs[i][j]);
        fprintf(fp, "\n");
    }

    fclose(fp);
}

void map(void)
{
    printf("---------------------------------------------------\n");
    printf("                         校园地图                    \n");
    printf("---------------------------------------------------\n\n");
    printf("                        菜鸟驿站              \n");
    printf("                           ┆\n");
    printf("                           ┆\n");
    printf("           --------------旭日苑---------------\n");
    printf("          ┆                                 ┆\n");
    printf("          ┆                                 ┆\n");
    printf("          ┆                                 ┆\n");
    printf("        体育馆                             医务室\n");
    printf("          ┆                                 ┆\n");
    printf("          ┆                           ------┆\n");
    printf("          ┆                          ┆\n");
    printf("        图书馆----------------------银杏林\n");
    printf("          ┆                          ┆\n");
    printf("          ┆                          ┆\n");
    printf("          ┆                          ┆\n");
    printf("    大学生活动中心------------------实验楼\n");
    printf("          ┆                          ┆\n");
    printf("          ┆                          ┆\n");
    printf("          ┆                          ┆\n");
    printf("        邮政快递-----------------------\n");
    printf("          ┆            ┆ \n");
    printf("          ┆            ┆\n");
    printf("  西门------------------┆\n");
    printf("                        ┆\n");
    printf("                       正门\n");
}

void map_information(AdjMatrix *G)
{
    char description[100];
    char place[20];
    char path[300] = ".\\information\\";
    char temp;

    printf("Please input the place you want to know: ");
    scanf("%s",place);
    getchar( );
    strcat(path, place);
    strcat(path, ".txt");

    printf("%s 相关信息：\n",place);
    FILE *fp;
    fp = fopen(path, "r+");
    if (fp == NULL) {
        printf("It't isn't exist\n");
        return ;
    }
    temp = fgetc(fp);
    if (temp == EOF) {
        printf("(empty)\n");
        return ;
    }
    fseek(fp, 0L, 0);
    fscanf(fp, "%s", description);
    printf("%s",description);
    fclose(fp);
    printf("\n");
}
