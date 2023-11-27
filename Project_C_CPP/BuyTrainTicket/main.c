#include <stdio.h>
#include <stdlib.h>
/**************************************************
*功能：对一辆列车在某一个区间内是否有票进行判断 有票返回1 没票返回0
*参数：	psites - 每个站的售票状态 用bit表示 0表示有 1 表示无
*		start  - 待查车票的起始位置 用位表示 第65个站 就是64（取下标）
*		end	   - 待查车票的终止位置 用位表示 第128个站 就是127（取下标）
*返回值： 有票返回1 没票返回0
**************************************************/
int check_Ticket(unsigned char* pSites, unsigned int start, unsigned int end)
{	
	//防御性编程
	if (!pSites){
		printf("...Error!!!...");
		return 0;
	}
	//判断 12-65是否有票
	unsigned char bit_mask = 0xFF;
	/*
	*说明：	因为我们传递过来的是chat类型的指针，所以每一个bit代表一个站
	*		为了定位每一个bit，我们首先要确定在哪个byte，然后再确定在哪个bit
	*/
	int byte_start = start / 8;
	int bit_start = start % 8;

	int byte_end = end / 8;
	int bit_end = end % 8;

	unsigned char first_mask = bit_mask >> bit_start;
	//同一字节
	if (byte_start == byte_end) {
		bit_mask = first_mask & (bit_mask << (8 - bit_end - 1));
		if (pSites[byte_start] & bit_mask) {
			return 0;
		}
		return 1;
	}
	//不同字节
	if (pSites[byte_start] & first_mask) {
		return 0;
	}

	for (int i = byte_start + 1; i < byte_end; i++)
	{
		if (pSites[i] & bit_mask) {
			return 0;
		}
	}

	unsigned char end_mask = bit_mask << (8 - bit_end - 1);
	if (pSites[byte_end] & end_mask) {
		return 0;
	}

	return 1;

}

int main() {

	unsigned char Sites[] = { 0x02,0x00 };

	if (check_Ticket(Sites, 10, 15)) {
		printf("Yes\n");
	}
	else
	{
		printf("No\n");
	}
	system("pause");
	return 0;
}
