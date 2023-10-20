# Locker_authenticator_RISCV

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/d3e27299-3bad-4e8b-b5df-02495fb6f521)


Under this repository, we have done a step by step implementation to make a passcode based authentication system for lockers based in RISCV Architecture summarizes the progress made towards the completion. 

## OBJECTIVE 

The core objective of the project undertaken is to develop a RISCV core to perform authentication operation of a locker and check for whether the storage space is available. The system upon the entry of correct passcode will look if the storage space is available, if yes, the system turns on the green LED. In case of wrong passcode, the system flags the occurance with a red LED.

## PROCEDURE

The locker authentication project is based on simple passcode. We have defined a 4 bit passcode, ```1101```. To take the passcode inputs, we will implement push down switches, ie we have an array of 4 switches. When the correct passcode is entered we move ahead with the space verification. In case of wrong passcode, the system flags it. In the project, we have taken the locker to have two comparments. Each compartment is one storage unit. To identify if a storage unit is available, we will integrate obstcle detection, using proximity sensors. Thus, in the given case, two units of proximity sensors are required. Henceforth, we have four cases at our hands, both available, either one avaliable and none. The following will be flagged using corresponding LEDs. 

## BLOCK DIAGRAM  

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/a31842ac-9181-4d9c-97ac-dc7d81b740d3)


## CODE

***Testing***
- We first compile the C code using gcc and check the expected outcomes for testcases.

  ```bash
  gcc locker.c
  ./a.out
  ```

 ![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/85b759cc-87ff-49d4-9cc2-bad9282c8c7f)


- After this, we define the inputs and outputs using ```asm``` to link the assemply level inputs and outputs and store them over variables in C.

***C Code***

C code implementing the above block diagram.

```bash
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
	
	c_reg = c*64;
	x_reg = x*128;
	av1_reg = av1*256;
	av2_reg = av2*512;
	
	asm volatile(
    	"or x30, x30, %0\n\t"  
    	"or x30, x30, %1\n\t"  
    	"or x30, x30, %2\n\t"
    	"or x30, x30, %3\n\t"  
    	:
    	: "r" (c_reg), "r" (x_reg), "r" (av1_reg), "r" (av2_reg)
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
    		"or x30, x30, %0\n\t"  
    		"or x30, x30, %1\n\t"  
    		"or x30, x30, %2\n\t"
    		"or x30, x30, %3\n\t"  
    		:
    		: "r" (c_reg), "r" (x_reg), "r" (av1_reg), "r" (av2_reg)
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
    		"or x30, x30, %0\n\t"  
    		"or x30, x30, %1\n\t"  
    		"or x30, x30, %2\n\t"
    		"or x30, x30, %3\n\t"  
    		:
    		: "r" (c_reg), "r" (x_reg), "r" (av1_reg), "r" (av2_reg)
		: "x30" 
		);

	}

	}
	return 0;

}


```

***Assembly Code***

Compile the C code using RISCV-V GNU Toolchain and dump the assembly code into ```locker.o```, the contents of which are copied into a .txt file for easy veiwing.

```bash

out:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <main>:
   10074:	fb010113          	add	sp,sp,-80
   10078:	04812623          	sw	s0,76(sp)
   1007c:	05010413          	add	s0,sp,80
   10080:	fe042623          	sw	zero,-20(s0)
   10084:	fe042423          	sw	zero,-24(s0)
   10088:	fe042223          	sw	zero,-28(s0)
   1008c:	fe042023          	sw	zero,-32(s0)
   10090:	fec42783          	lw	a5,-20(s0)
   10094:	00679793          	sll	a5,a5,0x6
   10098:	fcf42e23          	sw	a5,-36(s0)
   1009c:	fe842783          	lw	a5,-24(s0)
   100a0:	00779793          	sll	a5,a5,0x7
   100a4:	fcf42c23          	sw	a5,-40(s0)
   100a8:	fe442783          	lw	a5,-28(s0)
   100ac:	00879793          	sll	a5,a5,0x8
   100b0:	fcf42a23          	sw	a5,-44(s0)
   100b4:	fe042783          	lw	a5,-32(s0)
   100b8:	00979793          	sll	a5,a5,0x9
   100bc:	fcf42823          	sw	a5,-48(s0)
   100c0:	fdc42783          	lw	a5,-36(s0)
   100c4:	fd842703          	lw	a4,-40(s0)
   100c8:	fd442683          	lw	a3,-44(s0)
   100cc:	fd042603          	lw	a2,-48(s0)
   100d0:	00ff6f33          	or	t5,t5,a5
   100d4:	00ef6f33          	or	t5,t5,a4
   100d8:	00df6f33          	or	t5,t5,a3
   100dc:	00cf6f33          	or	t5,t5,a2
   100e0:	001f7793          	and	a5,t5,1
   100e4:	fcf42623          	sw	a5,-52(s0)
   100e8:	002f7793          	and	a5,t5,2
   100ec:	fcf42423          	sw	a5,-56(s0)
   100f0:	004f7793          	and	a5,t5,4
   100f4:	fcf42223          	sw	a5,-60(s0)
   100f8:	008f7793          	and	a5,t5,8
   100fc:	fcf42023          	sw	a5,-64(s0)
   10100:	010f7793          	and	a5,t5,16
   10104:	faf42e23          	sw	a5,-68(s0)
   10108:	020f7793          	and	a5,t5,32
   1010c:	faf42c23          	sw	a5,-72(s0)
   10110:	fcc42783          	lw	a5,-52(s0)
   10114:	0e078e63          	beqz	a5,10210 <main+0x19c>
   10118:	fc842783          	lw	a5,-56(s0)
   1011c:	0e078a63          	beqz	a5,10210 <main+0x19c>
   10120:	fc442783          	lw	a5,-60(s0)
   10124:	0e079663          	bnez	a5,10210 <main+0x19c>
   10128:	fc042783          	lw	a5,-64(s0)
   1012c:	0e078263          	beqz	a5,10210 <main+0x19c>
   10130:	fbc42783          	lw	a5,-68(s0)
   10134:	02078263          	beqz	a5,10158 <main+0xe4>
   10138:	fb842783          	lw	a5,-72(s0)
   1013c:	00078e63          	beqz	a5,10158 <main+0xe4>
   10140:	00100793          	li	a5,1
   10144:	fef42623          	sw	a5,-20(s0)
   10148:	fe042423          	sw	zero,-24(s0)
   1014c:	fe042223          	sw	zero,-28(s0)
   10150:	fe042023          	sw	zero,-32(s0)
   10154:	0680006f          	j	101bc <main+0x148>
   10158:	fbc42783          	lw	a5,-68(s0)
   1015c:	02078063          	beqz	a5,1017c <main+0x108>
   10160:	00100793          	li	a5,1
   10164:	fef42623          	sw	a5,-20(s0)
   10168:	fe042423          	sw	zero,-24(s0)
   1016c:	fe042223          	sw	zero,-28(s0)
   10170:	00100793          	li	a5,1
   10174:	fef42023          	sw	a5,-32(s0)
   10178:	0440006f          	j	101bc <main+0x148>
   1017c:	fb842783          	lw	a5,-72(s0)
   10180:	02078063          	beqz	a5,101a0 <main+0x12c>
   10184:	00100793          	li	a5,1
   10188:	fef42623          	sw	a5,-20(s0)
   1018c:	fe042423          	sw	zero,-24(s0)
   10190:	00100793          	li	a5,1
   10194:	fef42223          	sw	a5,-28(s0)
   10198:	fe042023          	sw	zero,-32(s0)
   1019c:	0200006f          	j	101bc <main+0x148>
   101a0:	00100793          	li	a5,1
   101a4:	fef42623          	sw	a5,-20(s0)
   101a8:	fe042423          	sw	zero,-24(s0)
   101ac:	00100793          	li	a5,1
   101b0:	fef42223          	sw	a5,-28(s0)
   101b4:	00100793          	li	a5,1
   101b8:	fef42023          	sw	a5,-32(s0)
   101bc:	fec42783          	lw	a5,-20(s0)
   101c0:	00679793          	sll	a5,a5,0x6
   101c4:	fcf42e23          	sw	a5,-36(s0)
   101c8:	fe842783          	lw	a5,-24(s0)
   101cc:	00779793          	sll	a5,a5,0x7
   101d0:	fcf42c23          	sw	a5,-40(s0)
   101d4:	fe442783          	lw	a5,-28(s0)
   101d8:	00879793          	sll	a5,a5,0x8
   101dc:	fcf42a23          	sw	a5,-44(s0)
   101e0:	fe042783          	lw	a5,-32(s0)
   101e4:	00979793          	sll	a5,a5,0x9
   101e8:	fcf42823          	sw	a5,-48(s0)
   101ec:	fdc42783          	lw	a5,-36(s0)
   101f0:	fd842703          	lw	a4,-40(s0)
   101f4:	fd442683          	lw	a3,-44(s0)
   101f8:	fd042603          	lw	a2,-48(s0)
   101fc:	00ff6f33          	or	t5,t5,a5
   10200:	00ef6f33          	or	t5,t5,a4
   10204:	00df6f33          	or	t5,t5,a3
   10208:	00cf6f33          	or	t5,t5,a2
   1020c:	0680006f          	j	10274 <main+0x200>
   10210:	fe042623          	sw	zero,-20(s0)
   10214:	00100793          	li	a5,1
   10218:	fef42423          	sw	a5,-24(s0)
   1021c:	fe042223          	sw	zero,-28(s0)
   10220:	fe042023          	sw	zero,-32(s0)
   10224:	fec42783          	lw	a5,-20(s0)
   10228:	00679793          	sll	a5,a5,0x6
   1022c:	fcf42e23          	sw	a5,-36(s0)
   10230:	fe842783          	lw	a5,-24(s0)
   10234:	00779793          	sll	a5,a5,0x7
   10238:	fcf42c23          	sw	a5,-40(s0)
   1023c:	fe442783          	lw	a5,-28(s0)
   10240:	00879793          	sll	a5,a5,0x8
   10244:	fcf42a23          	sw	a5,-44(s0)
   10248:	fe042783          	lw	a5,-32(s0)
   1024c:	00979793          	sll	a5,a5,0x9
   10250:	fcf42823          	sw	a5,-48(s0)
   10254:	fdc42783          	lw	a5,-36(s0)
   10258:	fd842703          	lw	a4,-40(s0)
   1025c:	fd442683          	lw	a3,-44(s0)
   10260:	fd042603          	lw	a2,-48(s0)
   10264:	00ff6f33          	or	t5,t5,a5
   10268:	00ef6f33          	or	t5,t5,a4
   1026c:	00df6f33          	or	t5,t5,a3
   10270:	00cf6f33          	or	t5,t5,a2
   10274:	e6dff06f          	j	100e0 <main+0x6c>

```

- The assembly code contains various instructions. The list of the individual instruction can be generated by using ```instruction_counter.py```. The list generated for our code is as follows.
```bash
Number of different instructions: 10
List of unique instructions:
j
and
or
bnez
add
li
beqz
lw
sw
sll

```

## Word of Thanks
I would take this opportunity to sciencerly thank Mr. Kunal Gosh(Founder/VSD) for helping me out to complete this flow smoothly.

## Acknowledgement
- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Skywater Foundry
- OpenAI Chatgpt
- Alwin Shaju, MTech, IIITB
- Emil Jayanth Lal, Mtech, IIITB
- Mayank Kabra, iMtech, IIITB

## Reference
- https://github.com/The-OpenROAD-Project/OpenSTA.git
- https://github.com/kunalg123
- https://www.vsdiat.com
- https://github.com/SakethGajawada/RISCV-GNU


