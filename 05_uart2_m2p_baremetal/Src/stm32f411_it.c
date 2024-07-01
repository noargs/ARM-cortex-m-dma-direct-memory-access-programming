#include "stm32f4xx.h"

void clear_exti_pending_bit(void)
{
  EXTI_TypeDef *exti = EXTI;

  if ((exti->PR & EXTI_PR_PR13))
  {
	/** clear pending bit by writing 1 */
	exti->PR |= EXTI_PR_PR13;
  }

}

void EXTI15_10_IRQHandler(void)
{
  clear_exti_pending_bit();
}

