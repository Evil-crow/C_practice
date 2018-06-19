#ifndef _LIST_H
#define _LIST_H

typedef struct student {
    char number[10];
    char name[100];
    int chineseScore;
    int mathScore;
    int englishScore;
    float average;
    struct student *next;
}Node;

typedef struct grade_status {
    int num;
    const char *name[100];
}Status;

typedef struct data {
    Node *list_head;
    float max_average;
    float min_average;
    Status A;
    Status B;
    Status C;
    Status D;
    int student_num;
}Data;

Node *create_list();

void get_data(Node *node);

Node *del_data(Node *list_head, char *number);          // 根据唯一学号进行删除

Node *add_data(Node *list_head, Node *data);

Node *find_data(Node *list_head, char *number);         // 根据唯一学号进行查找

void print_list(Node *list_head);

void sort(Node **list_head, int (*compare)(Node *stu1, Node *stu2));

int sort_grade(Node *stu1, Node *stu2);

int sort_number(Node *stu1, Node *stu2);

#endif