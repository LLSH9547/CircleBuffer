#ifndef CIRCLE_BUFFER_LLSH
#define CIRCLE_BUFFER_LLSH
#include "stdint.h"

#ifdef __cplusplus
export "C"{
#endif

#define DataLoopSize  (100)



enum eCircleBufferstate
{
    leisure = 0,
    busy = 1
};

struct sCircleBuffer
{
    volatile uint32_t HeadNumber;
    volatile uint32_t LatestNumber;
    volatile uint32_t FreeSpace;
    volatile uint8_t  Data[DataLoopSize];   
};
typedef struct sCircleBuffer CircleBuffer_t;



/****************************************/
/*

 * @brief ：环形数组初始化函数

 * @param ：NULL

 * @retval：Null
 * 
 * @Note  :	Null

 */
/***************************************/
void CircleBufferInit(void);



/****************************************/
/*

 * @brief ：环形数组查满函数

 * @param ：size 

 * @retval：1(full) 或 0（leisure）
 * 
 * @Note  :	当size=0时，可以查看环形数组是否已满；
 * 或者输入要输入数据的大小，看剩余空间是否足够

 */
/***************************************/
uint8_t DataPoolIsFull(uint32_t size);



/****************************************/
/*

 * @brief ：环形数组剩余空间查询

 * @param ：Null

 * @retval：剩余空间大小
 * 
 * @Note  :	Null

 */
/***************************************/
uint32_t GetFreeSpace(void);



/****************************************/
/*

 * @brief ：向环形数组加入数据

 * @param ：data数据地址指针
 
 * @param ：size数据大小 
 * 
 * @param ：flag 强制添加标志

 * @retval：1(Faul)) 或 0（Ture）
 * 
 * @Note  :	使用该函数时，由于存在查询剩余空间
 * 和查忙机制，所以并不一定会成功执行数据的加入。


 */
/***************************************/
uint8_t AddData(const uint8_t *data, uint8_t size);




/****************************************/
/*

 * @brief ：删除向环形数组加入数据

 * @param ：data数据地址指针
 
 * @param ：size数据大小 

 * @retval：1(Faul)) 或 0（Ture）
 * 
 * @Note  :	FIFO


 */
/***************************************/
uint8_t DeleteDate(uint8_t size);


uint8_t *GetDateAddress(void);


#ifdef __cplusplus
}
#endif

#endif