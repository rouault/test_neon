#include <arm_neon.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline void foo(char* yar, uint32x4_t vconstants)
{
    uint32x4_t y = vld1q_u32(yar);
    uint32x4_t x = vmulq_u32 (y, vconstants);
    vst1q_u32(yar, x);
}

int main(int argc, char* argv[])
{
    uint32_t constants[] = {atoi(argv[2]),atoi(argv[2]),atoi(argv[2]),atoi(argv[2])};
    uint32x4_t vconstants = vld1q_u32(constants);
    char content[16] = {1,0,0,0,2,0,0,0,3,0,0,0,4,0,0,0};
    char yar[100 * 16+15+8];
    char* ptr = atoi(argv[1]) + (yar + (16 - ((uintptr_t)yar % 16)) % 16);
    for( int j = 0; j < 100; j++ )
        memcpy(ptr + 16 * j, content, 16);
    for( int i = 0; i < 10000000; i++)
    {
        for( int j = 0; j < 100; j++ )
        {
            foo(ptr + j * 16, vconstants);
        }
    }
    for( int j = 1; j < 100; j++ )
    {
        ((uint32_t*)ptr)[0] += ((uint32_t*)ptr)[j * 4];
        ((uint32_t*)ptr)[1] += ((uint32_t*)ptr)[j * 4 + 1];
    }
    printf("%d %d\n", ((uint32_t*)ptr)[0], ((uint32_t*)ptr)[1]);
    return 0;
}
