#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "AdjMatrix.h"

void test(AdjMatrix *G);

void menu(void)
{
    char choice;
    AdjMatrix *G;
    while (1) {
        printf("----------------------School_Navigation-----------------\n\n");
        printf("                    1. Print the map\n\n");
        printf("                    2. Search the information\n\n");
        printf("                    3. Search the path\n\n");
        printf("                    4. Modify the graph\n\n");
        printf("                    5. Exit\n\n");
        printf("--------------------------------------------------------\n\n");
        scanf("%c",&choice);
        getchar( );
        switch(choice - '0')
        {
            case 1: matrix_init(&G); break;
            case 2: menu_path( ); break;
            case 3: test(G); break;
            case 4: matrix_Prim(G, 9); break;
            case 5: exit(0);
            default: break;
        }
    }
}

void menu_path(void)
{
    char choice;

    while (1) {
        printf("----------------------Path_menu------------------------\n\n");
        printf("                 1. Minimum transfer path\n\n");
        printf("                 2. Best path\n\n");
        printf("                 3. All path\n\n");
        printf("                 4. Exit\n\n");
        printf("-------------------------------------------------------\n\n");
        scanf("%c",&choice);
        getchar( );
        switch(choice - '0')
        {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: return;
            default: break;
        }
    }
}

void test(AdjMatrix *G)
{
    int *length, **path;
    char place[20];
    printf("place: ");
    scanf("%s",place);

    int temp = matrix_locate(G, place);

    path = (int **)malloc(sizeof(int *) * G->vexnum);

    for (int i = 0; i < G->vexnum; i++) {
        path[i] = (int *)malloc(sizeof(int) * G->vexnum);
    }

    length = (int *)malloc(sizeof(int) * G->vexnum);

    for (int i = 0; i < G->vexnum; i++) {
        length[i] = 0;
        for (int j = 0; j < G->vexnum; j++)
            path[i][j] = 0;
    }

    printf("Preparation OK!\n");
    matrix_Dijkstra(G, 0, path, length);
    printf("Dijkstra OK!\n");
    for (int i = 0; path[temp][i] != 0; i++) {
        printf("%s ",G->vex[path[temp][i]]);
    }
    printf("\n");
}
