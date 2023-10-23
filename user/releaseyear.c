#include "../kernel/types.h"
#include "user.h"

int main(void) {
    fprintf(1, "Note: Unix V6 was realased in year %d\n", getyear());
    return 0;
}