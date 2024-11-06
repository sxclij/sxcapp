#include <sys/resource.h>
#include <unistd.h>

#define sxcapp_stacksize (128 * 1024 * 1024)
#define sxcscript_path "data.txt"
#define sxcscript_mem_capacity (16 * 1024 * 1024)
#define sxcscript_compile_capacity (16 * 1024 * 1024)

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
void sxcscript_init(union sxcscript_mem* mem) {
    char src[sxcscript_compile_capacity];
    struct sxcscript_token token[sxcscript_compile_capacity];
    struct sxcscript_node node[sxcscript_compile_capacity];
    struct sxcscript_label label[sxcscript_compile_capacity];
    union sxcscript_mem* global_begin;
    union sxcscript_mem* inst_begin;
    union sxcscript_mem* data_begin;
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