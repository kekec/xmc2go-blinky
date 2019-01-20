/*
 * main.c
 *
 *  Created on: 2019 Jan 20 21:23:30
 *  Author: wiegelep
 */



#include <xmc_common.h>
#include <xmc_gpio.h>

#define TICKS_PER_SECOND 1
/**

 * @brief main() - Simple blinky with systick timer
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. 
 */

int main(void)
{
	// Clock configuration
	SCU_GENERAL->PASSWD = 0x000000C0UL; // disable bit protection
	SCU_CLK->CLKCR = 0x3FF00400UL; // MCLK = 8MHz, PCLK = 8MHz
	while((SCU_CLK->CLKCR & SCU_CLK_CLKCR_VDDC2LOW_Msk));
	SCU_GENERAL->PASSWD = 0x000000C3UL; // enable bit protection
	SystemCoreClockUpdate();

	const XMC_GPIO_CONFIG_t p1_0_conf = {
	  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
	  .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW
	};
	XMC_GPIO_Init(P1_0,&p1_0_conf);					/* LED */
	XMC_GPIO_ToggleOutput(P1_0);

	SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

	while(1U)
	{

	}
}

void SysTick_Handler(void)
{
	XMC_GPIO_ToggleOutput(P1_0);
}
