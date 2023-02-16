#include "../inc/delay.h"
#include "../../Inc/main.h"
#include "../inc/SSerial.h"
static u8  fac_us=0;							//us��ʱ������			   
static u16 fac_ms=0;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��



//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void delay_init()
{
//	HAL_TIM_Base_Start(&htim1);
//	HAL_TIM_Base_Stop(&htim1);
	soft_counter=0;
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
//	fac_us=SystemCoreClock/8000000;				//Ϊϵͳʱ�ӵ�1/8
//	fac_ms=(u16)fac_us*1000;					//��OS��,����ÿ��ms��Ҫ��systickʱ����
}								    

//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u32 nus)
{		
	if(nus<10) //we just need more than 10 micro second//so if you enter value less than 10 we change it to 10
		nus=10;
	soft_counter=0;
	HAL_TIM_Base_Start_IT(&htim1);
	while(nus > soft_counter*10){};
	HAL_TIM_Base_Stop_IT(&htim1);

//	u32 temp;
//	SysTick->LOAD=nus*fac_us; 					//ʱ�����
//	SysTick->VAL=0x00;        					//��ռ�����
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����
//	do
//	{
//		temp=SysTick->CTRL;
//	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
//	SysTick->VAL =0X00;      					 //��ռ�����
}

//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void delay_ms(u16 nms)
{
	HAL_Delay(nms);
//	u32 temp;
//	SysTick->LOAD=(u32)nms*fac_ms;				//ʱ�����(SysTick->LOADΪ24bit)
//	SysTick->VAL =0x00;							//��ռ�����
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����
//	do
//	{
//		temp=SysTick->CTRL;
//	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
//	SysTick->VAL =0X00;       					//��ռ�����
}








































