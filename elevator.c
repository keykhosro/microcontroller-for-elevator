#include<LPC213x.h>
//#include<stdio.h>

int flr = 0;
int i=0;
int door =1;




// this function makes mile second delay

void delay_ms ( int d ) {
	for( i=0 ; i<=16667*d ; i=i+1);
}



// this function converts bcd to 7 seg 
int bcd_to_7seg(int bcd){

	
switch (bcd) {
	case 0:
		return 0x0000003F;
	case 1:
		return 0x00000006;
	case 2:
		return 0x0000005B;
	case 3:
		return 0x0000004F;
	case 4:
		return 0x00000066;
	case 5:
		return 0x0000006D;
	case 6:
		return 0x0000007D;
	case 7:
		return 0x00000007;
	case 8:
		return 0x0000007F;
	case 9:
		return 0x0000006F;
	default:
		return 0x0000004F;
			
							}	
	
}

// this function show the value of flr that is a global variable and represents the floor of elevator into 7 seg and output it. 

void set_DC_7Seg(void ){

	
	//int yekan = (int) (flr * 1);
	int yekan = (int) flr;
	//int dahgan = 0;
	
	int yekan_seg;
	switch (yekan) { // bcd to 7 seg function
	case 0:
		yekan_seg= 0x0000003F;
		break;
	
	case 1:
		yekan_seg=0x00000006;
		break;
	case 2:
		yekan_seg=0x0000005B;
		break;
	case 3:
		yekan_seg=0x0000004F;
		break;
	case 4:
		yekan_seg=0x00000066;
		break;
	case 5:
		yekan_seg=0x0000006D;
		break;
	case 6:
		yekan_seg=0x0000007D;
		break;
	case 7:
		yekan_seg=0x00000007;
		break;
	case 8:
		yekan_seg=0x0000007F;
		break;
	case 9:
		yekan_seg=0x0000006F;
		break;
	default:
		yekan_seg=0x0000006F;}
	//int dahgan_seg;
	int dahgan_seg=0x0000003F;
	
	delay_ms(2);
	IO1CLR = (1 << 24) | (0x0000007f << 16); // clear the last number
	IO1SET = (1 << 23) | (yekan_seg << 16); // out put new number into 7 seg
	
}


// this function uses to send commands to lcd
void LCD_CMD( char command ){
	IO0PIN = ((IO0PIN & 0xFFFF00FF ) | ( command <<8) ) ;
	IO0SET = 0x00000040 ;
	IO0CLR = 0x00000030 ;
	delay_ms (2) ;
	IO0CLR = 0x00000040 ;
	delay_ms (5) ;
}
// this function uses to start lcd clear the whole 16*2 spots and set its write pointer to beginning of first line
void LCD_INIT( void ){
	
	delay_ms (20) ;
	LCD_CMD( 0x38 ) ;
	LCD_CMD( 0x0C ) ;
	LCD_CMD( 0x06 ) ;
	LCD_CMD( 0x01 ) ;
	LCD_CMD( 0x80 ) ;
}

//this function is similar to LCD_CMD the different is that this one sends massage we want 
//to show on lcd and last one uses to send commands
void LCD_CHAR ( char msg ){
	IO0PIN = ((IO0PIN & 0xFFFF00F0 ) | ( msg <<8) ) ;
	IO0SET = 0x00000050 ;
	IO0CLR = 0x00000020 ;
	delay_ms (2) ;
	IO0CLR = 0x00000040 ;
	delay_ms (5) ;
}


// this function print 'welcome' on lcd
void welcome(){
	LCD_INIT ( ) ; // first use init to start and clear the last massage and bring its write pointer to first spot of 2*16



	LCD_CHAR( 'w') ;     // then we send characters one by one
	LCD_CHAR( 'e') ;
	LCD_CHAR( 'l') ;
	LCD_CHAR( 'c') ;
	LCD_CHAR( 'o') ;
	LCD_CHAR( 'm') ;
	LCD_CHAR( 'e') ;
}


//this function print 'going down' on lcd
void going_down(){
	LCD_INIT ( ) ;     // first use init to start and clear the last massage and bring its write pointer to first spot of 2*16



	LCD_CHAR( 'g') ;    // then we send characters one by one
	LCD_CHAR( 'o') ;
	LCD_CHAR( 'i') ;
	LCD_CHAR( 'n') ;
	LCD_CHAR( 'g') ;
	LCD_CHAR( ' ') ;
	LCD_CHAR( 'd') ;
	LCD_CHAR( 'o') ;
	LCD_CHAR( 'w') ;
	LCD_CHAR( 'n') ;
}


//this function print 'going up' on lcd
void going_up(){
	LCD_INIT ( ) ;    // first use init to start and clear the last massage and bring its write pointer to first spot of 2*16



	LCD_CHAR( 'g') ;    // then we send characters one by one
	LCD_CHAR( 'o') ;
	LCD_CHAR( 'i') ;
	LCD_CHAR( 'n') ;
	LCD_CHAR( 'g') ;
	LCD_CHAR( ' ') ;
	LCD_CHAR( 'u') ;
	LCD_CHAR( 'p') ;
}



//this function print 'over weight' on lcd
void over_weight(){
	LCD_INIT ( ) ;     // first use init to start and clear the last massage and bring its write pointer to first spot of 2*16



	LCD_CHAR( 'o') ;     // then we send characters one by one
	LCD_CHAR( 'v') ;
	LCD_CHAR( 'e') ;
	LCD_CHAR( 'r') ;
	LCD_CHAR( ' ') ;
	LCD_CHAR( 'w') ;
	LCD_CHAR( 'e') ;
	LCD_CHAR( 'i') ;
	LCD_CHAR( 'g') ;
	LCD_CHAR( 'h') ;
	LCD_CHAR( 't') ;
}

// i chose the MSB of ADC signal of weight to this function and use it to check if the weight is more than capacity or not
int check_weight(){
	int temp=0x0;
	int a;
	temp=IO0PIN &0x40000000; //first i read the MSB

	if(temp==0x40000000) // then if msb=1 over weight and msb=0 is normal 
		a=1;
	else
		a=0;
	return a; // i return a than is 0 or 1 for compare and allow to main function
}


// this function is foor door sensor (( red led )) to show the door pose to user by turning a led on and off
void check_door(){
	if(door == 1)
		IO1SET |=(1<<26);
	if(door == 0)
		IO1CLR =(1<<26);
}
		

// this function observes floor keys and check which one set to low. so it finds the desire destination of user
int check_dst(){
	int temp;
	int dest;
	temp=IO1PIN&(0x78000000);
	temp=temp>>27;
	switch (temp) {
		case 0x0000000F:
		dest= flr;
		break;
	case 0x0000000E:
		dest= 0;
		break;
	
	case 0x0000000D:
		dest=1;
		break;
	case 0x0000000B:
		dest=2;
		break;
	case 0x00000007:
		dest=3;
		break;
	default:
		dest=8;}
	return dest;
	
}

//this is the core of elevator , this function decides to first go to which floor based on current floor ,
//destination elevator going to reach , is elevator going up or down and the new interrupt destination
//this is a recursive function.

void elevator(int destination){
	int hi=destination;
	int dst;
	int a;
	//int temp;
	int flag=0;
	delay_ms(200);
	door=0;
	check_door();
	if(hi>flr){
		going_up();
		while(flr<hi){
			
			for(i=0;i<444400;i++){
				delay_ms(40);
				dst=check_dst();
				delay_ms(40);
				if((dst!=flr)&&(flag==0)){
					flag=1;
					if((dst>flr)&&(dst<hi)){
						
						elevator(dst);
						a=check_weight();
						if(a!=0)
							over_weight();
						while(a!=0){
							a=check_weight();}
						//welcome();  // print welcome 
							
						elevator(hi);
						break;
					}
					else{
					//	temp=flr;
						elevator(hi);
						a=check_weight();
						if(a!=0)
							over_weight();
						while(a!=0){
							a=check_weight();}
						//welcome();  // print welcome 
						elevator(dst);
						break;
					}
				
				}
			
			}
		//	if(dst<temp){
		//		break;}
			if(flr<hi){
				flr=flr+1;
				set_DC_7Seg();}
		}
		door=1;
		check_door();
		welcome();
		delay_ms(10);
		
	}
	else if(hi==flr){
		door=1;
		check_door();
		welcome();
		delay_ms(100);
	}
	else if(hi<flr){
		going_down();
		while(flr>hi){
			
			for(i=0;i<44400;i++){
				delay_ms(40);
				dst=check_dst();
				delay_ms(40);
				if((dst!=flr)&&(flag==0)){
					flag==1;
					if((dst<flr)&&(dst>hi)){
						elevator(dst);
						a=check_weight();
						if(a!=0)
							over_weight();
						while(a!=0){
							a=check_weight();}
						//welcome();  // print welcome 
						elevator(hi);
						break;
					}
					else{
						//temp=flr;
						elevator(hi);
						a=check_weight();
						if(a!=0)
							over_weight();
						while(a!=0){
							a=check_weight();}
						//welcome();  // print welcome 
						elevator(dst);
						break;
					}
				
				}
			
			}
			//if(dst>temp){
			//	break;}
			if(flr>hi){
				flr=flr-1;
				set_DC_7Seg();}
		}
		door=1;
		check_door();
		welcome();
		delay_ms(10);
		
	}
}




// this is our interrupt
// when the pin set to low from high it actives and check new interrupt destination and start recursive function
__irq void EXT1_ISR(void){
	
	int dst;
	
	dst=check_dst();
		
	elevator(dst);
	
	EXTINT = EXTINT | (1<<1);// turn of the interrupt flag
	VICVectAddr = 0; // go back to main program or where it left
	
}


__irq void EXT2_ISR(void){
	
	int a;
	a=check_weight();
	if(a!=0)
		over_weight();
	while(a!=0){
			
		a=check_weight();}
	//dst=check_dst();
		
	//elevator(dst);
	
	EXTINT = EXTINT | (1<<2);
	VICVectAddr = 0;
	
}


// this is ADC function 

//float do_adc(){
//	int result;
//	float voltage;
//	AD0CR = AD0CR | (1<<24);  ////// start ADC
//	while(!(AD0DR & 0x80000000));  // check DONE bit 
//		result = AD0DR;
//		result = (result >>6);
//		result = (result & 0x000003FF); ?? extract bit 15:8
//		voltage = ( (result/1023.0) * 3.3 );
//	return voltage;
//}





int main ( void ) {
	PINSEL0 = 0x000000C0 ; // interupt pin and others GPIO
	//PINSEL1 = 0x10000000 ;
	PINSEL1=0x0; // all I/O
	PINSEL2 = 0;  // all I/O
	//PCONP |=  0X00001000;   //select adc 0 bit 12
	//AD0CR &=  0X00000000;
	//AD0INTEN &= 0x00000000; //Completion of a conversion on ADC channel 0 will not generate an interrupt.
	
	IO1DIR = 0x05ff0000;
	IO0DIR = 0x0000FFF0 ;
	//AD0CR = 0x00200408; // select AD0.3 and the clc rate and bits
	
	EXTMODE = 0x06;  // edge sensitive interrupts 
	
	EXTPOLAR = 0x06;  // falling edges sensitive
	
	
	VICIntSelect &= ~( (1<<15) | (1<<16) ); // select IRQ15 , IRQ16
	
	VICVectCntl0 = 0x20 |15;
	
	VICVectCntl1 = 0x20 |16;
	
	
	VICVectAddr0 = (unsigned) EXT1_ISR ;
	VICVectAddr1 = (unsigned) EXT2_ISR ;
	
	VICIntEnable |= ( (1<<15) | (1<<16) ) ; // enable interrupts
	
	EXTINT &= ~( ( 1<<1) | (1<< 2)); // external interrupts
	
	
	
	
	
	int dst;
	int a;
	//int temp;
	//int itrp;
	//int j=0;
	//int flag=0;
	//int floor=0x5;


	
	LCD_INIT ( ) ; // start the LED
	
	welcome();  // print welcome 
	set_DC_7Seg();  // print current floor in 7 seg
	check_door();  // show door sensor LED
	while(1){
		a=check_weight();
		if(a!=0)
			over_weight();
		while(a!=0){
			
			a=check_weight();} //// dont work when over weight
		welcome();  // print welcome 
		while(a==0){
			a=check_weight();
			dst=check_dst();
					if(dst!=flr){
			elevator(dst);}}
		//weight=do_adc();
		//while(weight>0.3){
			//over_weight();
			//weight=do_adc();}
			
		//over_weight();
		set_DC_7Seg();
		check_door();
		//over_weight();
			
		
	}
}
