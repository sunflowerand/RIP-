
/*路由表(Routing Table)由链表组成，所以先构造链表结构，并且封装部分函数功能*/
struct listnode {
  struct listnode *next;
};

typedef struct listnode listnode;
//listnode *first;
/*链表的一些相应的功能函数，其中的参数first是指向链表的头指针。
具体函数实现在list.c中*/

int list_insert(listnode *first, listnode *Position, listnode *toappend);
//在指定链表节点尾部插入新的节点，插入成功后返回0

listnode * list_next(listnode *Position);
//返回该节点指向的下一个节点

listnode * list_nextdelete(listnode *first, listnode *Position);
//在frist指向的链表中，删除Position->next并返回删除的节点

int list_append(listnode *first, listnode *toappend);
//在链表尾指针(最后一个节点)添加新节点

int is_list_empty(listnode * list);
//判断链表内容是否为空，如果为空返回1

int list_exist(listnode * list);
//判断链表头指针List是否为NULL，不是说明存在返回1

int list_delete(listnode *first, listnode *todelete);
//删除链表中的指定节点todelete，删除成功返回1，todelete节点不在链表中返回0
