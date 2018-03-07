/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "NBIOT-RRC-Definitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER`
 */

#include "NPRACH-Parameters-NB-v1330.h"

static int
nprach_NumCBRA_StartSubcarriers_r13_2_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
nprach_NumCBRA_StartSubcarriers_r13_2_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
nprach_NumCBRA_StartSubcarriers_r13_2_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	nprach_NumCBRA_StartSubcarriers_r13_2_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
nprach_NumCBRA_StartSubcarriers_r13_2_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	nprach_NumCBRA_StartSubcarriers_r13_2_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
nprach_NumCBRA_StartSubcarriers_r13_2_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	nprach_NumCBRA_StartSubcarriers_r13_2_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
nprach_NumCBRA_StartSubcarriers_r13_2_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	nprach_NumCBRA_StartSubcarriers_r13_2_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
nprach_NumCBRA_StartSubcarriers_r13_2_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	nprach_NumCBRA_StartSubcarriers_r13_2_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
nprach_NumCBRA_StartSubcarriers_r13_2_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	nprach_NumCBRA_StartSubcarriers_r13_2_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
nprach_NumCBRA_StartSubcarriers_r13_2_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	nprach_NumCBRA_StartSubcarriers_r13_2_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
nprach_NumCBRA_StartSubcarriers_r13_2_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	nprach_NumCBRA_StartSubcarriers_r13_2_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static asn_enc_rval_t
nprach_NumCBRA_StartSubcarriers_r13_2_encode_aper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	nprach_NumCBRA_StartSubcarriers_r13_2_inherit_TYPE_descriptor(td);
	return td->aper_encoder(td, constraints, structure, per_out);
}

static asn_comp_rval_t * 
nprach_NumCBRA_StartSubcarriers_r13_2_compare(asn_TYPE_descriptor_t *td1,
		const void *structure1,
		asn_TYPE_descriptor_t *td2,
		const void *structure2) {
	asn_comp_rval_t * res  = NULL;
	nprach_NumCBRA_StartSubcarriers_r13_2_inherit_TYPE_descriptor(td1);
	nprach_NumCBRA_StartSubcarriers_r13_2_inherit_TYPE_descriptor(td2);
	res = td1->compare(td1, structure1, td2, structure2);
	return res;
}

static asn_dec_rval_t
nprach_NumCBRA_StartSubcarriers_r13_2_decode_aper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	nprach_NumCBRA_StartSubcarriers_r13_2_inherit_TYPE_descriptor(td);
	return td->aper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_per_constraints_t asn_PER_type_nprach_NumCBRA_StartSubcarriers_r13_constr_2 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  15 }	/* (0..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_INTEGER_enum_map_t asn_MAP_nprach_NumCBRA_StartSubcarriers_r13_value2enum_2[] = {
	{ 0,	2,	"n8" },
	{ 1,	3,	"n10" },
	{ 2,	3,	"n11" },
	{ 3,	3,	"n12" },
	{ 4,	3,	"n20" },
	{ 5,	3,	"n22" },
	{ 6,	3,	"n23" },
	{ 7,	3,	"n24" },
	{ 8,	3,	"n32" },
	{ 9,	3,	"n34" },
	{ 10,	3,	"n35" },
	{ 11,	3,	"n36" },
	{ 12,	3,	"n40" },
	{ 13,	3,	"n44" },
	{ 14,	3,	"n46" },
	{ 15,	3,	"n48" }
};
static unsigned int asn_MAP_nprach_NumCBRA_StartSubcarriers_r13_enum2value_2[] = {
	1,	/* n10(1) */
	2,	/* n11(2) */
	3,	/* n12(3) */
	4,	/* n20(4) */
	5,	/* n22(5) */
	6,	/* n23(6) */
	7,	/* n24(7) */
	8,	/* n32(8) */
	9,	/* n34(9) */
	10,	/* n35(10) */
	11,	/* n36(11) */
	12,	/* n40(12) */
	13,	/* n44(13) */
	14,	/* n46(14) */
	15,	/* n48(15) */
	0	/* n8(0) */
};
static asn_INTEGER_specifics_t asn_SPC_nprach_NumCBRA_StartSubcarriers_r13_specs_2 = {
	asn_MAP_nprach_NumCBRA_StartSubcarriers_r13_value2enum_2,	/* "tag" => N; sorted by tag */
	asn_MAP_nprach_NumCBRA_StartSubcarriers_r13_enum2value_2,	/* N => "tag"; sorted by N */
	16,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_nprach_NumCBRA_StartSubcarriers_r13_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_nprach_NumCBRA_StartSubcarriers_r13_2 = {
	"nprach-NumCBRA-StartSubcarriers-r13",
	"nprach-NumCBRA-StartSubcarriers-r13",
	nprach_NumCBRA_StartSubcarriers_r13_2_free,
	nprach_NumCBRA_StartSubcarriers_r13_2_print,
	nprach_NumCBRA_StartSubcarriers_r13_2_constraint,
	nprach_NumCBRA_StartSubcarriers_r13_2_decode_ber,
	nprach_NumCBRA_StartSubcarriers_r13_2_encode_der,
	nprach_NumCBRA_StartSubcarriers_r13_2_decode_xer,
	nprach_NumCBRA_StartSubcarriers_r13_2_encode_xer,
	nprach_NumCBRA_StartSubcarriers_r13_2_decode_uper,
	nprach_NumCBRA_StartSubcarriers_r13_2_encode_uper,
	nprach_NumCBRA_StartSubcarriers_r13_2_decode_aper,
	nprach_NumCBRA_StartSubcarriers_r13_2_encode_aper,
	nprach_NumCBRA_StartSubcarriers_r13_2_compare,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_nprach_NumCBRA_StartSubcarriers_r13_tags_2,
	sizeof(asn_DEF_nprach_NumCBRA_StartSubcarriers_r13_tags_2)
		/sizeof(asn_DEF_nprach_NumCBRA_StartSubcarriers_r13_tags_2[0]) - 1, /* 1 */
	asn_DEF_nprach_NumCBRA_StartSubcarriers_r13_tags_2,	/* Same as above */
	sizeof(asn_DEF_nprach_NumCBRA_StartSubcarriers_r13_tags_2)
		/sizeof(asn_DEF_nprach_NumCBRA_StartSubcarriers_r13_tags_2[0]), /* 2 */
	&asn_PER_type_nprach_NumCBRA_StartSubcarriers_r13_constr_2,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_nprach_NumCBRA_StartSubcarriers_r13_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_NPRACH_Parameters_NB_v1330_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct NPRACH_Parameters_NB_v1330, nprach_NumCBRA_StartSubcarriers_r13),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_nprach_NumCBRA_StartSubcarriers_r13_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"nprach-NumCBRA-StartSubcarriers-r13"
		},
};
static ber_tlv_tag_t asn_DEF_NPRACH_Parameters_NB_v1330_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_NPRACH_Parameters_NB_v1330_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* nprach-NumCBRA-StartSubcarriers-r13 at 10669 */
};
static asn_SEQUENCE_specifics_t asn_SPC_NPRACH_Parameters_NB_v1330_specs_1 = {
	sizeof(struct NPRACH_Parameters_NB_v1330),
	offsetof(struct NPRACH_Parameters_NB_v1330, _asn_ctx),
	asn_MAP_NPRACH_Parameters_NB_v1330_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_NPRACH_Parameters_NB_v1330 = {
	"NPRACH-Parameters-NB-v1330",
	"NPRACH-Parameters-NB-v1330",
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
	asn_DEF_NPRACH_Parameters_NB_v1330_tags_1,
	sizeof(asn_DEF_NPRACH_Parameters_NB_v1330_tags_1)
		/sizeof(asn_DEF_NPRACH_Parameters_NB_v1330_tags_1[0]), /* 1 */
	asn_DEF_NPRACH_Parameters_NB_v1330_tags_1,	/* Same as above */
	sizeof(asn_DEF_NPRACH_Parameters_NB_v1330_tags_1)
		/sizeof(asn_DEF_NPRACH_Parameters_NB_v1330_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_NPRACH_Parameters_NB_v1330_1,
	1,	/* Elements count */
	&asn_SPC_NPRACH_Parameters_NB_v1330_specs_1	/* Additional specs */
};

