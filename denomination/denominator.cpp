/*
 * denominator.cpp
 *
 *  Created on: Oct 9, 2012
 *      Author: root
 *      Description: Program to denominate a Dollar number into $100, $50, $20, $10, $5, $1, $0.25, $0.10, $0.05 and $0.01
 */


#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

using namespace std;

int main()
{

	// intialize appropriate variables
	double given_number ;
	double denominator_array[]= { 100.0, 50.0, 20.0, 10.0, 5.0 , 1.0, 0.25, 0.10, 0.05, 0.01 } ;
	int max_denominations= 10 ;
	float denomination_factor ;
	double total_sum_denominated_sofar =0 ;

	// read the Dollar number
	std::cout<<"\n Please enter a dollar amount to be denominated \n" ;
	std::cin>> given_number ;

	//Logic : iteratively divide the Remaining amount with denominators  ( decreasing order )
	// and then calculate the integral value of the quotient.
	//The  Remaining amount is equal to given number minus amount denominated so far

	std::cout<<"\n The following  is the denomination  of the given dollar amount for least possible bills/coin criteria" ;
	for (int array_index=0; array_index<max_denominations ; array_index++ )
		{
			denomination_factor=   ( (given_number - total_sum_denominated_sofar ) /( denominator_array[array_index])) ;
			denomination_factor =  floor(denomination_factor) ;
			std::cout<<"\n The total # of $"<< denominator_array[array_index] << " bills/coins = " << denomination_factor ;
			total_sum_denominated_sofar+= denominator_array[array_index]*denomination_factor  ;
		}

  std::cout<<"\n End of the program \n"  ;

}
