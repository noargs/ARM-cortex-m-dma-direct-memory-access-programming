#ifndef MAIN_H_
#define MAIN_H_

#define LOW                  0
#define HIGH                 1

#define GPIO_MODER2_Pos      (4U)
#define GPIO_MODER2_AFM      (0x2UL << GPIO_MODER2_Pos)
#define GPIO_MODER3_Pos      (6U)
#define GPIO_MODER3_AFM      (0x2UL << GPIO_MODER3_Pos)

#define GPIO_AFRL2_Pos       (8U)
#define GPIO_AFRL2_AF7       (0x7UL << GPIO_AFRL2_Pos)
#define GPIO_AFRL3_Pos       (12U)
#define GPIO_AFRL3_AF7       (0x7UL << GPIO_AFRL3_Pos)

#define GPIO_PUPDR2_Pos      (4U)
#define GPIO_PUPDR2_PU       (0x1UL << GPIO_PUPDR2_Pos)
#define GPIO_PUPDR3_Pos      (6U)
#define GPIO_PUPDR3_PU       (0x1UL << GPIO_PUPDR3_Pos)

#endif /* MAIN_H_ */
