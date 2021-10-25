#include <stdio.h>
#include <stdlib.h>
#include"ssp.h"
void getdata(uint8 * data,uint16 z){
	uint8 dataflag=notready;
	uint8 i;

	uint8 arr[]={0x24,0xdb,0xc0,0xda,0x29,0xb4,0xc0,0x54,0xc0,0x33,0xc0,0xc0,0xc0,0x46,0xc0,0x37,0xc0,0x28,0xc0,0x37,0xc0,0x16,0x19,0x68,0xc0,0xdb};
(z)=sizeof(arr);

//z=*(&arr + 1) - arr;

	for(i=0;i<z;i++){
    data[i]=arr[i];

}

	dataflag=ready;
}
int main()
{
uint8 dataflag=0;
uint8 size=0;
uint16 z=26;
uint8 i;
uint8 desti=0x9a;
uint8 srce=0x6b;
uint8 txframe[dt];

//uint8 arr[]={0x24,0xdb,0xc0,0xda,0x29,0xb4,0xc0,0x54,0xc0,0x33,0xc0,0xc0,0xc0,0x46,0xc0,0x37,0xc0,0x28,0xc0,0x37,0xc0,0x16,0x19,0x68,0xc0,0xdb};
uint8 data[info];
uint8 rxframe[dt];
//uint16 z=sizeof(arr);

getdata(&data,z);
printf("z= %d\n",z);
for(i=0;i<z;i++){
   printf("data %x\n",data[i]);
}

uint8 adddest;
uint8 addsrc;
uint8 type;
uint8 datta[info];
uint16 size3=0;
//for(i=0;i<info;i++){
   // data[i]=arr[i];
//}
//printf("z= %d \n",z);
ssp_frame(&txframe,&size,&data,desti,srce,z,&dataflag);

printf("size = %d \n",size);
print(&txframe,size,&rxframe);
receiver(&rxframe,size,adddest,addsrc,type,&datta,&size3);

printf("\n\n\nafter receiving \n\n\n data = \n\n");
for(i=4;i<(size3);i++){

printf(" %x \n",datta[i]);
}
    return 0;
}
