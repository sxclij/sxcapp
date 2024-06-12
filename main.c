#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define file_capacity 65536
#define hashtable_capacity 65536

void file_read(char* dst, const char* src) {
    FILE* fp = fopen("data.txt", "r");
    uint32_t n = fread(dst, 1, file_capacity, fp);
    dst[n] = '\0';
    fclose(fp);
}

union uni64 {
    uint64_t u64;
    uint32_t u32[2];
    char* s;
    void (*fn)(union uni64);
};
struct token {
    uint32_t start;
    uint32_t size;
};

struct hashtable hashtable;
struct hashtable_table {
    struct token key;
    union uni64 value;
};
struct hashtable {
    struct hashtable_table table[hashtable_capacity];
    char data[hashtable_capacity];
    uint32_t data_size;
};
uint32_t hashtable_xorshift(uint32_t x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
}
union uni64* hashtable_provide(const char* src_data, uint32_t src_size) {
    uint32_t hash = 0;
    for (uint32_t i = 0; i < src_size; i++) {
        hash += src_data[i];
        hash = hashtable_xorshift(hash);
    }
    while (1) {
        hash %= hashtable_capacity;
        struct hashtable_table* x = &hashtable.table[hash];
        if (x->key.size == 0) {
            x->key = (struct token){.start = hashtable.data_size, .size = src_size};
            memcpy(&hashtable.data[hashtable.data_size], src_data, src_size);
            hashtable.data_size += src_size;
            return &x->value;
        }
        if (src_size == x->key.size) {
            if (memcmp(src_data, &hashtable.data[x->key.start], src_size) == 0) {
                return &x->value;
            }
        }
        hash = hashtable_xorshift(hash);
    }
}
union uni64* hashtable_provide_str(const char* src) {
    return hashtable_provide(src, strlen(src));
}



int main() {
    static char text_data[file_capacity];

    file_read(text_data, "data.txt");

    

    return 0;
}