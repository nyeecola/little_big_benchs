#pragma once

#include <stdlib.h>
#include <string.h>

#define DEFAULT_VEC_CAPACITY 4

#define DECLARE_VEC(type) \
    struct vector_ ## type { \
        type *data; \
        size_t size; \
        size_t capacity; \
    }; \

#define VEC_INIT(name, type) \
    vector_ ## type name; \
    name.data = (type *) calloc(DEFAULT_VEC_CAPACITY, sizeof(type)); \
    name.size = 0; \
    name.capacity = DEFAULT_VEC_CAPACITY;

#define VEC_INIT_N(name, num, type, ...) \
    vector_ ## type name; \
    name.data = (type *) malloc(MAX(DEFAULT_VEC_CAPACITY, num) * sizeof(type)); \
    { \
        type _temp_vector_[] = { __VA_ARGS__ }; \
        memcpy(name.data, _temp_vector_, num * sizeof(type)); \
    } \
    name.size = num; \
    name.capacity = MAX(DEFAULT_VEC_CAPACITY, num);

// Note: we currently kill the program when this fails, we could probably return an error instead
#define VEC_APPEND(vec, elem) \
    if (vec.size + 1 > vec.capacity) { \
        vec.data = (__typeof(*vec.data) *) realloc(vec.data, (vec.capacity * 2) * sizeof(*vec.data)); \
        if (vec.data) { \
            vec.capacity *= 2; \
        } else { \
            exit(-1); \
        } \
    } \
    vec.data[vec.size++] = elem; \

#define VEC_DELETE(vec, pos) \
    for (int _i_ = pos; _i_ < vec.size - 1; _i_++) { \
        vec.data[_i_] = vec.data[_i_]; \
    } \
    --vec.size;

#define VEC_I(vec, pos) vec.data[pos]

#define VEC_DESTROY(vec) \
    free(vec.data); \
    vec.data = NULL; \
    vec.size = 0; \
    vec.capacity = 0;

DECLARE_VEC(int);

