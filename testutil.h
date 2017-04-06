#ifndef _TESTUTIL_H
#define _TESTUTIL_H

#define check(assertion, msg) \
    if (!(assertion)) { \
      fprintf(stderr, "assertion failed: %s\n", msg); \
      return 0; \
    }

#define checkint(expected, actual, name) \
    check(expected == actual, name " should be " #expected)

#define checkstr(expected, actual, name) \
    check(!strcmp(actual, expected), name " should be '" expected "'")

#define test(NAME) \
    { \
    fprintf(stderr, "here %s\n", #NAME); \
      int result = NAME (); \
      if (!result) { \
          fprintf(stderr, "test failed: %s\n", #NAME); \
          return 0; \
      } \
    }

#define succeed() return 1

#endif

