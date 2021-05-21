#include "dht11.h"
/*******DQ-------PE3*/
#define DHT_IO HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)


void DHT11_IOin(void){
	GPIOE->CRL &=~ (0x0F000);
	GPIOE->CRL |=  (0x04000);
}
void DHT11_IOout(void){
	GPIOE->CRL &=~ (0x0F000);
	GPIOE->CRL |=  (0x01000);
}
void DQout(uint8_t v){
	switch (v) {
		case 1 :GPIOE->ODR|= (1<<3); break;
		case 0 :GPIOE->ODR&=~(1<<3); break;
	}
}
uint8_t DHT11_Read_Bit(){
	uint8_t retry=0;
	while(DHT_IO&&retry<100){retry++;delay_us(1);}
	while(!DHT_IO&&retry<200){retry++;delay_us(1);}
	delay_us(40);
	if(DHT_IO)return 1;else return 0;
}
uint8_t DHT11_Read_Byte(){
	uint8_t i,dat=0;
	for(i=0;i<8;i++){dat<<=1; dat|= DHT11_Read_Bit();}
	return dat;
}


uint8_t DHT11_Rst(){
	uint8_t retry=0;
	DHT11_IOout();
	DQout(0);
	HAL_Delay(20);
	DQout(1);
	delay_us(30);
	/******check*****////return 0ÎªÕý³£
	DHT11_IOin();
	while(DHT_IO&&retry<100){retry++;delay_us(1);}
	if(retry>=100)printf("rst=error\r\n") ;else retry=0; 
	while(!DHT_IO&&retry<100){retry++;delay_us(1);}
	if(retry>=100) return 1; else return 0 ;
}

uint8_t DHT11_Read_Data(uint8_t *th,uint8_t *dh){
	uint8_t buf[5];
	if(DHT11_Rst()==0){
		for(uint8_t i=0;i<5;i++){buf[i]=DHT11_Read_Byte();}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4]){
			*dh=buf[0];
			*th=buf[2];
			 printf("temp_calculate_ok\r\n");
		}else return 1;
	}
	return 0;
}





