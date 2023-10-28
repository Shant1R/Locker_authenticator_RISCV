# Locker_authenticator_RISCV

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/d3e27299-3bad-4e8b-b5df-02495fb6f521)


Under this repository, we have done a step by step implementation to make a passcode based authentication system for lockers based in RISCV Architecture summarizes the progress made towards the completion. 

## OBJECTIVE 

The core objective of the project undertaken is to develop a RISCV core to perform authentication operation of a locker and check for whether the storage space is available. The system upon the entry of correct passcode will look if the storage space is available, if yes, the system turns on the green LED. In case of wrong passcode, the system flags the occurance with a red LED.

## PROCEDURE

The locker authentication project is based on simple passcode. We have defined a 4 bit passcode, ```1101```. To take the passcode inputs, we will implement push down switches, ie we have an array of 4 switches. When the correct passcode is entered we move ahead with the space verification. In case of wrong passcode, the system flags it. In the project, we have taken the locker to have two comparments. Each compartment is one storage unit. To identify if a storage unit is available, we will integrate obstcle detection, using proximity sensors. Thus, in the given case, two units of proximity sensors are required. Henceforth, we have four cases at our hands, both available, either one avaliable and none. The following will be flagged using corresponding LEDs. 

## BLOCK DIAGRAM  

![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/a31842ac-9181-4d9c-97ac-dc7d81b740d3)


## CODE & LOGIC TESTING

- We first compile the C code using gcc and check the expected outcomes for testcases. This confirms, we have working code with no syntax errors and functional logical errors.

  ```bash
  gcc locker.c
  ./a.out
  ```
    ![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/85b759cc-87ff-49d4-9cc2-bad9282c8c7f)

### SPIKE TESTING

- After this, we define the inputs and outputs using ```asm``` to link the assemply level inputs and outputs and store them over variables in C.

- Now, we spike the code to again check the functionality of the code. The test code can be found above as ```spike_tester.c```. We have taken 5 testcases, 4 for the correct passcode and one with incorrect passcode. The correct passcode is ```{p4,p3,p2,p1} -> {1011}```.

  The masked output format comes as ```{av2,av1,x,c,s2,s1,p4,p3,p2,p1}```, in which the 6 bits from LSB are input bits which get masked to 0 for the output, thus the masked output is displayed in the spike simulation comes as ```{av2,av1,x,c,0,0,0,0,0,0}```.
  
  - Case with wrong passcode, expected output - ```2 (0010)```, Masked Output - ```128 (0010000000)```
    ![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/b58197f4-6011-474f-bc0e-e423c3268455)
  
  - Case with correct passcode

    - input - ```001011```, expexted output - ```D (1101)```, Masked Output - ```832 (1101000000)```
      ![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/91cceeac-0e19-4af0-9c19-e31dcd6376b3)

    - input - ```011011```, expected output - ```9 (1001)```, Masked Output - ```576 (1001000000)```
      ![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/abb53627-c684-4f36-9d7b-1e100168644f)
      
    - input - ```101011```, expected output - ```5 (0101)```, Masked Output - ```320 (0101000000)```
      ![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/a49fabae-5a9c-4bef-be8e-66ae977514f7)

    - input - ```111011```, expected putput - ```1 (0001)```, Masked Output - ```64 (0001000000)```
      ![image](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/a55f963f-17ac-4bbb-8e35-8c87cd15d29e)

## CODE

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


```

***Assembly Code***

Compile the C code using RISCV-V GNU Toolchain and dump the assembly code into ```locker.o```, the contents of which are copied into a .txt file for easy veiwing.

```bash

shant.out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fb010113          	addi	sp,sp,-80
   10058:	04812623          	sw	s0,76(sp)
   1005c:	05010413          	addi	s0,sp,80
   10060:	fe042623          	sw	zero,-20(s0)
   10064:	fe042423          	sw	zero,-24(s0)
   10068:	fe042223          	sw	zero,-28(s0)
   1006c:	fe042023          	sw	zero,-32(s0)
   10070:	c3f00793          	li	a5,-961
   10074:	fcf42e23          	sw	a5,-36(s0)
   10078:	fec42783          	lw	a5,-20(s0)
   1007c:	00679793          	slli	a5,a5,0x6
   10080:	fcf42c23          	sw	a5,-40(s0)
   10084:	fe842783          	lw	a5,-24(s0)
   10088:	00779793          	slli	a5,a5,0x7
   1008c:	fcf42a23          	sw	a5,-44(s0)
   10090:	fe442783          	lw	a5,-28(s0)
   10094:	00879793          	slli	a5,a5,0x8
   10098:	fcf42823          	sw	a5,-48(s0)
   1009c:	fe042783          	lw	a5,-32(s0)
   100a0:	00979793          	slli	a5,a5,0x9
   100a4:	fcf42623          	sw	a5,-52(s0)
   100a8:	fd842783          	lw	a5,-40(s0)
   100ac:	fd442703          	lw	a4,-44(s0)
   100b0:	fd042683          	lw	a3,-48(s0)
   100b4:	fcc42603          	lw	a2,-52(s0)
   100b8:	fdc42583          	lw	a1,-36(s0)
   100bc:	00bf7f33          	and	t5,t5,a1
   100c0:	00ff6f33          	or	t5,t5,a5
   100c4:	00ef6f33          	or	t5,t5,a4
   100c8:	00df6f33          	or	t5,t5,a3
   100cc:	00cf6f33          	or	t5,t5,a2
   100d0:	001f7793          	andi	a5,t5,1
   100d4:	fcf42423          	sw	a5,-56(s0)
   100d8:	002f7793          	andi	a5,t5,2
   100dc:	fcf42223          	sw	a5,-60(s0)
   100e0:	004f7793          	andi	a5,t5,4
   100e4:	fcf42023          	sw	a5,-64(s0)
   100e8:	008f7793          	andi	a5,t5,8
   100ec:	faf42e23          	sw	a5,-68(s0)
   100f0:	010f7793          	andi	a5,t5,16
   100f4:	faf42c23          	sw	a5,-72(s0)
   100f8:	020f7793          	andi	a5,t5,32
   100fc:	faf42a23          	sw	a5,-76(s0)
   10100:	fc842783          	lw	a5,-56(s0)
   10104:	10078263          	beqz	a5,10208 <main+0x1b4>
   10108:	fc442783          	lw	a5,-60(s0)
   1010c:	0e078e63          	beqz	a5,10208 <main+0x1b4>
   10110:	fc042783          	lw	a5,-64(s0)
   10114:	0e079a63          	bnez	a5,10208 <main+0x1b4>
   10118:	fbc42783          	lw	a5,-68(s0)
   1011c:	0e078663          	beqz	a5,10208 <main+0x1b4>
   10120:	fb842783          	lw	a5,-72(s0)
   10124:	02078263          	beqz	a5,10148 <main+0xf4>
   10128:	fb442783          	lw	a5,-76(s0)
   1012c:	00078e63          	beqz	a5,10148 <main+0xf4>
   10130:	00100793          	li	a5,1
   10134:	fef42623          	sw	a5,-20(s0)
   10138:	fe042423          	sw	zero,-24(s0)
   1013c:	fe042223          	sw	zero,-28(s0)
   10140:	fe042023          	sw	zero,-32(s0)
   10144:	0680006f          	j	101ac <main+0x158>
   10148:	fb842783          	lw	a5,-72(s0)
   1014c:	02078063          	beqz	a5,1016c <main+0x118>
   10150:	00100793          	li	a5,1
   10154:	fef42623          	sw	a5,-20(s0)
   10158:	fe042423          	sw	zero,-24(s0)
   1015c:	fe042223          	sw	zero,-28(s0)
   10160:	00100793          	li	a5,1
   10164:	fef42023          	sw	a5,-32(s0)
   10168:	0440006f          	j	101ac <main+0x158>
   1016c:	fb442783          	lw	a5,-76(s0)
   10170:	02078063          	beqz	a5,10190 <main+0x13c>
   10174:	00100793          	li	a5,1
   10178:	fef42623          	sw	a5,-20(s0)
   1017c:	fe042423          	sw	zero,-24(s0)
   10180:	00100793          	li	a5,1
   10184:	fef42223          	sw	a5,-28(s0)
   10188:	fe042023          	sw	zero,-32(s0)
   1018c:	0200006f          	j	101ac <main+0x158>
   10190:	00100793          	li	a5,1
   10194:	fef42623          	sw	a5,-20(s0)
   10198:	fe042423          	sw	zero,-24(s0)
   1019c:	00100793          	li	a5,1
   101a0:	fef42223          	sw	a5,-28(s0)
   101a4:	00100793          	li	a5,1
   101a8:	fef42023          	sw	a5,-32(s0)
   101ac:	fec42783          	lw	a5,-20(s0)
   101b0:	00679793          	slli	a5,a5,0x6
   101b4:	fcf42c23          	sw	a5,-40(s0)
   101b8:	fe842783          	lw	a5,-24(s0)
   101bc:	00779793          	slli	a5,a5,0x7
   101c0:	fcf42a23          	sw	a5,-44(s0)
   101c4:	fe442783          	lw	a5,-28(s0)
   101c8:	00879793          	slli	a5,a5,0x8
   101cc:	fcf42823          	sw	a5,-48(s0)
   101d0:	fe042783          	lw	a5,-32(s0)
   101d4:	00979793          	slli	a5,a5,0x9
   101d8:	fcf42623          	sw	a5,-52(s0)
   101dc:	fd842783          	lw	a5,-40(s0)
   101e0:	fd442703          	lw	a4,-44(s0)
   101e4:	fd042683          	lw	a3,-48(s0)
   101e8:	fcc42603          	lw	a2,-52(s0)
   101ec:	fdc42583          	lw	a1,-36(s0)
   101f0:	00bf7f33          	and	t5,t5,a1
   101f4:	00ff6f33          	or	t5,t5,a5
   101f8:	00ef6f33          	or	t5,t5,a4
   101fc:	00df6f33          	or	t5,t5,a3
   10200:	00cf6f33          	or	t5,t5,a2
   10204:	0700006f          	j	10274 <main+0x220>
   10208:	fe042623          	sw	zero,-20(s0)
   1020c:	00100793          	li	a5,1
   10210:	fef42423          	sw	a5,-24(s0)
   10214:	fe042223          	sw	zero,-28(s0)
   10218:	fe042023          	sw	zero,-32(s0)
   1021c:	fec42783          	lw	a5,-20(s0)
   10220:	00679793          	slli	a5,a5,0x6
   10224:	fcf42c23          	sw	a5,-40(s0)
   10228:	fe842783          	lw	a5,-24(s0)
   1022c:	00779793          	slli	a5,a5,0x7
   10230:	fcf42a23          	sw	a5,-44(s0)
   10234:	fe442783          	lw	a5,-28(s0)
   10238:	00879793          	slli	a5,a5,0x8
   1023c:	fcf42823          	sw	a5,-48(s0)
   10240:	fe042783          	lw	a5,-32(s0)
   10244:	00979793          	slli	a5,a5,0x9
   10248:	fcf42623          	sw	a5,-52(s0)
   1024c:	fd842783          	lw	a5,-40(s0)
   10250:	fd442703          	lw	a4,-44(s0)
   10254:	fd042683          	lw	a3,-48(s0)
   10258:	fcc42603          	lw	a2,-52(s0)
   1025c:	fdc42583          	lw	a1,-36(s0)
   10260:	00bf7f33          	and	t5,t5,a1
   10264:	00ff6f33          	or	t5,t5,a5
   10268:	00ef6f33          	or	t5,t5,a4
   1026c:	00df6f33          	or	t5,t5,a3
   10270:	00cf6f33          	or	t5,t5,a2
   10274:	e5dff06f          	j	100d0 <main+0x7c>
```

- The assembly code contains various instructions. The list of the individual instruction can be generated by using ```instruction_counter.py```. The list generated for our code is as follows.
```bash
Number of different instructions: 11

List of unique instructions:

or
sw
andi
li
beqz
j
bnez
and
addi
slli
lw

```

## Functional Simualation 

We will perform functional simulation to test the functionality of the verilog code generated for the processor chip. We have tested the processor and its functionality for various input combinations and compare the output generated with the desired expected output. The processor and testbench code are under the file name ```processor.v``` and ```testbench.v```. The files can be found in the repository above. 

*Note -* The inputs for the processor are p1, p2, p3, p4, s1 and s2. The inputs are taken from LSB for the x30 registor, thus, the input format is given as ```{s2,s1,p4,p3,p2,p1}```. ie, the LSB bit is mapped to p1 and continues. Similar;y the output is generated as ```{av2,av1,x,c}```. 

- Case with wrong passcode, expected output - ```2 (0010)```

![Screenshot from 2023-10-23 23-58-38](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/b8628b72-3634-4485-8278-9feb79224c8b)

- Case with correct passcode

  - input - ```001011```, expexted output - ```D (1101)```
    
![Screenshot from 2023-10-24 20-10-07](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/bdc4bcc7-52ef-4584-9c08-813f258043b5)

  - input - ```011011```, expected output - ```9 (1001)```

![Screenshot from 2023-10-24 23-51-35](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/f54196b4-7b90-4842-b820-3bf1a3bad206)

  - input - ```101011```, expected output - ```5 (0101)```

![Screenshot from 2023-10-24 00-25-09](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/db942d76-5210-45ae-92f0-3f55ebfacae0)

  - input - ```111011```, expected putput - ```1 (0001)```

![Screenshot from 2023-10-23 23-38-25](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/1b20e3b2-b764-4523-a87a-404aa3856b7c)


We have seen a few cases and verified the output. We can observe the instruction bit toggling and the input can be seen in the ```input_gpio_pins``` and input_write. We can see the output has been written in the ```output_gpio_pins``` and output_write. We can also observe the ```write_done``` being flagged once the output has been written. Thus we can conclude the processor code is working as expected and we can now move ahead with the synthesis and Gate level simulations.

## Instruction Verification 
We will consider the link: ```https://en.wikichip.org/wiki/risc-v/registers``` for refrence and decide the signal pins. Thus, according to the reference given, ```signal43``` is *zero* register, ```signal45``` is the *stack pointer*, ```signal51``` is the *s0* register and ```signal58``` is the *a5* register.

Instructions verified.

- addi	sp,sp,-80
  
![Screenshot from 2023-10-28 15-33-15](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/a672516a-5391-4ada-8cf5-678ea1c24515)

- addi	s0,sp,80
  
![Screenshot from 2023-10-28 15-35-12](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/d3bacb64-2622-48e7-bcba-630f5eeafb89)

- li	a5,-961

![Screenshot from 2023-10-28 15-37-44](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/665f6a6a-2ecb-4182-b15b-d9c92f50f3ad)

- slli	a5,a5,0x6

![Screenshot from 2023-10-28 15-43-52](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/887017c5-a47b-4f7f-b687-f807f1637764)

Some of the instructions in the above assembly code were tested in GTKWave and was verified.

## Word of Thanks
I would take this opportunity to sciencerly thank Mr. Kunal Gosh(Founder/VSD) for helping me out to complete this flow smoothly.

## Acknowledgement
- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Skywater Foundry
- OpenAI Chatgpt
- Alwin Shaju, MTech, IIITB
- Emil Jayanth Lal, MTech, IIITB
- N Sai Sampath, MTech, IIITB
- Mayank Kabra, iMtech, IIITB

## Reference
- https://github.com/The-OpenROAD-Project/OpenSTA.git
- https://github.com/kunalg123
- https://www.vsdiat.com
- https://github.com/SakethGajawada/RISCV-GNU


