/* Copyright (c) 2009, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#include "mt9t013.h"
#include <linux/kernel.h>

struct reg_struct mt9t013_reg_pat[2] = {
	{/* Preview 2x2 binning 20fps, pclk MHz, MCLK 24MHz */
	 /* vt_pix_clk_div:REG=0x0300 update get_snapshot_fps
	  * if this change */
	10,

	 /* vt_sys_clk_div: REG=0x0302  update get_snapshot_fps
	  * if this change */
	 1,

	 /* pre_pll_clk_div REG=0x0304  update get_snapshot_fps
	  * if this change */
	3,

	 /* pll_multiplier  REG=0x0306 60 for 30fps preview, 40
	  * for 20fps preview
	  * 46 for 30fps preview, try 47/48 to increase further */
	80,

	 /* op_pix_clk_div        REG=0x0308 */
	10,

	 /* op_sys_clk_div        REG=0x030A */
	 1,

	 /* scale_m       REG=0x0404 */
	 16,

	 /* row_speed     REG=0x3016 */
	 0x0111,

	 /* x_addr_start  REG=0x3004 */
	 8,

	 /* x_addr_end    REG=0x3008 */
	2073,	/*2053,*/

	 /* y_addr_start  REG=0x3002 */
	 8,

	 /* y_addr_end    REG=0x3006 */
	1557,/*1556,*/

	 /* read_mode     REG=0x3040 */
	 0x046C,

	 /* x_output_size REG=0x034C */
	1048,	/*1024,*/

	 /* y_output_size REG=0x034E */
	776,	/*768,*/

	 /* line_length_pck    REG=0x300C */
	3540,

	 /* frame_length_lines REG=0x300A */
	861,

	 /* coarse_int_time REG=0x3012 */
	 16,

	 /* fine_int_time   REG=0x3014 */
	1461
	},
	{ /*Snapshot */
	 /* vt_pix_clk_div  REG=0x0300 update get_snapshot_fps
	  * if this change */
	10,

	 /* vt_sys_clk_div  REG=0x0302 update get_snapshot_fps
	  * if this change */
	 1,

	 /* pre_pll_clk_div REG=0x0304 update get_snapshot_fps
	  * if this change */
	3,

	 /* pll_multiplier REG=0x0306 50 for 15fps snapshot,
	  * 40 for 10fps snapshot
	  * 46 for 30fps snapshot, try 47/48 to increase further */
	80,

	 /* op_pix_clk_div        REG=0x0308 */
	10,

	 /* op_sys_clk_div        REG=0x030A */
	 1,

	 /* scale_m       REG=0x0404 */
	 16,

	 /* row_speed     REG=0x3016 */
	 0x0111,

	 /* x_addr_start  REG=0x3004 */
	 8,

	 /* x_addr_end    REG=0x3008 */
	2073,

	 /* y_addr_start  REG=0x3002 */
	 8,

	 /* y_addr_end    REG=0x3006 */
	 1551,

	 /* read_mode     REG=0x3040 */
	 0x0024,

	 /* x_output_size REG=0x034C */
	 2064,

	 /* y_output_size REG=0x034E */
	 1544,

	 /* line_length_pck REG=0x300C */
	4800,

	 /* frame_length_lines    REG=0x300A */
	 1629,

	 /* coarse_int_time REG=0x3012 */
	 16,

	 /* fine_int_time REG=0x3014   */
	733
	}
};

struct mt9t013_i2c_reg_conf const mt9t013_test_tbl[] = {
	{0x3044, 0x0544 & 0xFBFF},
	{0x30CA, 0x0004 | 0x0001},
	{0x30D4, 0x9020 & 0x7FFF},
	{0x31E0, 0x0003 & 0xFFFE},
	{0x3180, 0x91FF & 0x7FFF},
	{0x301A, (0x10CC | 0x8000) & 0xFFF7},
	{0x301E, 0x0000},
	{0x3780, 0x0000},
};

/* [Lens shading 85 Percent TL84] */
struct mt9t013_i2c_reg_conf const mt9t013_lc_tbl[] = {
	{0x360A, 0x0130},	/* P_RD_P0Q0 */
	{0x360C, 0xADED},	/* P_RD_P0Q1 */
	{0x360E, 0x50D1},	/* P_RD_P0Q2 */
	{0x3610, 0x8FAD},	/* P_RD_P0Q3 */
	{0x3612, 0xCE31},	/* P_RD_P0Q4 */
	{0x364A, 0x38CB},	/* P_RD_P1Q0 */
	{0x364C, 0x8BCD},	/* P_RD_P1Q1 */
	{0x364E, 0x19CF},	/* P_RD_P1Q2 */
	{0x3650, 0x43EC},	/* P_RD_P1Q3 */
	{0x3652, 0xB3F1},	/* P_RD_P1Q4 */
	{0x368A, 0x3D31},	/* P_RD_P2Q0 */
	{0x368C, 0x8DF0},	/* P_RD_P2Q1 */
	{0x368E, 0xB033},	/* P_RD_P2Q2 */
	{0x3690, 0x61D2},	/* P_RD_P2Q3 */
	{0x3692, 0x4B74},	/* P_RD_P2Q4 */
	{0x36CA, 0x71ED},	/* P_RD_P3Q0 */
	{0x36CC, 0xE66B},	/* P_RD_P3Q1 */
	{0x36CE, 0xF392},	/* P_RD_P3Q2 */
	{0x36D0, 0x1E51},	/* P_RD_P3Q3 */
	{0x36D2, 0x6D94},	/* P_RD_P3Q4 */
	{0x370A, 0xA672},	/* P_RD_P4Q0 */
	{0x370C, 0x1E92},	/* P_RD_P4Q1 */
	{0x370E, 0x2315},	/* P_RD_P4Q2 */
	{0x3710, 0x8675},	/* P_RD_P4Q3 */
	{0x3712, 0x9C56},	/* P_RD_P4Q4 */
	{0x3600, 0x0190},	/* P_GR_P0Q0 */
	{0x3602, 0x02EE},	/* P_GR_P0Q1 */
	{0x3604, 0x4B31},	/* P_GR_P0Q2 */
	{0x3606, 0x1328},	/* P_GR_P0Q3 */
	{0x3608, 0x8292},	/* P_GR_P0Q4 */
	{0x3640, 0x262A},	/* P_GR_P1Q0 */
	{0x3642, 0x212B},	/* P_GR_P1Q1 */
	{0x3644, 0x4D8E},	/* P_GR_P1Q2 */
	{0x3646, 0x8F8E},	/* P_GR_P1Q3 */
	{0x3648, 0xB431},	/* P_GR_P1Q4 */
	{0x3680, 0x27B1},	/* P_GR_P2Q0 */
	{0x3682, 0x2C2C},	/* P_GR_P2Q1 */
	{0x3684, 0xE113},	/* P_GR_P2Q2 */
	{0x3686, 0x19F1},	/* P_GR_P2Q3 */
	{0x3688, 0x1855},	/* P_GR_P2Q4 */
	{0x36C0, 0x77EB},	/* P_GR_P3Q0 */
	{0x36C2, 0x7FAA},	/* P_GR_P3Q1 */
	{0x36C4, 0x8573},	/* P_GR_P3Q2 */
	{0x36C6, 0x828F},	/* P_GR_P3Q3 */
	{0x36C8, 0x20B5},	/* P_GR_P3Q4 */
	{0x3700, 0xC5B2},	/* P_GR_P4Q0 */
	{0x3702, 0x02D0},	/* P_GR_P4Q1 */
	{0x3704, 0x3535},	/* P_GR_P4Q2 */
	{0x3706, 0xD874},	/* P_GR_P4Q3 */
	{0x3708, 0x8216},	/* P_GR_P4Q4 */
	{0x3614, 0x0190},	/* P_BL_P0Q0 */
	{0x3616, 0x73ED},	/* P_BL_P0Q1 */
	{0x3618, 0x2551},	/* P_BL_P0Q2 */
	{0x361A, 0x840E},	/* P_BL_P0Q3 */
	{0x361C, 0xDFD1},	/* P_BL_P0Q4 */
	{0x3654, 0x80AD},	/* P_BL_P1Q0 */
	{0x3656, 0xD18D},	/* P_BL_P1Q1 */
	{0x3658, 0x7BCE},	/* P_BL_P1Q2 */
	{0x365A, 0x666C},	/* P_BL_P1Q3 */
	{0x365C, 0xC430},	/* P_BL_P1Q4 */
	{0x3694, 0x1C11},	/* P_BL_P2Q0 */
	{0x3696, 0xA46E},	/* P_BL_P2Q1 */
	{0x3698, 0x95D4},	/* P_BL_P2Q2 */
	{0x369A, 0x1072},	/* P_BL_P2Q3 */
	{0x369C, 0x6715},	/* P_BL_P2Q4 */
	{0x36D4, 0x02AD},	/* P_BL_P3Q0 */
	{0x36D6, 0x048E},	/* P_BL_P3Q1 */
	{0x36D8, 0xCEF2},	/* P_BL_P3Q2 */
	{0x36DA, 0x2CB0},	/* P_BL_P3Q3 */
	{0x36DC, 0x3054},	/* P_BL_P3Q4 */
	{0x3714, 0xB852},	/* P_BL_P4Q0 */
	{0x3716, 0x0710},	/* P_BL_P4Q1 */
	{0x3718, 0x1656},	/* P_BL_P4Q2 */
	{0x371A, 0xB7B4},	/* P_BL_P4Q3 */
	{0x371C, 0xA577},	/* P_BL_P4Q4 */
	{0x361E, 0x0290},	/* P_GB_P0Q0 */
	{0x3620, 0x890E},	/* P_GB_P0Q1 */
	{0x3622, 0x4731},	/* P_GB_P0Q2 */
	{0x3624, 0x1EAB},	/* P_GB_P0Q3 */
	{0x3626, 0x8712},	/* P_GB_P0Q4 */
	{0x365E, 0xCBEC},	/* P_GB_P1Q0 */
	{0x3660, 0x154D},	/* P_GB_P1Q1 */
	{0x3662, 0x3EEF},	/* P_GB_P1Q2 */
	{0x3664, 0xD8CD},	/* P_GB_P1Q3 */
	{0x3666, 0xB351},	/* P_GB_P1Q4 */
	{0x369E, 0x2B91},	/* P_GB_P2Q0 */
	{0x36A0, 0xF34F},	/* P_GB_P2Q1 */
	{0x36A2, 0xF053},	/* P_GB_P2Q2 */
	{0x36A4, 0x4BD2},	/* P_GB_P2Q3 */
	{0x36A6, 0x1795},	/* P_GB_P2Q4 */
	{0x36DE, 0x0E2B},	/* P_GB_P3Q0 */
	{0x36E0, 0x6DAB},	/* P_GB_P3Q1 */
	{0x36E2, 0xC8F2},	/* P_GB_P3Q2 */
	{0x36E4, 0xF68E},	/* P_GB_P3Q3 */
	{0x36E6, 0x4294},	/* P_GB_P3Q4 */
	{0x371E, 0xD0B2},	/* P_GB_P4Q0 */
	{0x3720, 0x1652},	/* P_GB_P4Q1 */
	{0x3722, 0x36B5},	/* P_GB_P4Q2 */
	{0x3724, 0x9655},	/* P_GB_P4Q3 */
	{0x3726, 0xE454},	/* P_GB_P4Q4 */
	{0x3782, 0x03F0},	/* POLY_ORIGIN_C */
	{0x3784, 0x0300},	/* POLY_ORIGIN_R  */
	{0x3780, 0x8000}	/* POLY_SC_ENABLE */
};

struct mt9t013_reg mt9t013_regs = {
	.reg_pat = &mt9t013_reg_pat[0],
	.reg_pat_size = ARRAY_SIZE(mt9t013_reg_pat),
	.ttbl = &mt9t013_test_tbl[0],
	.ttbl_size = ARRAY_SIZE(mt9t013_test_tbl),
	.lctbl = &mt9t013_lc_tbl[0],
	.lctbl_size = ARRAY_SIZE(mt9t013_lc_tbl),
	.rftbl = &mt9t013_lc_tbl[0],
	.rftbl_size = ARRAY_SIZE(mt9t013_lc_tbl)
};
