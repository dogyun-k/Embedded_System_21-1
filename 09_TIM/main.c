#include "STM32FDiscovery.h"
// #include <stdio.h>

unsigned int count = 0, len;
unsigned int tim2_tick = 0;
unsigned char rec, adc_val;
char buf[5];

void sendStr(char buf[], int max);

/* Setting Start */

void clk(void)
{
	RCC_CR = 0;
	RCC_PLLCFGR = 0;
	RCC_CFGR = 0;
		
	RCC_CR |= (1<<16);                  // HSE set
	while( (RCC_CR & ( 1<<17) ) == 0 ); // wait until HSE ready
	
	RCC_PLLCFGR |= 8;           // 0x00000008;  // set PLLM
	RCC_PLLCFGR |= (336<<6);    // |= (336<<6); // set PLLN
	RCC_PLLCFGR |= (0<<16);     // set PLLP
	RCC_PLLCFGR |= (7<<24);     // 0x07000000;  // set PLLQ

	RCC_PLLCFGR |= (1<<22);     // set PLL src HSE
	

	RCC_CR |= (1<<24);          // PLL ON
	while( (RCC_CR & (1<<25)) == 0); // wait until PLL ready
	
	FLASH_ACR |= 5;
	RCC_CFGR |= 2;              // set PLL to system clock
	
		
	while( (RCC_CFGR & (12) ) != 8); // wait until PLL ready
	
	RCC_CFGR |= (1<<12) | (1<<10);  // set APB1 div 4
	RCC_CFGR |= (1<<15);            // set APB2 div2	
}

void set_usart2() {      // uart has 3 models
    // use UART PA2, PA3 pin 
    RCC_AHB1ENR |= 1<<0;
    GPIOA_MODER |= (1<<5) | (1<<7);
    GPIOA_AFRL |= (7<<8) | (7<<12);


    // set USART2
    RCC_APB1ENR |= (1<<17);     //  USART2 clock enable
    USART2_CR1 |= (0<<12);
    USART2_CR2 |= (0<<13) | (0<<12);

    USART2_BRR = (unsigned int)(42000000/115200);   // set Bour rate

    USART2_CR1 |= (1<<3) | (1<<2);
    USART2_CR1 |= (1<<5);
    USART2_CR1 |= (1<<13);


    // USART Interrupt enable
    NVIC_ISER1 |= 1<<6;

}

void set_adc1() {        // ADC1, channel 1, PA1
    RCC_AHB1ENR |= 0x00000001;      // RCC clock enable
    GPIOA_MODER |= 3<<2;            // RA1 analog mode
    RCC_APB2ENR |= 1<<8;            // ADC1 clock enable
    RCC_CFGR |= 1<<15 | 1<<13;      // set APB2 div4 = 42 MHz

    ADC1_CR2 |= 1<<0;               // ADC1 enable
    
    ADC1_SMPR2 |= 3<<0;             // channel 1 sampling cycle 56 cycle
    ADC1_CR1 |= 2<<24 | 1<<5;       // 8-bit resolution
                                    // end-of-conversion interrupt enable
    
    ADC1_CCR |= 1<<16;              // PCLK2 div 4      haven't to know
    ADC1_SQR1 |= 0<<20;             // channel 1:1 conversion
    ADC1_SQR3 |= 1<<0;              // 1st conversion : channel 1

    NVIC_ISER0 |= 1<<18;            // enable interrupt
}   

void set_timer2(){
    RCC_APB1ENR |= 1<<0;        // clock enable
    TIM2_CR1 = 0;               // init

    TIM2_PSC = 84 - 1;          // run based clock. It is a free scaler
    TIM2_ARR = 1000 - 1;        // auto reroad register
    TIM2_DIER |= 1<<0;          // interrump 
    TIM2_EGR |= 1<<0;           // if count up to 1000, reset to 0 => it means occuring update
    TIM2_CR1 |= 1<<0;           // finally starting timer

    NVIC_ISER0 |= 1<<28;
}

/* Setting End */


/* IRQHandlers Start */
void TIM2_IRQHandler() {
    TIM2_SR &= 0x00000000;

    tim2_tick++;

    if( tim2_tick == 1000 ) {       // 1ms * 1000 = 1 sec
        GPIOA_ODR ^= 1<<12;         // green

        ADC1_CR2 |= 1<<30;
        
        tim2_tick = 0;
    }
}

void USART2_IRQHandler() {
    if( USART2_SR & (1<<5) ) {
        rec = USART2_DR;        // read
        USART2_DR = rec;        // write

        while( !(USART2_SR & (1<<7) ));
        while( !(USART2_SR & (1<<6) ));

        USART2_CR1 |= (1<<5);
    }
}

void ADC1_IRQHandler() {
    if( ADC1_SR & 1<<1 ) { 
        adc_val = ADC1_DR & 0xff;
        
        // len = sprintf(buf, "%3d\n", adc_val);       // return : string length

        if(adc_val > 100) {
            buf[0] = (adc_val / 100) + '0';
            buf[1] = ((adc_val % 100) / 10) +'0';
            buf[2] = ((adc_val % 100) % 10) +'0';
            buf[3] = '\n';
            len = 4;
        }
        else {
            buf[0] = (adc_val / 10) + '0';
            buf[1] = (adc_val % 10) +'0';
            buf[2] = '\n';
            len = 3;
        }

        sendStr(buf, len);
    }
    // ADC1_CR2 |= 1<<30;
}

void EXTI0_IRQHandler() {
    GPIOD_ODR ^= 1 << 13;
    GPIOD_ODR ^= 1 << 14;
    GPIOD_ODR ^= 1 << 15;

    EXTI_PR |= 1<<0;    // clear pending bit for EXTI0
}

/* IRQHandlers End */




int main (void) {
	
	clk();
	
	RCC_CFGR |= 0x04600000;

    /* PORT A */    // led 
	RCC_AHB1ENR  |= 1<<0;       //RCC clock enable register	
    GPIOA_MODER  |= 0<<0;       // input mode
    GPIOA_OTYPER |= 0<<0;       // output push-pull
    GPIOA_PUPDR  |= 0<<0;       // no pull-up, pull-down

    /* button intr set */
    SYSCFG_EXTICR1  |= 0<<0;    // EXTI0 connect to PA0
    EXTI_IMR        |= 1<<0;    // Mask EXTI0
    EXTI_RTSR       |= 1<<0;    // Rising edge trigger enable
    EXTI_FTSR       |= 0<<0;    // Falling edge trigger disable
    NVIC_ISER0      |= 1<<6;    // Enable EXTI0 interrupt

	/* PORT D */    // button
	RCC_AHB1ENR  |= 1<<3;		// PORTD enable
	GPIOD_MODER  |= 1<<24;		// PORTD 12 general output mode
	GPIOD_MODER  |= 1<<26;		// PORTD 13 general output mode
	GPIOD_MODER  |= 1<<28;		// PORTD 14 general output mode
	GPIOD_MODER  |= 1<<30;		// PORTD 15 general output mode
	GPIOD_OTYPER |= 0x00000000;
	GPIOD_PUPDR	 |= 0x00000000;
	
    GPIOA_ODR |= 1<<12;

    set_timer2();
    set_usart2();
    set_adc1();


    ADC1_CR2 |= 1<<30;

	while(1) {
        // Waiting Interrupt 
	}
}





void sendStr(char buf[], int max) {
    int cnt = 0;
    while( cnt < max ) {
        USART2_DR = buf[cnt++];
        while( !(USART2_SR & (1<<7) ));
        while( !(USART2_SR & (1<<6) ));
    }
}

