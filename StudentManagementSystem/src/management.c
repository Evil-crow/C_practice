#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/list.h"
#include "../include/file.h"
#include "../include/management.h"

void create_data_list(Node **list_head)
{
    char choice;
    char filename[100];

    printf("是否要读入文件(y/N): ");
    scanf("%c", &choice);
    if (choice == 'y') {
        printf("请输入文件名(绝对路径): ");
        scanf("%s", filename);
        (*list_head) = read_from_file(filename);
    } else {
        (*list_head) = create_list();
    }
}

void add_new_data(Node **list_head)
{
    Node *data = (Node *)malloc(sizeof(Node));
    get_data(data);
    add_data(*list_head, data);
}

void del_old_data(Node **list_head)
{
    char number[100];
    printf("请输入删除学生学号: ");
    scanf("%s", number);

    del_data(*list_head, number);
}

void modify_data(Node **list_head)
{
    char number[100];
    printf("请输入要修改学生学号: ");
    scanf("%s", number);
    Node *temp = find_data(*list_head, number);
    if (temp == NULL) {
        printf("未能定位节点\n");
        return ;
    }

    puts("+----------------------------------------------------+");
    printf("请输入学生信息进行修改: ");
    printf("学号: ");
    scanf("%s", temp->number);
    printf("姓名: ");
    scanf("%s", temp->name);
    printf("语文成绩: ");
    scanf("%d", &temp->chineseScore);
    printf("数学成绩: ");
    scanf("%d", &temp->mathScore);
    printf("英语成绩: ");
    scanf("%d", &temp->englishScore);
    puts("+----------------------------------------------------+");
}

void find_and_print_data(Node *list_head)
{
    char number[100];
    printf("请输入查找学生的学号: ");
    scanf("%s", number);

    Node *temp = find_data(list_head, number);
    if (temp == NULL) {
        printf("发生错误，无法查到节点\n");
        return ;
    }
    puts("+----------------------------------------------------+");
    puts("   学号     姓名     语文     数学     英语      平均");
    printf(" %-8s %6s    %3d      %3d      %3d       %.2f\n",
            temp->number, 
            temp->name,
            temp->chineseScore,
            temp->mathScore,
            temp->englishScore,
            temp->average );
    puts("+----------------------------------------------------+");
}

void display(Node *list_head)
{
    print_list(list_head);
}

void sort_data(Node **list_head)
{
    int choice;
    while (1) {
        printf("请选择排序方式: \n");
        printf("1. 按照学号排序\n");
        printf("2. 按照成绩排序\n");
        printf("3. 退出\n");
        scanf("%d", &choice);
        getchar();
        switch(choice) {
            case 1: sort(list_head, sort_number); break;
            case 2: sort(list_head, sort_grade); break;
            case 3: return ;
        }
    }
}

void analyze_grade(Data **data)
{
    if ((*data)->list_head == NULL) {
        printf("发生错误，链表错误\n");
        return ;
    }
    Node *head = (*data)->list_head->next;
    while (head != NULL) {
        if (head->average > (*data)->max_average)
            (*data)->max_average = head->average;
        if (head->average < (*data)->min_average)
            (*data)->min_average = head->average;

        if (head->average > 90) {
            (*data)->A.name[(*data)->A.num++] = head->name;
        } else if (head->average > 72) {
            (*data)->B.name[(*data)->B.num++] = head->name;
        } else if (head->average > 60) {
            (*data)->C.name[(*data)->C.num++] = head->name;
        } else
            (*data)->D.name[(*data)->D.num++] = head->name;
        
        head = head->next;
    }
    display_analyze_data(*data);
}

void display_analyze_data(Data *data)
{
    puts("+----------------------------------------------------+");
    puts("统计信息如下: ");
    printf("最高分: %f, 最低分: %f\n", data->max_average, data->min_average);
    printf("A分段(90 ~ 100): 共计 %d 人", data->A.num);
    for (int i = 0; i < data->A.num; ++i)
        printf(" %s ", data->A.name[i]);
    printf("\n");
    printf("B分段(72 ~ 90): 共计 %d 人", data->B.num);
    for (int i = 0; i < data->B.num; ++i)
        printf(" %s ", data->B.name[i]);
    printf("\n");
    printf("C分段(60 ~ 72): 共计 %d 人", data->C.num);
    for (int i = 0; i < data->C.num; ++i)
        printf(" %s ", data->C.name[i]);
    printf("\n");
    printf("D分段(0 ~ 60): 共计 %d 人", data->D.num);
    for (int i = 0; i < data->D.num; ++i)
        printf(" %s ", data->D.name[i]);
    printf("\n");
    puts("+----------------------------------------------------+");
}

void init(Data **data)
{
    (*data) = (Data *)malloc(sizeof(Data));
    (*data)->list_head = NULL;
    (*data)->list_head = (Node *)malloc(sizeof(Node));
    (*data)->list_head->next = NULL;
    (*data)->max_average = 0;
    (*data)->min_average = 100;
    (*data)->A.num = 0;
    (*data)->B.num = 0;
    (*data)->C.num = 0;
    (*data)->D.num = 0;
}

void save_file(Data *data)
{
    char filename[100];
    printf("请输入要保存的文件: ");
    scanf("%s", filename);

    write_to_file(filename, data);
}



