#include "ADC.h"

void ADC_Init() {
  //Change the function of the pin to ADC
  TRIMPOT |= 1;
	LDR_LEFT |= 1;
	LDR_RIGHT |= 1;

  //Change the mode value of the pin to mode which should be selected if Analog mode is used
  TRIMPOT &= ~(1 << 3) & ~(1 << 4);
	LDR_LEFT &= ~(1 << 3) & ~(1 << 4);
	LDR_RIGHT &= ~(1 << 3) & ~(1 << 4);

  //Change Analog/Digital mode of pin to Analog
  TRIMPOT &= ~(1 << 7);
	LDR_LEFT &= ~(1 << 7);
	LDR_RIGHT &= ~(1 << 7);

  //Turn on ADC
  PCONP |= (1 << 12);

  //Set the CLKDIV and make the A/D converter operational without burst mode
  ADC->CR |= 0x3B00 | (1 << 21);

  //NVIC_EnableIRQ(ADC_IRQn);
  //NVIC_ClearPendingIRQ(ADC_IRQn);

  //ADC->INTEN |= (1 << 0);
	//ADC->INTEN |= (1 << 2);
	//ADC->INTEN |= (1 << 3);
}

void ADC_Start() {
  //Write a code for starting A/D conversion
  uint32_t value = ADC->CR;
  value |= (1 << 24);
  value &= ~(1 << 25) & ~(1 << 26);
  ADC->CR = value;
}

void ADC_Stop() {
  //Write a code for stopping A/D conversion
	uint32_t value = ADC->CR;
	value &= ~(1 << 24);
	value &= ~(1 << 25);
	value &= ~(1 << 26);
  ADC->CR = value;
}

uint32_t trimpot = 30;

uint32_t Trimpot_Read() {
  //Configure CR SEL bits for sampled and converting corresponding pin
  uint32_t value = ADC->CR;
  value &= ~(1 << 0);
  value &= ~(1 << 2);
  value &= ~(1 << 3);
  value |= (1 << 0);
  ADC->CR = value;

  ADC_Start();

  //Wait until A/D conversion completed
  while ((ADC->DR[0] & (1 << 31)) == 0);

  uint32_t data = 0;

  //Convert the data result to 0 - 100 range and return the ADC data
  data = ((ADC->DR[0] >> 4) & 0xFFF);
  data *= 100;
  data /= ADC_MAX_VALUE;

  ADC_Stop();

  return data;
}

uint32_t ldrLeft = 500;

uint32_t LDR_Left_Read() {
  //Configure CR SEL bits for sampled and converting corresponding pin
  uint32_t value = ADC->CR;
  value &= ~(1 << 0);
  value &= ~(1 << 2);
  value &= ~(1 << 3);
  value |= (1 << 2);
  ADC->CR = value;

  ADC_Start();

  //Wait until A/D conversion completed
  while ((ADC->DR[2] & (1 << 31)) == 0);

  uint32_t data;

  //Convert the data result to 0 - 1000 range and return the ADC data
  data = ((ADC->DR[2] >> 4) & 0xFFF);
  data *= 1000;
  data /= ADC_MAX_VALUE;

  ADC_Stop();

  return data;
}

uint32_t ldrRight = 500;

uint32_t LDR_Right_Read() {
  //Configure CR SEL bits for sampled and converting corresponding pin
  uint32_t value = ADC->CR;
  value &= ~(1 << 0);
  value &= ~(1 << 2);
  value &= ~(1 << 3);
  value |= (1 << 3);
  ADC->CR = value;

  ADC_Start();

  //Wait until A/D conversion completed
  while ((ADC->DR[3] & (1 << 31)) == 0);

  uint32_t data;

  //Convert the data result to 0 - 1000 range and return the ADC data
  data = ((ADC->DR[3] >> 4) & 0xFFF);
  data *= 1000;
  data /= ADC_MAX_VALUE;

  ADC_Stop();

  return data;
}
