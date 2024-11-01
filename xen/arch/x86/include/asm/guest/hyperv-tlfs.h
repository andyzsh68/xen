/* SPDX-License-Identifier: GPL-2.0-only */

/*
 * This file contains definitions from Hyper-V Hypervisor Top-Level Functional
 * Specification (TLFS):
 * https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/reference/tlfs
 */

#ifndef _ASM_X86_HYPERV_TLFS_H
#define _ASM_X86_HYPERV_TLFS_H

#include <xen/bitops.h>
#include <xen/page-size.h>
#include <xen/types.h>

/*
 * While not explicitly listed in the TLFS, Hyper-V always runs with a page size
 * of 4096. These definitions are used when communicating with Hyper-V using
 * guest physical pages and guest physical page addresses, since the guest page
 * size may not be 4096 on all architectures.
 */
#define HV_HYP_PAGE_SHIFT      12
#define HV_HYP_PAGE_SIZE       BIT(HV_HYP_PAGE_SHIFT, UL)
#define HV_HYP_PAGE_MASK       (~(HV_HYP_PAGE_SIZE - 1))

/*
 * The below CPUID leaves are present if VersionAndFeatures.HypervisorPresent
 * is set by CPUID(HvCpuIdFunctionVersionAndFeatures).
 */
#define HYPERV_CPUID_VENDOR_AND_MAX_FUNCTIONS	0x40000000
#define HYPERV_CPUID_INTERFACE			0x40000001
#define HYPERV_CPUID_VERSION			0x40000002
#define HYPERV_CPUID_FEATURES			0x40000003
#define HYPERV_CPUID_ENLIGHTMENT_INFO		0x40000004
#define HYPERV_CPUID_IMPLEMENT_LIMITS		0x40000005
#define HYPERV_CPUID_NESTED_FEATURES		0x4000000A

#define HYPERV_HYPERVISOR_PRESENT_BIT		0x80000000
#define HYPERV_CPUID_MIN			0x40000005
#define HYPERV_CPUID_MAX			0x4000ffff

/*
 * Feature identification. EAX indicates which features are available
 * to the partition based upon the current partition privileges.
 * These are HYPERV_CPUID_FEATURES.EAX bits.
 */

/* VP Runtime (HV_X64_MSR_VP_RUNTIME) available */
#define HV_X64_MSR_VP_RUNTIME_AVAILABLE		BIT(0, UL)
/* Partition Reference Counter (HV_X64_MSR_TIME_REF_COUNT) available*/
#define HV_MSR_TIME_REF_COUNT_AVAILABLE		BIT(1, UL)
/*
 * Basic SynIC MSRs (HV_X64_MSR_SCONTROL through HV_X64_MSR_EOM
 * and HV_X64_MSR_SINT0 through HV_X64_MSR_SINT15) available
 */
#define HV_X64_MSR_SYNIC_AVAILABLE		BIT(2, UL)
/*
 * Synthetic Timer MSRs (HV_X64_MSR_STIMER0_CONFIG through
 * HV_X64_MSR_STIMER3_COUNT) available
 */
#define HV_MSR_SYNTIMER_AVAILABLE		BIT(3, UL)
/*
 * APIC access MSRs (HV_X64_MSR_EOI, HV_X64_MSR_ICR and HV_X64_MSR_TPR)
 * are available
 */
#define HV_X64_MSR_APIC_ACCESS_AVAILABLE	BIT(4, UL)
/* Hypercall MSRs (HV_X64_MSR_GUEST_OS_ID and HV_X64_MSR_HYPERCALL) available*/
#define HV_X64_MSR_HYPERCALL_AVAILABLE		BIT(5, UL)
/* Access virtual processor index MSR (HV_X64_MSR_VP_INDEX) available*/
#define HV_X64_MSR_VP_INDEX_AVAILABLE		BIT(6, UL)
/* Virtual system reset MSR (HV_X64_MSR_RESET) is available*/
#define HV_X64_MSR_RESET_AVAILABLE		BIT(7, UL)
/*
 * Access statistics pages MSRs (HV_X64_MSR_STATS_PARTITION_RETAIL_PAGE,
 * HV_X64_MSR_STATS_PARTITION_INTERNAL_PAGE, HV_X64_MSR_STATS_VP_RETAIL_PAGE,
 * HV_X64_MSR_STATS_VP_INTERNAL_PAGE) available
 */
#define HV_X64_MSR_STAT_PAGES_AVAILABLE		BIT(8, UL)
/* Partition reference TSC MSR is available */
#define HV_MSR_REFERENCE_TSC_AVAILABLE		BIT(9, UL)
/* Partition Guest IDLE MSR is available */
#define HV_X64_MSR_GUEST_IDLE_AVAILABLE		BIT(10, UL)
/*
 * There is a single feature flag that signifies if the partition has access
 * to MSRs with local APIC and TSC frequencies.
 */
#define HV_X64_ACCESS_FREQUENCY_MSRS		BIT(11, UL)
/* AccessReenlightenmentControls privilege */
#define HV_X64_ACCESS_REENLIGHTENMENT		BIT(13, UL)

/*
 * Feature identification: indicates which flags were specified at partition
 * creation. The format is the same as the partition creation flag structure
 * defined in section Partition Creation Flags.
 * These are HYPERV_CPUID_FEATURES.EBX bits.
 */
#define HV_X64_CREATE_PARTITIONS		BIT(0, UL)
#define HV_X64_ACCESS_PARTITION_ID		BIT(1, UL)
#define HV_X64_ACCESS_MEMORY_POOL		BIT(2, UL)
#define HV_X64_ADJUST_MESSAGE_BUFFERS		BIT(3, UL)
#define HV_X64_POST_MESSAGES			BIT(4, UL)
#define HV_X64_SIGNAL_EVENTS			BIT(5, UL)
#define HV_X64_CREATE_PORT			BIT(6, UL)
#define HV_X64_CONNECT_PORT			BIT(7, UL)
#define HV_X64_ACCESS_STATS			BIT(8, UL)
#define HV_X64_DEBUGGING			BIT(11, UL)
#define HV_X64_CPU_POWER_MANAGEMENT		BIT(12, UL)

/*
 * Feature identification. EDX indicates which miscellaneous features
 * are available to the partition.
 * These are HYPERV_CPUID_FEATURES.EDX bits.
 */
/* The MWAIT instruction is available (per section MONITOR / MWAIT) */
#define HV_X64_MWAIT_AVAILABLE				BIT(0, UL)
/* Guest debugging support is available */
#define HV_X64_GUEST_DEBUGGING_AVAILABLE		BIT(1, UL)
/* Performance Monitor support is available*/
#define HV_X64_PERF_MONITOR_AVAILABLE			BIT(2, UL)
/* Support for physical CPU dynamic partitioning events is available*/
#define HV_X64_CPU_DYNAMIC_PARTITIONING_AVAILABLE	BIT(3, UL)
/*
 * Support for passing hypercall input parameter block via XMM
 * registers is available
 */
#define HV_X64_HYPERCALL_PARAMS_XMM_AVAILABLE		BIT(4, UL)
/* Support for a virtual guest idle state is available */
#define HV_X64_GUEST_IDLE_STATE_AVAILABLE		BIT(5, UL)
/* Frequency MSRs available */
#define HV_FEATURE_FREQUENCY_MSRS_AVAILABLE		BIT(8, UL)
/* Crash MSR available */
#define HV_FEATURE_GUEST_CRASH_MSR_AVAILABLE		BIT(10, UL)
/* stimer Direct Mode is available */
#define HV_STIMER_DIRECT_MODE_AVAILABLE			BIT(19, UL)

/*
 * Implementation recommendations. Indicates which behaviors the hypervisor
 * recommends the OS implement for optimal performance.
 * These are HYPERV_CPUID_ENLIGHTMENT_INFO.EAX bits.
 */
/*
 * Recommend using hypercall for address space switches rather
 * than MOV to CR3 instruction
 */
#define HV_X64_AS_SWITCH_RECOMMENDED			BIT(0, UL)
/* Recommend using hypercall for local TLB flushes rather
 * than INVLPG or MOV to CR3 instructions */
#define HV_X64_LOCAL_TLB_FLUSH_RECOMMENDED		BIT(1, UL)
/*
 * Recommend using hypercall for remote TLB flushes rather
 * than inter-processor interrupts
 */
#define HV_X64_REMOTE_TLB_FLUSH_RECOMMENDED		BIT(2, UL)
/*
 * Recommend using MSRs for accessing APIC registers
 * EOI, ICR and TPR rather than their memory-mapped counterparts
 */
#define HV_X64_APIC_ACCESS_RECOMMENDED			BIT(3, UL)
/* Recommend using the hypervisor-provided MSR to initiate a system RESET */
#define HV_X64_SYSTEM_RESET_RECOMMENDED			BIT(4, UL)
/*
 * Recommend using relaxed timing for this partition. If used,
 * the VM should disable any watchdog timeouts that rely on the
 * timely delivery of external interrupts
 */
#define HV_X64_RELAXED_TIMING_RECOMMENDED		BIT(5, UL)

/*
 * Recommend not using Auto End-Of-Interrupt feature
 */
#define HV_DEPRECATING_AEOI_RECOMMENDED			BIT(9, UL)

/*
 * Recommend using cluster IPI hypercalls.
 */
#define HV_X64_CLUSTER_IPI_RECOMMENDED			BIT(10, UL)

/* Recommend using the newer ExProcessorMasks interface */
#define HV_X64_EX_PROCESSOR_MASKS_RECOMMENDED		BIT(11, UL)

/* Recommend using enlightened VMCS */
#define HV_X64_ENLIGHTENED_VMCS_RECOMMENDED		BIT(14, UL)

/*
 * Virtual processor will never share a physical core with another virtual
 * processor, except for virtual processors that are reported as sibling SMT
 * threads.
 */
#define HV_X64_NO_NONARCH_CORESHARING                  BIT(18, UL)

/* Nested features. These are HYPERV_CPUID_NESTED_FEATURES.EAX bits. */
#define HV_X64_NESTED_DIRECT_FLUSH			BIT(17, UL)
#define HV_X64_NESTED_GUEST_MAPPING_FLUSH		BIT(18, UL)
#define HV_X64_NESTED_MSR_BITMAP			BIT(19, UL)

/* Hyper-V specific model specific registers (MSRs) */

/* MSR used to identify the guest OS. */
#define HV_X64_MSR_GUEST_OS_ID			0x40000000

/* MSR used to setup pages used to communicate with the hypervisor. */
#define HV_X64_MSR_HYPERCALL			0x40000001

/* MSR used to provide vcpu index */
#define HV_X64_MSR_VP_INDEX			0x40000002

/* MSR used to reset the guest OS. */
#define HV_X64_MSR_RESET			0x40000003

/* MSR used to provide vcpu runtime in 100ns units */
#define HV_X64_MSR_VP_RUNTIME			0x40000010

/* MSR used to read the per-partition time reference counter */
#define HV_X64_MSR_TIME_REF_COUNT		0x40000020

/* A partition's reference time stamp counter (TSC) page */
#define HV_X64_MSR_REFERENCE_TSC		0x40000021

/* MSR used to retrieve the TSC frequency */
#define HV_X64_MSR_TSC_FREQUENCY		0x40000022

/* MSR used to retrieve the local APIC timer frequency */
#define HV_X64_MSR_APIC_FREQUENCY		0x40000023

/* Define the virtual APIC registers */
#define HV_X64_MSR_EOI				0x40000070
#define HV_X64_MSR_ICR				0x40000071
#define HV_X64_MSR_TPR				0x40000072
#define HV_X64_MSR_VP_ASSIST_PAGE		0x40000073

/* Define synthetic interrupt controller model specific registers. */
#define HV_X64_MSR_SCONTROL			0x40000080
#define HV_X64_MSR_SVERSION			0x40000081
#define HV_X64_MSR_SIEFP			0x40000082
#define HV_X64_MSR_SIMP				0x40000083
#define HV_X64_MSR_EOM				0x40000084
#define HV_X64_MSR_SINT0			0x40000090
#define HV_X64_MSR_SINT1			0x40000091
#define HV_X64_MSR_SINT2			0x40000092
#define HV_X64_MSR_SINT3			0x40000093
#define HV_X64_MSR_SINT4			0x40000094
#define HV_X64_MSR_SINT5			0x40000095
#define HV_X64_MSR_SINT6			0x40000096
#define HV_X64_MSR_SINT7			0x40000097
#define HV_X64_MSR_SINT8			0x40000098
#define HV_X64_MSR_SINT9			0x40000099
#define HV_X64_MSR_SINT10			0x4000009A
#define HV_X64_MSR_SINT11			0x4000009B
#define HV_X64_MSR_SINT12			0x4000009C
#define HV_X64_MSR_SINT13			0x4000009D
#define HV_X64_MSR_SINT14			0x4000009E
#define HV_X64_MSR_SINT15			0x4000009F

/*
 * Synthetic Timer MSRs. Four timers per vcpu.
 */
#define HV_X64_MSR_STIMER0_CONFIG		0x400000B0
#define HV_X64_MSR_STIMER0_COUNT		0x400000B1
#define HV_X64_MSR_STIMER1_CONFIG		0x400000B2
#define HV_X64_MSR_STIMER1_COUNT		0x400000B3
#define HV_X64_MSR_STIMER2_CONFIG		0x400000B4
#define HV_X64_MSR_STIMER2_COUNT		0x400000B5
#define HV_X64_MSR_STIMER3_CONFIG		0x400000B6
#define HV_X64_MSR_STIMER3_COUNT		0x400000B7

/* Hyper-V guest idle MSR */
#define HV_X64_MSR_GUEST_IDLE			0x400000F0

/* Hyper-V guest crash notification MSR's */
#define HV_X64_MSR_CRASH_P0			0x40000100
#define HV_X64_MSR_CRASH_P1			0x40000101
#define HV_X64_MSR_CRASH_P2			0x40000102
#define HV_X64_MSR_CRASH_P3			0x40000103
#define HV_X64_MSR_CRASH_P4			0x40000104
#define HV_X64_MSR_CRASH_CTL			0x40000105

/* TSC emulation after migration */
#define HV_X64_MSR_REENLIGHTENMENT_CONTROL	0x40000106
#define HV_X64_MSR_TSC_EMULATION_CONTROL	0x40000107
#define HV_X64_MSR_TSC_EMULATION_STATUS		0x40000108

/*
 * Declare the MSR used to setup pages used to communicate with the hypervisor.
 */
union hv_x64_msr_hypercall_contents {
	uint64_t as_uint64;
	struct {
		uint64_t enable:1;
		uint64_t reserved:11;
		uint64_t guest_physical_address:52;
	};
};

/*
 * TSC page layout.
 */
struct ms_hyperv_tsc_page {
	volatile uint32_t tsc_sequence;
	uint32_t reserved1;
	volatile uint64_t tsc_scale;
	volatile int64_t tsc_offset;
	uint64_t reserved2[509];
};

/*
 * The guest OS needs to register the guest ID with the hypervisor.
 * The guest ID is a 64 bit entity and the structure of this ID is
 * specified in the Hyper-V specification:
 *
 * msdn.microsoft.com/en-us/library/windows/hardware/ff542653%28v=vs.85%29.aspx
 *
 * While the current guideline does not specify how Linux guest ID(s)
 * need to be generated, our plan is to publish the guidelines for
 * Linux and other guest operating systems that currently are hosted
 * on Hyper-V. The implementation here conforms to this yet
 * unpublished guidelines.
 *
 *
 * Bit(s)
 * 63 - Indicates if the OS is Open Source or not; 1 is Open Source
 * 62:56 - Os Type; Linux 0x1, FreeBSD 0x2, Xen 0x3
 * 55:48 - Distro specific identification
 * 47:16 - Guest OS version number
 * 15:0  - Distro specific identification
 *
 *
 */

#define HV_LINUX_VENDOR_ID              0x8100
#define HV_XEN_VENDOR_ID                0x8300
union hv_guest_os_id
{
    uint64_t raw;
    struct
    {
        uint64_t build_number:16;
        uint64_t service_pack:8;
        uint64_t minor:8;
        uint64_t major:8;
        uint64_t os:8;
        uint64_t vendor:16;
    };
};

struct hv_reenlightenment_control {
	uint64_t vector:8;
	uint64_t reserved1:8;
	uint64_t enabled:1;
	uint64_t reserved2:15;
	uint64_t target_vp:32;
};

struct hv_tsc_emulation_control {
	uint64_t enabled:1;
	uint64_t reserved:63;
};

struct hv_tsc_emulation_status {
	uint64_t inprogress:1;
	uint64_t reserved:63;
};

#define HV_X64_MSR_HYPERCALL_ENABLE		0x00000001
#define HV_X64_MSR_HYPERCALL_PAGE_ADDRESS_SHIFT	12
#define HV_X64_MSR_HYPERCALL_PAGE_ADDRESS_MASK	\
		(~((1ull << HV_X64_MSR_HYPERCALL_PAGE_ADDRESS_SHIFT) - 1))

/*
 * Crash notification (HV_X64_MSR_CRASH_CTL) flags.
 */
#define HV_CRASH_CTL_CRASH_NOTIFY_MSG		BIT_ULL(62)
#define HV_CRASH_CTL_CRASH_NOTIFY		BIT_ULL(63)
#define HV_X64_MSR_CRASH_PARAMS		\
		(1 + (HV_X64_MSR_CRASH_P4 - HV_X64_MSR_CRASH_P0))

#define HV_IPI_LOW_VECTOR	0x10
#define HV_IPI_HIGH_VECTOR	0xff

/* Declare the various hypercall operations. */
#define HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE	0x0002
#define HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST	0x0003
#define HVCALL_NOTIFY_LONG_SPIN_WAIT		0x0008
#define HVCALL_SEND_IPI				0x000b
#define HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE_EX  0x0013
#define HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST_EX   0x0014
#define HVCALL_SEND_IPI_EX			0x0015
#define HVCALL_POST_MESSAGE			0x005c
#define HVCALL_SIGNAL_EVENT			0x005d
#define HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_SPACE 0x00af
#define HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST 0x00b0
#define HVCALL_EXT_CALL_QUERY_CAPABILITIES	0x8001

#define HV_X64_MSR_VP_ASSIST_PAGE_ENABLE	0x00000001
#define HV_X64_MSR_VP_ASSIST_PAGE_ADDRESS_SHIFT	12
#define HV_X64_MSR_VP_ASSIST_PAGE_ADDRESS_MASK	\
		(~((1ull << HV_X64_MSR_VP_ASSIST_PAGE_ADDRESS_SHIFT) - 1))

/* Hyper-V Enlightened VMCS version mask in nested features CPUID */
#define HV_X64_ENLIGHTENED_VMCS_VERSION		0xff

#define HV_X64_MSR_TSC_REFERENCE_ENABLE		0x00000001
#define HV_X64_MSR_TSC_REFERENCE_ADDRESS_SHIFT	12

#define HV_PROCESSOR_POWER_STATE_C0		0
#define HV_PROCESSOR_POWER_STATE_C1		1
#define HV_PROCESSOR_POWER_STATE_C2		2
#define HV_PROCESSOR_POWER_STATE_C3		3

#define HV_FLUSH_ALL_PROCESSORS			BIT(0, UL)
#define HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES	BIT(1, UL)
#define HV_FLUSH_NON_GLOBAL_MAPPINGS_ONLY	BIT(2, UL)
#define HV_FLUSH_USE_EXTENDED_RANGE_FORMAT	BIT(3, UL)

enum HV_GENERIC_SET_FORMAT {
	HV_GENERIC_SET_SPARSE_4K,
	HV_GENERIC_SET_ALL,
};

#define HV_HYPERCALL_RESULT_MASK	0xffff /* GENMASK_ULL(15, 0) */
#define HV_HYPERCALL_FAST_BIT		BIT(16, UL)
#define HV_HYPERCALL_VARHEAD_OFFSET	17
#define HV_HYPERCALL_REP_COMP_OFFSET	32
#define HV_HYPERCALL_REP_COMP_MASK	(0xfffULL << HV_HYPERCALL_REP_COMP_OFFSET) /* GENMASK_ULL(43, 32) */
#define HV_HYPERCALL_REP_START_OFFSET	48
#define HV_HYPERCALL_REP_START_MASK	(0xfffULL << HV_HYPERCALL_REP_START_OFFSET) /* GENMASK_ULL(59, 48) */

/* hypercall status code */
#define HV_STATUS_SUCCESS			0
#define HV_STATUS_INVALID_HYPERCALL_CODE	2
#define HV_STATUS_INVALID_HYPERCALL_INPUT	3
#define HV_STATUS_INVALID_ALIGNMENT		4
#define HV_STATUS_INVALID_PARAMETER		5
#define HV_STATUS_INSUFFICIENT_MEMORY		11
#define HV_STATUS_INVALID_PORT_ID		17
#define HV_STATUS_INVALID_CONNECTION_ID		18
#define HV_STATUS_INSUFFICIENT_BUFFERS		19

/*
 * The Hyper-V TimeRefCount register and the TSC
 * page provide a guest VM clock with 100ns tick rate
 */
#define HV_CLOCK_HZ (NSEC_PER_SEC/100)

typedef struct _HV_REFERENCE_TSC_PAGE {
	uint32_t tsc_sequence;
	uint32_t res1;
	uint64_t tsc_scale;
	int64_t tsc_offset;
} HV_REFERENCE_TSC_PAGE, *PHV_REFERENCE_TSC_PAGE;

/* Define the number of synthetic interrupt sources. */
#define HV_SYNIC_SINT_COUNT		(16)
/* Define the expected SynIC version. */
#define HV_SYNIC_VERSION_1		(0x1)
/* Valid SynIC vectors are 16-255. */
#define HV_SYNIC_FIRST_VALID_VECTOR	(16)

#define HV_SYNIC_CONTROL_ENABLE		(1ULL << 0)
#define HV_SYNIC_SIMP_ENABLE		(1ULL << 0)
#define HV_SYNIC_SIEFP_ENABLE		(1ULL << 0)
#define HV_SYNIC_SINT_MASKED		(1ULL << 16)
#define HV_SYNIC_SINT_AUTO_EOI		(1ULL << 17)
#define HV_SYNIC_SINT_VECTOR_MASK	(0xFF)

#define HV_SYNIC_STIMER_COUNT		(4)

/* Define synthetic interrupt controller message constants. */
#define HV_MESSAGE_SIZE			(256)
#define HV_MESSAGE_PAYLOAD_BYTE_COUNT	(240)
#define HV_MESSAGE_PAYLOAD_QWORD_COUNT	(30)

/* Define hypervisor message types. */
enum hv_message_type {
	HVMSG_NONE			= 0x00000000U,

	/* Memory access messages. */
	HVMSG_UNMAPPED_GPA		= 0x80000000U,
	HVMSG_GPA_INTERCEPT		= 0x80000001U,

	/* Timer notification messages. */
	HVMSG_TIMER_EXPIRED			= 0x80000010U,

	/* Error messages. */
	HVMSG_INVALID_VP_REGISTER_VALUE	= 0x80000020U,
	HVMSG_UNRECOVERABLE_EXCEPTION	= 0x80000021U,
	HVMSG_UNSUPPORTED_FEATURE		= 0x80000022U,

	/* Trace buffer complete messages. */
	HVMSG_EVENTLOG_BUFFERCOMPLETE	= 0x80000040U,

	/* Platform-specific processor intercept messages. */
	HVMSG_X64_IOPORT_INTERCEPT		= 0x80010000U,
	HVMSG_X64_MSR_INTERCEPT		= 0x80010001U,
	HVMSG_X64_CPUID_INTERCEPT		= 0x80010002U,
	HVMSG_X64_EXCEPTION_INTERCEPT	= 0x80010003U,
	HVMSG_X64_APIC_EOI			= 0x80010004U,
	HVMSG_X64_LEGACY_FP_ERROR		= 0x80010005U
};

/* Define synthetic interrupt controller message flags. */
union hv_message_flags {
	uint8_t asu8;
	struct {
		uint8_t msg_pending:1;
		uint8_t reserved:7;
	};
};

/* Define port identifier type. */
union hv_port_id {
	uint32_t asu32;
	struct {
		uint32_t id:24;
		uint32_t reserved:8;
	} u;
};

/* Define synthetic interrupt controller message header. */
struct hv_message_header {
	uint32_t message_type;
	uint8_t payload_size;
	union hv_message_flags message_flags;
	uint8_t reserved[2];
	union {
		uint64_t sender;
		union hv_port_id port;
	};
};

/* Define synthetic interrupt controller message format. */
struct hv_message {
	struct hv_message_header header;
	union {
		uint64_t payload[HV_MESSAGE_PAYLOAD_QWORD_COUNT];
	} u;
};

/* Define the synthetic interrupt message page layout. */
struct hv_message_page {
	struct hv_message sint_message[HV_SYNIC_SINT_COUNT];
};

/* Define timer message payload structure. */
struct hv_timer_message_payload {
	uint32_t timer_index;
	uint32_t reserved;
	uint64_t expiration_time; /* When the timer expired */
	uint64_t delivery_time;   /* When the message was delivered */
};

struct hv_nested_enlightenments_control {
	struct {
		uint32_t directhypercall:1;
		uint32_t reserved:31;
	} features;
	struct {
		uint32_t reserved;
	} hypercallControls;
};

union hv_vp_assist_page_msr
{
    uint64_t raw;
    struct
    {
        uint64_t enabled:1;
        uint64_t reserved_preserved:11;
        uint64_t pfn:48;
    };
};

/* Define virtual processor assist page structure. */
struct hv_vp_assist_page {
	uint32_t apic_assist;
	uint32_t reserved1;
	uint64_t vtl_control[3];
	struct hv_nested_enlightenments_control nested_control;
	uint8_t enlighten_vmentry;
	uint8_t reserved2[7];
	uint64_t current_nested_vmcs;
};

struct hv_enlightened_vmcs {
	uint32_t revision_id;
	uint32_t abort;

	uint16_t host_es_selector;
	uint16_t host_cs_selector;
	uint16_t host_ss_selector;
	uint16_t host_ds_selector;
	uint16_t host_fs_selector;
	uint16_t host_gs_selector;
	uint16_t host_tr_selector;

	uint16_t padding16_1;

	uint64_t host_ia32_pat;
	uint64_t host_ia32_efer;

	uint64_t host_cr0;
	uint64_t host_cr3;
	uint64_t host_cr4;

	uint64_t host_ia32_sysenter_esp;
	uint64_t host_ia32_sysenter_eip;
	uint64_t host_rip;
	uint32_t host_ia32_sysenter_cs;

	uint32_t pin_based_vm_exec_control;
	uint32_t vm_exit_controls;
	uint32_t secondary_vm_exec_control;

	uint64_t io_bitmap_a;
	uint64_t io_bitmap_b;
	uint64_t msr_bitmap;

	uint16_t guest_es_selector;
	uint16_t guest_cs_selector;
	uint16_t guest_ss_selector;
	uint16_t guest_ds_selector;
	uint16_t guest_fs_selector;
	uint16_t guest_gs_selector;
	uint16_t guest_ldtr_selector;
	uint16_t guest_tr_selector;

	uint32_t guest_es_limit;
	uint32_t guest_cs_limit;
	uint32_t guest_ss_limit;
	uint32_t guest_ds_limit;
	uint32_t guest_fs_limit;
	uint32_t guest_gs_limit;
	uint32_t guest_ldtr_limit;
	uint32_t guest_tr_limit;
	uint32_t guest_gdtr_limit;
	uint32_t guest_idtr_limit;

	uint32_t guest_es_ar_bytes;
	uint32_t guest_cs_ar_bytes;
	uint32_t guest_ss_ar_bytes;
	uint32_t guest_ds_ar_bytes;
	uint32_t guest_fs_ar_bytes;
	uint32_t guest_gs_ar_bytes;
	uint32_t guest_ldtr_ar_bytes;
	uint32_t guest_tr_ar_bytes;

	uint64_t guest_es_base;
	uint64_t guest_cs_base;
	uint64_t guest_ss_base;
	uint64_t guest_ds_base;
	uint64_t guest_fs_base;
	uint64_t guest_gs_base;
	uint64_t guest_ldtr_base;
	uint64_t guest_tr_base;
	uint64_t guest_gdtr_base;
	uint64_t guest_idtr_base;

	uint64_t padding64_1[3];

	uint64_t vm_exit_msr_store_addr;
	uint64_t vm_exit_msr_load_addr;
	uint64_t vm_entry_msr_load_addr;

	uint64_t cr3_target_value0;
	uint64_t cr3_target_value1;
	uint64_t cr3_target_value2;
	uint64_t cr3_target_value3;

	uint32_t page_fault_error_code_mask;
	uint32_t page_fault_error_code_match;

	uint32_t cr3_target_count;
	uint32_t vm_exit_msr_store_count;
	uint32_t vm_exit_msr_load_count;
	uint32_t vm_entry_msr_load_count;

	uint64_t tsc_offset;
	uint64_t virtual_apic_page_addr;
	uint64_t vmcs_link_pointer;

	uint64_t guest_ia32_debugctl;
	uint64_t guest_ia32_pat;
	uint64_t guest_ia32_efer;

	uint64_t guest_pdptr0;
	uint64_t guest_pdptr1;
	uint64_t guest_pdptr2;
	uint64_t guest_pdptr3;

	uint64_t guest_pending_dbg_exceptions;
	uint64_t guest_sysenter_esp;
	uint64_t guest_sysenter_eip;

	uint32_t guest_activity_state;
	uint32_t guest_sysenter_cs;

	uint64_t cr0_guest_host_mask;
	uint64_t cr4_guest_host_mask;
	uint64_t cr0_read_shadow;
	uint64_t cr4_read_shadow;
	uint64_t guest_cr0;
	uint64_t guest_cr3;
	uint64_t guest_cr4;
	uint64_t guest_dr7;

	uint64_t host_fs_base;
	uint64_t host_gs_base;
	uint64_t host_tr_base;
	uint64_t host_gdtr_base;
	uint64_t host_idtr_base;
	uint64_t host_rsp;

	uint64_t ept_pointer;

	uint16_t virtual_processor_id;
	uint16_t padding16_2[3];

	uint64_t padding64_2[5];
	uint64_t guest_physical_address;

	uint32_t vm_instruction_error;
	uint32_t vm_exit_reason;
	uint32_t vm_exit_intr_info;
	uint32_t vm_exit_intr_error_code;
	uint32_t idt_vectoring_info_field;
	uint32_t idt_vectoring_error_code;
	uint32_t vm_exit_instruction_len;
	uint32_t vmx_instruction_info;

	uint64_t exit_qualification;
	uint64_t exit_io_instruction_ecx;
	uint64_t exit_io_instruction_esi;
	uint64_t exit_io_instruction_edi;
	uint64_t exit_io_instruction_eip;

	uint64_t guest_linear_address;
	uint64_t guest_rsp;
	uint64_t guest_rflags;

	uint32_t guest_interruptibility_info;
	uint32_t cpu_based_vm_exec_control;
	uint32_t exception_bitmap;
	uint32_t vm_entry_controls;
	uint32_t vm_entry_intr_info_field;
	uint32_t vm_entry_exception_error_code;
	uint32_t vm_entry_instruction_len;
	uint32_t tpr_threshold;

	uint64_t guest_rip;

	uint32_t hv_clean_fields;
	uint32_t hv_padding_32;
	uint32_t hv_synthetic_controls;
	struct {
		uint32_t nested_flush_hypercall:1;
		uint32_t msr_bitmap:1;
		uint32_t reserved:30;
	}  hv_enlightenments_control;
	uint32_t hv_vp_id;

	uint64_t hv_vm_id;
	uint64_t partition_assist_page;
	uint64_t padding64_4[4];
	uint64_t guest_bndcfgs;
	uint64_t padding64_5[7];
	uint64_t xss_exit_bitmap;
	uint64_t padding64_6[7];
};

#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_NONE			0
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_IO_BITMAP		BIT(0, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_MSR_BITMAP		BIT(1, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_GRP2		BIT(2, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_GRP1		BIT(3, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_PROC		BIT(4, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_EVENT		BIT(5, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_ENTRY		BIT(6, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_EXCPN		BIT(7, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CRDR			BIT(8, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_XLAT		BIT(9, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_BASIC		BIT(10, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP1		BIT(11, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP2		BIT(12, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_HOST_POINTER		BIT(13, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_HOST_GRP1		BIT(14, UL)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_ENLIGHTENMENTSCONTROL	BIT(15, UL)

#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_ALL			0xFFFF

/* Define synthetic interrupt controller flag constants. */
#define HV_EVENT_FLAGS_COUNT		(256 * 8)
#define HV_EVENT_FLAGS_LONG_COUNT	(256 / sizeof(unsigned long))

/*
 * Synthetic timer configuration.
 */
union hv_stimer_config {
	uint64_t as_uint64;
	struct {
		uint64_t enable:1;
		uint64_t periodic:1;
		uint64_t lazy:1;
		uint64_t auto_enable:1;
		uint64_t apic_vector:8;
		uint64_t direct_mode:1;
		uint64_t reserved_z0:3;
		uint64_t sintx:4;
		uint64_t reserved_z1:44;
	};
};


/* Define the synthetic interrupt controller event flags format. */
union hv_synic_event_flags {
	unsigned long flags[HV_EVENT_FLAGS_LONG_COUNT];
};

/* Define SynIC control register. */
union hv_synic_scontrol {
	uint64_t as_uint64;
	struct {
		uint64_t enable:1;
		uint64_t reserved:63;
	};
};

/* Define synthetic interrupt source. */
union hv_synic_sint {
	uint64_t as_uint64;
	struct {
		uint64_t vector:8;
		uint64_t reserved1:8;
		uint64_t masked:1;
		uint64_t auto_eoi:1;
		uint64_t polling:1;
		uint64_t reserved2:45;
	};
};

/* Define the format of the SIMP register */
union hv_synic_simp {
	uint64_t as_uint64;
	struct {
		uint64_t simp_enabled:1;
		uint64_t preserved:11;
		uint64_t base_simp_gpa:52;
	};
};

/* Define the format of the SIEFP register */
union hv_synic_siefp {
	uint64_t as_uint64;
	struct {
		uint64_t siefp_enabled:1;
		uint64_t preserved:11;
		uint64_t base_siefp_gpa:52;
	};
};

struct hv_vpset {
	uint64_t format;
	uint64_t valid_bank_mask;
	uint64_t bank_contents[];
};

/* HvCallSendSyntheticClusterIpi hypercall */
struct hv_send_ipi {
	uint32_t vector;
	uint32_t reserved;
	uint64_t cpu_mask;
};

/* HvCallSendSyntheticClusterIpiEx hypercall */
struct hv_send_ipi_ex {
	uint32_t vector;
	uint32_t reserved;
	struct hv_vpset vp_set;
};

/* HvFlushGuestPhysicalAddressSpace hypercalls */
struct hv_guest_mapping_flush {
	uint64_t address_space;
	uint64_t flags;
};

/*
 *  HV_MAX_FLUSH_PAGES = "additional_pages" + 1. It's limited
 *  by the bitwidth of "additional_pages" in union hv_gpa_page_range.
 */
#define HV_MAX_FLUSH_PAGES (2048)

/* HvFlushGuestPhysicalAddressList hypercall */
union hv_gpa_page_range {
	uint64_t address_space;
	struct {
		uint64_t additional_pages:11;
		uint64_t largepage:1;
		uint64_t basepfn:52;
	} page;
};

/*
 * All input flush parameters should be in single page. The max flush
 * count is equal with how many entries of union hv_gpa_page_range can
 * be populated into the input parameter page.
 */
#define HV_MAX_FLUSH_REP_COUNT ((HV_HYP_PAGE_SIZE - 2 * sizeof(uint64_t)) / \
				sizeof(union hv_gpa_page_range))

struct hv_guest_mapping_flush_list {
	uint64_t address_space;
	uint64_t flags;
	union hv_gpa_page_range gpa_list[HV_MAX_FLUSH_REP_COUNT];
};

/* HvFlushVirtualAddressSpace, HvFlushVirtualAddressList hypercalls */
struct hv_tlb_flush {
	uint64_t address_space;
	uint64_t flags;
	uint64_t processor_mask;
	uint64_t gva_list[];
};

/* HvFlushVirtualAddressSpaceEx hypercall */
struct hv_tlb_flush_ex {
	uint64_t address_space;
	uint64_t flags;
	struct hv_vpset hv_vp_set;
	/* uint64_t gva_list[]; */
};

struct hv_partition_assist_pg {
	uint32_t tlb_lock_count;
};
#endif
