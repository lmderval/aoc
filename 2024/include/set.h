#ifndef SET_H
#define SET_H

#ifndef BUCKET_SIZE
#define BUCKET_SIZE 64
#endif

#define _MOD(VALUE, MOD) VALUE - VALUE / MOD * MOD
#define _INC(VAR) VAR := VAR + 1

#define LIST(TYPE) TYPE ## _list
#define BUCKET(TYPE) TYPE ## _bucket
#define SET(TYPE) TYPE ## _set

#define DEFINE_SET(TYPE)                                                       \
  type LIST(TYPE) = {                                                          \
    value: TYPE,                                                               \
    next: LIST(TYPE)                                                           \
  }                                                                            \
  type BUCKET(TYPE) = array of LIST(TYPE)                                      \
  type SET(TYPE) = {                                                           \
    size: int,                                                                 \
    bucket: BUCKET(TYPE)                                                       \
  }                                                                            \
  function create_list(value: TYPE) : LIST(TYPE) =                             \
    LIST(TYPE) {                                                               \
      value = value,                                                           \
      next = nil                                                               \
    }

#define HASH hash

#define EQUAL equal

#define DEFINE_HASH(TYPE, VALUE) function HASH(VALUE: TYPE) : int
#define DEFINE_EQUAL(TYPE, L, R) function EQUAL(L: TYPE, R: TYPE) : int

#define NOT_EQUAL(L, R) EQUAL(L, R) = 0

#define CREATE_SET(TYPE)                                                       \
  SET(TYPE) {                                                                  \
    size = 0,                                                                  \
    bucket = BUCKET(TYPE) [BUCKET_SIZE] of nil                                 \
  }                                                                            \

#define CREATE_LIST(VALUE) create_list(value)

#define SIZE_SET(SET) SET.size

#define APPEND_SET(SET, VALUE)                                                 \
  let                                                                          \
    var set := SET                                                             \
    var value := VALUE                                                         \
    var hash := HASH(value)                                                    \
    var idx := _MOD(hash, BUCKET_SIZE)                                         \
    var node := set.bucket[idx]                                                \
  in                                                                           \
    if set.bucket[idx] = nil                                                   \
      then (                                                                   \
        set.bucket[idx] := CREATE_LIST(value);                                 \
        _INC(set.size)                                                         \
      )                                                                        \
      else (                                                                   \
        while node.next <> nil do (                                            \
          if EQUAL(node.value, value)                                          \
            then break;                                                        \
          node := node.next                                                    \
        );                                                                     \
        if NOT_EQUAL(node.value, value)                                        \
          then (                                                               \
            node.next := CREATE_LIST(value);                                   \
            _INC(set.size)                                                     \
          )                                                                    \
      )                                                                        \
  end
  
#endif
