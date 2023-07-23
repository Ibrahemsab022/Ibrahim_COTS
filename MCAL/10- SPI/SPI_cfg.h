#ifndef SPI_CFG_H_
#define SPI_CFG_H_

/*Choose the SPI interrupt Initial state:
 * 									1- ENABLED
 * 									2- DISABLED
*/

#define SPI_INTERRUPT_INITIAL_STATE		DISABLED


/*
 * Choose The Data transfer order:
 * 								1- LSB_FIRST
 * 								2- MSB_FIRST
 **/

#define SPI_DATA_ORDER		LSB_FIRST


/*
 * Choose The mode of your Microcontroller:
 * 										1- MASTER_MODE
 * 										2- SLAVE_MODE
 * */

#define SPI_MICRO_MODE_SELECT	SLAVE_MODE


/*
 * Choose The clk polarity mode:
 * 							1- LEADING_RISING
 * 							2- LEADING_FALLING
 * */

#define SPI_CLK_POLARITY	LEADING_RISING


/*
 * Choose The clk phase:
 * 					1- SAMPLE_FIRST
 * 					2- SETUP_FIRST
 * */

#define SPI_CLK_PHASE	SAMPLE_FIRST


/*
 * Choose The clk rate:
 * 					1- DIVIDE_BY_4
 * 					2- DIVIDE_BY_16
 * 	                3- DIVIDE_BY_64
 *                  4- DIVIDE_BY_128
 *                  5- DIVIDE_BY_2
 *                  6- DIVIDE_BY_8
 *                  7- DIVIDE_BY_32
 *					8- DIVIDE_BY_64
*/

#define SPI_CLK_RATE	DIVIDE_BY_16





#endif

