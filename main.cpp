#include "Server0.h"

int main(void)
{
    start(8099, "127.0.0.1", uv_default_loop());
    return 0;
}
