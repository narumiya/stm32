#include "config_usb.h"

#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"
#include "usb_dcd_int.h"

#define BUFFER_LENGTH 10

/******************************************************************************
*	タイトル ： microUSBの一文字送信
*	  関数名 ： usb_put_char
*	  戻り値 ： void型 
*	   引数1 ： char型 c  送信する文字
*	  作成者 ： 桐生
*	  作成日 ： 2014/11/14
******************************************************************************/
void usb_put_char(char c){
	VCP_put_char((uint8_t)c);
}
/******************************************************************************
*	タイトル ： microUSBの設定関数
*	  関数名 ： Init_usb
*	  戻り値 ： void型
*	    引数 ： なし
*	  作成者 ： 桐生
*	  作成日 ： 2014/11/14
******************************************************************************/
void Init_usb(void){
	USBD_Init(&USB_OTG_dev,USB_OTG_FS_CORE_ID,&USR_desc,&USBD_CDC_cb,&USR_cb);
}

//static char buffer[BUFFER_LENGTH];
/*int usb_available(void){
	 return (VCP_get_string(buffer));
}*/

void usb_get_string(unsigned char *str){
	// strcpy(str, buffer);
 }

/******************************************************************************
*	タイトル ： カラフルなリング	楽しいよー＼(゜ロ＼)(／ロ゜)／
*	  関数名 ： ColorfulRingOfDeath
*	  戻り値 ： void型 なし
*	    引数 ： なし
*	  作成者 ： unknown
*	  作成日 ： 1970/01/01
******************************************************************************/
void ColorfulRingOfDeath(void)
{
	uint16_t ring = 1;
	while (1)
	{
		uint32_t count = 0;
		while (count++ < 500000);

		GPIOD->BSRRH = (ring << 12);
		ring = ring << 1;
		if (ring >= 1<<4)
		{
			ring = 1;
		}
		GPIOD->BSRRL = (ring << 12);
	}
}


/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
	ColorfulRingOfDeath();
}

/*******************************************************************************
* Function Name  : MemManage_Handler
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
	ColorfulRingOfDeath();
}

/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
	ColorfulRingOfDeath();
}

/*******************************************************************************
* Function Name  : UsageFault_Handler
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
	ColorfulRingOfDeath();
}

/*******************************************************************************
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
* Function Name  : DebugMon_Handler
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMon_Handler(void)
{
}

/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}
/*******************************************************************************
* Function Name  : SysTick_IRQHandler
* Description    : This function handles SysTick interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void OTG_FS_IRQHandler(void)
{
  USBD_OTG_ISR_Handler (&USB_OTG_dev);
}
/*******************************************************************************
* Function Name  : SysTick_IRQHandler
* Description    : This function handles SysTick interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void OTG_FS_WKUP_IRQHandler(void)
{
  if(USB_OTG_dev.cfg.low_power)
  {
    *(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9 ;
    SystemInit();
    USB_OTG_UngateClock(&USB_OTG_dev);
  }
  EXTI_ClearITPendingBit(EXTI_Line18);
}
