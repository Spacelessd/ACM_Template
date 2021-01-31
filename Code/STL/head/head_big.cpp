//
//	#define DEBUG_MEM_FORCE_SSE2	//force using SSE2 (not SSSE3)
//	#define DEBUG_MEM_FORCE_NO_PREF	//force using copy_no_prefetch loop
//	#define DEBUG_MEM_FORCE_PREF	//force using copy_prefetch loop
//	#define DEBUG_MEM_FORCE_NT		//force using copy_nt loop
	#define DEBUG_MEM_FORCE_PTR		//force using memcpy_ptr() in memcpy_sse() (never call memcpy())
//	#define DEBUG_MEM_CHECK			//check memcpy_sse() correctness
	#define ONLINE_JUDGE

	#define USE_MEMCPY_SSE
//	#define USE_MEMCPY_STD
	#if !defined(USE_MEMCPY_SSE)
		#undef USE_MEMCPY_STD
		#define USE_MEMCPY_STD
	#endif
/*//.101556DN
D:\Sed\SelectGo\mem_test_30_.cpp
*/
//	#define JMP_TAB_SIZE_32
	// Constants to control run_memcpy().
	#define MEM_REPEAT_N		40000	//run "blocks" of memcpy_sse() calls MEM_REPEAT_N times to get min/max time
	#define MEM_SIZE			64	//size of memory block to copy by memcpy_sse()/memcpy()
	#define MEM_SIZE_N			64	//use (MEM_SIZE <= size < MEM_SIZE + MEM_SIZE_N) with MEM_SIZE_STEP
//	#define MEM_SIZE_STEP		2	//step inside MEM_SIZE_N
	#define MEM_OFFS_2			0	//dest offset from allocated memory (4096-byte aligned)
	#define MEM_OFFS_N			16	//use (MEM_OFFS_2 <= offset < MEM_OFFS_2 + MEM_OFFS_N) with MEM_OFFS_STEP
//	#define MEM_OFFS_STEP		16	//
	#define MEM_OFFS_1			256	//src offset from allocated memory (4096-byte aligned); used with size >= 64
//	#define MEM_CONST_SIZE			//call memcpy_sse()/memcpy() with MEM_SIZE (not with mem_size param of run_memcpy())
//	#define MEM_PRINT_ALL			//print results for all sizes and offsets

	// Constants to control run_memcpy_buf(). Define's of run_memcpy() are also used (not MEM_OFFS_2).
//	#define MEM_BUF							//call run_memcpy_buf()
	#define MEM_BUF_SIZE		(32 * 1024)	//size of src/dest buffers
	#define MEM_COPY_N			2000		//number of random memcpy_x() calls

	#if !defined(MEM_REPEAT_N)
		#define MEM_REPEAT_N	10
	#endif
	#if !defined(MEM_SIZE)
		#define MEM_SIZE		8
	#endif
	#if !defined(MEM_SIZE_N)
		#define MEM_SIZE_N		1
	#endif
	#if !defined(MEM_SIZE_STEP)
		#define MEM_SIZE_STEP	1
	#endif
	#if !defined(MEM_OFFS_2)
		#define MEM_OFFS_2		0
	#endif
	#if !defined(MEM_OFFS_N)
		#define MEM_OFFS_N		1
	#endif
	#if !defined(MEM_OFFS_STEP)
		#define MEM_OFFS_STEP	1
	#endif
	#if !defined(MEM_OFFS_1)
		#define MEM_OFFS_1		0
	#endif
	#ifdef MEM_CONST_SIZE
		#undef MEM_SIZE_N
		#define MEM_SIZE_N		1
		#undef MEM_SIZE_STEP
		#define MEM_SIZE_STEP	1
	#endif

#pragma warning(disable: 4035)	//no return value
#pragma warning(disable: 4068)	//unknown pragma
#pragma warning(disable: 4731)	//frame pointer register 'ebp' modified by inline assembly code
#pragma warning(disable: 4799)	//function 'xxx' has no EMMS instruction
#pragma warning(disable: 4102)	//unreferenced label
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

//******************************
void p(const char * format, ...)
//******************************
{
} //p

#ifdef _MSC_VER
	#define __VC				_MSC_VER
#else
	#define __VC				0
#endif

#ifdef __GNUC__
	#define __GC				(__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
	#define __GC				0
#endif

#if ((__VC && !defined(_M_X64) && !defined(_M_IA64)) || \
	(__GC && defined(__i386__) && !defined(__LP64__)))
	#define __VC_GC_x86			1
#else
	#define __VC_GC_x86			0
#endif

#if __VC
	typedef unsigned __int64	u64_t;
	typedef __int64				i64_t;
#else
	typedef unsigned long long	u64_t;
	typedef long long			i64_t;
#endif
typedef unsigned int			u32_t;
typedef int						i32_t;
typedef unsigned short			u16_t;
typedef short					i16_t;
typedef unsigned char			u08_t;
typedef char					i08_t;

#define	ARRAY_N(a)				(sizeof(a) / sizeof(a[0]))

#define SSE_NONE				0
#define SSE_MMX					0x01
#define SSE_MMX_EXT				0x02	//AMD extensions to MMX (includes prefetchnta, prefetcht0/1/2, movntq)
#define SSE_SSE					0x10
#define SSE_SSE2				0x20
#define SSE_SSE3				0x30
#define SSE_SSSE3				0x31
#define SSE_SSE41				0x41
#define SSE_SSE42				0x42
#define SSE_AVX					0x50

#if defined(__SSE3__)			//gc -msse3
	#define SSE_TYPE			SSE_SSE3
#elif defined(_M_X64) || defined(_M_IA64) || defined(__SSE2__)	//VC 64-bit or gc -msse2 option
	#define SSE_TYPE			SSE_SSE2
#elif defined(__SSE__)			//gc -msse
	#define SSE_TYPE			SSE_SSE
#elif defined(__MMX__)			//gc -mmmx
	// Note: __MMX__ is defined if eg __SSE__ is defined,
	// __3dNOW__ (gc -m3dnow) is not equivalent to SSE_MMX_EXT?
	#define SSE_TYPE			SSE_MMX
#else
	#define SSE_TYPE			SSE_NONE
#endif

#if __VC_GC_x86

#define MMX_PREFETCH_OFFS		288			//offset used by prefetch
#define MMX_PREFETCH_SIZE		400			//use copy_64_prefetch if (size >= *)
#define MMX_NT_SIZE				180000		//default for cpu_info.mmx_nt_size
#define MMX_LOAD_NT_SIZE		350000		//default for cpu_info.mmx_load_nt_size
#define MMX_BLOCK_SIZE			(8 * 1024)	//load src block of this size before each copy_64_nt loop
#define MMX_BLOCK_SIZE_64		(MMX_BLOCK_SIZE / 64)	//number of 64-byte chunks in src block

#define SSE_PREFETCH_OFFS		1024		//offset used by prefetch
#define SSE_PREFETCH_NT_OFFS	512			//offset used by prefetch
#define SSE_CACHE_SIZE			(2 * 1024 * 1024)	//default L2/L3 cache size
#define SSE_BLOCK_SIZE			(64 * 1024)	//"load" src block of this size before each copy_nt_u loop. 64K could be much faster than 32K.

#define MEM_VC_INLINE_SIZE		24	//memcpy(size) could be inlined with (size <= *)
#define MEM_GC_INLINE_SIZE		64
#define MEM_RET_TYPE			void

#if __VC
	#define MEM_CALL			__fastcall
	#define MEM_INLINE			__forceinline
	#define MEM_CONST(v)		0
	#define __ALIGN(x)			__declspec(align(x))
#elif __GC
	#define MEM_CALL			__attribute__((regparm(3)))
	#define MEM_INLINE			__attribute__((always_inline))
	#define MEM_CONST(v)		__builtin_constant_p(v)
	#define __ALIGN(x)			__attribute__((aligned(x)))
#endif

typedef MEM_RET_TYPE (MEM_CALL * memcpy_t)(void *dest, void *src, size_t size);

static MEM_RET_TYPE MEM_CALL memcpy_sse_x(void *dest, void *src, size_t size);

__inline MEM_RET_TYPE MEM_CALL memcpy_no_sse(void *dest, void *src, size_t size)
{	memcpy(dest, src, size);}

typedef struct
{
	u32_t	eax;
	u32_t	ebx;
	u32_t	ecx;
	u32_t	edx;
} cpuid_t;

typedef struct
{
	u08_t	code;
	u08_t	line;	//bytes
	u08_t	ways;
	u32_t	size;	//KBytes
} cache_info_t;

//__cpu_info
typedef __ALIGN(16) struct
{
	memcpy_t	memcpy_ptr;
#ifndef JMP_TAB_SIZE_32
	u32_t		copy_jmp_tab[16];
#else
	u32_t		copy_jmp_tab[32];
#endif

	// These arrays depend on sse2/ssse3/avx.
	u32_t		copy_no_prefetch[16];
	u32_t		copy_prefetch[16];
	u32_t		copy_nt[16];

	u08_t		sse_type;
	u08_t		z[3];
	u32_t		sse_prefetch_size;	//use copy_prefetch_* if (size >= *)
	u32_t		sse_nt_size;		//use copy_nt if (size >= *)
	u32_t		mmx_nt_size;		//use copy_64_nt (with movntq) if (size >= *)
	u32_t		mmx_load_nt_size;	//use load_block_nt (with copy_64_nt) if (size >= *)

	cache_info_t	cache[3];		//L1, L2, L3 levels
	u32_t		core_n;
	u32_t		prefetch_line;
	u32_t		clflush_line;		//size of a cache line flushed by the CLFLUSH instruction
} cpu_info_t;

static cpu_info_t get_cpu_info(u08_t sse_type);
static cpu_info_t	cpu_info = get_cpu_info(SSE_TYPE);

//__memcpy_sse__
//*******************************************************************
static MEM_INLINE void memcpy_sse(void *dest, void *src, size_t size)
//*******************************************************************
{
	// memcpy() is inlined if size is a little constant (known at compile time).
	// In this case cpu_info.memcpy_ptr() is slower than memcpy() with any size.
	// Otherwise (memcpy() is not inlined), cpu_info.memcpy_ptr() is faster  with any size.
	// In VC memcpy() could be inlined if (size < 20), but we cannot determine if size is a constant.
#if defined(DEBUG_MEM_FORCE_PTR)
	cpu_info.memcpy_ptr(dest, src, size);
#else
	if ((__VC && (size <= MEM_VC_INLINE_SIZE)) ||	//memcpy() could be inlined
		(__GC && MEM_CONST(size) && (size <= MEM_GC_INLINE_SIZE)))
		memcpy(dest, src, size);
	else
		cpu_info.memcpy_ptr(dest, src, size);
#endif
} //memcpy_sse

// get_cpu_info().
static cache_info_t Lx_cache[] =
{
	{0x0A, 32, 2, 8},
	{0x0C, 32, 4, 16},
	{0x0D, 64, 4, 16},
	{0x0E, 64, 6, 24},
	{0x10, 32, 4, 16},
	{0x2C, 64, 8, 32},
	{0x60, 64, 8, 16},
	{0x66, 64, 4, 8},
	{0x67, 64, 4, 16},
	{0x68, 64, 4, 32},
	{0},					//end of L1
	{0x21, 64, 8, 256},
	{0x39, 64, 4, 128},
	{0x3A, 64, 6, 192},
	{0x3B, 64, 2, 128},
	{0x3C, 64, 4, 256},
	{0x3D, 64, 6, 384},
	{0x3E, 64, 4, 512},
	{0x41, 32, 4, 128},
	{0x42, 32, 4, 256},
	{0x43, 32, 4, 512},
	{0x44, 32, 4, 1024},
	{0x45, 32, 4, 2*1024},
	{0x48, 64, 12, 3*1024},
	{0x49, 64, 16, 4*1024},	//L2 if not (family==F && model==6) L3 otherwise
	{0x4E, 64, 24, 6*1024},
	{0x78, 64, 4, 1024},
	{0x79, 64, 8, 128},
	{0x7A, 64, 8, 256},
	{0x7B, 64, 8, 512},
	{0x7C, 64, 8, 1024},
	{0x7D, 64, 8, 2*1024},
	{0x7E, 128, 8, 256},
	{0x7F, 64, 2, 512},
	{0x80, 64, 8, 512},
	{0x81, 32, 8, 128},
	{0x82, 32, 8, 256},
	{0x83, 32, 8, 512},
	{0x84, 32, 8, 1024},
	{0x85, 32, 8, 2*1024},
	{0x86, 64, 4, 512},
	{0x87, 64, 8, 1024},
	{0},					//end of L2
	{0x22, 64, 4, 512},
	{0x23, 64, 8, 1024},
	{0x25, 64, 8, 2*1024},
	{0x29, 64, 8, 4*1024},
	{0x46, 64, 4, 4*1024},
	{0x47, 64, 8, 8*1024},
	{0x49, 64, 16, 4*1024},	//L3 if (family==F && model==6), L2 otherwise
	{0x4A, 64, 12, 6*1024},
	{0x4B, 64, 16, 8*1024},
	{0x4C, 64, 12, 12*1024},
	{0x4D, 64, 16, 16*1024},
	{0xD0, 64, 4, 512},
	{0xD1, 64, 4, 1024},
	{0xD2, 64, 4, 2*1024},
	{0xD6, 64, 8, 1024},
	{0xD7, 64, 8, 2*1024},
	{0xD8, 64, 8, 4*1024},
	{0xDC, 64, 12, 3*512},
	{0xDD, 64, 12, 3*1024},
	{0xDE, 64, 12, 6*1024},
	{0xE2, 64, 16, 2*1024},
	{0xE3, 64, 16, 4*1024},
	{0xE4, 64, 16, 8*1024},
	{0xEA, 64, 24, 12*1024},
	{0xEB, 64, 24, 18*1024},
	{0xEC, 64, 24, 24*1024},
}; //Lx_cache

//***********************
static int is_cpuid_cpu()
//***********************
{
#if __VC
	__asm
	{
		// cpuid op is available if we can flip CPUID bit (21) in EFLAGS.
		pushfd
		mov		eax, [esp]
		XOR		dword ptr [esp], (1 << 21)
		popfd
		pushfd
		XOR		eax, [esp]
		popfd
		shr		eax, 21
		AND		eax, 1
	}
#else
	register int	result;

	__asm volatile
	(
		"pushfl\n"
		"mov	(%%esp), %%eax\n"
		"xorl	$0x00200000, (%%esp)\n"
		"popfl\n"
		"pushfl\n"
		"xor	(%%esp), %%eax\n"
		"popfl\n"
		"shr	$21, %%eax\n"
		"and	$1, %%eax\n"

		: "=a" (result)
	);

	return result;
#endif //__VC
} //is_cpuid_cpu

//*********************************************
static u32_t cpuid_func(int func, cpuid_t *cpu)
//*********************************************
// http://wiki.osdev.org/CPUID
{
	cpuid_t	_cpu;

#if __VC
	__asm
	{
		push	ebx
		mov		eax, func
		cpuid
		mov		_cpu.eax, eax
		mov		_cpu.ebx, ebx
		mov		_cpu.ecx, ecx
		mov		_cpu.edx, edx
		pop		ebx
	}
#else
	__asm volatile
	(
		"cpuid"
		: "=a"(_cpu.eax), "=b"(_cpu.ebx), "=c"(_cpu.ecx), "=d"(_cpu.edx)
		: "a"(func)
	);
#endif //__VC

	if (cpu)
		*cpu = _cpu;

	return _cpu.eax;
} //cpuid_func

//__get_cpu_info
//********************************************
static cpu_info_t get_cpu_info(u08_t sse_type)
//********************************************
/*
http://www.intel.com/Assets/PDF/appnote/241618.pdf
	Intel Processor Identification and the CPUID Instruction.
http://support.amd.com/us/Processor_TechDocs/25481.pdf
	AMD CPUID Specification.
http://www.sandpile.org/ia32/cpuid.htm
*/
{
	cpuid_t	cpu;
	u32_t	max_func, max_func_80;
	u32_t	cache_size;
	int		intel, amd;
	u08_t	*code = (u08_t *)&cpu;
	int		code_i, i;
	int		cache_level, level;
	int		code_49_L3;
	u32_t	temp;

	cpu_info.sse_type = sse_type;

	if (!is_cpuid_cpu())
		return cpu_info;

	max_func = cpuid_func(0, &cpu);

	if (!max_func)
		return cpu_info;

	temp = cpu.ecx;
	cpu.ecx = cpu.edx;
	cpu.edx = temp;

	intel = !memcmp(&cpu.ebx, "GenuineIntel", 12);
	amd = !memcmp(&cpu.ebx, "AuthenticAMD", 12);

	max_func_80 = cpuid_func(0x80000000, &cpu);
//	p("get_cpu_info: intel=%d, amd=%d, max_func=%X, max_func_80=%X", intel, amd, max_func, max_func_80);

	cpuid_func(1, &cpu);

	code_49_L3 = ((cpu.eax & 0x0FFF0FF0) == 0xF60);	//ext family=0, ext model=0, family=F, model=6
	cpu_info.clflush_line = (cpu.edx & (1 << 19)/*CLFSH*/) ? ((cpu.ebx >> 8) & 0xFF) * 8 : 0;

	cpu_info.sse_type =
		(cpu.ecx & (1 << 20)) ? SSE_SSE42 :
		(cpu.ecx & (1 << 19)) ? SSE_SSE41 :
		(cpu.ecx & (1 << 9)) ? SSE_SSSE3 :
		(cpu.ecx & (1 << 0)) ? SSE_SSE3 :
		(cpu.edx & (1 << 26)) ? SSE_SSE2 :
		(cpu.edx & (1 << 25)) ? SSE_SSE :
		(cpu.edx & (1 << 23)) ? SSE_MMX :
		SSE_NONE;

	if ((cpu.ecx & (1 << 28)) &&	//AVX
		(cpu.ecx & (1 << 27)) &&	//OSXSAVE
		(max_func >= 0x0D))
	{
		cpu.eax = 0x0D;
		cpu.ecx = 0;
		cpuid_func(-1, &cpu);
		if ((cpu.eax & 6) == 6)	//OS has enabled both XMM and YMM state support
			cpu_info.sse_type = SSE_AVX;
	}

	// Check for AMD extensions to MMX (SSE_MMX_EXT: prefetchnta, prefetcht0/1/2, movntq).
	if ((cpu_info.sse_type == SSE_MMX) && amd && (max_func_80 >= 0x80000001))
	{
		cpuid_func(0x80000001, &cpu);
		if (cpu.edx & (1 << 22))
			cpu_info.sse_type = SSE_MMX_EXT;
	}

#if defined(DEBUG_MEM_FORCE_MMX)
	cpu_info.sse_type = (cpu_info.sse_type >= SSE_MMX_EXT) ? SSE_MMX_EXT : SSE_MMX;
#endif
#if defined(DEBUG_MEM_FORCE_SSE2)
	cpu_info.sse_type = SSE_SSE2;
#endif

	if (cpu_info.sse_type >= SSE_SSE2)
		memcpy_sse_x(NULL, NULL, 0);
//	else if (cpu_info.sse_type >= SSE_MMX)
//		memcpy_mmx(NULL, NULL, 0);
	else
		cpu_info.memcpy_ptr = &memcpy_no_sse;

	cpu_info.core_n = (cpu.edx & (1 << 28)/*HTT*/) ? ((cpu.ebx >> 16) & 0xFF) : 1;

	if (amd && (cpu.edx & (1 << 28)) && (max_func_80 >= 0x80000008))
	{
		cpuid_func(0x80000008, &cpu);
		cpu_info.core_n = (cpu.ecx & 0xFF) + 1;
	}

	if (amd && (max_func_80 >= 0x80000005))
	{
		cpuid_func(0x80000005, &cpu);	//reserved for intel
		cpu_info.cache[0].size = (cpu.ecx >> 24) * 1024;
		cpu_info.cache[0].line = (cpu.ecx & 0xFF);
	}
	if (max_func_80 >= 0x80000006)	//intel/amd
	{
		cpuid_func(0x80000006, &cpu);
		cpu_info.cache[1].size = (cpu.ecx >> 16) * 1024;
		cpu_info.cache[1].line = (cpu.ecx & 0xFF);

		if (amd)
		{
			cpu_info.cache[2].size = (cpu.edx >> 18) * 512 * 1024;
			cpu_info.cache[2].line = (cpu.edx & 0xFF);
		}
	}

	// cpuid_func(2) is reserved for amd.
	if ((max_func >= 2) &&
		((cpuid_func(2, &cpu) & 0xFF) >= 1))	//number of needed cpuid_func(2) calls
	{
//		p("get_cpu_info: func2(%08X %08X %08X %08X)", cpu.eax, cpu.ebx, cpu.ecx, cpu.edx);

		// Go through the bytes of all 4 regs of cpu.
		// (cpu.eax & 0xFF) is the number of needed cpuid_func(2) calls. We do one call only.
		for (code_i = 15; code_i >= 1; code_i--)
		{
			if (!code[code_i])
				continue;
			else if ((code[code_i] & 0x80) && ((code_i & 3) == 3))	//high byte of eax/ebx/ecx/edx
			{
				code_i -= 3;	//skip reg
				continue;
			}
			else if (code[code_i] == 0xF0)
			{
				cpu_info.prefetch_line = 64;
				continue;
			}
			else if (code[code_i] == 0xF1)
			{
				cpu_info.prefetch_line = 128;
				continue;
			}

			// Find code[code_i] in Lx_cache[].
			cache_level = 0;
			for (i = 0; i < ARRAY_N(Lx_cache); i++)
			{
				if (!Lx_cache[i].code)	//end of L1 or L2 info
				{
					cache_level++;
				}
				else if (Lx_cache[i].code == code[code_i])
				{
					level = (Lx_cache[i].code == 0x49) ? ((code_49_L3) ? 2 : 1) :
						cache_level;

					cpu_info.cache[level] = Lx_cache[i];
					cpu_info.cache[level].size *= 1024;
//					p("get_cpu_info: (%02X) L%d(%dK %d)", code[code_i], level + 1, cpu_info.cache[level].size / 1024, cpu_info.cache[level].line);
					break;
				}
			} //for (i
		} //for (code_i
	} //if ((max_func >= 2)

	cache_size = (cpu_info.cache[2].size) ? cpu_info.cache[2].size : cpu_info.cache[1].size;	//L3/L2

	if (cpu_info.sse_type >= SSE_SSE2)
	{
		if (!cache_size)
			cache_size = SSE_CACHE_SIZE;

		cpu_info.sse_nt_size = cache_size / 64 * 33;

		cpu_info.sse_prefetch_size = (cpu_info.sse_type >= SSE_SSSE3) ?
			cpu_info.sse_nt_size :	//prefetch is not used
			cache_size / 64 * 12;	//old machine

		#if defined(DEBUG_MEM_FORCE_NO_PREF)
			cpu_info.sse_prefetch_size = (u32_t)-1;
			cpu_info.sse_nt_size = (u32_t)-1;
		#endif
		#if defined(DEBUG_MEM_FORCE_PREF)
			cpu_info.sse_prefetch_size = 0;
			cpu_info.sse_nt_size = (u32_t)-1;
		#endif
		#if defined(DEBUG_MEM_FORCE_NT)
			cpu_info.sse_prefetch_size = 0;
			cpu_info.sse_nt_size = 0;
		#endif
	}
	else if (cpu_info.sse_type == SSE_MMX_EXT)
	{
		cpu_info.mmx_nt_size = (cache_size) ? cache_size / 64 * 40 : MMX_NT_SIZE;
		cpu_info.mmx_load_nt_size = (cache_size) ? cache_size / 64 * 50 : MMX_LOAD_NT_SIZE;
	}

	return cpu_info;
} //get_cpu_info

#if __VC
	#define COPY_RET \
		__asm	mov		ebx, [esp + 4] \
		__asm	ret		4

	#define COPY_RET_1 \
		__asm	ret		4

	#define ALIGN_16	__asm	align 16

	#define _PALIGNR(to, from, offs) \
		__asm	_emit	0x66 \
		__asm	_emit	0x0F \
		__asm	_emit	0x3A \
		__asm	_emit	0x0F \
		__asm	_emit	0xC0 + from + (to << 3) \
		__asm	_emit	offs

	#define _VPALIGNR(to, from1, from0, offs) \
		__asm	_emit	0xC4 \
		__asm	_emit	0xE3 \
		__asm	_emit	0x41 + ((7 - from1) << 3) \
		__asm	_emit	0x0F \
		__asm	_emit	0xC0 + from0 + (to << 3) \
		__asm	_emit	offs

	#define _VMOVDQA_0(to) \
		__asm	_emit	0xC5 \
		__asm	_emit	0xFD \
		__asm	_emit	0x6F \
		__asm	_emit	0x02 + (to << 3)

	#define _VMOVDQA(to, offs) \
		__asm	_emit	0xC5 \
		__asm	_emit	0xFD \
		__asm	_emit	0x6F \
		__asm	_emit	0x42 + (to << 3) \
		__asm	_emit	offs

	#define _VMOVNTDQ_0(from) \
		__asm	_emit	0xC5 \
		__asm	_emit	0xFD \
		__asm	_emit	0xE7 \
		__asm	_emit	0x01 + (from << 3)

	#define _VMOVNTDQ(offs, from) \
		__asm	_emit	0xC5 \
		__asm	_emit	0xFD \
		__asm	_emit	0xE7 \
		__asm	_emit	0x41 + (from << 3) \
		__asm	_emit	offs

	#define C64_PREFETCH_R_no_pref
	#define C64_PREFETCH_W_no_pref
	#define C64_PREFETCH_R_pref \
		__asm	prefetchnta	[edx + 1024]
	#define C64_PREFETCH_W_pref \
		__asm	prefetcht0	[eax + 1024]
	#define C64_PREFETCH_R_nt
	#define C64_PREFETCH_W_nt

	#define C64_STORE_no_pref	__asm	movaps
	#define C64_STORE_pref		__asm	movaps
	#define C64_STORE_nt		__asm	movntps

	#define C64_SFENCE_no_pref
	#define C64_SFENCE_pref
	#define C64_SFENCE_nt		__asm	sfence

	#define C64_JMP				__asm	jmp		copy_127_u
	#define C64_JMP_SSE2		__asm	jmp		copy_80_do

//__COPY_64_vc
	// SSE2 version.
	#define COPY_64(offs, op) \
		ALIGN_16 \
		__asm copy_64__##offs##op: \
			C64_PREFETCH_R_##op \
			C64_PREFETCH_W_##op \
			__asm	movaps	xmm1, [edx + 16] \
			__asm	movaps	xmm2, [edx + 32] \
			__asm	movaps	xmm3, [edx + 48] \
			__asm	movaps	xmm4, [edx + 64] \
			__asm	movaps	xmm5, xmm1 \
			__asm	movaps	xmm6, xmm2 \
			__asm	movaps	xmm7, xmm3 \
			__asm	psrldq	xmm0, offs		/*shift right (to first byte)*/ \
			__asm	pslldq	xmm1, 16 - offs	/*shift left*/ \
			__asm	psrldq	xmm5, offs \
			__asm	pslldq	xmm6, 16 - offs \
			__asm	por		xmm0, xmm1 \
			__asm	psrldq	xmm2, offs \
			__asm	por		xmm5, xmm6 \
			C64_STORE_##op	[ecx], xmm0 \
			__asm	pslldq	xmm3, 16 - offs \
			__asm	movaps	xmm0, xmm4 \
			__asm	psrldq	xmm7, offs \
			__asm	pslldq	xmm4, 16 - offs \
			C64_STORE_##op	[ecx + 16], xmm5 \
			__asm	por		xmm2, xmm3 \
			__asm	sub		eax, 64 \
			__asm	por		xmm7, xmm4 \
			C64_STORE_##op	[ecx + 32], xmm2 \
			__asm	cmp		eax, 80 \
			C64_STORE_##op	[ecx + 48], xmm7 \
			__asm	lea		edx, [edx + 64] \
			__asm	lea		ecx, [ecx + 64] \
			__asm	jae		copy_64__##offs##op \
			__asm	add		edx, offs \
			C64_SFENCE_##op \
			C64_JMP_SSE2

	// SSSE3 version (with _PALIGNR()).
	#define COPY_64x(offs, op) \
		ALIGN_16 \
		__asm copy_64x__##offs##op: \
			__asm	movaps	xmm1, [edx + 16] \
			__asm	movaps	xmm2, [edx + 32] \
			__asm	movaps	xmm3, [edx + 48] \
			__asm	movaps	xmm4, [edx + 64] \
			__asm	movaps	xmm5, xmm0 \
			__asm	movaps	xmm0, xmm4 \
			__asm	sub		eax, 64 \
			_PALIGNR(4, 3, offs) \
			_PALIGNR(3, 2, offs) \
			_PALIGNR(2, 1, offs) \
			_PALIGNR(1, 5, offs) \
\
			C64_PREFETCH_R_##op \
			C64_PREFETCH_W_##op \
			C64_STORE_##op	[ecx], xmm1 \
			__asm	cmp		eax, 80 \
			C64_STORE_##op	[ecx + 16], xmm2 \
			C64_STORE_##op	[ecx + 32], xmm3 \
			C64_STORE_##op	[ecx + 48], xmm4 \
\
			__asm	lea		edx, [edx + 64] \
			__asm	lea		ecx, [ecx + 64] \
			__asm	jae		copy_64x__##offs##op \
			__asm	add		edx, offs \
			C64_SFENCE_##op \
			C64_JMP

	// AVX version (with _VPALIGNR()).
	#define COPY_64v(offs, op) \
		ALIGN_16 \
		__asm copy_64v__##offs##op: \
			__asm	movaps	xmm1, [edx + 16] \
			__asm	movaps	xmm2, [edx + 32] \
			__asm	movaps	xmm3, [edx + 48] \
			__asm	movaps	xmm4, [edx + 64] \
			__asm	sub		eax, 64 \
/* \
			__asm	vpalignr	xmm5, xmm1, xmm0, offs \
			__asm	vpalignr	xmm6, xmm2, xmm1, offs \
			__asm	vpalignr	xmm7, xmm3, xmm2, offs \
			__asm	vpalignr	xmm1, xmm4, xmm3, offs \
*/ \
			_VPALIGNR(5, 1, 0, offs) \
			_VPALIGNR(6, 2, 1, offs) \
			_VPALIGNR(7, 3, 2, offs) \
			_VPALIGNR(1, 4, 3, offs) \
			__asm	movaps	xmm0, xmm4 \
\
			C64_PREFETCH_R_##op \
			C64_PREFETCH_W_##op \
			__asm	cmp		eax, 80 \
			C64_STORE_##op	[ecx], xmm5 \
			C64_STORE_##op	[ecx + 16], xmm6 \
			C64_STORE_##op	[ecx + 32], xmm7 \
			C64_STORE_##op	[ecx + 48], xmm1 \
\
			__asm	lea		edx, [edx + 64] \
			__asm	lea		ecx, [ecx + 64] \
			__asm	jae		copy_64v__##offs##op \
			__asm	add		edx, offs \
			C64_SFENCE_##op \
			C64_JMP

	#define COPY_64__4(op) \
		ALIGN_16 \
		__asm copy_64__4##op: \
			C64_PREFETCH_R_##op \
			C64_PREFETCH_W_##op \
			__asm	movaps	xmm1, [edx + 16] \
			__asm	movaps	xmm2, [edx + 32] \
			__asm	movaps	xmm3, [edx + 48] \
			__asm	movss	xmm0, xmm1 \
			__asm	sub		eax, 64 \
			__asm	movss	xmm1, xmm2 \
			__asm	cmp		eax, 80 \
			__asm	movss	xmm2, xmm3 \
			__asm	shufps  xmm0, xmm0, 0x39	/*xmm0[0]=xmm0[1], [1]=[2], [2]=[3], [3]=[0] (four 2-bit indexes)*/ \
			__asm	shufps  xmm1, xmm1, 0x39 \
			__asm	shufps  xmm2, xmm2, 0x39 \
\
			C64_STORE_##op	[ecx], xmm0 \
			C64_STORE_##op	[ecx + 16], xmm1 \
			__asm	movaps	xmm0, [edx + 64] \
			__asm	movss	xmm3, xmm0 \
			C64_STORE_##op	[ecx + 32], xmm2 \
			__asm	shufps  xmm3, xmm3, 0x39 \
			C64_STORE_##op	[ecx + 48], xmm3 \
\
			__asm	lea		edx, [edx + 64] \
			__asm	lea		ecx, [ecx + 64] \
			__asm	jae		copy_64__4##op \
			__asm	add		edx, 4 \
			C64_SFENCE_##op \
			C64_JMP_SSE2

	#define COPY_64__12(op) \
		ALIGN_16 \
		__asm copy_64__12##op: \
			C64_PREFETCH_R_##op \
			C64_PREFETCH_W_##op \
			__asm	movaps	xmm1, [edx + 16] \
			__asm	movaps	xmm2, [edx + 32] \
			__asm	shufps  xmm0, xmm1, 0x4E \
			__asm	movaps	xmm3, [edx + 48] \
			__asm	shufps  xmm0, xmm1, 0x99 \
			__asm	sub		eax, 64 \
\
			__asm	shufps  xmm1, xmm2, 0x4E \
			__asm	cmp		eax, 80 \
			__asm	shufps  xmm1, xmm2, 0x99 \
\
			__asm	shufps  xmm2, xmm3, 0x4E \
			C64_STORE_##op	[ecx], xmm0 \
			__asm	shufps  xmm2, xmm3, 0x99 \
			C64_STORE_##op	[ecx + 16], xmm1 \
\
			__asm	movaps	xmm0, [edx + 64] \
			C64_STORE_##op	[ecx + 32], xmm2 \
			__asm	shufps  xmm3, xmm0, 0x4E \
			__asm	shufps  xmm3, xmm0, 0x99 \
			C64_STORE_##op	[ecx + 48], xmm3 \
\
			__asm	lea		edx, [edx + 64] \
			__asm	lea		ecx, [ecx + 64] \
			__asm	jae		copy_64__12##op \
			__asm	add		edx, 12 \
			C64_SFENCE_##op \
			C64_JMP_SSE2

	#define COPY_64__8(op) \
		ALIGN_16 \
		__asm copy_64__8##op: \
			__asm	movaps	xmm1, [edx + 16] \
			C64_PREFETCH_R_##op \
			C64_PREFETCH_W_##op \
			__asm	movaps	xmm2, [edx + 32] \
			__asm	sub		eax, 64 \
			__asm	shufps  xmm0, xmm1, 0x4E	/*xmm0[0]=xmm0[2], [1]=[3], [2]=[0], [3]=[1]; shufpd xmm0, xmm1, 1*/ \
			C64_STORE_##op	[ecx], xmm0 \
\
			__asm	cmp		eax, 80 \
			__asm	shufps  xmm1, xmm2, 0x4E \
			C64_STORE_##op	[ecx + 16], xmm1 \
\
			__asm	movaps	xmm3, [edx + 48] \
			__asm	movaps	xmm0, [edx + 64] \
			__asm	shufps  xmm2, xmm3, 0x4E \
			C64_STORE_##op	[ecx + 32], xmm2 \
\
			__asm	shufps  xmm3, xmm0, 0x4E \
			C64_STORE_##op	[ecx + 48], xmm3 \
\
			__asm	lea		edx, [edx + 64] \
			__asm	lea		ecx, [ecx + 64] \
			__asm	jae		copy_64__8##op \
			__asm	add		edx, 8 \
			C64_SFENCE_##op \
			C64_JMP_SSE2
#endif //__VC

#define COPY_64__1_15(op) \
	COPY_64(1, op) \
	COPY_64(2, op) \
	COPY_64(3, op) \
	COPY_64__4(op) \
	COPY_64(5, op) \
	COPY_64(6, op) \
	COPY_64(7, op) \
	COPY_64__8(op) \
	COPY_64(9, op) \
	COPY_64(10, op) \
	COPY_64(11, op) \
	COPY_64__12(op) \
	COPY_64(13, op) \
	COPY_64(14, op) \
	COPY_64(15, op)

#define COPY_64x__1_15(op) \
	COPY_64x(1, op) \
	COPY_64x(2, op) \
	COPY_64x(3, op) \
	COPY_64x(4, op) \
	COPY_64x(5, op) \
	COPY_64x(6, op) \
	COPY_64x(7, op) \
	COPY_64x(8, op) \
	COPY_64x(9, op) \
	COPY_64x(10, op) \
	COPY_64x(11, op) \
	COPY_64x(12, op) \
	COPY_64x(13, op) \
	COPY_64x(14, op) \
	COPY_64x(15, op)

#define COPY_64v__1_15(op) \
	COPY_64v(1, op) \
	COPY_64v(2, op) \
	COPY_64v(3, op) \
	COPY_64v(4, op) \
	COPY_64v(5, op) \
	COPY_64v(6, op) \
	COPY_64v(7, op) \
	COPY_64v(8, op) \
	COPY_64v(9, op) \
	COPY_64v(10, op) \
	COPY_64v(11, op) \
	COPY_64v(12, op) \
	COPY_64v(13, op) \
	COPY_64v(14, op) \
	COPY_64v(15, op)

//****************************************************************************
static MEM_RET_TYPE MEM_CALL memcpy_sse_x(void *dest, void *src, size_t _size)
//****************************************************************************
{
//__memcpy_sse_x_vc
	__asm
	{
		mov		cpu_info.memcpy_ptr, offset memcpy_entry	//default entry

		#define L_16(size)	__asm	mov	cpu_info.copy_jmp_tab+size*4, offset copy_##size
		
		// mov	cpu_info.copy_jmp_tab+@*4, offset copy_@ (@=0..16)
		L_16(0)
		L_16(1)
		L_16(2)
		L_16(3)
		L_16(4)
		L_16(5)
		L_16(6)
		L_16(7)
		L_16(8)
		L_16(9)
		L_16(10)
		L_16(11)
		L_16(12)
		L_16(13)
		L_16(14)
		L_16(15)
		L_16(16)	//overlaps copy_no_prefetch[0] (first used is copy_no_prefetch[1])

#ifdef JMP_TAB_SIZE_32
		L_16(17)
		L_16(18)
		L_16(19)
		L_16(20)
		L_16(21)
		L_16(22)
		L_16(23)
		L_16(24)
		L_16(25)
		L_16(26)
		L_16(27)
		L_16(28)
		L_16(29)
		L_16(30)
		L_16(31)
		L_16(32)
#endif

		cmp		byte ptr cpu_info.sse_type, SSE_AVX
		jae		init_avx
		cmp		byte ptr cpu_info.sse_type, SSE_SSSE3
		jae		init_ssse3

		mov		cpu_info.memcpy_ptr, offset memcpy_entry_sse2

		#define L_no_pref(x64, offs)	__asm	mov	cpu_info.copy_no_prefetch+offs*4, offset copy_##x64##__##offs##no_pref
		#define L_pref(x64, offs)		__asm	mov	cpu_info.copy_prefetch+offs*4, offset copy_##x64##__##offs##pref
		#define L_nt(x64, offs)			__asm	mov	cpu_info.copy_nt+offs*4, offset copy_##x64##__##offs##nt

		#define STORE_LABEL_1_15(x64, op) \
			L_##op(x64, 1) \
			L_##op(x64, 2) \
			L_##op(x64, 3) \
			L_##op(x64, 4) \
			L_##op(x64, 5) \
			L_##op(x64, 6) \
			L_##op(x64, 7) \
			L_##op(x64, 8) \
			L_##op(x64, 9) \
			L_##op(x64, 10) \
			L_##op(x64, 11) \
			L_##op(x64, 12) \
			L_##op(x64, 13) \
			L_##op(x64, 14) \
			L_##op(x64, 15)

		// mov	cpu_info.copy_no_prefetch+@*4, offset copy_64__@no_pref (@=1..15)
		STORE_LABEL_1_15(64, no_pref)

		// mov	cpu_info.copy_prefetch+@*4, offset copy_64__@pref (@=1..15)
		STORE_LABEL_1_15(64, pref)

		jmp		init_end

	init_ssse3:
		// mov	cpu_info.copy_no_prefetch+@*4, offset copy_64x__@no_pref (@=1..15)
		STORE_LABEL_1_15(64x, no_pref)

		// Prefetch is not used (see get_cpu_info()->sse_prefetch_size).
		// mov	cpu_info.copy_prefetch+@*4, offset copy_64x__@pref (@=1..15)
//		STORE_LABEL_1_15(64x, pref)

		// mov	cpu_info.copy_nt+@*4, offset copy_64x__@nt (@=1..15)
		STORE_LABEL_1_15(64x, nt)

		jmp		init_end

	init_avx:
		// mov	cpu_info.copy_no_prefetch+@*4, offset copy_64v__@no_pref (@=1..15)
		STORE_LABEL_1_15(64v, no_pref)

		// Prefetch is not used (see get_cpu_info()->sse_prefetch_size).
		// mov	cpu_info.copy_prefetch+@*4, offset copy_64v__@pref (@=1..15)
//		STORE_LABEL_1_15(64v, pref)

		// mov	cpu_info.copy_nt+@*4, offset copy_64v__@nt (@=1..15)
		STORE_LABEL_1_15(64v, nt)
	init_end:

		#undef L_16
		#undef L_no_pref
		#undef L_pref
		#undef L_nt
		#undef STORE_LABEL_1_15
	}
	return;

	__asm
	{
		// Real entry is either memcpy_entry or memcpy_entry_sse2. It is called through memcpy_ptr.
		// It is stored to memcpy_ptr by the only memcpy_sse_x(NULL, NULL, 0) normal call.
		// esi, edi, ebx regs must be saved if they are used.
		// ecx: dest
		// edx: src
		// eax: _size
		// ebx: work reg; its value on entry is saved to [esp + 4] (_size param).
	////////////////////////////////////////////////////////////////////////////
//__memcpy_entry_sse2
		// memcpy_entry_sse2 is used if (cpu_info.sse_type < SSE_SSSE3).
	ALIGN_16
	memcpy_entry_sse2:
		mov		eax, [esp + 4]	//_size

		// Copy first 0..64 bytes.
		cmp		eax, 64
		ja		align_16

		cmp		eax, 16
		ja		copy_80_sse2

		jmp		dword ptr [cpu_info.copy_jmp_tab + eax * 4]

		// (_size > 16) && (_size <= 64).
	copy_80_sse2:
		mov		[esp + 4], ebx

		test	ecx, 3
		jz		align_4_end
		mov		ebx, [edx]
		mov		[ecx], ebx
		mov		ebx, ecx
		neg		ebx
		AND		ebx, 3	//"and" could be reserved word in some VC versions
		sub		eax, ebx
		add		edx, ebx
		add		ecx, ebx
	align_4_end:

		// Jump here from copy_64xxx methods only (not COPY_64x()), (_size < 80), (cpu_info.sse_type < SSE_SSSE3).
	copy_80_do:
		mov		ebx, [edx + eax - 4]
		mov		[ecx + eax - 4], ebx

		AND		eax, -4
		add		edx, eax
		add		ecx, eax
		shr		eax, 1
		lea		eax, [eax + eax * 2]
		neg		eax
		add		eax, offset copy_80_tab
		jmp		eax

		mov		eax, [edx - 20*4]
		mov		[ecx - 20*4], eax
		mov		ebx, [edx - 19*4]
		mov		[ecx - 19*4], ebx
		mov		eax, [edx - 18*4]
		mov		[ecx - 18*4], eax
		mov		ebx, [edx - 17*4]
		mov		[ecx - 17*4], ebx

		mov		eax, [edx - 16*4]
		mov		[ecx - 16*4], eax
		mov		ebx, [edx - 15*4]
		mov		[ecx - 15*4], ebx
		mov		eax, [edx - 14*4]
		mov		[ecx - 14*4], eax
		mov		ebx, [edx - 13*4]
		mov		[ecx - 13*4], ebx
		mov		eax, [edx - 12*4]
		mov		[ecx - 12*4], eax
		mov		ebx, [edx - 11*4]
		mov		[ecx - 11*4], ebx
		mov		eax, [edx - 10*4]
		mov		[ecx - 10*4], eax
		mov		ebx, [edx - 9*4]
		mov		[ecx - 9*4], ebx
		mov		eax, [edx - 8*4]
		mov		[ecx - 8*4], eax
		mov		ebx, [edx - 7*4]
		mov		[ecx - 7*4], ebx
		mov		eax, [edx - 6*4]
		mov		[ecx - 6*4], eax
		mov		ebx, [edx - 5*4]
		mov		[ecx - 5*4], ebx
		mov		eax, [edx - 4*4]
		mov		[ecx - 4*4], eax
		mov		ebx, [edx - 3*4]
		mov		[ecx - 3*4], ebx
		mov		eax, [edx - 2*4]
		mov		[ecx - 2*4], eax
		mov		ebx, [edx - 1*4]
		mov		[ecx - 1*4], ebx
	copy_80_tab:

		COPY_RET

	////////////////////////////////////////////////////////////////////////////
//__memcpy_entry
		// memcpy_entry is used if (cpu_info.sse_type >= SSE_SSSE3).
	ALIGN_16
	memcpy_entry:
		mov		eax, [esp + 4]	//_size

		cmp		eax, 64
		ja		align_16

		// Copy first 0..64 bytes.
#ifndef JMP_TAB_SIZE_32
		cmp		eax, 16
#else
		cmp		eax, 32
#endif
		ja		copy_64

		// Copy first 0..16 bytes.
		jmp		dword ptr [cpu_info.copy_jmp_tab + eax * 4]

	copy_1:
		movzx	eax, byte ptr [edx]
		mov		[ecx], al
	copy_0:
		COPY_RET_1

	ALIGN_16
	copy_2:
		movzx	eax, word ptr [edx]
		mov		[ecx], ax
		COPY_RET_1

	ALIGN_16
	copy_3:
		movzx	eax, word ptr [edx]
		mov		[ecx], ax
		movzx	eax, byte ptr [edx + 2]
		mov		[ecx + 2], al
		COPY_RET_1

	ALIGN_16
	copy_4:
		mov		eax, [edx]
		mov		[ecx], eax
		COPY_RET_1

	ALIGN_16
	copy_5:
		movd	xmm0, dword ptr [edx]
		movzx	eax, byte ptr [edx + 4]
		movd	dword ptr [ecx], xmm0
		mov		[ecx + 4], al
		COPY_RET_1

	ALIGN_16
	copy_6:
		movd	xmm0, dword ptr [edx]
		movzx	eax, word ptr [edx + 4]
		movd	dword ptr [ecx], xmm0
		mov		[ecx + 4], ax
		COPY_RET_1

	ALIGN_16
	copy_7:
		movd	xmm0, dword ptr [edx]
		mov		eax, [edx + 3]
		movd	dword ptr [ecx], xmm0
		mov		[ecx + 3], eax
		COPY_RET_1

	ALIGN_16
	copy_8:
		movq	xmm0, qword ptr [edx]
		movq	qword ptr [ecx], xmm0
		COPY_RET_1

	ALIGN_16
	copy_9:
		movq	xmm0, qword ptr [edx]
		movzx	eax, byte ptr [edx + 8]
		movq	qword ptr [ecx], xmm0
		mov		[ecx + 8], al
		COPY_RET_1

	ALIGN_16
	copy_10:
		movq	xmm0, qword ptr [edx]
		movzx	eax, word ptr [edx + 8]
		movq	qword ptr [ecx], xmm0
		mov		[ecx + 8], ax
		COPY_RET_1

	ALIGN_16
	copy_11:
		movq	xmm0, qword ptr [edx]
		mov		eax, [edx + 7]
		movq	qword ptr [ecx], xmm0
		mov		[ecx + 7], eax
		COPY_RET_1

	ALIGN_16
	copy_12:
		movq	xmm0, qword ptr [edx]
		mov		eax, [edx + 8]
		movq	qword ptr [ecx], xmm0
		mov		[ecx + 8], eax
		COPY_RET_1

	ALIGN_16
	copy_13:
		movq	xmm0, qword ptr [edx]
		movd	xmm1, dword ptr [edx + 8]
		movzx	eax, byte ptr [edx + 12]
		movq	qword ptr [ecx], xmm0
		movd	dword ptr [ecx + 8], xmm1
		mov		[ecx + 12], al
		COPY_RET_1

	ALIGN_16
	copy_14:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 6]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 6], xmm1
		COPY_RET_1

	ALIGN_16
	copy_15:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 7]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 7], xmm1
		COPY_RET_1

	ALIGN_16
	copy_16:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		COPY_RET_1

#ifdef JMP_TAB_SIZE_32
	ALIGN_16
	copy_17:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movzx	eax, byte ptr [edx + 16]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		mov		[ecx + 16], al
		COPY_RET_1

	ALIGN_16
	copy_18:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movzx	eax, word ptr [edx + 16]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		mov		[ecx + 16], ax
		COPY_RET_1

	ALIGN_16
	copy_19:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		mov		eax, [edx + 15]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		mov		[ecx + 15], eax
		COPY_RET_1

	ALIGN_16
	copy_20:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		mov		eax, [edx + 16]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		mov		[ecx + 16], eax
		COPY_RET_1

	ALIGN_16
	copy_21:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movd	xmm2, dword ptr [edx + 16]
		movzx	eax, byte ptr [edx + 20]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		movd	dword ptr [ecx + 16], xmm2
		mov		[ecx + 20], al
		COPY_RET_1

	ALIGN_16
	copy_22:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movq	xmm2, qword ptr [edx + 14]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		movq	qword ptr [ecx + 14], xmm2
		COPY_RET_1

	ALIGN_16
	copy_23:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movq	xmm2, qword ptr [edx + 15]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		movq	qword ptr [ecx + 15], xmm2
		COPY_RET_1

	ALIGN_16
	copy_24:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movq	xmm2, qword ptr [edx + 16]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		movq	qword ptr [ecx + 16], xmm2
		COPY_RET_1

	ALIGN_16
	copy_25:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movq	xmm2, qword ptr [edx + 16]
		movzx	eax, byte ptr [edx + 24]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		movq	qword ptr [ecx + 16], xmm2
		mov		[ecx + 24], al
		COPY_RET_1

	ALIGN_16
	copy_26:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movq	xmm2, qword ptr [edx + 16]
		movzx	eax, word ptr [edx + 24]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		movq	qword ptr [ecx + 16], xmm2
		mov		[ecx + 24], ax
		COPY_RET_1

	ALIGN_16
	copy_27:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movq	xmm2, qword ptr [edx + 16]
		mov		eax, [edx + 23]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		movq	qword ptr [ecx + 16], xmm2
		mov		[ecx + 23], eax
		COPY_RET_1

	ALIGN_16
	copy_28:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movq	xmm2, qword ptr [edx + 16]
		mov		eax, [edx + 24]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		movq	qword ptr [ecx + 16], xmm2
		mov		[ecx + 24], eax
		COPY_RET_1

	ALIGN_16
	copy_29:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movq	xmm2, qword ptr [edx + 16]
		movd	xmm3, dword ptr [edx + 24]
		movzx	eax, byte ptr [edx + 28]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		movq	qword ptr [ecx + 16], xmm2
		movd	dword ptr [ecx + 24], xmm3
		mov		[ecx + 28], al
		COPY_RET_1

	ALIGN_16
	copy_30:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movq	xmm2, qword ptr [edx + 16]
		movq	xmm3, qword ptr [edx + 22]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		movq	qword ptr [ecx + 16], xmm2
		movq	qword ptr [ecx + 22], xmm3
		COPY_RET_1

	ALIGN_16
	copy_31:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movq	xmm2, qword ptr [edx + 16]
		movq	xmm3, qword ptr [edx + 23]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		movq	qword ptr [ecx + 16], xmm2
		movq	qword ptr [ecx + 23], xmm3
		COPY_RET_1

	ALIGN_16
	copy_32:
		movq	xmm0, qword ptr [edx]
		movq	xmm1, qword ptr [edx + 8]
		movq	xmm2, qword ptr [edx + 16]
		movq	xmm3, qword ptr [edx + 24]
		movq	qword ptr [ecx], xmm0
		movq	qword ptr [ecx + 8], xmm1
		movq	qword ptr [ecx + 16], xmm2
		movq	qword ptr [ecx + 24], xmm3
		COPY_RET_1
#endif //JMP_TAB_SIZE_32

		// Copy first 17..64 bytes.
	ALIGN_16
	copy_64:
#ifndef JMP_TAB_SIZE_32
		cmp		eax, 48
		jae		copy_64_64
		cmp		eax, 32
		jae		copy_64_48

		movq	xmm0, qword ptr [edx+0*8]
		movq	xmm1, qword ptr [edx+1*8]
		movq	qword ptr [ecx+0*8], xmm0
		movq	qword ptr [ecx+1*8], xmm1
		add		edx, 16
		add		ecx, 16
		jmp		dword ptr [cpu_info.copy_jmp_tab - 16 * 4 + eax * 4]

	copy_64_48:
		movq	xmm0, qword ptr [edx+0*8]
		movq	xmm1, qword ptr [edx+1*8]
		movq	xmm2, qword ptr [edx+2*8]
		movq	xmm3, qword ptr [edx+3*8]
		movq	qword ptr [ecx+0*8], xmm0
		movq	qword ptr [ecx+1*8], xmm1
		movq	qword ptr [ecx+2*8], xmm2
		movq	qword ptr [ecx+3*8], xmm3
		add		edx, 32
		add		ecx, 32
		jmp		dword ptr [cpu_info.copy_jmp_tab - 32 * 4 + eax * 4]

	copy_64_64:
		movq	xmm0, qword ptr [edx+0*8]
		movq	xmm1, qword ptr [edx+1*8]
		movq	xmm2, qword ptr [edx+2*8]
		movq	xmm3, qword ptr [edx+3*8]
		movq	xmm4, qword ptr [edx+4*8]
		movq	xmm5, qword ptr [edx+5*8]
		movq	qword ptr [ecx+0*8], xmm0
		movq	qword ptr [ecx+1*8], xmm1
		movq	qword ptr [ecx+2*8], xmm2
		movq	qword ptr [ecx+3*8], xmm3
		movq	qword ptr [ecx+4*8], xmm4
		movq	qword ptr [ecx+5*8], xmm5
		add		edx, 48
		add		ecx, 48
		jmp		dword ptr [cpu_info.copy_jmp_tab - 48 * 4 + eax * 4]
#else
		movq	xmm0, qword ptr [edx+0*8]
		movq	xmm1, qword ptr [edx+1*8]
		movq	xmm2, qword ptr [edx+2*8]
		movq	xmm3, qword ptr [edx+3*8]
		movq	qword ptr [ecx+0*8], xmm0
		movq	qword ptr [ecx+1*8], xmm1
		movq	qword ptr [ecx+2*8], xmm2
		movq	qword ptr [ecx+3*8], xmm3
		add		edx, 32
		add		ecx, 32
		jmp		dword ptr [cpu_info.copy_jmp_tab - 32 * 4 + eax * 4]
#endif //JMP_TAB_SIZE_32

	////////////////////////////////////////////////////////////////////////////
		// Copy 0..15 bytes to align dest to 16-byte boundary (_size >= 17).
		// memcpy_ptr is in cache: it was used to call memcpy_sse_x().
//__align_16
	ALIGN_16
	align_16:
		mov		[esp + 4], ebx

		mov		ebx, ecx		//dest
		prefetcht0	cpu_info.memcpy_ptr + 64
		neg		ebx
		AND		ebx, 15			//ebx = 0..15 bytes to copy
		jz		align_16_end
		cmp		bl, 8
		movq	xmm0, qword ptr [edx]
		movq	qword ptr [ecx], xmm0
		jbe		align_16_add
		movq	xmm1, qword ptr [edx + ebx - 8]
		movq	qword ptr [ecx + ebx - 8], xmm1
	align_16_add:
		sub		eax, ebx		//remaining bytes
		add		edx, ebx
		add		ecx, ebx
	align_16_end:

	////////////////////////////////////////////////////////////////////////////
		// Choose one of copy_no_prefetch_*/copy_prefetch_*/copy_nt_* methods to copy all 64/128-byte blocks.
		// ecx: dest
		// edx: src
		// eax: _size
		// ebx: block count, work reg
		mov		ebx, edx
		AND		ebx, 15
		jz		aligned_src

		// COPY_64xxx methods can be used with (_size >= 112) only.
		cmp		eax, 112
		jb		copy_127_u

		// Align src for COPY_64xxx methods.
		movdqu	xmm0, [edx]
		movdqa	[ecx], xmm0
		sub		eax, 16
		add		edx, 16
		add		ecx, 16
		AND		edx, -16

		cmp		eax, cpu_info.sse_prefetch_size
		movdqa	xmm0, [edx]		//xmm0 will be used by COPY_64xxx methods
		jae		copy_prefetch_u0
		jmp		dword ptr [cpu_info.copy_no_prefetch + ebx * 4]
	copy_prefetch_u0:
		cmp		eax, cpu_info.sse_nt_size
		jae		copy_nt_u0
		jmp		dword ptr [cpu_info.copy_prefetch + ebx * 4]
	copy_nt_u0:
		cmp		byte ptr cpu_info.sse_type, SSE_SSSE3
		jb		copy_nt_u1
		jmp		dword ptr [cpu_info.copy_nt + ebx * 4]
	copy_nt_u1:
		lea		edx, [edx + ebx]	//edx value before "AND edx, -16" above
		XOR		ebx, ebx
		jmp		copy_nt_block_u

	aligned_src:
		cmp		eax, cpu_info.sse_prefetch_size
		mov		ebx, eax
		jb		copy_no_prefetch_a0
		shr		ebx, 7
		cmp		eax, cpu_info.sse_nt_size
		jb		copy_prefetch_a

		cmp		byte ptr cpu_info.sse_type, SSE_SSSE3
		jb		copy_nt_old_a
		cmp		byte ptr cpu_info.sse_type, SSE_AVX
		jb		copy_nt_a

		// Use copy_nt_avx_a if dest and src have same mod32, use copy_nt_a otherwise.
		mov		ebx, edx
		XOR		ebx, ecx
		test	ebx, 16
		jz		copy_nt_avx_a0

		// dest and src have different mod32.
		mov		ebx, eax
		shr		ebx, 7
		jmp		copy_nt_a

		// dest and src have same mod32. Copy 16 bytes if (mod32 == 16).
	copy_nt_avx_a0:
		test	edx, 16
		jz		copy_nt_avx_a1
		movdqa	xmm0, [edx]
		movdqa	[ecx], xmm0
		sub		eax, 16
		add		edx, 16
		add		ecx, 16
	copy_nt_avx_a1:
		mov		ebx, eax
		shr		ebx, 7
		jmp		copy_nt_avx_a

	copy_nt_old_a:
		XOR		ebx, ebx
		jmp		copy_nt_block_u

	////////////////////////////////////////////////////////////////////////////
//__COPY_64__1_15
		// COPY_64xxx methods for unaligned src (dest is always aligned after align_16).
		// SSE2 version.
		COPY_64__1_15(no_pref)
		COPY_64__1_15(pref)
//		COPY_64__1_15(nt)	//copy_nt_block_u is used

		// SSSE3 version (with _PALIGNR()).
		// Prefetch is not used (see get_cpu_info()->sse_prefetch_size).
		COPY_64x__1_15(no_pref)
//		COPY_64x__1_15(pref)
		COPY_64x__1_15(nt)

		// AVX version (with _VPALIGNR()).
		// Prefetch is not used (see get_cpu_info()->sse_prefetch_size).
		COPY_64v__1_15(no_pref)
//		COPY_64v__1_15(pref)
		COPY_64v__1_15(nt)

	////////////////////////////////////////////////////////////////////////////
//__copy_no_prefetch_a
	copy_no_prefetch_a0:
		shr		ebx, 6
		jz		copy_127_32_a

	ALIGN_16
	copy_no_prefetch_a:
		dec		ebx

		movdqa	xmm0, [edx+0*16]
		movdqa	xmm1, [edx+1*16]
		movdqa	xmm2, [edx+2*16]
		movdqa	xmm3, [edx+3*16]
		movdqa	[ecx+0*16], xmm0
		movdqa	[ecx+1*16], xmm1
		movdqa	[ecx+2*16], xmm2
		movdqa	[ecx+3*16], xmm3

		lea		edx, [edx + 64]
		lea		ecx, [ecx + 64]
		jnz		copy_no_prefetch_a

		AND		eax, 64
		jmp		copy_127_32_a

	////////////////////////////////////////////////////////////////////////////
		// eax >= cpu_info.sse_prefetch_size.
//__copy_prefetch_a
	ALIGN_16
	copy_prefetch_a:
		prefetchnta	[edx + SSE_PREFETCH_OFFS]
		dec		ebx

		movdqa	xmm0, [edx+0*16]
		movdqa	xmm1, [edx+1*16]
		movdqa	xmm2, [edx+2*16]
		movdqa	xmm3, [edx+3*16]
		movdqa	[ecx+0*16], xmm0
		movdqa	[ecx+1*16], xmm1
		movdqa	[ecx+2*16], xmm2
		movdqa	[ecx+3*16], xmm3

		prefetcht0	[ecx + SSE_PREFETCH_OFFS]
		movdqa	xmm0, [edx+4*16]
		movdqa	xmm1, [edx+5*16]
		movdqa	xmm2, [edx+6*16]
		movdqa	xmm3, [edx+7*16]
		movdqa	[ecx+4*16], xmm0
		movdqa	[ecx+5*16], xmm1
		movdqa	[ecx+6*16], xmm2
		movdqa	[ecx+7*16], xmm3

		lea		edx, [edx + 128]
		lea		ecx, [ecx + 128]
		jnz		copy_prefetch_a

		AND		eax, 127
		jmp		copy_127_a

	////////////////////////////////////////////////////////////////////////////
		// eax >= cpu_info.sse_nt_size.
		// cpu_info.sse_type < SSE_SSSE3. Used with aligned/unaligned src.

		// http://www.intel.com/Assets/PDF/manual/248966.pdf
		//	Intel? 64 and IA-32 Architectures Optimization Reference Manual. Order Number: 248966-022 September 2010.
		//	7.7.2.7 Using 16-byte Streaming Stores and Hardware Prefetch.
//__copy_nt_block_u
	ALIGN_16
	copy_nt_block_u:
		test	byte ptr [edx + ebx+0*128], 0
		test	byte ptr [edx + ebx+1*128], 0
		test	byte ptr [edx + ebx+2*128], 0
		test	byte ptr [edx + ebx+3*128], 0
		test	byte ptr [edx + ebx+4*128], 0
		test	byte ptr [edx + ebx+5*128], 0
		test	byte ptr [edx + ebx+6*128], 0
		test	byte ptr [edx + ebx+7*128], 0

		add		ebx, 8*128
		cmp		ebx, SSE_BLOCK_SIZE
		jb		copy_nt_block_u

		shr	ebx, 7

	ALIGN_16
	copy_nt_u:
		dec	ebx

		movdqu	xmm0, [edx+0*16]
		movdqu	xmm1, [edx+1*16]
		movdqu	xmm2, [edx+2*16]
		movdqu	xmm3, [edx+3*16]
		movntdq	[ecx+0*16], xmm0
		movntdq	[ecx+1*16], xmm1
		movntdq	[ecx+2*16], xmm2
		movntdq	[ecx+3*16], xmm3

		movdqu	xmm0, [edx+4*16]
		movdqu	xmm1, [edx+5*16]
		movdqu	xmm2, [edx+6*16]
		movdqu	xmm3, [edx+7*16]
		movntdq	[ecx+4*16], xmm0
		movntdq	[ecx+5*16], xmm1
		movntdq	[ecx+6*16], xmm2
		movntdq	[ecx+7*16], xmm3

		lea		edx, [edx + 128]
		lea		ecx, [ecx + 128]
		jnz		copy_nt_u

		sub		eax, SSE_BLOCK_SIZE
		cmp		eax, SSE_BLOCK_SIZE
		jae		copy_nt_block_u

	copy_nt_last_u0:
		mov		ebx, eax
		shr		ebx, 7
		jz		copy_nt_end_u

	copy_nt_last_u:
		prefetchnta	[edx+4*128]
		dec		ebx

		movdqu	xmm0, [edx+0*16]
		movdqu	xmm1, [edx+1*16]
		movdqu	xmm2, [edx+2*16]
		movdqu	xmm3, [edx+3*16]
		movntdq	[ecx+0*16], xmm0
		movntdq	[ecx+1*16], xmm1
		movntdq	[ecx+2*16], xmm2
		movntdq	[ecx+3*16], xmm3

		movdqu	xmm0, [edx+4*16]
		movdqu	xmm1, [edx+5*16]
		movdqu	xmm2, [edx+6*16]
		movdqu	xmm3, [edx+7*16]
		movntdq	[ecx+4*16], xmm0
		movntdq	[ecx+5*16], xmm1
		movntdq	[ecx+6*16], xmm2
		movntdq	[ecx+7*16], xmm3

		lea		edx, [edx + 128]
		lea		ecx, [ecx + 128]
		jnz		copy_nt_last_u

	copy_nt_end_u:
		sfence
		AND		eax, 127
		jmp		copy_127_u

	////////////////////////////////////////////////////////////////////////////
		// eax >= cpu_info.sse_nt_size.
		// cpu_info.sse_type >= SSE_SSSE3.
//__copy_nt_a
	ALIGN_16
	copy_nt_a:
		dec		ebx

		movdqa	xmm0, [edx+0*16]
		movdqa	xmm1, [edx+1*16]
		movdqa	xmm2, [edx+2*16]
		movdqa	xmm3, [edx+3*16]
		movntdq	[ecx+0*16], xmm0
		movntdq	[ecx+1*16], xmm1
		movntdq	[ecx+2*16], xmm2
		movntdq	[ecx+3*16], xmm3

		movdqa	xmm0, [edx+4*16]
		movdqa	xmm1, [edx+5*16]
		movdqa	xmm2, [edx+6*16]
		movdqa	xmm3, [edx+7*16]
		movntdq	[ecx+4*16], xmm0
		movntdq	[ecx+5*16], xmm1
		movntdq	[ecx+6*16], xmm2
		movntdq	[ecx+7*16], xmm3

		lea		edx, [edx + 128]
		lea		ecx, [ecx + 128]
		jnz		copy_nt_a

		sfence
		AND		eax, 127
		jmp		copy_127_a

	////////////////////////////////////////////////////////////////////////////
//__copy_nt_avx_a
	ALIGN_16
	copy_nt_avx_a:
		dec		ebx
/*
		vmovdqa		ymm0, [edx+0*32]
		vmovdqa		ymm1, [edx+1*32]
		vmovdqa		ymm2, [edx+2*32]
		vmovdqa		ymm3, [edx+3*32]
		vmovntdq	[ecx+0*32], ymm0
		vmovntdq	[ecx+1*32], ymm1
		vmovntdq	[ecx+2*32], ymm2
		vmovntdq	[ecx+3*32], ymm3
*/
		_VMOVDQA_0(0)
		_VMOVDQA(1, 1*32)
		_VMOVDQA(2, 2*32)
		_VMOVDQA(3, 3*32)
		_VMOVNTDQ_0(0)
		_VMOVNTDQ(1*32, 1)
		_VMOVNTDQ(2*32, 2)
		_VMOVNTDQ(3*32, 3)

		lea		edx, [edx + 128]
		lea		ecx, [ecx + 128]
		jnz		copy_nt_avx_a

		sfence
		AND		eax, 127
		jmp		copy_127_a

	////////////////////////////////////////////////////////////////////////////
		// Copy the last eax 0..127 bytes.
		// Jump here after all copy_no_prefetch_*/copy_prefetch_*/copy_nt_* loops.
//__copy_127_u
	ALIGN_16
	copy_127_u:
#ifndef JMP_TAB_SIZE_32
		test	eax, 64			//bytes to copy
		jz		copy_127_32_u
		movdqu	xmm0, [edx+0*16]
		movdqu	xmm1, [edx+1*16]
		movdqu	xmm2, [edx+2*16]
		movdqu	xmm3, [edx+3*16]
		movdqa	[ecx+0*16], xmm0
		movdqa	[ecx+1*16], xmm1
		movdqa	[ecx+2*16], xmm2
		movdqa	[ecx+3*16], xmm3
		add		edx, 64
		add		ecx, 64
	copy_127_32_u:
		test	eax, 32
		jz		copy_127_16_u
		movdqu	xmm0, [edx+0*16]
		movdqu	xmm1, [edx+1*16]
		movdqa	[ecx+0*16], xmm0
		movdqa	[ecx+1*16], xmm1
		add		edx, 32
		add		ecx, 32
	copy_127_16_u:
		test	eax, 16
		jz		copy_127_end_u
		movdqu	xmm0, [edx+0*16]
		movdqa	[ecx+0*16], xmm0
		add		edx, 16
		add		ecx, 16

	copy_127_end_u:
		AND		eax, 15
		mov		ebx, [esp + 4]
		jmp		dword ptr [cpu_info.copy_jmp_tab + eax * 4]
#else
		mov		ebx, [esp + 4]

		cmp		eax, 96
		jae		copy_127_96_u
		cmp		eax, 64
		jae		copy_127_64_u
		cmp		eax, 32
		jae		copy_127_32_u

		jmp		dword ptr [cpu_info.copy_jmp_tab + eax * 4]

	copy_127_32_u:
		movdqu	xmm0, [edx+0*16]
		movdqu	xmm1, [edx+1*16]
		movdqa	[ecx+0*16], xmm0
		movdqa	[ecx+1*16], xmm1
		add		edx, 32
		add		ecx, 32
		jmp		dword ptr [cpu_info.copy_jmp_tab - 32 * 4 + eax * 4]

	copy_127_64_u:
		movdqu	xmm0, [edx+0*16]
		movdqu	xmm1, [edx+1*16]
		movdqu	xmm2, [edx+2*16]
		movdqu	xmm3, [edx+3*16]
		movdqa	[ecx+0*16], xmm0
		movdqa	[ecx+1*16], xmm1
		movdqa	[ecx+2*16], xmm2
		movdqa	[ecx+3*16], xmm3
		add		edx, 64
		add		ecx, 64
		jmp		dword ptr [cpu_info.copy_jmp_tab - 64 * 4 + eax * 4]

	copy_127_96_u:
		movdqu	xmm0, [edx+0*16]
		movdqu	xmm1, [edx+1*16]
		movdqu	xmm2, [edx+2*16]
		movdqu	xmm3, [edx+3*16]
		movdqu	xmm4, [edx+4*16]
		movdqu	xmm5, [edx+5*16]
		movdqa	[ecx+0*16], xmm0
		movdqa	[ecx+1*16], xmm1
		movdqa	[ecx+2*16], xmm2
		movdqa	[ecx+3*16], xmm3
		movdqa	[ecx+4*16], xmm4
		movdqa	[ecx+5*16], xmm5
		add		edx, 96
		add		ecx, 96
		jmp		dword ptr [cpu_info.copy_jmp_tab - 96 * 4 + eax * 4]
#endif //JMP_TAB_SIZE_32

	////////////////////////////////////////////////////////////////////////////
	ALIGN_16
	copy_127_a:
		test	eax, 64
		jz		copy_127_32_a
		movdqa	xmm0, [edx+0*16]
		movdqa	xmm1, [edx+1*16]
		movdqa	xmm2, [edx+2*16]
		movdqa	xmm3, [edx+3*16]
		movdqa	[ecx+0*16], xmm0
		movdqa	[ecx+1*16], xmm1
		movdqa	[ecx+2*16], xmm2
		movdqa	[ecx+3*16], xmm3
		add		edx, 64
		add		ecx, 64
	copy_127_32_a:				//jump here from copy_no_prefetch_a0
		test	eax, 32
		jz		copy_127_16_a
		movdqa	xmm0, [edx+0*16]
		movdqa	xmm1, [edx+1*16]
		movdqa	[ecx+0*16], xmm0
		movdqa	[ecx+1*16], xmm1
		add		edx, 32
		add		ecx, 32
	copy_127_16_a:
#ifndef JMP_TAB_SIZE_32
		test	eax, 16
		jz		copy_127_end_a
		movdqa	xmm0, [edx+0*16]
		movdqa	[ecx+0*16], xmm0
		add		edx, 16
		add		ecx, 16

	copy_127_end_a:
		AND		eax, 15
#else
		AND		eax, 31
#endif //JMP_TAB_SIZE_32
		mov		ebx, [esp + 4]
		jmp		dword ptr [cpu_info.copy_jmp_tab + eax * 4]
	}
} //memcpy_sse_x

#else
	#define memcpy_sse(dest, src, size) \
		memcpy(dest, src, size)
#endif //__VC_GC_x86

#undef COPY_RET
#undef _PALIGNR
#undef C64_PREFETCH_R_no_pref
#undef C64_PREFETCH_W_no_pref
#undef C64_PREFETCH_R_pref
#undef C64_PREFETCH_W_pref
#undef C64_PREFETCH_R_nt
#undef C64_PREFETCH_W_nt
#undef C64_STORE_no_pref
#undef C64_STORE_pref
#undef C64_STORE_nt
#undef C64_SFENCE_no_pref
#undef C64_SFENCE_pref
#undef C64_SFENCE_nt
#undef C64_SIZE_no_pref
#undef C64_SIZE_pref
#undef C64_SIZE_nt
#undef COPY_64
#undef COPY_64__4
#undef COPY_64__12
#undef COPY_64__8
#undef COPY_64__1_15
#undef COPY_64x__1_15

//__mem_alloc
//*****************************************
void * mem_alloc(size_t size, size_t align)
//*****************************************
{
	size_t	mem0, mem1;

//	return malloc(size);

	if (!size)
		return NULL;

	if (align < sizeof(void *))
		align = sizeof(void *);

	if (align & (align - 1))	//align is not 2^x
		return NULL;

	// We assume mem0 is at least sizeof(void *) aligned (to save mem0).
	mem0 = (size_t)malloc(size + align);

	if (!mem0)
		return NULL;

	mem1 = (mem0 + align) & ~(align - 1);

	*(size_t *)(mem1 - sizeof(void *)) = mem0;	//save allocated ptr for mem_free()

	return (void *)mem1;
} //mem_alloc

//***********************
void mem_free(void * ptr)
//***********************
{
//	free(ptr);
//	return;

	if (ptr)
		free(((void **)ptr)[-1]);
}

#define __RAND_MAX		0x7FFF
#define __RAND_MAX_1	(__RAND_MAX + 1)
u32_t	rand_seed = 0;

//*******************
__inline int __rand()
//*******************
{
	rand_seed = rand_seed * 214013L + 2531011L;
	return (rand_seed >> 16) & __RAND_MAX;
}

void __srand(u32_t seed)
{
	rand_seed = seed;
	__rand();
	__rand();
}

//****************************
__inline int get_rand(int Mod)
//****************************
// Return rand int (0 <= x < Mod).
{
	if (Mod <= __RAND_MAX_1)
		return __rand() * Mod / __RAND_MAX_1;
	else
	{
		double	r0 = (double)__rand();
		double	r1 = (double)__rand() * __RAND_MAX_1;

		return (int)((r0 + r1) / ((double)__RAND_MAX_1 * __RAND_MAX_1) * Mod);
	}
}

#define TSC_DECL \
	int		tsc1 = 0, tsc2 = 0, min_tsc = 0, max_tsc = 0; \
	int		rdtsc_tsc = 0;

#if !defined(ONLINE_JUDGE)
// rdtsc must be serialized with mfence on AMD and with lfence on Intel? Both are sse2 ops.
// cpuid can also be used for this purpose, but it is too slow.
#if __VC
	#define RDTSC(tsc) \
	{ \
		__asm sfence \
		__asm rdtsc \
		__asm sfence \
		__asm mov	tsc, eax \
	}
#elif __GC
	#define RDTSC(tsc) \
		__asm volatile \
		( \
			"sfence\n" \
			"rdtsc\n" \
			"sfence\n" \
			: "=a"(tsc) \
			: \
			: "edx" \
		);
#endif

#define TSC_INIT \
{ \
	min_tsc = 0x7FFFFFFF; \
	max_tsc = 0; \
}

#define TSC_START \
	RDTSC(tsc1)

#define TSC_END \
{ \
	RDTSC(tsc2) \
\
	tsc2 -= (tsc1 + rdtsc_tsc); \
	if (tsc2 < min_tsc) \
		min_tsc = tsc2; \
	if (tsc2 > max_tsc) \
		max_tsc = tsc2; \
}
#else
	#define RDTSC(tsc)
	#define TSC_INIT
	#define TSC_START
	#define TSC_END
#endif //ONLINE_JUDGE

//************************************
char * get_tsc_str(int tsc, int rep_n)
//************************************
{
	static char	tsc_str[20];
	double	tsc1, tsc2;
	int i, i1;

	tsc1 = (double)tsc / rep_n;
	for (i = 0, tsc2 = tsc1; tsc2 >= 1; i++, tsc2 /= 10)
		;
	if (i <= 2)	//1..99
		sprintf(tsc_str, "%1.1f", tsc1);
	else if (i <= 4)
		sprintf(tsc_str, "%1.0f", tsc1);
	else
	{
		i1 = i - 4;
		for (i = 0; i < i1; i++, tsc1 /= 10)
			;
		sprintf(tsc_str, "%1.0fe%d", tsc1, i1);
	}

//	p("get_tsc_str: tsc=%d, rep_n=%d, %s", tsc, rep_n, tsc_str);
	return tsc_str;
} //get_tsc_str

//*****************
int get_rdtsc_tsc()
//*****************
{
	TSC_DECL
	int		i;

	rdtsc_tsc = 0;
	TSC_INIT
	for (i = 0; i < 100; i++)
	{
		TSC_START
		TSC_END
	}

	return min_tsc;
} //get_rdtsc_tsc

typedef struct
{
	int		sse_tsc;
	int		min_tsc;
	int		max_tsc;
	int		std_tsc;
	int		amd_tsc;
	u32_t	size_sum;
} tsc_t;

int		run_done;
int		error;

//__run_memcpy_buf
//***************************************************************************************
void run_memcpy_buf(u32_t mem_size, u08_t *buf1, u08_t *buf2, tsc_t *tsc, int warmup = 0)
//***************************************************************************************
{
	u32_t	offs1, offs2;
	int		dir;
	int		rep_n, rep_i;
	int		copy_i;
	tsc_t	tsc_save = *tsc;
	TSC_DECL
	int		print_all =
		#ifdef MEM_PRINT_ALL
			1;
		#else
			0;
		#endif

	struct
	{
		u08_t	*src;
		u08_t	*dest;
	} copy[MEM_COPY_N];
	int		copy_n;

	memset(buf1, 1, MEM_BUF_SIZE);
	memset(buf2, 2, MEM_BUF_SIZE);

	rdtsc_tsc = get_rdtsc_tsc();
	rep_n = (warmup) ? 1 : MEM_REPEAT_N;
	__srand(0);

	for (copy_n = 0; copy_n < MEM_COPY_N; copy_n++)
	{
		offs1 = get_rand(MEM_BUF_SIZE - mem_size + 1);
		offs2 = get_rand(MEM_BUF_SIZE - mem_size + 1);
		dir = get_rand(1);	//random copy direction does not change time

		copy[copy_n].src = (dir ? buf1 : buf2) + offs1;
		copy[copy_n].dest = (dir ? buf2 : buf1) + offs2;
	}

	if (!warmup && print_all)
		p("==%d: REPEAT_N=%d, BUF_SIZE=%d, COPY_N=%d, rdtsc_tsc=%d",
			mem_size, MEM_REPEAT_N, MEM_BUF_SIZE, MEM_COPY_N, rdtsc_tsc);

	#ifdef MEM_CONST_SIZE
		#define _MEM_SIZE		MEM_SIZE
	#else
		#define _MEM_SIZE		mem_size
	#endif

	TSC_INIT
	for (rep_i = 0; rep_i < rep_n; rep_i++)
	{
		TSC_START

		for (copy_i = 0; copy_i < MEM_COPY_N; copy_i++)
			memcpy(copy[copy_i].dest, copy[copy_i].src, _MEM_SIZE);

		TSC_END
	}
	tsc->std_tsc += min_tsc;

	if (!warmup && print_all)
		p("  memcpy_std: %s", get_tsc_str(min_tsc, MEM_COPY_N));

	TSC_INIT
	for (rep_i = 0; rep_i < rep_n; rep_i++)
	{
		TSC_START

		for (copy_i = 0; copy_i < MEM_COPY_N; copy_i++)
			memcpy_sse(copy[copy_i].dest, copy[copy_i].src, _MEM_SIZE);

		TSC_END
	}
	tsc->sse_tsc += min_tsc;
	tsc->size_sum += (mem_size ? mem_size : 1) * MEM_COPY_N;

	if (!warmup && print_all)
		p("  memcpy_sse: %s", get_tsc_str(min_tsc, MEM_COPY_N));

	if (warmup)
		*tsc = tsc_save;
} //run_memcpy_buf

//__run_memcpy__
//*************************************************************************************************
void run_memcpy(u32_t mem_size, u08_t *src, u08_t *dest, int dest_offs, tsc_t *tsc, int warmup = 0)
//*************************************************************************************************
{
	int		rep_n, rep_i;
	int		run_n;
	u08_t	*ptr1 = NULL, *ptr2 = NULL;
	int		i = 0;
	tsc_t	tsc_save = *tsc;
	TSC_DECL
	int		print_all =
		#ifdef MEM_PRINT_ALL
			1;
		#else
			0;
		#endif

	#ifdef MEM_CONST_SIZE
		#define _MEM_SIZE	MEM_SIZE
	#else
		#define _MEM_SIZE	mem_size
	#endif

	#define RUN_MEMCPY_1(memcpy_x)	memcpy_x(dest, src, _MEM_SIZE);

	#define RUN_MEMCPY(func, func_str) \
	{ \
		TSC_INIT \
		for (rep_i = 0; rep_i < rep_n; rep_i++) \
		{ \
			if (_MEM_SIZE <= 64 * 1024) \
			{ \
				run_n = 8; \
				TSC_START \
\
				RUN_MEMCPY_1(func) \
				RUN_MEMCPY_1(func) \
				RUN_MEMCPY_1(func) \
				RUN_MEMCPY_1(func) \
\
				RUN_MEMCPY_1(func) \
				RUN_MEMCPY_1(func) \
				RUN_MEMCPY_1(func) \
				RUN_MEMCPY_1(func) \
\
				TSC_END \
			} \
			else if (_MEM_SIZE <= 1024 * 1024) \
			{ \
				run_n = 2; \
				TSC_START \
				RUN_MEMCPY_1(func) \
				RUN_MEMCPY_1(func) \
				TSC_END \
			} \
			else \
			{ \
				run_n = 1; \
				TSC_START \
				RUN_MEMCPY_1(func) \
				TSC_END \
			} \
		} \
		run_done = 1; \
\
		if (!warmup && print_all) \
		{ \
			p("  %s: %s         ..+", func_str, get_tsc_str(min_tsc, run_n)); \
			p("%s", get_tsc_str(max_tsc, run_n)); \
		} \
	} //RUN_MEMCPY

	rdtsc_tsc = get_rdtsc_tsc();
	rep_n = (warmup) ? 1 : MEM_REPEAT_N;

	if (!warmup && print_all)
		p("==%d+%d: REPEAT_N=%d, rdtsc_tsc=%d", mem_size, dest_offs, MEM_REPEAT_N, rdtsc_tsc);

	#ifdef DEBUG_MEM_CHECK
		for (ptr1 = src, ptr2 = dest, i = 0;
			ptr1 < src + mem_size;
			ptr1++, ptr2++, i++)
		{
			if (!(i & 0xFF))
				i = 1;
			*ptr1 = i & 0xFF;
			*ptr2 = 0;
		}
	#endif

	#ifdef USE_MEMCPY_SSE
		RUN_MEMCPY(memcpy_sse, "memcpy_sse")
		tsc->sse_tsc += min_tsc;
	#endif

	#ifdef DEBUG_MEM_CHECK
		for (ptr1 = src, ptr2 = dest;
			(ptr1 < src + mem_size) && (*ptr2 == *ptr1);
			ptr1++, ptr2++)
			;
		if ((ptr1 - src < (ptrdiff_t)mem_size) && !error)
		{
			error = 1;
			p("!!! memcpy_sse: offset=%d, mem_size=%d, dest_offs=%d, (XX<-XX)", ptr1 - src, mem_size, dest_offs);

			#ifdef ONLINE_JUDGE
				tsc = NULL;
				tsc->sse_tsc = 0;
			#endif

			for (i = 0; (ptr1 < src + mem_size) && (i < 16); ptr1++, ptr2++, i++)
				p("(%02X %02X) +", *ptr2, *ptr1);
			p("");
		}
	#endif

	#ifdef USE_MEMCPY_STD
		RUN_MEMCPY(memcpy, "memcpy_std")
		tsc->std_tsc += min_tsc;
	#endif

	tsc->size_sum += (mem_size ? mem_size : 1) * run_n;

	if (warmup)
		*tsc = tsc_save;
} //run_memcpy

//__run_test__
//**************************************
void run_test(u32_t mem_size = MEM_SIZE)
//**************************************
{
	u08_t	*buf1, *buf2;
	u32_t	offs1, offs2;
	tsc_t	tsc;
	u32_t	mem_size_max;
	u32_t	size;
	int		i;
	struct
	{
		cpuid_t	cpu[3];
		char	z;
	} brand;
/*//.
	u32_t	time0 = clock();
	u32_t	dif = cpu_info.cache[1].ways * CLOCKS_PER_SEC / 10;

	while (clock() - time0 < dif)
		;
	return;
*/
	#ifdef MEM_CONST_SIZE
		mem_size = MEM_SIZE;
	#endif

	memset(&brand, 0, sizeof(brand));

	for (i = 0; i < 3; i++)
		cpuid_func(0x80000002 + i, &brand.cpu[i]);

	p("run_test: sse_type=%02X, L1(%dK %d %d) L2(%dK %d %d) L3(%dK %d %d) %s",
		cpu_info.sse_type,
		cpu_info.cache[0].size / 1024, cpu_info.cache[0].line, cpu_info.cache[0].ways,
		cpu_info.cache[1].size / 1024, cpu_info.cache[1].line, cpu_info.cache[1].ways,
		cpu_info.cache[2].size / 1024, cpu_info.cache[2].line, cpu_info.cache[2].ways,
		&brand);

	mem_size_max = mem_size + MEM_SIZE_N - 1;

#ifdef MEM_BUF
	if (mem_size <= 1024)
	{
		memset(&tsc, 0, sizeof(tsc));

		size = MEM_BUF_SIZE;
		buf1 = (u08_t *)mem_alloc(size, 4 * 1024);
		buf2 = (u08_t *)mem_alloc(size, 4 * 1024);
		memset(buf1, 0, size);

		for (size = mem_size; size <= mem_size_max; size += MEM_SIZE_STEP)
		{
			run_memcpy_buf(size, buf1, buf2, &tsc, 1);	//warmup call to get stable timing (no print)
			run_memcpy_buf(size, buf1, buf2, &tsc);
		}

		mem_free(buf1);
		mem_free(buf2);

		p((mem_size_max > mem_size) ? "size(%d..%d) +" : "size(%d) +", mem_size, mem_size_max);
		p("BUF_SIZE=%d, COPY_N=%d", MEM_BUF_SIZE, MEM_COPY_N);
		#if !defined(DEBUG_MEM_NO_TSC)
			p("  std_tsc=%1.3f", (double)tsc.std_tsc / tsc.size_sum);
			p("  sse_tsc=%1.3f        min/max_tsc(%d %d)", (double)tsc.sse_tsc / tsc.size_sum, tsc.min_tsc, tsc.max_tsc);
			p("  std/sse=%1.3f", (tsc.sse_tsc) ? (double)tsc.std_tsc / tsc.sse_tsc : 0);
			tsc.max_tsc
		#endif
	}
#endif //MEM_BUF

	memset(&tsc, 0, sizeof(tsc));

	size = mem_size_max + 8 * 1024;	//+8*1024 for MEM_OFFS_x
	buf1 = (u08_t *)mem_alloc(size, 4 * 1024);	
	buf2 = (u08_t *)mem_alloc(size, 4 * 1024);
	memset(buf1, 0, size);

	for (size = mem_size; size <= mem_size_max; size += MEM_SIZE_STEP)
	{
		if (mem_size_max < 64)
		{
			for (offs1 = MEM_OFFS_2; offs1 < MEM_OFFS_2 + MEM_OFFS_N; offs1 += MEM_OFFS_STEP)
			{
				for (offs2 = MEM_OFFS_2; offs2 < MEM_OFFS_2 + MEM_OFFS_N; offs2 += MEM_OFFS_STEP)
				{
					run_memcpy(size, buf1 + offs1, buf2 + offs2, offs2, &tsc, 1);	//warmup call to get stable timing (no print)
					run_memcpy(size, buf1 + offs1, buf2 + offs2, offs2, &tsc);
				}
			}
		}
		else
		{
			for (offs2 = MEM_OFFS_2; offs2 < MEM_OFFS_2 + MEM_OFFS_N; offs2 += MEM_OFFS_STEP)
			{
				run_memcpy(size, buf1 + MEM_OFFS_1, buf2 + offs2, offs2, &tsc, 1);	//warmup call to get stable timing (no print)
				run_memcpy(size, buf1 + MEM_OFFS_1, buf2 + offs2, offs2, &tsc);		//+MEM_OFFS_1 to avoid offset=4KB+16 cache conflict
			}
		}
	} //for (size

	mem_free(buf1);
	mem_free(buf2);

	p((mem_size_max > mem_size) ? "size(%d..%d, %d) +" : "size(%d) +", mem_size, mem_size_max, MEM_SIZE_STEP);
	p((MEM_OFFS_N > 1) ? "offs(%d..%d, %d)" : "offs(%d)", MEM_OFFS_2, MEM_OFFS_2 + MEM_OFFS_N - 1, MEM_OFFS_STEP);
	#if !defined(DEBUG_MEM_NO_TSC)
		p("  std_tsc=%1.3f", (double)tsc.std_tsc / tsc.size_sum);
		p("  sse_tsc=%1.3f        min/max_tsc(%d %d)", (double)tsc.sse_tsc / tsc.size_sum, tsc.min_tsc, tsc.max_tsc);
		p("  std/sse=%1.3f", (tsc.sse_tsc) ? (double)tsc.std_tsc / tsc.sse_tsc : 0);
	#endif
} //run_test

//********
int main()
//********
{
	run_test();
	return 0;
} //main

/*
__cpu_info
__memcpy_sse__
__get_cpu_info
__COPY_64_vc
__memcpy_sse_x_vc
__memcpy_entry
__align_16
__COPY_64__1_15
__copy_no_prefetch_a
__copy_prefetch_a
__copy_nt_block_u
__copy_nt_a
__copy_80_u
__copy_127_u

__run_memcpy_buf
__run_memcpy__
__run_test__
*/


