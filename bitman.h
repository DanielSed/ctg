#ifndef BITMAN_H
#define BITMAN_H
#include <stdlib.h>

/* MACROS */
/* HELPER MACROS */
#define BIT_TOGGLE(VAR, N)      (VAR ^= (N))
#define BIT_SET_TRUE(VAR, N)    (VAR |= (N))
#define BIT_SET_FALSE(VAR, N)   (VAR &= ~(N))
#define BIT_VAL_AT_POS(VAR, N)  ((VAR & N) ? 1 : 0)

/* FUNCTION-LIKE MACROS */
#define FLAG_TOGGLE(VAR, N)    BIT_TOGGLE(VAR, N)
#define FLAG_SET(VAR, N, VAL)  (VAL) ? BIT_SET_TRUE(VAR, N) : BIT_SET_FALSE(VAR, N)
#define FLAG_SET_TRUE(VAR, N)  FLAG_SET(VAR, N, 1)
#define FLAG_SET_FALSE(VAR, N) FLAG_SET(VAR, N, 0)

/* FOR CONDITIONAL USE */
#define IS_FLAG_TRUE(VAR, N)   (BIT_VAL_AT_POS(VAR, N))
#define IS_FLAG_FALSE(VAR, N)  (!(IS_FLAG_TRUE(VAR, N)))

#endif
