#ifndef __ISINCLUDED__
#define __ISINCLUDED__
#define TRIGUPDATE 11
#define REGUPDATE 22
#define RIP_PORT 3333  //应该是UDP的520大概
#define REQUEST 1
#define RESPONSE 2
#define INFINITY 16//RFC1058中规定了最大跳数为16
#define SET_ROUTE_CHANGE_FLAG 1、、
#define RESET_ROUTE_CHANGE_FLAG 0
#define VALID 1
#define INVALID 0
#define IPVER 4 
#define UPDTIME 5000ULL//更新定时器的时间
#define TIMEOUT 10000ULL
#define GARBAGE 20000ULL
#include "list.h"

typedef char byte;

/* 路由表中的条目组成
详见RFC1058 3.Specifications for the protocol P16 */
struct route_entry {
  listnode *lnode;		/*指向链表的指针 */
  struct in_addr destination;  /*目标的IP地址 */
  uint32_t metric;  /*到达目的地的度量 */
  struct in_addr nexthop;       /*路由器的下一跳IP地址 */
  byte routechanged;		/*将会在路由器更新的时候设置*/
  //路由器所拥有的两个计时器
  void *timeout_tmr;    /*存储超时(无效计时器)对象*/
  void *garbage_tmr;    /*存储垃圾回收计时器对象*/
};

/*详见RFC1058 3.1 MESSAGE FORMAT  */
/*RFC*/

/* RIP 数据包格式
|-----------------------------------------------|
|command (1) |version(1)|    zero(2)            |
|-----------------------------------------------|
|                RIP entry(20)                  |
~                                               ~
|-----------------------------------------------|
 */


/*
RIP entry 内容 
|-------------------------------------------------
|addr family id(2)     | must be zero(2)         |
|------------------------------------------------|
|               IPv4 addr (4)                    |
|------------------------------------------------|
|                must be zero(4)                 |
|------------------------------------------------|
|                must be zero(4)                 |
|------------------------------------------------|
|               metric(4)                        |
|------------------------------------------------|

 */

/*RIP报文的头结构*/
struct rip_header {
  byte command; 		/* 1-REQUEST, 2-RESPONSE */
  byte version;
  short int _zero;
};

/*RIP entry*/
struct rip_entry {
  short int addrfamily;/*目前只支持AF_INET*/
  short int _zero;
  struct in_addr destination;
  uint32_t _zero1;
  uint32_t _zero2;
  uint32_t metric;
};

/*构建一个链表结构存储节点的相临节点*/
struct neighbour {
  listnode *lnode;	       	/* 链表指针 */
  struct in_addr addr;
};

/* 以下函数的功能主要参考RFC1058 3.4 Input Processing 与 3.5 Output Processing */

struct neighbour *neighbours;	/* neighbour list的头结点 */
struct route_entry *route_table; /* 路由表的头结点 */
int sock;			 /* 通过RIP端口通信的套接字ID */
struct in_addr ownip;
FILE *logfile;//输入输出缓冲区
char fname[20];

byte packet_type(char *message);/*构造数据报*/
void add_route_entry(struct route_entry *re);/*增加路由表的路由条目*/
void set_route_entry(struct route_entry *re, struct in_addr destination, uint32_t metric, struct in_addr nexthop);
/*为单条链路信息赋值*/

char* add_rip_entry_to_packet(char *message, struct rip_entry rte);//将entry添加到message并返回message
char* add_rip_header_to_packet(char *message, struct rip_header rh);//将RIP——header添加到message中
void set_rip_entry(struct rip_entry *rte, short addrfamily, struct in_addr destination, uint32_t metric);//赋值

int validate_rip_entry(struct rip_entry e);//确认rip——entry中的metric是否正常
int validate_message(struct sockaddr_in from);//确认端口号是否正确，以及是否由是由相邻的路由器发送过来
/*分配内存单元*/
struct neighbour * alloc_neighbour();
struct route_entry * alloc_route_entry();

/*将数据报包的内容打印出来*/
void print_rip_header(struct rip_header *rh);
void print_rip_entry(struct rip_entry *rte);

//检查到目的地路由是否存在，存在返回route_entry的指针不存在就返回NULL
struct route_entry * is_route_available(struct in_addr destination);
int is_neighbour(struct in_addr s);//判断s是否在邻居链表中

/*此函数将生成适当的更新类型已触发更新或常规更新。
它将发送此更新到邻居列表中的所有地址。要生成常规更新消息
要调用construct_regular_update（）
*/
int send_update(int updatetype);
int construct_regular_update(struct in_addr sendto, char *message);

/*此功能将创建和更新路由表中的条目。
每个路由入口的计时器将根据可能的情况进行设置/重置。如果路由表发生更改，将调用send_update来发送触发的更新。*/
int decode_response(struct in_addr from, char *data, int len);
int decode_request(struct in_addr from, char *data, int len);
int decode_rip_message(char *message, struct rip_header *rh, struct rip_entry *rte );

int init();
void input();
void output(void *, void *);

void timeout_callback(void *r, void *dummy);
void garbage_callback(void *r, void *dummy);
int reset_neighbour_entry_timer(struct in_addr from);

int sendmesg( unsigned short int addrfamily, int port,  struct in_addr send_to_ip, int sock,char *message, int len);

void print_route_table(int flag);
int delete_route(struct route_entry *re);
void* cli(void *);
#endif
