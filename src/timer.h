
#define RECURSIVE_TIMER '1'
#define NON_RECURSIVE_TIMER '0'


/* 函数指针 */
typedef void (*fnptr_t)(void *arg1, void *arg2);

/* 计时器初始化
   Return Value : 0  = successful
                  -1 = error
*/
int init_timer(void);

/*
   参数:
   1) duration : 用户希望计时器的过期时间
   2) handler  : 函数指针回调函数
   3) arg1     : 函数指针
   4) arg2     : 函数指针
   5) recursion : '1' ---->递归计时器
                  '0' ----> 非递归计时器
   Return Value : 成功, 计时器结构的内存地址
                  失败, NULL.
*/
void *start_timer(unsigned long long duration, fnptr_t handler, void *arg1, void *arg2,char recursion);


/* 3. 停止计时器
   参数 :
   1) handle : Address of timer structure returned by start_timer 
*/
void stop_timer(void *handle);

/* 4. 重启计时器
   Parameter :
   1) handle : Address of timer structure returned by start_timer
*/ 
void *reset_timer(void* handle);
