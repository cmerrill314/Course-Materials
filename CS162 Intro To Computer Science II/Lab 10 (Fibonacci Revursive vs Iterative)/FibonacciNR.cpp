#include "FibonacciNR.hpp"
#include <iostream>

FibonacciNR::FibonacciNR() 
{

}

FibonacciNR::FibonacciNR(const long long &n):n_(&n)
{

}

FibonacciNR::~FibonacciNR() 
{

}

long long FibonacciNR::Fibonacci(const long long &n)
{
	long long first = 0;
	long long second = 1;
	long long counter = 2;

	while (counter < n)
	{
		long long temp = second;
		second = first + second;
		first = temp;
		++counter;
	}

	if (n == 0)
		return 0;
	else
		return first + second;
}

void FibonacciNR::PrintFibonacci() 
{
	const long long result = Fibonacci(*n_);
	std::cout << *n_ << "th Fibonacci Number:" <<  result << std::endl;
}