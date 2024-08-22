extern int __VERIFIER_nondet_int(void);
extern unsigned long __VERIFIER_nondet_ulong(void);
extern unsigned char __VERIFIER_nondet_uchar(void);
extern void abort(void);
void assume_abort_if_not(int cond) {
  if (!cond) {
    abort();
  }
}
extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }

/*  Generated by CSeq 0.5 (-t4 -r2 -fcbmc) 2013-06-08 02:22:20  */

#include <stdlib.h>
#include <assert.h>

void __VERIFIER_assert(int cond) {
  if (!(cond)) {
  ERROR : {
    reach_error();
    abort();
  }
  }
  return;
}

#define __CS_type unsigned char
#define __CS_pthread_t unsigned char
#define __CS_pthread_mutex_t unsigned char
#define __CS_pthread_cond_t unsigned char

// cseq: max no. of rounds and threads (parameters for the translation)
#define __CS_ROUNDS 2
#define __CS_THREADS 4

// cseq: main extra variables used for the simulation
//// __CS_type __k;

__CS_type __CS_round = 0; // cseq: index of the current round being simulated

__CS_type __CS_ret = 0; // cseq: thread exit conditions
const __CS_type __CS_ret_PREEMPTED =
    0x01; // cseq: context-switch happened before thread end
const __CS_type __CS_ret_ERROR =
    0x02; // cseq: thread returned due to an error condition
const __CS_type __CS_ret_FINISHED =
    0x04; // cseq: thread finished without errors happening

__CS_type __CS_error =
    0; // cseq: set whenever an error is found and checked after thread-wrapping

/*
__CS_type __CS_error_detail = 0;                                       //cseq:
error condition details (tells why __CS_error was set) const __CS_type
__ERR_MAXTHREADS_REACHED = 0x01; const __CS_type __ERR_ERROR_LABEL_REACHED =
0x02; const __CS_type __ERR_ASSERT_FAILURE = 0x04; const __CS_type
__ERR_UNLOCK_ATTEMPT = 0x08; const __CS_type __ERR_JOIN_FAILED_WRONG_THREAD_ID =
0x10; const __CS_type __ERR_JOIN_FAILED_THREAD_NOT_CREATED = 0x20; const
__CS_type __ERR_COND_WAIT_MUTEX_NOT_OWNED = 0x30; const __CS_type
__ERR_MUTEX_DESTROY = 0x40; const __CS_type __ERR_MUTEX_NOT_OWNED = 0x80;
*/

// cseq: handling of the status of the threads
__CS_type __CS_thread_index; // cseq: currently running thread ranging in
                             // [1..max+1], 1 being main()

__CS_type __CS_thread_allocated[__CS_THREADS +
                                1]; // cseq: threads used in the simulation
__CS_type __CS_thread_born_round[__CS_THREADS +
                                 1]; // cseq: round when a thread is born

void *(*__CS_thread[__CS_THREADS + 1])(
    void *); // cseq: pointers to thread functions

__CS_type __CS_thread_status[__CS_ROUNDS][__CS_THREADS +
                                          1]; // cseq: thread status at a round
const __CS_type __THREAD_UNUSED = 0x00;       // cseq: not used
const __CS_type __THREAD_RUNNING = 0x01;      // cseq: successfully created
const __CS_type __THREAD_FINISHED =
    0x02; // cseq: finished with errors or without errors
/*
const __CS_type __THREAD_FINISHED_ERROR = 0x02;                        //cseq:
finished with errors const __CS_type __THREAD_FINISHED_NO_ERROR = 0x04; //cseq:
finished without errors
*/

__CS_type *__CS_thread_lockedon[__CS_ROUNDS]
                               [__CS_THREADS + 1]; // cseq: threads waiting for
                                                   // conditional variables

/*
//cseq: size of dynamically allocated memory blocks, indexed by var ID
int __CS_size[__CS_ROUNDS][9];
int __CS_cp___CS_size[__CS_ROUNDS][9];
*/

/*
unsigned int __CS_SwitchPoints[__CS_ROUNDS];
unsigned int __CS_StmtCount;
unsigned int __CS_SwitchDone;
*/

// cseq: function declarations
int __VERIFIER_nondet_int();

void __CS_cs(void) {
  __CS_type k = __VERIFIER_nondet_uchar();

  assume_abort_if_not(__CS_round + k < __CS_ROUNDS); // k==0 --> no switch
  __CS_round += k;
  // this is removed when not needed

  // __CS_ret = (__VERIFIER_nondet_int() && __CS_round ==
  // __CS_ROUNDS-1)?1:__CS_ret;  // preemption
  __CS_ret = (__VERIFIER_nondet_int() && __CS_round == __CS_ROUNDS - 1)
                 ? __CS_ret_PREEMPTED
                 : __CS_ret;
}
/*
void __CS_cs(void)
{
        if (__CS_SwitchDone == __CS_ROUNDS-1) return;

        if (__CS_SwitchPoints[__CS_SwitchDone] == __CS_StmtCount++) {
                __CS_type k;

                assume_abort_if_not(__CS_round+k < __CS_ROUNDS);   //
k==__CS_round --> no switch
                __CS_round += k;
                //assume_abort_if_not(__CS_thread_lockedon[__CS_round][__CS_thread_index]
== 0);

                __CS_SwitchDone++;
                //__CS_StmtCount = 0;
        }
}
*/

int __CS_pthread_mutex_init(__CS_pthread_mutex_t *mutex, void *attr) {
  return 0;
}

int __CS_pthread_mutex_destroy(__CS_pthread_mutex_t *lock) {
  if (*lock != __CS_thread_index && *lock != 0) {
    __CS_error = 1;
    __CS_ret = __CS_ret_ERROR;
    //__CS_error_detail = __ERR_MUTEX_DESTROY;
  } else {
    *lock = 0;
  }

  return 0;
}

int __CS_pthread_mutex_lock(__CS_pthread_mutex_t *lock) {
  if (*lock == 0) {
    *lock = (__CS_thread_index + 1);
  } else {
    __CS_ret = __CS_ret_PREEMPTED;
    return 1;
  }

  return 0;
}

int __CS_pthread_mutex_unlock(__CS_pthread_mutex_t *lock) {
  if (*lock != (__CS_thread_index + 1)) {
    __CS_error = 1;
    __CS_ret = __CS_ret_ERROR;
    //__CS_error_detail = __ERR_UNLOCK_ATTEMPT;
    return 1;
  } else {
    *lock = 0;
  }

  return 0;
}

int __CS_pthread_cond_init(__CS_pthread_cond_t *cond, void *attr) { return 0; }

int __CS_pthread_cond_signal(__CS_pthread_cond_t *cond) {
  int j;

  for (j = 0; j <= __CS_THREADS; j++) {
    if (__CS_thread_lockedon[__CS_round][j] == cond) {
      __CS_thread_lockedon[__CS_round][j] = 0;
    }
  }

  return 0;
}

int __CS_pthread_cond_broadcast(__CS_pthread_cond_t *cond) {
  int j;

  for (j = 0; j <= __CS_THREADS; j++) {
    if (__CS_thread_lockedon[__CS_round][j] == cond) {
      __CS_thread_lockedon[__CS_round][j] = 0;
    }
  }

  return 0;
}

int __CS_pthread_cond_wait(__CS_pthread_cond_t *cond,
                           __CS_pthread_mutex_t *lock) {
  // __CS_pthread_mutex_unlock(mutex);
  if (*lock != (__CS_thread_index + 1)) {
    __CS_error = 1;
    __CS_ret = __CS_ret_ERROR;
    //__CS_error_detail = __ERR_COND_WAIT_MUTEX_NOT_OWNED;
    return 1;
  } else {
    *lock = 0;
  }

  __CS_thread_lockedon[__CS_round][__CS_thread_index] = cond;
  __CS_ret = __CS_ret_PREEMPTED; // force context-switch

  // __CS_pthread_mutex_lock(mutex);
  if (*lock == 0) {
    *lock = __CS_thread_index + 1;
  } else {
    __CS_ret = __CS_ret_PREEMPTED;
    return 1;
  }

  return 0;
}

void __CS_assert(int expr) {
  if (!expr) {
    __CS_error = 1;
    //__CS_error_detail = __ERR_ASSERT_FAILURE;
    __CS_ret = __CS_ret_ERROR;
  }
}

void __CS_assume(int expr) {
  if (!expr) {
    __CS_ret = __CS_ret_PREEMPTED;
  }
}

int __CS_pthread_join(__CS_pthread_t thread, void **value_ptr) {
  // checking index range
  if (thread != 123 && thread > __CS_THREADS + 1) {
    __CS_error = 1;
    //__CS_error_detail = __ERR_JOIN_FAILED_WRONG_THREAD_ID;
    __CS_ret = __CS_ret_ERROR;
    return 0;
  }

  if (thread == 123 ||
      __CS_thread_status[__CS_round][thread] == __THREAD_RUNNING) {
    __CS_ret = __CS_ret_PREEMPTED;
    return 0;
  }

  if (__CS_thread_status[__CS_round][thread] == __THREAD_UNUSED) {
    __CS_error = 1;
    //__CS_error_detail = __ERR_JOIN_FAILED_THREAD_NOT_CREATED;
    __CS_ret = __CS_ret_ERROR;
    return 0;
  }

  /*
  assume_abort_if_not( __CS_thread_status[__CS_round][thread] ==
  __THREAD_FINISHED_ERROR ||
                    __CS_thread_status[__CS_round][thread] ==
  __THREAD_FINISHED_NO_ERROR );
  */

  assume_abort_if_not(__CS_thread_status[__CS_round][thread] ==
                      __THREAD_FINISHED);

  return 0;
}

int __CS_pthread_create(__CS_pthread_t *id1, void *attr, void *(*t1)(void *),
                        void *arg) {
  /* if (__VERIFIER_nondet_int()) { *id = -1; return -1; } */

  /*
  if (__CS_thread_index == __CS_THREADS+1) {
          __CS_error = 1;
          __CS_ret = __CS_ret_ERROR;
          __CS_error_detail = __ERR_MAXTHREADS_REACHED;
          return 1;
  }
  */

  if (__CS_thread_index == __CS_THREADS) {
    *id1 = 123;
    return -1;
  }

  __CS_thread_index++;

  __CS_thread_allocated[__CS_thread_index] = 1;
  __CS_thread_born_round[__CS_thread_index] = __CS_round;
  __CS_thread[__CS_thread_index] = t1;
  __CS_thread_status[__CS_round][__CS_thread_index] = __THREAD_RUNNING;

  *id1 = __CS_thread_index;

  return __CS_thread_index;
}

/*
void *__CS_malloc(int varID, int size)
{
        __CS_size[__CS_round][varID] = size;
        return malloc((size_t)size);
}

void __CS_free(int varID, void *ptr)
{
        __CS_size[__CS_round][varID] = 0;
}

int __CS_memcmp(void *a, void *b, int size)
{
        int j;

        for (j=0; j<size; j++)
                if (*(char *)(a+j) != *(char *)(b+j))

        return 0;
}
*/
// cseq: Sequentialised code starts here.
int w[__CS_ROUNDS] = {0};
int r[__CS_ROUNDS] = {0};
int x[__CS_ROUNDS];
int y[__CS_ROUNDS];
union __CS__u {
  int w[__CS_ROUNDS];
  int r[__CS_ROUNDS];
  int x[__CS_ROUNDS];
  int y[__CS_ROUNDS];
};

union __CS__u __CS_u;

void __VERIFIER_atomic_take_write_lock() {
  __CS_assume((w[__CS_round] == 0) && (r[__CS_round] == 0));
  w[__CS_round] = 1;
}

void __VERIFIER_atomic_take_read_lock() {
  __CS_assume(w[__CS_round] == 0);
  // cseq: Translation for the assignment statement "r[__CS_round] =
  // r[__CS_round] + 1", case 2
  __CS_u.r[__CS_round] = r[__CS_round];
  r[__CS_round] = r[__CS_round] + 1;
  if (__CS_ret) {
    r[__CS_round] = __CS_u.r[__CS_round];
  }
}

void __VERIFIER_atomic_release_read_lock() {
  // cseq: Translation for the assignment statement "r[__CS_round] =
  // r[__CS_round] - 1", case 2
  __CS_u.r[__CS_round] = r[__CS_round];
  r[__CS_round] = r[__CS_round] - 1;
  if (__CS_ret) {
    r[__CS_round] = __CS_u.r[__CS_round];
  }
}

void *writer(void *arg) {
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  __VERIFIER_atomic_take_write_lock();
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  x[__CS_round] = 3;
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  w[__CS_round] = 0;
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
}

void *reader(void *arg) {
  int l;
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  __VERIFIER_atomic_take_read_lock();
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  l = x[__CS_round];
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  // cseq: Translation for the assignment statement "y[__CS_round] = l", case 2
  __CS_u.y[__CS_round] = y[__CS_round];
  y[__CS_round] = l;
  if (__CS_ret) {
    y[__CS_round] = __CS_u.y[__CS_round];
  }
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  if (!(y[__CS_round] == x[__CS_round])) {
    __CS_cs();
    if (__CS_ret != 0) {
      return 0;
    }
  __CS_ERROR:
    __CS_error = 1;
    __CS_ret = __CS_ret_ERROR;
    return 0;
    __CS_cs();
    if (__CS_ret != 0) {
      return 0;
    }
    goto __CS_ERROR;
  }

  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  };
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  __VERIFIER_atomic_release_read_lock();
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
}

void *main_thread(void *arg) {
  __CS_pthread_t t1 = __VERIFIER_nondet_uchar();
  __CS_pthread_t t2 = __VERIFIER_nondet_uchar();
  __CS_pthread_t t3 = __VERIFIER_nondet_uchar();
  __CS_pthread_t t4 = __VERIFIER_nondet_uchar();
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  __CS_pthread_create(&t1, 0, writer, 0);
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  __CS_pthread_create(&t2, 0, reader, 0);
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  __CS_pthread_create(&t3, 0, writer, 0);
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  __CS_pthread_create(&t4, 0, reader, 0);
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  __CS_pthread_join(t1, 0);
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  __CS_pthread_join(t2, 0);
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  __CS_pthread_join(t3, 0);
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
  __CS_pthread_join(t4, 0);
  __CS_cs();
  if (__CS_ret != 0) {
    return 0;
  }
}

int main() {
  // cseq: Copies of global variables
  __CS_type __CS_cp___CS_thread_status[__CS_ROUNDS][__CS_THREADS + 1];
  __CS_type *__CS_cp___CS_thread_lockedon[__CS_ROUNDS][__CS_THREADS + 1];
  int __CS_cp_w[__CS_ROUNDS];
  int __CS_cp_r[__CS_ROUNDS];
  int __CS_cp_x[__CS_ROUNDS];
  int __CS_cp_y[__CS_ROUNDS];
  int i, j;

  for (i = 0; i < 2; i++) {
    __CS_cp_w[i] = __VERIFIER_nondet_int();
    __CS_cp_r[i] = __VERIFIER_nondet_int();
    __CS_cp_x[i] = __VERIFIER_nondet_int();
    __CS_cp_y[i] = __VERIFIER_nondet_int();
    for (j = 0; j < 5; j++) {
      __CS_cp___CS_thread_status[i][j] = __VERIFIER_nondet_uchar();
      __CS_cp___CS_thread_lockedon[i][j] =
          (unsigned char *)(void *)__VERIFIER_nondet_ulong();
    }
  }
  // cseq: Copy statements for global variables:
  // cseq: for each global variable x,
  // cseq: copy into x[1...___CS_ROUNDS] <--- __CS_cp_x[1..___CS_ROUNDS].
  // cseq: This is used to fill global variables with non-initialised data.
  __CS_thread_status[1][0] =
      __CS_cp___CS_thread_status[1][0]; // cseq: Copy of __CS_thread_status
  __CS_thread_status[1][1] = __CS_cp___CS_thread_status[1][1];
  __CS_thread_status[1][2] = __CS_cp___CS_thread_status[1][2];
  __CS_thread_status[1][3] = __CS_cp___CS_thread_status[1][3];
  __CS_thread_status[1][4] = __CS_cp___CS_thread_status[1][4];
  __CS_thread_lockedon[1][0] =
      __CS_cp___CS_thread_lockedon[1][0]; // cseq: Copy of __CS_thread_lockedon
  __CS_thread_lockedon[1][1] = __CS_cp___CS_thread_lockedon[1][1];
  __CS_thread_lockedon[1][2] = __CS_cp___CS_thread_lockedon[1][2];
  __CS_thread_lockedon[1][3] = __CS_cp___CS_thread_lockedon[1][3];
  __CS_thread_lockedon[1][4] = __CS_cp___CS_thread_lockedon[1][4];
  w[1] = __CS_cp_w[1]; // cseq: Copy of w
  r[1] = __CS_cp_r[1]; // cseq: Copy of r
  x[1] = __CS_cp_x[1]; // cseq: Copy of x
  y[1] = __CS_cp_y[1]; // cseq: Copy of y

  // cseq: create new thread for the main function
  __CS_round = 0;
  __CS_thread_index = 0;
  __CS_thread_born_round[0] = __CS_round;
  __CS_thread_status[0][0] = __THREAD_RUNNING;
  __CS_thread[0] = main_thread;
  __CS_thread_allocated[0] = 1;

  // cseq: simulation of the threads
  if (__CS_thread_allocated[0] == 1) {
    __CS_round = __CS_thread_born_round[0];
    __CS_ret = 0;
    __CS_thread[0](0);
    if (__CS_ret != __CS_ret_PREEMPTED) {
      __CS_thread_status[__CS_round][0] = __THREAD_FINISHED;
    }
  }

  if (__CS_thread_allocated[1] == 1) {
    __CS_round = __CS_thread_born_round[1];
    __CS_ret = 0;
    __CS_thread[1](0);
    if (__CS_ret != __CS_ret_PREEMPTED) {
      __CS_thread_status[__CS_round][1] = __THREAD_FINISHED;
    }
  }

  if (__CS_thread_allocated[2] == 1) {
    __CS_round = __CS_thread_born_round[2];
    __CS_ret = 0;
    __CS_thread[2](0);
    if (__CS_ret != __CS_ret_PREEMPTED) {
      __CS_thread_status[__CS_round][2] = __THREAD_FINISHED;
    }
  }

  if (__CS_thread_allocated[3] == 1) {
    __CS_round = __CS_thread_born_round[3];
    __CS_ret = 0;
    __CS_thread[3](0);
    if (__CS_ret != __CS_ret_PREEMPTED) {
      __CS_thread_status[__CS_round][3] = __THREAD_FINISHED;
    }
  }

  if (__CS_thread_allocated[4] == 1) {
    __CS_round = __CS_thread_born_round[4];
    __CS_ret = 0;
    __CS_thread[4](0);
    if (__CS_ret != __CS_ret_PREEMPTED) {
      __CS_thread_status[__CS_round][4] = __THREAD_FINISHED;
    }
  }

  // cseq: Consistency checks for global variables:
  // cseq: for each global variable x,
  // cseq: check that x[0...___CS_ROUNDS-1] == __CS_cp_x[1..___CS_ROUNDS].
  assume_abort_if_not(__CS_thread_status[0][0] ==
                      __CS_cp___CS_thread_status[1][0]); // cseq: Consistency of
                                                         // __CS_thread_status
  assume_abort_if_not(__CS_thread_status[0][1] ==
                      __CS_cp___CS_thread_status[1][1]);
  assume_abort_if_not(__CS_thread_status[0][2] ==
                      __CS_cp___CS_thread_status[1][2]);
  assume_abort_if_not(__CS_thread_status[0][3] ==
                      __CS_cp___CS_thread_status[1][3]);
  assume_abort_if_not(__CS_thread_status[0][4] ==
                      __CS_cp___CS_thread_status[1][4]);
  assume_abort_if_not(
      __CS_thread_lockedon[0][0] ==
      __CS_cp___CS_thread_lockedon[1][0]); // cseq: Consistency of
                                           // __CS_thread_lockedon
  assume_abort_if_not(__CS_thread_lockedon[0][1] ==
                      __CS_cp___CS_thread_lockedon[1][1]);
  assume_abort_if_not(__CS_thread_lockedon[0][2] ==
                      __CS_cp___CS_thread_lockedon[1][2]);
  assume_abort_if_not(__CS_thread_lockedon[0][3] ==
                      __CS_cp___CS_thread_lockedon[1][3]);
  assume_abort_if_not(__CS_thread_lockedon[0][4] ==
                      __CS_cp___CS_thread_lockedon[1][4]);
  assume_abort_if_not(w[0] == __CS_cp_w[1]); // cseq: Consistency of w
  assume_abort_if_not(r[0] == __CS_cp_r[1]); // cseq: Consistency of r
  assume_abort_if_not(x[0] == __CS_cp_x[1]); // cseq: Consistency of x
  assume_abort_if_not(y[0] == __CS_cp_y[1]); // cseq: Consistency of y

  // cseq: Error check
  __VERIFIER_assert(__CS_error != 1);
}
