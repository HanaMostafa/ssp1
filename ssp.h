#ifndef SSP_H
#define SSP_H


#define fend 0
#define dt 512
#define dest 1
#define src 2
#define header 8
#define info 255
#define ready 1
#define notready 0
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

void ssp_frame(uint8 *txframe,uint8 *size,uint8 *data,uint8 desti,uint8 srce,uint16 z,uint8 *dataflag);
void print(uint8 *txframe ,uint16 size,uint8 *rxframe);
void receiver(uint8 *rxframe,uint16 size,uint8 adddest,uint8 addsrc,uint8 type, uint8 *datta,uint16 *size3);

#endif // SSP_H
