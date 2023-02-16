#include "../inc/SSerial.h"



enum{
	COM_START_BIT,
	COM_D0_BIT,
	COM_D1_BIT,
	COM_D2_BIT,
	COM_D3_BIT,
	COM_D4_BIT,
	COM_D5_BIT,
	COM_D6_BIT,
	COM_D7_BIT,
	COM_STOP_BIT,
};



u8 recvStat = COM_STOP_BIT;
u8 recvData = 0;

u8 len = 0;	//���ռ���
u8 USART_buf[11]={0};  //���ջ�����

void IOConfig(GPIO_TypeDef *TX_PORT, uint16_t GPIO_PIN_TX, GPIO_TypeDef *RX_PORT, uint16_t GPIO_PIN_RX,
uint8_t GPIO_PortSourcRX, uint8_t GPIO_PinSourceRX, uint32_t EXTI_LineRX, IRQn_Type* NVIC_IRQChannelRX)
 {
	SOFT_GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 	EXTI_InitTypeDef EXTI_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA, ENABLE);	 //Ê¹ÄÜPB,PC¶Ë¿ÚÊ±ÖÓ

	 //SoftWare Serial TXD
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_TX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�?Æ�?ìÊä³ö
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO¿ÚËÙ¶ÈÎª50MHz
  GPIO_Init(TX_PORT, &GPIO_InitStructure);
  GPIO_SetBits(TX_PORT ,GPIO_PIN_TX);


	//SoftWare Serial RXD
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_RX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RX_PORT, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourcRX, GPIO_PinSourceRX);
	EXTI_InitStruct.EXTI_Line =  EXTI_LineRX;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling; //�?Â½µÑØ´¥·¢Ö�?¶�?
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStruct);


	NVIC_InitStructure.NVIC_IRQChannel= NVIC_IRQChannelRX ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
 }

	void TIM4_Int_Init(u16 arr,u16 psc)
	{

		SOFT_TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //Ê±ÖÓÊ¹ÄÜ

		//¶¨Ê±Æ÷TIM4³õÊ¼»¯
		TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚ�?ÂÒ»¸ö¸ü�?ÂÊÂ¼þ×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ýÊýµÄÔ¤·ÖÆµÖµ
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM�?òÉ�?¼ÆÊýÄ£Ê½
		SOFT_TIM_TimeBaseInit(SOFT_TIM4, &TIM_TimeBaseStructure); //¸ù¾�?Ö¸¶¨µÄ²ÎÊý³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊýµ¥Î»
		SOFT_TIM_ClearITPendingBit(SOFT_TIM4, TIM_FLAG_Update);
		SOFT_TIM_ITConfig(SOFT_TIM4,TIM_IT_Update,ENABLE ); //Ê¹ÄÜÖ¸¶¨µÄTIM3Ö�?¶�?,ÔÊ�?í¸ü�?ÂÖ�?¶�?

		//Ö�?¶�?ÓÅ�?È¼¶NVICÉèÖÃ
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4Ö�?¶�?
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //�?ÈÕ¼ÓÅ�?È¼¶1¼¶
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //´ÓÓÅ�?È¼¶1¼¶
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ�?¨µÀ±»Ê¹ÄÜ
		NVIC_Init(&NVIC_InitStructure);  //³õÊ¼»¯NVIC¼Ä´æÆ÷
	}

	void IO_TXD(u8 Data)
	{
		u8 i = 0;
		OI_TXD = 0;
		delay_us(BuadRate_9600);
		for(i = 0; i < 8; i++)
		{
			if(Data&0x01)
				OI_TXD = 1;
			else
				OI_TXD = 0;

			delay_us(BuadRate_9600);
			Data = Data>>1;
		}
		OI_TXD = 1;
		delay_us(BuadRate_9600);
	}

	///////////////////
	void USART_Send(u8 *buf, u8 len)
	{
		u8 t;
		for(t = 0; t < len; t++)
		{
			IO_TXD(buf[t]);
		}
	}

	void EXTI15_10_IRQHandler(void)
	{

		if(EXTI_GetFlagStatus(EXTI_Line14) != RESET)
		{
			if(OI_RXD == 0)
			{
				if(recvStat == COM_STOP_BIT)
				{
					recvStat = COM_START_BIT;
					SOFT_TIM_Cmd(SOFT_TIM4, ENABLE);
				}
			}
			EXTI_ClearITPendingBit(EXTI_Line14);
		}
	}
	///////////////////////
	void TIM4_IRQHandler(void)
	{
		if(SOFT_TIM_GetFlagStatus(SOFT_TIM4, TIM_FLAG_Update) != RESET)
		{
			SOFT_TIM_ClearITPendingBit(SOFT_TIM4, TIM_FLAG_Update);
			 recvStat++;
			if(recvStat == COM_STOP_BIT)
			{
				SOFT_TIM_Cmd(SOFT_TIM4, DISABLE);
				USART_buf[len++] = recvData;
				return;
			}
			if(OI_RXD)
			{
				recvData |= (1 << (recvStat - 1));
			}else{
				recvData &= ~(1 << (recvStat - 1));
			}
	  }
	}
//////////////////////////////
	void Init_SSerial(GPIO_TypeDef *TX_PORT, uint16_t GPIO_PIN_TX, GPIO_TypeDef *RX_PORT, uint16_t GPIO_PIN_RX,
			uint8_t GPIO_PortSourcRX, uint8_t GPIO_PinSourceRX,  uint32_t EXTI_LineRX, IRQn_Type* NVIC_IRQChannelRX)
	{
		  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		  delay_init();
		  IOConfig(TX_PORT, GPIO_PIN_TX, RX_PORT, GPIO_PIN_RX, GPIO_PortSourcRX, GPIO_PinSourceRX, EXTI_LineRX, NVIC_IRQChannelRX);
		  TIM4_Int_Init(107, 71);	 //1M¼ÆÊýÆµÂÊHAL

	}
