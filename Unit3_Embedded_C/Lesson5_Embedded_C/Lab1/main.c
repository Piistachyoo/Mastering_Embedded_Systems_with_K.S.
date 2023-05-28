/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : main.c			         	                 		 */
/* Date          : May 28, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "Platform_Types.h"
#include <stdlib.h>

// register addresses

#define RCC_BASE	0x40021000
#define PORTB_BASE	0x40010C00

#define RCC_APB2ENR	*(vint32_t*)(RCC_BASE + 0x18)
#define GPIOB_CRL	*(vint32_t*)(PORTB_BASE)
#define GPIOB_CRH	*(vint32_t*)(PORTB_BASE + 0x04)
#define GPIOB_ODR	*(vint32_t*)(PORTB_BASE + 0x0C)

typedef union{
	vint32_t all_fields;
	struct{
		vint32_t pin0	 :1;
		vint32_t pin1	 :1;
		vint32_t pin2	 :1;
		vint32_t pin3	 :1;
		vint32_t pin4	 :1;
		vint32_t pin5	 :1;
		vint32_t pin6	 :1;
		vint32_t pin7	 :1;
		vint32_t pin8	 :1;
		vint32_t pin9	 :1;
		vint32_t pin10   :1;
		vint32_t pin11	 :1;
		vint32_t pin12	 :1;
		vint32_t pin13	 :1;
		vint32_t pin14	 :1;
		vint32_t pin15	 :1;
	}ODR_field;
}R_ODR_t;

volatile R_ODR_t *R_ODR = (volatile R_ODR_t *)(PORTB_BASE + 0x0C);
uint8 g_variables[3] = {1,2,3};
uint8 const const_variables[3] = {1,2,3};
uint8 BSS_VAR[3];

void * _sbrk (int incr){
	static uint8* heap_ptr = NULL;
	uint8* prev_heap_ptr = NULL;
	extern uint32 _E_BSS; // symbol
	extern uint32 _E_HEAP; // symbol
	/* If first time to initialize */
	if(NULL == heap_ptr){
		heap_ptr = (uint8*)&_E_BSS;
	}
	
	/* Save current heap location */
	prev_heap_ptr = heap_ptr;
	
	/* Protect stack */
	if((heap_ptr + incr) > ((uint8*)&_E_HEAP)){
		return (void*)NULL;
	}
	
	/* Reserve increment size */
	heap_ptr += incr;
	
	return (void*)prev_heap_ptr;
}

int main(void)
{
	int *ptr = malloc(sizeof(int));
	free(ptr);
	RCC_APB2ENR |= (1<<3); // Enable RCC Clock for port B
	GPIOB_CRL = (1<<1);
	while(1){
		R_ODR->ODR_field.pin0 = 1;
		for(int i=0; i<5000;i++);
		R_ODR->ODR_field.pin0 = 0;
		for(int i=0; i<5000;i++);
	}
	return 0;
}
