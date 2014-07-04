#include <cpu/x86/lapic.h>
#include <cpu/x86/msr.h>

#if CONFIG_SMP
int boot_cpu(void)
{
	int bsp;
	msr_t msr; /* msr(Model Specific Registers) */
	msr = rdmsr(0x1b);
	/* HTKIM
	 * msr의 index로 1b가 들어가며, 1b는 addr reg로 Local APIC status
	 * and Location 나타낸다.
	 */
	bsp = !!(msr.lo & (1 << 8)); /* ToDo !!의 의미?, mst_t구조체 값이
							 	  * 어디서 쓰여지고 읽혀 지는지 확인 필요
								  * bsp = 1?
								  */
	return bsp;
}
#else
#define boot_cpu(x) 1
#endif

