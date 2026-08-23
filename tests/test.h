#ifndef TEST_H
#define TEST_H

#include <stdio.h>

extern int tests_run;
extern int tests_failed;

/* Fails loudly with file:line and the failing expression, keeps running. */
#define CHECK(cond)                                                            \
  do {                                                                         \
    tests_run++;                                                               \
    if (!(cond)) {                                                             \
      tests_failed++;                                                          \
      fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);          \
    }                                                                          \
  } while (0)

#define CHECK_EQ(a, b) CHECK((a) == (b))
#define CHECK_NE(a, b) CHECK((a) != (b))

#define RUN_TEST(test)                                                         \
  do {                                                                         \
    printf("Running %s...\n", #test);                                          \
    test();                                                                    \
  } while (0)

#endif // !TEST_H
