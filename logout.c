#include "fonction.h"
#include <stdio.h>

int main(void) {
        remove("/tmp/auth");
        redirect("http://localhost");
        return 0;
}