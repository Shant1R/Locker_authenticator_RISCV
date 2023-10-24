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

	int p1_0,p2_0,p3_0,p4_0,s1_0,s2_0;
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
	"and x30, x30, 0xFFFFFC3F\n\t"
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
		: "=r" (p1_0)
		:
		:);
		
		
		asm volatile(
		"andi %0, x30, 0x02\n\t"
		: "=r" (p2_0)
		:
		:);
		

		asm volatile(
		"andi %0, x30, 0x04\n\t"
		: "=r" (p3_0)
		:
		:);

		asm volatile(
		"andi %0, x30, 0x08\n\t"
		: "=r" (p4_0)
		:
		:);

		asm volatile(
		"andi %0, x30, 0x10\n\t"
		: "=r" (s1_0)
		:
		:);

		asm volatile(
		"andi %0, x30, 0x20\n\t"
		: "=r" (s2_0)
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
			"and x30, x30, 0xFFFFFC3F\n\t"
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
			"and x30, x30, 0xFFFFFC3F\n\t"
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

00010054 <main>:
   10054:   fb010113            addi    sp,sp,-80
   10058:   04812623            sw  s0,76(sp)
   1005c:   05010413            addi    s0,sp,80
   10060:   fe042623            sw  zero,-20(s0)
   10064:   fe042423            sw  zero,-24(s0)
   10068:   fe042223            sw  zero,-28(s0)
   1006c:   fe042023            sw  zero,-32(s0)
   10070:   fec42783            lw  a5,-20(s0)
   10074:   00679793            slli    a5,a5,0x6
   10078:   fcf42e23            sw  a5,-36(s0)
   1007c:   fe842783            lw  a5,-24(s0)
   10080:   00779793            slli    a5,a5,0x7
   10084:   fcf42c23            sw  a5,-40(s0)
   10088:   fe442783            lw  a5,-28(s0)
   1008c:   00879793            slli    a5,a5,0x8
   10090:   fcf42a23            sw  a5,-44(s0)
   10094:   fe042783            lw  a5,-32(s0)
   10098:   00979793            slli    a5,a5,0x9
   1009c:   fcf42823            sw  a5,-48(s0)
   100a0:   fdc42783            lw  a5,-36(s0)
   100a4:   fd842703            lw  a4,-40(s0)
   100a8:   fd442683            lw  a3,-44(s0)
   100ac:   fd042603            lw  a2,-48(s0)
   100b0:   00ff6f33            or  t5,t5,a5
   100b4:   00ef6f33            or  t5,t5,a4
   100b8:   00df6f33            or  t5,t5,a3
   100bc:   00cf6f33            or  t5,t5,a2
   100c0:   001f7793            andi    a5,t5,1
   100c4:   fcf42623            sw  a5,-52(s0)
   100c8:   002f7793            andi    a5,t5,2
   100cc:   fcf42423            sw  a5,-56(s0)
   100d0:   004f7793            andi    a5,t5,4
   100d4:   fcf42223            sw  a5,-60(s0)
   100d8:   008f7793            andi    a5,t5,8
   100dc:   fcf42023            sw  a5,-64(s0)
   100e0:   010f7793            andi    a5,t5,16
   100e4:   faf42e23            sw  a5,-68(s0)
   100e8:   020f7793            andi    a5,t5,32
   100ec:   faf42c23            sw  a5,-72(s0)
   100f0:   fcc42783            lw  a5,-52(s0)
   100f4:   0e078e63            beqz    a5,101f0 <main+0x19c>
   100f8:   fc842783            lw  a5,-56(s0)
   100fc:   0e078a63            beqz    a5,101f0 <main+0x19c>
   10100:   fc442783            lw  a5,-60(s0)
   10104:   0e079663            bnez    a5,101f0 <main+0x19c>
   10108:   fc042783            lw  a5,-64(s0)
   1010c:   0e078263            beqz    a5,101f0 <main+0x19c>
   10110:   fbc42783            lw  a5,-68(s0)
   10114:   02078263            beqz    a5,10138 <main+0xe4>
   10118:   fb842783            lw  a5,-72(s0)
   1011c:   00078e63            beqz    a5,10138 <main+0xe4>
   10120:   00100793            li  a5,1
   10124:   fef42623            sw  a5,-20(s0)
   10128:   fe042423            sw  zero,-24(s0)
   1012c:   fe042223            sw  zero,-28(s0)
   10130:   fe042023            sw  zero,-32(s0)
   10134:   0680006f            j   1019c <main+0x148>
   10138:   fbc42783            lw  a5,-68(s0)
   1013c:   02078063            beqz    a5,1015c <main+0x108>
   10140:   00100793            li  a5,1
   10144:   fef42623            sw  a5,-20(s0)
   10148:   fe042423            sw  zero,-24(s0)
   1014c:   fe042223            sw  zero,-28(s0)
   10150:   00100793            li  a5,1
   10154:   fef42023            sw  a5,-32(s0)
   10158:   0440006f            j   1019c <main+0x148>
   1015c:   fb842783            lw  a5,-72(s0)
   10160:   02078063            beqz    a5,10180 <main+0x12c>
   10164:   00100793            li  a5,1
   10168:   fef42623            sw  a5,-20(s0)
   1016c:   fe042423            sw  zero,-24(s0)
   10170:   00100793            li  a5,1
   10174:   fef42223            sw  a5,-28(s0)
   10178:   fe042023            sw  zero,-32(s0)
   1017c:   0200006f            j   1019c <main+0x148>
   10180:   00100793            li  a5,1
   10184:   fef42623            sw  a5,-20(s0)
   10188:   fe042423            sw  zero,-24(s0)
   1018c:   00100793            li  a5,1
   10190:   fef42223            sw  a5,-28(s0)
   10194:   00100793            li  a5,1
   10198:   fef42023            sw  a5,-32(s0)
   1019c:   fec42783            lw  a5,-20(s0)
   101a0:   00679793            slli    a5,a5,0x6
   101a4:   fcf42e23            sw  a5,-36(s0)
   101a8:   fe842783            lw  a5,-24(s0)
   101ac:   00779793            slli    a5,a5,0x7
   101b0:   fcf42c23            sw  a5,-40(s0)
   101b4:   fe442783            lw  a5,-28(s0)
   101b8:   00879793            slli    a5,a5,0x8
   101bc:   fcf42a23            sw  a5,-44(s0)
   101c0:   fe042783            lw  a5,-32(s0)
   101c4:   00979793            slli    a5,a5,0x9
   101c8:   fcf42823            sw  a5,-48(s0)
   101cc:   fdc42783            lw  a5,-36(s0)
   101d0:   fd842703            lw  a4,-40(s0)
   101d4:   fd442683            lw  a3,-44(s0)
   101d8:   fd042603            lw  a2,-48(s0)
   101dc:   00ff6f33            or  t5,t5,a5
   101e0:   00ef6f33            or  t5,t5,a4
   101e4:   00df6f33            or  t5,t5,a3
   101e8:   00cf6f33            or  t5,t5,a2
   101ec:   0680006f            j   10254 <main+0x200>
   101f0:   fe042623            sw  zero,-20(s0)
   101f4:   00100793            li  a5,1
   101f8:   fef42423            sw  a5,-24(s0)
   101fc:   fe042223            sw  zero,-28(s0)
   10200:   fe042023            sw  zero,-32(s0)
   10204:   fec42783            lw  a5,-20(s0)
   10208:   00679793            slli    a5,a5,0x6
   1020c:   fcf42e23            sw  a5,-36(s0)
   10210:   fe842783            lw  a5,-24(s0)
   10214:   00779793            slli    a5,a5,0x7
   10218:   fcf42c23            sw  a5,-40(s0)
   1021c:   fe442783            lw  a5,-28(s0)
   10220:   00879793            slli    a5,a5,0x8
   10224:   fcf42a23            sw  a5,-44(s0)
   10228:   fe042783            lw  a5,-32(s0)
   1022c:   00979793            slli    a5,a5,0x9
   10230:   fcf42823            sw  a5,-48(s0)
   10234:   fdc42783            lw  a5,-36(s0)
   10238:   fd842703            lw  a4,-40(s0)
   1023c:   fd442683            lw  a3,-44(s0)
   10240:   fd042603            lw  a2,-48(s0)
   10244:   00ff6f33            or  t5,t5,a5
   10248:   00ef6f33            or  t5,t5,a4
   1024c:   00df6f33            or  t5,t5,a3
   10250:   00cf6f33            or  t5,t5,a2
   10254:   e6dff06f            j   100c0 <main+0x6c>

```

- The assembly code contains various instructions. The list of the individual instruction can be generated by using ```instruction_counter.py```. The list generated for our code is as follows.
```bash
Number of different instructions: 10

List of unique instructions:

bnez
slli
or
lw
addi
sw
beqz
andi
li
j


```

## Functional Simualation 

We will perform functional simulation to test the functionality of the verilog code generated for the processor chip. We have tested the processor and its functionality for various input combinations and compare the output generated with the desired expected output. The processor and testbench code are under the file name ```processor.v``` and ```testbench.v```. The files can be found in the repository above. 

*Note -* The inputs for the processor are p1, p2, p3, p4, s1 and s2. The inputs are taken from LSB for the x30 registor, thus, the input format is given as ```{s2,s1,p4,p3,p2,p1}```. ie, the LSB bit is mapped to p1 and continues. Similar;y the output is generated as ```{av2,av1,x,c}```. 

- Case with wrong passcode, expected output --> 2 (0010)
  
![Screenshot from 2023-10-23 23-58-38](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/9cc1ca13-cd68-47be-afe9-410a66cb29a5)

- Case with correct passcode
  - input --> 111011, expected output --> 1 (0001)

![Screenshot from 2023-10-23 23-38-25](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/07c3cc8d-f82c-45cd-9c74-92b94861ef69)

  - input --> 101011, expected output --> 5 (0101)

![Screenshot from 2023-10-24 00-25-09](https://github.com/Shant1R/Locker_authenticator_RISCV/assets/59409568/5acd84be-1a19-4a8c-baf4-42a0257a69b2)

We have seen a few cases and verified the output. We can observe the instruction bit toggling and the input can be seen in the ```input_gpio_pins``` and input_write. We can see the output has been written in the ```output_gpio_pins``` and output_write. We can also observe the ```write_done``` being flagged once the output has been written. Thus we can conclude the processor code is working as expected and we can now move ahead with the synthesis and Gate level simulations.

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


