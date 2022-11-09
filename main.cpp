// 1.2.1: Example of SSE2 intrinsics
#pragma intrinsic(__rdtsc)
// for int32_t
#include <stdint.h>
// for SSE2 intrinsics
#include <emmintrin.h>

#include <iostream>
#include <intrin.h>
using namespace std;

#include <omp.h>

unsigned long long pft_start;
unsigned long long pft_finish;
unsigned long long pft_start1;
unsigned long long pft_finish1;
double time;
double time1;

#define SPEED_START_CONSOLE pft_start = __rdtsc();
#define SPEED_FINISH_CONSOLE pft_finish = __rdtsc();

#define SPEED_START_CONSOLE1 pft_start1 = __rdtsc();
#define SPEED_FINISH_CONSOLE1 pft_finish1 = __rdtsc();

void usual()
{

    double array_a[4] = { 0.5,2.5,1.5,2.5 };
    double array_b[4] = { 8.5,5.5,0.5,6.5 };
    double array_c[4];

    double start = omp_get_wtime( );
    SPEED_START_CONSOLE1

    for (int i = 0; i < 40000; i++) {
        array_c[i%4] = array_a[i%4] + array_b[i%4];
    }
    SPEED_FINISH_CONSOLE1
    double end = omp_get_wtime( );
    time1 = end-start;
}


void vec()
{
    double_t array_a[4] = { 0.5,2.5,1.5,2.5 }; 
    double_t array_b[4] = { 8.5,5.5,0.5,6.5 };
    double_t array_c[4];

    __m256d a, b, c;

    double start = omp_get_wtime( );
    SPEED_START_CONSOLE
    for (int i = 0; i < 10000; i++) {
        a = _mm256_set_pd(array_a[0],array_a[1],array_a[2],array_a[3]);
        b = _mm256_set_pd(array_b[0],array_b[1],array_b[2],array_b[3]);
        c = _mm256_add_pd(a, b);
        _mm256_storeu_pd(array_c, c);
    }
    SPEED_FINISH_CONSOLE
    double end = omp_get_wtime( );
    time = end-start;

}

int main() {
    vec();
    usual();
    uint64_t result = pft_finish - pft_start;
    uint64_t result1 = pft_finish1 - pft_start1;

    double quotient = result/time;
    double quotient1 = result1/time1;

    printf("vectorisation  : Cycle count = %llu | Time execution : %5.8f |  Cycle / Second : %5.8f\n",result, time, quotient);

    printf("simple addition: Cycle count = %llu | Time execution : %5.8f |  Cycle / Second : %5.8f\n",result1, time1, quotient1);

    return 0;
}
