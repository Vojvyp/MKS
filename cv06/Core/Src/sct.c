/*
 * sct.c
 *
 *  Created on: 7. 10. 2021
 *      Author: student
 */

#include <stdint.h>
#include "stm32f0xx.h"
#include "sct.h"

#define sct_nla(x) do { if (x) GPIOB->BSRR = (1 << 5); else GPIOB->BRR = (1 << 5); } while (0)
#define sct_sdi(x) do { if (x) GPIOB->BSRR = (1 << 4); else GPIOB->BRR = (1 << 4);} while (0)
#define sct_clk(x) do { if (x) GPIOB->BSRR = (1 << 3); else GPIOB->BRR = (1 << 3);} while (0)
#define sct_noe(x) do { if (x) GPIOB->BSRR = (1 << 10); else GPIOB->BRR = (1 << 10);} while (0)

// Table to translate numbers to 7-seg registers
static const uint32_t reg_values[4][10] = {
 {
 //PCDE--------GFAB @ DIS1
 0b0111000000000111 << 16,
 0b0100000000000001 << 16,
 0b0011000000001011 << 16,
 0b0110000000001011 << 16,
 0b0100000000001101 << 16,
 0b0110000000001110 << 16,
 0b0111000000001110 << 16,
 0b0100000000000011 << 16,
 0b0111000000001111 << 16,
 0b0110000000001111 << 16,
 },
 {
 //----PCDEGFAB---- @ DIS2
 0b0000111101110000 << 0,
 0b0000110000010000 << 0,
 0b0000101110110000 << 0,
 0b0000111010110000 << 0,
 0b0000110011010000 << 0,
 0b0000111011100000 << 0,
 0b0000111111100000 << 0,
 0b0000110000110000 << 0,
 0b0000111111110000 << 0,
 0b0000111011110000 << 0,
 },
 {
 //PCDE--------GFAB @ DIS3
 0b0111000000000111 << 0,
 0b0100000000000001 << 0,
 0b0011000000001011 << 0,
 0b0110000000001011 << 0,
 0b0100000000001101 << 0,
 0b0110000000001110 << 0,
 0b0111000000001110 << 0,
 0b0100000000000011 << 0,
 0b0111000000001111 << 0,
 0b0110000000001111 << 0,
 },
 {
 //----43215678--- @ LED
 // light up leds in the bar
 0b0000000100000000 << 16,
 0b0000000100000000 << 16,
 0b0000001100000000 << 16,
 0b0000011100000000 << 16,
 0b0000111100000000 << 16,
 0b0000111110000000 << 16,
 0b0000111111000000 << 16,
 0b0000111111100000 << 16,
 0b0000111111110000 << 16,
 },
 };



/*Enable registers and signals*/
void sct_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // enable register GPIO B
	GPIOB->MODER |= GPIO_MODER_MODER5_0; // signal initializations
	GPIOB->MODER |= GPIO_MODER_MODER4_0;
	GPIOB->MODER |= GPIO_MODER_MODER3_0;
	GPIOB->MODER |= GPIO_MODER_MODER10_0;

	/*Write 0 to shift registers*/
	sct_led(0);
	sct_noe(0);

}

/*Fction to send the value to the 7-seg*/
void sct_led(uint32_t value)
{
	/*Loop 32 times through the value and allow latch after its done*/
	/*Starting from LSB setting it to 1 set clock and continue with shifted 1*/
	for (uint8_t i=0; i<32; i++)
	{
		sct_sdi(value & 1);
		value >>= 1;
		sct_clk(1);
		sct_clk(0);
	}
	sct_nla(1);
	sct_nla(0);
}

void sct_value(uint16_t value, uint8_t led)
{
	uint32_t reg=0;

	/*Extract the right number on the rigt position from the table*/
	/*eg. 231*/
	reg |= reg_values[0][value / 100 % 10]; // 231/100 = 2 % 10 = 2
	reg |= reg_values[1][value / 10 % 10];  // 231/10 = 23 % 10 = 3
	reg |= reg_values[2][value / 1 % 10];   // 231/1 = 231 % 10 = 1


	reg |= reg_values[3][led % 8]; // math for the bar

	sct_led(reg);
}
