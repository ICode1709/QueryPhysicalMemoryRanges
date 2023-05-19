#include "PhysicalRanges.h"


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma comment(lib, "ntdll.lib")
typedef NTSTATUS(__stdcall* PRTL_QUERY_REGISTRY_ROUTINE)(PWSTR ValueName, ULONG ValueType, PVOID ValueData, ULONG ValueLength, PVOID Context, PVOID EntryContext);
typedef struct _RTL_QUERY_REGISTRY_TABLE
{
	PRTL_QUERY_REGISTRY_ROUTINE QueryRoutine;
	ULONG Flags;
	PCWSTR Name;
	PVOID EntryContext;
	ULONG DefaultType;
	PVOID DefaultData;
	ULONG DefaultLength;
}RTL_QUERY_REGISTRY_TABLE, * PRTL_QUERY_REGISTRY_TABLE;
EXTERN_C NTSTATUS RtlQueryRegistryValues(ULONG RelativeTo, PCWSTR Path, PRTL_QUERY_REGISTRY_TABLE QueryTable, PVOID Context, PVOID Environment);

#define RTL_QUERY_REGISTRY_SUBKEY   0x00000001
#define RTL_QUERY_REGISTRY_TOPKEY   0x00000002

#define RTL_QUERY_REGISTRY_REQUIRED 0x00000004
#define RTL_QUERY_REGISTRY_NOVALUE  0x00000008

#define RTL_QUERY_REGISTRY_NOEXPAND 0x00000010

#define RTL_QUERY_REGISTRY_DIRECT   0x00000020  
#define RTL_QUERY_REGISTRY_DELETE   0x00000040 

#define RTL_QUERY_REGISTRY_NOSTRING 0x00000080 
#define RTL_QUERY_REGISTRY_TYPECHECK 0x00000100

#define RTL_REGISTRY_ABSOLUTE     0   // Path is a full path
#define RTL_REGISTRY_SERVICES     1   // \Registry\Machine\System\CurrentControlSet\Services
#define RTL_REGISTRY_CONTROL      2   // \Registry\Machine\System\CurrentControlSet\Control
#define RTL_REGISTRY_WINDOWS_NT   3   // \Registry\Machine\Software\Microsoft\Windows NT\CurrentVersion
#define RTL_REGISTRY_DEVICEMAP    4   // \Registry\Machine\Hardware\DeviceMap
#define RTL_REGISTRY_USER         5   // \Registry\User\CurrentUser
#define RTL_REGISTRY_MAXIMUM      6
#define RTL_REGISTRY_HANDLE       0x40000000    // Low order bits are registry handle
#define RTL_REGISTRY_OPTIONAL     0x80000000    // Indicates the key node is optional

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define CmResourceTypeNull                0   // ResType_All or ResType_None (0x0000)
#define CmResourceTypePort                1   // ResType_IO (0x0002)
#define CmResourceTypeInterrupt           2   // ResType_IRQ (0x0004)
#define CmResourceTypeMemory              3   // ResType_Mem (0x0001)
#define CmResourceTypeDma                 4   // ResType_DMA (0x0003)
#define CmResourceTypeDeviceSpecific      5   // ResType_ClassSpecific (0xFFFF)
#define CmResourceTypeBusNumber           6   // ResType_BusNumber (0x0006)
#define CmResourceTypeMemoryLarge         7   // ResType_MemLarge (0x0007)

#define CmResourceTypeNonArbitrated     128   // Not arbitrated if 0x80 bit set
#define CmResourceTypeConfigData        128   // ResType_Reserved (0x8000)
#define CmResourceTypeDevicePrivate     129   // ResType_DevicePrivate (0x8001)
#define CmResourceTypePcCardConfig      130   // ResType_PcCardConfig (0x8002)
#define CmResourceTypeMfCardConfig      131   // ResType_MfCardConfig (0x8003)
#define CmResourceTypeConnection        132   // ResType_Connection (0x8004)

#define CM_RESOURCE_MEMORY_LARGE                            0x0E00
#define CM_RESOURCE_MEMORY_LARGE_40                         0x0200
#define CM_RESOURCE_MEMORY_LARGE_48                         0x0400
#define CM_RESOURCE_MEMORY_LARGE_64                         0x0800

typedef enum _INTERFACE_TYPE {
	InterfaceTypeUndefined,
	Internal,
	Isa,
	Eisa,
	MicroChannel,
	TurboChannel,
	PCIBus,
	VMEBus,
	NuBus,
	PCMCIABus,
	CBus,
	MPIBus,
	MPSABus,
	ProcessorInternal,
	InternalPowerBus,
	PNPISABus,
	PNPBus,
	Vmcs,
	ACPIBus,
	MaximumInterfaceType
} INTERFACE_TYPE, * PINTERFACE_TYPE;

#pragma pack(push, 4)
typedef struct _CM_PARTIAL_RESOURCE_DESCRIPTOR {
	UCHAR  Type;
	UCHAR  ShareDisposition;
	USHORT Flags;
	union {
		struct
		{
			ULARGE_INTEGER Start;
			ULONG Length;
		} Generic;
		struct
		{
			ULARGE_INTEGER Start;
			ULONG Length;
		} Port;
		struct
		{
			USHORT Level;
			USHORT Group;
			ULONG Vector;
			ULONGLONG Affinity;
		} Interrupt;
		union
		{
			struct
			{
				USHORT Group;
				USHORT MessageCount;
				ULONG Vector;
				ULONGLONG Affinity;
			} Raw;
			struct
			{
				USHORT Level;
				USHORT Group;
				ULONG Vector;
				ULONGLONG Affinity;
			} Translated;
		} MessageInterrupt;
		struct
		{
			ULARGE_INTEGER Start;
			ULONGLONG Length;
		} Memory;
		struct
		{
			ULONG Channel;
			ULONG Port;
			ULONG Reserved1;
		} Dma;
		struct
		{
			ULONG Channel;
			ULONG RequestLine;
			UCHAR TransferWidth;
			UCHAR Reserved1;
			UCHAR Reserved2;
			UCHAR Reserved3;
		} DmaV3;
		struct
		{
			ULONG Data[3];
		} DevicePrivate;
		struct
		{
			ULONG Start;
			ULONG Length;
			ULONG Reserved;
		} BusNumber;
		struct
		{
			ULONG DataSize;
			ULONG Reserved1;
			ULONG Reserved2;
		} DeviceSpecificData;
		struct
		{
			ULARGE_INTEGER Start;
			ULONG Length40;
		} Memory40;
		struct
		{
			ULARGE_INTEGER Start;
			ULONG Length48;
		} Memory48;
		struct
		{
			ULARGE_INTEGER Start;
			ULONG Length64;
		} Memory64;
		struct
		{
			UCHAR Class;
			UCHAR Type;
			UCHAR Reserved1;
			UCHAR Reserved2;
			ULONG IdLowPart;
			ULONG IdHighPart;
		} Connection;
	} u;
} CM_PARTIAL_RESOURCE_DESCRIPTOR, * PCM_PARTIAL_RESOURCE_DESCRIPTOR;
typedef struct _CM_PARTIAL_RESOURCE_LIST {
	USHORT                         Version;
	USHORT                         Revision;
	ULONG                          Count;
	CM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptors[1];
} CM_PARTIAL_RESOURCE_LIST, * PCM_PARTIAL_RESOURCE_LIST;
typedef struct _CM_FULL_RESOURCE_DESCRIPTOR {
	INTERFACE_TYPE           InterfaceType;
	ULONG                    BusNumber;
	CM_PARTIAL_RESOURCE_LIST PartialResourceList;
} CM_FULL_RESOURCE_DESCRIPTOR, * PCM_FULL_RESOURCE_DESCRIPTOR;

typedef struct _CM_RESOURCE_LIST {
	ULONG                       Count;
	CM_FULL_RESOURCE_DESCRIPTOR List[1];
} CM_RESOURCE_LIST, * PCM_RESOURCE_LIST;

#pragma pack(pop)

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct _PHYSICAL_RANGES {
	ULONG MaxCount;
	ULONG Count;
	PPHYSICAL_RANGE List;
}PHYSICAL_RANGES, * PPHYSICAL_RANGES;

NTSTATUS NTAPI QueryPhysicalTranslated(IN PWSTR ValueName, IN ULONG ValueType, IN PVOID ValueData, IN ULONG ValueLength, IN PVOID Context, IN PVOID EntryContext)
{
	PPHYSICAL_RANGES Ranges = (PPHYSICAL_RANGES)Context;
	Ranges->Count = 0;

	PCM_RESOURCE_LIST ResourceList = (PCM_RESOURCE_LIST)ValueData;
	PCM_PARTIAL_RESOURCE_LIST PartialResourceList = &ResourceList->List[0].PartialResourceList;

	for (ULONG i = 0; i < ResourceList->Count; ++i)
	{
		for (ULONG j = 0; j < PartialResourceList->Count; j++)
		{
			PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor = &PartialResourceList->PartialDescriptors[j];
			switch (Descriptor->Type)
			{
			case CmResourceTypeMemoryLarge:
				switch (Descriptor->Flags & (CM_RESOURCE_MEMORY_LARGE_40 | CM_RESOURCE_MEMORY_LARGE_48 | CM_RESOURCE_MEMORY_LARGE_64))
				{
				case CM_RESOURCE_MEMORY_LARGE_40:
					Descriptor->u.Memory.Length <<= 8;
					break;
				case CM_RESOURCE_MEMORY_LARGE_48:
					Descriptor->u.Memory.Length <<= 16;
					break;
				case CM_RESOURCE_MEMORY_LARGE_64:
					Descriptor->u.Memory.Length <<= 32;
					break;
				}
			case CmResourceTypeMemory:
				if (Ranges->Count < Ranges->MaxCount)
				{
					Ranges->List[Ranges->Count].Address = Descriptor->u.Memory.Start.QuadPart;
					Ranges->List[Ranges->Count].Length = Descriptor->u.Memory.Length;
				}
				Ranges->Count++;
				break;
			}
		}
		PartialResourceList = (PCM_PARTIAL_RESOURCE_LIST)&PartialResourceList->PartialDescriptors[PartialResourceList->Count];
	}
	return STATUS_SUCCESS;
}

BOOLEAN QueryPhysicalRanges(PPHYSICAL_RANGE PhysicalRanges, ULONG Count, PULONG ReturnCount)
{
	if (PhysicalRanges == NULL || Count == NULL || ReturnCount == NULL)
		return FALSE;

	*ReturnCount = 0;

	PHYSICAL_RANGES QueryPhysicalRanges;
	QueryPhysicalRanges.List = PhysicalRanges;
	QueryPhysicalRanges.MaxCount = Count;
	QueryPhysicalRanges.Count = 0;

	RTL_QUERY_REGISTRY_TABLE QueryTable[2] = { 0 };

	QueryTable[0].QueryRoutine = QueryPhysicalTranslated;
	QueryTable[0].Flags = RTL_QUERY_REGISTRY_TYPECHECK | RTL_QUERY_REGISTRY_REQUIRED;
	QueryTable[0].DefaultType = REG_RESOURCE_LIST;
	QueryTable[0].Name = L".Translated";

	NTSTATUS status = RtlQueryRegistryValues(RTL_REGISTRY_ABSOLUTE, L"\\REGISTRY\\MACHINE\\HARDWARE\\RESOURCEMAP\\System Resources\\Physical Memory", QueryTable, &QueryPhysicalRanges, NULL);

	if (status == STATUS_SUCCESS)
	{
		*ReturnCount = QueryPhysicalRanges.Count;

		if (QueryPhysicalRanges.MaxCount >= QueryPhysicalRanges.Count)
		{
			return TRUE;
		}

	}
	return FALSE;
}