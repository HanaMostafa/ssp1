#ifndef SSP_H
#define SSP_H


#define fend 0
#define dt 236
#define dest 1
#define src 2
#define typ 3
#define header 8
#define info 229
#define ready 1
#define notready 0
#define tx 1
#define rx 2
#define idle 0
typedef unsigned char         uint8;
typedef unsigned short        uint16;
/*typedef struct txframe{
	uint8 fend;
	uint8 dest;
	uint8 src;
	uint8 type;
	uint8 len;
	uint8 secheader[header];
	uint8 data[dt];
	uint8 crc0;
	uint8 crc1;
};*/
//uint8 txframe[dt];



/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )


unsigned short compute_crc16( unsigned char* data_p, unsigned char length);
void ssp_frame(uint8 *txframe,uint8 *data ,uint8 desti,uint8 srce,uint8 typee,uint16 tx_size,uint8 *txflag);
void print(uint8 *txframe ,uint8 *rxframe);
void receiver(uint8 *rxframe,uint8* adddest,uint8* addsrc,uint8* type, uint8 *datta,uint16 *size3,uint8 *rxflag,uint8 *crcflag);
void commandtype(uint8 *type);
void management_layer(uint8 *Tx_App_data,uint16 z,uint8 Tx_App_desti,uint8 *Tx_Frm_srce,uint8 Tx_App_type,uint8 *Tx_Frm_type,uint8 *Tx_Frm_data,uint8 *Tx_Frm_desti,uint8 *Rx_Frm_type,uint8 *Rx_Frm_data,uint8 *Rx_Frm_dest,uint16 Rx_length,uint8 *dataflag,uint8 *rxflag,uint8 *txflag,uint8 *Rx_App_data,uint8 crcflag,uint16 *tx_size);
#endif // SSP_H
