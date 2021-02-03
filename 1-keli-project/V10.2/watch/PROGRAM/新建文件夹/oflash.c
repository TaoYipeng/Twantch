
#include "oflash.h"

#include <stdio.h>
#include <string.h> //ʹ�õ���memcpy
#include "main.h"

void Onchip_Flash_Test(void)
{
	int i;
	uint32_t PageError = 0;
	
	FLASH_EraseInitTypeDef FlashSet;
	
	HAL_StatusTypeDef status;
	
	uint32_t addr = 0x0803F800;
	uint32_t data_buf[LEN];
	
	/* ��ȡFlash���� */
	memcpy(data_buf, (uint32_t*)addr, sizeof(uint32_t)*LEN);
	printf("read before erase:\r\n\t");
	for(i = 0;i < LEN;i++)
	{
		printf("0x%08x ", data_buf[i]);
	}
	printf("\r\n");
	
	/* д���µ����� */
	//�������һҳ
	FlashSet.TypeErase = FLASH_TYPEERASE_PAGES;
	FlashSet.Banks = FLASH_BANK_1;
	FlashSet.Sector = 127;
	FlashSet.NbSectors = 1;
	//����Flash����
	HAL_FLASH_Unlock();
	status = HAL_FLASHEx_Erase(&FlashSet, &PageError);
	HAL_FLASH_Lock();
	if(status != HAL_OK)
	{
		printf("erase fail, PageError = %d\r\n", PageError);
	}
	printf("erase success\r\n");
	
	
	/* ��ȡFlash���� */
	memcpy(data_buf, (uint32_t*)addr, sizeof(uint32_t)*LEN);
	printf("read after erase:\r\n\t");
	for(i = 0;i < LEN;i++)
	{
		printf("0x%08x ", data_buf[i]);
	}
	printf("\r\n");

	//д��Flash����
	HAL_FLASH_Unlock();
	for (i = 0; i < LEN * sizeof(uint32_t); i+=8)
	{
			//һ������32λ��һ��д�������֣�64λ��8���ֽ�
			status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addr + i, (uint64_t)i);
			if(status != HAL_OK)
			{
				break;
			}
	}
	HAL_FLASH_Lock();
	if(i < LEN)
	{
		printf("write fail\r\n");
	}
	else
	{
		printf("write success\r\n");
	}

	/* ��ȡFlash���� */
	addr = 0x0803F800;
	memcpy(data_buf, (uint32_t*)addr, sizeof(uint32_t)*LEN);
	printf("read after write:\r\n\t");
	for(i = 0;i < LEN;i++)
	{
		printf("0x%08x ", data_buf[i]);
	}
	printf("\r\n");
	
}

