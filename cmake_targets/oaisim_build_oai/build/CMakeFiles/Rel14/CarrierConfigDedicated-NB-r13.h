/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "NBIOT-RRC-Definitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_CarrierConfigDedicated_NB_r13_H_
#define	_CarrierConfigDedicated_NB_r13_H_


#include <asn_application.h>

/* Including external dependencies */
#include "DL-CarrierConfigDedicated-NB-r13.h"
#include "UL-CarrierConfigDedicated-NB-r13.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* CarrierConfigDedicated-NB-r13 */
typedef struct CarrierConfigDedicated_NB_r13 {
	DL_CarrierConfigDedicated_NB_r13_t	 dl_CarrierConfig_r13;
	UL_CarrierConfigDedicated_NB_r13_t	 ul_CarrierConfig_r13;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CarrierConfigDedicated_NB_r13_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CarrierConfigDedicated_NB_r13;

#ifdef __cplusplus
}
#endif

#endif	/* _CarrierConfigDedicated_NB_r13_H_ */
#include <asn_internal.h>
