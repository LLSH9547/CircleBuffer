#include "CircleBuffer.h"
static CircleBuffer_t CircleBuffer;
static volatile uint8_t BusyFlag = 0;

void CircleBufferDelayMs(uint32_t time)
{}


/****************************************/
/*

 * @brief ：环形数组初始化函数

 * @param ：NULL

 * @retval：Null
 * 
 * @Note  :	Null

 */
/***************************************/
void CircleBufferInit(void)
{
	CircleBuffer.FreeSpace = DataLoopSize;
	CircleBuffer.HeadNumber = CircleBuffer.LatestNumber = 0;
}


/****************************************/
/*

 * @brief ：环形数组剩余空间查询

 * @param ：Null

 * @retval：剩余空间大小
 * 
 * @Note  :	Null

 */
/***************************************/
uint32_t GetFreeSpace(void)
{
	return CircleBuffer.FreeSpace;
}


/****************************************/
/*

 * @brief ：环形数组查满函数

 * @param ：size 

 * @retval：1(full) 或 0（free）
 * 
 * @Note  :	当size=0时，可以查看环形数组是否已满；
 * 或者输入要输入数据的大小，看剩余空间是否足够

 */
/***************************************/
uint8_t DataPoolIsFull(uint32_t size)
{
	if((CircleBuffer.FreeSpace - size)>=0)
		return 0;
	else
		return 1;
}




/****************************************/
/*

 * @brief ：等待环形数组忙结束

 * @param ：Null 

 * @retval：1(Busy) 或 0（leisure）
 * 
 * @Note  :	当环形数组忙时，会等待一段时间，
 * 但这段时间结束后数组依然处于忙状态，那么将
 * 输出忙(1)，否则输出空闲(0)

 */
/***************************************/
uint8_t WaitingBusyState(void)
{
	uint16_t Loop_Number = 0;
	uint8_t loop_i = 0xff;
	uint8_t loop_j = 0xff;	
	while(BusyFlag==1) 
	{
		for(;loop_i>0;loop_i--)
		{
			for(;loop_j>0;loop_j--)
			{

			}
		}
		Loop_Number++;
		if(Loop_Number >= 10)
			return 1;
	}
	return 0;
}




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
uint8_t AddData(const uint8_t *data, uint8_t size)
{
	if(DataPoolIsFull(size))
		return 1;
   if(WaitingBusyState())
 		return 1;
	 BusyFlag = 1;
   for(;size>0;size--)
   {
    	CircleBuffer.FreeSpace--;
    	CircleBuffer.Data[CircleBuffer.LatestNumber] = *data;
    	CircleBuffer.LatestNumber++;
		if(CircleBuffer.LatestNumber == (DataLoopSize))
			CircleBuffer.LatestNumber = 0;
       data++;
   }
	BusyFlag = 0;
   return 0;
}



/****************************************/
/*

 * @brief ：向环形数组加入数据

 * @param ：size数据大小 

 * @retval：1(Faul)) 或 0（Ture）
 
 * @Note  :	使用该函数时，由于存在查忙机制，所
 * 以并不一定会成功执行数据的删除工作。


 */
/***************************************/
uint8_t DeleteDate(uint8_t size)
{
   if(WaitingBusyState())
 		return 1;
	 BusyFlag = 1;
	for(;(size>0)&&(CircleBuffer.FreeSpace<=DataLoopSize);size--)
	{
		CircleBuffer.FreeSpace++;
		CircleBuffer.Data[CircleBuffer.HeadNumber] = 0;
		CircleBuffer.HeadNumber++;
		if(CircleBuffer.HeadNumber == (DataLoopSize))
			CircleBuffer.HeadNumber = 0;
	}
	BusyFlag = 0;
	return 0;
}



/****************************************/
/*

 * @brief ：获取数组的当前首地址

 * @param ：NULL

 * @retval：1(Faul)) 或 0（Ture）
 
 * @Note  :	NULL


 */
/***************************************/
uint8_t *GetDateAddress(void)
{
   return &(CircleBuffer.Data[CircleBuffer.HeadNumber]);
}
