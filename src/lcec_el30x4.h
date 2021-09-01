//
//    Copyright (C) 2019 Scott Laird <laird@google.com>
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
//
#ifndef _LCEC_EL30x4_H_
#define _LCEC_EL30x4_H_

#include "lcec.h"

#define LCEC_EL30x4_VID LCEC_BECKHOFF_VID
#define LCEC_EL3004_PID 0x0bbc3052
#define LCEC_EL3044_PID 0x0be43052
#define LCEC_EL3054_PID 0x0bee3052
#define LCEC_EL3064_PID 0x0bf83052
#define LCEC_EL30x4_CHANS 4
#define LCEC_EL30x4_PDOS  (LCEC_EL30x4_CHANS * 5)

int lcec_el30x4_init(int comp_id, struct lcec_slave *slave, ec_pdo_entry_reg_t *pdo_entry_regs);

#endif

