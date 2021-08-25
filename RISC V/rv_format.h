#ifndef RV_FORMAT
#define RV_FORMAT.h

typedef union{
	uint32_t instr;

	struct{
		uint32_t opcode:7;
		uint32_t rd:5;
		uint32_t funct3:3;
		uint32_t rs1:5;
		uint32_t rs2:5;
		uint32_t funct7:7;
	} r;

	struct{
		uint32_t opcode:7;
		uint32_t rd:5;
		uint32_t funct3:3;
		uint32_t rs1:5;
		uint32_t imm:12;
	} i;

	struct{
		uint32_t opcode:7;
		uint32_t imm1:5;
		uint32_t funct3:3;
		uint32_t rs1:5;
		uint32_t rs2:5;
		uint32_t imm2:7;
	} sb;

	struct{
		uint32_t opcode:7;
		uint32_t rd:5;
		uint32_t imm:20;
	} u;
	
	struct{
		uint32_t opcode:7;
		uint32_t rd:5;
		uint32_t imm:20;
	} uj;
} rv_format;

#endif

