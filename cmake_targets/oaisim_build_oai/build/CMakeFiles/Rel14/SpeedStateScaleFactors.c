/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#include "SpeedStateScaleFactors.h"

static int
sf_Medium_2_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	/* Replace with underlying type checker */
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
	return td->check_constraints(td, sptr, ctfailcb, app_key);
}

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static void
sf_Medium_2_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
	td->free_struct    = asn_DEF_NativeEnumerated.free_struct;
	td->print_struct   = asn_DEF_NativeEnumerated.print_struct;
	td->ber_decoder    = asn_DEF_NativeEnumerated.ber_decoder;
	td->der_encoder    = asn_DEF_NativeEnumerated.der_encoder;
	td->xer_decoder    = asn_DEF_NativeEnumerated.xer_decoder;
	td->xer_encoder    = asn_DEF_NativeEnumerated.xer_encoder;
	td->uper_decoder   = asn_DEF_NativeEnumerated.uper_decoder;
	td->uper_encoder   = asn_DEF_NativeEnumerated.uper_encoder;
	td->aper_decoder   = asn_DEF_NativeEnumerated.aper_decoder;
	td->aper_encoder   = asn_DEF_NativeEnumerated.aper_encoder;
	td->compare        = asn_DEF_NativeEnumerated.compare;
	if(!td->per_constraints)
		td->per_constraints = asn_DEF_NativeEnumerated.per_constraints;
	td->elements       = asn_DEF_NativeEnumerated.elements;
	td->elements_count = asn_DEF_NativeEnumerated.elements_count;
     /* td->specifics      = asn_DEF_NativeEnumerated.specifics;	// Defined explicitly */
}

static void
sf_Medium_2_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	sf_Medium_2_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
sf_Medium_2_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	sf_Medium_2_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
sf_Medium_2_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	sf_Medium_2_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
sf_Medium_2_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	sf_Medium_2_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
sf_Medium_2_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	sf_Medium_2_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
sf_Medium_2_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	sf_Medium_2_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
sf_Medium_2_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	sf_Medium_2_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
sf_Medium_2_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	sf_Medium_2_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static asn_enc_rval_t
sf_Medium_2_encode_aper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	sf_Medium_2_inherit_TYPE_descriptor(td);
	return td->aper_encoder(td, constraints, structure, per_out);
}

static asn_comp_rval_t * 
sf_Medium_2_compare(asn_TYPE_descriptor_t *td1,
		const void *structure1,
		asn_TYPE_descriptor_t *td2,
		const void *structure2) {
	asn_comp_rval_t * res  = NULL;
	sf_Medium_2_inherit_TYPE_descriptor(td1);
	sf_Medium_2_inherit_TYPE_descriptor(td2);
	res = td1->compare(td1, structure1, td2, structure2);
	return res;
}

static asn_dec_rval_t
sf_Medium_2_decode_aper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	sf_Medium_2_inherit_TYPE_descriptor(td);
	return td->aper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static int
sf_High_7_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	/* Replace with underlying type checker */
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
	return td->check_constraints(td, sptr, ctfailcb, app_key);
}

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static void
sf_High_7_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
	td->free_struct    = asn_DEF_NativeEnumerated.free_struct;
	td->print_struct   = asn_DEF_NativeEnumerated.print_struct;
	td->ber_decoder    = asn_DEF_NativeEnumerated.ber_decoder;
	td->der_encoder    = asn_DEF_NativeEnumerated.der_encoder;
	td->xer_decoder    = asn_DEF_NativeEnumerated.xer_decoder;
	td->xer_encoder    = asn_DEF_NativeEnumerated.xer_encoder;
	td->uper_decoder   = asn_DEF_NativeEnumerated.uper_decoder;
	td->uper_encoder   = asn_DEF_NativeEnumerated.uper_encoder;
	td->aper_decoder   = asn_DEF_NativeEnumerated.aper_decoder;
	td->aper_encoder   = asn_DEF_NativeEnumerated.aper_encoder;
	td->compare        = asn_DEF_NativeEnumerated.compare;
	if(!td->per_constraints)
		td->per_constraints = asn_DEF_NativeEnumerated.per_constraints;
	td->elements       = asn_DEF_NativeEnumerated.elements;
	td->elements_count = asn_DEF_NativeEnumerated.elements_count;
     /* td->specifics      = asn_DEF_NativeEnumerated.specifics;	// Defined explicitly */
}

static void
sf_High_7_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	sf_High_7_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
sf_High_7_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	sf_High_7_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
sf_High_7_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	sf_High_7_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
sf_High_7_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	sf_High_7_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
sf_High_7_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	sf_High_7_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
sf_High_7_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	sf_High_7_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
sf_High_7_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	sf_High_7_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
sf_High_7_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	sf_High_7_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static asn_enc_rval_t
sf_High_7_encode_aper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	sf_High_7_inherit_TYPE_descriptor(td);
	return td->aper_encoder(td, constraints, structure, per_out);
}

static asn_comp_rval_t * 
sf_High_7_compare(asn_TYPE_descriptor_t *td1,
		const void *structure1,
		asn_TYPE_descriptor_t *td2,
		const void *structure2) {
	asn_comp_rval_t * res  = NULL;
	sf_High_7_inherit_TYPE_descriptor(td1);
	sf_High_7_inherit_TYPE_descriptor(td2);
	res = td1->compare(td1, structure1, td2, structure2);
	return res;
}

static asn_dec_rval_t
sf_High_7_decode_aper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	sf_High_7_inherit_TYPE_descriptor(td);
	return td->aper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_per_constraints_t asn_PER_type_sf_Medium_constr_2 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  3 }	/* (0..3) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_sf_High_constr_7 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  3 }	/* (0..3) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_INTEGER_enum_map_t asn_MAP_sf_Medium_value2enum_2[] = {
	{ 0,	6,	"oDot25" },
	{ 1,	5,	"oDot5" },
	{ 2,	6,	"oDot75" },
	{ 3,	5,	"lDot0" }
};
static unsigned int asn_MAP_sf_Medium_enum2value_2[] = {
	3,	/* lDot0(3) */
	0,	/* oDot25(0) */
	1,	/* oDot5(1) */
	2	/* oDot75(2) */
};
static asn_INTEGER_specifics_t asn_SPC_sf_Medium_specs_2 = {
	asn_MAP_sf_Medium_value2enum_2,	/* "tag" => N; sorted by tag */
	asn_MAP_sf_Medium_enum2value_2,	/* N => "tag"; sorted by N */
	4,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_sf_Medium_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_sf_Medium_2 = {
	"sf-Medium",
	"sf-Medium",
	sf_Medium_2_free,
	sf_Medium_2_print,
	sf_Medium_2_constraint,
	sf_Medium_2_decode_ber,
	sf_Medium_2_encode_der,
	sf_Medium_2_decode_xer,
	sf_Medium_2_encode_xer,
	sf_Medium_2_decode_uper,
	sf_Medium_2_encode_uper,
	sf_Medium_2_decode_aper,
	sf_Medium_2_encode_aper,
	sf_Medium_2_compare,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_sf_Medium_tags_2,
	sizeof(asn_DEF_sf_Medium_tags_2)
		/sizeof(asn_DEF_sf_Medium_tags_2[0]) - 1, /* 1 */
	asn_DEF_sf_Medium_tags_2,	/* Same as above */
	sizeof(asn_DEF_sf_Medium_tags_2)
		/sizeof(asn_DEF_sf_Medium_tags_2[0]), /* 2 */
	&asn_PER_type_sf_Medium_constr_2,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_sf_Medium_specs_2	/* Additional specs */
};

static asn_INTEGER_enum_map_t asn_MAP_sf_High_value2enum_7[] = {
	{ 0,	6,	"oDot25" },
	{ 1,	5,	"oDot5" },
	{ 2,	6,	"oDot75" },
	{ 3,	5,	"lDot0" }
};
static unsigned int asn_MAP_sf_High_enum2value_7[] = {
	3,	/* lDot0(3) */
	0,	/* oDot25(0) */
	1,	/* oDot5(1) */
	2	/* oDot75(2) */
};
static asn_INTEGER_specifics_t asn_SPC_sf_High_specs_7 = {
	asn_MAP_sf_High_value2enum_7,	/* "tag" => N; sorted by tag */
	asn_MAP_sf_High_enum2value_7,	/* N => "tag"; sorted by N */
	4,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_sf_High_tags_7[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_sf_High_7 = {
	"sf-High",
	"sf-High",
	sf_High_7_free,
	sf_High_7_print,
	sf_High_7_constraint,
	sf_High_7_decode_ber,
	sf_High_7_encode_der,
	sf_High_7_decode_xer,
	sf_High_7_encode_xer,
	sf_High_7_decode_uper,
	sf_High_7_encode_uper,
	sf_High_7_decode_aper,
	sf_High_7_encode_aper,
	sf_High_7_compare,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_sf_High_tags_7,
	sizeof(asn_DEF_sf_High_tags_7)
		/sizeof(asn_DEF_sf_High_tags_7[0]) - 1, /* 1 */
	asn_DEF_sf_High_tags_7,	/* Same as above */
	sizeof(asn_DEF_sf_High_tags_7)
		/sizeof(asn_DEF_sf_High_tags_7[0]), /* 2 */
	&asn_PER_type_sf_High_constr_7,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_sf_High_specs_7	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SpeedStateScaleFactors_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SpeedStateScaleFactors, sf_Medium),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_sf_Medium_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sf-Medium"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SpeedStateScaleFactors, sf_High),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_sf_High_7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sf-High"
		},
};
static ber_tlv_tag_t asn_DEF_SpeedStateScaleFactors_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SpeedStateScaleFactors_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* sf-Medium at 6509 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* sf-High at 6510 */
};
static asn_SEQUENCE_specifics_t asn_SPC_SpeedStateScaleFactors_specs_1 = {
	sizeof(struct SpeedStateScaleFactors),
	offsetof(struct SpeedStateScaleFactors, _asn_ctx),
	asn_MAP_SpeedStateScaleFactors_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SpeedStateScaleFactors = {
	"SpeedStateScaleFactors",
	"SpeedStateScaleFactors",
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
	asn_DEF_SpeedStateScaleFactors_tags_1,
	sizeof(asn_DEF_SpeedStateScaleFactors_tags_1)
		/sizeof(asn_DEF_SpeedStateScaleFactors_tags_1[0]), /* 1 */
	asn_DEF_SpeedStateScaleFactors_tags_1,	/* Same as above */
	sizeof(asn_DEF_SpeedStateScaleFactors_tags_1)
		/sizeof(asn_DEF_SpeedStateScaleFactors_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SpeedStateScaleFactors_1,
	2,	/* Elements count */
	&asn_SPC_SpeedStateScaleFactors_specs_1	/* Additional specs */
};

