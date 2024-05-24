#pragma once

class CMTRandom
{
	static const int n = 624, m = 397;

public:
	CMTRandom(unsigned int s);
	unsigned int next();

protected:
	unsigned int twiddle(unsigned int, unsigned int);
	void gen_state();
	void seed(unsigned int);

private:
	unsigned int state[n];
	int p;
	bool init;
};
