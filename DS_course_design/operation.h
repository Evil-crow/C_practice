#ifndef _OPERATION_H
#define _OPERATION_H
#include "AdjMatrix.h"

void get_best_path(AdjMatrix *G);

void get_small_tree(AdjMatrix *G);

void get_all_way(AdjMatrix *G);

void get_mininum_transfer_path(AdjMatrix *G);

void add_vexnode(AdjMatrix *G);

void del_vexnode(AdjMatrix *G);

void add_arcs(AdjMatrix *G);

void del_arcs(AdjMatrix *G);

void save_file(AdjMatrix *G);

void map(void);

void map_information(AdjMatrix *G);

// TODO：map地图

// TODO：修改图（增删路线，地点）

    // 地点，修改数组，复制

    // 路线，修改值
#endif
