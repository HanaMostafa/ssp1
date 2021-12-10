#include <stdio.h>
#include <stdlib.h>
#include"ssp.h"

unsigned short compute_crc16( unsigned char* data_p, unsigned char length){
    unsigned char x;
    unsigned short crc = 0xFFFF;

    while (length--){
/*  reverse the bits in each 8-bit byte going in */
* data_p = (* data_p & 0x55555555) << 1 | (* data_p & 0xAAAAAAAA) >> 1;
* data_p = (* data_p & 0x33333333) << 2 | (* data_p & 0xCCCCCCCC) >> 2;
* data_p = (* data_p & 0x0F0F0F0F) << 4 | (* data_p & 0xF0F0F0F0) >> 4;

        x = crc >> 8 ^ *data_p++;
        x ^= x>>4;
        crc = (crc << 8) ^ ((unsigned short)(x << 12)) ^ ((unsigned short)(x <<5)) ^ ((unsigned short)x);
    }
    /*reverse the 16-bit CRC*/
crc = (crc & 0x55555555) << 1 | (crc & 0xAAAAAAAA) >> 1;
crc = (crc & 0x33333333) << 2 | (crc & 0xCCCCCCCC) >> 2;
crc = (crc & 0x0F0F0F0F) << 4 | (crc & 0xF0F0F0F0) >> 4;
crc = (crc & 0x00FF00FF) << 8 | (crc & 0xFF00FF00) >> 8;

    return crc;
}

void getdata(uint8 * data,uint16 *z,uint8* dataflag){
 *dataflag=notready;
	uint8 i;

	uint8 arr[]={0x24,0xdb,0xc0,0xda,0x29,0xb4,0xc0,0x54,0xc0,0x33,0xc0,0xc0,0xc0,0x46,0xc0,0x37,0xc0,0x28,0xc0,0x37,0xc0,0x16,0x19,0x68,0xc0,0xdb};
*z=sizeof(arr);

//z=*(&arr + 1) - arr;

	for(i=0;i<*z;i++){
    data[i]=arr[i];

}

	*dataflag=ready;
}
int main()
{
uint8 dataflag;
uint8 rxflag=notready;
uint8 txflag=notready;
uint8 size=0;
uint16 z;
uint8 i;
uint8 desti=0x9a;
uint8 srce;
uint8 typee=0x2c;
uint8 txframe[dt];

//uint8 arr[]={0x24,0xdb,0xc0,0xda,0x29,0xb4,0xc0,0x54,0xc0,0x33,0xc0,0xc0,0xc0,0x46,0xc0,0x37,0xc0,0x28,0xc0,0x37,0xc0,0x16,0x19,0x68,0xc0,0xdb};
uint8 data[info];
uint8 data2[info];
uint8 desti2;
uint8 type2;
uint8 rxframe[dt];
//uint16 z=sizeof(arr);

getdata(&data,&z,&dataflag);

uint8 adddest;
uint8 addsrc;
uint8 type;
uint8 Rx_data[info];
uint16 Rx_length=0;
uint8 layerdata[info];
 layer (&data,z,desti,&srce, typee, &type2,&data2, &desti2, &type, &Rx_data,&adddest,Rx_length, &dataflag, &rxflag, &txflag,&layerdata);

if(txflag==ready){
ssp_frame(&txframe,&data2,desti2,srce,type2,z,&txflag);


}
//dataflag=notready;

//printf("size = %d \n",size);
print(&txframe,&rxframe);
receiver(&rxframe,&adddest,&addsrc,&type,&Rx_data,&Rx_length,&rxflag);

printf("\n\n\n after receiving \n\n\n data = \n\n");
for(i=0;i<(Rx_length);i++){

printf(" %x \n",Rx_data[i]);
}
printf("type = %x \n",type);
printf("destination = %x \n",adddest);
commandtype(type);

    return 0;
}
