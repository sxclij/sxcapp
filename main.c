#include <unistd.h>

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