/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_PDCCH_ConfigLAA_r14_H_
#define	_PDCCH_ConfigLAA_r14_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>
#include <NULL.h>
#include <constr_SEQUENCE.h>
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14_PR {
	PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14_PR_NOTHING,	/* No components present */
	PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14_PR_release,
	PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14_PR_setup
} PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14_PR;
typedef enum PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14__setup__maxNumberOfSchedSubframes_Format0B_r14 {
	PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14__setup__maxNumberOfSchedSubframes_Format0B_r14_sf2	= 0,
	PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14__setup__maxNumberOfSchedSubframes_Format0B_r14_sf3	= 1,
	PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14__setup__maxNumberOfSchedSubframes_Format0B_r14_sf4	= 2
} e_PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14__setup__maxNumberOfSchedSubframes_Format0B_r14;
typedef enum PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14_PR {
	PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14_PR_NOTHING,	/* No components present */
	PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14_PR_release,
	PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14_PR_setup
} PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14_PR;
typedef enum PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14__setup__maxNumberOfSchedSubframes_Format4B_r14 {
	PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14__setup__maxNumberOfSchedSubframes_Format4B_r14_sf2	= 0,
	PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14__setup__maxNumberOfSchedSubframes_Format4B_r14_sf3	= 1,
	PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14__setup__maxNumberOfSchedSubframes_Format4B_r14_sf4	= 2
} e_PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14__setup__maxNumberOfSchedSubframes_Format4B_r14;
typedef enum PDCCH_ConfigLAA_r14__skipMonitoringDCI_Format0A_r14 {
	PDCCH_ConfigLAA_r14__skipMonitoringDCI_Format0A_r14_true	= 0
} e_PDCCH_ConfigLAA_r14__skipMonitoringDCI_Format0A_r14;
typedef enum PDCCH_ConfigLAA_r14__skipMonitoringDCI_Format4A_r14 {
	PDCCH_ConfigLAA_r14__skipMonitoringDCI_Format4A_r14_true	= 0
} e_PDCCH_ConfigLAA_r14__skipMonitoringDCI_Format4A_r14;

/* Forward declarations */
struct PDCCH_CandidateReductions_r13;
struct PDCCH_CandidateReductionsLAA_UL_r14;

/* PDCCH-ConfigLAA-r14 */
typedef struct PDCCH_ConfigLAA_r14 {
	struct PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14 {
		PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14_PR present;
		union PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14_u {
			NULL_t	 release;
			struct PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format0B_r14__setup {
				long	 maxNumberOfSchedSubframes_Format0B_r14;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} setup;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *enableMonitoringDCI_Format0B_r14;
	struct PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14 {
		PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14_PR present;
		union PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14_u {
			NULL_t	 release;
			struct PDCCH_ConfigLAA_r14__enableMonitoringDCI_Format4B_r14__setup {
				long	 maxNumberOfSchedSubframes_Format4B_r14;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} setup;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *enableMonitoringDCI_Format4B_r14;
	long	*skipMonitoringDCI_Format0A_r14	/* OPTIONAL */;
	long	*skipMonitoringDCI_Format4A_r14	/* OPTIONAL */;
	struct PDCCH_CandidateReductions_r13	*pdcch_CandidateReductions_Format0A_r14	/* OPTIONAL */;
	struct PDCCH_CandidateReductionsLAA_UL_r14	*pdcch_CandidateReductions_Format4A_r14	/* OPTIONAL */;
	struct PDCCH_CandidateReductionsLAA_UL_r14	*pdcch_CandidateReductions_Format0B_r14	/* OPTIONAL */;
	struct PDCCH_CandidateReductionsLAA_UL_r14	*pdcch_CandidateReductions_Format4B_r14	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PDCCH_ConfigLAA_r14_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_maxNumberOfSchedSubframes_Format0B_r14_5;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_maxNumberOfSchedSubframes_Format4B_r14_12;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_skipMonitoringDCI_Format0A_r14_16;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_skipMonitoringDCI_Format4A_r14_18;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_PDCCH_ConfigLAA_r14;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "PDCCH-CandidateReductions-r13.h"
#include "PDCCH-CandidateReductionsLAA-UL-r14.h"

#endif	/* _PDCCH_ConfigLAA_r14_H_ */
#include <asn_internal.h>