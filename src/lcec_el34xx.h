//
// Created by chad on 2021-06-04.
//

/*
 *  EL34xx 3 Phase power monitoring cards
 */

#ifndef _LCEC_EL34XX_H
#define _LCEC_EL34XX_H

#include "lcec.h"

#define LCEC_EL34xx_VID LCEC_BECKHOFF_VID

//#define LCEC_EL3423_PID 0x0D5F3052
#define LCEC_EL3443_PID 0x0d733052
//#define LCEC_EL3446_PID 0x0D763052
//#define LCEC_EL3483_PID 0x0D9B3052

#define LCEC_EL3443_PDOS 64

#define LCEC_EL34xx_CHANS 3 // 3 Phase Power

int lcec_el34xx_init(int comp_id, struct lcec_slave *slave, ec_pdo_entry_reg_t *pdo_entry_regs);

#endif //_LCEC_EL34XX_H
