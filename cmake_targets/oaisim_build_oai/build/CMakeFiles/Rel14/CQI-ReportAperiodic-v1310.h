/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_CQI_ReportAperiodic_v1310_H_
#define	_CQI_ReportAperiodic_v1310_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NULL.h>
#include <BIT_STRING.h>
#include <constr_SEQUENCE.h>
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum CQI_ReportAperiodic_v1310_PR {
	CQI_ReportAperiodic_v1310_PR_NOTHING,	/* No components present */
	CQI_ReportAperiodic_v1310_PR_release,
	CQI_ReportAperiodic_v1310_PR_setup
} CQI_ReportAperiodic_v1310_PR;
typedef enum CQI_ReportAperiodic_v1310__setup__aperiodicCSI_Trigger2_r13_PR {
	CQI_ReportAperiodic_v1310__setup__aperiodicCSI_Trigger2_r13_PR_NOTHING,	/* No components present */
	CQI_ReportAperiodic_v1310__setup__aperiodicCSI_Trigger2_r13_PR_release,
	CQI_ReportAperiodic_v1310__setup__aperiodicCSI_Trigger2_r13_PR_setup
} CQI_ReportAperiodic_v1310__setup__aperiodicCSI_Trigger2_r13_PR;

/* CQI-ReportAperiodic-v1310 */
typedef struct CQI_ReportAperiodic_v1310 {
	CQI_ReportAperiodic_v1310_PR present;
	union CQI_ReportAperiodic_v1310_u {
		NULL_t	 release;
		struct CQI_ReportAperiodic_v1310__setup {
			struct CQI_ReportAperiodic_v1310__setup__aperiodicCSI_Trigger_v1310 {
				BIT_STRING_t	 trigger1_r13;
				BIT_STRING_t	 trigger2_r13;
				BIT_STRING_t	 trigger3_r13;
				BIT_STRING_t	 trigger4_r13;
				BIT_STRING_t	 trigger5_r13;
				BIT_STRING_t	 trigger6_r13;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *aperiodicCSI_Trigger_v1310;
			struct CQI_ReportAperiodic_v1310__setup__aperiodicCSI_Trigger2_r13 {
				CQI_ReportAperiodic_v1310__setup__aperiodicCSI_Trigger2_r13_PR present;
				union CQI_ReportAperiodic_v1310__setup__aperiodicCSI_Trigger2_r13_u {
					NULL_t	 release;
					struct CQI_ReportAperiodic_v1310__setup__aperiodicCSI_Trigger2_r13__setup {
						BIT_STRING_t	 trigger1_SubframeSetIndicator_r13;
						BIT_STRING_t	 trigger2_SubframeSetIndicator_r13;
						BIT_STRING_t	 trigger3_SubframeSetIndicator_r13;
						BIT_STRING_t	 trigger4_SubframeSetIndicator_r13;
						BIT_STRING_t	 trigger5_SubframeSetIndicator_r13;
						BIT_STRING_t	 trigger6_SubframeSetIndicator_r13;
						
						/* Context for parsing across buffer boundaries */
						asn_struct_ctx_t _asn_ctx;
					} setup;
				} choice;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *aperiodicCSI_Trigger2_r13;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} setup;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CQI_ReportAperiodic_v1310_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CQI_ReportAperiodic_v1310;

#ifdef __cplusplus
}
#endif

#endif	/* _CQI_ReportAperiodic_v1310_H_ */
#include <asn_internal.h>
