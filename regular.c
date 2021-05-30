#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

inline void foo(char* yar, uint32_t* constants)
{
    ((uint32_t*)yar)[0] *= constants[0];
    ((uint32_t*)yar)[1] *= constants[1];
    ((uint32_t*)yar)[2] *= constants[2];
    ((uint32_t*)yar)[3] *= constants[3];
}

int main(int argc, char* argv[])
{
    uint32_t constants[] = {atoi(argv[2]),atoi(argv[2]),atoi(argv[2]),atoi(argv[2])};
    char content[16] = {1,0,0,0,2,0,0,0,3,0,0,0,4,0,0,0};
    char yar[100 * 16+15+8];
    char* ptr = atoi(argv[1]) + (yar + (16 - ((uintptr_t)yar % 16)) % 16);
    for( int j = 0; j < 100; j++ )
        memcpy(ptr + 16 * j, content, 16);
    for( int i = 0; i < 10000000; i++)
    {
        for( int j = 0; j < 100; j++ )
        {
            foo(ptr + j * 16, constants);
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
