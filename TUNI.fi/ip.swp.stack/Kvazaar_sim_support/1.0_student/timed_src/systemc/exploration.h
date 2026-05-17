#ifndef EXPLORATION_H_
#define EXPLORATION_H_

// Data transfers
typedef enum {CONFIG=0,UNFILT1,UNFILT2,ORIG,LAMBDA,RESULT} data_transfers_t;
extern int data_amount[6]; //bytes
extern int data_transfers[6]; // number of transfers

// ARM exploration
#define ARM_STOCK_MHZ 925
//#define ARM_USED_CORES 1
//const int arm_overclock_mhz_c = 925;
#define ARM_USED_CORES 16
const int arm_overclock_mhz_c = 4250;

// Encoder simulation values
const int delay_c = 24700;
const double search_intra_rough_percentage_c = 0.5798;
const double rest_percentage_c = 0.4202; // (1-0.5798)

// HPS->FPGA->HPS simulation values
const double onchip_fpga_to_hps_ns_per_byte_c = ( 1 / ( ( 131.30 ) * 1024 * 1024 ) ) * 1000000000;
const double hps_to_onchip_fpga_ns_per_byte_c = ( 1 / ( ( 206.24 ) * 1024 * 1024 ) ) * 1000000000;
const double hps_ddr_to_fpga_ns_per_byte_c = ( 1 / ( ( 264.11 ) * 1024 * 1024 ) ) * 1000000000;

// Accelerator exploration
//#define NUMBER_OF_ACCS 1
//#define FPGA_FREQ_MHZ 90
#define NUMBER_OF_ACCS 16
#define FPGA_FREQ_MHZ 150
const int period_ns_c = 1000/FPGA_FREQ_MHZ;

#endif
