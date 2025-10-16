#pragma once

typedef enum { OK = 0, ERROR } status_t;

typedef struct {
    const char *msg;
    status_t error;
} untyped_error_t;

#define checked_t(type) checked_##type##_t

#define checked(type)                                                          \
    typedef union {                                                            \
        const char *err;                                                       \
        type val;                                                              \
    } checked_union_##type##_t;                                                \
                                                                               \
    typedef struct {                                                           \
        status_t error;                                                        \
        checked_union_##type##_t out;                                          \
    } checked_##type##_t;

#define error_msg(type, message)                                               \
    (checked_##type##_t) {                                                     \
        .error = ERROR, .out = {.err = message }                               \
    }

#define error_empty(type)                                                      \
    (checked_##type##_t) { .error = ERROR, .out = {.err = ""} }

#define ok(type, value)                                                        \
    (checked_##type##_t) {                                                     \
        .error = OK, .out = {.val = value }                                    \
    }
