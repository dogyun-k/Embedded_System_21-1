#include "STM32FDiscovery.h"
#include <string.h>

#define BUF_SIZE 2048

unsigned int count = 0;
unsigned char rec;

char welcome[] = "/*************************************/\n/* LED Controller Shell for STM32F4! */\n/*************************************/\n";
char help[] = "* Command List\nLEDON + [1, 2, 3, 4]\nLEDOFF + [1, 2, 3, 4]\nLEDALL + [0, 1]\nFLASH\n";
char error[] = "\nWrong command!\nType [help]\n";
char question[] = "\n> ";
char buffer[BUF_SIZE];

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

void set_usart2() {  // uart has 3 models
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

void print_error(){
    for(int i = 0; i < strlen(error); i++){
        USART2_DR = error[i];
        while( !(USART2_SR & (1<<7) ));
        while( !(USART2_SR & (1<<6) ));
    }
}

void print_help(){
    for(int i = 0; i < strlen(help); i++){
        USART2_DR = help[i];
        while( !(USART2_SR & (1<<7) ));
        while( !(USART2_SR & (1<<6) ));
    }
}

void USART2_IRQHandler() {
    if( USART2_SR & (1<<5) ) {
        rec = USART2_DR;        // read
        USART2_DR = rec;        // write

        if(rec != 13){          // 13 == Enter
            buffer[count++] = rec;
        }
        else{
            int i;
            USART2_DR = 13;
            while( !(USART2_SR & (1<<7) ));
            while( !(USART2_SR & (1<<6) ));


            // store command 
            char command[3][BUF_SIZE];
            char *ptr = strtok(buffer, " ");
            int j = 0;
            while( ptr != NULL ){
                strncpy(command[j], "", BUF_SIZE);
                strncpy(command[j], ptr, strlen(ptr));
                ptr = strtok(NULL, " ");
                j++;
            }


            // print command
            // for(i = 0; i < BUF_SIZE; i++){
            //     USART2_DR = buffer[i];
            //     while( !(USART2_SR & (1<<7) ));
            //     while( !(USART2_SR & (1<<6) ));
            // }
            // for(i = 0; i < strlen(command[0]); i++){
            //     USART2_DR = command[0][i];
            //     while( !(USART2_SR & (1<<7) ));
            //     while( !(USART2_SR & (1<<6) ));
            // }

            // for(i = 0; i < strlen(command[1]); i++){
            //     USART2_DR = command[1][i];
            //     while( !(USART2_SR & (1<<7) ));
            //     while( !(USART2_SR & (1<<6) ));
            // }


            // Functions
            if( strcmp(command[0], "help") == 0){           // help
                print_help();
            }
            else if( strcmp(command[0], "LEDON") == 0){     // LED ON
                if( strcmp(command[1], "1") == 0 ){
                    GPIOD_ODR |= 1 << 12;
                }
                else if( strcmp(command[1], "2") == 0 ){
                    GPIOD_ODR |= 1 << 13;
                }
                else if( strcmp(command[1], "3") == 0 ){
                    GPIOD_ODR |= 1 << 14;
                }
                else if( strcmp(command[1], "4") == 0 ){
                    GPIOD_ODR |= 1 << 15;
                }
                else{
                    print_error();
                }
            }
            else if( strcmp(command[0], "LEDOFF") == 0){    // LED OFF
                if( strcmp(command[1], "1") == 0 ){
                    GPIOD_ODR &= ~(1 << 12);
                }
                else if( strcmp(command[1], "2") == 0 ){
                    GPIOD_ODR &= ~(1 << 13);
                }
                else if( strcmp(command[1], "3") == 0 ){
                    GPIOD_ODR &= ~(1 << 14);
                }
                else if( strcmp(command[1], "4") == 0 ){
                    GPIOD_ODR &= ~(1 << 15);
                }
                else{
                    print_error();
                }
            }
            else if( strcmp(command[0], "LEDALL") == 0 ){
                if( strcmp(command[1], "0") == 0 ){
                    GPIOD_ODR &= ~(1 << 12);
                    GPIOD_ODR &= ~(1 << 13);
                    GPIOD_ODR &= ~(1 << 14);
                    GPIOD_ODR &= ~(1 << 15);
                }
                else if( strcmp(command[1], "1") == 0 ){
                    GPIOD_ODR |= 1 << 12;
                    GPIOD_ODR |= 1 << 13;
                    GPIOD_ODR |= 1 << 14;
                    GPIOD_ODR |= 1 << 15;
                }
                else{
                    print_error();
                }
            }
            else if( strcmp(command[0], "FLASH") == 0 ){
                for(i = 0; i < 10; i++){
                    for(int j = 0; j < 100000; j++);
                    GPIOD_ODR ^= 1 << 12;
                    
                    for(int j = 0; j < 100000; j++);
                    GPIOD_ODR ^= 1 << 13;
                    
                    for(int j = 0; j < 100000; j++);
                    GPIOD_ODR ^= 1 << 14;
                    
                    for(int j = 0; j < 100000; j++);
                    GPIOD_ODR ^= 1 << 15;
                }
            }
            else{
                // ERROR
                print_error();
            }



            strncpy(buffer, "", BUF_SIZE);
            for(i = 0; i < 3; i++){
                strncpy(command[i], "", strlen(command[i]));
            }

            for(i = 0; i < strlen(question); i++){      // print question
                USART2_DR = question[i];
                while( !(USART2_SR & (1<<7) ));
                while( !(USART2_SR & (1<<6) ));
            }
            count = 0;
        }
   
        
        USART2_CR1 |= (1<<5);
    }
}



void EXTI0_IRQHandler() {
    GPIOD_ODR ^= 1 << 13;
    GPIOD_ODR ^= 1 << 14;
    GPIOD_ODR ^= 1 << 15;

    EXTI_PR |= 1<<0;    // clear pending bit for EXTI0
}

int main (void)
{
	
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
	
    
    set_usart2();

    // Init Terminal Screen
    int i;
    for(i = 0; i < strlen(welcome); i++){
        USART2_DR = welcome[i];
        while( !(USART2_SR & (1<<7) ));
        while( !(USART2_SR & (1<<6) ));
    }
    for(i = 0; i < strlen(question); i++){
        USART2_DR = question[i];
        while( !(USART2_SR & (1<<7) ));
        while( !(USART2_SR & (1<<6) ));
    }

	while(1) {
        // Waiting Interrupt 
	}
}
