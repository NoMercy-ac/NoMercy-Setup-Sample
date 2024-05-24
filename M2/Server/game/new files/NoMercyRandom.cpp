#include "stdafx.h"
#include "NoMercyRandom.h"

CMTRandom::CMTRandom(unsigned int s) :
	init(true), p(0)
{
	seed(s);
	memset(&state, 0x0, n);
}

void CMTRandom::gen_state()
{
	for (int i = 0; i < (n - m); ++i)
		state[i] = state[i + m] ^ twiddle(state[i], state[i + 1]);

	for (int i = n - m; i < (n - 1); ++i)
		state[i] = state[i + m - n] ^ twiddle(state[i], state[i + 1]);

	state[n - 1] = state[m - 1] ^ twiddle(state[n - 1], state[0]);

	p = 0;
}

void CMTRandom::seed(unsigned int s)
{
	state[0] = s & 0xFFFFFFFFUL;

	for (int i = 1; i < n; ++i) {
		state[i] = 1812433253UL * (state[i - 1] ^ (state[i - 1] >> 30)) + i;
		state[i] &= 0xFFFFFFFFUL;
	}

	p = n;
}

inline unsigned int CMTRandom::twiddle(unsigned int u, unsigned int v)
{
	return (((u & 0x80000000UL) | (v & 0x7FFFFFFFUL)) >> 1) ^ ((v & 1UL) * 0x9908B0DFUL);
}

unsigned int CMTRandom::next()
{
	if (p == n) gen_state();

	unsigned int x = state[p++];
	x ^= (x >> 11);
	x ^= (x << 7) & 0x9D2C5680UL;
	x ^= (x << 15) & 0xEFC60000UL;

	return x ^ (x >> 18);
}
