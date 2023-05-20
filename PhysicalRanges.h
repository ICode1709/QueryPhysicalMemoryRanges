#pragma once
#include <Windows.h>

typedef struct _PHYSICAL_RANGE {
	ULONGLONG Address;
	ULONGLONG Length;
}PHYSICAL_RANGE, * PPHYSICAL_RANGE;

BOOLEAN QueryPhysicalRanges(PPHYSICAL_RANGE PhysicalRanges, ULONG Count, PULONG ReturnCount);
