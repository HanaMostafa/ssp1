#include <stdio.h>
#include <stdlib.h>
#include "ssp.h"
#include "time.h"




void ssp_frame(uint8 *txframe,uint8 *size,uint8 *data ,uint8 desti,uint8 srce,uint16 z, uint8 *dataflag) {

    uint16 p,k;


    txframe[fend]=0xc0;

    txframe[dest]=desti;

 if(txframe[dest]!=0xc0 && txframe[dest]!=0xdb && txframe[dest]!=0){
   txframe[src]=srce;
 if(txframe[src]!=0xc0 && txframe[src]!=0xdb && txframe[src]!=0){

   uint8 pk;
    uint8 ss;
   //uint8 modeid=0x03;
    //uint8 nodeaddress=0x05;
    //uint8 timestamp=0x01;



 txframe[3]=0x2f;
    pk=(txframe[3] & 0x3f);
    ss=(txframe[3] & 0xc0);
    ss=ss&0x00;




   if ((ss>>6)==0x0){

 uint8 f,count=0,w=0,count2=0;
 int temp=0,temp2=0;

for(k=0;k<z;k++){

if(data[k]==0xc0){

   count++;

}}
for(k=0;k<z;k++){

if(data[k]==0xdb){

   count2++;

}}
    temp=z+count;
    temp2=z+count2;
    //printf("k= %x \n",k);
            //printf("%d \n",*(&data + 1) - data);
    for(k=0;k<=temp;k++){

    if(data[k]==0xc0){

   data[k]=0xdb;
   //printf("k= %x \n",k);
  //printf("fend= %x \n",txframe[fend]);
    for(f=temp;f>=(k+1);f--){

        data[f]= data[f-1];

    }
    data[k+1]=0xdc;


    }
 else if(data[k]==0xdb){
    data[k]=0xdb;
    for(f=temp2;f>=(k+1);f--){
        data[f]= data[f-1];

    }
    data[k+1]=0xdd;
    }
    }

    //printf("%d \n",z);
w=temp+count2+4;
    for(p=4;p<(w);p++){

        txframe[p]=data[p-4];

   }
   txframe[w]=0xd3;                    // crc0
   txframe[(w+=1)]=0x23;                //crc1
    txframe[(w+1)]=0xc0;
    *size=(w+2);
    }

 *dataflag =0;
 }}
}
void print(uint8 *txframe,uint16 size, uint8 *rxframe){
    int i;


     /*for(i=0;i<size;i++){
            if(txframe[dest]==0xc0 || txframe[dest]==0xdb || txframe[dest]==0){
            printf("error\n");
           exit(1);


            }
             else if(txframe[src]==0xc0 || txframe[src]==0xdb || txframe[src]==0){
        printf("error\n");
   exit(1);


            }*/

 for(i=0;i<size;i++){

      printf("%x \n",txframe[i]);
      rxframe[i]=txframe[i];

      }


     }


void receiver(uint8 *rxframe,uint16 size,uint8 adddest,uint8 addsrc,uint8 type, uint8* datta,uint16 *size3){
    uint16 i,size2;
    uint8 count=0,k;
    size2=size-3;

    if(rxframe[fend]==0xc0){
        adddest=rxframe[dest];
        addsrc=rxframe[src];
        type=rxframe[3];
  for(i=4;i<(size-3);i++){

datta[i]=rxframe[i];
  }
for(i=4;i<(size-3);i++){
    if((datta[i]==0xdb) && (datta[i+1]==0xdc)){

            size2--;


        }
}
for(i=4;i<(size-3);i++){
    if((datta[i]==0xdb) && (datta[i+1]==0xdd)){

            count++;

        }
}

for(i=4;i<(size-3);i++){
if((datta[i]==0xdb) && (datta[i+1]==0xdc)){

 datta[i]=0xc0;
    for(k=i+1; k<size-3; k++)
        {

            datta[k] =datta[k+1];

        }

}}


for(i=4;i<(size-3);i++){
if((datta[i]==0xdb) && (datta[i+1]==0xdd)){

 datta[i]=0xdb;
    for(k=i+1; k<size-3; k++)
        {

            datta[k] =datta[k+1];

        }

}}
*size3=size2-count;
/*for(i=4;i<(size3);i++){

printf("data %x \n",datta[i]);
}
*/
    }
}
