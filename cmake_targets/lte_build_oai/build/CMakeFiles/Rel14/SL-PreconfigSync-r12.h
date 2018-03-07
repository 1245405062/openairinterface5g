/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-Sidelink-Preconf"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_SL_PreconfigSync_r12_H_
#define	_SL_PreconfigSync_r12_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SL-CP-Len-r12.h"
#include "SL-OffsetIndicatorSync-r12.h"
#include "P0-SL-r12.h"
#include "RSRP-RangeSL3-r12.h"
#include "FilterCoefficient.h"
#include <NativeEnumerated.h>
#include <constr_SEQUENCE.h>
#include "SL-OffsetIndicatorSync-v14xy.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SL_PreconfigSync_r12__syncRefMinHyst_r12 {
	SL_PreconfigSync_r12__syncRefMinHyst_r12_dB0	= 0,
	SL_PreconfigSync_r12__syncRefMinHyst_r12_dB3	= 1,
	SL_PreconfigSync_r12__syncRefMinHyst_r12_dB6	= 2,
	SL_PreconfigSync_r12__syncRefMinHyst_r12_dB9	= 3,
	SL_PreconfigSync_r12__syncRefMinHyst_r12_dB12	= 4
} e_SL_PreconfigSync_r12__syncRefMinHyst_r12;
typedef enum SL_PreconfigSync_r12__syncRefDiffHyst_r12 {
	SL_PreconfigSync_r12__syncRefDiffHyst_r12_dB0	= 0,
	SL_PreconfigSync_r12__syncRefDiffHyst_r12_dB3	= 1,
	SL_PreconfigSync_r12__syncRefDiffHyst_r12_dB6	= 2,
	SL_PreconfigSync_r12__syncRefDiffHyst_r12_dB9	= 3,
	SL_PreconfigSync_r12__syncRefDiffHyst_r12_dB12	= 4,
	SL_PreconfigSync_r12__syncRefDiffHyst_r12_dBinf	= 5
} e_SL_PreconfigSync_r12__syncRefDiffHyst_r12;
typedef enum SL_PreconfigSync_r12__ext1__syncTxPeriodic_r13 {
	SL_PreconfigSync_r12__ext1__syncTxPeriodic_r13_true	= 0
} e_SL_PreconfigSync_r12__ext1__syncTxPeriodic_r13;

/* SL-PreconfigSync-r12 */
typedef struct SL_PreconfigSync_r12 {
	SL_CP_Len_r12_t	 syncCP_Len_r12;
	SL_OffsetIndicatorSync_r12_t	 syncOffsetIndicator1_r12;
	SL_OffsetIndicatorSync_r12_t	 syncOffsetIndicator2_r12;
	P0_SL_r12_t	 syncTxParameters_r12;
	RSRP_RangeSL3_r12_t	 syncTxThreshOoC_r12;
	FilterCoefficient_t	 filterCoefficient_r12;
	long	 syncRefMinHyst_r12;
	long	 syncRefDiffHyst_r12;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	struct SL_PreconfigSync_r12__ext1 {
		long	*syncTxPeriodic_r13	/* OPTIONAL */;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext1;
	struct SL_PreconfigSync_r12__ext2 {
		SL_OffsetIndicatorSync_v14xy_t	*syncOffsetIndicator1_v14xy	/* OPTIONAL */;
		SL_OffsetIndicatorSync_v14xy_t	*syncOffsetIndicator2_v14xy	/* OPTIONAL */;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext2;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SL_PreconfigSync_r12_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_syncRefMinHyst_r12_8;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_syncRefDiffHyst_r12_14;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_syncTxPeriodic_r13_23;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_SL_PreconfigSync_r12;

#ifdef __cplusplus
}
#endif

#endif	/* _SL_PreconfigSync_r12_H_ */
#include <asn_internal.h>
