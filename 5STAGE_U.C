#include<stdio.h>
#include<limits.h>
void main()
{
short int index=0;
//	           {   100  ,   100  ,   -53  ,  -300  ,    0   ,    0   }
int  	n1_s_96[6]={    0   ,    0   ,    1   ,    1   ,    0   ,    0   },
	n1_e_96[6]={  0x85  ,  0x85  ,  0x84  ,  0x87  ,  0x00  ,  0x00  },

//                 {   200  ,   -50  ,   35   ,   -99  ,    0   ,  -171  }
	n2_s_96[6]={    0   ,    1   ,    0   ,    1   ,    0   ,    1   },
	n2_e_96[6]={  0x86  ,  0x84  ,  0x84  ,  0x85  ,  0x00  ,  0x86  },
	ans_s_96[6],
	ans_e_96[6],
	diff;
// also checked for value n1 = 0.0673 and n2 = -0.532 which should result in
// -0.4647 we got -0.4641 as an output (accurate up to 3 decimal places)

unsigned long int	n1_m_96[6]={0x480000,0x480000,0x540000,0x160000,0x000000,0x000000},
			n2_m_96[6]={0x480000,0x480000,0x0c0000,0x460000,0x000000,0x2b0000},
			ans_m_96[6],
			foo;



clrscr();
foo = 0x400000;

for(index=0;index<6;index++)
	{
		printf("\npair = %d",index+1);
		printf("\n%d %x %lx\n",n1_s_96[index],n1_e_96[index],n1_m_96[index]);
		printf("%d %x %lx\n",n2_s_96[index],n2_e_96[index],n2_m_96[index]);

		n1_m_96[index] = (n1_m_96[index]>>1) | foo;
		n2_m_96[index] = (n2_m_96[index]>>1) | foo;
		n1_e_96[index] += 1;
		n2_e_96[index] += 1;


		printf("\n%d %x %lx",n1_s_96[index],n1_e_96[index],n1_m_96[index]);
		printf("\n%d %x %lx",n2_s_96[index],n2_e_96[index],n2_m_96[index]);

		printf("\n-------------------------- 1st stage ----------------------------");
		diff = n1_e_96[index] - n2_e_96[index];
		if(diff>0)
			ans_s_96[index] = n1_s_96[index];
		else if(diff<0)
			ans_s_96[index] = n2_s_96[index];
		else
		{
			if(n1_m_96[index]>n2_m_96[index])
			ans_s_96[index] = n1_s_96[index];
			else
			ans_s_96[index] = n2_s_96[index];
		}
		printf("\nshifts needed = %d",diff);
		printf("\n---------------------- end of 1st stage--------------------------");

		printf("\n-------------------------- 2nd stage ----------------------------");
		if(diff!=0)
		{
			if(diff<0)
			diff = 0 - diff;

			if(n1_e_96[index] > n2_e_96[index])
			{
				n2_m_96[index] = n2_m_96[index] >> diff;
				n2_e_96[index] = n2_e_96[index]+diff;
			}
			else
			{
				n1_m_96[index] = n1_m_96[index] >> diff;
				n1_e_96[index] = n1_e_96[index]+diff;
			}
		}
		printf("\n%x %lx %x %lx",n1_e_96[index],n1_m_96[index],n2_e_96[index],n2_m_96[index]);
		printf("\n---------------------- end of 2nd stage -------------------------");

		printf("\n-------------------------- 3rd stage ----------------------------");
		if(n1_s_96[index] != n2_s_96[index])
		{
			if(n1_m_96[index] < n2_m_96[index])
			{
				n1_m_96[index] = ~(n1_m_96[index])+1;
				printf("\n2's of n1 = %lx",n1_m_96[index]);
			}
			else
			{
				n2_m_96[index] = ~(n2_m_96[index])+1;
				printf("\n2's of n2 = %lx",n2_m_96[index]);
			}
		}
		else
		printf("\n signs are same so no 2's compliment.");
		printf("\n---------------------- end of 3rd stage -------------------------");

		printf("\n-------------------------- 4th stage ----------------------------");
		ans_m_96[index] = n1_m_96[index] + n2_m_96[index];
		ans_e_96[index] = n1_e_96[index];
		printf("\n%d %x %lx",ans_s_96[index],ans_e_96[index],ans_m_96[index]);
		printf("\n---------------------- end of 4th stage -------------------------");

		printf("\n-------------------------- 5th stage ----------------------------");
		if(n1_s_96[index] != n2_s_96[index])
		{
			ans_m_96[index] &=0x1fffff;
			if(n1_m_96[index] ==0 )
			{
				ans_m_96[index]=ans_m_96[index]<<1;
				ans_e_96[index] -= 1;
			}
			else
			{
				ans_m_96[index]=ans_m_96[index]<<2;
				ans_e_96[index] -= 2;
			}
		}
		else if(n1_s_96[index] == 0 && n2_s_96[index] == 0)
			ans_m_96[index] &= 0x7fffff;
		else
		{
			ans_m_96[index] &= 0x4fffff;
			ans_e_96[index] -= 1;
		}

		printf("\nans = %d %x %lx",ans_s_96[index],ans_e_96[index],ans_m_96[index]);                                //7
		printf("\n---------------------- end of 5th stage -------------------------\n\n");
		getch();
	}
}