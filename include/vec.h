#pragma once
#include <assert.h>
#include <error.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define VEC_INITIAL_SIZE 32

#define vec(type)                                                              \
    typedef struct {                                                           \
        type *val;                                                             \
        size_t size;                                                           \
        size_t len;                                                            \
        bool free;                                                             \
    } vec_##type##_t;

#define v_append(type) vec_##type##_append
#define v_get(type) vec_##type##_get
#define vec_t(type) vec_##type##_t

#define new_vec(type)                                                          \
    (vec_##type##_t){                                                          \
        .size = 32,                                                            \
        .len = 0,                                                              \
        .val = calloc(32, sizeof(type)),                                       \
        .free = false,                                                         \
    };

#define free_vec(vec)                                                          \
    free(vec.val);                                                             \
    vec.size = 0;                                                              \
    vec.len = 0;                                                               \
    vec.free = true;

#define d_vector_append(type)                                                  \
    untyped_error_t vec_##type##_append(vec_##type##_t *vector, type value) {  \
        if (vector->free == true) {                                            \
            return (untyped_error_t){.error = ERROR,                           \
                                     .msg = "ERROR: use after free!"};         \
        }                                                                      \
        vector->len++;                                                         \
        if (vector->len == vector->size) {                                     \
            vector->size *= 2;                                                 \
            vector->val =                                                      \
                realloc(vector->val, vector->size * sizeof(*vector->val));     \
        }                                                                      \
        vector->val[vector->len - 1] = value;                                  \
        return (untyped_error_t){.error = OK, .msg = ""};                      \
    }

#define d_vector_get(type)                                                     \
    checked_##type##_t vec_##type##_get(vec_##type##_t vector, size_t index) { \
        if (vector.free == true) {                                             \
            return error_msg(type, "ERROR: attempted use after free!");        \
        }                                                                      \
        if (vector.len <= index) {                                             \
            return error_msg(type, "ERROR: index out of bound!");              \
        }                                                                      \
        return ok(type, vector.val[index]);                                    \
    }
