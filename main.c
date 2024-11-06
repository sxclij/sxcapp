#include <fcntl.h>
#include <sys/resource.h>
#include <unistd.h>

#define sxcapp_stacksize (128 * 1024 * 1024)
#define sxcscript_path "data.txt"
#define sxcscript_mem_capacity (16 * 1024 * 1024)
#define sxcscript_compile_capacity (2 * 1024)

enum bool {
    false = 0,
    true = 1,
};
enum sxcscript_kind {
    sxcscript_kind_null,
    sxcscript_kind_nop,
    sxcscript_kind_push,
    sxcscript_kind_label,
    sxcscript_kind_label_fnend,
    sxcscript_kind_call,
    sxcscript_kind_return,
    sxcscript_kind_jmp,
    sxcscript_kind_jze,
    sxcscript_kind_const_get,
    sxcscript_kind_local_get,
    sxcscript_kind_local_set,
    sxcscript_kind_global_get,
    sxcscript_kind_global_set,
    sxcscript_kind_add,
    sxcscript_kind_sub,
    sxcscript_kind_mul,
    sxcscript_kind_div,
    sxcscript_kind_mod,
    sxcscript_kind_not,
    sxcscript_kind_and,
    sxcscript_kind_eq,
    sxcscript_kind_lt,
    sxcscript_kind_open,
    sxcscript_kind_close,
    sxcscript_kind_read,
    sxcscript_kind_write,
    sxcscript_kind_usleep,
};
enum sxcscript_global {
    sxcscript_global_ip = 0,
    sxcscript_global_sp = 1,
    sxcscript_global_bp = 2,
};
struct sxcscript_token {
    const char* data;
    int size;
};
struct sxcscript_node {
    enum sxcscript_kind kind;
    struct sxcscript_token* token;
    int val;
};
struct sxcscript_label {
    struct sxcscript_token* token;
    int arg_size;
    int inst_i;
};
union sxcscript_mem {
    enum sxcscript_kind kind;
    int val;
};

void sxcscript_run(union sxcscript_mem* mem) {
}
void sxcscript_readfile(char* dst) {
    int fd = open(sxcscript_path, O_RDONLY);
    int n = read(fd, dst, sxcscript_compile_capacity);
    dst[n] = '\0';
    close(fd);
}
void sxcscript_tokenize(char* src, struct sxcscript_token* token) {
    struct sxcscript_token* token_itr = token;
    struct sxcscript_token token_this = {.data = src, .size = 0};
    for (char* itr = src; *itr != '\0'; itr++) {
        if (*itr == ' ' || *itr == '\n') {
            if (token_this.size > 0) {
                *(token_itr++) = token_this;
            }
            token_this = (struct sxcscript_token){.data = itr + 1, .size = 0};
        } else if (*itr == ',' || *itr == '(' || *itr == ')') {
            if (token_this.size > 0) {
                *(token_itr++) = token_this;
            }
            *(token_itr++) = (struct sxcscript_token){.data = itr, .size = 1};
            token_this = (struct sxcscript_token){.data = itr + 1, .size = 0};
        } else {
            token_this.size++;
        }
    }
}
void sxcscript_parse(struct sxcscript_token* token, struct sxcscript_node* node, struct sxcscript_label* label) {
}
void sxcscript_link(struct sxcscript_node* node, struct sxcscript_label* label, union sxcscript_mem* mem) {
}
void sxcscript_init(union sxcscript_mem* mem) {
    char src[sxcscript_compile_capacity];
    struct sxcscript_token token[sxcscript_compile_capacity / sizeof(struct sxcscript_token)];
    struct sxcscript_node node[sxcscript_compile_capacity / sizeof(struct sxcscript_node)];
    struct sxcscript_label label[sxcscript_compile_capacity / sizeof(struct sxcscript_label)];
    union sxcscript_mem* global_begin;
    union sxcscript_mem* inst_begin;
    union sxcscript_mem* data_begin;
    sxcscript_readfile(src);
    sxcscript_tokenize(src, token);
    sxcscript_parse(token, node, label);
    sxcscript_link(node, label, mem);
}
void sxcscript() {
    static union sxcscript_mem mem[sxcscript_mem_capacity];
    sxcscript_init(mem);
    sxcscript_run(mem);
}
void init() {
    struct rlimit rlim = (struct rlimit){.rlim_cur = sxcapp_stacksize, .rlim_max = sxcapp_stacksize};
    setrlimit(RLIMIT_STACK, &rlim);
}
int main() {
    init();
    sxcscript();
}