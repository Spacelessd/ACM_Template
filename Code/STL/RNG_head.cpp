//
// rng_test.cpp
// random number generator

	#define ONLINE_JUDGE
//	#define DEBUG_TOPCODER
//	#define DEBUG_DIEHARD_FILE
//	#define DEBUG_TESTU01
//	#define DEBUG_BOOST
//	#define DEBUG_PRINT_NORMAL
	#define DEBUG_HIGH_PRIORITY
//	#define DEBUG_CHECK
//	#define DEBUG_GAUSSIAN
	#define DEBUG_ARRAY_N		(4000)	//array[DEBUG_ARRAY_N]
	#define DEBUG_REP_RAND_N	(250 * 1000 * 1000)//.
//	#define DEBUG_REP_RAND_N	(10 * 1000 * 1000)
	#define DEBUG_REP_ARRAY_N	(DEBUG_REP_RAND_N / DEBUG_ARRAY_N)
	#define DEBUG_ARRAY			//get_array()
	#define DEBUG_NORMAL		//get_normal()

	#define RNG_USE_SSE2
//	#define RNG_APPROX_RAND

	#define RNG_RANGE_CONST		6	//65
//	#define RNG_RANGE_CONST		(1u << 16)
//	#define RNG_RANGE_CONST		555000
//	#define RNG_RANGE			RNG_RANGE_CONST
	#define RNG_RANGE			rng_range
	// If both RNG_MIN_VAL and RNG_MAX_VAL defined, call funcs with (RNG_MIN_VAL, RNG_MAX_VAL).
	#define RNG_MIN_VAL_CONST	1
//	#define RNG_MIN_VAL			RNG_MIN_VAL_CONST
	#define RNG_MIN_VAL			rng_min_val
//	#define RNG_MAX_VAL			(RNG_MIN_VAL + RNG_RANGE - 1)
//	#define RNG_ARRAY_T			u32_t
//	#define RNG_ARRAY_T			char
	#define RNG_ARRAY_T			double
//	#define RNG_ARRAY_T			float

	#define RNG_FUNC			get_uint
//	#define RNG_FUNC			get_int
//	#define RNG_FUNC			get_double
//	#define RNG_FUNC			get_float
//	#define RNG_FUNC			get_bool

#pragma warning(disable: 4035)	//no return value
#pragma warning(disable: 4068)	//unknown pragma
#pragma warning(disable: 4996)	//the POSIX name for this item is deprecated
#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE

void p(const char * format, ...);//.

#if !defined(ONLINE_JUDGE)
#include "rng_class.h"
#endif

#if defined(WIN32)
	#undef ONLINE_JUDGE
#endif

#pragma once

#ifndef RNG_CLASS_H
#define RNG_CLASS_H

#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

#if (_MSC_VER && ((_M_IX86_FP >= 2) || defined(_M_X64))) ||	/*arch:SSE2 or x86-64*/ \
	(__GNUC__ && __SSE2__)	/*-msse2 (default for x86-64)*/
	#define RNG_USE_SSE2
#endif

#ifdef RNG_USE_SSE2
	#include <emmintrin.h>
#endif

//***********
namespace rng
//***********
{

#ifdef _MSC_VER
	typedef __int64				i64_t;
	typedef unsigned __int64	u64_t;
#else
	typedef long long			i64_t;
	typedef unsigned long long	u64_t;
#endif
typedef int						i32_t;
typedef unsigned int			u32_t;
typedef short					i16_t;
typedef unsigned short			u16_t;
typedef unsigned char			u8_t;

#ifdef RNG_USE_SSE2
union x128_t
{
	__m128i	i128;
	__m128d	d128;
	__m128	f128;
	double	d64[2];
	u32_t	u32[4];
	i32_t	i32[4];
	u16_t	u16[8];
	u8_t	u8[16];
};
#endif

union x32_t
{
	u32_t	u32;
	u16_t	u16[2];
	u8_t	u8[4];
};

#ifdef _MSC_VER
	#define FORCE_INLINE		__inline	//__forceinline
#elif __GNUC__
	#define FORCE_INLINE		__inline	//__attribute__((always_inline))
#else
	#define FORCE_INLINE		__inline
#endif

#define RNG_POW_2(n)			(1. / ((u64_t)1 << n))
#define LIST_16(n)				n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n,

static const char	bit_n_tab[256] =
{
	0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
	LIST_16(5) LIST_16(6) LIST_16(6) LIST_16(7) LIST_16(7) LIST_16(7) LIST_16(7)
	LIST_16(8) LIST_16(8) LIST_16(8) LIST_16(8) LIST_16(8) LIST_16(8) LIST_16(8) LIST_16(8)
};

//__get_bit_n
//************************************
static __inline int get_bit_n(u32_t x)
//************************************
// Return the number of significant bits of x.
// Based on: http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogLookup
{
	u32_t	h, t;

	return (h = (u32_t)x >> 16) ?
		(t = h >> 8) ? 24 + bit_n_tab[t] : 16 + bit_n_tab[h] :
		(t = (u32_t)x >> 8) ? 8 + bit_n_tab[t] : bit_n_tab[x];
}

#ifdef RNG_USE_SSE2
//*********************************************************
static FORCE_INLINE __m128i mul128_hi(__m128i x, __m128i y)
//*********************************************************
// Return four 32-bit numbers: ((u64_t)x[] * y[]) >> 32.
// y == (y1, y1, y1, y1).
{
	__m128i	res_2_0 = _mm_mul_epu32(x, y);	//x[2]*y[2], x[0]*y[0]
	__m128i	res_3_1 = _mm_mul_epu32(_mm_srli_epi64(x, 32), y);	//x[3]*y[2], x[1]*y[0]

	res_2_0 = _mm_srli_epi64(res_2_0, 32);
	res_3_1 = _mm_slli_epi64(_mm_srli_epi64(res_3_1, 32), 32);
	return _mm_or_si128(res_2_0, res_3_1);
}

//******************************************************
static FORCE_INLINE __m128i mul128(__m128i x, __m128i y)
//******************************************************
// Return four 32-bit numbers: (u32_t)(x[] * y[]).
// y == (y1, y1, y1, y1).
{
	__m128i	res_2_0 = _mm_mul_epu32(x, y);	//x[2]*y[2], x[0]*y[0]
	__m128i	res_3_1 = _mm_mul_epu32(_mm_srli_epi64(x, 32), y);	//x[3]*y[2], x[1]*y[0]

	res_2_0 = _mm_srli_epi64(_mm_slli_epi64(res_2_0, 32), 32);
	res_3_1 = _mm_slli_epi64(res_3_1, 32);
	return _mm_or_si128(res_2_0, res_3_1);
}
#endif //RNG_USE_SSE2

//__div_class
//*************
class div_class
//*************
{
	u32_t	m_mul;
	u8_t	m_log;
	u8_t	m_add;

#ifdef RNG_USE_SSE2
	__m128i	m_mul4;
	__m128i	m_log4;
	__m128i	m_divisor4;
#endif

public:
	u32_t	m_max_num;	//2^32 / (m_divisor^m_div_n) * (m_divisor^m_div_n) (> 7/8 * 2^32)
	u32_t	m_divisor;	//to calculate remainder
	// Number of random [0..range) numbers we get dividing random [0..m_max_num) number by range.
	int		m_div_n;

	//**********************
	div_class(u32_t divisor)
	//**********************
	// divisor cannot be 2^n or zero.
	{
		m_log = get_bit_n(divisor) - 1;
		u64_t	pow2 = (u64_t)1 << (m_log + 32);
		m_mul = (u32_t)(pow2 / divisor);
		u32_t	rem = (u32_t)(pow2 - (u64_t)m_mul * divisor);

		if (divisor - rem >= (1u << m_log))
		{
			m_mul *= 2;
			if ((rem * 2 >= divisor) || (rem * 2 < rem))
				m_mul++;
			m_add = 1;
		}
		else
			m_add = 0;

		m_mul++;

		u64_t	divisor_pow64;
		u32_t	divisor_pow = divisor;
		m_div_n = 1;

		// We always use (m_div_n == 1) if gc and !SSE because it is faster.
#if defined(_MSC_VER) || defined(RNG_USE_SSE2)
		while (1)
		{
			divisor_pow64 = (u64_t)divisor_pow * divisor;
			if (divisor_pow64 > 0x20000000)
				break;

			divisor_pow = (u32_t)divisor_pow64;
			m_div_n++;

			#ifdef RNG_USE_SSE2
				if (m_div_n >= 2)
					break;
			#endif
		}
#endif

		// For little divisor: (m_max_num > 7/8 * 2^32).
		// In worst case (divisor > 2^31): (m_max_num > 1/2 * 2^32).
		m_max_num = (u32_t)(((u64_t)1 << 32) / divisor_pow * divisor_pow);
		m_divisor = divisor;
//		p("m_div_n=%d, m_max_num=%08X", m_div_n, m_max_num);

#ifdef RNG_USE_SSE2
		m_mul4 = _mm_set1_epi32(m_mul);
		m_log4 = _mm_set_epi32(0, 0, 0, m_log);
		m_divisor4 = _mm_set1_epi32(divisor);
#endif
	} //div_class

	//__div
	//*************************************************
	FORCE_INLINE u32_t div(u32_t num, u32_t &rem) const
	//*************************************************
	// Return result (q, rem) of (num / m_divisor).
	{
//		rem = num % m_divisor;
//		return num / m_divisor;

		u32_t	q = u32_t(((u64_t)num * m_mul) >> 32);

		if (m_add)
			q = ((num - q) >> 1) + q;

		q >>= m_log;
		rem = num - q * m_divisor;
		return q;
	} //div

#ifdef RNG_USE_SSE2
	//**********************************************************
	FORCE_INLINE __m128i div128(__m128i num, __m128i &rem) const
	//**********************************************************
	// Return result (q, rem) of (num / m_divisor4).
	{
		__m128i	q = mul128_hi(num, m_mul4);

		if (m_add)
//			q = ((num - q) >> 1) + q;
			q = _mm_add_epi32(_mm_srli_epi32(_mm_sub_epi32(num, q), 1), q);

//		q >>= m_log;
		q = _mm_srl_epi32(q, m_log4);

//		rem = num - q * m_divisor;
		rem = _mm_sub_epi32(num, mul128(q, m_divisor4));
		return q;
	} //div128
#endif //RNG_USE_SSE2
}; //class div_class

#define ZIG_TAB_N		128
#define ZIG_TAIL_START	3.442619855899
#define ZIG_V			9.91256303526217e-3	//print_normal()

static const i32_t zig_k[ZIG_TAB_N] =
{
 1991057938, 0, 1611602771, 1826899878, 1918584482, 1969227037, 2001281515, 2023368125,  
 2039498179, 2051788381, 2061460127, 2069267110, 2075699398, 2081089314, 2085670119, 2089610331,  
 2093034710, 2096037586, 2098691595, 2101053571, 2103168620, 2105072996, 2106796166, 2108362327,  
 2109791536, 2111100552, 2112303493, 2113412330, 2114437283, 2115387130, 2116269447, 2117090813,  
 2117856962, 2118572919, 2119243101, 2119871411, 2120461303, 2121015852, 2121537798, 2122029592,  
 2122493434, 2122931299, 2123344971, 2123736059, 2124106020, 2124456175, 2124787725, 2125101763,  
 2125399283, 2125681194, 2125948325, 2126201433, 2126441213, 2126668298, 2126883268, 2127086657,  
 2127278949, 2127460589, 2127631985, 2127793506, 2127945490, 2128088244, 2128222044, 2128347141,  
 2128463758, 2128572095, 2128672327, 2128764606, 2128849065, 2128925811, 2128994934, 2129056501,  
 2129110560, 2129157136, 2129196237, 2129227847, 2129251929, 2129268426, 2129277255, 2129278312,  
 2129271467, 2129256561, 2129233410, 2129201800, 2129161480, 2129112170, 2129053545, 2128985244,  
 2128906855, 2128817916, 2128717911, 2128606255, 2128482298, 2128345305, 2128194452, 2128028813,  
 2127847342, 2127648860, 2127432031, 2127195339, 2126937058, 2126655214, 2126347546, 2126011445,  
 2125643893, 2125241376, 2124799783, 2124314271, 2123779094, 2123187386, 2122530867, 2121799464,  
 2120980787, 2120059418, 2119015917, 2117825402, 2116455471, 2114863093, 2112989789, 2110753906,  
 2108037662, 2104664315, 2100355223, 2094642347, 2086670106, 2074676188, 2054300022, 2010539237,  
}; //zig_k
 
static const double zig_w[ZIG_TAB_N] =
{
 1.729040521542798e-9, 1.268092844700203e-10, 1.689751777318408e-10, 1.986268844247869e-10,  
 2.223243179249965e-10, 2.424493612544867e-10, 2.601613190063183e-10, 2.761198871170374e-10,  
 2.907396281771578e-10, 3.042997041437641e-10, 3.169979521395409e-10, 3.289802052711289e-10,  
 3.403573812183390e-10, 3.512160221366455e-10, 3.616250995056502e-10, 3.716405763495964e-10,  
 3.813085643110583e-10, 3.906675680994868e-10, 3.997501186997677e-10, 4.085839861598427e-10,  
 4.171930964016051e-10, 4.255982353459250e-10, 4.338175973925498e-10, 4.418672181252873e-10,  
 4.497613196266569e-10, 4.575125889458817e-10, 4.651324048139998e-10, 4.726310238481164e-10,  
 4.800177347232556e-10, 4.873009867798738e-10, 4.944884980538964e-10, 5.015873466119608e-10,  
 5.086040482424553e-10, 5.155446229195383e-10, 5.224146519706308e-10, 5.292193275006298e-10,  
 5.359634953312882e-10, 5.426516924820611e-10, 5.492881800346013e-10, 5.558769720760764e-10,  
 5.624218612983579e-10, 5.689264417346542e-10, 5.753941290375594e-10, 5.818281786390891e-10,  
 5.882317020812163e-10, 5.946076817624988e-10, 6.009589843108295e-10, 6.072883727627878e-10,  
 6.135985177054128e-10, 6.198920075155914e-10, 6.261713578149422e-10, 6.324390202435394e-10,  
 6.386973906435728e-10, 6.449488167337375e-10, 6.511956053464690e-10, 6.574400292928591e-10,  
 6.636843339139868e-10, 6.699307433723294e-10, 6.761814667327437e-10, 6.824387038791130e-10,  
 6.887046513100727e-10, 6.949815078551661e-10, 7.012714803513149e-10, 7.075767893185553e-10,  
 7.138996746735843e-10, 7.202424015197480e-10, 7.266072660527041e-10, 7.329966016220859e-10,  
 7.394127849911223e-10, 7.458582428383534e-10, 7.523354585483483e-10, 7.588469793417648e-10,  
 7.653954237992259e-10, 7.719834898384397e-10, 7.786139632098378e-10, 7.852897265828994e-10,  
 7.920137693034095e-10, 7.987891979113533e-10, 8.056192475202168e-10, 8.125072941713966e-10,  
 8.194568682925743e-10, 8.264716694066623e-10, 8.335555822587843e-10, 8.407126945532989e-10,  
 8.479473165218370e-10, 8.552640025776092e-10, 8.626675753519361e-10, 8.701631524574422e-10,  
 8.777561763803282e-10, 8.854524479737276e-10, 8.932581641080367e-10, 9.011799601356603e-10,  
 9.092249579511379e-10, 9.174008205786003e-10, 9.257158144040124e-10, 9.341788803988470e-10,  
 9.427997159666312e-10, 9.515888693998881e-10, 9.605578493831251e-10, 9.697192525453942e-10,  
 9.790869127908899e-10, 9.886760770687722e-10, 9.985036134535423e-10, 1.008588258991447e-9,  
 1.018950916862138e-9, 1.029615015200667e-9, 1.040606943699987e-9, 1.051956589272804e-9,  
 1.063697999193087e-9, 1.075870210164582e-9, 1.088518296060728e-9, 1.101694707813504e-9,  
 1.115461009559716e-9, 1.129890161349322e-9, 1.145069570006724e-9, 1.161105242602235e-9,  
 1.178127560945613e-9, 1.196299505385076e-9, 1.215828698329556e-9, 1.236985629080497e-9,  
 1.260132330060853e-9, 1.285769684420515e-9, 1.314620184967718e-9, 1.347783956221086e-9,  
 1.387063531506704e-9, 1.435740319181638e-9, 1.500865903022299e-9, 1.603094793809112e-9,  
}; //zig_w
 
static const double zig_f[ZIG_TAB_N] =
{
 1.000000000000000, 0.963599693127090, 0.936282681685063, 0.913043647971743,  
 0.892281650784029, 0.873243048910072, 0.855500607869453, 0.838783605295992,  
 0.822907211381411, 0.807738294682963, 0.793177011771307, 0.779146085929690,  
 0.765584173897707, 0.752441559174613, 0.739677243672649, 0.727256918344187,  
 0.715151507410500, 0.703336099016160, 0.691789143436677, 0.680491840997336,  
 0.669427667348892, 0.658582000050090, 0.647941821110224, 0.637495477335044,  
 0.627232485249929, 0.617143370818882, 0.607219536625122, 0.597453150944518,  
 0.587837054434708, 0.578364681119764, 0.569029991067952, 0.559827412704088,  
 0.550751793114606, 0.541798355025426, 0.532962659383837, 0.524240572672985,  
 0.515628238244003, 0.507122051075570, 0.498718635470981, 0.490414825283845,  
 0.482207646329486, 0.474094300693018, 0.466072152689457, 0.458138716267873,  
 0.450291643682040, 0.442528715275469, 0.434847830249992, 0.427246998304997,  
 0.419724332049575, 0.412278040102662, 0.404906420807224, 0.397607856493874,  
 0.390380808237316, 0.383223811055902, 0.376135469510564, 0.369114453664473,  
 0.362159495369318, 0.355269384847918, 0.348442967546327, 0.341679141231551,  
 0.334976853313590, 0.328335098372851, 0.321752915875986, 0.315229388065012,  
 0.308763638006182, 0.302354827786484, 0.296002156846934, 0.289704860442960,  
 0.283462208223233, 0.277273502919189, 0.271138079138385, 0.265055302255590,  
 0.259024567396205, 0.253045298507326, 0.247116947512322, 0.241238993545440,  
 0.235410942263479, 0.229632325232116, 0.223902699385009, 0.218221646554306,  
 0.212588773071730, 0.207003709439927, 0.201466110074314, 0.195975653116278,  
 0.190532040319137, 0.185134997008992, 0.179784272123296, 0.174479638330790,  
 0.169220892237365, 0.164007854683421, 0.158840371139479, 0.153718312208182,  
 0.148641574242342, 0.143610080090628, 0.138623779984595, 0.133682652583440,  
 0.128786706195943, 0.123935980202868, 0.119130546707651, 0.114370512448866,  
 0.109656021014840, 0.104987255409421, 0.100364441028656, 0.095787849121732,  
 0.091257800826830, 0.086774671894780, 0.082338898242236, 0.077950982513973,  
 0.073611501884113, 0.069321117393578, 0.065080585213068, 0.060890770348040,  
 0.056752663481050, 0.052667401903051, 0.048636295859868, 0.044660862200491,  
 0.040742868074444, 0.036884388786656, 0.033087886146226, 0.029356317440007,  
 0.025693291935934, 0.022103304615927, 0.018592102737011, 0.015167298010547,  
 0.011839478657885, 0.008624484412860, 0.005548995220771, 0.002669629083881,  
}; //zig_f
 
//*************
class rng_class
//*************
{
	u32_t	m_rand32[4];
	u32_t	m_bool_rand;
	int		m_bool_bit_n;

#ifdef RNG_USE_SSE2
	__m128i	m_rand128[4];

	double	m_double_32_4[4];
	int		m_double_32_i;
#endif

#ifdef DEBUG_GAUSSIAN
 	bool	m_have_gaussian;
 	double	m_gaussian;
#endif

public:
	//__rng_class
	//***********************
	rng_class(u32_t seed = 0)
	//***********************
	// This compiler defaults are available:
	//	rng_class x;
	//	rng_class y(x);
	//	y = x;
	{
		set_seed(seed);
	}

	//__set_seed
	//***************************
	void set_seed(u32_t seed = 0)
	//***************************
	{
		const u32_t	seed32[4] = {123456789, 362436069, 521288629, 88675123};
		const u32_t	A = 1103515245;
		const u32_t	B = 12345;
		u32_t	s;
		int		i;

		m_bool_bit_n = 0;

		s = seed;
		for (i = -4; i < 4; i++)
		{
			// s is (odd, even, odd, even,...).
			s = s * A + B;

			if (i >= 0)
				m_rand32[i & 3] = seed32[i & 3] ^ (s & ~1);
		}

		for (i = 0; i < 4; i++)
			get_uint();

#ifdef RNG_USE_SSE2
		// With SSE2 we have 4 parallel generators.
		// The first one is represented by the first dword of each m_rand128[0..3], and so on.
		u32_t	*rand32 = (u32_t *)m_rand128;
		int		x, y;

		for (x = 0; x < 4; x++)	//generator
		{
			for (y = 0; y < 4; y++)	//generator's dword
			{
				s = s * A + B;
				rand32[4 * y + x] = seed32[y] ^ (s & ~1);
			}
		}

		for (i = 0; i < 4; i++)
			get_uint128();

		get_double_32_4(m_double_32_4);
		m_double_32_i = 0;
#endif //RNG_USE_SSE2

#ifdef DEBUG_GAUSSIAN
 		m_have_gaussian = false;
#endif
	} //set_seed

	//__get_uint
	//***************************
	FORCE_INLINE u32_t get_uint()
	//***************************
	// Return random 32-bit (0 <= result < 2^32).
	// Based on Marsaglia's Xorshift RNGs: http://www.jstatsoft.org/v08/i14/paper
	// "+ m_rand32[0]" is added to the original method to pass bbattery_SmallCrush()->sknuth_MaxOft
	// and all bbattery_Crush() tests.
	{
		u32_t	t = m_rand32[0] ^ (m_rand32[0] << 11);

		m_rand32[0] = m_rand32[1];
		m_rand32[1] = m_rand32[2];
		m_rand32[2] = m_rand32[3];

		return m_rand32[3] = (m_rand32[3] ^ (m_rand32[3] >> 19) ^ t ^ (t >> 8))
			+ m_rand32[0];
	} //get_uint

#ifdef RNG_USE_SSE2
	//********************************
	FORCE_INLINE __m128i get_uint128()
	//********************************
	{
		__m128i	t = _mm_xor_si128(m_rand128[0], _mm_slli_epi32(m_rand128[0], 11));

		m_rand128[0] = m_rand128[1];
		m_rand128[1] = m_rand128[2];
		m_rand128[2] = m_rand128[3];

		return m_rand128[3] = _mm_add_epi32(_mm_xor_si128(_mm_xor_si128(_mm_xor_si128(
			m_rand128[3], _mm_srli_epi32(m_rand128[3], 19)), t), _mm_srli_epi32(t, 8)), m_rand128[0]);
	}
#endif //RNG_USE_SSE2

	//**************************************
	FORCE_INLINE u32_t get_uint(u32_t range)
	//**************************************
	// Return random u32_t (0 <= result < range).
	{
#ifdef RNG_APPROX_RAND
		if (range <= 0x10000)
			return (u32_t)(((u64_t)get_uint() * range) >> 32);
#endif

		u32_t	rand32, rem;

		do
		{
			rand32 = get_uint();
			rem = rand32 % range;
		} while (rand32 > rem - range);	//while (rand32 - rem > 2^32 - range)

		return rem;
	}

	//*******************************************************
	FORCE_INLINE u32_t get_uint(u32_t min_val, u32_t max_val)
	//*******************************************************
	// Return random u32_t (min_val <= result <= max_val).
	{
		if (max_val <= min_val)
			return min_val;

		u32_t	range = max_val - min_val + 1;

		return (!range) ? get_uint() :	//max_val == 2^32-1, min_val == 0
			min_val + get_uint(range);
	}

	//__get_int
	//************************
	FORCE_INLINE int get_int()
	//************************
	// Return random int (-2^31 <= result < 2^31).
	{
		return get_uint();
	}

	//*********************************
	FORCE_INLINE int get_int(int range)
	//*********************************
	// Return random int (0 <= result < range).
	{
		return (range <= 1) ? 0 :
			get_uint(range);
	}

	//************************************************
	FORCE_INLINE int get_int(int min_val, int max_val)
	//************************************************
	// Return random int (min_val <= result <= max_val).
	{
		if (max_val <= min_val)
			return min_val;

		u32_t	range = max_val - min_val + 1;

		return (!range) ? get_uint() :	//max_val == 2^31-1, min_val == -2^31
			min_val + get_uint(range);
	}

	//__get_bool
	//**************************
	FORCE_INLINE bool get_bool()
	//**************************
	// Return random bool.
	{
		if (m_bool_bit_n <= 0)
		{
			m_bool_rand = get_uint();
			m_bool_bit_n = sizeof(m_bool_rand) * 8;
		}

		bool	result = m_bool_rand & 1;
		m_bool_rand >>= 1;
		m_bool_bit_n--;
		return result;
	}

	//__get_double__
	//******************************
	FORCE_INLINE double get_double()
	//******************************
	// Return random double (0 <= result < 1) with 53 bits of precision:
	// 0, 1/2^53, 2/2^53 ... (2^53 - 1) / 2^53.
	// Based on nextDouble() of Java:
	// http://download.oracle.com/javase/1.4.2/docs/api/java/util/Random.html
	// Using int instead of u32_t is important because there are FILD, FIMUL, ...
	// instructions for ints, but not for u32_t.
	{
		int		x = get_uint() & 0x7FFFFFFF;
		int		y = get_uint() & 0x003FFFFF;
		return x * RNG_POW_2(31) + y * RNG_POW_2(53);
	}

	//**************************************
	__inline double get_double(double range)
	//**************************************
	// Return random double (0 <= result < range).
	{
		return get_double() * range;
	}

	//********************************************************
	__inline double get_double(double min_val, double max_val)
	//********************************************************
	// Return random double (min_val <= result < max_val).
	{
		return min_val + get_double(max_val - min_val);
	}

	//__get_double_32
	//*****************************
	__inline double get_double_32()
	//*****************************
	// Return random double (0 <= result < 1) with 32 bits of precision.
	// This is faster than get_double().
	// get_uint() * RNG_POW_2(32) is > 2 times as slow.
	{
#ifdef RNG_USE_SSE2
#if 0//.
		double	d = m_double_32_4[m_double_32_i++];

		if (m_double_32_i >= 4)
		{
			get_double_32_4(m_double_32_4);
			m_double_32_i = 0;
		}

		return d;
#else
		if (m_double_32_i >= 4)
		{
			get_double_32_4(m_double_32_4);
			m_double_32_i = 0;
		}

		return m_double_32_4[m_double_32_i++];
#endif
#else
		// (int)get_uint() * RNG_POW_2(32) == [-2^31..2^31-1) / 2^32 == [-0.5..0.5).
		return (int)get_uint() * RNG_POW_2(32) + .5;
#endif
	}

#ifdef RNG_USE_SSE2
	//******************************
	void get_double_32_4(double *d4)
	//******************************
	// Updating m_double_32_4[]/m_double_32_i explicitly here is slow.
	{
		const __m128d	mul2 = _mm_set1_pd(RNG_POW_2(32));
		const __m128d	add2 = _mm_set1_pd(0.5);
		__m128i	d128;
		__m128d	d2;

		d128 = get_uint128();
		d2 = _mm_cvtepi32_pd(d128);
		d2 = _mm_mul_pd(d2, mul2);
		d2 = _mm_add_pd(d2, add2);
		_mm_storeu_pd(d4, d2);

		d128 = _mm_srli_si128(d128, 8);
		d2 = _mm_cvtepi32_pd(d128);
		d2 = _mm_mul_pd(d2, mul2);
		d2 = _mm_add_pd(d2, add2);
		_mm_storeu_pd(d4 + 2, d2);
	} //get_double_32_4
#endif //RNG_USE_SSE2

	//__get_float
	//************************
	__inline float get_float()
	//************************
	// Return random float (0 <= result < 1) with 24 bits of precision.
	// Similar to get_double_32(). "& 0xFFFFFF00" is needed to avoid "return 1".
	{
		return (float)((int)(get_uint() & 0xFFFFFF00) * RNG_POW_2(32) + .5);
	}

	//***********************************
	__inline float get_float(float range)
	//***********************************
	// Return random float (0 <= result < range).
	{
		return get_float() * range;
	}

	//****************************************************
	__inline float get_float(float min_val, float max_val)
	//****************************************************
	// Return random float (min_val <= result < max_val).
	{
		return min_val + get_float(max_val - min_val);
	}

#ifdef RNG_USE_SSE2
	//__get_array_double
	//**********************************************************************************
	void get_array_double(double *array, size_t array_n, double min_val, double max_val)
	//**********************************************************************************
	// Called from all get_array().
	{
		const double	D1 = -1.0;
		const int		IEEE_754 = (*(u64_t *)&D1 == (u64_t)0xBFF0000000000000);
		double	range = max_val - min_val;
		size_t	array_i;
		x128_t	r;

		if (IEEE_754)
		{
			__m128i	mask_and = _mm_set_epi32(0x000FFFFF, 0xFFFFFFFF, 0x000FFFFF, 0xFFFFFFFF);
			__m128i	mask_or = _mm_set_epi32(0x3FF00000, 0, 0x3FF00000, 0);
			__m128d	min_val2 = _mm_set1_pd(min_val);
			__m128d	range2 = _mm_set1_pd(range);
			__m128d	d2 = _mm_set_pd(1, 1);

			for (array_i = 0; array_i < array_n / 2 * 2; array_i += 2)
			{
				r.i128 = get_uint128();
				r.i128 = _mm_and_si128(r.i128, mask_and);
				r.i128 = _mm_or_si128(r.i128, mask_or);
				r.d128 = _mm_sub_pd(r.d128, d2);
				r.d128 = _mm_mul_pd(r.d128, range2);
				r.d128 = _mm_add_pd(r.d128, min_val2);
				_mm_storeu_pd(&array[array_i], r.d128);
			}
		}
		else
		{
			// See get_double().
			const __m128i	mask4 = _mm_set_epi32(0x003FFFFF, 0x7FFFFFFF, 0x003FFFFF, 0x7FFFFFFF);
			double	d;

			for (array_i = 0; array_i < array_n / 2 * 2; array_i += 2)
			{
				r.i128 = _mm_and_si128(get_uint128(), mask4);

				d = r.i32[0] * RNG_POW_2(31) + r.i32[1] * RNG_POW_2(53);
				array[array_i + 0] = min_val + d * range;

				d = r.i32[2] * RNG_POW_2(31) + r.i32[3] * RNG_POW_2(53);
				array[array_i + 1] = min_val + d * range;
			}
		}

		for (; array_i < array_n; array_i++)
			array[array_i] = get_double(min_val, max_val);
	} //get_array_double

	//__get_array_float
	//******************************************************************************
	void get_array_float(float *array, size_t array_n, float min_val, float max_val)
	//******************************************************************************
	// Called from all get_array().
	{
		const float	F1 = (float)-1.0;
		const int	IEEE_754 = (*(u32_t *)&F1 == (u32_t)0xBF800000);
		float	range = max_val - min_val;
		size_t	array_i;
		__m128	min_val4 = _mm_set1_ps(min_val);
		__m128	range4 = _mm_set1_ps(range);

		if (IEEE_754)
		{
			x128_t	r;
			__m128i	mask_and = _mm_set_epi32(0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF);
			__m128i	mask_or = _mm_set_epi32(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000);
			__m128	f4 = _mm_set_ps(1, 1, 1, 1);

			for (array_i = 0; array_i < array_n / 4 * 4; array_i += 4)
			{
				r.i128 = get_uint128();
				r.i128 = _mm_and_si128(r.i128, mask_and);
				r.i128 = _mm_or_si128(r.i128, mask_or);
				r.f128 = _mm_sub_ps(r.f128, f4);
				r.f128 = _mm_mul_ps(r.f128, range4);
				r.f128 = _mm_add_ps(r.f128, min_val4);
				_mm_storeu_ps(&array[array_i], r.f128);
			}
		}
		else
		{
			// See get_float().
			__m128i	r;
			__m128i	mask4 = _mm_set1_epi32(0xFFFFFF00);
			__m128	f4;
			__m128	mul4 = _mm_set1_ps(RNG_POW_2(32));
			__m128	add4 = _mm_set1_ps((float)0.5);

			for (array_i = 0; array_i < array_n / 4 * 4; array_i += 4)
			{
				r = get_uint128();
				r = _mm_and_si128(r, mask4);

				f4 = _mm_cvtepi32_ps(r);
				f4 = _mm_mul_ps(f4, mul4);
				f4 = _mm_add_ps(f4, add4);
				f4 = _mm_mul_ps(f4, range4);
				f4 = _mm_add_ps(f4, min_val4);
				_mm_storeu_ps(&array[array_i], f4);
			}
		}

		for (; array_i < array_n; array_i++)
			array[array_i] = get_float(min_val, max_val);
	} //get_array_float
#endif //RNG_USE_SSE2

	//__get_array__no_range
	template<typename array_t>
	//********************************************
	bool get_array(array_t *array, size_t array_n)
	//********************************************
	// The range is assumed to be [0..1) for double/float or maximal for integers of all types.
	// For integers, we just fill the array with random bits (works with both signed/unsigned).
	{
		const int	FLOAT = (array_t).5 == .5;	//array_t == double/float
		size_t		array_i = 0;

		if (FLOAT && (sizeof(array_t) > sizeof(double)))	//long double
			return false;

		if (FLOAT)
		{
#ifdef RNG_USE_SSE2
			if (sizeof(array_t) == sizeof(double))
				get_array_double((double *)array, array_n, (double)0, (double)1);
			else
				get_array_float((float *)array, array_n, (float)0, (float)1);
#else
			if (sizeof(array_t) == sizeof(double))
				for (; array_i < array_n; array_i++)
					array[array_i] = (array_t)get_double();
			else
				for (; array_i < array_n; array_i++)
					array[array_i] = (array_t)get_float();
#endif
			return true;
		}

		size_t	array_size = array_n * sizeof(array_t);
		u32_t	*array32 = (u32_t *)array;
		size_t	array32_n = array_size / sizeof(u32_t);

		array_i = 0;

#ifdef RNG_USE_SSE2
		if (array_size >= 64)
		{
			size_t	offset = 16 - ((size_t)array & 15);

			if (offset < 16)
			{
				// Align array32 on 16-byte boundary.
				_mm_storeu_si128((__m128i *)array, get_uint128());

				array_size -= offset;
				array32 = (u32_t *)((u8_t *)array + offset);
				array32_n = array_size / sizeof(u32_t);
			}

			// Get random 16-byte chunks.
			for (; array_i < array32_n / 4 * 4; array_i += 4)
				_mm_store_si128((__m128i *)&array32[array_i], get_uint128());
		}
#endif

		for (; array_i < array32_n; array_i++)
			array32[array_i] = get_uint();

		// Get final 0..3 bytes.
		u8_t	*array8 = (u8_t *)&array32[array32_n];
		x32_t	rand32;

		rand32.u32 = get_uint();
		for (array_i = 0; array_i < (array_size & 3); array_i++)
			array8[array_i] = rand32.u8[array_i];

		return true;
	} //get_array

	//__get_array__range
	template<typename array_t, typename range_t>
	//***********************************************************
	bool get_array(array_t *array, size_t array_n, range_t range)
	//***********************************************************
	{
		const int	FLOAT = (array_t).5 == .5;	//array_t == double/float

		if (FLOAT)
			return get_array(array, array_n, (array_t)0, (array_t)range);
		else
			return get_array(array, array_n, (array_t)0, (array_t)range - 1);
	} //get_array

	//__get_array__min_max
	template<typename array_t, typename min_val_t, typename max_val_t>
	//************************************************************************************
	bool get_array(array_t *array, size_t array_n, min_val_t _min_val, max_val_t _max_val)
	//************************************************************************************
	{
		const int	FLOAT = (array_t).5 == .5;	//array_t == double/float
		const int	UNSIGNED = (array_t)-1 > 0;
		u32_t	rand32;
		size_t	array_i = 0;

		if ((FLOAT && (sizeof(array_t) > sizeof(double))) ||	//long double
			(!FLOAT && (sizeof(array_t) > sizeof(int))))
			return false;

		if (!array_n)
			return true;

////////////////////////////////////////////////////////////////////////////////
		if (FLOAT)
		{
#ifdef RNG_USE_SSE2
			if (sizeof(array_t) == sizeof(double))
				get_array_double((double *)array, array_n, (double)_min_val, (double)_max_val);
			else
				get_array_float((float *)array, array_n, (float)_min_val, (float)_max_val);
#else
			if (sizeof(array_t) == sizeof(double))
				for (; array_i < array_n; array_i++)
					array[array_i] = (array_t)get_double((double)_min_val, (double)_max_val);
			else
				for (; array_i < array_n; array_i++)
					array[array_i] = (array_t)get_float((float)_min_val, (float)_max_val);
#endif
			return true;
		}

////////////////////////////////////////////////////////////////////////////////
		const array_t	min_val = (array_t)_min_val;
		const array_t	max_val = (array_t)_max_val;
		// (array_t) converts 2^n->0 if (sizeof(array_t) < sizeof(int)).
		const u32_t		range = (u32_t)(array_t)(max_val - min_val + 1);

		if (max_val < min_val)
			return false;

		if (range == 1)	//max_val == min_val
		{
			for (; array_i < array_n; array_i++)
				array[array_i] = min_val;
			return true;
		}

		// Overflow (range == 2^32):
		// (min_val, max_val): (0, 2^32-1) or (-2^31, 2^31-1).
		if (!range)
			return get_array(array, array_n);

////////////////////////////////////////////////////////////////////////////////
		if (!(range & (range - 1)))	//range == 2^n
		{
			const int	range_bit_n = get_bit_n(range - 1);	//1..32
			const u32_t	range_mask = ((u32_t)1 << range_bit_n) - 1;

#ifdef RNG_USE_SSE2
			x128_t	rand128;
			int		i;

			// Handling (range_bit_n <= 8) separately is no faster.
			if (range_bit_n <= 16)
			{
				const __m128i	range_mask8 = _mm_set1_epi16(range_mask);

				while (array_i < array_n / 8 * 8)
				{
					rand128.i128 = _mm_and_si128(get_uint128(), range_mask8);

					// Adding min_val with _mm_add_epi16() is no faster.
					for (i = 0; i < 8; i++)
						array[array_i++] = min_val + rand128.u16[i];
				}
			}
			else	//range_bit_n > 16
			{
				const __m128i	range_mask4 = _mm_set1_epi32(range_mask);

				while (array_i < array_n / 4 * 4)
				{
					rand128.i128 = _mm_and_si128(get_uint128(), range_mask4);

					for (i = 0; i < 4; i++)
						array[array_i++] = min_val + rand128.u32[i];
				}
			}
#else
			x32_t	rand32;

			if (range_bit_n <= 8)
			{
				const u32_t	range_mask1 = range_mask | (range_mask << 8) || (range_mask << 16) || (range_mask << 24);

				for (; array_i < array_n / 4 * 4; array_i += 4)
				{
					rand32.u32 = get_uint() & range_mask1;
					array[array_i + 0] = min_val + rand32.u8[0];
					array[array_i + 1] = min_val + rand32.u8[1];
					array[array_i + 2] = min_val + rand32.u8[2];
					array[array_i + 3] = min_val + rand32.u8[3];
				}
			}
			else if (range_bit_n <= 16)
			{
				const u32_t	range_mask1 = range_mask | (range_mask << 16);

				for (; array_i < array_n / 2 * 2; array_i += 2)
				{
					rand32.u32 = get_uint() & range_mask1;
					array[array_i + 0] = min_val + rand32.u16[0];
					array[array_i + 1] = min_val + rand32.u16[1];
				}
			}
#endif //RNG_USE_SSE2

			for (; array_i < array_n; array_i++)
				array[array_i] = min_val + (get_uint() & range_mask);

			return true;
		} //if (!(range & (range - 1)))

////////////////////////////////////////////////////////////////////////////////
#ifdef RNG_APPROX_RAND
		if (range <= 0x10000)
		{
			#ifdef RNG_USE_SSE2
				x128_t	rand128;
				__m128i	range4 = _mm_set1_epi32(range);
				__m128i	min_val4 = _mm_set1_epi32(min_val);

				for (; array_i < array_n / 4 * 4; array_i += 4)
				{
					rand128.i128 = mul128_hi(get_uint128(), range4);
					rand128.i128 = _mm_add_epi32(rand128.i128, min_val4);

					array[array_i + 0] = (array_t)rand128.u32[0];
					array[array_i + 1] = (array_t)rand128.u32[1];
					array[array_i + 2] = (array_t)rand128.u32[2];
					array[array_i + 3] = (array_t)rand128.u32[3];
				}
			#endif //RNG_USE_SSE2

			for (; array_i < array_n; array_i++)
				array[array_i] = min_val + (u32_t)(((u64_t)get_uint() * range) >> 32);

			return true;
		}
#endif //RNG_APPROX_RAND

////////////////////////////////////////////////////////////////////////////////
		const div_class	div(range);
		u32_t	rem;

#ifdef RNG_USE_SSE2
		if (array_n >= 8)
		{
			x128_t	rand128;
			x128_t	rem0;
			x128_t	rem1;
			__m128i	q;
			__m128i	min_val4 = _mm_set1_epi32((i32_t)min_val);

			if (div.m_div_n > 1)
			{
				while (array_i <= array_n - 8)
				{
					rand128.i128 = get_uint128();

					q = div.div128(rand128.i128, rem0.i128);
					div.div128(q, rem1.i128);
					rem0.i128 = _mm_add_epi32(rem0.i128, min_val4);
					rem1.i128 = _mm_add_epi32(rem1.i128, min_val4);

					for (int i = 0; i < 4; i++)
						if (rand128.u32[i] < div.m_max_num)
						{
							array[array_i + 0] = (array_t)rem0.u32[i];
							array[array_i + 1] = (array_t)rem1.u32[i];
							array_i += 2;
						}
				}
			}
			else
			{
				while (array_i <= array_n - 4)
				{
					rand128.i128 = get_uint128();

					div.div128(rand128.i128, rem0.i128);
					rem0.i128 = _mm_add_epi32(rem0.i128, min_val4);

					for (int i = 0; i < 4; i++)
						if (rand128.u32[i] < div.m_max_num)
							array[array_i++] = (array_t)rem0.u32[i];
				}
			}
		}
#else
		// (div.m_div_n > 1) can only be if VC or SSE (see div_class()).
		if (div.m_div_n > 1)
		{
			size_t	array_end = array_n / div.m_div_n * div.m_div_n;
			size_t	array_i1 = 0;

			while (1)
			{
				if (array_i >= array_i1)
				{
					if (array_i >= array_end)
						break;
					array_i1 += div.m_div_n;
					while ((rand32 = get_uint()) >= div.m_max_num)
						;

					rand32 = div.div(rand32, rem);
					array[array_i++] = min_val + rem;
				}

				rand32 = div.div(rand32, rem);
				array[array_i++] = min_val + rem;
			}
		}
#endif //RNG_USE_SSE2

		for (; array_i < array_n; array_i++)
		{
			while ((rand32 = get_uint()) >= div.m_max_num)
				;
			div.div(rand32, rem);
			array[array_i] = min_val + rem;
		}

		return true;
	} //get_array

#ifdef DEBUG_GAUSSIAN
	//***********************************
	double get_gaussian(double sigma = 1)
	//***********************************
	{
		if (m_have_gaussian)
		{
			m_have_gaussian = false;
			return m_gaussian;
		}
		else
		{
			double	v1, v2;
			double	s, mul;

			do
			{
				v1 = 2 * get_double_32() - 1;	//-1..1
				v2 = 2 * get_double_32() - 1;
				s = v1 * v1 + v2 * v2;
			} while ((s >= 1) || (s == 0));

			mul = sqrt(-2 * log(s) / s) * sigma;
			m_gaussian = v2 * mul;
			m_have_gaussian = true;
			return v1 * mul;
		}
	} //get_gaussian
#endif //DEBUG_GAUSSIAN
 
	//************************
	double zig_tail_x(i32_t k)
	//************************
	// Called from get_normal() if (!i).
	{
		double	x, y;

		do
		{
			x = -log(get_double_32()) / ZIG_TAIL_START;
			y = -log(get_double_32());
		} while (2 * y < x * x);

		x += ZIG_TAIL_START;
		return (k >= 0) ? x : -x;
	} //zig_tail_x

 	//*********************************
	double get_normal(double sigma = 1)
	//*********************************
	{
		i32_t	i, k;
		double	x;

#ifdef DEBUG_GAUSSIAN
		return get_gaussian(sigma);
#endif

		while (1)
		{
			i = get_uint() & (ZIG_TAB_N - 1);
			k = get_uint();
			x = k * zig_w[i];

			if (abs(k) < zig_k[i])
				break;

			if (!i)
			{
				x = zig_tail_x(k);
				break;
			}
			else if (zig_f[i] + get_double_32() * (zig_f[i - 1] - zig_f[i]) < exp(-x * x / 2))
				break;
		} //while (1)

		return sigma * x;
	} //get_normal

	//__get_normal
	//**************************************************************
	void get_normal(double *array, size_t array_n, double sigma = 1)
	//**************************************************************
	{
		size_t	array_i = 0;

#if defined(RNG_USE_SSE2) && !defined(DEBUG_GAUSSIAN)
		if (array_n >= 6)
		{
			x128_t	rand128[2];
			int		rand_i;
			i32_t	i, k;
			double	x;

			while (array_i <= array_n - 6)
			{
				rand128[0].i128 = get_uint128();
				rand128[1].i128 = get_uint128();

				for (rand_i = 0; rand_i < 6; rand_i++)
				{
					i = rand128[0].u8[rand_i] & (ZIG_TAB_N - 1);
					k = rand128[0].i32[rand_i + 2];
					x = k * zig_w[i];

					if (abs(k) >= zig_k[i])
					{
						if (!i)
							x = zig_tail_x(k);
						else if (zig_f[i] + get_double_32() * (zig_f[i - 1] - zig_f[i]) >= exp(-x * x / 2))
							continue;
					}

					array[array_i++] = sigma * x;
				} //for (rand_i
			}
		}
#endif //RNG_USE_SSE2

		for (; array_i < array_n; array_i++)
			array[array_i] = get_normal(sigma);
	} //get_normal

}; //class rng_class

} //namespace rng
#endif //RNG_CLASS_H
//.
using namespace rng;

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#if defined(_WIN32)
	#if !defined(ONLINE_JUDGE)
		#include <windows.h>
	#endif
	#include <io.h>
	#include <share.h>
#else
	#include <unistd.h>
	#include <sys/time.h>	//gettimeofday()
	#include <sys/types.h>

	#define O_BINARY			0
#endif

#include <fcntl.h>		//O_CREAT
#include <sys/stat.h>	//S_IREAD

#if defined(_WIN32) && defined(ONLINE_JUDGE)
#define WINBASEAPI				__declspec(dllimport)
#define WINAPI					__stdcall
#define IDLE_PRIORITY_CLASS		0x00000040
#define HIGH_PRIORITY_CLASS		0x00000080

extern "C"
{
	WINBASEAPI int WINAPI SetPriorityClass(void * h_process, u32_t priority_class);
	WINBASEAPI void * WINAPI GetCurrentProcess();

	WINBASEAPI int WINAPI QueryPerformanceFrequency(i64_t *p_frequency);
	WINBASEAPI int WINAPI QueryPerformanceCounter(i64_t *p_performance_count);
}
#endif //_WIN32

u32_t	rng_range;
u32_t	rng_min_val;

//************************************
void p(const char * format = " ", ...)
//************************************
{
	va_list	_va_list;
	char	buf[2000];
	int		len;

	va_start(_va_list, format);
	len = vsprintf(buf, format, _va_list);

	if (len && (buf[len - 1] == '+'))
		len--;
	else
		buf[len++] = '\n';

	buf[len] = 0;

#if !defined(ONLINE_JUDGE)
	OutputDebugString(buf);
#else
	fprintf(stdout, buf);
#endif
} //p

#ifdef _WIN32
	#if !defined(ONLINE_JUDGE)
		typedef LARGE_INTEGER	usec_t;
	#else
		typedef i64_t	usec_t;
	#endif

	static usec_t get_time_freq();
	static usec_t	time_freq = get_time_freq();
#else
	typedef timeval		usec_t;
#endif

#ifdef _WIN32
//***************************
static usec_t get_time_freq()
//***************************
{
	usec_t	time_freq;
	QueryPerformanceFrequency(&time_freq);
	return time_freq;
}
#endif

//__get_time
//**********************
inline usec_t get_time()
//**********************
{
	usec_t	time;

#ifdef _WIN32
	QueryPerformanceCounter(&time);
#else
	gettimeofday(&time, NULL);
#endif

	return time;
} //get_time

//****************************************
inline double get_time_dif(usec_t & time0)
//****************************************
{
	usec_t	time1 = get_time();

#ifdef _WIN32
	#if !defined(ONLINE_JUDGE)
		return (double)(time1.QuadPart - time0.QuadPart) / time_freq.QuadPart;
	#else
		return (double)(time1 - time0) / time_freq;
	#endif
#else
	return time1.tv_sec - time0.tv_sec + (double)(time1.tv_usec - time0.tv_usec) / 1e6;
#endif
} //get_time_dif

#ifdef DEBUG_BOOST
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/taus88.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>

//boost::random::mt19937 gen;
boost::random::taus88 gen;

//boost::random::uniform_int_distribution<> dist(1, 6);
//int		rnd = dist(gen);
#endif //DEBUG_BOOST

#if defined(DEBUG_TESTU01) && defined(__GNUC__) && !defined(ONLINE_JUDGE)
extern "C"
{
	#include "unif01.h"
	#include "bbattery.h"
}

rng_class	rng1;

u32_t rng_get_uint()
{	return rng1.get_uint();}

double rng_get_double()
{	return rng1.get_double();}

#if defined(DEBUG_DIEHARD_FILE) && !defined(ONLINE_JUDGE)
//__create_diehard_file
//************************
void create_diehard_file()
//************************
// Create diehard.bin file here and run diehard.exe from:
// http://www.stat.fsu.edu/pub/diehard/
{
	rng_class	rng;
	int		file;
	#define BUF_SIZE	(10 * 1000 * 1000)
	u32_t	*buf = (u32_t *)malloc(BUF_SIZE);

	rng.set_seed(1);

	rng.get_array(buf, BUF_SIZE / sizeof(buf[0]));

	file = open("diehard.bin", O_CREAT | O_WRONLY | O_BINARY | O_TRUNC, S_IREAD | S_IWRITE);
	write(file, buf, BUF_SIZE);
	close(file);

	free(buf);
} //create_diehard_file
#endif //DEBUG_DIEHARD_FILE

//__run_testu01
//****************
void run_testu01()
//****************
// Download "Binaries for MinGW under MS Windows" from http://www.iro.umontreal.ca/~simardr/testu01/tu01.html
// Compile and run:
// C:\MinGW\bin\g++.exe rng_test.cpp -ID:\Sed\Rand\TestU01\include\ -LD:\Sed\Rand\TestU01\lib -ltestu01 -lmylib -lprobdist -lws2_32 -O2 -msse2 -orng_test
{
	unif01_Gen	*gen;
	char	str[40];

	rng1.set_seed(1);

	strcpy(str, "rng_get_uint");
	gen = unif01_CreateExternGenBits(str, rng_get_uint);
	bbattery_SmallCrush(gen);
//	bbattery_Crush(gen);
//	bbattery_BigCrush(gen);
	unif01_DeleteExternGenBits(gen);

	strcpy(str, "rng_get_double");
	gen = unif01_CreateExternGen01(str, rng_get_double);
//	bbattery_SmallCrush(gen);
//	bbattery_Crush(gen);
//	bbattery_BigCrush(gen);
	unif01_DeleteExternGen01(gen);
} //run_testu01
#endif //DEBUG_TESTU01

#ifdef DEBUG_PRINT_NORMAL
//********************************************
static char *float_str(double x, char *format)
//********************************************
// Delete zeros in e-007.
// Called from print_normal().
{
	static char	str[40];
	char	*pos, *pos1;

	sprintf(str, format, x);
	if (pos = strstr(str, "e"))
	{
		pos++;
		if (pos[0] == '-')
			pos++;
		for (pos1 = pos; (pos1[0] == '+') || (pos1[0] == '0'); pos1++)
			;
		strcpy(pos, pos1);
	}

	return str;
} //float_str

//*****************
void print_normal()
//*****************
// Print zig_k[], zig_w[], zig_f[].
{
	i32_t	zig_k[ZIG_TAB_N];
	double	zig_w[ZIG_TAB_N];
	double	zig_f[ZIG_TAB_N];
	double	m = (1u << 31);
	double	d = ZIG_TAIL_START;
	double	v = ZIG_V;
	double	d0, q;
	int		i, i1;

	q = v / exp(-d * d / 2);
	zig_k[0] = (i32_t)((d / q) * m);
	zig_k[1]=0;

	zig_w[0] = q / m;
	zig_w[ZIG_TAB_N - 1] = d / m;

	zig_f[0] = 1;
	zig_f[ZIG_TAB_N - 1] = exp(-d * d / 2);

	for (i = ZIG_TAB_N - 2; i >= 1; i--)
	{
		d0 = d;
		d = sqrt(-2 * log(v / d + exp(-d * d / 2)));
		zig_k[i + 1] = (i32_t)((d / d0) * m);
		zig_f[i] = exp(-.5 * d * d);
		zig_w[i] = d / m;
	}

	p("static const i32_t zig_k[ZIG_TAB_N] =");
	p("{");
	for (i = 0; i <= ZIG_TAB_N - 8; i += 8)
	{
		p(" +");
		for (i1 = 0; i1 < 8; i1++)
			p("%d, +", zig_k[i + i1]);
		p();
	}
	p("}; //zig_k");
	p();

	p("static const double zig_w[ZIG_TAB_N] =");
	p("{");
	for (i = 0; i <= ZIG_TAB_N - 4; i += 4)
	{
		p(" +");
		for (i1 = 0; i1 < 4; i1++)
			p("%s, +", float_str(zig_w[i + i1], "%1.15e"));
		p();
	}
	p("}; //zig_w");
	p();

	p("static const double zig_f[ZIG_TAB_N] =");
	p("{");
	for (i = 0; i <= ZIG_TAB_N - 4; i += 4)
	{
		p(" +");
		for (i1 = 0; i1 < 4; i1++)
			p("%1.15f, +", zig_f[i + i1]);
		p();
	}
	p("}; //zig_f");
	p();
} //print_normal
#endif //DEBUG_PRINT_NORMAL

//__run__
//********
void run()
//********
{
#if defined(_WIN32) && defined(DEBUG_HIGH_PRIORITY)
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
#endif

	rng_class	rng;
	typedef RNG_ARRAY_T	array_t;
	array_t	*array = (array_t *)malloc(DEBUG_ARRAY_N * sizeof(array_t));
	int		i, i1;

#ifdef DEBUG_CHECK
	#define DEBUG_CNT_N			32
	int		cnt[DEBUG_CNT_N] = {0};
	double	sum = 0;
#endif

	rng_range = RNG_RANGE_CONST;
	rng_min_val = RNG_MIN_VAL_CONST;

	usec_t	time0 = get_time();

	#ifdef DEBUG_BOOST
//		boost::random::uniform_int_distribution<> dist(RNG_RANGE_CONST);
//		boost::random::uniform_int_distribution<> dist(0, rng_range - 1);
		boost::random::uniform_real_distribution<> dist(0, 1);

		for (i = 0; i < DEBUG_ARRAY_N; i++)
			array[i] = dist(gen);
	#else
		rng.set_seed(2);

		for (i1 = 0; i1 < DEBUG_REP_ARRAY_N; i1++)
		{
			#ifdef DEBUG_NORMAL
				rng.get_normal(array, DEBUG_ARRAY_N, RNG_RANGE);
			#elif defined(DEBUG_ARRAY)
				#if defined(RNG_MIN_VAL) && defined(RNG_MAX_VAL)
					rng.get_array(array, DEBUG_ARRAY_N, RNG_MIN_VAL, RNG_MAX_VAL);
				#elif defined(RNG_RANGE)
					rng.get_array(array, DEBUG_ARRAY_N, RNG_RANGE);
				#else
					rng.get_array(array, DEBUG_ARRAY_N);
				#endif
			#else
				for (i = 0; i < DEBUG_ARRAY_N; i++)
					#if defined(RNG_MIN_VAL) && defined(RNG_MAX_VAL)
						array[i] = rng.RNG_FUNC(RNG_MIN_VAL, RNG_MAX_VAL);
					#elif deined(RNG_RANGE)
						array[i] = rng.RNG_FUNC(RNG_RANGE);
					#else
						array[i] = rng.RNG_FUNC();
					#endif
			#endif

			#ifdef DEBUG_CHECK
				for (i = 0; i < DEBUG_ARRAY_N; i++)
				{
					#ifdef DEBUG_NORMAL
						if (array[i] < 0)
							array[i] = -array[i];
					#endif

					sum += array[i];

					#if defined(RNG_MIN_VAL) && defined(RNG_MAX_VAL)
						if (array[i] - RNG_MIN_VAL < DEBUG_CNT_N)
							cnt[(int)(array[i] - RNG_MIN_VAL)]++;
					#else
						if (array[i] < DEBUG_CNT_N)	//min_val == 0
							cnt[(int)array[i]]++;
					#endif
				}
			#endif
		}
	#endif

	double	time_dif = get_time_dif(time0);
	p("M/sec=%1.1f, time=%1.3f", (double)DEBUG_REP_RAND_N / time_dif / (1000 * 1000), time_dif);

#ifdef DEBUG_CHECK
	p("avg=%1.6f", sum / DEBUG_REP_RAND_N);

	for (i = 0; i < DEBUG_CNT_N; i++)
		if (cnt[i])
			p("%d, +", cnt[i]);
	p();
#endif

	free(array);
} //run

//__WinMain
#if !defined(DEBUG_TOPCODER)
#if !defined(ONLINE_JUDGE)
//*************************************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev_Instance, char *Cmd_Line, int Cmd_Show)
//*************************************************************************************
#else
int main()
#endif
{
//	p(">");
#ifdef _WIN32
	SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
#endif

#if defined(DEBUG_DIEHARD_FILE) && !defined(ONLINE_JUDGE)
	create_diehard_file();
#elif defined(DEBUG_TESTU01) && defined(__GNUC__) && !defined(ONLINE_JUDGE)
	run_testu01();
#elif defined(DEBUG_PRINT_NORMAL)
	print_normal();
#else
	run();
#endif

	p("~");
	return 0;
} //WinMain
#endif //DEBUG_TOPCODER

#if defined(DEBUG_TOPCODER)
	#pragma warning(disable: 4786)
	#include <vector>
	#include <string>
	using namespace std;

	//*******************
	struct CuttingFigures
	//*******************
	{
		int init(vector<string> & fld, int k, int order_n)
		{
			run();
			return 0;
		}
		vector<int> & processOrder(vector<string> & fig, int price)
		{
			vector<int>	z;
			return z;
		}
	};

	struct BlackBox
	{
		vector<string> scan(int R, int C, int A, int T)
		{
			vector<string>	z;
			string	s;
			z.push_back(s);

			run();
			return z;
		}
	};

	struct EnclosingCircles
	{
		vector<string> placeCircles(vector<int> pointX, vector<int> pointY, int M)
		{
			vector<string>	z;
			string	x;
			z.push_back(x);

			run();
			return z;
		}
		vector<int> generateTestCase(int testNumber)
		{
			vector<int>	z;
			return z;
		}
	};

	struct IsolatedPrimes	//<100K
	{
		string findPrime(int x, int a, int b)
		{
			string	z;

			run();
			return z;
		}
	};

	struct ReliefMap
	{
		vector<double> getMap(vector<string> contourMap)
		{
			vector<double>	z;

			run();
			return z;
		}
	};
#endif //DEBUG_TOPCODER
/*
__get_bit_n
__div_class
__div
__rng_class
__set_seed
__get_uint
__get_int
__get_bool
__get_double__
__get_double_32
__get_float
__get_array_double
__get_array_float
__get_array__no_range
__get_array__range
__get_array__min_max
__get_normal

__get_time
__create_diehard_file
__run_testu01
__print_normal
__run__
__WinMain
*/


