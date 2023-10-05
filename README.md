# Locker_authenticator_RISCV
Under this repo, we have done a step by step implementation to make a passcode based authentication system for lockers based in RISCV Architecture summarizes the progress made towards the completion. 

## OBJECTIVE 

The core objective of the project undertaken is to develop a RISCV core to perform authentication operation of a locker and check for whether the storage space is available. The system upon the entry of correct passcode will look if the storage space is available, if yes, the system turns on the green LED. In case of wrong passcode, the system flags the occurance with a red LED.

## PROCEDURE

The locker authentication project is based on simple passcode. We have defined a 4 bit passcode, ```1101```. To take the passcode inputs, we will implement push down switches, ie we have an array of 4 switches. When the correct passcode is entered we move ahead with the space verification. In case of wrong passcode, the system flags it. In the project, we have taken the locker to have two comparments. Each compartment is one storage unit. To identify if a storage unit is available, we will integrate obstcle detection, using proximity sensors. Thus, in the given case, two units of proximity sensors are required. Henceforth, we have four cases at our hands, both available, either one avaliable and none. The following will be flagged using corresponding LEDs. 

## BLOCK DIAGRAM  

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
```bash
#include <stdio.h>
void read();
void authenticate();
	
int main()
{
	while(1)
	{
		read();
	}
	return 0;

}

void read()
{
	
	authenticate();
}

void authenticate()
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
	
	asm(
    	"or x30, x30, %0\n\t"  
    	"or x30, x30, %1\n\t"  
    	"or x30, x30, %2\n\t"
    	"or x30, x30, %3\n\t"  
    	: "=r" (c_reg), "=r" (x_reg), "=r" (av1_reg), "=r" (av2_reg));
	
		
	asm(
	"andi %0, x30, 0x01\n\t"
	: "=r" (p1));
	
	asm(
	"andi %0, x30, 0x02\n\t"
	: "=r" (p2));

	asm(
	"andi %0, x30, 0x04\n\t"
	: "=r" (p3));

	asm(
	"andi %0, x30, 0x08\n\t"
	: "=r" (p4));

	asm(
	"andi %0, x30, 0x10\n\t"
	: "=r" (s1));

	
	asm(
	"andi %0, x30, 0x20\n\t"
	: "=r" (s2));
	
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
	
		asm(
    		"or x30, x30, %0\n\t"  
    		"or x30, x30, %1\n\t"  
    		"or x30, x30, %2\n\t"
    		"or x30, x30, %3\n\t"  
    		: "=r" (c_reg), "=r" (x_reg), "=r" (av1_reg), "=r" (av2_reg));
		
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
	
		asm(
    		"or x30, x30, %0\n\t"  
    		"or x30, x30, %1\n\t"  
    		"or x30, x30, %2\n\t"
    		"or x30, x30, %3\n\t"  
    		: "=r" (c_reg), "=r" (x_reg), "=r" (av1_reg), "=r" (av2_reg));
	}
}


```

***Assembly Code***

```bash
locker.o:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <main>:
   0:	ff010113          	add	sp,sp,-16
   4:	00112623          	sw	ra,12(sp)
   8:	00812423          	sw	s0,8(sp)
   c:	01010413          	add	s0,sp,16

00000010 <.L2>:
  10:	00000097          	auipc	ra,0x0
  14:	000080e7          	jalr	ra # 10 <.L2>
  18:	ff9ff06f          	j	10 <.L2>

0000001c <read>:
  1c:	ff010113          	add	sp,sp,-16
  20:	00112623          	sw	ra,12(sp)
  24:	00812423          	sw	s0,8(sp)
  28:	01010413          	add	s0,sp,16
  2c:	00000097          	auipc	ra,0x0
  30:	000080e7          	jalr	ra # 2c <read+0x10>
  34:	00000013          	nop
  38:	00c12083          	lw	ra,12(sp)
  3c:	00812403          	lw	s0,8(sp)
  40:	01010113          	add	sp,sp,16
  44:	00008067          	ret

00000048 <authenticate>:
  48:	fb010113          	add	sp,sp,-80
  4c:	04812623          	sw	s0,76(sp)
  50:	05010413          	add	s0,sp,80
  54:	fe042623          	sw	zero,-20(s0)
  58:	fe042423          	sw	zero,-24(s0)
  5c:	fe042223          	sw	zero,-28(s0)
  60:	fe042023          	sw	zero,-32(s0)
  64:	fec42783          	lw	a5,-20(s0)
  68:	00679793          	sll	a5,a5,0x6
  6c:	fcf42e23          	sw	a5,-36(s0)
  70:	fe842783          	lw	a5,-24(s0)
  74:	00779793          	sll	a5,a5,0x7
  78:	fcf42c23          	sw	a5,-40(s0)
  7c:	fe442783          	lw	a5,-28(s0)
  80:	00879793          	sll	a5,a5,0x8
  84:	fcf42a23          	sw	a5,-44(s0)
  88:	fe042783          	lw	a5,-32(s0)
  8c:	00979793          	sll	a5,a5,0x9
  90:	fcf42823          	sw	a5,-48(s0)
  94:	00cf6f33          	or	t5,t5,a2
  98:	00df6f33          	or	t5,t5,a3
  9c:	00ef6f33          	or	t5,t5,a4
  a0:	00ff6f33          	or	t5,t5,a5
  a4:	fcc42e23          	sw	a2,-36(s0)
  a8:	fcd42c23          	sw	a3,-40(s0)
  ac:	fce42a23          	sw	a4,-44(s0)
  b0:	fcf42823          	sw	a5,-48(s0)
  b4:	001f7793          	and	a5,t5,1
  b8:	fcf42623          	sw	a5,-52(s0)
  bc:	002f7793          	and	a5,t5,2
  c0:	fcf42423          	sw	a5,-56(s0)
  c4:	004f7793          	and	a5,t5,4
  c8:	fcf42223          	sw	a5,-60(s0)
  cc:	008f7793          	and	a5,t5,8
  d0:	fcf42023          	sw	a5,-64(s0)
  d4:	010f7793          	and	a5,t5,16
  d8:	faf42e23          	sw	a5,-68(s0)
  dc:	020f7793          	and	a5,t5,32
  e0:	faf42c23          	sw	a5,-72(s0)
  e4:	fcc42783          	lw	a5,-52(s0)
  e8:	0e078e63          	beqz	a5,1e4 <.L5>
  ec:	fc842783          	lw	a5,-56(s0)
  f0:	0e078a63          	beqz	a5,1e4 <.L5>
  f4:	fc442783          	lw	a5,-60(s0)
  f8:	0e079663          	bnez	a5,1e4 <.L5>
  fc:	fc042783          	lw	a5,-64(s0)
 100:	0e078263          	beqz	a5,1e4 <.L5>
 104:	fbc42783          	lw	a5,-68(s0)
 108:	02078263          	beqz	a5,12c <.L6>
 10c:	fb842783          	lw	a5,-72(s0)
 110:	00078e63          	beqz	a5,12c <.L6>
 114:	00100793          	li	a5,1
 118:	fef42623          	sw	a5,-20(s0)
 11c:	fe042423          	sw	zero,-24(s0)
 120:	fe042223          	sw	zero,-28(s0)
 124:	fe042023          	sw	zero,-32(s0)
 128:	0680006f          	j	190 <.L7>

0000012c <.L6>:
 12c:	fbc42783          	lw	a5,-68(s0)
 130:	02078063          	beqz	a5,150 <.L8>
 134:	00100793          	li	a5,1
 138:	fef42623          	sw	a5,-20(s0)
 13c:	fe042423          	sw	zero,-24(s0)
 140:	fe042223          	sw	zero,-28(s0)
 144:	00100793          	li	a5,1
 148:	fef42023          	sw	a5,-32(s0)
 14c:	0440006f          	j	190 <.L7>

00000150 <.L8>:
 150:	fb842783          	lw	a5,-72(s0)
 154:	02078063          	beqz	a5,174 <.L9>
 158:	00100793          	li	a5,1
 15c:	fef42623          	sw	a5,-20(s0)
 160:	fe042423          	sw	zero,-24(s0)
 164:	00100793          	li	a5,1
 168:	fef42223          	sw	a5,-28(s0)
 16c:	fe042023          	sw	zero,-32(s0)
 170:	0200006f          	j	190 <.L7>

00000174 <.L9>:
 174:	00100793          	li	a5,1
 178:	fef42623          	sw	a5,-20(s0)
 17c:	fe042423          	sw	zero,-24(s0)
 180:	00100793          	li	a5,1
 184:	fef42223          	sw	a5,-28(s0)
 188:	00100793          	li	a5,1
 18c:	fef42023          	sw	a5,-32(s0)

00000190 <.L7>:
 190:	fec42783          	lw	a5,-20(s0)
 194:	00679793          	sll	a5,a5,0x6
 198:	fcf42e23          	sw	a5,-36(s0)
 19c:	fe842783          	lw	a5,-24(s0)
 1a0:	00779793          	sll	a5,a5,0x7
 1a4:	fcf42c23          	sw	a5,-40(s0)
 1a8:	fe442783          	lw	a5,-28(s0)
 1ac:	00879793          	sll	a5,a5,0x8
 1b0:	fcf42a23          	sw	a5,-44(s0)
 1b4:	fe042783          	lw	a5,-32(s0)
 1b8:	00979793          	sll	a5,a5,0x9
 1bc:	fcf42823          	sw	a5,-48(s0)
 1c0:	00cf6f33          	or	t5,t5,a2
 1c4:	00df6f33          	or	t5,t5,a3
 1c8:	00ef6f33          	or	t5,t5,a4
 1cc:	00ff6f33          	or	t5,t5,a5
 1d0:	fcc42e23          	sw	a2,-36(s0)
 1d4:	fcd42c23          	sw	a3,-40(s0)
 1d8:	fce42a23          	sw	a4,-44(s0)
 1dc:	fcf42823          	sw	a5,-48(s0)
 1e0:	06c0006f          	j	24c <.L10>

000001e4 <.L5>:
 1e4:	fe042623          	sw	zero,-20(s0)
 1e8:	00100793          	li	a5,1
 1ec:	fef42423          	sw	a5,-24(s0)
 1f0:	fe042223          	sw	zero,-28(s0)
 1f4:	fe042023          	sw	zero,-32(s0)
 1f8:	fec42783          	lw	a5,-20(s0)
 1fc:	00679793          	sll	a5,a5,0x6
 200:	fcf42e23          	sw	a5,-36(s0)
 204:	fe842783          	lw	a5,-24(s0)
 208:	00779793          	sll	a5,a5,0x7
 20c:	fcf42c23          	sw	a5,-40(s0)
 210:	fe442783          	lw	a5,-28(s0)
 214:	00879793          	sll	a5,a5,0x8
 218:	fcf42a23          	sw	a5,-44(s0)
 21c:	fe042783          	lw	a5,-32(s0)
 220:	00979793          	sll	a5,a5,0x9
 224:	fcf42823          	sw	a5,-48(s0)
 228:	00cf6f33          	or	t5,t5,a2
 22c:	00df6f33          	or	t5,t5,a3
 230:	00ef6f33          	or	t5,t5,a4
 234:	00ff6f33          	or	t5,t5,a5
 238:	fcc42e23          	sw	a2,-36(s0)
 23c:	fcd42c23          	sw	a3,-40(s0)
 240:	fce42a23          	sw	a4,-44(s0)
 244:	fcf42823          	sw	a5,-48(s0)
 248:	00000013          	nop

0000024c <.L10>:
 24c:	00000013          	nop
 250:	04c12403          	lw	s0,76(sp)
 254:	05010113          	add	sp,sp,80
 258:	00008067          	ret

```

- The assembly code contains various instructions. The list of the individual instruction can be generated by using ```instruction_counter.py```. The list generated for our code is as follows.
```bash
Number of different instructions: 14
List of unique instructions:
add
auipc
j
bnez
li
and
lw
sw
sll
nop
beqz
ret
jalr
or
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
https://github.com/The-OpenROAD-Project/OpenSTA.git
https://github.com/kunalg123
https://www.vsdiat.com
https://github.com/SakethGajawada/RISCV-GNU


