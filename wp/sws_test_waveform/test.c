
#include<stdio.h>
#include<math.h>

float T;
float value_to_write;
const float pi =3.1416;
float delta_t=0.01;
float t;
int value_to_write_bit;
//byte buffer_serial[26];
unsigned long currentMillis;
unsigned long previousMillis;
unsigned long interval;
unsigned long currentMillis_2;
unsigned long previousMillis_2;
unsigned long interval_2;
// word word_baseline; 
// word word_A_heart;
// word word_f_heart;
// word word_A_breathing;
// word word_f_breathing;
// word word_A1;
// word word_P1;
// word word_A2;
// word word_P2;
// word word_A3;
// word word_P3;
float baseline; 
float A_heart;
float f_heart;
float A_breathing;
float f_breathing;
float A1_heart;
float P1_heart;
float A2_heart;
float P2_heart;
float A3_heart;
float P3_heart;
float resolution_factor;
void loop(); 

unsigned long a = 0;


void main()
{
    baseline=1;
    A_heart=0;
    f_heart=1;
    A_breathing=0;
    f_breathing=0;
	
	resolution_factor=0.0022;  // per 10 bit
    t=0.01;
    A1_heart=1;
    P1_heart=0;
    A2_heart=0;
    P2_heart=0;
    A3_heart=0;
    P3_heart=0;	
    
    while(1)
    {
	    loop();
		//mdelay(1);
		a++;
    }	
}



void loop() 
{

    currentMillis = a;  //cpu当前的运行时间 
    
    if(currentMillis - previousMillis_2 >= interval_2) {   //10 毫秒进入一次
       previousMillis_2 = currentMillis;     
    
       T=1/f_heart;
       value_to_write=(3500)*sin(2*pi*t*f_heart);
    
         if (value_to_write<1000)
            {    
             value_to_write = 1000; 
            }
          
   //       if (value_to_write>2.24/resolution_factor) {
   //            value_to_write =  
   //         }
            
            if (t < (T-delta_t/10))
            {
             t=t+delta_t; 
            }
            else
            {
             t=0.01;
            }
            
            value_to_write_bit=(int) value_to_write;
            //analogWrite(DAC1, value_to_write_bit);    //设置dac的值    
			printf("%d \r\n", value_to_write_bit);
          //  delay(1);
            
    }
}
