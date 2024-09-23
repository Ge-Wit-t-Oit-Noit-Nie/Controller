#include "pcu.h"
#include "main.h"
#include "cmsis_os.h"

/**
 * Initialise the PCU
 */
uint8_t PCU_Init(PCU *instance) {
	instance->program_counter=0;
	return 0;
}

uint8_t PCU_Step(PCU *instance) {
	instance->program_counter++;
	if(instance->program_counter >= instance->program_size) instance->program_counter=0;

	return instance->program_counter;
};

/**
 * Start the Program Control Unit
 */
uint8_t PCU_Execute(PCU *instance) {

	switch(instance->instructions[instance->program_counter].opcode){
	case OPCODE_LED:
		// TODO: Remove the instruction from PCU. Instead, send message
		HAL_GPIO_TogglePin((GPIO_TypeDef*)instance->instructions[instance->program_counter].parameter1, (uint16_t)instance->instructions[instance->program_counter].parameter0);
		break;
	case OPCODE_DELAY:
		osDelay((uint32_t)instance->instructions[instance->program_counter].parameter0);

	case OPCODE_NOOP:
		break;
	}
	return 0;
}
