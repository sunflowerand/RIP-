#include<stdlib.h>
#include<stdio.h>

#include "list.h"

int list_append(listnode *first, listnode *toappend)
{
  listnode *p;
  if(!list_exist(first)) {
     return -1;
  }
  p = first;
  while(p->next != NULL) {
    p = list_next(p);
  }
  p->next = toappend;
  toappend->next = NULL;
  return 0;
}
int list_insert(listnode *first, listnode *Position, listnode *toappend)
{
  /*当Position为空(即链表为空)，toappend是第一个节点*/
  if(Position == NULL) {
    Position = toappend;
    toappend->next = first;
    first = Position;
    first->next = NULL;
    return 0;
  }

  /* 如果postion是在链表尾部 */
  if(Position->next == NULL) {
    Position->next = toappend;
    toappend->next = NULL;
    return 0;
  }

  /* 正常情况下作为中间节点 */
  toappend->next = Position->next;
  Position->next = toappend;
  return 0;
}

listnode * list_next(listnode *Position)
{
  return (Position->next);

}

/* 删除成功返回0，如果todelete节点不在链表中返回-1*/

int list_delete(listnode *first, listnode *todelete)
{
  listnode *prev;
  if(list_exist(first)==0 || is_list_empty(first) ) {
    return -1;
  }
  if(todelete == NULL) {
    return -1;
  }
  prev = first;
  while(prev->next != todelete) {
    prev = prev->next;
    if(prev->next == NULL)
      return -1;
  }
  prev->next = todelete->next;
  todelete->next = NULL;
  return 0;
}

/* 删除 Position->next  然后返回node节点 */

listnode * list_nextdelete(listnode *first, listnode *Position)
{
  listnode *temp;
  /* 如果Position是NULL，删除*/
  if(Position == NULL) {
    temp = first;
    first = first->next;
    temp->next = NULL;
    return temp;
  }

  /*返回NULL如果Position指向的是最后一个节点 */
  if(Position->next == NULL)
    return NULL;
  
  /*当Position位于链表中间的正常情况时*/
  temp = Position->next;
  Position->next = temp->next;
  temp->next = NULL;
  return temp;
}

int is_list_empty(listnode * list)
{
  if(list->next == NULL)
    return 1;
  return 0; /*如果链表为空返回1，否则返回0*/
}
int list_exist(listnode * list)
{
  if(list == NULL)
    return 0;
  return 1;			/* 如果链表存在返回1值 */
}

/* 链表测试程序 */

/*
struct listdata {
  listnode *l;
  int data;
};
int main()
{
  struct listdata *new, *p, *q;
  new = (struct listdata *)malloc(sizeof(struct listdata));
  new->data = 10;
  first = NULL;
  list_insert(first, (listnode*)new);
  q = (struct listdata *)malloc(sizeof(struct listdata));
  q->data = 20;
  list_insert((listnode*)new,(listnode*)q); 
  list_nextdelete(NULL);
  p = (struct listdata*)first;
  do{
    printf("\n %d \n", p->data);
    p =(struct listdata *) list_next((listnode*)p); 
  }while(p!=NULL);
 return 0;
}
*/
