#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/file.h"
#include "../include/list.h"

Node *read_from_file(const char *filename)
{
    FILE *fp;
    Node *file_list;

    fp = fopen(filename, "r+");
    if (!fp) {
        printf("发生错误，打开文件失败！\n");
        return NULL;
    }

    if (fgetc(fp) == EOF) {
        printf("发生错误，文件为空！\n");
        return NULL;
    }
    fseek(fp, 0L, 0);

    
    file_list = (Node *)malloc(sizeof(Node));
    file_list->next == NULL;
    
    fseek(fp, 0L, 0);
    while (!feof(fp)) {
        Node *data = (Node *)malloc(sizeof(Node));
        fscanf(fp, "%s %s %d %d %d %f\n", 
            data->number,
            data->name,
            &data->chineseScore,
            &data->mathScore,
            &data->englishScore,
            &data->average);
        data->next = NULL;
        file_list = add_data(file_list, data);
    }
    fclose(fp);

    return file_list;
}

void write_to_file(const char *filename, Data *data)
{
    FILE *fp = fopen(filename, "w+");
    if (fp == NULL) {
        printf("发生错误，无法定位文件\n");
        return ;
    }

    if (data->list_head == NULL) {
        printf("发生错误，链表不存在\n");
        return ;
    }

    Node *temp = data->list_head->next;
    while (temp != NULL) {
        fprintf(fp, "%s %s %d %d %d %f\n",
                temp->number,
                temp->name,
                temp->chineseScore,
                temp->mathScore,
                temp->englishScore,
                temp->average);
        temp = temp->next;
    }
    
    fclose(fp);
}