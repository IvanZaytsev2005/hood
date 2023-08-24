#define scl PD0
#define sda PD1

void delay_twi(void)
{
	volatile unsigned int i=0;
//	volatile unsigned int a;
	i=0;
	while (i<time_cloc)//0xf0//time_cloc
	{
// 		a=0;
// 		while (a<0xFF)
// 		{
// 			a++;
// 		}
		i++;;
	}
}

void twi_init(void)
{
	DDRD&=~(1<<sda)|(1<<scl);
	PORTD&=~(1<<sda)|(1<<scl);
	delay_twi();
}

void twi_start(void)
{
	delay_twi();
	DDRD|=(1<<sda);
	delay_twi();
	DDRD|=(1<<scl);
	delay_twi();
}

void twi_transmit(volatile unsigned char data)
{
	for (volatile unsigned char i=8; i>0; i--)
	{
		if ((data&(1<<(i-1)))!=0)
		{
			DDRD&=~(1<<sda);
		}
		delay_twi();
		DDRD&=~(1<<scl);
		delay_twi();
		DDRD|=(1<<scl);
		delay_twi();
		DDRD|=(1<<sda);
		delay_twi();
	} 
	DDRD&=~(1<<sda);
	delay_twi();
	DDRD&=~(1<<scl);
	delay_twi();
	
/*
	// писк по ACK
	if (((PIND&(1<<sda))==0) & (data==adres_pres+1))
	{
		PORTB=0xFF;
		delay_twi();
		delay_twi();
		delay_twi();
		delay_twi();
		PORTB=0x00;
	}
/*	else
	{
		PORTB=0xFF;
		delay_twi();
		delay_twi();
		delay_twi();
		delay_twi();
		PORTB=0x00;
		delay_twi();
		delay_twi();
		delay_twi();
		delay_twi();
		PORTB=0xFF;
		delay_twi();
		delay_twi();
		delay_twi();
		delay_twi();
		PORTB=0x00;
	}*/
	DDRD|=(1<<scl);
	delay_twi();
	DDRD|=(1<<sda);
	delay_twi();
}

volatile long int twi_read(void)
{
	volatile long int data=0;
	DDRD&=~(1<<sda);
	for (volatile unsigned char i=9; i>1; i--)
	{
		delay_twi();
		DDRD&=~(1<<scl);
		delay_twi();
		if ((PIND&(1<<sda))!=0)
		{
			data=data+(1<<(i-2));
		}
		DDRD|=(1<<scl);
		//data=(data<<1);
	} 
	delay_twi();
	return(data);
}

void twi_ackm(void)
{
	delay_twi();
	DDRD|=(1<<sda);
	delay_twi();
	DDRD&=~(1<<scl);
	delay_twi();
	DDRD|=(1<<scl);
	delay_twi();
	DDRD|=(1<<sda);
	delay_twi();
}
void twi_nackm(void)
{
	delay_twi();
	DDRD&=~(1<<sda);
	delay_twi();
	DDRD&=~(1<<scl);
	delay_twi();
	DDRD|=(1<<scl);
	delay_twi();
	DDRD|=(1<<sda);
	delay_twi();
}

void twi_stop(void)
{
	delay_twi();
	DDRD&=~(1<<scl);
	delay_twi();
	DDRD&=~(1<<sda);
	delay_twi();
}

volatile  signed long int read_signed(void)
{
	volatile unsigned int data=0;
	DDRD&=~(1<<sda);
	for (volatile unsigned char i=9; i>1; i--)
	{
		delay_twi();
		DDRD&=~(1<<scl);
		delay_twi();
		if ((PIND&(1<<sda))!=0)
		{
			data=data+(1<<(i-2));
		}
		DDRD|=(1<<scl);
		//data=(data<<1);
	} 
	
	twi_ackm();
	//data=data<<8;
	DDRD&=~(1<<sda);
	for (volatile unsigned char i=16; i>8; i--)
	{
		delay_twi();
		DDRD&=~(1<<scl);
		delay_twi();
		if ((PIND&(1<<sda))!=0)
		{
			data=data+(1<<(i-1));
		}
		DDRD|=(1<<scl);
	} 
	
	
//	data=0b1111111101101111;
	if ((data&0x8000)!=0)
	{
		return(data|0xFFFF0000);
	}
	else
	{
		return(data);
	}
}


/*void twi_transmit_array(volatile unsigned char a)
{
	delay_twi();
	DDRD|=(1<<sda);
	delay_twi();
	DDRD|=(1<<scl);
	delay_twi();
	volatile unsigned char b=a;
	while (a>0)
	{
		volatile unsigned char data=twi_out[b-a];
		for (volatile unsigned char i=8; i>0; i--)
		{
			if ((data&(1<<(i-1)))!=0)
			{
				DDRD&=~(1<<sda);
			}
			delay_twi();
			DDRD&=~(1<<scl);
			delay_twi();
			DDRD|=(1<<scl);
			delay_twi();
			DDRD|=(1<<sda);
			//delay_twi();
		}	 
		DDRD&=~(1<<sda);
			delay_twi();
		DDRD&=~(1<<scl);
		delay_twi();
		DDRD|=(1<<sda);
		DDRD|=(1<<scl);
		delay_twi();
		/*if (!(PIND&(1<<sda)))
		{
			return(true);
		}
		else
		{
			return(false);
		}
		a--;
	}	
	DDRD|=(1<<scl);
	delay_twi();
	DDRD|=(1<<sda);
	delay_twi();
	DDRD&=~(1<<scl);
	delay_twi();
	DDRD&=~(1<<sda);
	delay_twi();
	
}*/

