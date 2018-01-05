/****************************************************************
  Author:Evilcrow
  E-mail:Evilcrow486@gmail.com
  Date:2017/06/30
****************************************************************/

#include<stdio.h>
#include<stdlib.h>                        //malloc( )的头文件
#include<string.h>                        //字符串函数头文件
                                          //实现getch功能依靠system("stty -echo")
typedef struct bicycle                    //自行车信息结构体
{
    int number;
    char brand[15];
    char owner[20];
    char place;
    char date[14];
    struct bicycle *next;
}Node;

typedef struct log                        //注册登录用户信息结构体
{
    char username[20];
    char passwd[20];
    struct log *next;
}User;

struct information                       //进行信息统计时的结构体
{
    int number;
    char place;
};

char filename1[20];                       //存储读文件名的全局变量

char filename2[20];                       //存储写文件名的全局变量

Node *file_read(void);                    //读文件函数并创建链表

Node *file_save(Node *);                   //保存文件函数

void print(Node *);                       //信息遍历函数

Node *append_data(Node *);                 //信息追加函数

void seek_menu(Node *);                   //查询菜单函数

void seek_place_print(Node *);            //停车区域查询函数

void seek_date_print(Node *);             //日期查询函数

void seek_brand_place_print(Node *);      //品牌以及停车区域额的复合查询

Node *seek_number(Node *,int );            //查找节点函数

void modify_menu(Node *);                 //修改数据菜单函数

Node *modify_place(Node *);                 //修改停车区域

Node *modify_date(Node *);                 //修改登记日期

Node *modify_owner(Node *);                //修改车主

Node *insert_data(Node *);                 //插入数据函数

Node *del_data(Node *);                   //删除数据函数

void sort_menu(Node *);                    //排序菜单函数

Node *ascending_sort(Node *,int );         //升序排序

Node *descending_sort(Node *,int );         //降序排序

int count(Node *);                         //节点计算函数

void information_menu(Node *);             //信息统计菜单

void simple_information(Node *);           //简单信息统计

void comflict_information(Node *);          //复杂信息统计

void menu(void);                           //主菜单函数

void the_page(void);                       //使用说明函数

void About(void);                         //关于函数

void cover(void);                          //封面函数

User *File_read(void);                      //用户读文件函数

int log_in(User *);                          //登陆函数

void register_user(User *);                 //注册用户函数

void log_in_menu(void);                      //用户登陆菜单

int main(void)
{
    system("clear");
    Node *pHead;
    int choice = 20;
    int n;

    cover( );
    n = log_in_menu( );
    if(n == 0)
        return 0;
    system("clear");                        //清屏进入主函数菜单
	menu( );
    while(choice != 0)
    {
		switch(choice)                    //switch进行菜单功能的选择
                {
                    case 1:
                            pHead = file_read( );
                            break;
                    case 2:
                        system("clear");
                        printf("\n\n\n\t\t\t\t");
                        pHead = append_data(pHead);
                        system("clear");
                        menu(  );
                        break;
                    case 3:
                        system("clear");
                        seek_menu(pHead);
                        menu( );
                        break;
                    case 4:
                        system("clear");
                        modify_menu(pHead);
                        menu( );
                        break;
                    case 5:
                        system("clear");
                        printf("\n\n\n\t\t\t\t");
                        pHead = insert_data(pHead);
                        menu(  );
                        break;
                    case 6:
                        system("clear");
                        printf("\n\n\n\t\t\t\t");
                        pHead = del_data(pHead);
                        menu(  );
                        break;
                    case 7:
                        system("clear");
                        sort_menu(pHead);
                        menu( );
                        break;
                    case 8:
                        system("clear");
                        information_menu(pHead);
                        menu( );
                        break;
                    case 9:
                        system("clear");
                        printf("\n\n\n");
                        print(pHead);
                        printf("\n\t\t\t\t");
                        getchar(  );
                        system("clear");
                        menu(  );
                        break;
                    case 10:
                        pHead = file_save(pHead);
                        break;
                    case 11:
                        system("clear");
                        the_page( );
                        menu( );
                        break;
                    case 12:
                        system("clear");
                        About( );
                        menu( );
                        break;
                    case 0:
                        exit(0);
		}
    	printf("\t\t\t\tPlease input your choice:");
    	scanf("%d",&choice);                                     //循环进行功能的选择
    	getchar( );
	}
}

Node *file_read(void)
{
    FILE *fp;
    printf("\t\t\t\tplease input the file_name:");
    scanf("%s",filename1);                           //保存要打开的文件名
    getchar( );
    fp = fopen(filename1,"r+");                     //以“可读”打开文件
    if(fp == NULL)
    {
        printf("\t\t\t\tError,Can't open the file!\n");
        return NULL;
    }


    Node *pHead;
    Node *pNew;
    Node *pEnd;

    pHead = (Node *)malloc(sizeof(Node));             //创建带头节点的链表
    pHead->next = NULL;
    pEnd = pHead;                                    //保存当前结点
    if(fgetc(fp) == EOF)
    {
        printf("\t\t\t\tThe file is empty!\n");
        return pHead;
    }
    fseek(fp,0L,0);                                    //使文件指针重新回到文件开头

    while(!feof(fp))                               //当文件未结束时，循环读取文件内容
    {
        pNew = (Node *)malloc(sizeof(Node));
        if(pNew == NULL)
        {
            printf("\t\t\t\tError!Can't creat the list!");
            return NULL;
        }
        fscanf(fp,"%d %s %s %c %s\n",&pNew->number,pNew->brand,pNew->owner,&pNew->place,pNew->date);
        pNew->next = NULL;
        pEnd->next = pNew;
        pEnd = pNew;
    }

    printf("\t\t\t\tAll information has been read!\n");
    fclose(fp);                                      //关闭文件，否则会丢失数据
    return pHead;                                     //返回链表的头结点
}

Node *append_data(Node *pHead)
{
    Node *temp;
    temp = pHead;
    while(temp->next != NULL)                      //循环指向当前链表的最后一个节点
        temp = temp->next;
    Node *pNew;
    Node *pEnd;
    pEnd = temp;

    int n;
    printf("\n\t\t\t\tplease input the number of the node:");
    scanf("%d",&n);                                //存取想要添加的节点数
    getchar( );
    while(n--)                                       //循环添加节点
    {
        printf("\n");
        char place;
        pNew = (Node *)malloc(sizeof(Node));         //动态内存分配新节点
        if(pNew == NULL)
        {
            printf("\t\t\t\tError,Can't creat the list!\n");
            return NULL;
        }
        printf("\t\t\t\tplease input your number:");
        scanf("%d",&pNew->number);                   // 保存节点信息
        getchar( );
        printf("\t\t\t\tplease input your brand:");
        scanf("%s",pNew->brand);
        getchar( );
        printf("\t\t\t\tplease input your owner:");
        scanf("%s",pNew->owner);
        getchar( );
        printf("\t\t\t\tplease input your place:");
        scanf("%c",&place);
        getchar( );
        while(place < 'A' || place > 'F')           //进行停车区域的判别
        {
            printf("\t\t\t\tError,please input the correct parking-place:");
            scanf("%c",&place);
        }
        pNew->place = place;
        printf("\t\t\t\tplease input your date:");
        scanf("%s",pNew->date);
        getchar( );

        pNew->next = NULL;                        //使链表结构继续连接
        pEnd->next = pNew;
        pEnd = pNew;
    }

    return pHead;                                //返回头节点
}

void print(Node *pHead)
{
    Node *temp;                               //用于遍历的节点
    temp = pHead->next;
    if(temp == NULL)
    {
        printf("\t\t\t\tError,the list is empty!\n");
        return ;
    }
    printf("\t\t\t\t====================================================\n");
    printf("\t\t\t\tNumber   Brand    Owner    Place  Date\n");
    printf("\t\t\t\t====================================================\n");
    while(temp != NULL)                     //在节点指空前，遍历信息并打印
    {
        printf("\t\t\t\t%-8d %-8s %-8s %c      %-14s\n",temp->number,temp->brand,temp->owner,temp->place,temp->date);
		temp = temp->next;
    }
    printf("\t\t\t\t====================================================\n");
}

Node *file_save(Node *pHead)
{
    FILE *fp;
    printf("\t\t\t\tplease input the filename you want to save:");
    scanf("%s",filename2);                         //输入想要保存的文件名
    fp = fopen(filename2,"w+");
    if(fp == NULL)
    {
        printf("\t\t\t\tError,Can't write into the file!\n");
        return NULL;
    }

    Node *temp;
    temp = pHead->next;

    while(temp != NULL)                       //将每一个节点的信息依次保存入文件
    {
        fprintf(fp,"%d %s %s %c %s\n",temp->number,temp->brand,temp->owner,temp->place,temp->date);
        temp = temp->next;
    }

    printf("\t\t\t\tAll information ha been saved!\n");
    fclose(fp);                               //关闭文件

    return pHead;
}

void seek_menu(Node *pHead)
{
    int choice;
    printf("\n\n\n\t\t\t\t************************************************************\n");
    printf("\t\t\t\t                        Seek   Menu                         \n");
    printf("                                                                                \n");
    printf("\t\t\t\t                     1.Seek by place                        \n");
    printf("                                                                                \n");
    printf("\t\t\t\t                     2.Seek by date                         \n");
    printf("                                                                                \n");
    printf("\t\t\t\t                     3.Seek by brand and place              \n");
    printf("                                                                                \n");
    printf("\t\t\t\t                     0.quit                                 \n");
    printf("                                                                                \n");
    printf("\t\t\t\t************************************************************\n");
    printf("\t\t\t\tplease input your choice:");
    scanf("%d",&choice);
    while(choice != 0)                             //循环进行菜单功能的选择
    {
        switch(choice)
        {
            case 1:
                seek_place_print(pHead);
                break;
            case 2:
                seek_date_print(pHead);
                break;
            case 3:
                seek_brand_place_print(pHead);
                break;
            case 0:
                return;
        }
        printf("\t\t\t\tplease input your choice:");
        scanf("%d",&choice);
    }
    system("clear");
}

void seek_place_print(Node *pHead)
{
    char place;
    Node *temp;
    int flag = 0;

    printf("\t\t\t\tplease input the place:");
    scanf("%c",&place);
    place = getchar( );
    temp = pHead->next;

    if(pHead == NULL || temp == NULL)
    {
        printf("\t\t\t\tError! Can't seek the data!\n");
        return;
    }
    printf("\t\t\t\t====================================================\n");
    printf("\t\t\t\tNumber   Brand    Owner    Place  Date\n");
    printf("\t\t\t\t====================================================\n");
    while(temp != NULL)
    {
        if(temp->place == place)                        //如果该节点信息与所查找信息匹配，则打印节点信息
        {
            printf("\t\t\t\t%-8d %-8s %-8s %c      %-12s\n",temp->number,temp->brand,temp->owner,temp->place,temp->date);
            flag++;
        }
        temp = temp->next;
    }
    if(flag == 0)
        printf("\n\t\t\t\tError! No data!\n");
    printf("\t\t\t\t====================================================\n");
}

void seek_date_print(Node *pHead)
{
    char date[14];
    Node *temp;
    int flag = 0;

    printf("\t\t\t\tplease input the date:");
    scanf("%s",date);
    temp = pHead->next;
    if(pHead == NULL || temp == NULL)
    {
        printf("\t\t\t\tError! Can't seek the data!\n");
        return;
    }
    printf("\t\t\t\t====================================================\n");
    printf("\t\t\t\tNumber   Brand    Owner    Place  Date\n");
    printf("\t\t\t\t====================================================\n");
    while(temp != NULL)
    {
        if(strcmp(temp->date,date) == 0)                  //同上例
        {
            printf("\t\t\t\t%-8d %-8s %-8s %c      %-14s\n",temp->number,temp->brand,temp->owner,temp->place,temp->date);
            flag++;
        }
        temp = temp->next;
    }
    if(flag == 0)
        printf("\n\t\t\t\tError! No data!\n");
    printf("\t\t\t\t====================================================\n");

}

void seek_brand_place_print(Node *pHead)
{
    char brand[8];
    char place;
    Node *temp;
    int flag = 0;

    printf("\t\t\t\tplease input the brand and the place (with blank):");
    scanf("%s %c",brand,&place);
    getchar( );
    temp = pHead->next;
    if(pHead == NULL || temp == NULL)
    {
        printf("\t\t\t\tError! Can't seek the data!\n");
        return;
    }
    printf("\t\t\t\t====================================================\n");
    printf("\t\t\t\tNumber   Brand    Owner    Place  Date\n");
    printf("\t\t\t\t====================================================\n");
    while(temp != NULL)
    {
        if(temp->place == place)                      //复合查询，即将两次普通查询进行结合，双重选择结构
        {
            if(strcmp(temp->brand,brand) == 0)
            {
                printf("\t\t\t\t%-8d %-8s %-8s %c      %-12s\n",temp->number,temp->brand,temp->owner,temp->place,temp->date);
                flag++;
            }
        }
        temp = temp->next;
    }
    if(flag == 0)
        printf("\n\t\t\t\tError! No data!\n");
    printf("\t\t\t\t====================================================\n");
}

Node *seek_number(Node *pHead,int number)
{
	Node *temp;
	Node *prev;
	temp = pHead->next;
	if(pHead == NULL || temp == NULL)
	{
		printf("\t\t\t\tError! The list is empty!\n");
		return NULL;
	}
	while(temp != NULL)
	{
		if(temp->number == number)              //如果符合要求
		return temp;                            //则返回节点
		prev = temp;
		temp = temp->next;                     //否则继续遍历
	}
	if(temp == NULL && prev->number != number)
		return NULL;
}

void modify_menu(Node *pHead)
{
	int choice = 8;
	printf("\n\n\n\t\t\t\t*************************************************************\n");
    printf("\t\t\t\t                       Modify   Menu                         \n");
    printf("                                                                                 \n");
    printf("\t\t\t\t                    1.Modify the place                       \n");
    printf("                                                                                 \n");
    printf("\t\t\t\t                    2.Modify the date                        \n");
    printf("                                                                                 \n");
    printf("\t\t\t\t                    3.Modify the owner                       \n");
    printf("                                                                                 \n");
    printf("\t\t\t\t                    0.quit                                   \n");
    printf("                                                                                 \n");
    printf("\t\t\t\t*************************************************************\n");
    printf("\t\t\t\tplease input your choice:");
    scanf("%d",&choice);
    while(choice != 0)
    {
    	switch(choice)                               //循环进行修改功能的选择
    	{
    		case 1:
    			pHead = modify_place(pHead);
    			break;
    		case 2:
    			pHead = modify_date(pHead);
    			break;
    		case 3:
    			pHead = modify_owner(pHead);
    			break;
    		case 0:
    			return ;
		}
		printf("\t\t\t\tplease input your choice:");
		scanf("%d",&choice);
		getchar( );
	}
	system("clear");
}

Node *modify_place(Node *pHead)
{
	int number;
	char c = 'Y';
	char place;
	Node *temp;

	while(c == 'Y')
	{
		printf("\t\t\t\tplease input your number:");
		scanf("%d",&number);
		getchar( );
		temp = seek_number(pHead,number);
		if(temp == NULL)                                      //如果符合要求，则对其录入新的节点信息
		{
			printf("\t\t\t\tcan't find the data!\n");
			return pHead;
		}
		printf("\t\t\t\tplease input the place you want to modify:");
		scanf("%c",&place);
		getchar( );
		while(place < 'A' || place > 'F')
		{
			printf("\t\t\t\tError! please input the correct parking-place:");
			scanf("%c",&place);
			getchar( );
		}
		temp->place = place;
		printf("\t\t\t\tThe informaton has been modified!\n");
		printf("\t\t\t\tcontinue?(Y/n):");
		scanf("%c",&c);
		getchar( );
	}

}

Node *modify_date(Node *pHead)                          //同上例
{
	int number;
	char c = 'Y';
	char date[14];
	Node *temp;

	while(c == 'Y')
	{
		printf("\t\t\t\tplease input your number:");
		scanf("%d",&number);
		getchar( );
		temp = seek_number(pHead,number);
		if(temp == NULL)
		{
			printf("\t\t\t\tcan't find the data!\n");
			return pHead;
		}
		printf("\t\t\t\tplease input the date you want to modify:");
		scanf("%s",date);
		getchar( );

		strcpy(temp->date,date);
		printf("\t\t\t\tThe informaton has been modified!\n");
		printf("\t\t\t\tcontinue?(Y/n):");
		scanf("%c",&c);
		getchar( );
	}
}

Node *modify_owner(Node *pHead)                          //同上例
{
	int number;
	char c = 'Y';
	char owner[8];
	Node *temp;

	while(c == 'Y')
	{
		printf("\t\t\t\tplease input your number:");
		scanf("%d",&number);
		getchar( );
		temp = seek_number(pHead,number);
		if(temp == NULL)
		{
			printf("\t\t\t\tcan't find the data!\n");
			return pHead;
		}
		printf("\t\t\t\tplease input the owner you want to modify:");
		scanf("%s",owner);
		getchar( );

		strcpy(temp->owner,owner);
		printf("\t\t\t\tThe informaton has been modified!\n");
		printf("\t\t\t\tcontinue?(Y/n):");
		scanf("%c",&c);
		getchar( );
	}
}

Node *insert_data(Node *pHead)
{
	int number;
	char place;
	char choice = 'Y';
	Node *temp;
	printf("\t\t\t\tplease input your target number:");
	scanf("%d",&number);
	getchar( );
	temp = seek_number(pHead,number);                  //使用seek_number函数获取节点值
	if(temp == NULL)
	{
		printf("\t\t\t\tError Can't find the data\n");
		return pHead;
	}
	Node *cur;
	Node *prev;
	prev = temp;
	cur = (Node *)malloc(sizeof(Node));                //重新分配新的节点内存
	if(cur == NULL)
	{
		printf("\t\t\t\tError,Can't insert the list\n");
		return pHead;
	}
	printf("\t\t\t\tplease input the number:");
	scanf("%d",&cur->number);
	getchar( );
	printf("\t\t\t\tplease input your brand:");
	scanf("%s",cur->brand);
	getchar( );
	printf("\t\t\t\tplease input your owner:");
	scanf("%s",cur->owner);
	getchar( );
	printf("\t\t\t\tplease input your place:");
	scanf("%c",&place);
	getchar( );
	while(place < 'A' || place > 'F')
    {
        printf("\t\t\t\tError,please input the correct parking-place:");
        scanf("%c",&place);
    }
    cur->place = place;
	printf("\t\t\t\tplease input your date:");
	scanf("%s",cur->date);
	getchar( );
	printf("\t\t\t\tContinue?(Y/n)");
	scanf("%c",&choice);
	getchar( );
	while(choice == 'Y')                           //循环插入信息，提高效率
	{
		cur->next = prev->next;
		prev->next = cur;
		prev = cur;
		cur = (Node *)malloc(sizeof(Node));
		if(cur == NULL)
		{
			printf("\t\t\t\tError! Can't creat a new list");
			return NULL;
		}
		printf("\t\t\t\tplease input the number:");
		scanf("%d",&cur->number);
		getchar( );
		printf("\t\t\t\tplease input your brand:");
		scanf("%s",cur->brand);
		getchar( );
		printf("\t\t\t\tplease input your owner:");
		scanf("%s",cur->owner);
		getchar( );
		printf("\t\t\t\tplease input your place:");
		scanf("%c",&place);
		getchar( );
		while(place < 'A' || place > 'F')
        {
            printf("\t\t\t\tError,please input the correct parking-place:");
            scanf("%c",&place);
        }
        cur->place = place;
		printf("\t\t\t\tplease input your date:");
		scanf("%s",cur->date);
		getchar( );
		printf("\t\t\t\tContinue?(Y/n)");
		scanf("%c",&choice);
		getchar( );
	}
	cur->next = prev->next;
	prev->next = cur;

	return pHead;
}

Node *del_data(Node *pHead)
{
	Node *temp;
	Node *cur;
	Node *prev;
	int choice = 'Y';
	int number;

	while(choice == 'Y')
	{
	    cur = pHead;
		printf("\t\t\t\tplease input the number you want to delete:");
		scanf("%d",&number);
		getchar( );
		temp = seek_number(pHead,number);                          //同样使用seek_number函数查找结点
		if(temp == NULL)
		{
			printf("\t\t\t\tError! Can't find the data\n");
			return pHead;
		}
		while(cur != temp)
		{
			prev = cur;                        //保存目标节点上一个节点的信息
			cur = cur->next;
		}
		prev->next = cur->next;                  //删除目标节点
		printf("\t\t\t\tThe information has been delete!\n");
		printf("\t\t\t\tContinue?(Y/n):");
		scanf("%c",&choice);
		getchar( );
	}

	return pHead;
}

void sort_menu(Node *pHead)
{
	int choice = 9;
	int number;
	printf("\n\n\n\t\t\t\t************************************************************\n");
    printf("\t\t\t\t                        Sort   Menu                         \n");
    printf("                                                                                \n");
    printf("\t\t\t\t                    1.ascending_sort                        \n");
    printf("                                                                                \n");
    printf("\t\t\t\t                    2.descending_sort                       \n");
    printf("                                                                                \n");
    printf("\t\t\t\t                    0.quit                                  \n");
    printf("                                                                                \n");
    printf("\t\t\t\t************************************************************\n");

	number = count(pHead);
	if(number == 0)
	{
		printf("\t\t\t\tThe list is 0 Node\n We can't sort the data!\n");
	}
	printf("\t\t\t\tplease input your choice:");
	scanf("%d",&choice);
	getchar( );
	while(choice != 0)                    //循环进行排序功能的选择
	{
		switch(choice)
		{
			case 1:
				pHead = ascending_sort(pHead,number);
				break;
			case 2:
				pHead = descending_sort(pHead,number);
				break;
			case 0:
				return ;
		}
		printf("\t\t\t\tplease input your choice:");
		scanf("%d",&choice);
		getchar( );
	}
	system("clear");
}

int count(Node *pHead)
{
	Node *temp;
	int count = 0;
	temp = pHead->next;
	if(pHead == NULL || pHead->next == NULL)
	return 0;                                //如果头结点为空，返回0节点
	while(temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return count;                            //返回目标节点数
}

Node *ascending_sort(Node *pHead,int count)
{
	Node *temp;
	while(count--)                                  //外层循环
	{
		for(temp = pHead;temp->next->next != NULL;temp = temp->next)     //内层循环
		{
			if(temp->next->number > temp->next->next->number)          //如果符合交换条件
			{
				Node *cur = temp->next;
				Node *loop = temp->next->next;
				cur->next = loop->next;
				temp->next = loop;
				loop->next = cur;
			}
		}
	}
	temp->next->next = NULL;
	printf("\t\t\t\tThe data has been sorted!\n");

	return pHead;
}

Node *descending_sort(Node *pHead,int count)                     //同上例
{
	Node *temp;
	while(count--)
	{
		for(temp = pHead;temp->next->next != NULL;temp = temp->next)
		{
			if(temp->next->number < temp->next->next->number)
			{
				Node *cur = temp->next;
				Node *loop = temp->next->next;
				cur->next = loop->next;
				temp->next = loop;
				loop->next = cur;
			}
		}
	}
	printf("\t\t\t\tThe data has been sorted!\n");

	return pHead;
}

void information_menu(Node *pHead)
{
	int choice;
	printf("\n\n\n\t\t\t\t************************************************************\n");
    printf("\t\t\t\t                   Information   Menu                       \n");
    printf("                                                                                \n");
    printf("\t\t\t\t                 1.Simple  information                      \n");
    printf("                                                                                \n");
    printf("\t\t\t\t                 2.Comflict  information                    \n");
    printf("                                                                                \n");
    printf("\t\t\t\t                 0.quit                                     \n");
    printf("                                                                                \n");
    printf("\t\t\t\t************************************************************\n");
    printf("\t\t\t\tplease input your choice:");
    scanf("%d",&choice);
    getchar( );
    while(choice != 0)                                    //循环进行信息统计功能的选择
    {
    	switch(choice)
    	{
    		case 1:
    			simple_information(pHead);
    			break;
    		case 2:
    			comflict_information(pHead);
    			break;
    		case 0:
    			return;
		}
		printf("\t\t\t\tplease input your choice:");
		scanf("%d",&choice);
		getchar( );
	}
	system("clear");
}

void simple_information(Node *pHead)
{
	Node *temp;
	int A,B,C,D,E,F;
	A = B = C = D = E = F = 0;
	temp = pHead->next;
	if(pHead == NULL || temp == NULL)
	{
		printf("\t\t\t\tError! Can't analyze the data!\n");
		return;
	}
	while(temp != NULL)                                       //遍历节点的同时进行信息统计
	{
		if(temp->place == 'A')
		A++;
		else if(temp->place == 'B')
		B++;
		else if(temp->place == 'C')
		C++;
		else if(temp->place == 'D')
		D++;
		else if(temp->place == 'E')
		E++;
		else
		F++;
		temp = temp->next;
	}
	printf("\t\t\t\tA-area: %d  bicycle(s)\n",A);
	printf("\t\t\t\tB-area: %d  bicycle(s)\n",B);
	printf("\t\t\t\tC-area: %d  bicycle(s)\n",C);
	printf("\t\t\t\tD-area: %d  bicycle(s)\n",D);
	printf("\t\t\t\tE-area: %d  bicycle(s)\n",E);
	printf("\t\t\t\tF-area: %d  bicycle(s)\n",F);
}

void comflict_information(Node *pHead)
{
    Node *temp;
    temp = pHead;
    if(temp == NULL || pHead->next == NULL)
    {
        printf("\t\t\t\tError! Can't analyze the data!\n");
        return ;
    }

    struct information ofo[6];
    int t;
    char ch = 'A';
    for(t = 0;t < 6;t++,ch++)
    {
        ofo[t].place = ch;
        ofo[t].number = 0;
    }

	temp = pHead->next;
	if(pHead == NULL || temp == NULL)
	{
		printf("\t\t\t\tError! Can't analyze the data!\n");
		return;
	}
	while(temp != NULL)
	{
		if(temp->place == 'A')
		ofo[0].number++;
		else if(temp->place == 'B')
		ofo[1].number++;
		else if(temp->place == 'C')
		ofo[2].number++;
		else if(temp->place == 'D')
		ofo[3].number++;
		else if(temp->place == 'E')
		ofo[4].number++;
		else
		ofo[5].number++;
		temp = temp->next;
	}

	int max = -99;
	for(t = 0;t < 6;t++)
	{
		if(max < ofo[t].number)
            max = ofo[t].number;
	}
	printf("\t\t\t\tThe most Parking-place is:\n");
	printf("\t\t\t\t");
	for(t = 0;t < 6;t++)
    {
        if(ofo[t].number == max)
            printf("%c area %d bicycle(s),",ofo[t].place,ofo[t].number);
    }
    printf("\n\t\t\t\t");
    printf("\n");

}

void menu(void)                                    //菜单打印
{
	printf("\n\n\n\t\t\t\t************************************************************\n");
	printf("                                                                                \n");
	printf("\t\t\t\t          Welcome to Workers' Bicycle Management Menu       \n");
	printf("                                                                                \n");
	printf("\t\t\t\t             1.Get information from the file                \n");
	printf("                                                                                \n");
	printf("\t\t\t\t             2.Append the data to the Link_list             \n");
	printf("                                                                                \n");
	printf("\t\t\t\t             3.Search the target informaton and print it    \n");
	printf("                                                                                \n");
	printf("\t\t\t\t             4.Modify the data                              \n");
	printf("                                                                                \n");
	printf("\t\t\t\t             5.Insert the data to the Link_list             \n");
	printf("                                                                                \n");
	printf("\t\t\t\t             6.Delete the data from the Link_list           \n");
	printf("                                                                                \n");
	printf("\t\t\t\t             7.Sort the data                                \n");
	printf("                                                                                \n");
	printf("\t\t\t\t             8.Some information about the data              \n");
	printf("                                                                                \n");
	printf("\t\t\t\t             9.Print the data as the form                   \n");
	printf("                                                                                \n");
	printf("\t\t\t\t            10.Write the information to the file            \n");
	printf("                                                                                \n");
	printf("\t\t\t\t            11.The instrustions of the system               \n");
	printf("                                                                                \n");
	printf("\t\t\t\t            12.About                                        \n");
	printf("                                                                                \n");
	printf("\t\t\t\t             0.quit                                         \n");
	printf("                                                                                \n");
	printf("\t\t\t\t************************************************************\n");
}

void the_page(void)                               //使用说明打印
{
	int choice = 9;
	printf("\n\n\n\t\t\t\t************************************************************\n");
	printf("\n\n\t\t\t\t         Please read the instrustions seriously             \n");
	printf("                                                            \n");
	printf("\t\t\t\tThis system is used to manage the workers' bicycle information\n");
	printf("\n");
	printf("\t\t\t\tBut you need to know how to use this system:\n");
	printf("\n");
	printf("\t\t\t\tWell,first you need to know that this system is very easy \n");
	printf("\n");
	printf("\t\t\t\t1.The Node->number mustn't start as '0' \n");
	printf("\n");
	printf("\t\t\t\t2.Do your choice by input the number\n");
	printf("\n");
	printf("\t\t\t\t3.I have set a short time for you to analyse the data\n");
	printf("\n");
	printf("\t\t\t\t  I achieved this function by function-getchar( )\n");
	printf("\n");
	printf("\t\t\t\t  if your have noted the data,Well press[Enter] to continue!\n");
	printf("\n");
	printf("\t\t\t\t4.And you must remember that input the date as \"yyyy/mm/dd\"\n");
	printf("\n");
	printf("\t\t\t\t5.This C program must start by the choice 1,open an existed file!");
	printf("\n");
	printf("\t\t\t\t************************************************************\n");
	printf("\n\n\t\t\t\tPress [0] to getback!\n");
	printf("\t\t\t\t");
	scanf("%d",&choice);
	if(choice == 0)
        system("clear");
	return ;
}

void About(void)                                   //关于打印
{
	int choice = 9;
	printf("\n\n\n\t\t\t\t************************************************************\n");
	printf("\n\t\t\t\t              Works' Bicycle Management System v2.0         \n");
	printf("\n");
	printf("\n\t\t\t\t                Author:Evilcrow                             \n");
	printf("\n");
	printf("\n\t\t\t\t                Mail:Evilcrow486@gmail.com                  \n");
	printf("\n");
	printf("\n\t\t\t\t                Version:v2.0  (Linux English)\n");
	printf("\n");
	printf("\n\t\t\t\t                @Copyright belongs to Evilcrow\n");
	printf("\n");
	printf("\t\t\t\t************************************************************\n");
	printf("\n\n\t\t\t\tPress [0] to go back to the Main menu\n\n");
	printf("\t\t\t\t");
	scanf("%d",&choice);
	getchar( );
	if(choice == 0)
        system("clear");
	return ;
}

void cover(void)                                   //封面信息打印
{
	char choice;
	printf("\n\n\n\t\t\t\t###################################################################\n");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t            Welcome to Works' Bicycle Management System     \n");
	printf("\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t                 Press [Enter] to Continue\n");
	printf("\n\n\n\n");
	printf("\t\t\t\t    Copyrigtht@2017  All Rights Reserved Xiyou Computer_Science\n");
	printf("\n");
	printf("\t\t\t\t####################################################################\n");
    printf("\t\t\t\t\t\t");
	scanf("%c",&choice);
	if(choice == '\n')
        system("clear");
	return ;
}

User *File_read(void)
{
    User *pHead,*pNew,*pEnd;
    FILE *fp;
    fp = fopen("user","r");                  //打开用户信息文件
    if(fp == NULL)
    {
        printf("Error1");
        return NULL;
    }
    pHead = (User *)malloc(sizeof(User));
    if(fgetc(fp) == EOF)
    {
        printf("\t\t\t\tThere is no users!\n");
        return pHead;
    }
    fseek(fp,0L,0);
    pHead = (User *)malloc(sizeof(User));
    if(pHead == NULL)
    {
        printf("Error2!\n");
        return NULL;
    }
    pHead->next = NULL;
    pEnd = pHead;
    while(!feof(fp))                                    //当未到文件尾前，进行信息的读取
    {
        pNew = (User *)malloc(sizeof(User));
        if(pNew == NULL)
        {
            printf("Error3!");
            return NULL;
        }
        fscanf(fp,"%s %s\n",pNew->username,pNew->passwd);          //fscanf写入链表
        pEnd->next = pNew;
        pNew->next = NULL;
        pEnd = pNew;
    }

    fclose(fp);
    return pHead;
}

int log_in(User *pHead)
{
    char username[20];
    char passwd[20];
    int i = 0;
    User *temp,*loop;
    printf("\t\t\t\tplease input your username:");
    scanf("%s",username);
    getchar( );
    temp = pHead->next;
    if(temp == NULL)
        return 0;
    while(temp != NULL)
    {
        if(strcmp(temp->username,username) == 0)                   //当用户名在已存数据内，才能输入密码
        {
            printf("\t\t\t\tplease input your passwd:");
            system("stty -echo");                                 //不显示用户键盘输入
            while((passwd[i] = getchar( )) != '\n')
            {
                i++;
            }
            passwd[i] = '\0';
            system("stty echo");                                   //显示用户键盘输入
            if(strcmp(temp->passwd,passwd) == 0)                   //当密码也符合文件信息时，进入系统
            {
                printf("\n\n\n\n\t\t\t\t        Welcome!\n");
                getchar(  );
                return 1;
            }
            else
            {
                printf("\n\t\t\t\tError,The passwd isn't correct");
                getchar(  );
                exit(1);
            }
        }
        temp = temp->next;
    }
    printf("\n\t\t\t\tThe username isn't exist please correct it!");
    return 0;

}

void register_user(User *pHead)
{
    char username[20];
    char passwd1[20];
    char passwd2[20];
    FILE *fp;
    fp = fopen("user","a+");
    if(fp == NULL)
    {
        printf("Error4!");
        return;
    }
    User *temp;
    User *prev;
    temp = pHead->next;
    if(pHead == NULL)
    {
        printf("Error5!");
        return ;
    }
    if(temp == NULL)
        printf("\t\t\t\tplease register a new user!\n");
    while(temp != NULL)
        temp = temp->next;
    printf("\t\t\t\tplease input the username:");
    scanf("%s",username);
    getchar( );
    prev = pHead->next;
    while(prev != NULL)
    {
        while(strcmp(prev->username,username) == 0)          //当用户名不重名时，录入链表
        {
            printf("\t\t\t\tThe user name has been used!\n\t\t\t\tPlease input another username:");
            scanf("%s",username);
            getchar( );
            prev = pHead->next;
        }
        prev = prev->next;
    }
    printf("\t\t\t\tplease input the passwd:");
    system("stty -echo");
    scanf("%s",passwd1);
    getchar( );
    printf("\n");
    printf("\t\t\t\tplease input the passwd again:");
    scanf("%s",passwd2);
    getchar( );
    printf("\n");
    system("stty echo");
    while(strcmp(passwd1,passwd2) != 0)                  //当两次输入密码相同时，存入链表
    {
        printf("\t\t\t\tThe passwd isn't same,please input again:");
        scanf("%s",passwd2);
        getchar( );
    }

    fprintf(fp,"%s %s\n",username,passwd2);     //信息统一写入链表
    fclose(fp);

    printf("\t\t\t\tCongratulations! You have registered youe user!");
}

int log_in_menu(void) {
    User *pHead;
    int choice = 8;
    int n;
    printf("\n\n\t\t\t\t************************************************************\n");
    printf("\n");
    printf("\t\t\t\t                   Log_in_menu                \n");
    printf("\n");
    printf("\t\t\t\t                    1.Log_in          \n");
    printf("\n");
    printf("\t\t\t\t                    2.Register        \n");
    printf("\n");
    printf("\t\t\t\t                    0.Quit            \n");
    printf("\t\t\t\t************************************************************\n");
    printf("\t\t\t\tplease input your choice:");
    scanf("%d",&choice);
    while(choice != 0)
    {
        switch(choice)                     //循环进行登录功能的选择
        {
            case 1:
                system("clear");
                pHead = File_read( );
                n = log_in(pHead);
                if(n == 1)
                    return 1;
                break;
            case 2:
                system("clear");
                pHead = File_read( );
                register_user(pHead);
                getchar(  );
                system("clear");
                break;
            case 0:
                return 0;
        }
        printf("\n\n\t\t\t\t************************************************************\n");
        printf("\n");
        printf("\t\t\t\t                                 Log_in_menu                \n");
        printf("\n");
        printf("\t\t\t\t                               1.Log_in          \n");
        printf("\n");
        printf("\t\t\t\t                               2.Register        \n");
        printf("\n");
        printf("\t\t\t\t                               0.Quit            \n");
        printf("\t\t\t\t************************************************************\n");
        printf("\n\t\t\t\tPlease input your choice:");
        scanf("%d",&choice);
        getchar( );
    }
    return 0;
}
