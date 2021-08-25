#ifndef UTILS_H
#define UTILS_H

extern uint8_t memory[4096];
extern uint32_t x_reg[32];

uint32_t byte_to_word(uint8_t data[]);

void display_reg();
void display_memory(uint32_t start, uint32_t size);

#endif
