/*
 * primenumbersum.cpp
 *
 *  	Created on: Oct 9, 2012
 *      Author: root
 *      Description: Sums all the primenumbers that are below a give number.
 *
 *      Logic: a vector of long int is defined to store all the prime numbers.
 *      For each number check if it is divisible by any one of the previous prime numbers in the vector.
 *      If it is not divisible by any of the previous prime numbers then it is a prime number and push it back to vector.
 *      In order to speedup just test the division only with primenumbers that are below sqrt(n), because if  n is composite, then it should have
 *      a factor that is less or equal to sqrt(n) .
 *      Other fast and deterministic tests can be performed by using fermat's little theorem.
 *
 */


#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<vector>
using namespace std;

int main()
{


	vector<long int> primevector ;
	long long int totalprimesum ;
	long int totalprimenumbercount ;
	long int givennumber ;
	std::cout<< "Enter a number ";
	std::cin >> givennumber ;
	std::cout<<" The number read is "<<givennumber<<"\n";
	//primevector[0]= 2 ;
	primevector.push_back(2) ;
	totalprimesum = 2 ;
	totalprimenumbercount =1 ;
	bool primeflag= false ;
	for (long int i=3 ;i<givennumber ; i++)
		{    primeflag = true ;

			for (long int j=0 ; j< totalprimenumbercount ; j++)
				{
					if (i%primevector.at(j) == 0)
					{	  primeflag = false ;
						  break ;
					}
					if(primevector.at(j) > sqrt(i))
						break ;
				}

			if(primeflag == true )
			{
				primevector.push_back(i) ;
				totalprimesum+=i ;
				totalprimenumbercount++ ;

			}

		}


std::cout<<"Sum of all the prime numbers less than givennumber is "<< totalprimesum
		<<" and total prime number count is " << totalprimenumbercount <<"\n";

}



