//
//    Copyright (C) 2011 Sascha Ittner <sascha.ittner@modusoft.de>
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
#ifndef _LCEC_EP23XX_H_
#define _LCEC_EP23XX_H_

#include "lcec.h"

#define LCEC_EP23xx_VID LCEC_BECKHOFF_VID

// Add additional EP23xx models here, as well as lcec_main.c, lcec_conf.c, and lcec_conf.h.
#define LCEC_EP2338_PID 0x09224052
#define LCEC_EP2349_PID 0x092d4052
#define LCEC_EP2316_PID 0x090C4052  // Untested, may not work.

#define LCEC_EP2338_PDOS 16  // Can be in or out on each port, so 2 PDOs per port.
#define LCEC_EP2349_PDOS 32  // Can be in or out on each port, so 2 PDOs per port.
#define LCEC_EP2316_PDOS 16  // Each port is fixed in or out, so 1 PDO per port.

int lcec_ep23xx_init(int comp_id, struct lcec_slave *slave, ec_pdo_entry_reg_t *pdo_entry_regs);

#endif

