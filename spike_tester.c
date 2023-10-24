#include <stdio.h>

int main()
{

	int testing;
	int p1,p2,p3,p4,s1,s2;
	
	
	int c = 0; 
	int x = 0;
	int av1 = 0;
	int av2 = 0;
	int c_reg;
	int x_reg;
	int av1_reg;
	int av2_reg;
	
	int ch1,ch2,ch3,ch4; //spike checkers
	int mask = 0xFFFFFC3F; 
	
	c_reg = c*64;
	x_reg = x*128;
	av1_reg = av1*256;
	av2_reg = av2*512;
	
	asm volatile(
	"and x30, x30, %4\n\t"
    	"or x30, x30, %0\n\t"  
    	"or x30, x30, %1\n\t"  
    	"or x30, x30, %2\n\t"
    	"or x30, x30, %3\n\t"  
    	:
    	: "r" (c_reg), "r" (x_reg), "r" (av1_reg), "r" (av2_reg), "r"(mask)
	: "x30"
	);
	
	for (int z = 0;z<=10;z++)
	//while(1)
	{
		
		
		asm volatile(
		"andi %0, x30, 0x01\n\t"
		: "=r" (p1)
		:
		:);
		
		
		asm volatile(
		"andi %0, x30, 0x02\n\t"
		: "=r" (p2)
		:
		:);
		

		asm volatile(
		"andi %0, x30, 0x04\n\t"
		: "=r" (p3)
		:
		:);

		asm volatile(
		"andi %0, x30, 0x08\n\t"
		: "=r" (p4)
		:
		:);

		asm volatile(
		"andi %0, x30, 0x10\n\t"
		: "=r" (s1)
		:
		:);

		asm volatile(
		"andi %0, x30, 0x20\n\t"
		: "=r" (s2)
		:
		:);
		
		p1=1;
		p2=1;
		p3=0;
		p4=1;
		s1=0;
		s2=1;
	
		if( p1 && p2 && (!p3) && p4 )  //locker password --> 1101
		{

			if (s1 && s2)
			{
				c=1;
				x=0;
				av1=0;
				av2=0;
				
	
			}
			else if (s1)
			{
				c=1;
				x=0;
				av1=0;
				av2=1;
				
			}
			else if (s2)
			{
				c=1;
				x=0;
				av1=1;
				av2=0;
			}
			else 
			{
				c=1;
				x=0;
				av1=1;
				av2=1;
			}
		
			c_reg = c*64;
			x_reg = x*128;
			av1_reg = av1*256;
			av2_reg = av2*512;
	
			asm volatile(
			"and x30, x30, %4\n\t"
    			"or x30, x30, %0\n\t"  
    			"or x30, x30, %1\n\t"  
    			"or x30, x30, %2\n\t"
    			"or x30, x30, %3\n\t"  
    			:
    			: "r" (c_reg), "r" (x_reg), "r" (av1_reg), "r" (av2_reg), "r"(mask)
			: "x30"
			);
	
	
		}	
		else
		{
			c=0;
			x=1;
			av1=0;
			av2=0;
			
			c_reg = c*64;
			x_reg = x*128;
			av1_reg = av1*256;
			av2_reg = av2*512;
	
			asm volatile(
			"and x30, x30, %4\n\t"
    			"or x30, x30, %0\n\t"  
    			"or x30, x30, %1\n\t"  
    			"or x30, x30, %2\n\t"
    			"or x30, x30, %3\n\t"  
    			:
    			: "r" (c_reg), "r" (x_reg), "r" (av1_reg), "r" (av2_reg), "r"(mask)
			: "x30"
			);
	
		}
		
		printf("passcode = %d%d%d%d\n",p1,p2,p3,p4);
		printf("lockers = %d%d\n",s1,s2);
		printf("correct = %d, wrong =%d, Avail_1=%d, Avail_2=%d\n",c,x,av1,av2);
		
		asm volatile(
    		"addi %0, x30, 0\n\t"
    		:"=r"(testing)
    		:
    		:"x30"
    		);
    		printf("outcome = %d\n",testing);
	

	}
	return 0;

}


