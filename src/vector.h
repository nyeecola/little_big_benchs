#pragma once

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define DEFAULT_VEC_CAPACITY 4
#define INLINE_CAPACITY_BYTES 40 // chosen so that the total struct size is not over 64

#define DECLARE_VEC(type) \
    struct vector_ ## type { \
        type *data; \
        size_t size; \
        size_t capacity; \
        type inline_data[INLINE_CAPACITY_BYTES/sizeof(type)]; \
    }; \

// TODO: check allocation error
#define VEC_INIT(name, type) \
    vector_ ## type name; \
    assert(sizeof(name.inline_data) <= INLINE_CAPACITY_BYTES); \
    if (sizeof(type) <= INLINE_CAPACITY_BYTES) { \
        name.data = &name.inline_data[0]; \
        name.capacity = INLINE_CAPACITY_BYTES / sizeof(type); \
    } else { \
        name.data = (type *) calloc(DEFAULT_VEC_CAPACITY, sizeof(type)); \
        name.capacity = DEFAULT_VEC_CAPACITY; \
    } \
    name.size = 0; \
    assert(name.capacity > 0);

// TODO: check allocation error
#define VEC_INIT_N(name, num, type, ...) \
    vector_ ## type name; \
    assert(sizeof(name.inline_data) <= INLINE_CAPACITY_BYTES); \
    if (num * sizeof(type) <= INLINE_CAPACITY_BYTES) { \
        name.data = &name.inline_data[0]; \
        name.capacity = INLINE_CAPACITY_BYTES / sizeof(type); \
    } else { \
        name.data = (type *) malloc(MAX(DEFAULT_VEC_CAPACITY, num) * sizeof(type)); \
        name.capacity = MAX(DEFAULT_VEC_CAPACITY, num); \
    } \
    { \
        type _temp_vector_[] = { __VA_ARGS__ }; \
        memcpy(name.data, _temp_vector_, num * sizeof(type)); \
    } \
    name.size = num; \
    assert(name.capacity > 0);

// TODO: investigate why this became so much more expensive (check the ASM code)
// Note: we currently kill the program when this fails, we could probably return an error instead
#define VEC_APPEND(vec, elem) \
    if (unlikely(vec.size + 1 > vec.capacity)) { \
        size_t new_capacity = MAX(vec.capacity * 2, DEFAULT_VEC_CAPACITY); \
        if (unlikely((char*)vec.data == ((char*)&vec) + offsetof(__typeof(vec), inline_data))) { \
            vec.data = (__typeof(*vec.data) *) malloc(new_capacity * sizeof(*vec.data)); \
        } else { \
            vec.data = (__typeof(*vec.data) *) realloc(vec.data, new_capacity * sizeof(*vec.data)); \
        } \
        if (likely(vec.data != NULL)) { \
            vec.capacity = new_capacity; \
        } else { \
            exit(-1); \
        } \
    } \
    vec.data[vec.size++] = elem; \

#define VEC_DELETE(vec, pos) \
    for (int _i_ = pos; _i_ < vec.size - 1; _i_++) { \
        vec.data[_i_] = vec.data[_i_+1]; \
    } \
    --vec.size;

#define VEC_I(vec, pos) vec.data[pos]

#define VEC_DESTROY(vec) \
    if ((char*)vec.data != ((char*)&vec) + offsetof(__typeof(vec), inline_data)) \
        free(vec.data); \
    vec.data = NULL; \
    vec.size = 0; \
    vec.capacity = 0;

