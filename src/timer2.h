#ifndef __TIMER_H
#define __TIMER_H

#include<time.h>
/* 哈希表中的最大值 */
#define MAX 50

#define TIME_GRANULARITY 50
#define DEBUG 1

/* Function Pointer */
typedef void (*fnptr)(void *arg1, void *arg2);

/* Typedefs */
typedef struct timer_info     timer_info_t;
typedef struct timer_header   timer_header_t;
typedef struct timer_info*    timer_info_ptr_t;
typedef struct timer_header*  timer_header_ptr_t;
typedef unsigned long long    timer_time_t;

/* 存储计时器信息 */

struct timer_info {
  int duration;                        // 回调后的持续时间
  fnptr handler;                       // 指向回调函数的指针
  void *arg1;                          
  void *arg2;                          
  timer_info_ptr_t next;                 //双向链表
  timer_info_ptr_t prev;
  timer_header_ptr_t up;                 // list链表的头指针
  char recursive:1;                     //判断是否是递归计时器
};


/* 存储结束时间信息和维护定时器链路表的数据结构 */

struct timer_header {
  unsigned int number_of_timers;       // 具有此结束时间的计时器的数量
  timer_time_t  end_time;        // 与此头关联的计时器过期的时间
  timer_header_ptr_t prev;               // 指向prev计时器的指针
  timer_header_ptr_t next;               // 指向next计时器的指针
  timer_info_ptr_t down;                 // 指向timer——info链表的指针
  int bucket_number;
};


struct timer_data_struct{
/* 维护当前bucket的编号 */
int current_bucket;

/* (granularity of 50 ms) */
timer_time_t current_time;

/* 有关线程的设置 */
pthread_mutex_t currenttime_mutex;
pthread_mutex_t timer_mutex ;
pthread_cond_t timer_cond;

/* 哈希表 */
timer_header_ptr_t hash_table[MAX];         // timer_header结构体数组
}timer_ds;


#endif
