

#ifndef FIBONACCINR_H_
#define FIBONACCINR_H_
class FibonacciNR 
{
	public:
		FibonacciNR(const long long &n);
		virtual ~FibonacciNR();
		void PrintFibonacci();
	private:
		FibonacciNR();
		long long Fibonacci(const long long &n);
		const long long* n_;
};

#endif /* FIBONACCINR_H_ */
