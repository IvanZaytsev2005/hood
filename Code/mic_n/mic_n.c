/*
 * mic_n.c
 *
 * Created: 29.11.2022 3:02:12
 *  Author: HP
 */ 
/*
пины:

PC5 -лампочка засора
PB2- реле на двигатель
PB1- зуммер

*/
#include <avr/io.h> 
#include <avr/interrupt.h>

#define dif_press 3000//разность давлений
#define dif_temp_max 90
#define dif_temp_min 80

#define adres_lcd 0x70//0x70//0b01001110//адрес дисплея
#define adres_pres 0b11101100//адрес датчика давления

#define hour_addr_1 800//адреса часов в ПЗУ
#define hour_addr_2 801
#define hour_addr_3 802
#define minute_addr 803
#define second_addr 804
#define hour_f_addr_1 805
#define hour_f_addr_2 806
#define hour_f_addr_3 807
#define minute_f_addr 808
#define second_f_addr 809

#define time_lcd 0x40//задержка в протоколе для дисплея
#define time_bmp 10//задержка в протоколе для датчика

#include "var.c"

#include "alpfabet.c"
#include "TWI_C.c"
#include "BMP280.c"
#include "lcd_c.c"


int main(void)
{
	cli();
	PORTB=0x00;
	DDRB=0xFF;
	time_cloc=time_lcd;
	//PORTB=(1<<PB2);
	////////////////////////////////////////////////////////инициализация дисплея
	delay_twi();
	delay_twi();
	delay_twi();
	delay_twi();
	twi_init();
	delay_twi();
	delay_twi();
	delay_twi();
	delay_twi();
	
	//saving();
	
	times_read();
	lcd_init();
    //print_time_filtr();
	//print_decide();


		
// 	
//	time_out(10,45,32);
//  print_time_filtr();
// 	print_engin();
//	print_time_full();
// 
///////////////////////////////////////////////	//инициализация АЦП
	PORTC=0;
	DDRC=0b100000;
	ADMUX=(1<<ADLAR)|(1<<REFS0);
	ADCSRA=(1<<ADEN)|(1<<ADIE);
	ADCSRA|=(1<<ADSC);
/////////////////////////////////////////////инициализация компаратора
	DDRD&=~(1<<PD6)|(1<<PD7);
	PORTD&=~(1<<PD6)|(1<<PD7);
	ACSR=(1<<ACIE)|(0<<ACIS1)|(0<<ACIS0);
	
////////////////////////////////////////////установка начального значения флагового регистра	

flag=0b00100100;

///////////////////     // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  инициализация bmp280
	time_cloc=5;


	read_constant();

	twi_start();
	twi_transmit(adres_pres);
	twi_transmit(0xD0);
	twi_stop();
	twi_start();
	twi_transmit(adres_pres+1);
	twi_read();
	twi_nackm();
	twi_stop();

 bmp_280_init();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    	
//	long_out(dig_P2);
//


     read_pressure();



 	volatile unsigned long int press_0=press;
	time_cloc=time_lcd;// 	long_out(press);
// 	time_cloc=10;
// 	read_pressure();
// 	time_cloc=time_lcd;	

	 	 
////////////////////////////////////////////////////////////////////////////////////////////////////////

	//инициализация кнопок
		DDRD&=~((1<<PD2)|(1<<PD3));
		PORTD=(1<<PD2)|(1<<PD3);
		MCUCR=(1<<ISC11)|(1<<ISC01);
		GICR=(1<<INT1)|(1<<INT0);
		PORTC|=(1<<PC1);
// 	////////////////////////////////////////////////////////////////////////////////////////////////////////
 	//инициализация таймер 2 асинхронный режим
	ASSR=(1<<AS2);
	TCCR2=(1<<CS22)|(1<<CS20);
	TIMSK=(1<<TOIE2);
	PORTB=(1<<PB2);
 	//time_hour(123);
	//time_hour(123);
	 sei();
	 //flag=0b00100100;
    while(1)
    {		////////////////////////////////////////обработчик вывода фраз
				flag_copy=flag;
		//проверка на нажатие кнопки двигателя
		if (((PINC&(1<<PC1))==0)&((flag_copy&0b11)!=1))
		{
			PORTB|=(1<<PB2);
			flag|=0b10000000;
		}
		else
		{
			PORTB&=~(1<<PB2);
			flag&=~(0b10000000);
		}
		switch (flag_copy&0b11100)
		{
			case 0:
			break;
			
			case 0b0100:
			print_time_full();
			flag&=~(0b11100);
			GIFR=0b11000000;
			GICR=(1<<INT1)|(1<<INT0);
			break;
			
			case 0b1000:
			print_time_filtr();
			flag&=~(0b11100);
 			GIFR=0b11000000;
 			GICR=(1<<INT1)|(1<<INT0);
			break;
			
			case 0b1100:
			print_engin();
			flag&=~(0b11100);
			break;
			
			case 0b10000:
			print_filtr();
			flag&=~(0b111100);
			GICR=(1<<INT1)|(1<<INT0);
			break;
			case 0b10100:
			print_decide();
			flag&=~(0b111100);
			GIFR=0b11000000;
			GICR=(1<<INT1)|(1<<INT0);
			break;
		}
		////////////////////////////////////////обработчик вывода времени
		if ((flag_copy&0b00100000)!=0)//вывод времени по необходимости
		{
			if (aaaaa==0)
			{
			if ((flag_copy&0b1000000)!=0)
			{
				/*b=minuts_f;
				c=seconds_f;
				time_out(a,b,c);*/
				time_hour(hours_f);
			}
			else
			{
// 				b=minuts;
// 				c=seconds;
// 				time_out(a, b,c);
				time_hour(hours);
			}
			flag&=0b11011111;
			}			
		}
		
		//////////////////////////////////////////////////выбор режима работы
		
		switch (flag_copy&0b11)
		{
			case 0://штатный режим- вывод времени, измерения
			aaaaa=0;
			run=0;
			//flag_two=0;
			PORTC&=~(1<<PC5);
			time_cloc=10;
			//bmp_280_init();
			read_pressure();//                                                         костыль!!!!
// 			press_2=press;
// 			bmp_280_init();
// 			read_pressure();//                                                         костыль!!!!
// 			press_2=press_2+press;
// 			press=press_2/2;
			time_cloc=time_lcd;
			//long_out(press);
			//press_0=press;
			if (abs((press-press_0))>dif_press)
			{
				aaaaa=5;
				run=10;
				flag=0b10010|(flag_copy&0b10000000);
// 				if ((flag_copy&0b1000000)!=0)
// 				{
// 					filtr_to_all=0b1001000;
// 				}
// 				else
// 				{
// 					filtr_to_all=0b0000100;
// 				}
				
				PORTC&=~(1<<PC5);
				break;
			}
			if (temp_temp>=dif_temp_max)
			{
				flag=(flag&~(0b1111111))|0b00001101;
				PORTB&=~(1<<PB2);
				run=1;
				
			}
			break;
			
			case 1://перегрев двигателя - вывод соотв фразы, выключение двига, ждем пока уменьшится
			if (((run&0b111)%2)==1)
			{
				PORTC|=(1<<PC5);
				PORTB|=(1<<PB1);
			}
			else
			{
				PORTC&=~(1<<PC5);
				PORTB&=~(1<<PB1);
			}
			if (temp_temp<dif_temp_min)
			{
				flag=(flag&~(0b1111111))|0b10100100;
				//PORTB|=(1<<PB2);
				PORTB&=~(1<<PB1);
			}
			break;
			
			case 2://засор фильтра - моргаем фразами, лампочкой и зумером, проверяем температуру
						if (temp_temp>=dif_temp_max)
			{
				flag=((flag&~(0b11111111))|0b00001101)|(flag_copy&0b10000000);
				PORTB&=~(1<<PB2);
				run=1;
			}
			if (((run)==8))
			{
				flag=0b00010010|(flag_copy&0b10000000);
				run++;
				aaaaa=5;
			}
			if ((run)==16)
			{
				flag=0b1101010|(flag_copy&0b10000000);
				run=1;
				aaaaa=0;
			}
			break;
			
			case 0b11:
			if (run==0)
			{
				run=1;
			}
			aaaaa=5;
			if (run>=8)
			{
				switch (filtr_to&0b11)
				{
					case 0:
					if ((filtr_to&0b01000000)!=0)
					{
						flag=0b01101000|(flag_copy&0b10000000);
					}
					else
					{
						flag=0b00100100|(flag_copy&0b10000000);
					}
					aaaaa=0;
					run=0;
					break;
					case 2:
					flag=0b01101010|(flag_copy&0b10000000);//|(filtr_to&0b01100000);
					aaaaa=5;
					break;
					default:
					break;
					
				}
				break;
				
			}
			default: break;
		}
		
		if (flag_two!=0)
		{
			flag=flag_two;//|(flag&0b10000000);
			flag_two=0;
		}			
		//flag_two=0;
    }
}





  
 ISR(INT0_vect)
 {
	 cli();
	 volatile unsigned int i=0;
 	 while (i<0xFFF)
 	 {
 		 i--;
 	 }
	  if ((flag&0b11)==0)
	  {
		 if ((flag&0b01000000)!=0)
		 {
			 flag_two=(flag&0b11)|0b00100100|(flag&0b10000000);
		 }
		 else
		 {
			 flag_two=(flag&0b11)|0b01101000|(flag&0b10000000);
		 }
		 GICR=(0<<INT1)|(0<<INT0);
	  }	 
	  
	  /*if ((flag&0b11)==2)
	  {
		  filtr_to_all=flag_two&0b11111100+0b10;
	  }*/
	  
	  sei();
  }
  
  ISR(INT1_vect)
  {
	  cli();
	  volatile unsigned int i=0;
	 while (i<0xFFF)
	 {
		 i--;
	 }
	 
	 if ((flag&0b11)==0b11)
	 {
		 seconds_f=0;
		 minuts_f=0;
		 hours_f=0;
		 
		 flag_two=0b01101000|(flag&0b10000000);
		 //flag=0b01101000|(flag&0b10000000);
// 		 run=0;
// 		 aaaaa=0;
	 }	 
	 else
	 {
		 if ((flag&0b11)!=0b01)
		{ 
			filtr_to=flag;
		 //flag=;
		 flag_two=0b00010111|(flag&0b10000000);
 		 run=1;
// 		 aaaaa=5;
		 }
	 }
	 GICR=(0<<INT1)|(0<<INT0);
	 sei();
  }
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ISR(TIMER2_OVF_vect)
 {
	 ADCSRA|=(1<<ADSC);
	 if ((run>0))//(flag&0b11)!=0)
	 {
		 run++;
	 }
	 
	 if ((flag&0b10000000)!=0)
	 {	 
	 seconds++;//замненить hours на seconds
	 if (seconds>=60)
	 {
		 seconds=0;
		 minuts++;
		 if (minuts>=60)
		 {
			 minuts=0;
			 hours++;
		 }			 
	 }	
	 
	 seconds_f++;//замненить hours_f на seconds_f
	 if (seconds_f>=60)
	 {
		 seconds_f=0;
		 minuts_f++;
		 if (minuts_f>=60)
		 {
			 minuts_f=0;
			 hours_f++;
		 }			 
 	 }	

// 	 if (run!=0b00)
// 	 {
 		flag|=0b00100000;
//	 }	 
	}	 
 }

ISR(ADC_vect)
{
	
	res_adc=(ADC&0xFF00)>>8;
	//res_adc=res_adc>>2;
	//time_out(0,res_adc/100, res_adc%100);
	//проверка ацп и преобразователя в температуру, вывод температуры на экран//эта хрень работает, не трогать!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		volatile unsigned char i=0;
		while (((tep_adc[i+91])>res_adc)&(i<90))
		{
			i++;
		}
		temp_temp=tep_adc[i];
		if (temp_0!=temp_temp)
		{
			//time_out(0,temp_temp/100, temp_temp%100);
			temp_0=temp_temp;
		}			
		
}



// проверка процедуры чтения
		// 	
		// 		twi_start();
		// 		twi_transmit(0b11010000);
		// 		twi_transmit(0);
		// 		twi_transmit(0x32);
		// 		twi_transmit(0x45);
		// 		twi_stop();
		// 		
		// 		twi_start();
		// 		twi_transmit(0b11010000);
		// 		twi_transmit(1);
		// 		twi_stop();
		// 		
		// 		twi_start();
		// 		twi_transmit(0b11010001);
		// 		volatile char x=twi_read();
		// 		twi_stop();
		// 		
		// 		twi_start();
		// 		twi_transmit(x);
		// 		twi_stop();
		
// работа с bmp170
// 	twi_start();
// 	twi_transmit(adres_pres);
// 	twi_transmit(0xE0);
// 	twi_transmit(0xB6);
// 	twi_stop();
// 	twi_start();
// 	twi_transmit(adres_pres);
// 	twi_transmit(0xFA);
// 	twi_stop();
// 	twi_start();
// 	twi_transmit(adres_pres+1);
// 	press[0]=twi_read();
//  	press[1]=twi_read();
//  	press[2]=twi_read();
// 	twi_stop();
// 	twi_start();
// 	twi_transmit(press[0]);
//  	twi_transmit(press[1]);
//  	twi_transmit(press[2]);
// 	twi_stop();
// 
// 
// 
//  	twi_start();
//  	twi_transmit(adres_pres);
//  	twi_transmit(0xF6);
//  	twi_stop();
//  	twi_start();
//  	twi_transmit(adres_pres+1);
//  	volatile unsigned char x;
//  	x=twi_read();
//  	twi_nackm();
// 	twi_stop();
// //	DDRD&=~(1<<sda);
// 	time_out(0,0,x);

ISR(ANA_COMP_vect)
{
	cli();
	//print_filtr();
	/*
	ASSR=0;
	TCCR2=0;
	TIMSK=0;*/
	
	DDRD=0;
	DDRC=0;
	DDRB=0;
	PORTB=0;
	PORTD=0;
	PORTC=0;
	/*
	ADMUX=0;
	ADCSRA=0;
	ADCSRA=0;
	
	ACSR=0;
	
	MCUCR=0;
	GICR=0;*/
	
	//////////////////////////////////////////запись времени в eeprom
	
	//unsigned int uiAddress;
	//unsigned char ucData;
	
	saving();
	
	while (1)
	{
	}
}

void saving(void)
{
		while(EECR & (1<<EEWE));
	EEDR = hours&0xFF;
	EEAR = hour_addr_1;
	EECR |= (1<<EEMWE);
	EECR |= (1<<EEWE);
	
	while(EECR & (1<<EEWE));
	EEDR = (hours&0xFF00)>>8;
	EEAR = hour_addr_2;
	EECR |= (1<<EEMWE);
	EECR |= (1<<EEWE);
	
	while(EECR & (1<<EEWE));
	EEDR = (hours&0xFF0000)>>16;
	EEAR = hour_addr_3;
	EECR |= (1<<EEMWE);
	EECR |= (1<<EEWE);
	
/*
	while(EECR & (1<<EEWE));
	EEDR = minuts;
	EEAR = minute_addr;
	EECR |= (1<<EEMWE);
	EECR |= (1<<EEWE);
	
	while(EECR & (1<<EEWE));
	EEDR = seconds;
	EEAR = second_addr;
	EECR |= (1<<EEMWE);
	EECR |= (1<<EEWE);*/
	
	
	while(EECR & (1<<EEWE));
	EEDR = hours_f&0xFF;
	EEAR = hour_f_addr_1;
	EECR |= (1<<EEMWE);
	EECR |= (1<<EEWE);
	
	while(EECR & (1<<EEWE));
	EEDR = (hours_f&0xFF00)>>8;
	EEAR = hour_f_addr_2;
	EECR |= (1<<EEMWE);
	EECR |= (1<<EEWE);
	
	while(EECR & (1<<EEWE));
	EEDR = (hours_f&0xFF0000)>>16;
	EEAR = hour_f_addr_3;
	EECR |= (1<<EEMWE);
	EECR |= (1<<EEWE);
	
/*
	while(EECR & (1<<EEWE));
	EEDR = minuts_f;
	EEAR = minute_f_addr;
	EECR |= (1<<EEMWE);
	EECR |= (1<<EEWE);
	
	while(EECR & (1<<EEWE));
	EEDR = seconds_f;
	EEAR = second_f_addr;
	EECR |= (1<<EEMWE);
	EECR |= (1<<EEWE);*/
	
	while(EECR & (1<<EEWE));
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
/* Wait for completion of previous write */
while(EECR & (1<<EEWE))
;
/* Set up address register */
EEAR = uiAddress;
/* Start eeprom read by writing EERE */
EECR |= (1<<EERE);
/* Return data from data register */
return EEDR;
}

void times_read(void)
{
	hours=EEPROM_read(hour_addr_1);
 	hours=hours+((EEPROM_read(hour_addr_2))<<8);
 	hours=hours+((EEPROM_read(hour_addr_3))<<16);
	minuts=EEPROM_read(minute_addr);
	seconds=EEPROM_read(second_addr);
	
	hours_f=EEPROM_read(hour_f_addr_1);
 	hours_f=hours_f+((EEPROM_read(hour_f_addr_2))<<8);
 	hours_f=hours_f+((EEPROM_read(hour_f_addr_3))<<16);
	minuts_f=EEPROM_read(minute_f_addr);
	seconds_f=EEPROM_read(second_f_addr);
	while(EECR & (1<<EEWE));
}