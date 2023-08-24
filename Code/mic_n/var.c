const char tep_adc[2*90]={20,21,22,23,24,25,26,27,28,29,30,31,32,33,34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,
						228, 227, 226, 225, 223, 222, 221, 219, 218, 217, 215, 214, 212, 211, 209, 208, 206, 204, 203, 201, 199, 197, 195, 194, 192, 190, 188, 186, 184, 182, 180, 178, 176, 174, 172, 170, 168, 165, 163, 161, 159, 157, 155, 153, 150, 148, 146, 144, 142, 140, 138, 135, 133, 131, 129, 127, 125, 123, 121, 119, 117, 115, 113, 111, 109, 107, 105, 103, 101, 99, 98, 96, 94, 92, 91, 89, 87, 85, 84, 82, 81, 79, 78, 76, 75, 73, 72, 70, 69, 67, 66};

volatile unsigned char temp_temp;//текущее значение температуры

volatile unsigned char seconds;
volatile unsigned char minuts;
volatile unsigned long hours;

volatile unsigned char seconds_f;
volatile unsigned char minuts_f;
volatile unsigned long hours_f;

volatile unsigned char res_adc;

volatile unsigned char flag=0b1000011;

volatile unsigned char flag_copy;

volatile unsigned char filtr_to_all;//считаем 3 секунды, потом переключаем информацию на диспелее с засора на предыдущую 
volatile unsigned char run;
volatile unsigned char flag_two;

volatile unsigned long int press;//, temp;

volatile unsigned char temp_0;
volatile unsigned char aaaaa;
volatile unsigned int time_cloc;

volatile unsigned long filtr_to; 