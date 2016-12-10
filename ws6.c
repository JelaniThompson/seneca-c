/*/*
== Banking - Savings Account ==

Author  : Jelani Thompson
Date    : 10/20/2016
Revision:
Workshop: #6 in-Lab

*/

#include <stdio.h>


// Structure Declaration for account
struct account
{
	int accNumber;                          // Account number
	double balance;                         // Balance of the account
};

/*  Function to add an amount if positive-valued */
double balanceUp(double balance, double amount) {
  if (amount > 0) {
    balance += amount;
  }
  return balance;
}

/* Function to calculate the interest rate*/
double interestCalc(double balance, double rate) {
  double monthlyInterest;
  monthlyInterest = balance * (rate/100);
  return monthlyInterest;
}


/* main program */
int main()
{
	const int nosClients = 5;                                                       // Number of accounts
	int option,
	    i;
	int accountNumber;
	float interestRate;
	// Hold the selection
	// Initialize the struct account array with opening balance
	struct account acct[] = { { 11111111, 123.45 },{ 22222222, 12365.50 },{ 33333333,0 },{ 44444444,1475 },{ 55555555,25000.65 } };
    double deposit;
	printf("***** Welcome to Savings Account Banking *****\n\n");

	do
	{
		// Print the option list
		printf("1.) Deposit \n");
		printf("2.) Withdraw\n");
		printf("3.) Apply monthly interest earnings to all accounts\n");
		printf("4.) Apply service charges to all accounts\n");
		printf("5.) Account Summary\n");
		printf("0.) Log out\n\n");
		printf("Please enter an option to continue: ");
		
		// Waiting for the input
		scanf("%d", &option);
        printf("\n");
		switch (option)
		{
		case 0: // Exit the program
			break;

		case 1: // Deposit
            printf("-- Make a deposit --\n\n");
			printf("Enter account number: ");
			scanf("%d", &accountNumber);
            // Check for account number
            // search(struct account acct[], int nosClient);
            int found = 0; 
            for (i = 0; i < nosClients; i++) {
                if(accountNumber == acct[i].accNumber) {
                    found = 1;
                    //i = nosClients; or break;
                    break;
                }
            }

            if (found) {
                printf("Enter amount to deposit (CAD): ");
                scanf("%lf", &deposit);
                acct[i].balance = balanceUp(acct[i].balance, deposit);
                printf("Current balance is : %.2lf\n\n", acct[i].balance);
            } else {
                printf("ERROR: Account number does not exist.\n\n");
            }
		break;
		case 2: // Withdraw funds
				//@HOME


			break;

		case 3: 
        // Apply interest earnings to all account
            printf("-- Add monthly interest earnings to all accounts --\n\n");
            printf("Account# New Balance Interest Earnings (M)\n");
            printf("-------- ----------- ---------------------\n");
			for (i = 0; i < nosClients; i++) {
				if (acct[i].balance < 500) {
				  interestRate = 0.99;
				  double calcInterest = interestCalc(acct[i].balance, interestRate);
                  acct[i].balance = balanceUp(acct[i].balance, calcInterest);
                  //printf("Account# New Balance Interest Earnings (M)\n");
                  //printf("-------- ----------- ---------------------\n");
                  printf("%8d %11.2lf %21.2lf\n", acct[i].accNumber, acct[i].balance, calcInterest);
				}
				else if (acct[i].balance > 500 && acct[i].balance <= 1500) {
				  interestRate = 1.66;
                  double calcInterest = interestCalc(acct[i].balance, interestRate);
				  acct[i].balance = balanceUp(acct[i].balance, calcInterest);
                  //printf("Account# New Balance Interest Earnings (M)\n");
                  //printf("-------- ----------- ---------------------\n");
                  printf("%8d %11.2lf %21.2lf\n", acct[i].accNumber, acct[i].balance, calcInterest);
                }
				else {
				  interestRate = 2.49;
                  double calcInterest = interestCalc(acct[i].balance, interestRate);
                  acct[i].balance = balanceUp(acct[i].balance, calcInterest);
			      //printf("Account# New Balance Interest Earnings (M)\n");
                  //printf("-------- ----------- ---------------------\n");
                  printf("%8d %11.2lf %21.2lf\n", acct[i].accNumber, acct[i].balance, calcInterest);
                }
			}	
        printf("\n");    
		break;

		case 4: // Apply Service Charges
				//@HOME


			break;

		case 5: // Display Account Information
				//@IN-LAB
            printf("-- Account information --\n\n");
            printf("Account# Balance   \n");
            printf("-------- ----------\n");
            for(i = 0; i < nosClients; i++) {
                printf("%8d %10.2lf\n", acct[i].accNumber, acct[i].balance);
            }
            printf("\n");
			break;

		default:
			printf("Error: Please enter a valid option to continue\n");
			break;
		}

    }  while (option != 0); 
	return 0;
}
