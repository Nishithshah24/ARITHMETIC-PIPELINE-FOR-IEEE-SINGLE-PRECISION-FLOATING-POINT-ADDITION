#include<stdio.h>
#include<limits.h>

void main()
{
	short int index=0;
//	        	         {   100  ,   100  ,   -53  ,  -300  ,    0   ,    0   }
	int  	no1_sign_48[6] = {    0   ,    0   ,    1   ,    1   ,    0   ,    0   },
		no1_exp_48[6] =  {  0x85  ,  0x85  ,  0x84  ,  0x87  ,  0x00  ,  0x00  },

//      	                 {   200  ,   -50  ,   35   ,   -99  ,    0   ,  -171  }
		no2_s‌ign_48[6] = {    0   ,    1   ,    0   ,    1   ,    0   ,    1   },
		no2_exp_48[6]  = {  0x86  ,  0x84  ,  0x84  ,  0x85  ,  0x00  ,  0x86  },
		sum_sign_48[6],
		sum_exp_48[6],
		shifts;

		unsigned long int	no1_mantissa_48[6]={0x480000,0x480000,0x540000,0x160000,0x000000,0x000000},
					no2_mantissa_48[6]={0x480000,0x480000,0x0c0000,0x460000,0x000000,0x2b0000},
					sum_mantissa_48[6],
					mask;

	clrscr();
	mask = 0x400000;

	for(index=0;index<6;index++)
	{
		printf("\npair = %d",index+1);
		printf("\n%d %x %lx\n",no1_sign_48[index],no1_exp_48[index],no1_mantissa_48[index]);
		printf("%d %x %lx\n",no2_sign_48[index],no2_exp_48[index],no2_mantissa_48[index]);

		no1_mantissa_48[index] = (no1_mantissa_48[index]>>1) | mask;
		no2_mantissa_48[index] = (no2_mantissa_48[index]>>1) | mask;
		no1_exp_48[index] += 1;
		no2_exp_48[index] += 1;

		printf("\n%d %x %lx",no1_sign_48[index],no1_exp_48[index],no1_mantissa_48[index]);
		printf("\n%d %x %lx",no2_sign_48[index],no2_exp_48[index],no2_mantissa_48[index]);


		printf("\n-------------------------- 1st stage ----------------------------");
		shifts = no1_exp_48[index] - no2_exp_48[index];
		if(shifts>0)
			sum_sign_48[index] = no1_sign_48[index];
		else if(shifts<0)
			sum_sign_48[index] = no2_sign_48[index];
		else
		{
			if(no1_mantissa_48[index]>no2_mantissa_48[index])
			sum_sign_48[index] = no1_sign_48[index];
			else
			sum_sign_48[index] = no2_sign_48[index];
		}
		printf("\nNo. of Shifts required = %d",shifts);


		printf("\n-------------------------- 2nd stage ----------------------------");
		if(shifts!=0)
		{
			if(shifts<0)
			shifts = 0 - shifts;

			if(no1_exp_48[index] > no2_exp_48[index])
			{
				no2_mantissa_48[index] = no2_mantissa_48[index] >> shifts;
				no2_exp_48[index] = no2_exp_48[index]+shifts;
			}
			else
			{
				no1_mantissa_48[index] = no1_mantissa_48[index] >> shifts;
				no1_exp_48[index] = no1_exp_48[index]+shifts;
			}
		}
		printf("\n%x %lx %x %lx",no1_exp_48[index],no1_mantissa_48[index],no2_exp_48[index],no2_mantissa_48[index]);
		

		printf("\n-------------------------- 3rd stage ----------------------------");
		if(no1_sign_48[index] != no2_sign_48[index])
		{
			if(no1_mantissa_48[index] < no2_mantissa_48[index])
			{
				no1_mantissa_48[index] = ~(no1_mantissa_48[index])+1;
				printf("\n2's Complement of First Number = %lx",no1_mantissa_48[index]);
			}
			else
			{
				no2_mantissa_48[index] = ~(no2_mantissa_48[index])+1;
				printf("\n2's Complement of Second Number = %lx",no2_mantissa_48[index]);
			}
		}
		else
		printf("\n 2's Complement not required as signs are same");
		

		printf("\n-------------------------- 4th stage ----------------------------");
		sum_mantissa_48[index] = no1_mantissa_48[index] + no2_mantissa_48[index];
		sum_exp_48[index] = no1_exp_48[index];
		printf("\n%d %x %lx",sum_sign_48[index],sum_exp_48[index],sum_mantissa_48[index]);
		

		printf("\n-------------------------- 5th stage ----------------------------");
		if(no1_sign_48[index] != no2_sign_48[index])
		{
			sum_mantissa_48[index] &=0x1fffff;
			if(no1_mantissa_48[index] ==0 )
			{
				sum_mantissa_48[index]=sum_mantissa_48[index]<<1;
				sum_exp_48[index] -= 1;
			}
			else
			{
				sum_mantissa_48[index]=sum_mantissa_48[index]<<2;
				sum_exp_48[index] -= 2;
			}
		}
		else if(no1_sign_48[index] == 0 && no2_sign_48[index] == 0)
			sum_mantissa_48[index] &= 0x7fffff;
		else
		{
			sum_mantissa_48[index] &= 0x4fffff;
			sum_exp_48[index] -= 1;
		}

		printf("\nSum = %d %x %lx",sum_sign_48[index],sum_exp_48[index],sum_mantissa_48[index]);                               
		getch();
	}
}