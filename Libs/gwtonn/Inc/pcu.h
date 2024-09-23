#ifndef __PCU_H__
#define __PCU_H__

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

typedef enum {
	// Specific
	OPCODE_LED = 0x00,

	// Program related
	OPCODE_NOOP = 0x10,
	OPCODE_DELAY = 0x11
} OPCODE;

typedef struct {
	OPCODE opcode;
	void * parameter0;
	void * parameter1;
} Instruction;

typedef struct {
	uint32_t program_counter;
	uint16_t program_size;
	Instruction *instructions;
} PCU;

uint8_t PCU_Init(PCU *instance);
uint8_t PCU_Step(PCU *instance);
uint8_t PCU_Execute(PCU *instance);

#ifdef __cplusplus
}
#endif

#endif // __PCU_H__
