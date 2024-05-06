/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|*Target Instruction Enum Values                                              *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


#ifdef GET_INSTRINFO_ENUM
#undef GET_INSTRINFO_ENUM

enum {
  TMS320C64x_PHI	= 0,
  TMS320C64x_INLINEASM	= 1,
  TMS320C64x_CFI_INSTRUCTION	= 2,
  TMS320C64x_EH_LABEL	= 3,
  TMS320C64x_GC_LABEL	= 4,
  TMS320C64x_KILL	= 5,
  TMS320C64x_EXTRACT_SUBREG	= 6,
  TMS320C64x_INSERT_SUBREG	= 7,
  TMS320C64x_IMPLICIT_DEF	= 8,
  TMS320C64x_SUBREG_TO_REG	= 9,
  TMS320C64x_COPY_TO_REGCLASS	= 10,
  TMS320C64x_DBG_VALUE	= 11,
  TMS320C64x_REG_SEQUENCE	= 12,
  TMS320C64x_COPY	= 13,
  TMS320C64x_BUNDLE	= 14,
  TMS320C64x_LIFETIME_START	= 15,
  TMS320C64x_LIFETIME_END	= 16,
  TMS320C64x_STACKMAP	= 17,
  TMS320C64x_PATCHPOINT	= 18,
  TMS320C64x_LOAD_STACK_GUARD	= 19,
  TMS320C64x_STATEPOINT	= 20,
  TMS320C64x_FRAME_ALLOC	= 21,
  TMS320C64x_ABS2_l2_rr	= 22,
  TMS320C64x_ABS_l1_pp	= 23,
  TMS320C64x_ABS_l1_rr	= 24,
  TMS320C64x_ADD2_d2_rrr	= 25,
  TMS320C64x_ADD2_l1_rrr_x2	= 26,
  TMS320C64x_ADD2_s1_rrr	= 27,
  TMS320C64x_ADD4_l1_rrr_x2	= 28,
  TMS320C64x_ADDAB_d1_rir	= 29,
  TMS320C64x_ADDAB_d1_rrr	= 30,
  TMS320C64x_ADDAD_d1_rir	= 31,
  TMS320C64x_ADDAD_d1_rrr	= 32,
  TMS320C64x_ADDAH_d1_rir	= 33,
  TMS320C64x_ADDAH_d1_rrr	= 34,
  TMS320C64x_ADDAW_d1_rir	= 35,
  TMS320C64x_ADDAW_d1_rrr	= 36,
  TMS320C64x_ADDKPC_s3_iir	= 37,
  TMS320C64x_ADDK_s2_ir	= 38,
  TMS320C64x_ADDU_l1_rpp	= 39,
  TMS320C64x_ADDU_l1_rrp_x2	= 40,
  TMS320C64x_ADD_d1_rir	= 41,
  TMS320C64x_ADD_d1_rrr	= 42,
  TMS320C64x_ADD_d2_rir	= 43,
  TMS320C64x_ADD_d2_rrr	= 44,
  TMS320C64x_ADD_l1_ipp	= 45,
  TMS320C64x_ADD_l1_irr	= 46,
  TMS320C64x_ADD_l1_rpp	= 47,
  TMS320C64x_ADD_l1_rrp_x2	= 48,
  TMS320C64x_ADD_l1_rrr_x2	= 49,
  TMS320C64x_ADD_s1_irr	= 50,
  TMS320C64x_ADD_s1_rrr	= 51,
  TMS320C64x_ANDN_d2_rrr	= 52,
  TMS320C64x_ANDN_l1_rrr_x2	= 53,
  TMS320C64x_ANDN_s4_rrr	= 54,
  TMS320C64x_AND_d2_rir	= 55,
  TMS320C64x_AND_d2_rrr	= 56,
  TMS320C64x_AND_l1_irr	= 57,
  TMS320C64x_AND_l1_rrr_x2	= 58,
  TMS320C64x_AND_s1_irr	= 59,
  TMS320C64x_AND_s1_rrr	= 60,
  TMS320C64x_AVG2_m1_rrr	= 61,
  TMS320C64x_AVGU4_m1_rrr	= 62,
  TMS320C64x_BDEC_s8_ir	= 63,
  TMS320C64x_BITC4_m2_rr	= 64,
  TMS320C64x_BNOP_s10_ri	= 65,
  TMS320C64x_BNOP_s9_ii	= 66,
  TMS320C64x_BPOS_s8_ir	= 67,
  TMS320C64x_B_s5_i	= 68,
  TMS320C64x_B_s6_r	= 69,
  TMS320C64x_B_s7_irp	= 70,
  TMS320C64x_B_s7_nrp	= 71,
  TMS320C64x_CLR_s15_riir	= 72,
  TMS320C64x_CLR_s1_rrr	= 73,
  TMS320C64x_CMPEQ2_s1_rrr	= 74,
  TMS320C64x_CMPEQ4_s1_rrr	= 75,
  TMS320C64x_CMPEQ_l1_ipr	= 76,
  TMS320C64x_CMPEQ_l1_irr	= 77,
  TMS320C64x_CMPEQ_l1_rpr	= 78,
  TMS320C64x_CMPEQ_l1_rrr_x2	= 79,
  TMS320C64x_CMPGT2_s1_rrr	= 80,
  TMS320C64x_CMPGTU4_s1_rrr	= 81,
  TMS320C64x_CMPGT_l1_ipr	= 82,
  TMS320C64x_CMPGT_l1_irr	= 83,
  TMS320C64x_CMPGT_l1_rpr	= 84,
  TMS320C64x_CMPGT_l1_rrr_x2	= 85,
  TMS320C64x_CMPLTU_l1_ipr	= 86,
  TMS320C64x_CMPLTU_l1_irr	= 87,
  TMS320C64x_CMPLTU_l1_rpr	= 88,
  TMS320C64x_CMPLTU_l1_rrr_x2	= 89,
  TMS320C64x_CMPLT_l1_ipr	= 90,
  TMS320C64x_CMPLT_l1_irr	= 91,
  TMS320C64x_CMPLT_l1_rpr	= 92,
  TMS320C64x_CMPLT_l1_rrr_x2	= 93,
  TMS320C64x_DEAL_m2_rr	= 94,
  TMS320C64x_DOTP2_m1_rrp	= 95,
  TMS320C64x_DOTP2_m1_rrr	= 96,
  TMS320C64x_DOTPN2_m1_rrr	= 97,
  TMS320C64x_DOTPNRSU2_m1_rrr	= 98,
  TMS320C64x_DOTPRSU2_m1_rrr	= 99,
  TMS320C64x_DOTPSU4_m1_rrr	= 100,
  TMS320C64x_DOTPU4_m1_rrr	= 101,
  TMS320C64x_EXTU_s15_riir	= 102,
  TMS320C64x_EXTU_s1_rrr	= 103,
  TMS320C64x_EXT_s15_riir	= 104,
  TMS320C64x_EXT_s1_rrr	= 105,
  TMS320C64x_GMPGTU_l1_ipr	= 106,
  TMS320C64x_GMPGTU_l1_irr	= 107,
  TMS320C64x_GMPGTU_l1_rpr	= 108,
  TMS320C64x_GMPGTU_l1_rrr_x2	= 109,
  TMS320C64x_GMPY4_m1_rrr	= 110,
  TMS320C64x_LDBU_d5_mr	= 111,
  TMS320C64x_LDBU_d6_mr	= 112,
  TMS320C64x_LDB_d5_mr	= 113,
  TMS320C64x_LDB_d6_mr	= 114,
  TMS320C64x_LDDW_d7_mp	= 115,
  TMS320C64x_LDHU_d5_mr	= 116,
  TMS320C64x_LDHU_d6_mr	= 117,
  TMS320C64x_LDH_d5_mr	= 118,
  TMS320C64x_LDH_d6_mr	= 119,
  TMS320C64x_LDNDW_d8_mp	= 120,
  TMS320C64x_LDNW_d5_mr	= 121,
  TMS320C64x_LDW_d5_mr	= 122,
  TMS320C64x_LDW_d6_mr	= 123,
  TMS320C64x_LMBD_l1_irr	= 124,
  TMS320C64x_LMBD_l1_rrr_x2	= 125,
  TMS320C64x_MAX2_l1_rrr_x2	= 126,
  TMS320C64x_MAXU4_l1_rrr_x2	= 127,
  TMS320C64x_MIN2_l1_rrr_x2	= 128,
  TMS320C64x_MINU4_l1_rrr_x2	= 129,
  TMS320C64x_MPY2_m1_rrp	= 130,
  TMS320C64x_MPYHIR_m1_rrr	= 131,
  TMS320C64x_MPYHI_m1_rrp	= 132,
  TMS320C64x_MPYHLU_m4_rrr	= 133,
  TMS320C64x_MPYHL_m4_rrr	= 134,
  TMS320C64x_MPYHSLU_m4_rrr	= 135,
  TMS320C64x_MPYHSU_m4_rrr	= 136,
  TMS320C64x_MPYHULS_m4_rrr	= 137,
  TMS320C64x_MPYHUS_m4_rrr	= 138,
  TMS320C64x_MPYHU_m4_rrr	= 139,
  TMS320C64x_MPYH_m4_rrr	= 140,
  TMS320C64x_MPYLHU_m4_rrr	= 141,
  TMS320C64x_MPYLH_m4_rrr	= 142,
  TMS320C64x_MPYLIR_m1_rrr	= 143,
  TMS320C64x_MPYLI_m1_rrp	= 144,
  TMS320C64x_MPYLSHU_m4_rrr	= 145,
  TMS320C64x_MPYLUHS_m4_rrr	= 146,
  TMS320C64x_MPYSU4_m1_rrp	= 147,
  TMS320C64x_MPYSU_m4_irr	= 148,
  TMS320C64x_MPYSU_m4_rrr	= 149,
  TMS320C64x_MPYU4_m1_rrp	= 150,
  TMS320C64x_MPYUS_m4_rrr	= 151,
  TMS320C64x_MPYU_m4_rrr	= 152,
  TMS320C64x_MPY_m4_irr	= 153,
  TMS320C64x_MPY_m4_rrr	= 154,
  TMS320C64x_MVC_s1_rr	= 155,
  TMS320C64x_MVC_s1_rr2	= 156,
  TMS320C64x_MVD_m2_rr	= 157,
  TMS320C64x_MVKLH_s12_ir	= 158,
  TMS320C64x_MVKL_s12_ir	= 159,
  TMS320C64x_MVK_d1_rr	= 160,
  TMS320C64x_MVK_l2_ir	= 161,
  TMS320C64x_NOP_n	= 162,
  TMS320C64x_NORM_l1_pr	= 163,
  TMS320C64x_NORM_l1_rr	= 164,
  TMS320C64x_OR_d2_rir	= 165,
  TMS320C64x_OR_d2_rrr	= 166,
  TMS320C64x_OR_l1_irr	= 167,
  TMS320C64x_OR_l1_rrr_x2	= 168,
  TMS320C64x_OR_s1_irr	= 169,
  TMS320C64x_OR_s1_rrr	= 170,
  TMS320C64x_PACK2_l1_rrr_x2	= 171,
  TMS320C64x_PACK2_s4_rrr	= 172,
  TMS320C64x_PACKH2_l1_rrr_x2	= 173,
  TMS320C64x_PACKH2_s1_rrr	= 174,
  TMS320C64x_PACKH4_l1_rrr_x2	= 175,
  TMS320C64x_PACKHL2_l1_rrr_x2	= 176,
  TMS320C64x_PACKHL2_s1_rrr	= 177,
  TMS320C64x_PACKL4_l1_rrr_x2	= 178,
  TMS320C64x_PACKLH2_l1_rrr_x2	= 179,
  TMS320C64x_PACKLH2_s1_rrr	= 180,
  TMS320C64x_ROTL_m1_rir	= 181,
  TMS320C64x_ROTL_m1_rrr	= 182,
  TMS320C64x_SADD2_s4_rrr	= 183,
  TMS320C64x_SADDU4_s4_rrr	= 184,
  TMS320C64x_SADDUS2_s4_rrr	= 185,
  TMS320C64x_SADD_l1_ipp	= 186,
  TMS320C64x_SADD_l1_irr	= 187,
  TMS320C64x_SADD_l1_rpp	= 188,
  TMS320C64x_SADD_l1_rrr_x2	= 189,
  TMS320C64x_SADD_s1_rrr	= 190,
  TMS320C64x_SAT_l1_pr	= 191,
  TMS320C64x_SET_s15_riir	= 192,
  TMS320C64x_SET_s1_rrr	= 193,
  TMS320C64x_SHFL_m2_rr	= 194,
  TMS320C64x_SHLMB_l1_rrr_x2	= 195,
  TMS320C64x_SHLMB_s4_rrr	= 196,
  TMS320C64x_SHL_s1_pip	= 197,
  TMS320C64x_SHL_s1_prp	= 198,
  TMS320C64x_SHL_s1_rip	= 199,
  TMS320C64x_SHL_s1_rir	= 200,
  TMS320C64x_SHL_s1_rrp	= 201,
  TMS320C64x_SHL_s1_rrr	= 202,
  TMS320C64x_SHR2_s1_rir	= 203,
  TMS320C64x_SHR2_s4_rrr	= 204,
  TMS320C64x_SHRMB_l1_rrr_x2	= 205,
  TMS320C64x_SHRMB_s4_rrr	= 206,
  TMS320C64x_SHRU2_s1_rir	= 207,
  TMS320C64x_SHRU2_s4_rrr	= 208,
  TMS320C64x_SHRU_s1_pip	= 209,
  TMS320C64x_SHRU_s1_prp	= 210,
  TMS320C64x_SHRU_s1_rir	= 211,
  TMS320C64x_SHRU_s1_rrr	= 212,
  TMS320C64x_SHR_s1_pip	= 213,
  TMS320C64x_SHR_s1_prp	= 214,
  TMS320C64x_SHR_s1_rir	= 215,
  TMS320C64x_SHR_s1_rrr	= 216,
  TMS320C64x_SMPY2_m1_rrp	= 217,
  TMS320C64x_SMPYHL_m4_rrr	= 218,
  TMS320C64x_SMPYH_m4_rrr	= 219,
  TMS320C64x_SMPYLH_m4_rrr	= 220,
  TMS320C64x_SMPY_m4_rrr	= 221,
  TMS320C64x_SPACK2_s4_rrr	= 222,
  TMS320C64x_SPACKU4_s4_rrr	= 223,
  TMS320C64x_SSHL_s1_rir	= 224,
  TMS320C64x_SSHL_s1_rrr	= 225,
  TMS320C64x_SSHVL_m1_rrr	= 226,
  TMS320C64x_SSHVR_m1_rrr	= 227,
  TMS320C64x_SSUB_l1_ipp	= 228,
  TMS320C64x_SSUB_l1_irr	= 229,
  TMS320C64x_SSUB_l1_rrr_x1	= 230,
  TMS320C64x_SSUB_l1_rrr_x2	= 231,
  TMS320C64x_STB_d5_rm	= 232,
  TMS320C64x_STB_d6_rm	= 233,
  TMS320C64x_STDW_d7_pm	= 234,
  TMS320C64x_STH_d5_rm	= 235,
  TMS320C64x_STH_d6_rm	= 236,
  TMS320C64x_STNDW_d8_pm	= 237,
  TMS320C64x_STNW_d5_rm	= 238,
  TMS320C64x_STW_d5_rm	= 239,
  TMS320C64x_STW_d6_rm	= 240,
  TMS320C64x_SUB2_d2_rrr	= 241,
  TMS320C64x_SUB2_l1_rrr_x2	= 242,
  TMS320C64x_SUB2_s1_rrr	= 243,
  TMS320C64x_SUB4_l1_rrr_x2	= 244,
  TMS320C64x_SUBABS4_l1_rrr_x2	= 245,
  TMS320C64x_SUBAB_d1_rir	= 246,
  TMS320C64x_SUBAB_d1_rrr	= 247,
  TMS320C64x_SUBAH_d1_rir	= 248,
  TMS320C64x_SUBAH_d1_rrr	= 249,
  TMS320C64x_SUBAW_d1_rir	= 250,
  TMS320C64x_SUBAW_d1_rrr	= 251,
  TMS320C64x_SUBC_l1_rrr_x2	= 252,
  TMS320C64x_SUBU_l1_rrp_x1	= 253,
  TMS320C64x_SUBU_l1_rrp_x2	= 254,
  TMS320C64x_SUB_d1_rir	= 255,
  TMS320C64x_SUB_d1_rrr	= 256,
  TMS320C64x_SUB_d2_rrr	= 257,
  TMS320C64x_SUB_l1_ipp	= 258,
  TMS320C64x_SUB_l1_irr	= 259,
  TMS320C64x_SUB_l1_rrp_x1	= 260,
  TMS320C64x_SUB_l1_rrp_x2	= 261,
  TMS320C64x_SUB_l1_rrr_x1	= 262,
  TMS320C64x_SUB_l1_rrr_x2	= 263,
  TMS320C64x_SUB_s1_irr	= 264,
  TMS320C64x_SUB_s1_rrr	= 265,
  TMS320C64x_SUB_s4_rrr	= 266,
  TMS320C64x_SWAP4_l2_rr	= 267,
  TMS320C64x_UNPKHU4_l2_rr	= 268,
  TMS320C64x_UNPKHU4_s14_rr	= 269,
  TMS320C64x_UNPKLU4_l2_rr	= 270,
  TMS320C64x_UNPKLU4_s14_rr	= 271,
  TMS320C64x_XOR_d2_rir	= 272,
  TMS320C64x_XOR_d2_rrr	= 273,
  TMS320C64x_XOR_l1_irr	= 274,
  TMS320C64x_XOR_l1_rrr_x2	= 275,
  TMS320C64x_XOR_s1_irr	= 276,
  TMS320C64x_XOR_s1_rrr	= 277,
  TMS320C64x_XPND2_m2_rr	= 278,
  TMS320C64x_XPND4_m2_rr	= 279,
  TMS320C64x_INSTRUCTION_LIST_END = 280
};

#endif // GET_INSTRINFO_ENUM
