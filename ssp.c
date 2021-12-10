#include <stdio.h>
#include <stdlib.h>
#include "ssp.h"
#include "time.h"

void layer (uint8 *Tx_App_data,uint16 z,uint8 Tx_App_desti,uint8 *Tx_Frm_srce,uint8 Tx_App_type,uint8 *Tx_Frm_type,uint8 *Tx_Frm_data,uint8 *Tx_Frm_desti,uint8 *Rx_Frm_type,uint8 *Rx_Frm_data,uint8 *Rx_Frm_dest,uint16 Rx_length,uint8 *dataflag,uint8 *rxflag,uint8 *txflag,uint8 *Rx_App_data){
    uint8 controlflag=idle,source=0x6b;
    uint8 layerflag=notready;
    uint8 i;

if(*dataflag==ready && controlflag==idle&& *txflag==notready){
 controlflag= tx;
 *Tx_Frm_srce=source;
 // es2ali 3ala el z ??
 for(i=0;i<z;i++){
 Tx_Frm_data[i]=Tx_App_data[i];
 }
 *Tx_Frm_desti=Tx_App_desti;
 *Tx_Frm_type=Tx_App_type;
*txflag=ready;
*dataflag=notready;
}
else if(*rxflag==ready&&layerflag==notready&& controlflag==idle){

if(*Rx_Frm_dest==source){
    controlflag= rx;
    layerflag=ready;
    *rxflag=notready;
    // hab3at el data ll layer el b3dha
    for(i=0;i<Rx_length;i++){
 Rx_App_data[i]=Rx_Frm_data[i];
 }
}
else{

    *rxflag=notready;
}
}
else if(controlflag!=rx && controlflag!=tx){
    controlflag=idle;
}
if(controlflag==tx&& *rxflag==ready){

if(*Rx_Frm_dest==source&& *Rx_Frm_type==0x02){
controlflag=idle;
  }

 else if((*Rx_Frm_dest==source)&&(*Rx_Frm_type==0x03||*Rx_Frm_type==0x13||*Rx_Frm_type==0x23)){
*Tx_Frm_srce=source;
 for(i=0;i<z;i++){
 Tx_Frm_data[i]=Tx_App_data[i];
 }

 *Tx_Frm_desti=Tx_App_desti;
 *Tx_Frm_type=Tx_App_type;
*txflag=ready;
  }
 else if(*Rx_Frm_dest!=source){
    *rxflag=notready;
  }
}
 if(controlflag==rx) {
        //frame ack w hab3ato ll tframing layer
        // hena el data hatb2a ehh ??
 *Tx_Frm_srce=Rx_Frm_dest;
 for(i=0;i<z;i++){
 Tx_Frm_data[i]=Tx_App_data[i];
 }

 *Tx_Frm_desti=source;
 *Tx_Frm_type=0x02;
 *txflag=ready;
  controlflag=idle;
 }

}



void ssp_frame(uint8 *txframe,uint8 *data ,uint8 desti,uint8 srce,uint8 typee,uint16 z,uint8 *txflag) {

    uint16 p,k;

*txflag=ready;
    txframe[fend]=0xc0;

    txframe[dest]=desti;


   txframe[src]=srce;


   uint8 pk;
    uint8 ss;


 txframe[typ]=typee;
    pk=(txframe[typ] & 0x3f);
    ss=(txframe[typ] & 0xc0);
    ss=ss&0x00;






 uint8 f,d,dattta[info],count=0,w=0,count2=0,arr[dt];
 int temp=0,temp2=0,temp3=0;
uint16 crc,crc0,crc1;
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


  /*  temp3=z+count+count2;

 for(k=0;k<=temp3;k++){

    if(data[k]==0xc0){
            dattta[k]=0xdb;
            dattta[k+1]=0xdc;
            k=k+1;
    }
    else if(data[k]==0xdb){
    dattta[k]=0xdb;
    dattta[k]=0xdd;
    k=k+1;
    }
    else{
        dattta[k]=data[k];
    }}
    */
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
//w=temp3+4;


    for(p=4;p<(w);p++){

        txframe[p]=data[p-4];

   }
    for(d=1;d<w;d++){
        arr[d-1]=txframe[d];
       // printf("array %x \n",arr[d-1]);
    }
   crc=compute_crc16(arr,(w-1));
   crc0=(crc & 0x00ff);
   crc1=((crc& 0xff00)>>8);
   printf(" crc= %x \n",crc);
   txframe[w]=crc0;                    // crc0
   txframe[(w+=1)]=crc1;                //crc1
    txframe[(w+1)]=0xc0;
   // *size=(w+2);

*txflag=notready;
}
void print(uint8 *txframe, uint8 *rxframe){
    int i,j,count=1;
for(j=1;j<dt;j++){

    if(txframe[j]==0xc0){
count++;
           break;

        }
        else{

         count++;

        }

}
printf("sizeeeeeee count = %d \n",count);
 for(i=0;i<count;i++){

      printf("%x \n",txframe[i]);
      rxframe[i]=txframe[i];

      }


     }


void receiver(uint8 *rxframe,uint8* adddest,uint8* addsrc,uint8* type, uint8* Rx_data,uint16 *length,uint8 *rxflag){
    uint16 i,j,d,size2,size=1,crc,size3;
    uint8 count=0,k,y=0,arr[dt],datta[info+4];
    *rxflag= notready;
    *adddest=rxframe[dest];
    for(j=1;j<dt;j++){

    if(rxframe[j]==0xc0){
    size++;
           break;

        }
        else{

         size++;

        }

}

for(d=1;d<size-1;d++){
        arr[y]=rxframe[d];
 // printf("frame %x \n",arr[d-1]);
  y++;
}
crc=compute_crc16(arr,y);
//printf("crccc %x ",crc);



    size2=size-3;

    if(rxframe[fend]==0xc0 && crc==0x00){
        *adddest=rxframe[dest];
        *addsrc=rxframe[src];
        *type=rxframe[3];
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
size3=size2-count;
*length=size3-4;
printf("size3 = %d \n",*length);
/*for(i=4;i<(*size3);i++){

printf("data %x \n",datta[i]);
}
*/
for(i=0;i<(*length);i++){
 Rx_data[i]=datta[i+4];
}

*rxflag =ready;
    }
}


void commandtype(uint8 *type){

 if(*type==0x01){

 }

if(*type==0x2c){

 }

}

