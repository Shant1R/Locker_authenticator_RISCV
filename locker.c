int main()
{

	int p1,p2,p3,p4,s1,s2;
	
	
	int c = 0; 
	int x = 0;
	int av1 = 0;
	int av2 = 0;
	int c_reg;
	int x_reg;
	int av1_reg;
	int av2_reg;
	
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
	
	while(1)
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

	}
	return 0;

}

