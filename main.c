#include "stm32f1xx.h"

int main(void){
	uint8_t seg_code[10] = {
	    0x3F, // 0 -> 0b00111111
	    0x06, // 1 -> 0b00000110
	    0x5B, // 2 -> 0b01011011
	    0x4F, // 3 -> 0b01001111
	    0x66, // 4 -> 0b01100110
	    0x6D, // 5 -> 0b01101101
	    0x7D, // 6 -> 0b01111101
	    0x07, // 7 -> 0b00000111
	    0x7F, // 8 -> 0b01111111
	    0x6F  // 9 -> 0b01101111
	};

	int pulse_count = 0;

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	GPIOA->CRL = 0x22222222;
	GPIOB->CRL &= ~(0xF << 0);
	GPIOB->CRL |=  (0x8 << 0);
	GPIOB->ODR |=  (0x1 << 0);

	GPIOA->ODR = 0x00;
	GPIOA->ODR = seg_code[pulse_count];

	while(1){
		if ((GPIOB->IDR & (1 << 0)) == 0){
			while(!(GPIOB->IDR & (1<<0)));
			pulse_count = pulse_count + 1;
			if (pulse_count == 10){
				pulse_count = 0;
			}
			GPIOA->ODR = 0x00;
			GPIOA->ODR = seg_code[pulse_count];
		}
	}

}
