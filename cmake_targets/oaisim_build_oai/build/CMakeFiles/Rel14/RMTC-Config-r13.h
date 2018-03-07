/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_RMTC_Config_r13_H_
#define	_RMTC_Config_r13_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NULL.h>
#include <NativeEnumerated.h>
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RMTC_Config_r13_PR {
	RMTC_Config_r13_PR_NOTHING,	/* No components present */
	RMTC_Config_r13_PR_release,
	RMTC_Config_r13_PR_setup
} RMTC_Config_r13_PR;
typedef enum RMTC_Config_r13__setup__rmtc_Period_r13 {
	RMTC_Config_r13__setup__rmtc_Period_r13_ms40	= 0,
	RMTC_Config_r13__setup__rmtc_Period_r13_ms80	= 1,
	RMTC_Config_r13__setup__rmtc_Period_r13_ms160	= 2,
	RMTC_Config_r13__setup__rmtc_Period_r13_ms320	= 3,
	RMTC_Config_r13__setup__rmtc_Period_r13_ms640	= 4
} e_RMTC_Config_r13__setup__rmtc_Period_r13;
typedef enum RMTC_Config_r13__setup__measDuration_r13 {
	RMTC_Config_r13__setup__measDuration_r13_sym1	= 0,
	RMTC_Config_r13__setup__measDuration_r13_sym14	= 1,
	RMTC_Config_r13__setup__measDuration_r13_sym28	= 2,
	RMTC_Config_r13__setup__measDuration_r13_sym42	= 3,
	RMTC_Config_r13__setup__measDuration_r13_sym70	= 4
} e_RMTC_Config_r13__setup__measDuration_r13;

/* RMTC-Config-r13 */
typedef struct RMTC_Config_r13 {
	RMTC_Config_r13_PR present;
	union RMTC_Config_r13_u {
		NULL_t	 release;
		struct RMTC_Config_r13__setup {
			long	 rmtc_Period_r13;
			long	*rmtc_SubframeOffset_r13	/* OPTIONAL */;
			long	 measDuration_r13;
			/*
			 * This type is extensible,
			 * possible extensions are below.
			 */
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} setup;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RMTC_Config_r13_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_rmtc_Period_r13_4;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_measDuration_r13_11;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_RMTC_Config_r13;

#ifdef __cplusplus
}
#endif

#endif	/* _RMTC_Config_r13_H_ */
#include <asn_internal.h>
