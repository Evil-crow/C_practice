#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"

Node *create_list()
{
    char choice = 'y';
    Node *pTemp;

    Node *list_head = (Node *)malloc(sizeof(Node));
    list_head->next = NULL;
    pTemp = list_head;
    while (choice == 'y') {
        Node *data = (Node *)malloc(sizeof(Node));
        get_data(data);
        data->next = pTemp->next;
        pTemp->next = data;

        printf("Continue(y/N)? ");
        getchar();
        scanf("%c", &choice);
    }

    return list_head;
}

void get_data(Node *data)
{
    puts("+----------------------------------------------------+");
    puts("请输入学生信息: ");
    printf("学号: ");
    scanf("%s", data->number);
    printf("姓名: ");
    scanf("%s", data->name);
    printf("语文成绩: ");
    scanf("%d", &data->chineseScore);
    printf("数学成绩: ");
    scanf("%d", &data->mathScore);
    printf("英语成绩: ");
    scanf("%d", &data->englishScore);
    data->next = NULL;

    data->average = ((double)(data->chineseScore + data->mathScore + data->englishScore)) / 3;

}

void print_list(Node *list_head)
{
    if (list_head == NULL || list_head->next == NULL) {
        printf("发生错误，链表为空\n");
        return ;
    }

    Node *temp = list_head->next;
    puts("+----------------------------------------------------+");
    puts("   学号     姓名     语文     数学     英语      平均");
    while (temp != NULL) {
        printf(" %-8s %6s    %3d      %3d      %3d       %.2f\n",
                temp->number, 
                temp->name,
                temp->chineseScore,
                temp->mathScore,
                temp->englishScore,
                temp->average );
        temp = temp->next;
    }
    puts("+----------------------------------------------------+");
}

Node *find_data(Node *list_head, char *number)
{
    if (list_head == NULL || list_head->next == NULL) {
        printf("发生错误，链表为空\n");
        return NULL;
    }

    Node *temp = list_head->next;
    while (temp != NULL) {
        if (strcmp(temp->number, number) == 0)
            return temp;
        temp = temp->next;
    }

    return NULL;
}

Node *del_data(Node *list_head, char *number)
{
    if (list_head == NULL || list_head->next == NULL) {
        printf("发生错误，链表为空\n");
        return list_head;
    }

    Node *prev, *temp, *target;
    target = find_data(list_head, number);
    if (target == NULL) {
        printf("发生错误，无法定位节点\n");
        return list_head;
    }

    prev = list_head;
    temp = prev->next;
    while (temp != NULL) {
        if (temp == target) {
            prev->next = temp->next;
            return list_head;
        }
        prev = temp;
        temp = temp->next;
    }
}

Node *add_data(Node *list_head, Node *data)
{
    if (list_head == NULL) {
        printf("发生错误，链表不存在\n");
        return list_head;
    }

    data->next = list_head->next;
    list_head->next = data;

    return list_head;
}

void sort(Node **list_head, int (*compare)(Node *stu1, Node *stu2))
{
    int count  = 0;
    Node *fuck = (*list_head)->next;
    while (fuck) {
        ++count;
        fuck = fuck->next;
    }

    for (int i = 0; i < count; ++i)
        for (Node *temp = (*list_head); temp->next->next != NULL; temp = temp->next)
            if (compare(temp->next, temp->next->next)) {
                Node *cur = temp->next;
                Node *loop = temp->next->next;
                cur->next = loop->next;
                temp->next = loop;
                loop->next = cur;
            }
}

int sort_number(Node *stu1, Node *stu2)
{
    return (strcmp(stu1->number, stu2->number) > 0) ? 1 : 0;
}

int sort_grade(Node *stu1, Node *stu2)
{
    return stu1->average > stu2->average ? 1 : 0;
}