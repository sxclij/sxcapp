#include <unistd.h>

enum bool {
    false = 0,
    true = 1,
};


void global_update() {
}
void global_init() {
}
int main() {
    global_init();
    while (1) {
        global_update();
    }
}