#include <stdio.h>
#include <stdint.h>

#define file_capacity 65536

void file_read(char* dst, const char* src) {
    FILE* fp = fopen("data.txt", "r");
    uint32_t n = fread(dst, 1, file_capacity, fp);
    dst[n] = '\0';
    fclose(fp);
}

int main() {
    static char text_data[file_capacity];

    file_read(text_data, "data.txt");

    printf("%s\n", text_data);

    return 0;
}