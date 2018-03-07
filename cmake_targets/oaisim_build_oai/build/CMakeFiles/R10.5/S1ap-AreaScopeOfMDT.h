/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "S1AP-IEs"
 * 	found in "/home/liu/openairinterface5g/openair3/S1AP/MESSAGES/ASN1/R10.5/S1AP-IEs.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_S1ap_AreaScopeOfMDT_H_
#define	_S1ap_AreaScopeOfMDT_H_


#include <asn_application.h>

/* Including external dependencies */
#include "S1ap-CellBasedMDT.h"
#include "S1ap-TABasedMDT.h"
#include <NULL.h>
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum S1ap_AreaScopeOfMDT_PR {
	S1ap_AreaScopeOfMDT_PR_NOTHING,	/* No components present */
	S1ap_AreaScopeOfMDT_PR_cellBased,
	S1ap_AreaScopeOfMDT_PR_tABased,
	S1ap_AreaScopeOfMDT_PR_pLMNWide,
	/* Extensions may appear below */
	
} S1ap_AreaScopeOfMDT_PR;

/* S1ap-AreaScopeOfMDT */
typedef struct S1ap_AreaScopeOfMDT {
	S1ap_AreaScopeOfMDT_PR present;
	union S1ap_AreaScopeOfMDT_u {
		S1ap_CellBasedMDT_t	 cellBased;
		S1ap_TABasedMDT_t	 tABased;
		NULL_t	 pLMNWide;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} S1ap_AreaScopeOfMDT_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_S1ap_AreaScopeOfMDT;

#ifdef __cplusplus
}
#endif

#endif	/* _S1ap_AreaScopeOfMDT_H_ */
#include <asn_internal.h>
