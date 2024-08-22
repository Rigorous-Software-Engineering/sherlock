#define __CBMC_assert(cond) __CPROVER_assert((cond), "assertion"); __CPROVER_assume(cond)
