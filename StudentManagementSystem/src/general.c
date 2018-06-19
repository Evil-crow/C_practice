#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"
#include "../include/management.h"
#include "../include/general.h"
#include "../include/file.h"

void menu(void)
{
    Data *data;
    init(&data);

    int choice;
    while (1) {
        puts("+----------------------------------------------------+");
        printf("                    Menu\n");
        printf("                1. 创建链表\n");
        printf("                2. 添加学生数据\n");
        printf("                3. 删除学生数据\n");
        printf("                4. 修改学生数据\n");
        printf("                5. 查询学生数据\n");
        printf("                6. 打印学生列表\n");
        printf("                7. 学生数据排序\n");
        printf("                8. 学生数据分析\n");
        printf("                9. 数据写回文件\n");
        printf("               10. 退出\n");
        puts("+----------------------------------------------------+");
        scanf("%d", &choice);
        getchar();
        switch(choice) {
            case 1: create_data_list(&(data->list_head)); break;
            case 2: add_new_data(&(data->list_head)); break;
            case 3: del_old_data(&(data->list_head)); break;
            case 4: modify_data(&(data->list_head)); break;
            case 5: find_and_print_data(data->list_head); break;
            case 6: display(data->list_head); break;
            case 7: sort_data(&(data->list_head)); break;
            case 8: analyze_grade(&data); break;
            case 9: save_file(data); break;
            case 10: return;
        }
    }
}

void welcome(void)
{
    char choice;
	printf("\n\n\n\t\t\t\t+------------------------------------------------------------------+\n");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t            Welcome to Students' Grade Management System     \n");
	printf("\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t                 Press [Enter] to Continue\n");
	printf("\n\n\n\n");
	printf("\t\t\t\t    Copyrigtht@2018  All Rights Reserved ShaanXi Science University\n");
	printf("\n");
	printf("\t\t\t\t+------------------------------------------------------------------+\n");
    printf("\t\t\t\t\t\t");
	scanf("%c",&choice);
	if(choice == '\n')
        system("clear");
	return ;
}

void goodbye(void)
{
    system("clear");
    char choice;
    printf("\n\n\n\t\t\t\t+------------------------------------------------------------------+\n");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t                        Goodbye! Have a nice day!     \n");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n");
	printf("\t\t\t\t    Copyrigtht@2018  All Rights Reserved ShaanXi Science University\n");
	printf("\n");
	printf("\t\t\t\t+------------------------------------------------------------------+\n");
    printf("\t\t\t\t\t\t");
    scanf("%c",&choice);
	if(choice == '\n')
        system("clear");
	return ;
}
