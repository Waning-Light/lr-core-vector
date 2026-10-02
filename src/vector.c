/* vector.c —— 你要实现的地方 */

#include"vector.h"
#include<stdlib.h>
#include<string.h>

int vector_init(vector *v, size_t capacity) {
    if (capacity == 0) {
        v->data = NULL;
        v->end = NULL;
        v->cap = NULL;
        return 0;
    }
    
    if(capacity > SIZE_MAX / sizeof(int) ) {
        v->data = NULL;
        v->end = NULL;
        v->cap = NULL;
        return -1;
    }

    int *new_data = malloc(capacity*sizeof(int));
    if (new_data == NULL) {
        v->data = NULL;
        v->end = NULL;
        v->cap = NULL;
        return -1;
    }
    v->data = new_data;
    v->end = v->data;
    v->cap = v->data + capacity;
    return 0;
}

void vector_destroy(vector *v) {
    if (v->data != NULL) {
        free(v->data);
    }
    v->data = NULL;
    v->end = NULL;
    v->cap = NULL;
}

size_t size(const vector *v) {
    if (v->data == NULL) {
        return 0;
    }
    return (size_t)(v->end - v->data);
}

size_t capacity(const vector *v) {
    if (v->data == NULL) {
        return 0;
    }
    return (size_t)(v->cap - v->data);
}


int empty(const vector *v) {
    return size(v) == 0 ? 1 : 0;
}

int get(const vector *v, size_t index, int *out) {
    if (index >= size(v)) {
        return -1;
    }
    *out = v->data[index];
    return 0;
}

int set(vector *v, size_t index, int value) {
    if (index >= size(v)) {
        return -1;
    }
    v->data[index] = value;
    return 0;
}

int front(const vector *v, int *out) {
    if (empty(v)) {
        return -1;
    }
    *out = v->data[0];
    return 0;
}

int back(const vector *v, int *out) {
    if (empty(v)) {
        return -1;
    }
    *out = *(v->end - 1);
    return 0;
}

int push_back(vector *v, int value) {
    if (v->end==v->cap) {
        size_t new_capacity = capacity(v) == 0 ? 1 : capacity(v) * 2;
        if (reserve(v, new_capacity) != 0) {
            return -1;
        }
    }
    *v->end = value;
    v->end++;
    return 0;
}

int pop_back(vector *v, int *out) {
    if (empty(v)) {
        return -1;
    }
    v->end--;
    if (out != NULL) {
        *out = *(v->end);
    }
    return 0;
}

int reserve(vector *v, size_t new_capacity) {
    if (new_capacity <= capacity(v)) {
        return 0;
    }
    if (new_capacity > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    size_t old_size = size(v);
    int *new_data = (int *) malloc(new_capacity * sizeof(int));
    if (new_data == NULL) {
        return -1;
    }
    if (v->data != NULL) {
        memcpy(new_data, v->data, old_size * sizeof(int));
        free(v->data);
    }
    v->data = new_data;
    v->end = v->data + old_size;
    v->cap = v->data + new_capacity;
    return 0;
}

int shrink_to_fit(vector *v) {
    size_t current_size = size(v);
    if (current_size == 0) {
        free(v->data);
        v->data = NULL;
        v->end = NULL;
        v->cap = NULL;
        return 0;
    }
    if (current_size == capacity(v)) {
        return 0;
    }
    int *new_data = (int *) malloc(current_size * sizeof(int));
    if (new_data == NULL) {
        return -1;
    }
    memcpy(new_data, v->data, current_size * sizeof(int));
    v->data = new_data;
    v->end = v->data + current_size;
    v->cap = v->data + current_size;
    return 0;
}

void clear(vector *v) {
    v->end = v->data;
}
