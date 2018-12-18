#include "problems.h"

/**
 * ShuffleDeck Shuffle deck as described in problem statement. Compare to array of 
 * [1, 2, 3, ... , N] at each iteration and stop when deck is back in original order. Return
 * number of iterations. This does a complete shuffle at every step, i.e., it maps all cards 
 * in a deck of size N to their new positions at each iteration. 
 * Too slow.
 *  
 * @param  size Deck size.
 * @return      Number of shuffles required to get deck back to original order.
 */

uint32_t ShuffleDeck(uint32_t size)
{
	vector<uint32_t> originalDeck(size);
	vector<uint32_t> tmp1(size);
	vector<uint32_t> tmp2(size);

	for (uint32_t i = 0; i < size; i++)
	{
		originalDeck[i] = i + 1;
		tmp1[i] = i + 1;
	}

	bool deckReset = false;
	uint32_t halfSize = size / 2;
	uint32_t numShuffles = 0;

	while (!deckReset)
	{
		for (uint32_t i = 0; i < halfSize; i++)
		{
			tmp2[2 * i]     = tmp1[i];
			tmp2[2 * i + 1] = tmp1[halfSize + i];
		}

		memcpy(&tmp1[0], &tmp2[0], size * sizeof(uint32_t));
		numShuffles++;

		if (memcmp(&tmp1[0], &originalDeck[0], size * sizeof(uint32_t)) == 0)
		{
			deckReset = true;
		}
	}

	return numShuffles;
}


/**
 * GetShuffleCycleLength Another attempt. This time, just pick the card as position two (first
 * card always stays in place) and follow it around during shuffles. Step when it gets back to
 * its original position.
 *
 * Also too slow for general solution.
 * 
 * @param  deckSize Deck size.
 * @return          Cycle length -- number of steps required to get card to back to its
 *                  starting position.
 */

uint64_t GetShuffleCycleLength(uint64_t deckSize)
{
	uint64_t cycleLength = 1;
	uint64_t pos = 2;

	while (pos != 1)
	{
		if (cycleLength > 60)
		{
			cycleLength = 0;
			break;
		}

		pos = (2 * pos) % (deckSize - 1);
		cycleLength++;
	}

	return cycleLength;
}

/**
 * ReverseBits Reverse bits of a 32-bit value.
 * 
 * Brainstorming. Thought I might be able to use bit reversal for shuffling. Not needed.
 *
 * @param  x Value whose bits are to be reversed.
 * @return   Value when x's bits are reversed.
 */

uint32_t ReverseBits(uint32_t x)
{
	uint32_t val = x;

	val = ((0xaaaaaaa & val) >> 1) | ((0x55555555 & val) << 1);
	val = ((0xccccccc & val) >> 2) | ((0x33333333 & val) << 2);
	val = ((0xf0f0f0f0 & val) >> 4) | ((0x0f0f0f0f & val) << 4);
	val = ((0xff00ff00 & val) >> 8) | ((0x00ff00ff & val) << 8);
	val = ((0xffff0000 & val) >> 16) | ((0x0000ffff & val) << 16);

	return val;
}

/**
 * GetDivisorsSimple Get divisors of an input value by trial division up to the
 * squareroot of that value.
 * 
 * @param val      Value to get divisors for.
 * @param divisors Vector of output values. Expected to be empty on input.
 */

void GetDivisorsSimple(uint64_t val, vector<uint64_t> &divisors)
{
	uint64_t sqroot = (uint64_t)sqrt((double)val);

	for (uint64_t i = 1; i <= sqroot; i++)
	{
		if (val % i == 0)
		{
			divisors.push_back(i);
			divisors.push_back(val / i);
		}
	}
}

/**
 * BitCount Count bits set in an input value.
 * 
 * @param  val Value to count bits for.
 * @return     Number of bits sets for input value.
 */

uint64_t BitCount(uint64_t val)
{
	uint64_t bitCount = 0;

	while (val)
	{
		if (val & 0x1)
		{
			bitCount++;
		}
		val >>= 1;
	}

	return bitCount;
}

/**
 * PE622 - Shuffle a deck by interleaving top and bottom halfs. This solution works by
 * noting that a given card goes from position N -> 2N mod (deckSize - 1). So, if the second card
 * in the deck returns to its original position in 60 shuffles, the deckSize will satisfy
 * 2^60 = 1 mod (deckSize - 1). To solve, then, find divisors of 2^60 - 1. Loop over the
 * potential deck sizes and verify they don't have a shorter shuffle length by manually
 * iterating the second card via N -> 2N mod (deckSize - 1). Sum deck sizes that actually do
 * have shuffle length 60.
 * 
 * @return Nothing.
 */

uint64_t PE622()
{
	const uint64_t cycleLength = 60LL;
	const uint64_t maxDeckSize = 1LL << cycleLength;
	vector<uint64_t> divisors;
	GetDivisorsSimple(maxDeckSize - 1, divisors);
	uint64_t deckSum = maxDeckSize;

	uint64_t deckSize = 2;
	uint64_t badFactor = (1LL << 30LL) - 1;

	while (true)
	{
		if (GetShuffleCycleLength(deckSize) == cycleLength)
		{
			break;
		}

		deckSize += 2;
	}

	for (auto &div : divisors)
	{
		if (GetShuffleCycleLength(div + 1) != cycleLength && div > cycleLength)
		{
			if (badFactor % div != 0)
			{
				__debugbreak();
			}

			continue;
		}

		deckSum += (div + 1);
	}

	return 0;
}