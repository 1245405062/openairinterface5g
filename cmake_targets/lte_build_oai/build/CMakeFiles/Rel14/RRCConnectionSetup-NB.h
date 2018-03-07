/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "NBIOT-RRC-Definitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_RRCConnectionSetup_NB_H_
#define	_RRCConnectionSetup_NB_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RRC-TransactionIdentifier.h"
#include "RRCConnectionSetup-NB-r13-IEs.h"
#include <NULL.h>
#include <constr_CHOICE.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RRCConnectionSetup_NB__criticalExtensions_PR {
	RRCConnectionSetup_NB__criticalExtensions_PR_NOTHING,	/* No components present */
	RRCConnectionSetup_NB__criticalExtensions_PR_c1,
	RRCConnectionSetup_NB__criticalExtensions_PR_criticalExtensionsFuture
} RRCConnectionSetup_NB__criticalExtensions_PR;
typedef enum RRCConnectionSetup_NB__criticalExtensions__c1_PR {
	RRCConnectionSetup_NB__criticalExtensions__c1_PR_NOTHING,	/* No components present */
	RRCConnectionSetup_NB__criticalExtensions__c1_PR_rrcConnectionSetup_r13,
	RRCConnectionSetup_NB__criticalExtensions__c1_PR_spare1
} RRCConnectionSetup_NB__criticalExtensions__c1_PR;

/* RRCConnectionSetup-NB */
typedef struct RRCConnectionSetup_NB {
	RRC_TransactionIdentifier_t	 rrc_TransactionIdentifier;
	struct RRCConnectionSetup_NB__criticalExtensions {
		RRCConnectionSetup_NB__criticalExtensions_PR present;
		union RRCConnectionSetup_NB__criticalExtensions_u {
			struct RRCConnectionSetup_NB__criticalExtensions__c1 {
				RRCConnectionSetup_NB__criticalExtensions__c1_PR present;
				union RRCConnectionSetup_NB__criticalExtensions__c1_u {
					RRCConnectionSetup_NB_r13_IEs_t	 rrcConnectionSetup_r13;
					NULL_t	 spare1;
				} choice;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} c1;
			struct RRCConnectionSetup_NB__criticalExtensions__criticalExtensionsFuture {
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} criticalExtensionsFuture;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} criticalExtensions;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRCConnectionSetup_NB_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RRCConnectionSetup_NB;

#ifdef __cplusplus
}
#endif

#endif	/* _RRCConnectionSetup_NB_H_ */
#include <asn_internal.h>
