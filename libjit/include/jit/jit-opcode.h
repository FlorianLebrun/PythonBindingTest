/* Automatically generated from ../../jit/jit-opcodes.ops - DO NOT EDIT */

/*
 * jit-opcode.h - List of primitive opcodes for JIT instructions.
 *
 * Copyright (C) 2004  Southern Storm Software, Pty Ltd.
 *
 * The libjit library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * The libjit library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the libjit library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef	_JIT_OPCODE_H
#define	_JIT_OPCODE_H

#include <jit/jit-defs.h>

#ifdef	__cplusplus
extern	"C" {
#endif

#define	JIT_OP_NOP						0x0000
#define	JIT_OP_TRUNC_SBYTE					0x0001
#define	JIT_OP_TRUNC_UBYTE					0x0002
#define	JIT_OP_TRUNC_SHORT					0x0003
#define	JIT_OP_TRUNC_USHORT					0x0004
#define	JIT_OP_TRUNC_INT					0x0005
#define	JIT_OP_TRUNC_UINT					0x0006
#define	JIT_OP_CHECK_SBYTE					0x0007
#define	JIT_OP_CHECK_UBYTE					0x0008
#define	JIT_OP_CHECK_SHORT					0x0009
#define	JIT_OP_CHECK_USHORT					0x000A
#define	JIT_OP_CHECK_INT					0x000B
#define	JIT_OP_CHECK_UINT					0x000C
#define	JIT_OP_LOW_WORD						0x000D
#define	JIT_OP_EXPAND_INT					0x000E
#define	JIT_OP_EXPAND_UINT					0x000F
#define	JIT_OP_CHECK_LOW_WORD					0x0010
#define	JIT_OP_CHECK_SIGNED_LOW_WORD				0x0011
#define	JIT_OP_CHECK_LONG					0x0012
#define	JIT_OP_CHECK_ULONG					0x0013
#define	JIT_OP_FLOAT32_TO_INT					0x0014
#define	JIT_OP_FLOAT32_TO_UINT					0x0015
#define	JIT_OP_FLOAT32_TO_LONG					0x0016
#define	JIT_OP_FLOAT32_TO_ULONG					0x0017
#define	JIT_OP_CHECK_FLOAT32_TO_INT				0x0018
#define	JIT_OP_CHECK_FLOAT32_TO_UINT				0x0019
#define	JIT_OP_CHECK_FLOAT32_TO_LONG				0x001A
#define	JIT_OP_CHECK_FLOAT32_TO_ULONG				0x001B
#define	JIT_OP_INT_TO_FLOAT32					0x001C
#define	JIT_OP_UINT_TO_FLOAT32					0x001D
#define	JIT_OP_LONG_TO_FLOAT32					0x001E
#define	JIT_OP_ULONG_TO_FLOAT32					0x001F
#define	JIT_OP_FLOAT32_TO_FLOAT64				0x0020
#define	JIT_OP_FLOAT64_TO_INT					0x0021
#define	JIT_OP_FLOAT64_TO_UINT					0x0022
#define	JIT_OP_FLOAT64_TO_LONG					0x0023
#define	JIT_OP_FLOAT64_TO_ULONG					0x0024
#define	JIT_OP_CHECK_FLOAT64_TO_INT				0x0025
#define	JIT_OP_CHECK_FLOAT64_TO_UINT				0x0026
#define	JIT_OP_CHECK_FLOAT64_TO_LONG				0x0027
#define	JIT_OP_CHECK_FLOAT64_TO_ULONG				0x0028
#define	JIT_OP_INT_TO_FLOAT64					0x0029
#define	JIT_OP_UINT_TO_FLOAT64					0x002A
#define	JIT_OP_LONG_TO_FLOAT64					0x002B
#define	JIT_OP_ULONG_TO_FLOAT64					0x002C
#define	JIT_OP_FLOAT64_TO_FLOAT32				0x002D
#define	JIT_OP_NFLOAT_TO_INT					0x002E
#define	JIT_OP_NFLOAT_TO_UINT					0x002F
#define	JIT_OP_NFLOAT_TO_LONG					0x0030
#define	JIT_OP_NFLOAT_TO_ULONG					0x0031
#define	JIT_OP_CHECK_NFLOAT_TO_INT				0x0032
#define	JIT_OP_CHECK_NFLOAT_TO_UINT				0x0033
#define	JIT_OP_CHECK_NFLOAT_TO_LONG				0x0034
#define	JIT_OP_CHECK_NFLOAT_TO_ULONG				0x0035
#define	JIT_OP_INT_TO_NFLOAT					0x0036
#define	JIT_OP_UINT_TO_NFLOAT					0x0037
#define	JIT_OP_LONG_TO_NFLOAT					0x0038
#define	JIT_OP_ULONG_TO_NFLOAT					0x0039
#define	JIT_OP_NFLOAT_TO_FLOAT32				0x003A
#define	JIT_OP_NFLOAT_TO_FLOAT64				0x003B
#define	JIT_OP_FLOAT32_TO_NFLOAT				0x003C
#define	JIT_OP_FLOAT64_TO_NFLOAT				0x003D
#define	JIT_OP_IADD						0x003E
#define	JIT_OP_IADD_OVF						0x003F
#define	JIT_OP_IADD_OVF_UN					0x0040
#define	JIT_OP_ISUB						0x0041
#define	JIT_OP_ISUB_OVF						0x0042
#define	JIT_OP_ISUB_OVF_UN					0x0043
#define	JIT_OP_IMUL						0x0044
#define	JIT_OP_IMUL_OVF						0x0045
#define	JIT_OP_IMUL_OVF_UN					0x0046
#define	JIT_OP_IDIV						0x0047
#define	JIT_OP_IDIV_UN						0x0048
#define	JIT_OP_IREM						0x0049
#define	JIT_OP_IREM_UN						0x004A
#define	JIT_OP_INEG						0x004B
#define	JIT_OP_LADD						0x004C
#define	JIT_OP_LADD_OVF						0x004D
#define	JIT_OP_LADD_OVF_UN					0x004E
#define	JIT_OP_LSUB						0x004F
#define	JIT_OP_LSUB_OVF						0x0050
#define	JIT_OP_LSUB_OVF_UN					0x0051
#define	JIT_OP_LMUL						0x0052
#define	JIT_OP_LMUL_OVF						0x0053
#define	JIT_OP_LMUL_OVF_UN					0x0054
#define	JIT_OP_LDIV						0x0055
#define	JIT_OP_LDIV_UN						0x0056
#define	JIT_OP_LREM						0x0057
#define	JIT_OP_LREM_UN						0x0058
#define	JIT_OP_LNEG						0x0059
#define	JIT_OP_FADD						0x005A
#define	JIT_OP_FSUB						0x005B
#define	JIT_OP_FMUL						0x005C
#define	JIT_OP_FDIV						0x005D
#define	JIT_OP_FREM						0x005E
#define	JIT_OP_FREM_IEEE					0x005F
#define	JIT_OP_FNEG						0x0060
#define	JIT_OP_DADD						0x0061
#define	JIT_OP_DSUB						0x0062
#define	JIT_OP_DMUL						0x0063
#define	JIT_OP_DDIV						0x0064
#define	JIT_OP_DREM						0x0065
#define	JIT_OP_DREM_IEEE					0x0066
#define	JIT_OP_DNEG						0x0067
#define	JIT_OP_NFADD						0x0068
#define	JIT_OP_NFSUB						0x0069
#define	JIT_OP_NFMUL						0x006A
#define	JIT_OP_NFDIV						0x006B
#define	JIT_OP_NFREM						0x006C
#define	JIT_OP_NFREM_IEEE					0x006D
#define	JIT_OP_NFNEG						0x006E
#define	JIT_OP_IAND						0x006F
#define	JIT_OP_IOR						0x0070
#define	JIT_OP_IXOR						0x0071
#define	JIT_OP_INOT						0x0072
#define	JIT_OP_ISHL						0x0073
#define	JIT_OP_ISHR						0x0074
#define	JIT_OP_ISHR_UN						0x0075
#define	JIT_OP_LAND						0x0076
#define	JIT_OP_LOR						0x0077
#define	JIT_OP_LXOR						0x0078
#define	JIT_OP_LNOT						0x0079
#define	JIT_OP_LSHL						0x007A
#define	JIT_OP_LSHR						0x007B
#define	JIT_OP_LSHR_UN						0x007C
#define	JIT_OP_BR						0x007D
#define	JIT_OP_BR_IFALSE					0x007E
#define	JIT_OP_BR_ITRUE						0x007F
#define	JIT_OP_BR_IEQ						0x0080
#define	JIT_OP_BR_INE						0x0081
#define	JIT_OP_BR_ILT						0x0082
#define	JIT_OP_BR_ILT_UN					0x0083
#define	JIT_OP_BR_ILE						0x0084
#define	JIT_OP_BR_ILE_UN					0x0085
#define	JIT_OP_BR_IGT						0x0086
#define	JIT_OP_BR_IGT_UN					0x0087
#define	JIT_OP_BR_IGE						0x0088
#define	JIT_OP_BR_IGE_UN					0x0089
#define	JIT_OP_BR_LFALSE					0x008A
#define	JIT_OP_BR_LTRUE						0x008B
#define	JIT_OP_BR_LEQ						0x008C
#define	JIT_OP_BR_LNE						0x008D
#define	JIT_OP_BR_LLT						0x008E
#define	JIT_OP_BR_LLT_UN					0x008F
#define	JIT_OP_BR_LLE						0x0090
#define	JIT_OP_BR_LLE_UN					0x0091
#define	JIT_OP_BR_LGT						0x0092
#define	JIT_OP_BR_LGT_UN					0x0093
#define	JIT_OP_BR_LGE						0x0094
#define	JIT_OP_BR_LGE_UN					0x0095
#define	JIT_OP_BR_FEQ						0x0096
#define	JIT_OP_BR_FNE						0x0097
#define	JIT_OP_BR_FLT						0x0098
#define	JIT_OP_BR_FLE						0x0099
#define	JIT_OP_BR_FGT						0x009A
#define	JIT_OP_BR_FGE						0x009B
#define	JIT_OP_BR_FLT_INV					0x009C
#define	JIT_OP_BR_FLE_INV					0x009D
#define	JIT_OP_BR_FGT_INV					0x009E
#define	JIT_OP_BR_FGE_INV					0x009F
#define	JIT_OP_BR_DEQ						0x00A0
#define	JIT_OP_BR_DNE						0x00A1
#define	JIT_OP_BR_DLT						0x00A2
#define	JIT_OP_BR_DLE						0x00A3
#define	JIT_OP_BR_DGT						0x00A4
#define	JIT_OP_BR_DGE						0x00A5
#define	JIT_OP_BR_DLT_INV					0x00A6
#define	JIT_OP_BR_DLE_INV					0x00A7
#define	JIT_OP_BR_DGT_INV					0x00A8
#define	JIT_OP_BR_DGE_INV					0x00A9
#define	JIT_OP_BR_NFEQ						0x00AA
#define	JIT_OP_BR_NFNE						0x00AB
#define	JIT_OP_BR_NFLT						0x00AC
#define	JIT_OP_BR_NFLE						0x00AD
#define	JIT_OP_BR_NFGT						0x00AE
#define	JIT_OP_BR_NFGE						0x00AF
#define	JIT_OP_BR_NFLT_INV					0x00B0
#define	JIT_OP_BR_NFLE_INV					0x00B1
#define	JIT_OP_BR_NFGT_INV					0x00B2
#define	JIT_OP_BR_NFGE_INV					0x00B3
#define	JIT_OP_ICMP						0x00B4
#define	JIT_OP_ICMP_UN						0x00B5
#define	JIT_OP_LCMP						0x00B6
#define	JIT_OP_LCMP_UN						0x00B7
#define	JIT_OP_FCMPL						0x00B8
#define	JIT_OP_FCMPG						0x00B9
#define	JIT_OP_DCMPL						0x00BA
#define	JIT_OP_DCMPG						0x00BB
#define	JIT_OP_NFCMPL						0x00BC
#define	JIT_OP_NFCMPG						0x00BD
#define	JIT_OP_IEQ						0x00BE
#define	JIT_OP_INE						0x00BF
#define	JIT_OP_ILT						0x00C0
#define	JIT_OP_ILT_UN						0x00C1
#define	JIT_OP_ILE						0x00C2
#define	JIT_OP_ILE_UN						0x00C3
#define	JIT_OP_IGT						0x00C4
#define	JIT_OP_IGT_UN						0x00C5
#define	JIT_OP_IGE						0x00C6
#define	JIT_OP_IGE_UN						0x00C7
#define	JIT_OP_LEQ						0x00C8
#define	JIT_OP_LNE						0x00C9
#define	JIT_OP_LLT						0x00CA
#define	JIT_OP_LLT_UN						0x00CB
#define	JIT_OP_LLE						0x00CC
#define	JIT_OP_LLE_UN						0x00CD
#define	JIT_OP_LGT						0x00CE
#define	JIT_OP_LGT_UN						0x00CF
#define	JIT_OP_LGE						0x00D0
#define	JIT_OP_LGE_UN						0x00D1
#define	JIT_OP_FEQ						0x00D2
#define	JIT_OP_FNE						0x00D3
#define	JIT_OP_FLT						0x00D4
#define	JIT_OP_FLE						0x00D5
#define	JIT_OP_FGT						0x00D6
#define	JIT_OP_FGE						0x00D7
#define	JIT_OP_FLT_INV						0x00D8
#define	JIT_OP_FLE_INV						0x00D9
#define	JIT_OP_FGT_INV						0x00DA
#define	JIT_OP_FGE_INV						0x00DB
#define	JIT_OP_DEQ						0x00DC
#define	JIT_OP_DNE						0x00DD
#define	JIT_OP_DLT						0x00DE
#define	JIT_OP_DLE						0x00DF
#define	JIT_OP_DGT						0x00E0
#define	JIT_OP_DGE						0x00E1
#define	JIT_OP_DLT_INV						0x00E2
#define	JIT_OP_DLE_INV						0x00E3
#define	JIT_OP_DGT_INV						0x00E4
#define	JIT_OP_DGE_INV						0x00E5
#define	JIT_OP_NFEQ						0x00E6
#define	JIT_OP_NFNE						0x00E7
#define	JIT_OP_NFLT						0x00E8
#define	JIT_OP_NFLE						0x00E9
#define	JIT_OP_NFGT						0x00EA
#define	JIT_OP_NFGE						0x00EB
#define	JIT_OP_NFLT_INV						0x00EC
#define	JIT_OP_NFLE_INV						0x00ED
#define	JIT_OP_NFGT_INV						0x00EE
#define	JIT_OP_NFGE_INV						0x00EF
#define	JIT_OP_IS_FNAN						0x00F0
#define	JIT_OP_IS_FINF						0x00F1
#define	JIT_OP_IS_FFINITE					0x00F2
#define	JIT_OP_IS_DNAN						0x00F3
#define	JIT_OP_IS_DINF						0x00F4
#define	JIT_OP_IS_DFINITE					0x00F5
#define	JIT_OP_IS_NFNAN						0x00F6
#define	JIT_OP_IS_NFINF						0x00F7
#define	JIT_OP_IS_NFFINITE					0x00F8
#define	JIT_OP_FACOS						0x00F9
#define	JIT_OP_FASIN						0x00FA
#define	JIT_OP_FATAN						0x00FB
#define	JIT_OP_FATAN2						0x00FC
#define	JIT_OP_FCEIL						0x00FD
#define	JIT_OP_FCOS						0x00FE
#define	JIT_OP_FCOSH						0x00FF
#define	JIT_OP_FEXP						0x0100
#define	JIT_OP_FFLOOR						0x0101
#define	JIT_OP_FLOG						0x0102
#define	JIT_OP_FLOG10						0x0103
#define	JIT_OP_FPOW						0x0104
#define	JIT_OP_FRINT						0x0105
#define	JIT_OP_FROUND						0x0106
#define	JIT_OP_FSIN						0x0107
#define	JIT_OP_FSINH						0x0108
#define	JIT_OP_FSQRT						0x0109
#define	JIT_OP_FTAN						0x010A
#define	JIT_OP_FTANH						0x010B
#define	JIT_OP_FTRUNC						0x010C
#define	JIT_OP_DACOS						0x010D
#define	JIT_OP_DASIN						0x010E
#define	JIT_OP_DATAN						0x010F
#define	JIT_OP_DATAN2						0x0110
#define	JIT_OP_DCEIL						0x0111
#define	JIT_OP_DCOS						0x0112
#define	JIT_OP_DCOSH						0x0113
#define	JIT_OP_DEXP						0x0114
#define	JIT_OP_DFLOOR						0x0115
#define	JIT_OP_DLOG						0x0116
#define	JIT_OP_DLOG10						0x0117
#define	JIT_OP_DPOW						0x0118
#define	JIT_OP_DRINT						0x0119
#define	JIT_OP_DROUND						0x011A
#define	JIT_OP_DSIN						0x011B
#define	JIT_OP_DSINH						0x011C
#define	JIT_OP_DSQRT						0x011D
#define	JIT_OP_DTAN						0x011E
#define	JIT_OP_DTANH						0x011F
#define	JIT_OP_DTRUNC						0x0120
#define	JIT_OP_NFACOS						0x0121
#define	JIT_OP_NFASIN						0x0122
#define	JIT_OP_NFATAN						0x0123
#define	JIT_OP_NFATAN2						0x0124
#define	JIT_OP_NFCEIL						0x0125
#define	JIT_OP_NFCOS						0x0126
#define	JIT_OP_NFCOSH						0x0127
#define	JIT_OP_NFEXP						0x0128
#define	JIT_OP_NFFLOOR						0x0129
#define	JIT_OP_NFLOG						0x012A
#define	JIT_OP_NFLOG10						0x012B
#define	JIT_OP_NFPOW						0x012C
#define	JIT_OP_NFRINT						0x012D
#define	JIT_OP_NFROUND						0x012E
#define	JIT_OP_NFSIN						0x012F
#define	JIT_OP_NFSINH						0x0130
#define	JIT_OP_NFSQRT						0x0131
#define	JIT_OP_NFTAN						0x0132
#define	JIT_OP_NFTANH						0x0133
#define	JIT_OP_NFTRUNC						0x0134
#define	JIT_OP_IABS						0x0135
#define	JIT_OP_LABS						0x0136
#define	JIT_OP_FABS						0x0137
#define	JIT_OP_DABS						0x0138
#define	JIT_OP_NFABS						0x0139
#define	JIT_OP_IMIN						0x013A
#define	JIT_OP_IMIN_UN						0x013B
#define	JIT_OP_LMIN						0x013C
#define	JIT_OP_LMIN_UN						0x013D
#define	JIT_OP_FMIN						0x013E
#define	JIT_OP_DMIN						0x013F
#define	JIT_OP_NFMIN						0x0140
#define	JIT_OP_IMAX						0x0141
#define	JIT_OP_IMAX_UN						0x0142
#define	JIT_OP_LMAX						0x0143
#define	JIT_OP_LMAX_UN						0x0144
#define	JIT_OP_FMAX						0x0145
#define	JIT_OP_DMAX						0x0146
#define	JIT_OP_NFMAX						0x0147
#define	JIT_OP_ISIGN						0x0148
#define	JIT_OP_LSIGN						0x0149
#define	JIT_OP_FSIGN						0x014A
#define	JIT_OP_DSIGN						0x014B
#define	JIT_OP_NFSIGN						0x014C
#define	JIT_OP_CHECK_NULL					0x014D
#define	JIT_OP_CALL						0x014E
#define	JIT_OP_CALL_TAIL					0x014F
#define	JIT_OP_CALL_INDIRECT					0x0150
#define	JIT_OP_CALL_INDIRECT_TAIL				0x0151
#define	JIT_OP_CALL_VTABLE_PTR					0x0152
#define	JIT_OP_CALL_VTABLE_PTR_TAIL				0x0153
#define	JIT_OP_CALL_EXTERNAL					0x0154
#define	JIT_OP_CALL_EXTERNAL_TAIL				0x0155
#define	JIT_OP_RETURN						0x0156
#define	JIT_OP_RETURN_INT					0x0157
#define	JIT_OP_RETURN_LONG					0x0158
#define	JIT_OP_RETURN_FLOAT32					0x0159
#define	JIT_OP_RETURN_FLOAT64					0x015A
#define	JIT_OP_RETURN_NFLOAT					0x015B
#define	JIT_OP_RETURN_SMALL_STRUCT				0x015C
#define	JIT_OP_SETUP_FOR_NESTED					0x015D
#define	JIT_OP_SETUP_FOR_SIBLING				0x015E
#define	JIT_OP_IMPORT						0x015F
#define	JIT_OP_THROW						0x0160
#define	JIT_OP_RETHROW						0x0161
#define	JIT_OP_LOAD_PC						0x0162
#define	JIT_OP_LOAD_EXCEPTION_PC				0x0163
#define	JIT_OP_ENTER_FINALLY					0x0164
#define	JIT_OP_LEAVE_FINALLY					0x0165
#define	JIT_OP_CALL_FINALLY					0x0166
#define	JIT_OP_ENTER_FILTER					0x0167
#define	JIT_OP_LEAVE_FILTER					0x0168
#define	JIT_OP_CALL_FILTER					0x0169
#define	JIT_OP_CALL_FILTER_RETURN				0x016A
#define	JIT_OP_ADDRESS_OF_LABEL					0x016B
#define	JIT_OP_COPY_LOAD_SBYTE					0x016C
#define	JIT_OP_COPY_LOAD_UBYTE					0x016D
#define	JIT_OP_COPY_LOAD_SHORT					0x016E
#define	JIT_OP_COPY_LOAD_USHORT					0x016F
#define	JIT_OP_COPY_INT						0x0170
#define	JIT_OP_COPY_LONG					0x0171
#define	JIT_OP_COPY_FLOAT32					0x0172
#define	JIT_OP_COPY_FLOAT64					0x0173
#define	JIT_OP_COPY_NFLOAT					0x0174
#define	JIT_OP_COPY_STRUCT					0x0175
#define	JIT_OP_COPY_STORE_BYTE					0x0176
#define	JIT_OP_COPY_STORE_SHORT					0x0177
#define	JIT_OP_ADDRESS_OF					0x0178
#define	JIT_OP_INCOMING_REG					0x0179
#define	JIT_OP_INCOMING_FRAME_POSN				0x017A
#define	JIT_OP_OUTGOING_REG					0x017B
#define	JIT_OP_OUTGOING_FRAME_POSN				0x017C
#define	JIT_OP_RETURN_REG					0x017D
#define	JIT_OP_PUSH_INT						0x017E
#define	JIT_OP_PUSH_LONG					0x017F
#define	JIT_OP_PUSH_FLOAT32					0x0180
#define	JIT_OP_PUSH_FLOAT64					0x0181
#define	JIT_OP_PUSH_NFLOAT					0x0182
#define	JIT_OP_PUSH_STRUCT					0x0183
#define	JIT_OP_POP_STACK					0x0184
#define	JIT_OP_FLUSH_SMALL_STRUCT				0x0185
#define	JIT_OP_SET_PARAM_INT					0x0186
#define	JIT_OP_SET_PARAM_LONG					0x0187
#define	JIT_OP_SET_PARAM_FLOAT32				0x0188
#define	JIT_OP_SET_PARAM_FLOAT64				0x0189
#define	JIT_OP_SET_PARAM_NFLOAT					0x018A
#define	JIT_OP_SET_PARAM_STRUCT					0x018B
#define	JIT_OP_PUSH_RETURN_AREA_PTR				0x018C
#define	JIT_OP_LOAD_RELATIVE_SBYTE				0x018D
#define	JIT_OP_LOAD_RELATIVE_UBYTE				0x018E
#define	JIT_OP_LOAD_RELATIVE_SHORT				0x018F
#define	JIT_OP_LOAD_RELATIVE_USHORT				0x0190
#define	JIT_OP_LOAD_RELATIVE_INT				0x0191
#define	JIT_OP_LOAD_RELATIVE_LONG				0x0192
#define	JIT_OP_LOAD_RELATIVE_FLOAT32				0x0193
#define	JIT_OP_LOAD_RELATIVE_FLOAT64				0x0194
#define	JIT_OP_LOAD_RELATIVE_NFLOAT				0x0195
#define	JIT_OP_LOAD_RELATIVE_STRUCT				0x0196
#define	JIT_OP_STORE_RELATIVE_BYTE				0x0197
#define	JIT_OP_STORE_RELATIVE_SHORT				0x0198
#define	JIT_OP_STORE_RELATIVE_INT				0x0199
#define	JIT_OP_STORE_RELATIVE_LONG				0x019A
#define	JIT_OP_STORE_RELATIVE_FLOAT32				0x019B
#define	JIT_OP_STORE_RELATIVE_FLOAT64				0x019C
#define	JIT_OP_STORE_RELATIVE_NFLOAT				0x019D
#define	JIT_OP_STORE_RELATIVE_STRUCT				0x019E
#define	JIT_OP_ADD_RELATIVE					0x019F
#define	JIT_OP_LOAD_ELEMENT_SBYTE				0x01A0
#define	JIT_OP_LOAD_ELEMENT_UBYTE				0x01A1
#define	JIT_OP_LOAD_ELEMENT_SHORT				0x01A2
#define	JIT_OP_LOAD_ELEMENT_USHORT				0x01A3
#define	JIT_OP_LOAD_ELEMENT_INT					0x01A4
#define	JIT_OP_LOAD_ELEMENT_LONG				0x01A5
#define	JIT_OP_LOAD_ELEMENT_FLOAT32				0x01A6
#define	JIT_OP_LOAD_ELEMENT_FLOAT64				0x01A7
#define	JIT_OP_LOAD_ELEMENT_NFLOAT				0x01A8
#define	JIT_OP_STORE_ELEMENT_BYTE				0x01A9
#define	JIT_OP_STORE_ELEMENT_SHORT				0x01AA
#define	JIT_OP_STORE_ELEMENT_INT				0x01AB
#define	JIT_OP_STORE_ELEMENT_LONG				0x01AC
#define	JIT_OP_STORE_ELEMENT_FLOAT32				0x01AD
#define	JIT_OP_STORE_ELEMENT_FLOAT64				0x01AE
#define	JIT_OP_STORE_ELEMENT_NFLOAT				0x01AF
#define	JIT_OP_MEMCPY						0x01B0
#define	JIT_OP_MEMMOVE						0x01B1
#define	JIT_OP_MEMSET						0x01B2
#define	JIT_OP_ALLOCA						0x01B3
#define	JIT_OP_MARK_OFFSET					0x01B4
#define	JIT_OP_MARK_BREAKPOINT					0x01B5
#define	JIT_OP_JUMP_TABLE					0x01B6
#define	JIT_OP_NUM_OPCODES					0x01B7

/*
 * Opcode information.
 */
typedef struct jit_opcode_info jit_opcode_info_t;
struct jit_opcode_info
{
	const char *name;
	int			flags;
};
#define	JIT_OPCODE_DEST_MASK			0x0000000F
#define	JIT_OPCODE_DEST_EMPTY			0x00000000
#define	JIT_OPCODE_DEST_INT				0x00000001
#define	JIT_OPCODE_DEST_LONG			0x00000002
#define	JIT_OPCODE_DEST_FLOAT32			0x00000003
#define	JIT_OPCODE_DEST_FLOAT64			0x00000004
#define	JIT_OPCODE_DEST_NFLOAT			0x00000005
#define	JIT_OPCODE_DEST_ANY				0x00000006
#define	JIT_OPCODE_SRC1_MASK			0x000000F0
#define	JIT_OPCODE_SRC1_EMPTY			0x00000000
#define	JIT_OPCODE_SRC1_INT				0x00000010
#define	JIT_OPCODE_SRC1_LONG			0x00000020
#define	JIT_OPCODE_SRC1_FLOAT32			0x00000030
#define	JIT_OPCODE_SRC1_FLOAT64			0x00000040
#define	JIT_OPCODE_SRC1_NFLOAT			0x00000050
#define	JIT_OPCODE_SRC1_ANY				0x00000060
#define	JIT_OPCODE_SRC2_MASK			0x00000F00
#define	JIT_OPCODE_SRC2_EMPTY			0x00000000
#define	JIT_OPCODE_SRC2_INT				0x00000100
#define	JIT_OPCODE_SRC2_LONG			0x00000200
#define	JIT_OPCODE_SRC2_FLOAT32			0x00000300
#define	JIT_OPCODE_SRC2_FLOAT64			0x00000400
#define	JIT_OPCODE_SRC2_NFLOAT			0x00000500
#define	JIT_OPCODE_SRC2_ANY				0x00000600
#define	JIT_OPCODE_IS_BRANCH			0x00001000
#define	JIT_OPCODE_IS_CALL				0x00002000
#define	JIT_OPCODE_IS_CALL_EXTERNAL		0x00004000
#define	JIT_OPCODE_IS_REG				0x00008000
#define	JIT_OPCODE_IS_ADDROF_LABEL		0x00010000
#define JIT_OPCODE_IS_JUMP_TABLE		0x00020000
#define	JIT_OPCODE_OPER_MASK			0x01F00000
#define	JIT_OPCODE_OPER_NONE			0x00000000
#define	JIT_OPCODE_OPER_ADD				0x00100000
#define	JIT_OPCODE_OPER_SUB				0x00200000
#define	JIT_OPCODE_OPER_MUL				0x00300000
#define	JIT_OPCODE_OPER_DIV				0x00400000
#define	JIT_OPCODE_OPER_REM				0x00500000
#define	JIT_OPCODE_OPER_NEG				0x00600000
#define	JIT_OPCODE_OPER_AND				0x00700000
#define	JIT_OPCODE_OPER_OR				0x00800000
#define	JIT_OPCODE_OPER_XOR				0x00900000
#define	JIT_OPCODE_OPER_NOT				0x00A00000
#define	JIT_OPCODE_OPER_EQ				0x00B00000
#define	JIT_OPCODE_OPER_NE				0x00C00000
#define	JIT_OPCODE_OPER_LT				0x00D00000
#define	JIT_OPCODE_OPER_LE				0x00E00000
#define	JIT_OPCODE_OPER_GT				0x00F00000
#define	JIT_OPCODE_OPER_GE				0x01000000
#define	JIT_OPCODE_OPER_SHL				0x01100000
#define	JIT_OPCODE_OPER_SHR				0x01200000
#define	JIT_OPCODE_OPER_SHR_UN			0x01300000
#define	JIT_OPCODE_OPER_COPY			0x01400000
#define	JIT_OPCODE_OPER_ADDRESS_OF		0x01500000
#ifdef JIT_NATIVE_INT32
#define	JIT_OPCODE_DEST_PTR				JIT_OPCODE_DEST_INT
#define	JIT_OPCODE_SRC1_PTR				JIT_OPCODE_SRC1_INT
#define	JIT_OPCODE_SRC2_PTR				JIT_OPCODE_SRC2_INT
#else
#define	JIT_OPCODE_DEST_PTR				JIT_OPCODE_DEST_LONG
#define	JIT_OPCODE_SRC1_PTR				JIT_OPCODE_SRC1_LONG
#define	JIT_OPCODE_SRC2_PTR				JIT_OPCODE_SRC2_LONG
#endif
JIT_EXPORT_DATA jit_opcode_info_t const jit_opcodes[JIT_OP_NUM_OPCODES];

#include "jit/jit-opcode-compat.h"

#ifdef	__cplusplus
};
#endif

#endif /* _JIT_OPCODE_H */
