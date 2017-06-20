#include "FibonacciR.hpp"
#include <iostream>

FibonacciR::FibonacciR() 
{

}

FibonacciR::FibonacciR(const long long &n) :n_(&n)
{

}

FibonacciR::~FibonacciR() 
{

}

long long FibonacciR::Fibonacci(const long long &n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

void FibonacciR::PrintFibonacci() 
{
	long long FibonaciNum = Fibonacci(*n_);
	std::cout << *n_ << "th Fibonaci Number: " << FibonaciNum << std::endl;
}