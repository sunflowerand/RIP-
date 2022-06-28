
/* Log Level = 0 什么都没有 */
/* Log Level = 1 只显示WARNS  */
/* Log level = 2 . WARNS和FlOW */
/* Log level = 3 . 显示所有. */

/* Logging level can be set for individual .c files. */

/*   eg: to set log level 2 for file foo.c */

/* #define LOG_LEVEL 2 */
/* #include "log.h" */
/* in foo.c */

/* and so on. */

/* 如果在.c文件中没有定义日志级别，将使用默认级别(0)。*/

/* WARNs will be displayed on stdout. All other logs will be displayed on the stderr. */

/* Calling convention :: */

/* To log , follow the following convention of printf()*/
  
/*   WARN("warning message -- i == %d", i); */
/*   LOG_FLOW("found bar = %s", bar); */
/*   LOG("msg"); */
/*在末尾使用"\n"确保缓冲区被刷新*/
 

#ifndef LOG_LEVEL    //检测是否明确了日志等级 
#define LOG_LEVEL 0  // 设置默认值
#endif

#define WARN(expr, args...) if (LOG_LEVEL >= 1) fprintf(stdout, expr, ##args)
#define LOG_FLOW(expr, args...) if (LOG_LEVEL >= 2) fprintf (stderr, expr, ##args)
#define LOG(expr, args...) if(LOG_LEVEL >= 3) fprintf(stderr, expr, ##args)
