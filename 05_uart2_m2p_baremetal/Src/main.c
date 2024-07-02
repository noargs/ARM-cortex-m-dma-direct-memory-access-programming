#include <stdint.h>

#include "stm32f4xx.h"
#include "main.h"

void button_init(void);
void uart2_init(void);
void dma1_init(void);
void send_data(void);

int main(void)
{
  button_init();
  uart2_init();
  send_data();
  dma1_init();

  for(;;);

  return 0;
}


void button_init(void)
{
  /**
    * Nucleo-F411 user button b1 connected at pc13
    */

  /** 1. enable the peripheral clock for the GPIOC periheral */
  /** 2. keep the gpio pin 13 in input mode */
  /** 3. enable the interrupt over that gpio pin */
  /** 4. enable the clock for SYSCFG register */
  /** 5. configure the SYSCFG register to choose pc13 -> exti15_10 */
  /** 6. configure the edge detection on the gpio pin [[[Cannot do before step 5]]] */
  /** 7. enable the IRQ related to that GPIO pin in NVIC of the processor */
  /** 8. on interrupt, pending register (EXTI_PR) is set, unset it in `EXTI15_10_IRQHandler` */

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

  GPIO_TypeDef *gpioc = GPIOC;
  gpioc->MODER &= ~GPIO_MODER_MODER13;

  EXTI_TypeDef *exti = EXTI;
  exti->IMR |= EXTI_IMR_MR13;

  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  SYSCFG_TypeDef *syscfg = SYSCFG;
  syscfg->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
  syscfg->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;

  exti->FTSR |= EXTI_FTSR_TR13;

  NVIC_EnableIRQ(EXTI15_10_IRQn);

}

void uart2_init(void)
{
  /** 1. enable the peripheral clock for the UART2 periheral */
  /** 2. configure the gpio pins for UART_Tx (pa2) and UART_Rx (pa3) functionality */
  /** 2a. enable the clock for the GPIOA peripheral */
  /** 2b. change the mode of the pa2 and pa3 to alternate function mode */
  /** 2c. enable or disable pull resistor if required */
  /** 3. configure the baud (BRR page:550) Calculation table page: 522, for 16Mhz clock and 115200 */
  /** 4. configure the data width, no. of stops bits, parity etc */
  /** 5. enable the Tx engine of the UART peripheral */
  /** 6. enable the UART2 peripheral */

  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  GPIO_TypeDef *gpioa = GPIOA;
  gpioa->MODER &= ~(0x3UL << GPIO_MODER2_Pos);
  gpioa->MODER |= GPIO_MODER2_AFM;
  gpioa->AFR[LOW] &= ~(0xFUL << GPIO_AFRL2_Pos);
  gpioa->AFR[LOW] |= GPIO_AFRL2_AF7;
  gpioa->PUPDR &= ~(0x3UL << GPIO_PUPDR2_Pos);
  gpioa->PUPDR |= GPIO_PUPDR2_PU;
  gpioa->MODER &= ~(0x3UL << GPIO_MODER3_Pos);
  gpioa->MODER |= GPIO_MODER3_AFM;
  gpioa->AFR[LOW] &= ~(0xFUL << GPIO_AFRL3_Pos);
  gpioa->AFR[LOW] |= GPIO_AFRL3_AF7;
  gpioa->PUPDR &= ~(0x3UL << GPIO_PUPDR3_Pos);
  gpioa->PUPDR |= GPIO_PUPDR3_PU;

  USART_TypeDef *uart2 = USART2;
  uart2->BRR = 0x8B;                    // 8.6875

  uart2->CR1 &= ~(USART_CR1_M);         // M: Word length, default `0`= 8 bit, not required, for brevity
  uart2->CR1 &= ~(USART_CR1_PS);        // Parity Selection: default `0`= Even, not required, for brevity
  uart2->CR2 &= ~(USART_CR2_STOP_1);    // STOP bit, default `0` = 1 stop bit, not required, for brevity

  uart2->CR1 |= USART_CR1_TE;

  uart2->CR1 |= USART_CR1_UE;

}

void dma1_init(void)
{
  /** 1. enable the peripheral clock for the dma1 */
  /** 2. identify the stream which is suitable for your peripheral */
  /** 3. identify the channel number on which uart2 peripheral sends the dma request */
  /** 4. program the source address, program the destination address */
  /** 5. program number of data items to send */
  /** 6. the direction (transfer mode) of data transfer, m2p, p2m, m2m */
  /** 7. program the source and destination data width */
  /** 8. direct mode or fifo mode (8a. if in fifo then select the fifo threshold as well) */
  /** 9. enable the circular mode if required */
  /** 10. single transfer or burst transfer */
  /** 11. configure the stream priority */
  /** 12. enable the stream */

}

void send_data(void)
{
  char message[] = "Hello world\r\n";

  uint32_t leng = sizeof(message);

  for (uint32_t i=0; i< leng; i++)
  {
	while (! (USART2->SR & USART_SR_TXE));
	USART2->DR = message[i];
  }
}
