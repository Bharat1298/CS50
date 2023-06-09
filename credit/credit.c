#include <cs50.h>
#include <stdio.h>

int checksum(long card);
long placeholder = 10;
long placeholder2 = 1;
int count = 0;
int sum1 = 0;
int sum2 = 0;
int totalSum = 0;
long num1 = 0;
long num2 = 0;

int main(void)
{
    long cardNum = get_long("Card: ");

    int sum = checksum(cardNum);

	long digitCount = cardNum;

	for (long digits = 0; digitCount > 0; digits++){
	digitCount /= 10;
	count++;
	}

    if((sum % 10) == 0){
        if((count) == 13){
			printf("VISA\n");
		}else if(count == 15 && ((cardNum / 10000000000000 == 34) || (cardNum / 10000000000000 == 37))){
			printf("AMEX\n");
		}else if(count == 16){
			if (cardNum / 1000000000000000 < 5){
				printf("VISA\n");
			}else if((cardNum / 100000000000000 < 56) && (cardNum / 100000000000000 > 50)){
				printf("MASTERCARD\n");
			}else{
				printf("INVALID\n");
			}
		}else{
			printf("INVALID\n");
		}
    }else{
        printf("INVALID\n");
    }
}

int checksum(long card){

long cardnum = card / 10;
long cardnum2 = card;

for (int i = 0; cardnum > 0; i++){
	long remainder = cardnum % 10; //gets tens place remainder
	cardnum /= 100; //shifts card value by two places

	//for every iteration, need a multiplier to put remainder in correct space

	num1 += remainder * placeholder;

	placeholder *= 100;
}

for (int k = 0; cardnum2 > 0; k++){ // GIVES EVERY OTHER NUMBER STARTING FROM SECOND TO LAST
	long remainder2 = cardnum2 % 10; //gets tens place remainder
	cardnum2 /= 100; //shifts card by two places

	//for every iteration, need a multiplier to put remainder in correct space

	sum2 += remainder2;

	num2 += remainder2 * placeholder2;

	placeholder2 *= 100;
}
// stores numbers: repeat the loop but make each remainder multiply by two and store into an array

int remainders[30];

for (int j = 1; num1 > 0; j++) { //loop with array
	remainders[j] = (num1 % 10) * 2;
	num1 /= 10;
	if (remainders[j] >= 10){
		int x = remainders[j];
		// printf("Iteration: %li\n", j);
		// printf("Value: %li\n", x);
		sum1 += x % 10;
		x /= 10;
		sum1 += x % 10;
	}else{
		sum1 += remainders[j];
	}
}
// GIVES SUM OF MULTIPLIED DIGITS

totalSum = sum1 + sum2;

// printf("Sum 1: %li\n", sum1);
// printf("Sum 2: %li\n", sum2);
//printf("Total Sum: %i\n", totalSum);

return totalSum;
}