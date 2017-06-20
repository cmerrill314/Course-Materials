#ifndef FIBONACCIR_H_
#define FIBONACCIR_H_

class FibonacciR 
{
	public:
		FibonacciR(const long long &n);
		virtual ~FibonacciR();
		void PrintFibonacci();
	private:
		FibonacciR();
		long long Fibonacci(const long long &n);
		const long long *n_;
};

#endif /* FIBONACCIR_H_ */
