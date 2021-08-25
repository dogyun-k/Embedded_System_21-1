#include <stdio.h>
#include <stdint.h>
#include "utils.h"

uint32_t byte_to_word(uint8_t data[]){
	
	uint32_t result = 0;

	result = data[0];
	result |= data[1] << 8;
	result |= data[2] << 16;
	result |= data[3] << 24;

	return result;
}

void display_reg(){

	printf("============================== Register ==============================\n");
	for(uint32_t i = 0; i < 8; i++){
		for(uint32_t j = 0; j < 4; j++){
			printf("X[%2d] = %8d  ", i*4 + j, x_reg[i*4 + j]);
		}
		printf("\n");
	}
	printf("======================================================================\n");
}

void display_memory(uint32_t start, uint32_t size){

	for(uint32_t i = start; i < start + size; i++){

		printf("M[%4d] = 0x%x\n", i, memory[i]);
	}
}
