//
// Created by chad on 2021-06-04.
//

/*
 *  EL34xx 3 Phase power monitoring cards
 */

#include "lcec.h"
#include "lcec_el34xx.h"


typedef struct {
    hal_bit_t *volt_sign;
    hal_bit_t *volt_over;
    hal_bit_t *curr_over;
    hal_bit_t *volt_true;
    hal_bit_t *curr_true;
    hal_bit_t *volt_warn;
    hal_bit_t *volt_err;
    hal_bit_t *curr_warn;
    hal_bit_t *curr_err;
    hal_u32_t *voltage;
    hal_u32_t *current;
    hal_u32_t *active_pwr;
    hal_u32_t *apparent_pwr;
    hal_u32_t *reactive_pwr;
    hal_u32_t *pwr_factor;

    unsigned int sign_pdo_os;
    unsigned int sign_pdo_bp;
    unsigned int volt_over_pdo_os;
    unsigned int volt_over_pdo_bp;
    unsigned int curr_over_pdo_os;
    unsigned int curr_over_pdo_bp;
    unsigned int volt_true_pdo_os;
    unsigned int volt_true_pdo_bp;
    unsigned int curr_true_pdo_os;
    unsigned int curr_true_pdo_bp;
    unsigned int volt_warn_pdo_os;
    unsigned int volt_warn_pdo_bp;
    unsigned int curr_warn_pdo_os;
    unsigned int curr_warn_pdo_bp;
    unsigned int volt_err_pdo_os;
    unsigned int volt_err_pdo_bp;
    unsigned int curr_err_pdo_os;
    unsigned int curr_err_pdo_bp;
    unsigned int voltage_pdo_os;
    unsigned int voltage_pdo_bp;
    unsigned int current_pdo_os;
    unsigned int current_pdo_bp;
    unsigned int active_pwr_pdo_os;
    unsigned int active_pwr_pdo_bp;
    unsigned int apparent_pwr_pdo_os;
    unsigned int apparent_pwr_pdo_bp;
    unsigned int reactive_pwr_pdo_os;
    unsigned int reactive_pwr_pdo_bp;
    unsigned int pwr_factor_pdo_os;
    unsigned int pwr_factor_pdo_bp;
} lcec_el34xx_chan_t;


static const lcec_pindesc_t slave_pins[] = {
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_chan_t, volt_sign),    "%s.%s.%s.L%d-voltage-sign"       },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_chan_t, volt_over),    "%s.%s.%s.L%d-over-voltage"       },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_chan_t, curr_over),    "%s.%s.%s.L%d-over-current"       },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_chan_t, volt_true),    "%s.%s.%s.L%d-inaccurate-voltage" },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_chan_t, curr_true),    "%s.%s.%s.L%d-inaccurate-current" },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_chan_t, volt_warn),    "%s.%s.%s.L%d-voltage-warn"       },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_chan_t, curr_warn),    "%s.%s.%s.L%d-current-warn"       },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_chan_t, volt_err),     "%s.%s.%s.L%d-voltage-error"      },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_chan_t, curr_err),     "%s.%s.%s.L%d-current-error"      },
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_chan_t, voltage),      "%s.%s.%s.L%d-voltage"            },
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_chan_t, current),      "%s.%s.%s.L%d-current"            },
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_chan_t, active_pwr),   "%s.%s.%s.L%d-active-power"       },
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_chan_t, apparent_pwr), "%s.%s.%s.L%d-apparent-power"     },
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_chan_t, reactive_pwr), "%s.%s.%s.L%d-reactive-power"     },
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_chan_t, pwr_factor),   "%s.%s.%s.L%d-power-factor"       },
  { HAL_TYPE_UNSPECIFIED, HAL_DIR_UNSPECIFIED, -1, NULL }
};

typedef struct{
    hal_bit_t *sys_state;
    hal_bit_t *grid_dir;
    hal_bit_t *freq_warn;
    hal_bit_t *freq_err;
    hal_bit_t *neutral_warn;
    hal_bit_t *neutral_err;
    hal_bit_t *active_pwr_warn;
    hal_bit_t *active_pwr_err;
    hal_bit_t *apparent_pwr_warn;
    hal_bit_t *apparent_pwr_err;
    hal_bit_t *poor_pwr_warn;
    hal_bit_t *poor_pwr_err;
    hal_u32_t *pwr_quality;
    hal_u32_t *frequency;
    hal_u32_t *pwr_factor;
    hal_u32_t *neutral_current;
    hal_u32_t *active_pwr;
//    hal_u64_t *active_energy;
//    hal_u64_t *active_pos_energy;
//    hal_u64_t *active_neg_energy;
    hal_u32_t *L1_L2_voltage;
    hal_u32_t *L2_L3_voltage;
    hal_u32_t *L3_L1_voltage;

    unsigned int state_pdo_os;
    unsigned int state_pdo_bp;
    unsigned int grid_pdo_os;
    unsigned int grid_pdo_bp;
    unsigned int freq_warn_pdo_os;
    unsigned int freq_warn_pdo_bp;
    unsigned int freq_err_pdo_os;
    unsigned int freq_err_pdo_bp;
    unsigned int neutral_warn_pdo_os;
    unsigned int neutral_warn_pdo_bp;
    unsigned int neutral_err_pdo_os;
    unsigned int neutral_err_pdo_bp;
    unsigned int active_warn_pdo_os;
    unsigned int active_warn_pdo_bp;
    unsigned int active_err_pdo_os;
    unsigned int active_err_pdo_bp;
    unsigned int apparent_warn_pdo_os;
    unsigned int apparent_warn_pdo_bp;
    unsigned int apparent_err_pdo_os;
    unsigned int apparent_err_pdo_bp;
    unsigned int poor_pwr_warn_pdo_os;
    unsigned int poor_pwr_warn_pdo_bp;
    unsigned int poor_pwr_err_pdo_os;
    unsigned int poor_pwr_err_pdo_bp;
    unsigned int pwr_quality_pdo_os;
    unsigned int pwr_quality_pdo_bp;
    unsigned int frequency_pdo_os;
    unsigned int frequency_pdo_bp;
    unsigned int pwr_factor_pdo_os;
    unsigned int pwr_factor_pdo_bp;
    unsigned int neutral_current_pdo_os;
    unsigned int neutral_current_pdo_bp;
    unsigned int active_pwr_pdo_os;
    unsigned int active_pwr_pdo_bp;
//    unsigned int active_energy_pdo_os;
//    unsigned int active_energy_pdo_bp;
//    unsigned int active_pos_energy_pdo_os;
//    unsigned int active_pos_energy_pdo_bp;
//    unsigned int active_neg_energy_pdo_os;
//    unsigned int active_neg_energy_pdo_bp;
    unsigned int L1_L2_voltage_pdo_os;
    unsigned int L1_L2_voltage_pdo_bp;
    unsigned int L2_L3_voltage_pdo_os;
    unsigned int L2_L3_voltage_pdo_bp;
    unsigned int L3_L1_voltage_pdo_os;
    unsigned int L3_L1_voltage_pdo_bp;

} lcec_el34xx_stat_chan_t;

typedef struct {
    lcec_el34xx_chan_t chans[LCEC_EL34xx_CHANS];
    lcec_el34xx_stat_chan_t stat;
} lcec_el34xx_data_t;


static const lcec_pindesc_t stat_pins[] = {
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, sys_state          ), "%s.%s.%s.system-state" },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, grid_dir           ), "%s.%s.%s.grid-direction" },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, freq_warn          ), "%s.%s.%s.frequency-warning" },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, freq_err           ), "%s.%s.%s.frequency-error" },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, neutral_warn       ), "%s.%s.%s.neutral-warning" },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, neutral_err        ), "%s.%s.%s.neutral-error" },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, active_pwr_warn    ), "%s.%s.%s.active-pwr-warning" },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, active_pwr_err     ), "%s.%s.%s.active-pwr-error" },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, apparent_pwr_warn  ), "%s.%s.%s.apparent-pwr-warning" },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, apparent_pwr_err   ), "%s.%s.%s.apparent-pwr-error" },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, poor_pwr_warn      ), "%s.%s.%s.pwr-quality-warning" },
  { HAL_BIT,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, poor_pwr_err       ), "%s.%s.%s.pwr-quality-error" },
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, pwr_quality        ), "%s.%s.%s.pwr-quality-factor"},
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, frequency          ), "%s.%s.%s.frequency"},
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, pwr_factor         ), "%s.%s.%s.pwr-factor"},
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, neutral_current    ), "%s.%s.%s.neutral-current"},
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, active_pwr         ), "%s.%s.%s.active-pwr"},
//  { HAL_U64,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, active_energy      ), "%s.%s.%s.active-energy"},
//  { HAL_U64,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, active_pos_energy  ), "%s.%s.%s.active-pos-energy"},
//  { HAL_U64,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, active_neg_energy  ), "%s.%s.%s.active-neg-energy"},
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, L1_L2_voltage      ), "%s.%s.%s.L1-L2-voltage"},
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, L2_L3_voltage      ), "%s.%s.%s.L2-L3-voltage"},
  { HAL_U32,   HAL_OUT, offsetof(lcec_el34xx_stat_chan_t, L3_L1_voltage      ), "%s.%s.%s.L3-L1-voltage"},
  { HAL_TYPE_UNSPECIFIED, HAL_DIR_UNSPECIFIED, -1, NULL }
};

void lcec_el34xx_read(struct lcec_slave *slave, long period);


int lcec_el34xx_init(int comp_id, struct lcec_slave *slave, ec_pdo_entry_reg_t *pdo_entry_regs) {
  lcec_master_t *master = slave->master;
  lcec_el34xx_data_t *hal_data;
  lcec_el34xx_chan_t *chan;
  lcec_el34xx_stat_chan_t *stat;
  int i;
  int err;

  // initialize callbacks
  slave->proc_read = lcec_el34xx_read;

  // alloc hal memory
  if ((hal_data = hal_malloc(sizeof(lcec_el34xx_data_t))) == NULL) {
    rtapi_print_msg(RTAPI_MSG_ERR, LCEC_MSG_PFX "hal_malloc() for slave %s.%s failed\n", master->name, slave->name);
    return -EIO;
  }
  memset(hal_data, 0, sizeof(lcec_el34xx_data_t));
  slave->hal_data = hal_data;

  // initialize pins

  for (i=0; i<LCEC_EL34xx_CHANS; i++) {
    chan = &hal_data->chans[i];

    // initialize POD entries
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6000 + (i <<  4), 0x01, &chan->sign_pdo_os, &chan->sign_pdo_bp);
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6000 + (i <<  4), 0x02, &chan->volt_over_pdo_os, &chan->volt_over_pdo_bp);
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6000 + (i <<  4), 0x03, &chan->curr_over_pdo_os, &chan->curr_over_pdo_bp);
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6000 + (i <<  4), 0x04, &chan->volt_true_pdo_os, &chan->volt_true_pdo_bp);
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6000 + (i <<  4), 0x05, &chan->curr_true_pdo_os, &chan->curr_true_pdo_bp);
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6000 + (i <<  4), 0x06, &chan->volt_warn_pdo_os, &chan->volt_warn_pdo_bp);
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6000 + (i <<  4), 0x07, &chan->volt_err_pdo_os, &chan->volt_err_pdo_bp);
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6000 + (i <<  4), 0x08, &chan->curr_warn_pdo_os, &chan->curr_warn_pdo_bp);
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6000 + (i <<  4), 0x09, &chan->curr_err_pdo_os, &chan->curr_err_pdo_bp);

    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6001 + (i <<  4), 0x11, &chan->voltage_pdo_os, &chan->voltage_pdo_bp);
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6001 + (i <<  4), 0x12, &chan->current_pdo_os, &chan->current_pdo_bp);
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6002 + (i <<  4), 0x11, &chan->active_pwr_pdo_os, &chan->active_pwr_pdo_bp);
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6002 + (i <<  4), 0x12, &chan->apparent_pwr_pdo_os, &chan->apparent_pwr_pdo_bp);
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6002 + (i <<  4), 0x13, &chan->reactive_pwr_pdo_os, &chan->reactive_pwr_pdo_bp);
    LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x6002 + (i <<  4), 0x14, &chan->pwr_factor_pdo_os, &chan->pwr_factor_pdo_bp);


    // export pins
    if ((err = lcec_pin_newf_list(chan, slave_pins, LCEC_MODULE_NAME, master->name, slave->name, i)) != 0) {
      return err;
    }

  }

  stat = &hal_data->stat;
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf600, 0x01, &stat->state_pdo_os,             &stat->state_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf600, 0x02, &stat->grid_pdo_os,              &stat->grid_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf600, 0x03, &stat->freq_warn_pdo_os,         &stat->freq_warn_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf600, 0x04, &stat->freq_err_pdo_os,          &stat->freq_err_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf600, 0x05, &stat->neutral_warn_pdo_os,      &stat->neutral_warn_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf600, 0x06, &stat->neutral_err_pdo_os,       &stat->neutral_err_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf600, 0x07, &stat->active_warn_pdo_os,       &stat->active_warn_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf600, 0x08, &stat->active_err_pdo_os,        &stat->active_err_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf600, 0x09, &stat->apparent_warn_pdo_os,     &stat->apparent_warn_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf600, 0x0a, &stat->apparent_err_pdo_os,      &stat->apparent_err_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf600, 0x0b, &stat->poor_pwr_warn_pdo_os,     &stat->poor_pwr_warn_pdo_os);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf600, 0x0c, &stat->poor_pwr_err_pdo_os,      &stat->poor_pwr_err_pdo_os);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf600, 0x11, &stat->pwr_quality_pdo_os,       &stat->pwr_quality_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf601, 0x11, &stat->frequency_pdo_os,         &stat->frequency_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf601, 0x12, &stat->pwr_factor_pdo_os,        &stat->pwr_factor_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf601, 0x13, &stat->neutral_current_pdo_os,   &stat->neutral_current_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf603, 0x11, &stat->active_pwr_pdo_os,        &stat->active_pwr_pdo_bp);
//  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf603, 0x12, &stat->active_energy_pdo_os,     &stat->active_energy_pdo_bp);
//  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf603, 0x13, &stat->active_pos_energy_pdo_os, &stat->active_pos_energy_pdo_bp);
//  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf603, 0x14, &stat->active_neg_energy_pdo_os, &stat->active_neg_energy_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf609, 0x11, &stat->L1_L2_voltage_pdo_os,     &stat->L1_L2_voltage_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf609, 0x12, &stat->L2_L3_voltage_pdo_os,     &stat->L2_L3_voltage_pdo_bp);
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0xf609, 0x13, &stat->L3_L1_voltage_pdo_os,     &stat->L3_L1_voltage_pdo_bp);


  // export stat pins
  if ((err = lcec_pin_newf_list(stat, stat_pins, LCEC_MODULE_NAME, master->name, slave->name, i)) != 0) {
    return err;
  }
  return 0;
}


void lcec_el34xx_read(struct lcec_slave *slave, long period) {
  lcec_master_t *master = slave->master;
  lcec_el34xx_data_t *hal_data = (lcec_el34xx_data_t *) slave->hal_data;
  uint8_t *pd = master->process_data;
  int i;
  lcec_el34xx_chan_t *chan;
  lcec_el34xx_stat_chan_t *stat;
  int32_t value = 0;

  // wait for slave to be operational
  if (!slave->state.operational) {
    return;
  }

  // check inputs
  for (i=0; i<LCEC_EL34xx_CHANS; i++) {
    chan = &hal_data->chans[i];

    // Update State Variables
    *(chan->volt_sign) = EC_READ_BIT(&pd[chan->sign_pdo_os]     , chan->sign_pdo_bp);
    *(chan->volt_over) = EC_READ_BIT(&pd[chan->volt_over_pdo_os], chan->volt_over_pdo_bp);
    *(chan->curr_over) = EC_READ_BIT(&pd[chan->curr_over_pdo_os], chan->curr_over_pdo_bp);
    *(chan->volt_true) = EC_READ_BIT(&pd[chan->volt_true_pdo_os], chan->volt_true_pdo_bp);
    *(chan->curr_true) = EC_READ_BIT(&pd[chan->curr_true_pdo_os], chan->curr_true_pdo_bp);
    *(chan->volt_warn) = EC_READ_BIT(&pd[chan->volt_warn_pdo_os], chan->volt_warn_pdo_bp);
    *(chan->curr_warn) = EC_READ_BIT(&pd[chan->curr_warn_pdo_os], chan->curr_warn_pdo_bp);
    *(chan->volt_err ) = EC_READ_BIT(&pd[chan->volt_err_pdo_os] , chan->volt_err_pdo_bp);
    *(chan->curr_err ) = EC_READ_BIT(&pd[chan->curr_err_pdo_os] , chan->curr_err_pdo_bp);

    // Update Values variables
    *(chan->voltage)      = EC_READ_U32(&pd[chan->voltage_pdo_os]);       //TODO Does this need to be converted??
    *(chan->current)      = EC_READ_U32(&pd[chan->current_pdo_os]);       //TODO Does this need to be converted??
    *(chan->active_pwr)   = EC_READ_U32(&pd[chan->active_pwr_pdo_os]);    //TODO Does this need to be converted??
    *(chan->apparent_pwr) = EC_READ_U32(&pd[chan->apparent_pwr_pdo_os]);  //TODO Does this need to be converted??
    *(chan->reactive_pwr) = EC_READ_U32(&pd[chan->reactive_pwr_pdo_os]);  //TODO Does this need to be converted??
    *(chan->pwr_factor)   = EC_READ_U32(&pd[chan->pwr_factor_pdo_os]);    //TODO Does this need to be converted??

  }


  //Check status
  stat = &hal_data->stat;
  *(stat->sys_state)         = EC_READ_BIT(&pd[stat->state_pdo_os],         stat->state_pdo_bp         );
  *(stat->grid_dir)          = EC_READ_BIT(&pd[stat->grid_pdo_os],          stat->grid_pdo_bp          );
  *(stat->freq_warn)         = EC_READ_BIT(&pd[stat->freq_warn_pdo_os],     stat->freq_warn_pdo_bp     );
  *(stat->freq_err)          = EC_READ_BIT(&pd[stat->freq_err_pdo_os],      stat->freq_err_pdo_bp      );
  *(stat->neutral_warn)      = EC_READ_BIT(&pd[stat->neutral_warn_pdo_os],  stat->neutral_warn_pdo_bp  );
  *(stat->neutral_err)       = EC_READ_BIT(&pd[stat->neutral_err_pdo_os],   stat->neutral_err_pdo_bp   );
  *(stat->active_pwr_warn)   = EC_READ_BIT(&pd[stat->active_warn_pdo_os],   stat->active_warn_pdo_bp   );
  *(stat->active_pwr_err)    = EC_READ_BIT(&pd[stat->active_err_pdo_os],    stat->active_err_pdo_bp    );
  *(stat->apparent_pwr_warn) = EC_READ_BIT(&pd[stat->apparent_warn_pdo_os], stat->apparent_warn_pdo_bp );
  *(stat->apparent_pwr_err)  = EC_READ_BIT(&pd[stat->apparent_err_pdo_os],  stat->apparent_err_pdo_bp  );
  *(stat->poor_pwr_warn)     = EC_READ_BIT(&pd[stat->poor_pwr_warn_pdo_os], stat->poor_pwr_warn_pdo_bp );
  *(stat->poor_pwr_err)      = EC_READ_BIT(&pd[stat->poor_pwr_err_pdo_os],  stat->poor_pwr_err_pdo_bp  );

  *(stat->pwr_quality)       = EC_READ_U32(&pd[stat->pwr_quality_pdo_os]);
  *(stat->frequency)         = EC_READ_U32(&pd[stat->frequency_pdo_os]);
  *(stat->pwr_factor)        = EC_READ_U32(&pd[stat->pwr_factor_pdo_os]);
  *(stat->neutral_current)   = EC_READ_U32(&pd[stat->neutral_current_pdo_os]);
  *(stat->active_pwr)        = EC_READ_U32(&pd[stat->active_pwr_pdo_os]);
//  *(stat->active_energy)     = EC_READ_U64(&pd[stat->active_energy_pdo_os]);
//  *(stat->active_pos_energy) = EC_READ_U64(&pd[stat->active_pos_energy_pdo_os]);
//  *(stat->active_neg_energy) = EC_READ_U64(&pd[stat->active_neg_energy_pdo_os]);
  *(stat->L1_L2_voltage)     = EC_READ_U32(&pd[stat->L1_L2_voltage_pdo_os]);
  *(stat->L2_L3_voltage)     = EC_READ_U32(&pd[stat->L2_L3_voltage_pdo_os]);
  *(stat->L3_L1_voltage)     = EC_READ_U32(&pd[stat->L3_L1_voltage_pdo_os]);

}