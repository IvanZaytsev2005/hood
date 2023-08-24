void lcd_init(void)
{
/*
	delay_twi();
	delay_twi();
	delay_twi();
	
	delay_twi();
	delay_twi();
	delay_twi();*/
	
	delay_twi();
	delay_twi();
	delay_twi();
	
	delay_twi();
	delay_twi();
	delay_twi();
	
	twi_start();
	twi_transmit(adres_lcd);
	lcd_comand(0x33);		// Переход в 4-х битный режим
// 	delay_twi();
// 	delay_twi();
// 	delay_twi();
// 	delay_twi();
	
	delay_twi();
	delay_twi();
	delay_twi();
	delay_twi();		// Пауза после подачи питания
	lcd_comand(0x33);		// Переход в 4-х битный режим
	delay_twi();
// 	delay_twi();
// 	delay_twi();
// 	delay_twi();
// 	delay_twi();
// 	delay_twi();
// 	delay_twi();
	delay_twi();
	delay_twi();		// Задержка для выполнения команды
	lcd_comand(0x32);		// Переход в 4-х битный режим
	delay_twi();
	delay_twi();
// 	delay_twi();
// 	delay_twi();
// 	delay_twi();
// 	delay_twi();
// 	delay_twi();		// Задержка для выполнения команды
	//lcd_comand(0x80);		// Установка параметров
	lcd_comand(0x08);		// Выключаем дисплей
	lcd_comand(0x01);		// Очищаем дисплей
	lcd_comand(0x06);		// Устанавливаем режим ввода данных
	lcd_comand(0x28);

	lcd_comand(0x0C);		// Включаем дисплей с выбранным курсором
	//запись основных русских символов, встречающихся 3-4 раза
	lcd_add(16,0);
	lcd_add(0,1);
	lcd_add(8,2);
	lcd_add(32,3);
	lcd_add(80,4);
	lcd_add(24,5);
	twi_stop();
}

void print_time_full(void)
{
	twi_start();
	twi_transmit(adres_lcd);
	lcd_comand(1);
	lcd_add(64,6);
	lcd_add(72,7);
	
	
//	lcd_comand(0b10000000); //???
	lcd_out('B');
	lcd_out('P');
	lcd_out('E');
	lcd_out('M');
	lcd_out(1);
	
	lcd_out(' ');
	
	lcd_out('P');
	lcd_out('A');
	lcd_out(2);
	lcd_out('O');
	lcd_out('T');
	lcd_out(6);
	lcd_comand(0x80+0x40);
	
	lcd_out(7);
	lcd_out('C');
	lcd_out('T');
	lcd_out('A');
	lcd_out('H');
	lcd_out('O');
	lcd_out('B');
	lcd_out('K');
	lcd_out(0);
	twi_stop();
}

 void print_time_filtr(void)
 {
	 twi_start();
	twi_transmit(adres_lcd);
	lcd_comand(1);
	lcd_add(64,6);
	lcd_comand(1);
//	lcd_comand(0b10000000);
	lcd_out('B');
	lcd_out('P');
	lcd_out('E');
	lcd_out('M');
	lcd_out(1);

	lcd_out(' ');
	
	lcd_out('P');
	lcd_out('A');
	lcd_out(2);	
	lcd_out('O');
	lcd_out('T');
	lcd_out(6);
	
	lcd_comand(0b11000000);
	
	lcd_out(5);
	lcd_out(0);
	lcd_out(3);
	lcd_out('b');
	lcd_out('T');
	lcd_out('P');
	lcd_out('A');
	twi_stop();
 }
 
 void print_engin(void)
 {
	  twi_start();
	twi_transmit(adres_lcd);

	
	lcd_comand(1);
	//lcd_comand(0b10000000);
	
	lcd_add(48,6);
	lcd_add(56,7);
	
	lcd_comand(1);
	
	lcd_out(6);
	lcd_out('E');
	lcd_out('P');
	lcd_out('E');
	lcd_out(7);
	lcd_out('P');
	lcd_out('E');
	lcd_out('B');
	
	lcd_comand(0b11000000);
	
	lcd_out(4);
	lcd_out('B');
	lcd_out(0);
	lcd_out(7);
	lcd_out('A');
	lcd_out('T');
	lcd_out('E');
	lcd_out(3);
	lcd_out(1);	
	twi_stop();
 }
 
 void print_filtr(void)
 {
	twi_start();
	twi_transmit(adres_lcd);
	lcd_comand(1);
	delay_twi();
	lcd_add(40,6);
	
	
	
	lcd_out('H');
	lcd_out('E');
	lcd_out('O');
	lcd_out(2);
	lcd_out('X');
	lcd_out('O');
	lcd_out(4);
	lcd_out(0);
	lcd_out('M');
	lcd_out('A');
	
	lcd_comand(0b11000000);
	
	lcd_out(6);
	lcd_out('A');
	lcd_out('M');
	lcd_out('E');
	lcd_out('H');
	lcd_out('A');
	
	lcd_out(' ');
	
	lcd_out(5);
	lcd_out(0);
	lcd_out(3);
	lcd_out('b');
	lcd_out('T');
	lcd_out('P');
	lcd_out('A');
	
	twi_stop();
 }
 
 void print_decide(void)
 {
	 twi_start();
	twi_transmit(adres_lcd);
	lcd_comand(1);
	delay_twi();
	lcd_add(64,6);
	
	lcd_out('C');
	lcd_out(2);
	lcd_out('P');
	lcd_out('O');
	lcd_out('C');
	lcd_out(0);
	lcd_out('T');
	lcd_out('b');
	
	lcd_out(' ');
	
	lcd_out('B');
	lcd_out('P');
	lcd_out('E');
	lcd_out('M');
	lcd_out(1);
	
	lcd_comand(0b11000000);
	
	lcd_out('P');
	lcd_out('A');
	lcd_out(2);
	lcd_out('O');
	lcd_out('T');
	lcd_out(6);
	
	lcd_out(' ');
	
	lcd_out(5);
	lcd_out(0);
	lcd_out(3);
	lcd_out('b');
	lcd_out('T');
	lcd_out('P');
	lcd_out('A');
	
	lcd_out('?');
 }
 
/*
 void time_out(volatile unsigned char a, volatile unsigned char b, volatile unsigned char c)
 {
	 twi_start();
	 twi_stop();
	 twi_start();
	 twi_transmit(adres_lcd);
	 lcd_comand(0xC8);
	 lcd_out(0x30+(a%100)/10);
	 lcd_out(0x30+(a%10));
	 lcd_out(0b00111010);
	 lcd_out(0x30+(b%100)/10);
	 lcd_out(0x30+(b%10));
	 lcd_out(0b00111010);
	 lcd_out(0x30+(c%100)/10);
	 lcd_out(0x30+(c%10));
	 twi_stop();
 }*/
 
/*

 }*/
 
 
 void lcd_comand(volatile unsigned char data)
{
	twi_transmit((data&0b11110000)|0b00000100);
	twi_transmit((data&0b11110000)&0b11111011);	
	twi_transmit(((data&0b1111)*16)|0b00000100);
	twi_transmit(((data&0b1111)*16)&0b11111011);
}

void lcd_out(volatile unsigned char data)
{
	twi_transmit((data&0b11110000)|0b00000101);
	twi_transmit(((data&0b11110000)&0b11111011)|0b1);	
	twi_transmit(((data&0b1111)<<4)|0b00000101);
	twi_transmit((((data&0b1111)<<4)&0b11111011)|0b1);
}

void lcd_data(volatile unsigned char data)
{
	twi_transmit((data&0b11110000)|0b00000101);
	twi_transmit(((data&0b11110000)&0b11111011)|0b1);	
	twi_transmit(((data&0b1111)<<4)|0b00000101);
	twi_transmit((((data&0b1111)<<4)&0b11111011)|0b1);
}

void lcd_add(volatile unsigned char addr, volatile unsigned char shift)
{
	lcd_comand(0x40+shift*8);
	//twi_start();
	//twi_transmit(adres_lcd);
	for(volatile unsigned char i=0; i<8; i++)	
	{
		lcd_data(alpfa[addr+i]);
	}	
	//twi_stop();
	lcd_comand(0b10000000);
}

 void time_hour(volatile unsigned long int a)
 {
	 //data=10006;
	 twi_start();
	 twi_transmit(adres_lcd);
	 lcd_comand(0xca);

	 lcd_out(0x30+(a%1000000)/100000);
	 lcd_out(0x30+(a%100000)/10000);
	 lcd_out(0x30+(a%10000)/1000);
	 lcd_out(0x30+(a%1000)/100);
	 lcd_out(0x30+(a%100)/10);
	 lcd_out(0x30+(a%10));
	 twi_stop();
 }	 

/*
void time_hour(volatile unsigned long int data)
{
	twi_start();
	 twi_transmit(adres_lcd);
	 lcd_comand(1);
	//for (volatile char i=1; i<12; i++)
	//{
		lcd_out(0x30+(data%10));
		//data=data/10;
	//}
	twi_stop();*/
//}