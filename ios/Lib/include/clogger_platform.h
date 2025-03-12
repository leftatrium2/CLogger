#ifndef _CLOGGER_PLATFORM_H_
#define _CLOGGER_PLATFORM_H_

/**
 * @brief 判断是否是UI线程
 *
 * @return int 1:true&0:false
 */
int is_main_thread(void);
/**
 * @brief 判断当前SD卡中容量是否够用，ios默认返回1【表示成功】
 *
 * @param path 给定的全路径
 * @return int 1:true&0:false
 */
int is_can_write_sdcard(const char *path);

#endif
