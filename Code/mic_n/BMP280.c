//bmp280
#define bmp180 0xAA
#define bmp280 0x88

// для проверки правильности расчетов вводим значения
volatile signed long   dig_T1;//=27504;
volatile signed long   dig_T2;//=26435;
volatile signed long   dig_T3;//=-1000;
volatile signed long   dig_P1;//=36477;
volatile signed long   dig_P2;//=-10685;
volatile signed long   dig_P3;//=3024;
volatile signed long   dig_P4;//=2855;
volatile signed long   dig_P5;//=140;
volatile signed long   dig_P6;//=-7;
volatile signed long   dig_P7;//=15500;
volatile signed long   dig_P8;//=-14600;
volatile signed long   dig_P9;//=6000;
volatile signed long   bmp_pressure;
volatile signed long   bmp_temp;


void read_constant()
{
	twi_start();
	twi_transmit(adres_pres);
	twi_transmit(0x88);
	twi_stop();
	twi_start();
	twi_transmit(adres_pres+1);
	dig_T1=twi_read();
	twi_ackm();
	dig_T1|=(twi_read())<<8;
	twi_ackm();
	dig_T2=read_signed();
	twi_ackm();
	dig_T3=read_signed();
	twi_ackm();
	dig_P1=twi_read();
	twi_ackm();
	dig_P1|=(twi_read())<<8;
	twi_ackm();
	dig_P2=read_signed();
	twi_ackm();
	dig_P3=read_signed();
	twi_ackm();
	dig_P4=read_signed();
	twi_ackm();
	dig_P5=read_signed();
	twi_ackm();
	dig_P6=read_signed();
	twi_ackm();
	dig_P7=read_signed();
	twi_ackm();
	dig_P8=read_signed();
	twi_ackm();
	dig_P9=read_signed();
	twi_nackm();
	twi_stop();
}

volatile void read_pressure(void)
{
	
	//temp=0;
	//press=0;
	twi_start();
	twi_transmit(adres_pres);
	twi_transmit(0xF7);
	twi_stop();
	//bmp_pressure=0;
	//считываем значения давления и темпы из микросхемы баз компенсации
	twi_start();
	twi_transmit(adres_pres+1);
	bmp_pressure=twi_read()*4096;
	twi_ackm();
	bmp_pressure=(twi_read()*16)+bmp_pressure;
	twi_ackm();
	bmp_pressure=twi_read()+bmp_pressure;

	twi_ackm();
	//bmp_temp=0;
	bmp_temp=twi_read()*4096;
	twi_ackm();
	bmp_temp=(twi_read()*16)+bmp_temp;
	twi_ackm();
	bmp_temp=twi_read()+bmp_temp;
	twi_nackm();
	twi_stop();
	
	//для проверки вводим какие то цифры
 	//volatile signed long   bmp_pressure=415156;
 	//volatile signed long   bmp_temp=519888;
	
	// каллибровка по даташиту
	volatile signed long var1=0;
	volatile long signed   var2=0;
	volatile long signed   t_fine=0;
	volatile long signed   T=0;
	volatile long unsigned   ppp=0;

	
	var1=(((bmp_temp>>3)-(dig_T1<<1))*(dig_T2))>>11;
	var2=(((((bmp_temp>>4)-(dig_T1))*((bmp_temp>>4)-(dig_T1)))>>12)*(dig_T3))>>14;
	t_fine=(var2+var1);
	T=((t_fine*5+128)>>8);
	//temp=T;
	
	
	var1=0;
	var2=0;
	
	var1=((t_fine>>1)-64000);
	var2=var1*var1*dig_P6/32768;
	//var2=(((var1>>2)*(var1>>2))>>11)*(dig_P6);
	
	//var2=-9;
	
	var2=var2+(var1*(dig_P5)*2);
	var2=(var2>>2)+((dig_P4)<<16);
	var1=(((dig_P3*(((var1>>2)*(var1>>2))>>13))>>3)+(((dig_P2)*var1)>>1))>>18;
	var1=((32768+var1)*(dig_P1))>>15;
	if (var1==0)
	{
		press=0;
	}
	ppp=((((1048576-bmp_pressure))-(var2>>12)))*3125;
//	ppp=((long signed  )(528688*3125-var2*3125/0x1000));
	if (ppp<0x80000000)
		{
			ppp=(ppp<<1)/(var1);
		}	
		else
		{
			ppp=(ppp/var1)*2;
	}
	//ppp=0x1448f;
	var1=((dig_P9)*((((ppp>>3)*(ppp>>3))>>13)))>>12;
	var2=(ppp>>15)*dig_P8;
	press=(ppp+((var1+var2+dig_P7)>>4));




	//press=1234567;
	//temp=1234;
	//time_cloc=0x90;
	//long_out(press);
	//time_out((temp%1000000)/10000,(temp%10000)/100, temp%100);
	//time_out(12,35,67);
}

void bmp_280_init (void)
{
	twi_start();
twi_transmit(adres_pres);
twi_transmit(0xE0);
twi_transmit(0xB6);
twi_stop();

press=1;
while ((press&1)!=0)
{
	twi_start();
	twi_transmit(adres_pres);
	twi_transmit(0xF3);
	twi_stop();
	twi_start();
	twi_transmit(adres_pres+1);
	press=twi_read();
	twi_nackm();
	twi_stop();
}

// twi_start();
// twi_transmit(adres_pres);
// twi_transmit(0xF4);
// twi_transmit(0b001001);
// twi_stop();

twi_start();
twi_transmit(adres_pres);
twi_transmit(0xF4);
twi_transmit(0b00100111);
twi_stop();


twi_start();
twi_transmit(adres_pres);
twi_transmit(0xF5);
twi_transmit(0x80);
twi_stop();

// press=1;
// while ((press&1)!=0)
// {
// 	twi_start();
// twi_transmit(adres_pres);
// twi_transmit(0xF3);
// twi_stop();
// twi_start();
// twi_transmit(adres_pres+1);
// press=twi_read();
// twi_nackm();
// twi_stop();
// }


// press=1;
// while ((press&1)!=0)
// {
// 	twi_start();
// twi_transmit(adres_pres);
// twi_transmit(0xF3);
// twi_stop();
// twi_start();
// twi_transmit(adres_pres+1);
// press=twi_read();
// twi_nackm();
// twi_stop();
// }

// twi_start();
// twi_transmit(adres_pres);
// twi_transmit(0xF4);
// twi_transmit(0b01001011);
// twi_stop();

// press=1;
// while ((press&1)!=0)
// {
// 	twi_start();
// twi_transmit(adres_pres);
// twi_transmit(0xF3);
// twi_stop();
// twi_start();
// twi_transmit(adres_pres+1);
// press=twi_read();
// twi_nackm();
// twi_stop();
// }
/*

	press=0b1000;
while ((press&0b1000)!=0)
{
	twi_start();
	twi_transmit(adres_pres);
	twi_transmit(0xF3);
	twi_stop();
	twi_start();
	twi_transmit(adres_pres+1);
	press=twi_read();
	twi_nackm();
	twi_stop();
}	*/
// twi_start();
// twi_transmit(adres_pres);
// twi_transmit(0xf7);
// twi_stop();
// twi_start();
// 	twi_transmit(adres_pres+1);
// 	bmp_pressure=twi_read()*4096;
// 	twi_ackm();
// 	bmp_pressure=(twi_read()*16)+bmp_pressure;
// 	twi_ackm();
// 	bmp_pressure=twi_read()+bmp_pressure;
// 	twi_ackm();
// 	bmp_temp=twi_read()*4096;
// 	twi_ackm();
// 	bmp_temp=(twi_read()*16)+bmp_temp;
// 	twi_ackm();
// 	bmp_temp=twi_read()+bmp_temp;
// 	twi_nackm();
// 	twi_stop();
}