#pragma once
#define UMDF_USING_NTSTATUS
#include <Windows.h>
#include <ntstatus.h>

typedef struct _PHYSICAL_RANGE {
	ULONGLONG Address;
	ULONGLONG Length;
}PHYSICAL_RANGE, * PPHYSICAL_RANGE;

BOOLEAN QueryPhysicalRanges(PPHYSICAL_RANGE PhysicalRanges, ULONG Count, PULONG ReturnCount);