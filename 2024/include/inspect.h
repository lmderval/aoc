#ifndef INSPECT_H
#define INSPECT_H

#define STRINGIFY(X) #X

#define INSPECTOR(TYPE, X) function inspect(X: TYPE)

#ifdef DEBUG
  #define INSPECT(X)                                                           \
    (                                                                          \
      print(STRINGIFY(X:\t));                                                  \
      inspect(X);                                                              \
      print("\n")                                                              \
    )
#else
  #define INSPECT(X)                                                           \
    ()
#endif

#endif
