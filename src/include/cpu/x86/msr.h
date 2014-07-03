#ifndef CPU_X86_MSR_H
#define CPU_X86_MSR_H

#if defined(__ROMCC__)

typedef __builtin_msr_t msr_t;

static msr_t rdmsr(unsigned long index)
{
	return __builtin_rdmsr(index);
}

static void wrmsr(unsigned long index, msr_t msr)
{
	__builtin_wrmsr(index, msr.lo, msr.hi);
}

#else

typedef struct msr_struct
{
	unsigned lo;
	unsigned hi;
} msr_t;

typedef struct msrinit_struct
{
        unsigned index;
        msr_t msr;
} msrinit_t;

/* The following functions require the always_inline due to AMD
 * function STOP_CAR_AND_CPU that disables cache as
 * ram, the cache as ram stack can no longer be used. Called
 * functions must be inlined to avoid stack usage. Also, the
 * compiler must keep local variables register based and not
 * allocated them from the stack. With gcc 4.5.0, some functions
 * declared as inline are not being inlined. This patch forces
 * these functions to always be inlined by adding the qualifier
 * __attribute__((always_inline)) to their declaration.
 * HTKIM
 * __attribute__((always_inline)) 키워드를 사용함으로써 최적화
 * 레벨에 상관없이 항상 함수를 인라인한다.
 * __asm__ 어셈을 사용한다는 키원드
 * __volatile__ 최적화 옵션을 사용하지 않고 그대로 컴파일.
 */

/* HTKIM
 * __asm__(asm statements : outputs : inputs : registers-modified);
 * asm statements - 뉴라인으로 구분되는 AT&T 형식.
 * output - ','로 구분되고 괄호안의 이름이 따르는 constraints.
 * input - ','로 구분되고 괄호안의 이름이 따르는 constraints.
 * reg modify - ','로 구분되는 이름.
 * EX)
 * int i=0;
 * __asm__ ("
 *  pushl %%eax   //입력,출력, reg modify 필드 중 어느것이라도 사용된다면
 *                // '%' 하나가 아니라 '%%'를 사용한다.
 *  movl %0 %%eax //입력이 하나:%0 입력이 둘:%0, %1
 *  popl %%eax "
 *  :             //출력 필드를 사용하면 앞에 '='을 쓴다. ex) "=g" (k)
 *  : "g" (i)
 * );
 *
 * 입력 필드만 사용하므로 출력 및 마지막 필드는 그냥 두어야 함.
 * constraints는 컴파일러에게 값을 넘겨주어 처리하도록 하는 명령어.
 * 일반적으로 입력 변수로 "g" 를 사용하며, "g"는 i 의 값을 어디로 불러올지를
 * 컴파일러가 결정 하도록 한다.
 * 범용적으로 사용되는 것으로 "r" 이 있는데, 이것은 현재 사용가능한 아무
 * 레지스터로 로딩하는 것을 의미한다.
 * "a" (ax/eax), "b" (bx/ebx), "c" (cx/ecx), "d" (dx/edx), "D" (di/edi),
 * "S" (si/esi), etc.
 */
static inline __attribute__((always_inline)) msr_t rdmsr(unsigned index)
{
	msr_t result;
	__asm__ __volatile__ (
		"rdmsr"
		: "=a" (result.lo), "=d" (result.hi)
		: "c" (index)
		);
	return result;
}

static inline __attribute__((always_inline)) void wrmsr(unsigned index, msr_t msr)
{
	__asm__ __volatile__ (
		"wrmsr"
		: /* No outputs */
		: "c" (index), "a" (msr.lo), "d" (msr.hi)
		);
}

#endif /* __ROMCC__ */

#endif /* CPU_X86_MSR_H */
