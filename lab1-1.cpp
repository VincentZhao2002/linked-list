#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iostream>
#include <wchar.h>
#include <string>
using namespace std;

typedef char Elemtype;

typedef struct LNode{
    Elemtype data[25] = {'\0'};
    struct LNode *next;
}LNode, *LinkList;
//分割符号
char ch[13] = {' ', ',', '.','?', '!', ':', '+', '-', '=', '*', '\'', '(', ')'};

//判定是否到达分割处
//参数：a:遍历过程中原始字符串某个字符，b:分割符号
//返回：是否为分割处
bool judge_seq(char a, char b[])
{
    for(int i = 0; i < 10;i++)
    {
        if(a == b[i])
        {
            return true;
        }
    }
    return false;
}

//获得分割后的词组
//参数：temp[]：原始文本，subtemp：储存分割后单词的子串
//返回：分割为多少个单词
int get_words(char temp[], char subtemp[][25])
{
    int i = 0, start = 0;
    int j = 0, k = 0;
    while(1){
        //获得所有子串的循环
		if(judge_seq(temp[i], ch)||temp[i]==0){
			for(int l=start;l<i;l++){
				subtemp[j][k++]=temp[l];
			}
			subtemp[j][k]=0;
			j++;
			k=0;
			start=i+1;    //获得子串后，把当前位置的下一个位置设置为头
		}
		if(temp[i]==0)break;
		i++;
    }
    return j;
}
//初始化
bool InitList(LinkList *L){
    (*L) = (LNode *)malloc(sizeof (LNode));    // 分配一个头结点
    if((*L) == NULL)      // 内存不足，分配失败。
        return false;
    (*L)->next = NULL;
    return true;
}
//后插结点
//参数：L：被操作的单链表，i：插入位置
bool InsertNextNode(LinkList &L, int i)
{
    LNode *p = L;

    int m = 0;
    while( p  &&  m < i - 1 )  
    { 
        p = p->next; 
        ++m; 
    }

    if(!p||m>i-1)
    {
        return false;
    }
    printf("Please enter the text you want to insert.\n");
    char temp[4096];
    char subtemp[500][25];
    gets(temp);
    int j = get_words(temp, subtemp);
    //适配插入一句话即多个词的形式，将分割后的词组插入指定位置
    for(int i = j - 1;i>=0;i--)
    {
        LNode *s =  (LNode*)malloc(sizeof(LNode));
        if(!s)
        {
            exit(-2);
        }
        if(s == NULL)
        {
            return false;
        }
        for(int n = 0;n <25;n++)
        {
            s->data[n] = subtemp[i][n];
        }
        s->next = p->next;
        p->next = s;
    }
    printf("Operate successfully! :)\n");
    return true;
}
// 按值查找，找到数据域 ==e 的结点，返回节点序号
int LocateElem(LinkList L, Elemtype e[]){
    LNode *p = L->next;          // 指向头结点
    int i = 1;
    while (p != NULL)
    {
        if(!strcmp(p->data,e))
        {
            return i;
        }
        p = p->next;
        i++;
    }
    return -1;      
}
//清空列表
bool ClearList(LinkList &L)
{ 
    if(L->next == NULL)
    {
        return false;
    }
    LNode *p = L;
	while(L->next != NULL)
    {        
        p = L->next;         
        L->next = p->next;   
        free(p);                  
    }
    printf("Operate successfully! :)\n");
	return true;
}
// 统计表长
int Length(LinkList L)
{
    int len = 0;        
    
    LNode *p = L;       // p指向当前结点。先令其等于头结点
    while(p->next != NULL)
    {   // 遍历单链表
        p = p->next;
        len++;
    }
    return len;
}
//删除指定位置，指定数目的节点
//参数：seq_num:指定删除位置，num:删除节点数目
bool DeleteNode(LinkList &L, int seq_num, int num)
{      // 把将删除的结点数据改成其下一结点的数据，再把下一结点删除
    if(seq_num + num > Length(L))
    {
        printf("Please enter right number!");
        return false;
    }
    LNode *p = L->next;
    int i = 1;
    while(p != NULL && i < seq_num)
    {
        p = p->next;
        i++;
    }
    if(!p || i > seq_num)
    {
        return false;
    }
    for(int j = 0;j<num;j++)
    {
        LNode *q = p->next;         // q为p的下一结点
        strcpy(p->data,q->data);    // p的数据域改为下一节点数据域
        p->next = q->next;          // p的下一结点改为下下结点
        free(q);
    }
    printf("Operate successfully! :)\n");
    return true;
}
// 正向建立单链表
LinkList List_TailInsert(LinkList &L)
{     
    printf("Please enter the text.\n");
    LNode *r = L;   
    char temp[4096];
    gets(temp);
    char subtemp[500][25];

    int j = get_words(temp, subtemp);

    for(int i = 0;i < j;i++)
    {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        if(!s)
        {
            exit(-2);
        }
        for(int n = 0; n< 25; n++)
        {
            s->data[n] = subtemp[i][n];
            
        }
        r->next = s;    // 指向新结点
        r = s;          // 指向新的表尾结点
        r->next = NULL;  
    }
    printf("Operate successfully! :)\n");
    return L;
}

// 输出单链表
void PrintList(LinkList L)
{
    LNode *p;       // 声明一个结点
    p = L->next;          // 指向头结点
    while(p != NULL)
    {      // 遍历单链表
        printf("%s", p->data);
        p = p->next;
        printf(" ");        
    }
    printf("\n");
}
//将链表倒置，以词为单位
bool Invert(LinkList &L)
{
    LNode *p = L->next;
    int i = 0;
    char words[500][25];
    while(p != NULL)
    {
        strcpy(words[i],p->data);
        i++;
        p = p->next;
    }

    ClearList(L);

    LNode *r = L;

    for(int j = i - 1;j >= 0;j--)
    {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        if(!s)
        {
            exit(-2);
        }
        strcpy(s->data, words[j]);
        r->next = s;    // 指向新结点
        r = s;          // 指向新的表尾结点
        r->next = NULL;  
    }
    printf("Operate successfully! :)\n");
    return true;
}
//判断是否为回文
bool Palindrome(LinkList &L)
{
    LNode *p = L->next;
    int i = 0;
    char words[500][25];
    while(p != NULL)
    {
        strcpy(words[i],p->data);
        i++;
        p = p->next;
    }
    int len = i/2;
    for(int j = 0; j < len; j++)
    {
        if(strcmp(words[j],words[i-1-j]))
        {
            return false;
        }
    }
    return true;
}
//获取指定位置的节点数据
Elemtype * Getelem(LinkList &L, int pos)
{
    LNode *p = L->next;
    int i = 0;
    while(p->next != NULL && i < pos - 1)
    {
        p = p->next;
    }
    return p->data;
}
//统计指定词在链表中出现的次数
int Word_count(LinkList &L, Elemtype word[])
{
    LNode *p = L->next;
    int count = 0;
    while(p != NULL)
    {
        if(!strcmp(p->data, word))
        {
            count++;
        }
        p = p->next;
    }
    return count;
}
//统计所有词在链表中出现的次数
void All_word_count(LinkList &L)
{
    char word_set[500][25];
    LNode *p = L->next;
    int j = 0;
    while(p != NULL)
    {
        bool exist = false;
        for(int n = 0; n < j; n++)
        {
            if(!(strcmp(p->data, word_set[n])))
            {
                exist = true;
                break;
            }
        }
        if(!exist)
        {
            strcpy(word_set[j], p->data);
            j++;
        }
        p = p->next;
    }
    for(int i = 0;i < j; i++)
    {
        printf("%s ", word_set[i]);
        printf("%d\n", Word_count(L, word_set[i]));
    }
    return;
}
//两个链表合并，将第二个链表中未在第一个链表中出现的节点复制到第一个链表中
void Merge_list(LinkList &L, LinkList &L1)
{
    LNode *p1 = L->next;
    LNode *p2 = L1->next;
    while(p1->next != NULL)
    {
        p1 = p1->next;
    }
    while(p2 != NULL)
    {
        if(LocateElem(L, p2->data) == -1)
        {
            LNode *s = (LNode *)malloc(sizeof(LNode));
            if(!s)
            {
                exit(-2);
            }
            strcpy(s->data, p2->data);
            p1->next = s;
            p1 = p1->next;
            p1->next = NULL;
        }
        p2 = p2->next;
    }
    printf("Operate successfully! :)\n");
    return;
}

int main(){
    LinkList L;
    LinkList L1;
    LNode *s;        // 结点
    int pos;         // 位置
    int len;
    int list_num;         // 表
    if(InitList(&L) && InitList(&L1)){   // 初始化成功后才进行后续操作
        int status;  // 操作码
        while(1){
            printf("Please enter a status code:\n1.List_TailInsert    2.List_Insert        3.LocateElem\n");
            printf("4.DeleteElem         5.ListDelete         6.Invert\n7.Length             8.PrintList          9.Palindrome\n");
            printf("10.Word_Count        11.Add_List          12.Merge_list\n0.exit\n");
            scanf("%d", &status);
            if(status == 0) break;
            switch (status){
                case 1:
                {
                    printf("Please enter which list you want to operate on.\n");
                    scanf("%d",&list_num);
                    getchar();
                    if(list_num == 1)
                    {
                        List_TailInsert(L);
                    }
                    else if(list_num == 2)
                    {
                        List_TailInsert(L1);   
                    }
                    break;
                }
                case 2:
                {
                    int pos;
                    printf("Please enter which list you want to operate on.\n");
                    scanf("%d",&list_num);
                    printf("Please enter which position you want to insert.\n");
                    scanf("%d", &pos);
                    getchar();
                    if(list_num == 1)
                    {
                        InsertNextNode(L, pos);
                    }
                    else if(list_num == 2)
                    {
                        InsertNextNode(L1, pos);   
                    }
                    break;
                }
                case 3:
                {
                    printf("Please enter which list you want to operate on.\n");
                    scanf("%d",&list_num);
                    getchar();
                    printf("Please enter the element you want to locate.\n");
                    char elem[25];
                    gets(elem);
                    
                    if(list_num == 1)
                    {
                        printf("%d",LocateElem(L, elem));
                    }
                    else if(list_num == 2)
                    {
                        printf("%d",LocateElem(L1, elem));   
                    }
                    printf("\n");
                    break;
                }
                case 4:
                {
                    int seq_num, num;
                    printf("Please enter which list you want to operate on.\n");
                    scanf("%d",&list_num);
                    printf("Please enter the starting position and the number of nodes you want to delete.\n");
                    scanf("%d %d",&seq_num, &num);
                    
                    if(list_num == 1)
                    {
                        DeleteNode(L, seq_num, num);
                    }
                    else if(list_num == 2)
                    {
                        DeleteNode(L1, seq_num, num);   
                    }
                    break;
                }
                case 5:
                {
                    printf("Please enter which list you want to operate on.\n");
                    scanf("%d",&list_num);
                    if(list_num == 1)
                    {
                        ClearList(L);
                    }
                    else if(list_num == 2)
                    {
                        ClearList(L1);   
                    }
                    break;
                }
                case 6:
                {
                    printf("Please enter which list you want to operate on.\n");
                    scanf("%d",&list_num);
                    if(list_num == 1)
                    {
                        Invert(L);
                    }
                    else if(list_num == 2)
                    {
                        Invert(L1);   
                    }
                    break;
                }
                case 7:     // 求表长
                {
                    printf("Please enter which list you want to operate on.\n");
                    scanf("%d",&list_num);
                    if(list_num == 1)
                    {
                        len = Length(L);
                    }
                    else if(list_num == 2)
                    {
                        len = Length(L1);  
                    }
                    printf("The length of the LinkList is %d\n", len);
                    break;
                }
                case 8:     // 输出表
                {
                    printf("Please enter which list you want to operate on.\n");
                    scanf("%d",&list_num);
                    if(list_num == 1)
                    {
                        PrintList(L);
                    }
                    else if(list_num == 2)
                    {
                        PrintList(L1);  
                    }
                    break;
                }
                case 9:
                {
                    printf("Please enter which list you want to operate on.\n");
                    scanf("%d",&list_num);
                    if(list_num == 1)
                    {
                        if(Palindrome(L))
                        {
                            printf("This is a Palindrome string! :)\n");
                        }
                        else
                        {
                            printf("This is not a Palindrome string. :(\n");
                        }
                    }
                    else if(list_num == 2)
                    {
                        if(Palindrome(L1))
                        {
                            printf("This is a Palindrome string! :)\n");
                        }
                        else
                        {
                            printf("This is not a Palindrome string. :(\n");
                        } 
                    }
                    break;
                }
                case 10:
                {
                    printf("Please enter which list you want to operate on.\n");
                    scanf("%d", &list_num);
                    int pick = 0;
                    printf("If you want to enter words and count, please enter -1.\n");
                    printf("If you want to konw all the words' number, please enter 0.\n");
                    scanf("%d", &pick);
                    
                    switch(pick)
                    {
                        case -1:
                            getchar();
                            char word[25];
                            gets(word);
                            if(list_num == 1)
                            {
                                printf("%d\n", Word_count(L, word));
                            }
                            else if(list_num == 2)
                            {
                                printf("%d\n", Word_count(L1, word)); 
                            }
                            break;
                        case 0:
                            if(list_num == 1)
                            {
                                All_word_count(L);
                            }
                            else if(list_num == 2)
                            {
                                All_word_count(L1); 
                            }
                            break;
                        default:
                            printf("Please enter right number.");
                            break;
                    }
                    break;
                }
                case 11:
                {
                    InitList(&L1);
                    getchar();
                    List_TailInsert(L1);
                    break;
                }
                case 12:
                {
                    Merge_list(L, L1);
                    break;
                }    
                default:
                    printf("Error!\n");
                    break;
            }
        }
    }else{
        printf("Failed to initList!\n");
    }

    return 0;
}