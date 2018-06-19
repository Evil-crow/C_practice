#ifndef _MANAGEMENT_H
#define _MANAGEMENT_H

#include "../include/list.h"

void menu(void);            // ������Ϣ����ʾ

void analyze_grade(Data **data);

void create_data_list(Node **list_head);

void init(Data **data);

void add_new_data(Node **list_head);

void del_old_data(Node **list_head);

void modify_data(Node **list_head);

void find_and_print_data(Node *list_head);

void display(Node *list_head);

void sort_data(Node **list_head);

void display_analyze_data(Data *data);

void save_file(Data *data);

#endif