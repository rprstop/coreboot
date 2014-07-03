#include <cpu/x86/lapic.h>
#include <cpu/x86/msr.h>

#if CONFIG_SMP
int boot_cpu(void)
{
	int bsp;
	msr_t msr; /* msr(Model Specific Registers) */
	msr = rdmsr(0x1b); /* msr.lo is 0x1b ? */
	bsp = !!(msr.lo & (1 << 8)); /* ToDo !!의 의미?, bsp = 0? */
	return bsp;
}
#else
#define boot_cpu(x) 1
#endif

