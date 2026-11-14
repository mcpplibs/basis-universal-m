// mcpplibs.mwrap.basis_universal — Basis Universal's transcoder (KTX2 and .basis textures to pixels or
// to a GPU's own compressed format) as a C++ module. Every exported name is the upstream entity of
// <transcoder/basisu_transcoder.h>, in the namespace upstream declares it in: `basist`, `basisu` and
// the namespaces inside them. Written by tools/surface.py from the header as the compiler reads it
// (tools/surface.json; tools/check_exports.py holds the three together).
module;
#include <transcoder/basisu_transcoder.h>

export module mcpplibs.mwrap.basis_universal;

export namespace basist {
// types
using ::basist::approx_move_to_front;
using ::basist::astc_bc7_common_partition2_desc;
using ::basist::astc_bc7_common_partition3_desc;
using ::basist::astc_block_desc;
using ::basist::astc_quant_bin;
using ::basist::basis_file_header;
using ::basist::basis_header_flags;
using ::basist::basis_key_value_data_header;
using ::basist::basis_slice_desc;
using ::basist::basis_slice_desc_flags;
using ::basist::basis_tex_format;
using ::basist::basis_texture_type;
using ::basist::basisu_decode_flags;
using ::basist::basisu_file_info;
using ::basist::basisu_image_info;
using ::basist::basisu_image_level_info;
using ::basist::basisu_lowlevel_astc_hdr_6x6_transcoder;
using ::basist::basisu_lowlevel_etc1s_transcoder;
using ::basist::basisu_lowlevel_uastc_hdr_4x4_transcoder;
using ::basist::basisu_lowlevel_uastc_hdr_6x6_intermediate_transcoder;
using ::basist::basisu_lowlevel_uastc_ldr_4x4_transcoder;
using ::basist::basisu_lowlevel_xuastc_ldr_transcoder;
using ::basist::basisu_lowlevel_xubc7_transcoder;
using ::basist::basisu_map_range;
using ::basist::basisu_slice_info;
using ::basist::basisu_slice_info_vec;
using ::basist::basisu_transcoder;
using ::basist::basisu_transcoder_state;
using ::basist::bc1_block;
using ::basist::bc6h_bit_layout;
using ::basist::bc6h_block;
using ::basist::bc6h_logical_block;
using ::basist::bc73_astc2_common_partition_desc;
using ::basist::bc7_block;
using ::basist::bc7_mode_5;
using ::basist::bc7_optimization_results;
using ::basist::bit_hasher;
using ::basist::bitwise_decoder;
using ::basist::block_format;
using ::basist::color32;
using ::basist::color_quad_u8;
using ::basist::color_rgba;
using ::basist::dds_format;
using ::basist::dds_transcoder;
using ::basist::dds_uncompressed_channel;
using ::basist::debug_flags_t;
using ::basist::decoder_etc_block;
using ::basist::eNoClamp;
using ::basist::eac_block;
using ::basist::endpoint;
using ::basist::endpoint_err;
using ::basist::fixed;
using ::basist::fixed16_16;
using ::basist::fixed22_10;
using ::basist::fixed24_8;
using ::basist::fixed8_24;
using ::basist::half_float;
using ::basist::huffman_decoding_table;
using ::basist::key_value;
using ::basist::key_value_vec;
using ::basist::ktx2_animdata;
using ::basist::ktx2_df_channel_id;
using ::basist::ktx2_df_color_primaries;
using ::basist::ktx2_etc1s_global_data_header;
using ::basist::ktx2_etc1s_image_desc;
using ::basist::ktx2_header;
using ::basist::ktx2_image_level_info;
using ::basist::ktx2_level_index;
using ::basist::ktx2_slice_offset_len_desc_orig;
using ::basist::ktx2_slice_offset_len_desc_std;
using ::basist::ktx2_supercompression;
using ::basist::ktx2_transcoder;
using ::basist::ktx2_transcoder_state;
using ::basist::selector;
using ::basist::simplified_bitwise_decoder;
using ::basist::string_hasher;
using ::basist::transcoder_texture_format;
using ::basist::uastc_block;
using ::basist::unpacked_uastc_block;
using ::basist::xuastc_decoded_image;
// enumerators of unscoped enumerations
using ::basist::KTX2_DF_CHANNEL_ETC1S_AAA;
using ::basist::KTX2_DF_CHANNEL_ETC1S_GGG;
using ::basist::KTX2_DF_CHANNEL_ETC1S_RGB;
using ::basist::KTX2_DF_CHANNEL_ETC1S_RRR;
using ::basist::KTX2_DF_CHANNEL_UASTC_DATA;
using ::basist::KTX2_DF_CHANNEL_UASTC_RG;
using ::basist::KTX2_DF_CHANNEL_UASTC_RGB;
using ::basist::KTX2_DF_CHANNEL_UASTC_RGBA;
using ::basist::KTX2_DF_CHANNEL_UASTC_RRR;
using ::basist::KTX2_DF_CHANNEL_UASTC_RRRG;
using ::basist::KTX2_DF_PRIMARIES_ACES;
using ::basist::KTX2_DF_PRIMARIES_ACESCC;
using ::basist::KTX2_DF_PRIMARIES_ADOBERGB;
using ::basist::KTX2_DF_PRIMARIES_BT2020;
using ::basist::KTX2_DF_PRIMARIES_BT601_EBU;
using ::basist::KTX2_DF_PRIMARIES_BT601_SMPTE;
using ::basist::KTX2_DF_PRIMARIES_BT709;
using ::basist::KTX2_DF_PRIMARIES_CIEXYZ;
using ::basist::KTX2_DF_PRIMARIES_DISPLAYP3;
using ::basist::KTX2_DF_PRIMARIES_NTSC1953;
using ::basist::KTX2_DF_PRIMARIES_PAL525;
using ::basist::KTX2_DF_PRIMARIES_SRGB;
using ::basist::KTX2_DF_PRIMARIES_UNSPECIFIED;
using ::basist::KTX2_SS_BASISLZ;
using ::basist::KTX2_SS_DEFLATE;
using ::basist::KTX2_SS_NONE;
using ::basist::KTX2_SS_UASTC_HDR_6x6I;
using ::basist::KTX2_SS_XUASTC_LDR;
using ::basist::KTX2_SS_XUBC7;
using ::basist::KTX2_SS_ZSTANDARD;
using ::basist::cBASISHeaderFlagETC1S;
using ::basist::cBASISHeaderFlagHasAlphaSlices;
using ::basist::cBASISHeaderFlagSRGB;
using ::basist::cBASISHeaderFlagUsesGlobalCodebook;
using ::basist::cBASISHeaderFlagYFlipped;
using ::basist::cBASISMaxUSPerFrame;
using ::basist::cBASISTexType2D;
using ::basist::cBASISTexType2DArray;
using ::basist::cBASISTexTypeCubemapArray;
using ::basist::cBASISTexTypeTotal;
using ::basist::cBASISTexTypeVideoFrames;
using ::basist::cBASISTexTypeVolume;
using ::basist::cDebugFlagVisBC1Endpoints;
using ::basist::cDebugFlagVisBC1Sels;
using ::basist::cDebugFlagVisCRs;
using ::basist::cDecodeFlagXUASTCLDRDisableFastBC7Transcoding;
using ::basist::cDecodeFlagsBC1ForbidThreeColorBlocks;
using ::basist::cDecodeFlagsForceDeblockFiltering;
using ::basist::cDecodeFlagsHighQuality;
using ::basist::cDecodeFlagsNoDeblockFiltering;
using ::basist::cDecodeFlagsNoETC1SChromaFiltering;
using ::basist::cDecodeFlagsOutputHasAlphaIndices;
using ::basist::cDecodeFlagsPVRTCDecodeToNextPow2;
using ::basist::cDecodeFlagsTranscodeAlphaDataToOpaqueFormats;
using ::basist::cEncodeBC1HighQuality;
using ::basist::cEncodeBC1HigherQuality;
using ::basist::cEncodeBC1UseSelectors;
using ::basist::cNoClamp;
using ::basist::cSliceDescFlagsFrameIsIFrame;
using ::basist::cSliceDescFlagsHasAlpha;
// objects
using ::basist::g_astc_bc7_common_partitions2;
using ::basist::g_astc_bc7_common_partitions3;
using ::basist::g_astc_bc7_pattern2_anchors;
using ::basist::g_astc_bc7_pattern3_anchors;
using ::basist::g_astc_bc7_patterns2;
using ::basist::g_astc_bc7_patterns3;
using ::basist::g_astc_bise_range_table;
using ::basist::g_astc_to_bc7_partition_index_perm_tables;
using ::basist::g_astc_unquant;
using ::basist::g_astc_weights4;
using ::basist::g_astc_weights5;
using ::basist::g_astc_weights_3levels;
using ::basist::g_bc6h_2subset_patterns;
using ::basist::g_bc6h_bit_layouts;
using ::basist::g_bc6h_mode_lookup;
using ::basist::g_bc6h_mode_sig_bits;
using ::basist::g_bc6h_weight3;
using ::basist::g_bc6h_weight4;
using ::basist::g_bc7_3_astc2_common_partitions;
using ::basist::g_bc7_3_astc2_patterns2;
using ::basist::g_bc7_3_astc2_patterns2_anchors;
using ::basist::g_bc7_alpha_index_bitcount;
using ::basist::g_bc7_alpha_precision_table;
using ::basist::g_bc7_color_index_bitcount;
using ::basist::g_bc7_color_precision_table;
using ::basist::g_bc7_mode_5_optimal_endpoints;
using ::basist::g_bc7_mode_6_optimal_endpoints;
using ::basist::g_bc7_mode_has_p_bits;
using ::basist::g_bc7_mode_has_shared_p_bits;
using ::basist::g_bc7_num_subsets;
using ::basist::g_bc7_partition1;
using ::basist::g_bc7_partition2;
using ::basist::g_bc7_partition3;
using ::basist::g_bc7_partition_bits;
using ::basist::g_bc7_table_anchor_index_second_subset;
using ::basist::g_bc7_table_anchor_index_third_subset_1;
using ::basist::g_bc7_table_anchor_index_third_subset_2;
using ::basist::g_bc7_to_astc_partition_index_perm_tables;
using ::basist::g_bc7_weights1;
using ::basist::g_bc7_weights2;
using ::basist::g_bc7_weights3;
using ::basist::g_bc7_weights4;
using ::basist::g_ktx2_file_identifier;
using ::basist::g_uastc_mode_comps;
using ::basist::g_uastc_mode_endpoint_ranges;
using ::basist::g_uastc_mode_has_alpha;
using ::basist::g_uastc_mode_has_bc1_hint0;
using ::basist::g_uastc_mode_has_bc1_hint1;
using ::basist::g_uastc_mode_has_etc1_bias;
using ::basist::g_uastc_mode_huff_codes;
using ::basist::g_uastc_mode_is_la;
using ::basist::g_uastc_mode_planes;
using ::basist::g_uastc_mode_subsets;
using ::basist::g_uastc_mode_weight_bits;
using ::basist::g_uastc_mode_weight_ranges;
using ::basist::s_uastc_to_bc1_weights;
// functions and operators
using ::basist::add_key_value;
using ::basist::apply_etc1_bias;
using ::basist::astc_get_levels;
using ::basist::astc_interpolate;
using ::basist::astc_is_valid_endpoint_range;
using ::basist::basis_block_format_is_uncompressed;
using ::basist::basis_compute_transcoded_image_size_in_bytes;
using ::basist::basis_get_basisu_texture_format;
using ::basist::basis_get_block_format_name;
using ::basist::basis_get_block_height;
using ::basist::basis_get_block_width;
using ::basist::basis_get_bytes_per_block_or_pixel;
using ::basist::basis_get_format_name;
using ::basist::basis_get_tex_format_name;
using ::basist::basis_get_texture_format_from_xuastc_or_astc_ldr_basis_tex_format;
using ::basist::basis_get_texture_type_name;
using ::basist::basis_get_transcoder_texture_format_from_basis_tex_format;
using ::basist::basis_get_transcoder_texture_format_from_xuastc_or_astc_ldr_basis_tex_format;
using ::basist::basis_get_uncompressed_bytes_per_pixel;
using ::basist::basis_is_dds_format_uncompressed;
using ::basist::basis_is_format_supported;
using ::basist::basis_is_transcoder_texture_format_astc;
using ::basist::basis_tex_format_get_block_height;
using ::basist::basis_tex_format_get_block_width;
using ::basist::basis_tex_format_is_astc_ldr;
using ::basist::basis_tex_format_is_hdr;
using ::basist::basis_tex_format_is_ldr;
using ::basist::basis_tex_format_is_xuastc_ldr;
using ::basist::basis_tex_format_is_xubc7;
using ::basist::basis_transcoder_format_has_alpha;
using ::basist::basis_transcoder_format_is_hdr;
using ::basist::basis_transcoder_format_is_ldr;
using ::basist::basis_transcoder_format_is_uncompressed;
using ::basist::basis_validate_output_buffer_size;
using ::basist::basisd_rand;
using ::basist::basisd_urand;
using ::basist::basisu_transcoder_init;
using ::basist::basisu_transcoder_supports_ktx2;
using ::basist::basisu_transcoder_supports_ktx2_zstd;
using ::basist::bc6h_blog16_to_half;
using ::basist::bc6h_enc_block_1subset_3bit_weights;
using ::basist::bc6h_enc_block_1subset_4bit_weights;
using ::basist::bc6h_enc_block_1subset_mode9_3bit_weights;
using ::basist::bc6h_enc_block_2subset_3bit_weights;
using ::basist::bc6h_enc_block_2subset_mode9_3bit_weights;
using ::basist::bc6h_enc_block_mode10;
using ::basist::bc6h_enc_block_solid_color;
using ::basist::bc6h_enc_init;
using ::basist::bc6h_half_to_blog;
using ::basist::bc6h_half_to_blog16;
using ::basist::bc7_convert_partition_index_3_to_2;
using ::basist::block_format_is_astc;
using ::basist::block_format_is_hdr;
using ::basist::clamp255;
using ::basist::crc16;
using ::basist::encode_bc1;
using ::basist::encode_bc1_alt;
using ::basist::encode_bc1_solid_block;
using ::basist::encode_bc4;
using ::basist::encode_bc7_block;
using ::basist::encode_pvrtc1;
using ::basist::find_key_value;
using ::basist::float_to_half;
using ::basist::get_anchor_indices;
using ::basist::get_basis_tex_format_block_size;
using ::basist::get_bc7_alpha_index_size;
using ::basist::get_bc7_color_index_size;
using ::basist::get_bc7_mode_has_seperate_alpha_selectors;
using ::basist::get_bits;
using ::basist::get_block_height;
using ::basist::get_block_width;
using ::basist::get_debug_flags;
using ::basist::get_half_exp;
using ::basist::get_half_mantissa;
using ::basist::get_half_mantissaf;
using ::basist::get_half_sign;
using ::basist::half_is_signed;
using ::basist::half_to_float;
using ::basist::hash_hsieh;
using ::basist::is_half_denorm;
using ::basist::is_half_inf_or_nan;
using ::basist::ktx2_get_df_color_primaries_str;
using ::basist::ktx2_get_etc1s_df_channel_id_str;
using ::basist::ktx2_get_uastc_df_channel_id_str;
using ::basist::pack_astc_block;
using ::basist::pack_astc_solid_block;
using ::basist::pack_bc6h_block;
using ::basist::set_debug_flags;
using ::basist::transcode_4x4_block;
using ::basist::transcode_uastc_to_astc;
using ::basist::transcode_uastc_to_bc1;
using ::basist::transcode_uastc_to_bc1_hint0;
using ::basist::transcode_uastc_to_bc1_hint1;
using ::basist::transcode_uastc_to_bc3;
using ::basist::transcode_uastc_to_bc4;
using ::basist::transcode_uastc_to_bc5;
using ::basist::transcode_uastc_to_bc7;
using ::basist::transcode_uastc_to_etc1;
using ::basist::transcode_uastc_to_etc2_eac_a8;
using ::basist::transcode_uastc_to_etc2_eac_r11;
using ::basist::transcode_uastc_to_etc2_eac_rg11;
using ::basist::transcode_uastc_to_etc2_rgba;
using ::basist::transcode_uastc_to_pvrtc1_4_rgb;
using ::basist::transcode_uastc_to_pvrtc1_4_rgba;
using ::basist::uastc_init;
using ::basist::unpack_uastc;
using ::basist::unquant_astc_endpoint;
using ::basist::unquant_astc_endpoint_val;
using ::basist::xuastc_get_block_format;
}  // namespace basist

export namespace basist::arith {
// types
using ::basist::arith::arith_bit_model;
using ::basist::arith::arith_data_model;
using ::basist::arith::arith_dec;
using ::basist::arith::arith_enc;
using ::basist::arith::arith_gamma_contexts;
// enumerators of unscoped enumerations
using ::basist::arith::cARITH_GAMMA_MAX_PREFIX_CTX;
using ::basist::arith::cARITH_GAMMA_MAX_TAIL_CTX;
}  // namespace basist::arith

export namespace basist::arith_fastbits_f32 {
// enumerators of unscoped enumerations
using ::basist::arith_fastbits_f32::FRAC_BITS;
using ::basist::arith_fastbits_f32::FRAC_MASK;
using ::basist::arith_fastbits_f32::MANT_BITS;
using ::basist::arith_fastbits_f32::TABLE_BITS;
using ::basist::arith_fastbits_f32::TABLE_SIZE;
// objects
using ::basist::arith_fastbits_f32::g_initialized;
using ::basist::arith_fastbits_f32::g_lut_edge;
// functions and operators
using ::basist::arith_fastbits_f32::bits_from_prob_linear;
using ::basist::arith_fastbits_f32::init;
using ::basist::arith_fastbits_f32::unpack;
}  // namespace basist::arith_fastbits_f32

export namespace basist::astc_6x6_hdr {
// objects
using ::basist::astc_6x6_hdr::g_quantize_tables_preserve2;
using ::basist::astc_6x6_hdr::g_quantize_tables_preserve3;
}  // namespace basist::astc_6x6_hdr

export namespace basist::astc_ldr_t {
// types
using ::basist::astc_ldr_t::astc_block_grid_config;
using ::basist::astc_ldr_t::astc_block_grid_data;
using ::basist::astc_ldr_t::astc_block_grid_data_hash_t;
using ::basist::astc_ldr_t::dct2f;
using ::basist::astc_ldr_t::dct_syms;
using ::basist::astc_ldr_t::fvec;
using ::basist::astc_ldr_t::grid_dim_hash_map;
using ::basist::astc_ldr_t::grid_dim_key;
using ::basist::astc_ldr_t::grid_dim_value;
using ::basist::astc_ldr_t::grid_weight_dct;
using ::basist::astc_ldr_t::grouped_trial_modes;
using ::basist::astc_ldr_t::prev_block_state;
using ::basist::astc_ldr_t::prev_block_state_full_zstd;
using ::basist::astc_ldr_t::sample_quant_table_state;
using ::basist::astc_ldr_t::trial_mode;
using ::basist::astc_ldr_t::xuastc_decomp_image_block_callback_ptr;
using ::basist::astc_ldr_t::xuastc_decomp_image_init_callback_ptr;
using ::basist::astc_ldr_t::xuastc_ldr_arith_header;
using ::basist::astc_ldr_t::xuastc_ldr_full_zstd_header;
using ::basist::astc_ldr_t::xuastc_ldr_syntax;
using ::basist::astc_ldr_t::xuastc_mode;
using ::basist::astc_ldr_t::xuastc_zstd_mode;
// objects
using ::basist::astc_ldr_t::g_astc_block_grid_data_hash;
using ::basist::astc_ldr_t::g_encoder_trial_modes;
using ::basist::astc_ldr_t::g_grouped_encoder_trial_modes;
using ::basist::astc_ldr_t::g_total_unique_patterns;
using ::basist::astc_ldr_t::g_unique_index_to_astc_part_seed;
using ::basist::astc_ldr_t::s_unique_ldr_index_to_astc_cem;
// functions and operators
using ::basist::astc_ldr_t::blue_contract_dec;
using ::basist::astc_ldr_t::blue_contract_enc;
using ::basist::astc_ldr_t::calc_grid_aniso_val;
using ::basist::astc_ldr_t::calc_grid_size_val;
using ::basist::astc_ldr_t::cem_to_ldrcem_index;
using ::basist::astc_ldr_t::compute_adjoint_downsample_matrix;
using ::basist::astc_ldr_t::compute_upsample_matrix;
using ::basist::astc_ldr_t::convert_endpoints_across_cems;
using ::basist::astc_ldr_t::create_encoder_trial_modes_table;
using ::basist::astc_ldr_t::decode_endpoints;
using ::basist::astc_ldr_t::decode_endpoints_ise20;
using ::basist::astc_ldr_t::find_astc_block_grid_data;
using ::basist::astc_ldr_t::get_tm_candidates;
using ::basist::astc_ldr_t::get_total_unique_patterns;
using ::basist::astc_ldr_t::init;
using ::basist::astc_ldr_t::init_astc_block_grid_data_hash;
using ::basist::astc_ldr_t::pack_base_offset;
using ::basist::astc_ldr_t::part_hash_index;
using ::basist::astc_ldr_t::requantize_ise_endpoints;
using ::basist::astc_ldr_t::tm_hash_index;
using ::basist::astc_ldr_t::unique_pat_index_to_part_seed;
using ::basist::astc_ldr_t::xuastc_ldr_decompress_image;
}  // namespace basist::astc_ldr_t

export namespace basist::bc7_mode_5_encoder {
// functions and operators
using ::basist::bc7_mode_5_encoder::encode_bc7_mode_5_block;
}  // namespace basist::bc7_mode_5_encoder

export namespace basist::bc7f {
// enumerators of unscoped enumerations
using ::basist::bc7f::cPackBC7FlagASTCCompatible;
using ::basist::bc7f::cPackBC7FlagDefault;
using ::basist::bc7f::cPackBC7FlagDefaultFast;
using ::basist::bc7f::cPackBC7FlagDefaultFaster;
using ::basist::bc7f::cPackBC7FlagDefaultFastest;
using ::basist::bc7f::cPackBC7FlagDefaultNonAnalytical;
using ::basist::bc7f::cPackBC7FlagDefaultPartiallyAnalytical;
using ::basist::bc7f::cPackBC7FlagDisableRGBDualPlane;
using ::basist::bc7f::cPackBC7FlagNonAnalyticalRGB;
using ::basist::bc7f::cPackBC7FlagNonAnalyticalRGBA;
using ::basist::bc7f::cPackBC7FlagPBitOpt;
using ::basist::bc7f::cPackBC7FlagPBitOptMode6;
using ::basist::bc7f::cPackBC7FlagPartiallyAnalyticalRGB;
using ::basist::bc7f::cPackBC7FlagPartiallyAnalyticalRGBA;
using ::basist::bc7f::cPackBC7FlagUse2SubsetsRGB;
using ::basist::bc7f::cPackBC7FlagUse2SubsetsRGBA;
using ::basist::bc7f::cPackBC7FlagUse3SubsetsRGB;
using ::basist::bc7f::cPackBC7FlagUseDualPlaneRGB;
using ::basist::bc7f::cPackBC7FlagUseDualPlaneRGBA;
using ::basist::bc7f::cPackBC7FlagUseTrivialMode6;
// functions and operators
using ::basist::bc7f::calc_sse;
using ::basist::bc7f::fast_pack_astc;
using ::basist::bc7f::fast_pack_bc7_auto_rgba;
using ::basist::bc7f::fast_pack_bc7_rgb_analytical;
using ::basist::bc7f::fast_pack_bc7_rgb_partial_analytical;
using ::basist::bc7f::fast_pack_bc7_rgba_analytical;
using ::basist::bc7f::fast_pack_bc7_rgba_partial_analytical;
using ::basist::bc7f::init;
using ::basist::bc7f::print_perf_stats;
}  // namespace basist::bc7f

export namespace basist::bc7u {
// types
using ::basist::bc7u::endpoint_format;
using ::basist::bc7u::log_bc7_block;
using ::basist::bc7u::phys_bc7_block;
// objects
using ::basist::bc7u::g_endpoint_formats;
using ::basist::bc7u::g_weight_quant;
// functions and operators
using ::basist::bc7u::canonicalize_endpoints;
using ::basist::bc7u::compare_block_configs;
using ::basist::bc7u::compare_block_endpoints;
using ::basist::bc7u::compare_block_full;
using ::basist::bc7u::compare_block_pbits;
using ::basist::bc7u::compare_block_weights;
using ::basist::bc7u::create_solid_blk;
using ::basist::bc7u::dequant_weight;
using ::basist::bc7u::determine_bc7_mode;
using ::basist::bc7u::determine_bc7_mode_4_index_mode;
using ::basist::bc7u::determine_bc7_mode_4_or_5_rotation;
using ::basist::bc7u::endpoint_dpcm;
using ::basist::bc7u::get_texel_subset;
using ::basist::bc7u::init_log_blk;
using ::basist::bc7u::init_weight_quant;
using ::basist::bc7u::is_solid_blk;
using ::basist::bc7u::pack_bc7;
using ::basist::bc7u::pack_endpoints;
using ::basist::bc7u::quant_weight;
using ::basist::bc7u::set_endpoints;
using ::basist::bc7u::unpack_bc7;
using ::basist::bc7u::unpack_bc7_mode6;
using ::basist::bc7u::unpack_bc7_texel;
using ::basist::bc7u::unpack_endpoints;
using ::basist::bc7u::validate_log_blk;
}  // namespace basist::bc7u

export namespace basist::bcu {
// functions and operators
using ::basist::bcu::unpack_bc1;
using ::basist::bcu::unpack_bc2;
using ::basist::bcu::unpack_bc3;
using ::basist::bcu::unpack_bc4;
using ::basist::bcu::unpack_bc5;
}  // namespace basist::bcu

export namespace basist::etc1f {
// types
using ::basist::etc1f::pack_etc1_state;
// functions and operators
using ::basist::etc1f::init;
using ::basist::etc1f::pack_etc1;
using ::basist::etc1f::pack_etc1_grayscale;
using ::basist::etc1f::pack_etc1_solid;
}  // namespace basist::etc1f

export namespace basist::fixed_detail {
// types
using ::basist::fixed_detail::sqrt_lut_t;
// objects
using ::basist::fixed_detail::SQRT_LUT;
// functions and operators
using ::basist::fixed_detail::clz64;
using ::basist::fixed_detail::isqrt_floor;
using ::basist::fixed_detail::make_sqrt_lut;
}  // namespace basist::fixed_detail

export namespace basisu {
// types
using ::basisu::bitwise_copyable;
using ::basisu::bitwise_movable;
using ::basisu::bool_vec;
using ::basisu::double_vec;
using ::basisu::eNoClamp;
using ::basisu::eZero;
using ::basisu::elemental_vector;
using ::basisu::empty_type;
using ::basisu::equal_to;
using ::basisu::fixed_array;
using ::basisu::float_vec;
using ::basisu::fmt_variant;
using ::basisu::fmt_variant_vec;
using ::basisu::hash_map;
using ::basisu::hasher;
using ::basisu::int16_vec;
using ::basisu::int_vec;
using ::basisu::is_class;
using ::basisu::is_pointer;
using ::basisu::no_t;
using ::basisu::packed_uint;
using ::basisu::readable_span;
using ::basisu::rel_ops;
using ::basisu::scalar_type;
using ::basisu::size_t_vec;
using ::basisu::static_vector;
using ::basisu::texture_format;
using ::basisu::uint16_vec;
using ::basisu::uint64_vec;
using ::basisu::uint8_vec;
using ::basisu::uint_vec;
using ::basisu::variant_type;
using ::basisu::vector;
using ::basisu::vector2D;
using ::basisu::writable_span;
using ::basisu::yes_t;
// enumerators of unscoped enumerations
using ::basisu::cHuffmanBigRepeatCode;
using ::basisu::cHuffmanBigRepeatExtraBits;
using ::basisu::cHuffmanBigRepeatSizeMax;
using ::basisu::cHuffmanBigRepeatSizeMin;
using ::basisu::cHuffmanBigZeroRunCode;
using ::basisu::cHuffmanBigZeroRunExtraBits;
using ::basisu::cHuffmanBigZeroRunSizeMax;
using ::basisu::cHuffmanBigZeroRunSizeMin;
using ::basisu::cHuffmanFastLookupBits;
using ::basisu::cHuffmanMaxSupportedCodeSize;
using ::basisu::cHuffmanMaxSupportedInternalCodeSize;
using ::basisu::cHuffmanMaxSyms;
using ::basisu::cHuffmanMaxSymsLog2;
using ::basisu::cHuffmanSmallRepeatCode;
using ::basisu::cHuffmanSmallRepeatExtraBits;
using ::basisu::cHuffmanSmallRepeatSizeMax;
using ::basisu::cHuffmanSmallRepeatSizeMin;
using ::basisu::cHuffmanSmallZeroRunCode;
using ::basisu::cHuffmanSmallZeroRunExtraBits;
using ::basisu::cHuffmanSmallZeroRunSizeMax;
using ::basisu::cHuffmanSmallZeroRunSizeMin;
using ::basisu::cHuffmanTotalCodelengthCodes;
using ::basisu::cInvalidIndex;
using ::basisu::cNoClamp;
using ::basisu::cZero;
// objects
using ::basisu::g_debug_printf;
// functions and operators
using ::basisu::add_overflow_check;
using ::basisu::append_vector;
using ::basisu::can_fit_into_size_t;
using ::basisu::ceil_log2i;
using ::basisu::clamp;
using ::basisu::clampf;
using ::basisu::class_test;
using ::basisu::clear_obj;
using ::basisu::clear_vector;
using ::basisu::construct;
using ::basisu::construct_array;
using ::basisu::container_abort;
using ::basisu::debug_printf;
using ::basisu::debug_puts;
using ::basisu::destruct;
using ::basisu::destruct_array;
using ::basisu::do_excl_ranges_overlap;
using ::basisu::enable_debug_printf;
using ::basisu::enlarge_vector;
using ::basisu::equal_tol;
using ::basisu::floor_log2i;
using ::basisu::fmt_debug_printf;
using ::basisu::fmt_fprintf;
using ::basisu::fmt_printf;
using ::basisu::fmt_string;
using ::basisu::fmt_variants;
using ::basisu::get_astc_ldr_texture_format;
using ::basisu::get_bit;
using ::basisu::get_bits;
using ::basisu::get_block_height;
using ::basisu::get_block_width;
using ::basisu::get_bytes_per_block_or_pixel;
using ::basisu::get_qwords_per_block;
using ::basisu::iabs;
using ::basisu::iabs64;
using ::basisu::imod;
using ::basisu::is_astc;
using ::basisu::is_bit_set;
using ::basisu::is_block_based_texture_format;
using ::basisu::is_hdr_astc;
using ::basisu::is_hdr_texture_format;
using ::basisu::is_in_bounds;
using ::basisu::is_in_range;
using ::basisu::is_ldr_astc;
using ::basisu::is_ldr_texture_format;
using ::basisu::is_pow2;
using ::basisu::is_uncompressed_texture_format;
using ::basisu::is_valid_astc_block_size;
using ::basisu::lerp;
using ::basisu::maximum;
using ::basisu::maximumf;
using ::basisu::maximumi;
using ::basisu::maximumu;
using ::basisu::maximumub;
using ::basisu::minimum;
using ::basisu::minimumf;
using ::basisu::minimumi;
using ::basisu::minimumu;
using ::basisu::minimumub;
using ::basisu::mul_overflow_check;
using ::basisu::next_wrap;
using ::basisu::open_range_check;
using ::basisu::posmod;
using ::basisu::posmodf;
using ::basisu::prev_wrap;
using ::basisu::range_check;
using ::basisu::read_be64;
using ::basisu::safe_cast_int16;
using ::basisu::safe_cast_int8;
using ::basisu::safe_cast_uint16;
using ::basisu::safe_cast_uint8;
using ::basisu::safe_shift_left;
using ::basisu::saturate;
using ::basisu::sign;
using ::basisu::span_copy;
using ::basisu::square;
using ::basisu::squared;
using ::basisu::squaref;
using ::basisu::squarei;
using ::basisu::string_format;
using ::basisu::total_bits;
using ::basisu::unordered_set_contains;
using ::basisu::vector_ensure_element_is_valid;
using ::basisu::vector_find;
using ::basisu::vector_set_all;
using ::basisu::vector_sort;
using ::basisu::write_be64;
}  // namespace basisu

export namespace basisu::helpers {
// functions and operators
using ::basisu::helpers::floor_log2i;
using ::basisu::helpers::is_power_of_2;
using ::basisu::helpers::maximum;
using ::basisu::helpers::minimum;
using ::basisu::helpers::next_pow2;
}  // namespace basisu::helpers

// The header's scalar constants of internal linkage (every includer has its own, and none can be
// exported), again under their names with their types and values.
export namespace mcpplibs::mwrap::basis_universal::basist {
inline constexpr auto BASISU_DEBLOCKING_BLOCK_SIZE_THRESHOLD = ::basist::BASISU_DEBLOCKING_BLOCK_SIZE_THRESHOLD;
inline constexpr auto BASISU_MAX_SUPPORTED_TEXTURE_DIMENSION = ::basist::BASISU_MAX_SUPPORTED_TEXTURE_DIMENSION;
inline constexpr auto BC6H_FIRST_1SUBSET_MODE_INDEX = ::basist::BC6H_FIRST_1SUBSET_MODE_INDEX;
inline constexpr auto BC6H_LAST_MODE_INDEX = ::basist::BC6H_LAST_MODE_INDEX;
inline constexpr auto BC7ENC_BLOCK_SIZE = ::basist::BC7ENC_BLOCK_SIZE;
inline constexpr auto BC7ENC_MODE_5_OPTIMAL_INDEX = ::basist::BC7ENC_MODE_5_OPTIMAL_INDEX;
inline constexpr auto BC7ENC_MODE_6_OPTIMAL_INDEX = ::basist::BC7ENC_MODE_6_OPTIMAL_INDEX;
inline constexpr auto BC7ENC_TOTAL_ASTC_RANGES = ::basist::BC7ENC_TOTAL_ASTC_RANGES;
inline constexpr auto COLOR5_PAL0_DELTA_HI = ::basist::COLOR5_PAL0_DELTA_HI;
inline constexpr auto COLOR5_PAL0_DELTA_LO = ::basist::COLOR5_PAL0_DELTA_LO;
inline constexpr auto COLOR5_PAL0_PREV_HI = ::basist::COLOR5_PAL0_PREV_HI;
inline constexpr auto COLOR5_PAL1_DELTA_HI = ::basist::COLOR5_PAL1_DELTA_HI;
inline constexpr auto COLOR5_PAL1_DELTA_LO = ::basist::COLOR5_PAL1_DELTA_LO;
inline constexpr auto COLOR5_PAL1_PREV_HI = ::basist::COLOR5_PAL1_PREV_HI;
inline constexpr auto COLOR5_PAL2_DELTA_HI = ::basist::COLOR5_PAL2_DELTA_HI;
inline constexpr auto COLOR5_PAL2_DELTA_LO = ::basist::COLOR5_PAL2_DELTA_LO;
inline constexpr auto COLOR5_PAL2_PREV_HI = ::basist::COLOR5_PAL2_PREV_HI;
inline constexpr auto COLOR5_PAL_DELTA_5_RUNLEN_VLC_BITS = ::basist::COLOR5_PAL_DELTA_5_RUNLEN_VLC_BITS;
inline constexpr auto COLOR5_PAL_MIN_DELTA_B_RUNLEN = ::basist::COLOR5_PAL_MIN_DELTA_B_RUNLEN;
inline constexpr auto CR_ENDPOINT_PRED_INDEX = ::basist::CR_ENDPOINT_PRED_INDEX;
inline constexpr auto ENDPOINT_PRED_COUNT_VLC_BITS = ::basist::ENDPOINT_PRED_COUNT_VLC_BITS;
inline constexpr auto ENDPOINT_PRED_MIN_REPEAT_COUNT = ::basist::ENDPOINT_PRED_MIN_REPEAT_COUNT;
inline constexpr auto ENDPOINT_PRED_REPEAT_LAST_SYMBOL = ::basist::ENDPOINT_PRED_REPEAT_LAST_SYMBOL;
inline constexpr auto ENDPOINT_PRED_TOTAL_SYMBOLS = ::basist::ENDPOINT_PRED_TOTAL_SYMBOLS;
inline constexpr auto KTX2_FORMAT_ASTC_10x10_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_10x10_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_10x10_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_10x10_UNORM_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_10x5_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_10x5_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_10x5_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_10x5_UNORM_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_10x6_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_10x6_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_10x6_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_10x6_UNORM_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_10x8_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_10x8_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_10x8_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_10x8_UNORM_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_12x10_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_12x10_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_12x10_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_12x10_UNORM_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_12x12_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_12x12_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_12x12_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_12x12_UNORM_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_4x4_SFLOAT_BLOCK = ::basist::KTX2_FORMAT_ASTC_4x4_SFLOAT_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_4x4_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_4x4_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_4x4_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_4x4_UNORM_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_5x4_SFLOAT_BLOCK = ::basist::KTX2_FORMAT_ASTC_5x4_SFLOAT_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_5x4_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_5x4_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_5x4_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_5x4_UNORM_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_5x5_SFLOAT_BLOCK = ::basist::KTX2_FORMAT_ASTC_5x5_SFLOAT_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_5x5_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_5x5_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_5x5_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_5x5_UNORM_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_6x5_SFLOAT_BLOCK = ::basist::KTX2_FORMAT_ASTC_6x5_SFLOAT_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_6x5_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_6x5_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_6x5_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_6x5_UNORM_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_6x6_SFLOAT_BLOCK = ::basist::KTX2_FORMAT_ASTC_6x6_SFLOAT_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_6x6_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_6x6_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_6x6_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_6x6_UNORM_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_8x5_SFLOAT_BLOCK = ::basist::KTX2_FORMAT_ASTC_8x5_SFLOAT_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_8x5_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_8x5_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_8x5_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_8x5_UNORM_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_8x6_SFLOAT_BLOCK = ::basist::KTX2_FORMAT_ASTC_8x6_SFLOAT_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_8x6_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_8x6_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_8x6_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_8x6_UNORM_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_8x8_SRGB_BLOCK = ::basist::KTX2_FORMAT_ASTC_8x8_SRGB_BLOCK;
inline constexpr auto KTX2_FORMAT_ASTC_8x8_UNORM_BLOCK = ::basist::KTX2_FORMAT_ASTC_8x8_UNORM_BLOCK;
inline constexpr auto KTX2_IMAGE_IS_P_FRAME = ::basist::KTX2_IMAGE_IS_P_FRAME;
inline constexpr auto KTX2_KDF_DF_MODEL_ASTC = ::basist::KTX2_KDF_DF_MODEL_ASTC;
inline constexpr auto KTX2_KDF_DF_MODEL_ETC1S = ::basist::KTX2_KDF_DF_MODEL_ETC1S;
inline constexpr auto KTX2_KDF_DF_MODEL_UASTC_HDR_4X4 = ::basist::KTX2_KDF_DF_MODEL_UASTC_HDR_4X4;
inline constexpr auto KTX2_KDF_DF_MODEL_UASTC_HDR_6X6_INTERMEDIATE = ::basist::KTX2_KDF_DF_MODEL_UASTC_HDR_6X6_INTERMEDIATE;
inline constexpr auto KTX2_KDF_DF_MODEL_UASTC_LDR_4X4 = ::basist::KTX2_KDF_DF_MODEL_UASTC_LDR_4X4;
inline constexpr auto KTX2_KDF_DF_MODEL_XUASTC_LDR_INTERMEDIATE = ::basist::KTX2_KDF_DF_MODEL_XUASTC_LDR_INTERMEDIATE;
inline constexpr auto KTX2_KDF_DF_MODEL_XUBC7 = ::basist::KTX2_KDF_DF_MODEL_XUBC7;
inline constexpr auto KTX2_KHR_DF_TRANSFER_LINEAR = ::basist::KTX2_KHR_DF_TRANSFER_LINEAR;
inline constexpr auto KTX2_KHR_DF_TRANSFER_SRGB = ::basist::KTX2_KHR_DF_TRANSFER_SRGB;
inline constexpr auto KTX2_MAX_SUPPORTED_LAYER_COUNT = ::basist::KTX2_MAX_SUPPORTED_LAYER_COUNT;
inline constexpr auto KTX2_MAX_SUPPORTED_LEVEL_COUNT = ::basist::KTX2_MAX_SUPPORTED_LEVEL_COUNT;
inline constexpr auto KTX2_UASTC_BLOCK_SIZE = ::basist::KTX2_UASTC_BLOCK_SIZE;
inline constexpr auto KTX2_VK_FORMAT_UNDEFINED = ::basist::KTX2_VK_FORMAT_UNDEFINED;
inline constexpr auto MAX_BC6H_HALF_FLOAT_AS_UINT = ::basist::MAX_BC6H_HALF_FLOAT_AS_UINT;
inline constexpr auto MAX_BC6H_LAYOUT_INDEX = ::basist::MAX_BC6H_LAYOUT_INDEX;
inline constexpr auto MAX_BLOG16_VAL = ::basist::MAX_BLOG16_VAL;
inline constexpr auto MAX_HALF_FLOAT_AS_INT_BITS = ::basist::MAX_HALF_FLOAT_AS_INT_BITS;
inline constexpr auto MAX_SELECTOR_HISTORY_BUF_SIZE = ::basist::MAX_SELECTOR_HISTORY_BUF_SIZE;
inline constexpr auto NO_ENDPOINT_PRED_INDEX = ::basist::NO_ENDPOINT_PRED_INDEX;
inline constexpr auto NUM_BC6H_MODES = ::basist::NUM_BC6H_MODES;
inline constexpr auto NUM_ENDPOINT_PREDS = ::basist::NUM_ENDPOINT_PREDS;
inline constexpr auto SELECTOR_HISTORY_BUF_RLE_COUNT_BITS = ::basist::SELECTOR_HISTORY_BUF_RLE_COUNT_BITS;
inline constexpr auto SELECTOR_HISTORY_BUF_RLE_COUNT_THRESH = ::basist::SELECTOR_HISTORY_BUF_RLE_COUNT_THRESH;
inline constexpr auto SELECTOR_HISTORY_BUF_RLE_COUNT_TOTAL = ::basist::SELECTOR_HISTORY_BUF_RLE_COUNT_TOTAL;
inline constexpr auto TOTAL_ASTC_BC6H_COMMON_PARTITIONS2 = ::basist::TOTAL_ASTC_BC6H_COMMON_PARTITIONS2;
inline constexpr auto TOTAL_ASTC_BC7_COMMON_PARTITIONS2 = ::basist::TOTAL_ASTC_BC7_COMMON_PARTITIONS2;
inline constexpr auto TOTAL_ASTC_BC7_COMMON_PARTITIONS3 = ::basist::TOTAL_ASTC_BC7_COMMON_PARTITIONS3;
inline constexpr auto TOTAL_ASTC_RANGES = ::basist::TOTAL_ASTC_RANGES;
inline constexpr auto TOTAL_BC6H_PARTITION_PATTERNS = ::basist::TOTAL_BC6H_PARTITION_PATTERNS;
inline constexpr auto TOTAL_BC7_3_ASTC2_COMMON_PARTITIONS = ::basist::TOTAL_BC7_3_ASTC2_COMMON_PARTITIONS;
inline constexpr auto TOTAL_UASTC_MODES = ::basist::TOTAL_UASTC_MODES;
inline constexpr auto UASTC_MODE_INDEX_SOLID_COLOR = ::basist::UASTC_MODE_INDEX_SOLID_COLOR;
inline constexpr auto cBASISKVDataSig = ::basist::cBASISKVDataSig;
}  // namespace mcpplibs::mwrap::basis_universal::basist

export namespace mcpplibs::mwrap::basis_universal::basist::arith {
inline constexpr auto ArithMaxLen = ::basist::arith::ArithMaxLen;
inline constexpr auto ArithMaxSyms = ::basist::arith::ArithMaxSyms;
inline constexpr auto ArithMinExpectedDataBufSize = ::basist::arith::ArithMinExpectedDataBufSize;
inline constexpr auto ArithMinLen = ::basist::arith::ArithMinLen;
inline constexpr auto BMLenShift = ::basist::arith::BMLenShift;
inline constexpr auto BMMaxCount = ::basist::arith::BMMaxCount;
inline constexpr auto DMLenShift = ::basist::arith::DMLenShift;
inline constexpr auto DMMaxCount = ::basist::arith::DMMaxCount;
}  // namespace mcpplibs::mwrap::basis_universal::basist::arith

export namespace mcpplibs::mwrap::basis_universal::basist::astc_ldr_t {
inline constexpr auto ARITH_HEADER_MARKER = ::basist::astc_ldr_t::ARITH_HEADER_MARKER;
inline constexpr auto ARITH_HEADER_MARKER_BITS = ::basist::astc_ldr_t::ARITH_HEADER_MARKER_BITS;
inline constexpr auto CFG_PACK_CCS_BITS = ::basist::astc_ldr_t::CFG_PACK_CCS_BITS;
inline constexpr auto CFG_PACK_CEM_BITS = ::basist::astc_ldr_t::CFG_PACK_CEM_BITS;
inline constexpr auto CFG_PACK_EISE_BITS = ::basist::astc_ldr_t::CFG_PACK_EISE_BITS;
inline constexpr auto CFG_PACK_GRID_BITS = ::basist::astc_ldr_t::CFG_PACK_GRID_BITS;
inline constexpr auto CFG_PACK_SUBSETS_BITS = ::basist::astc_ldr_t::CFG_PACK_SUBSETS_BITS;
inline constexpr auto CFG_PACK_WISE_BITS = ::basist::astc_ldr_t::CFG_PACK_WISE_BITS;
inline constexpr auto DCT_MAX_ARITH_COEFF_MAG = ::basist::astc_ldr_t::DCT_MAX_ARITH_COEFF_MAG;
inline constexpr auto DCT_MEAN_LEVELS0 = ::basist::astc_ldr_t::DCT_MEAN_LEVELS0;
inline constexpr auto DCT_MEAN_LEVELS1 = ::basist::astc_ldr_t::DCT_MEAN_LEVELS1;
inline constexpr auto DCT_RUN_LEN_EOB_SYM_INDEX = ::basist::astc_ldr_t::DCT_RUN_LEN_EOB_SYM_INDEX;
inline constexpr auto FINAL_SYNC_MARKER = ::basist::astc_ldr_t::FINAL_SYNC_MARKER;
inline constexpr auto FINAL_SYNC_MARKER_BITS = ::basist::astc_ldr_t::FINAL_SYNC_MARKER_BITS;
inline constexpr auto FULL_ZSTD_HEADER_MARKER = ::basist::astc_ldr_t::FULL_ZSTD_HEADER_MARKER;
inline constexpr auto FULL_ZSTD_HEADER_MARKER_BITS = ::basist::astc_ldr_t::FULL_ZSTD_HEADER_MARKER_BITS;
inline constexpr auto OTM_NUM_CCS = ::basist::astc_ldr_t::OTM_NUM_CCS;
inline constexpr auto OTM_NUM_CEMS = ::basist::astc_ldr_t::OTM_NUM_CEMS;
inline constexpr auto OTM_NUM_GRID_ANISOS = ::basist::astc_ldr_t::OTM_NUM_GRID_ANISOS;
inline constexpr auto OTM_NUM_GRID_SIZES = ::basist::astc_ldr_t::OTM_NUM_GRID_SIZES;
inline constexpr auto OTM_NUM_SUBSETS = ::basist::astc_ldr_t::OTM_NUM_SUBSETS;
inline constexpr auto PART_HASH_BITS = ::basist::astc_ldr_t::PART_HASH_BITS;
inline constexpr auto PART_HASH_SIZE = ::basist::astc_ldr_t::PART_HASH_SIZE;
inline constexpr auto TM_HASH_BITS = ::basist::astc_ldr_t::TM_HASH_BITS;
inline constexpr auto TM_HASH_SIZE = ::basist::astc_ldr_t::TM_HASH_SIZE;
inline constexpr auto XUASTC_LDR_MODE_BYTE_DPCM_ENDPOINTS_FLAG = ::basist::astc_ldr_t::XUASTC_LDR_MODE_BYTE_DPCM_ENDPOINTS_FLAG;
inline constexpr auto XUASTC_LDR_MODE_BYTE_IS_BASE_OFS_FLAG = ::basist::astc_ldr_t::XUASTC_LDR_MODE_BYTE_IS_BASE_OFS_FLAG;
inline constexpr auto XUASTC_LDR_MODE_BYTE_PART_HASH_HIT = ::basist::astc_ldr_t::XUASTC_LDR_MODE_BYTE_PART_HASH_HIT;
inline constexpr auto XUASTC_LDR_MODE_BYTE_TM_HASH_HIT_FLAG = ::basist::astc_ldr_t::XUASTC_LDR_MODE_BYTE_TM_HASH_HIT_FLAG;
inline constexpr auto XUASTC_LDR_MODE_BYTE_USE_DCT = ::basist::astc_ldr_t::XUASTC_LDR_MODE_BYTE_USE_DCT;
inline constexpr auto cMaxConfigReuseNeighbors = ::basist::astc_ldr_t::cMaxConfigReuseNeighbors;
}  // namespace mcpplibs::mwrap::basis_universal::basist::astc_ldr_t

export namespace mcpplibs::mwrap::basis_universal::basisu {
inline constexpr auto BASISU_PATH_SEPERATOR_CHAR = ::basisu::BASISU_PATH_SEPERATOR_CHAR;
inline constexpr auto BIG_FLOAT_VAL = ::basisu::BIG_FLOAT_VAL;
inline constexpr auto REALLY_SMALL_FLOAT_VAL = ::basisu::REALLY_SMALL_FLOAT_VAL;
inline constexpr auto SIZE_T_BITS = ::basisu::SIZE_T_BITS;
inline constexpr auto SMALL_FLOAT_VAL = ::basisu::SMALL_FLOAT_VAL;
inline constexpr auto cHuffmanTotalSortedCodelengthCodes = ::basisu::cHuffmanTotalSortedCodelengthCodes;
inline constexpr auto cPiD = ::basisu::cPiD;
}  // namespace mcpplibs::mwrap::basis_universal::basisu
