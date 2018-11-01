/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-InterNodeDefinitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#include "AS-Config-v1250.h"

static asn_TYPE_member_t asn_MBR_AS_Config_v1250_1[] = {
	{ ATF_POINTER, 3, offsetof(struct AS_Config_v1250, sourceWlan_OffloadConfig_r12),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_WLAN_OffloadConfig_r12,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sourceWlan-OffloadConfig-r12"
		},
	{ ATF_POINTER, 2, offsetof(struct AS_Config_v1250, sourceSL_CommConfig_r12),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SL_CommConfig_r12,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sourceSL-CommConfig-r12"
		},
	{ ATF_POINTER, 1, offsetof(struct AS_Config_v1250, sourceSL_DiscConfig_r12),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SL_DiscConfig_r12,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sourceSL-DiscConfig-r12"
		},
};
static int asn_MAP_AS_Config_v1250_oms_1[] = { 0, 1, 2 };
static ber_tlv_tag_t asn_DEF_AS_Config_v1250_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_AS_Config_v1250_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* sourceWlan-OffloadConfig-r12 at 11780 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* sourceSL-CommConfig-r12 at 11781 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* sourceSL-DiscConfig-r12 at 11782 */
};
static asn_SEQUENCE_specifics_t asn_SPC_AS_Config_v1250_specs_1 = {
	sizeof(struct AS_Config_v1250),
	offsetof(struct AS_Config_v1250, _asn_ctx),
	asn_MAP_AS_Config_v1250_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_AS_Config_v1250_oms_1,	/* Optional members */
	3, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_AS_Config_v1250 = {
	"AS-Config-v1250",
	"AS-Config-v1250",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	SEQUENCE_decode_uper,
	SEQUENCE_encode_uper,
	SEQUENCE_decode_aper,
	SEQUENCE_encode_aper,
	SEQUENCE_compare,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_AS_Config_v1250_tags_1,
	sizeof(asn_DEF_AS_Config_v1250_tags_1)
		/sizeof(asn_DEF_AS_Config_v1250_tags_1[0]), /* 1 */
	asn_DEF_AS_Config_v1250_tags_1,	/* Same as above */
	sizeof(asn_DEF_AS_Config_v1250_tags_1)
		/sizeof(asn_DEF_AS_Config_v1250_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_AS_Config_v1250_1,
	3,	/* Elements count */
	&asn_SPC_AS_Config_v1250_specs_1	/* Additional specs */
};
