#ifndef CPU_X86_TSC_H
#define CPU_X86_TSC_H

#if CONFIG_TSC_SYNC_MFENCE
#define TSC_SYNC "mfence\n"
#elif CONFIG_TSC_SYNC_LFENCE
#define TSC_SYNC "lfence\n"
#else
#define TSC_SYNC
#endif

struct tsc_struct {
	unsigned lo;
	unsigned hi;
};
typedef struct tsc_struct tsc_t;

/* HTKIM
 * 프로세스의 이벤트 및 모니터를 위해 time-stamp counter mechanism을 정의
 * TSC flag - CPUID.1:EDX.TSC[bit 4] = 1 -> 사용
 * RDTSC instruction - time-stamp counter을 읽기 위해 사용
 * TSD flag - time-stamp counter을 enable/disable 하기 위한 control reg
 *			 CR4.TSD[bit 2] =1
 */
static inline tsc_t rdtsc(void)
{
	tsc_t res;
	asm volatile (
		TSC_SYNC
		"rdtsc"
		: "=a" (res.lo), "=d"(res.hi) /* outputs */
	);
	return res;
}

#if !defined(__ROMCC__)
/* Too many registers for ROMCC */
static inline unsigned long long rdtscll(void)
{
	unsigned long long val;
	asm volatile (
		TSC_SYNC
		"rdtsc"
		: "=A" (val)
	);
	return val;
}
#endif

#if CONFIG_TSC_CONSTANT_RATE
unsigned long tsc_freq_mhz(void);
#endif

#endif /* CPU_X86_TSC_H */
