#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "AdjMatrix.h"
#include "operation.h"

void menu(void)
{
    char choice;
    AdjMatrix *G;
    while (1) {
        printf("----------------------School_Navigation-----------------\n\n");
        printf("                    1. Print the map\n\n");
        printf("                    2. Search the information\n\n");
        printf("                    3. Search the path\n\n");
        printf("                    4. Best layout path\n\n");
        printf("                    5. Modify the graph\n\n");
        printf("                    6. Exit\n\n");
        printf("--------------------------------------------------------\n\n");
        scanf("%c",&choice);
        getchar( );
        switch(choice - '0')
        {
            case 1: matrix_init(&G); break;
            case 2: menu_path(G); break;
            case 3: break;
            case 4: get_small_tree(G); break;
            case 5: matrix_Prim(G, 9); break;
            case 6: exit(0);
            default: break;
        }
    }
}

void menu_path(AdjMatrix *G)
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
            case 1: get_mininum_transfer_path(G); break;
            case 2: get_best_path(G); break;
            case 3: get_all_way(G); break;
            case 4: return;
            default: break;
        }
    }
}
