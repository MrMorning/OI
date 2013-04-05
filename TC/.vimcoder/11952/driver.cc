
#include "GreedyTravelingSalesman.cc"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <vector>

using namespace std;


static double __time = 0.0;

static void __timer_start()
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == 0)
	{
		__time = (double)tv.tv_sec + (double)tv.tv_usec * 0.000001;
	}
}

static double __timer_stop()
{
	double start = __time;
	__timer_start();
	return __time - start;
}


std::ostream& operator << (std::ostream& out, const std::string& str)
{
	out << '"' << str.c_str() << '"';
	return out;
}

template <class T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vec)
{
	out << '{';
	if (0 < vec.size())
	{
		out << vec[0];
		for (size_t i = 1; i < vec.size(); ++i) out << ", " << vec[i];
	}
	out << '}';
	return out;
}

std::istream& operator >> (std::istream& in, std::string& str)
{
	while (in.good() && std::isspace(in.peek())) in.get();

	int c;
	if (in.good() && (c = in.get()) == '"')
	{
		std::ostringstream s;
		while (in.good() && (c = in.get()) != '"')
		{
			s.put(char(c));
		}
		str = s.str();
	}
	else
	{
		in.putback(c);
	}

	return in;
}

template <class T>
std::istream& operator >> (std::istream& in, std::vector<T>& vec)
{
	while (in.good() && std::isspace(in.peek())) in.get();

	int c;
	if (in.good() && (c = in.get()) == '{')
	{
		while (in.good() && std::isspace(in.peek())) in.get();
		T t;
		vec.clear();
		while (in.good() && (c = in.get()) != '}')
		{
			if (c != ',') in.putback(c);
			in >> t;
			vec.push_back(t);
			while (in.good() && std::isspace(in.peek())) in.get();
		}
	}
	else
	{
		in.putback(c);
	}

	return in;
}


int main(int argc, char* argv[])
{
	bool	__exit_on_fail = false;
	int	__pass = 0;
	int	__fail = 0;
	
	if (1 < argc) __exit_on_fail = true;
	
	std::ifstream __in("testcases.txt");
	for(;;)
	{
		int	__expected;
		vector <string>	thousands;
vector <string>	hundreds;
vector <string>	tens;
vector <string>	ones;

		__in >> __expected >> thousands >> hundreds >> tens >> ones;
		if (!__in.good()) break;
		
		std::cout << "----------------------------------------" << std::endl
			  << "Test " << (__pass + __fail) << ": ";
		std::cout.flush();
		
		__timer_start();
		
		GreedyTravelingSalesman object;
		int __actual = object.worstDistance(thousands, hundreds, tens, ones);
		
		double __t = __timer_stop();
		
		if (__actual == __expected)
		{
			std::cout << "[PASS] in " << __t << " seconds." << std::endl;
			++__pass;
		}
		else
		{
			std::cout << "[FAIL] in " << __t << " seconds." << std::endl
				  << "->  Input: " << thousands << ", " << hundreds << ", " << tens << ", " << ones << std::endl
				  << "   Actual: " << __actual << std::endl
				  << " Expected: " << __expected << std::endl;
			++__fail;
			if (__exit_on_fail) exit(1);
		}
	}

	std::cout << "========================================" << std::endl
		  << " Total Pass: " << __pass << std::endl
		  << " Total Fail: " << __fail << std::endl;

	if (__fail == 0)
	{
		std::cout << std::endl << "Nice!  "
			  << "Don't forget to compile remotely before submitting."
			  << std::endl;
	}

	return __fail;
}

