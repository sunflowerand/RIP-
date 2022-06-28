#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>


#define PAGE_SIZE 4096
#define NUM_OF_PAGES 5

int total_size = 0;
pthread_mutex_t memory_mutex = PTHREAD_MUTEX_INITIALIZER;//多线程上锁
void *first = NULL;
void *last = NULL;


/* -------------------------------------------------------------------------------------------------------------------- */

/* 删除计时器结构 */
void free_mem(void* to_delete)
{
  unsigned long *addr;
  unsigned long *temp;
  
  /* 互斥锁在第一个，最后一个执行更新 */
  pthread_mutex_lock(&memory_mutex);
  temp = addr = (unsigned long *)last;
  *addr = (unsigned int)to_delete;
  last = to_delete;
  addr = (unsigned long *)to_delete;
  *addr = 0;
  if(first == NULL)
    first = last;
  pthread_mutex_unlock(&memory_mutex);

}

/* -------------------------------------------------------------------------------------------------------------------- */



int init_mem(int size)
{
  //  TIMER_INFO_PTR temp;
  char *temp;
  unsigned long *addr;
  char *end;
  size_t length;

  pthread_mutex_lock(&memory_mutex);
  first            = (void*)malloc(NUM_OF_PAGES*PAGE_SIZE);
  if(first == NULL)
    return -1;
  temp             = (char *) first;
  end              = first + NUM_OF_PAGES*PAGE_SIZE;
  length           = 2 * size;
  total_size       = size;

  while( ( end - temp ) > length ) {
    addr = (unsigned long*) temp;
    *addr = (unsigned long)(temp+size);
    temp += size;
  }

  last = (void*)temp;
  addr = (unsigned long*)temp;
  *addr = 0;

#ifdef DEBUG
  if(DEBUG){
    //    printf("\n%x %x\n",last,*addr);
  }
#endif

  pthread_mutex_unlock(&memory_mutex);
  return 0;
}

/* -------------------------------------------------------------------------------------------------------------------- */


void *get_memory(void)
{
  unsigned long *addr;
  unsigned long addr2;
  if(first == NULL)
    {
      if(init_mem(total_size)==-1)
	return(NULL);
    }
  
  pthread_mutex_lock(&memory_mutex);
  addr = (unsigned long *)first;
  addr2 = *addr;
  first = (void*)addr2;
  if(first == NULL)
    last = NULL;
  //  printf("\nfirst=%x,last=%x",first,last);
  pthread_mutex_unlock(&memory_mutex);
  return(addr);
    
}


/* -------------------------------------------------------------------------------------------------------------------- */
