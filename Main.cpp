#include <iostream>
#include "PhysicalRanges.h"

int main()
{
	ULONG Count = 100;
	PHYSICAL_RANGE List[100];
	if (QueryPhysicalRanges(List, Count, &Count))
	{
		printf("Count: %d\n", Count);
		for (ULONG i = 0; i < Count; ++i)
		{
			printf("[%d] PhysicalAddress 0x%I64X Length 0x%I64X\n", i, List[i].Address, List[i].Length);
		}
	}
}