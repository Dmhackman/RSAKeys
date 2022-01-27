// Name: Derek Hackman
// Partner Name: Ben Abbott
// Class: Network Security
// Assignment: Project 2 - RSA Key Generation
// Description: Using a provided list of prime numbers user will choose
// two large primes, this will calculate n and then and then find totient of
// n. After it will ask the user for an e and check that it is valid, if it is
// then it will calculate d and print the keys
//--------------------------------------------------------------------------------------------------------------------------


#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <string.h>
using namespace std;


void choosePrimes(unsigned long long int& p, unsigned long long int& q, unsigned long long int primes[]);
void chooseE(unsigned long long int totN, unsigned long long int& e);
bool factorE( unsigned long long int e, unsigned long long int totN);
void calculateD(unsigned long long int e, unsigned long long int totN, unsigned long long int& d);
long long int gcdExtended(long long int a, unsigned long long int b, long long int& x, long long int& y);

int main()
{

	fstream myfile;
	myfile.open("primes.txt", ios::in);
	unsigned long long int primes[200] = { 2ULL, 0 } ;
	cout << "Opening file" << endl;

	if (myfile.is_open())
	{
		/* ok, proceed with reading */
		int i = 0;
		unsigned long long int num;
		while (myfile >> num)
		{
			primes[i] = num; 
			//cout << primes[i] << endl;
			i++;
		}
	}
	else
	{
		cout << "Did not open";
	}

	unsigned long long int p, q, n, e, d, totN; 

	choosePrimes(p, q, primes);

	//cout << endl << p << ' ' << q << endl;

	n = p * q;

	totN = (p - 1) * (q - 1);

	cout << "Value for n: " << n << endl;
	cout << "Value for toteint of n:" << totN << endl;

	chooseE(totN, e);

	calculateD(e, totN, d);

	//cout << d << endl;

	cout << "Public Key : [ " << e << ", " << n << " ]" << endl; 
	cout << "Private Key : [ " << d << ", " << n << " ]" << endl;

	myfile.close();
	return 0;

}

void choosePrimes(unsigned long long int& p, unsigned long long int& q, unsigned long long int primes [])
{

	for (int i = 0; i < 200; i++)
	{
		if (i % 5 == 0)
		{
			cout << endl;
		}
		cout << primes[i] << '\t';
	}
	cout << endl << "Choose two primes from the list provided: " << endl; 
	cout << "Choose a value for p: ";
	cin >> p;

	cout << "Choose a value for q: ";
	cin >> q;

}

void chooseE(unsigned long long int totN, unsigned long long int& e)
{
	cout << endl << "Enter a value for e: ";
	cin >> e; 
	
	bool valid = false;
	valid = factorE(e, totN);
	
	while (!valid)
	{
		valid = factorE(e, totN);
		cout << endl << "Value is not coprime to totient of n, enter a value for e: ";
		cin >> e;
	}

}

bool factorE( unsigned long long int e, unsigned long long int totN)
{
	unsigned long long int factors[1000] = { 2ULL, 0 };
	int j = 0;

	for (int i = 2; i <= e/2; ++i)
	{
		if (e % i == 0)
		{
			factors[j] = i; 
			j++;
		}
	}
	factors[j] = e; 
	j++;

	// Check to make sure it is coprime with totN
	bool coprime = true;

	for (int i = 0; i < j; i++)
	{
		//cout << factors[i]; 
		if (totN % factors[i] == 0)
		{
			coprime = false; 
		}
	}

	return coprime; 
}

void calculateD(unsigned long long int e, unsigned long long int totN, unsigned long long int& d)
{
	long long int x, y, gcd;

	gcd = gcdExtended(e, totN, x, y);

	//cout << x << ' ' << y << endl;

	if (gcd != 1)
	{
		cout << "There is a problem...";
	}

	if (x < 0)
	{
		x = totN + x;
	}

	d = x; 

}

long long int gcdExtended(long long int a, unsigned long long int b, long long int& x, long long int& y) 
{
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	
	long long int x1, y1;
	long long int gcd = gcdExtended(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return gcd;
}