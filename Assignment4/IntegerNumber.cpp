/* CS 590
Assignment 4 
Stevens Institute of Technology
*/

/* 
	Written by Group 9 on  2/22/2015
*/

#include <assert.h>
#include <iostream>

using namespace std;

class IntegerNumber
{
public:
	IntegerNumber();
	IntegerNumber(const char *num);
	IntegerNumber(const IntegerNumber &numObj);

	~IntegerNumber();

	const IntegerNumber& operator=(const IntegerNumber &y);
	const IntegerNumber& operator=(const char *num);
	friend bool operator==(const IntegerNumber &x, const IntegerNumber &y);
	friend bool operator!=(const IntegerNumber &x, const IntegerNumber &y);
	friend bool operator>(const IntegerNumber &x, const IntegerNumber &y);
	friend bool operator>=(const IntegerNumber &x, const IntegerNumber &y);
	friend bool operator<(const IntegerNumber &x, const IntegerNumber &y);
	friend bool operator<=(const IntegerNumber &x, const IntegerNumber &y);
	friend IntegerNumber operator+(const IntegerNumber &x, const IntegerNumber &y);
	friend IntegerNumber operator-(const IntegerNumber &x, const IntegerNumber &y);
	const IntegerNumber& operator+=(const IntegerNumber &y);
	const IntegerNumber& operator-=(const IntegerNumber &y);
	friend ostream& operator<<(ostream &out, const IntegerNumber &in);

	// private member variables
private:
	bool  negative;  // the negative sign of the number
	char *num;    // the integer number
	int   len;    // the length of integer number string
};


// constructors
IntegerNumber::IntegerNumber() {
	num = new char[];
	num[0] = '\0';
	len = 0;
	negative = false;
}

IntegerNumber::IntegerNumber(const char* input) {
	len = 0;
	negative = false;
	int total_len = 0;
	int zero_len = 0;
	int flag = 0;
	const char *temp = input;
	const char *absolute = input;

	if (*input == '-') { 
		negative = true;
		temp = input + 1;
		absolute = input + 1;
	}

	while (*temp) {
		if (flag == 0 && *temp == '0') {
			++zero_len;
		} else {
			flag = 1;
		}
		++total_len;
		++temp;
	}

	len = total_len - zero_len;  
	num = new char[len + 1];
	
	for (int i = 0; i < len; ++i) {
		num[i] = absolute[total_len - i - 1];
	}

	num[len] = 0;
	
	if (0 == len) {
		len = 1;
		delete[] num;
		num = new char[len + 1];
		num[len - 1] = '0';
		num[len] = 0;
		negative = false;
	}
}

// copy constructor
IntegerNumber::IntegerNumber(const IntegerNumber &IntegerNum) {
	len = IntegerNum.len;
	num = new char[len + 1];
	negative = IntegerNum.negative;
	for (int i = 0; i <= len; ++i)
		num[i] = IntegerNum.num[i];
}

IntegerNumber::~IntegerNumber() {
	delete[] num;
	len = 0;
	negative = false;
}

//overload operator=
const IntegerNumber& IntegerNumber::operator=(const IntegerNumber &y) {
		this->len = y.len;
		this->negative = y.negative;
		this->num = new char[len + 1];
		for (int i = 0; i <= len; ++i)
			this->num[i] = y.num[i];

	return *this;
}

// overload operator =
const IntegerNumber& IntegerNumber::operator=(const char *y) {
	len = 0;
	negative = false;
	
	int total_len = 0;
	int zero_len = 0;
	int flag = 0;
	const char *tmp = y;
	const char *absolute = y;
	if (*y == '-') {
		negative = true;
		tmp = y + 1;
		absolute = y + 1;
	}
	while (*tmp) {
		if (0 == flag && '0' == *tmp) {
			++zero_len;
		}
		else {
			flag = 1;
		}
		++total_len;
		++tmp;
	}
	len = total_len - zero_len;
	num = new char[len + 1];
	for (int i = 0; i < len; ++i) {
		num[i] = absolute[total_len - i - 1];
	}
	num[len] = 0;
	if (0 == len) {	
		len = 1;
		delete[] num;
		num = new char[len + 1];
		num[len - 1] = '0';
		num[len] = 0;
		negative = false;
	}
	return *this;
}


// overload operator ==
bool operator==(const IntegerNumber &x, const IntegerNumber &y) {
	
	if (x.len != y.len || x.negative != y.negative)	// different length or negative sign
		return false;
	
	return !strcmp(x.num, y.num);	// compare two number equal or not
}


// overload operator !=
bool operator!=(const IntegerNumber &x, const IntegerNumber &y) {
	return !(x == y);
}


// overload operator >
bool operator>(const IntegerNumber &x, const IntegerNumber &y) {
	if (x == y) return false;

	if (x.negative == false && y.negative == true) return true;	
	
	if (x.negative == true && y.negative == false) return false;	

	bool absolute = true;	
	if (x.len > y.len)
		absolute = true;
	else if (x.len < y.len)
		absolute = false;
	else {
		for (int i = x.len - 1; i >= 0; --i) {
			if (x.num[i] < y.num[i])
				absolute = false;
		}
	}

	if (x.negative == true && y.negative == true) return !absolute;    
	if (x.negative == false && y.negative == false) return absolute;   
	return true;
}

// overload operator >=
bool operator>=(const IntegerNumber &x, const IntegerNumber &y) {
	if (x == y) return true;
	return x > y;
}


// overload operator <
bool operator<(const IntegerNumber &x, const IntegerNumber &y) {
	return !(x >= y);
}


// overload operator <=
bool operator<=(const IntegerNumber &x, const IntegerNumber &y) {
	return !(x > y);
}


IntegerNumber operator+(const IntegerNumber &x, const IntegerNumber &y) {
	IntegerNumber l = x;
	IntegerNumber r = y;
	IntegerNumber result;

	if (l.negative == true && r.negative == true) {	// both negative, do abs values' addition and set result as negative
		l.negative = false;
		r.negative = false;
		result = l + r;
		result.negative = true;
	}
	else if (l.negative == false && r.negative == true) { // x positive and y negative, do (x - y)
		l.negative = false;
		r.negative = false;
		result = l - r;
	}
	else if (l.negative == true && r.negative == false) {	// x negative and y positive, do (y - x)
		l.negative = false;
		r.negative = false;
		result = r - l;
	}
	else {	
		int flag = 0; 
		int ma_len = x.len >= y.len ? x.len : y.len;
		int result_len = 0;
		char *tmp = new char[ma_len + 2];

		for (int i = 0; i < ma_len; ++i) {
			if (i < x.len && i < y.len) {
				tmp[i] = x.num[i] - 48 + y.num[i] - 48 + flag;
			}
			else if (i >= x.len) {
				tmp[i] = y.num[i] - 48 + flag;
			}
			else if (i >= y.len) {
				tmp[i] = x.num[i] - 48 + flag;
			}
			flag = tmp[i] / 10;
			tmp[i] = tmp[i] % 10 + 48;
			++result_len;
		}
		
		if (0 != flag) {
			tmp[ma_len] = 49;
			++result_len;
		}

		char t;
		for (int i = 0; i < result_len / 2; ++i) {
			t = tmp[i];
			tmp[i] = tmp[result_len - i - 1];
			tmp[result_len - i - 1] = t;
		}
		for (int i = 0; i < ma_len + 2 - result_len; ++i) {
			tmp[result_len + i] = 0;
		}
		result.len = result_len;
		
		result = tmp;
		delete[] tmp;
	}

	return result;
}


// overload operator-
IntegerNumber operator-(const IntegerNumber &x, const IntegerNumber &y) {
	IntegerNumber l = x;
	IntegerNumber r = y;
	IntegerNumber result;
	
	if (l.negative == true && r.negative == true) {
		l.negative = false;
		r.negative = false;
		result = r - l;
	}

	else if (l.negative == false && r.negative == true) { 
		l.negative = false;
		r.negative = false;
		result = l + r;
		result.negative = false;
	}

	else if (l.negative == true && r.negative == false) {	
		l.negative = false;
		r.negative = false;
		result = l + r;
		result.negative = true;
	}
	else {	
		int flag = 0, last_flag = 0;
		bool negative = false;
		int ma_len = x.len >= y.len ? x.len : y.len;
		char *tmp = new char[ma_len + 2];
		memset(tmp, 0, ma_len + 2);
		
		IntegerNumber big, small;
		if (x >= y) {
			big = x;
			small = y;
			negative = false;
		}
		else {
			big = y;
			small = x;
			negative = true;
		}
		
		char subtractor;
		for (int i = 0; i < ma_len; ++i) {
			if (i < big.len && i < small.len) {
				subtractor = small.num[i];
			}
			else if (i >= small.len) {
				subtractor = '0';
			}
			flag = 0;
			if (big.num[i] - last_flag < subtractor) {
				big.num[i] += 10;
				flag = 1;
			}
			tmp[i] = big.num[i] - subtractor - last_flag + 48;
			last_flag = flag;
		}

	
		int result_len = 0;
		for (int i = ma_len - 1; i >= 0; --i) {
			if (0 == tmp[i] && 0 == result_len) continue;
			++result_len;
		}

		char t;
		for (int i = 0; i < result_len / 2; ++i) {
			t = tmp[i];
			tmp[i] = tmp[result_len - i - 1];
			tmp[result_len - i - 1] = t;
		}
		for (int i = 0; i < ma_len + 2 - result_len; ++i) {
			tmp[result_len + i] = 0;
		}

		if (0 == result_len) { 
			result_len = 1;
			delete[] tmp;
			tmp = new char[result_len + 1];
			tmp[result_len - 1] = '0';
			tmp[result_len] = 0;
			negative = false;
		}
		result.len = result_len;
	
		result = tmp;
		result.negative = negative;	
	}


	return result;
}

const IntegerNumber& IntegerNumber::operator+=(const IntegerNumber &y) {
	*this = *this + y;
	return *this;
}

const IntegerNumber& IntegerNumber::operator-=(const IntegerNumber &y) {
	*this= *this - y;
	return *this;
}

ostream& operator<<(ostream &out, const IntegerNumber &in) {
	int len = in.len;
	char *output = new char[len + 1];
	
	for (int i = 0; i < len; ++i) {
		output[i] = in.num[len - i - 1];
	}
	output[len] = 0;
	if (in.negative == true)
		out << "-" << output;
	else
		out << output;
	delete[] output;

	return out;
}




int main()
{

	IntegerNumber A;
	// IntegerNumber inect A
	// is created and A contains the integer 0
	
	IntegerNumber B("-12345678954688709764347890"); // IntegerNumber
	// inect B is created and B contains the negative number shown
	// within the quotes " "
	IntegerNumber C = "5678954688709764347890"; // IntegerNumber
	// inect C is created and C contains the positive number shown
	// within the quotes " "
	 // output to screen the
	IntegerNumber D(B); // IntegerNumber inect D is created and
	//D contains the number that B contains
	IntegerNumber E(B);
	
	// IntegerNumber inect E is created and
	// E contains the number that B contains
	A = B; // assigns the value of A to that of B

	cout << A << " " << B << endl; // output to screen the
	// integers in A and B
	C = B + C;
	cout << C << endl; // output to screen the sum of the
	// numbers B and C
	D = B - C;
	cout << D << endl; // output to screen the number B - C
	if (A < B) {
		E += B;
	}
	cout << E << endl; // output to screen the sum of E and B }
	if (A >= B) {
		E -= B;
	}
	cout << E << endl; // output to screen the number E - B }
	if (A == B || C != D) {
		cout << A << E << D << endl; // output to screen the
		//numbers A, E, and D}*/

	}

}
