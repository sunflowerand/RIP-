/*内存管理部分*/
/* 删除一个计时器结构*/
void free_mem(void*);

/* 使用malloc初始计时器结构的内存快
0：执行成功   1：执行失败
*/
int init_mem(int size);


/* 获取剩余的内存空间
   返回分配的IP地址说明成功，返回控制说明失败
*/
void *get_memory(void);
