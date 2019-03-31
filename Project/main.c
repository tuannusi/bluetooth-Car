#include <stm32f10x.h>
#include <delay.h>

GPIO_InitTypeDef 				GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM_InitStructure;
TIM_OCInitTypeDef 			TIM_OCInitStructure;
USART_InitTypeDef				UART_InitStructure;
NVIC_InitTypeDef				NVIC_InitStructure;

void TIM_PWM_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);

unsigned int Velo_Right(unsigned int velo);
unsigned int Velo_Left(unsigned int velo);
void Control_Motor_Right_Fordward(void);
void Control_Motor_Left_Fordward(void);
void Control_Motor_Left_Backward(void);
void Control_Motor_Right_Backward(void);
void Fordward(void);
void Backward(void);
void Turn_Left(void);
void Turn_Right(void);
void Stop(void);
void ControlServo(unsigned int goc);
void FrontLed_Left(unsigned int status);
void FrontLed_Right(unsigned int status);
void BackLed_Left(unsigned int status);
void BackLed_Right(unsigned int status);

int i = 0;
char data  ;


int main()
{
	TIM_PWM_Configuration();
	GPIO_Configuration();
	USART_Configuration();
	delay_init(SystemCoreClock);
	while(1)
	{
		switch(data)
		{
			case '0':
				Velo_Right(0);
				Velo_Left(0);
			break;
			
			case '1':
				Velo_Right(10);
				Velo_Left(10);
			break;
			
			case '2':
				Velo_Right(20);
				Velo_Left(20);
			break;
			
			case '3':
				Velo_Right(30);
				Velo_Left(30);
			break;
			
			case '4':
				Velo_Right(40);
				Velo_Left(40);
			break;
			
			case '5':
				Velo_Right(50);
				Velo_Left(50);
			break;
			
			case '6':
				Velo_Right(60);
				Velo_Left(60);
			break;
			
			case '7':
				Velo_Right(70);
				Velo_Left(70);
			break;
			
			case '8':
				Velo_Right(80);
				Velo_Left(80);
			break;
			
			case '9':
				Velo_Right(90);
				Velo_Left(90);
			break;
			
			case 'q':
				Velo_Right(100);
				Velo_Left(100);
			break;
			
			case 'F':
				Fordward();
				ControlServo(85);
			break;
			
			case 'B':
				Backward();
				ControlServo(85);
			break;
			
			case 'L':
				ControlServo(57);
			break;
			
			case 'R':
				ControlServo(110);
			break;
			
			case 'G':
				ControlServo(57);
				Fordward();
			break;
			
			case 'I':
				ControlServo(110);
				Fordward();
			break;
			
			case 'H':
				ControlServo(57);
				Backward();
			break;
			
			case 'J':
				ControlServo(110);
				Backward();
			break;
			
			case 'W':
				FrontLed_Left(1);
				FrontLed_Right(1);
			break;
			
			case 'w':
				FrontLed_Left(0);
				FrontLed_Right(0);
			break;
			
			case 'U':
				BackLed_Left(1);
				BackLed_Right(1);
			break;
			
			case 'u':
				BackLed_Left(0);
				BackLed_Right(0);
			break;
			
			case 'V':
				BackLed_Left(1);
				BackLed_Right(1);
				FrontLed_Left(1);
				FrontLed_Right(1);
				delay_ms(10);
				BackLed_Left(0);
				BackLed_Right(0);
				FrontLed_Left(0);
				FrontLed_Right(0);
				delay_ms(10);
			break;
			
			case 'v':
				BackLed_Left(0);
				BackLed_Right(0);
				FrontLed_Left(0);
				FrontLed_Right(0);
			break;
			
			case 'S':
				Stop();
				ControlServo(85);
			break;
			
			case 'D':
				Stop();
				ControlServo(85);
			break;
			
			default:
				Stop();
				ControlServo(85);
				break;
			
		}
	}
}

void TIM_PWM_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_InitStructure.TIM_Prescaler = 35;
	TIM_InitStructure.TIM_Period = 39999;
	TIM_InitStructure.TIM_ClockDivision = 0;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM1, &TIM_InitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 0;
	
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
	
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);
	
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	
	TIM_Cmd(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}

void GPIO_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
		
}

void USART_Configuration(void)
{

			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);/* USART2 Periph clock enable */
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			
			/* Cau Tx mode AF_PP, Rx mode FLOATING  */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOA, &GPIO_InitStructure);	
		
		/*Cau hinh USART*/
			UART_InitStructure.USART_BaudRate = 9600;
			UART_InitStructure.USART_WordLength = USART_WordLength_8b;
			UART_InitStructure.USART_StopBits = USART_StopBits_1;
			UART_InitStructure.USART_Parity = USART_Parity_No;
			UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			UART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART2, &UART_InitStructure);
				
		/* Cau hinh vector ngat va muc uu tien */
			NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
			
			/* xoa co ngat nhan cho lan dau su dung*/
			USART_ClearFlag(USART2, USART_IT_RXNE);
			
			/* Cau hinh cho phep ngat nhan*/
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

			/* Cho phep UART hoat dong */
			USART_Cmd(USART2, ENABLE);
}

unsigned int Velo_Right(unsigned int velo)
{
	TIM1->CCR2 = velo*399; // PA9
	if(TIM1->CCR2 > 39999)
		TIM1->CCR2 = 39999;
	if(TIM1->CCR2 < 1)
		TIM1->CCR2 = 1;
	return TIM1->CCR2;
}

unsigned int Velo_Left(unsigned int velo)
{
	TIM1->CCR1 = velo*399; // PA8
	if(TIM1->CCR1 > 39999)
		TIM1->CCR1 = 39999;
	if(TIM1->CCR1 < 1)
		TIM1->CCR1 = 1;
	return TIM1->CCR1;
}

void Control_Motor_Left_Fordward(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

void Control_Motor_Left_Backward(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
}

void Control_Motor_Right_Fordward(void)
{
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
}

void Control_Motor_Right_Backward(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
}

//FORDWARD
void Fordward(void)
{
	Control_Motor_Left_Fordward();
	Control_Motor_Right_Fordward();
}

//BACKWARD
void Backward(void)
{
	Control_Motor_Left_Backward();
	Control_Motor_Right_Backward();
}

//TURN LEFT
void Turn_Left(void)
{
	Control_Motor_Left_Backward();
	Control_Motor_Right_Fordward();
}

//TURN RiGHT
void Turn_Right(void)
{
	Control_Motor_Right_Backward();
	Control_Motor_Left_Fordward();
}

//STOP
void Stop(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}

//CONTROL SERRVO
void ControlServo(unsigned int goc)
{
	float data;
	data = 20.278*goc + 1500;
	if(goc>180)
		goc = 180;
	if(goc<1)
		goc = 0;
	TIM_SetCompare4(TIM1,data);
	
}

//LED
void FrontLed_Left(unsigned int status) 
{
	if(status == 1) // trai sang
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
	}
	else
		GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
}

void FrontLed_Right(unsigned int status) 
{
	if(status == 1) // phai sang
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
	}
	else
		GPIO_ResetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
}

void BackLed_Left(unsigned int status)  
{
	if(status == 1) // trai sang
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5);
	}
	else
		GPIO_ResetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5);
}

void BackLed_Right(unsigned int status)  
{
	if(status == 1) // phai sang
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_6| GPIO_Pin_7);
	}
	else
		GPIO_ResetBits(GPIOA, GPIO_Pin_6 | GPIO_Pin_7);
}



