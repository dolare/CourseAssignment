/* CS 590
Assignment 4 
Stevens Institute of Technology

	Written by Group 9 on  2/22/2015
*/


#include <iostream>

using namespace std;

class IntegerNumber
{
public:
	IntegerNumber();
	IntegerNumber(const char *input);
	IntegerNumber(const IntegerNumber &IntegerNum);

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

	
private:
	bool  negative;  // the negative sign of the number
	char *num;    // the integer number
	int   len;    // the length of integer number string
};


/*constructor without initial values*/
IntegerNumber::IntegerNumber() {
	this->num = new char;
	this->num[0] = '\0';
	this->len = 0;
	this->negative = false;
}

/*constructor with initial values*/
IntegerNumber::IntegerNumber(const char* input) {
	this->len = 0;
	this->negative = false;
	int total_len = 0;
	int zero_len = 0;
	bool boolean = false;
	const char *temp = input;
	const char *temp1 = input;

	if (*input == '-') { 
		negative = true;
		temp = input + 1;
		temp1 = input + 1;
	}

	while (*temp) {
		if (!boolean && *temp == '0') {
			++zero_len;
		} else {
			boolean = true;
		}
		++total_len;
		++temp;
	}

	this->len = total_len - zero_len;
	this->num = new char[len + 1];
	
	for (int i = 0; i < len; ++i) {
		this->num[i] = temp1[total_len - i - 1];
	}

	this->num[len] = 0;
	
	if (0 == len) {
		len = 1;
		
		this->num = new char[len + 1];
		this->num[len - 1] = '0';
		this->num[len] = 0;
		this->negative = false;
	}
}

/*constructor with initial values from another IntegerNumber*/
IntegerNumber::IntegerNumber(const IntegerNumber &IntegerNum) {
	this->len = IntegerNum.len;
	this->num = new char[len + 1];
	this->negative = IntegerNum.negative;
	for (int i = 0; i <= len; ++i)
		this->num[i] = IntegerNum.num[i];
}


IntegerNumber::~IntegerNumber() {
	delete[] num;
	this->len = 0;
	this->negative = false;
}

/* overload operator=*/
const IntegerNumber& IntegerNumber::operator=(const IntegerNumber &y) {
		this->len = y.len;
		this->negative = y.negative;
		this->num = new char[len + 1];
		for (int i = 0; i <= len; ++i)
			this->num[i] = y.num[i];

	return *this;
}

/*overload operator= */ 
const IntegerNumber& IntegerNumber::operator=(const char *y) {
	this->len = 0;
	this->negative = false;
	
	int total_len = 0;
	int zero_len = 0;
	bool boolean = false;
	const char *temp = y;
	const char *temp1 = y;
	if (*y == '-') {//If the IntegerNumber is negative
		this->negative = true;
		temp = y + 1;
		temp1 = y + 1;
	}
	while (*temp) {
		if (!boolean && '0' == *temp) {
			++zero_len;
		}
		else {
			boolean = true;
		}
		++total_len;
		++temp;
	}
	this->len = total_len - zero_len;
	this->num = new char[len + 1];
	for (int i = 0; i < len; ++i) {
		num[i] = temp1[total_len - i - 1];
	}
	this->num[len] = 0;
	if (0 == len) {	
		len = 1;
		
		this->num = new char[len + 1];
		this->num[len - 1] = '0';
		this->num[len] = 0;
		this->negative = false;
	}
	return *this;
}


/* overload operator == */ 
bool operator==(const IntegerNumber &x, const IntegerNumber &y) {

	if (x.len != y.len)
		return false;
	if (x.negative != y.negative)
		return false;
	
	return !strcmp(x.num, y.num);	// compare two number equal or not
}


/* overload operator !=*/
bool operator!=(const IntegerNumber &x, const IntegerNumber &y) {
	return !(x == y);
}

/*overload operator >*/  
bool operator>(const IntegerNumber &x, const IntegerNumber &y) {

	if (x == y) return false;

	if (x.negative == false && y.negative == true) return true;	
	
	if (x.negative == true && y.negative == false) return false;	
	
	if (x.negative == true && y.negative == true){
		if (x.len > y.len)
			return false;
		else if (x.len < y.len)
			return true;
		else {
			for (int i = x.len - 1; i >= 0; --i) {
				if (x.num[i] < y.num[i])
					return true;
			}
		}
}
	if (x.negative == false && y.negative == false){
		if (x.len > y.len)
			return true;
		else if (x.len < y.len)
			return false;
		else {
			for (int i = x.len - 1; i >= 0; --i) {
				if (x.num[i] < y.num[i])
					return false;
			}
		}
	}
	return true;
}

/*overload operator >=*/  
bool operator>=(const IntegerNumber &x, const IntegerNumber &y) {
	if (x == y) return true;
	return x > y;
}


/*overload operator <*/  
bool operator<(const IntegerNumber &x, const IntegerNumber &y) {
	return !(x >= y);
}


/*overload operator <=*/  
bool operator<=(const IntegerNumber &x, const IntegerNumber &y) {
	return !(x > y);
}

/*overload operator +*/
IntegerNumber operator+(const IntegerNumber &x, const IntegerNumber &y) {
	IntegerNumber left = x;
	IntegerNumber right = y;
	IntegerNumber result;

	if (left.negative == true && right.negative == true) {	// both negative, do abs values' addition and set result as negative
		left.negative = false;
		right.negative = false;
		result = left + right;
		result.negative = true;
	}
    else if (left.negative == true && right.negative == false) {	// x negative and y positive, do (y - x)
		left.negative = false;
		right.negative = false;
		result = right - left;
	}

	else if (left.negative == false && right.negative == true) { // x positive and y negative, do (x - y)
		left.negative = false;
		right.negative = false;
		result = left - right;
	}

	else if (left.negative == false && right.negative == false){
		int Isop = 0; 
		int temp_len = x.len >= y.len ? x.len : y.len;
		int result_len = 0;
		char *temp = new char[temp_len + 2];

		for (int i = 0; i < temp_len; ++i) {
			if (i < x.len && i < y.len) {
				temp[i] = x.num[i] - 48 + y.num[i] - 48 + Isop;
			}
			else if (i >= x.len) {
				temp[i] = y.num[i] - 48 + Isop;
			}
			else if (i >= y.len) {
				temp[i] = x.num[i] - 48 + Isop;
			}
			Isop = temp[i] / 10;
			temp[i] = temp[i] % 10 + 48;
			result_len++;
		}
		
		if (0 != Isop) {
			temp[temp_len] = 49;
			result_len++;
		}

		for (int i = 0; i < result_len / 2; i++) {
			char t;
			t = temp[i];
			temp[i] = temp[result_len - i - 1];
			temp[result_len - i - 1] = t;
		}

		for (int i = 0; i < temp_len + 2 - result_len; i++) {
			temp[result_len + i] = 0;
		}
		result.len = result_len;
		
		result = temp;
		
	}

	return result;
}


/*overload operator-*/ 
IntegerNumber operator-(const IntegerNumber &x, const IntegerNumber &y) {
	IntegerNumber left = x;
	IntegerNumber right = y;
	IntegerNumber result;
	
	if (left.negative == true && right.negative == true) {
		left.negative = false;
		right.negative = false;
		result = right - left;
	}

	else if (left.negative == true && right.negative == false) {	
		left.negative = false;
		right.negative = false;	
		result = left + right;
	}
	
	else if (left.negative == false && right.negative == true) { 
		left.negative = false;
		right.negative = false;
		result = left + right;	
	}

	else if(left.negative == false && right.negative == false){
		int Isop = 0;
		int last_bit = 0;
		int temp_len = x.len >= y.len ? x.len : y.len;
		int result_len = 0;
		bool negative = false;
		char *temp = new char[temp_len + 2];
		char subtractor;
	    

		memset(temp, 0, temp_len + 2);
		
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
	
		for (int i = 0; i < temp_len; ++i) {
			if (i < big.len && i < small.len) {
				subtractor = small.num[i];
			}
			else if (i >= small.len) {
				subtractor = '0';
			}
			Isop = 0;
			if (big.num[i] - last_bit < subtractor) {
				big.num[i] += 10;
				Isop = 1;
			}
			temp[i] = big.num[i] - subtractor - last_bit + 48;
			last_bit = Isop;
		}

		for (int i = temp_len - 1; i >= 0; --i) {
			if (0 == temp[i] && 0 == result_len) continue;
			result_len++;
		}

		
		for (int i = 0; i < result_len / 2; ++i) {
			char t;
			t = temp[i];
			temp[i] = temp[result_len - i - 1];
			temp[result_len - i - 1] = t;
		}
		for (int i = 0; i < temp_len + 2 - result_len; ++i) {
			temp[result_len + i] = 0;
		}

		if (0 == result_len) { 
			result_len = 1;
			temp = new char[result_len + 1];
			temp[result_len - 1] = '0';
			temp[result_len] = 0;
			negative = false;
		}
		result.len = result_len;
	
		result = temp;
		result.negative = negative;	
	}


	return result;
}

/*overload operator +=*/
const IntegerNumber& IntegerNumber::operator+=(const IntegerNumber &y) {
	*this = *this + y;
	return *this;
}

/*overload operator -=*/
const IntegerNumber& IntegerNumber::operator-=(const IntegerNumber &y) {
	*this= *this - y;
	return *this;
}

/*overload operator << to print out*/
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

	return out;
}




int main()
{
	IntegerNumber A;
	// IntegerNumber object A
	// is created and A contains the integer 0

	IntegerNumber B("-12345678954688709764347890"); // IntegerNumber
	// object B is created and B contains the negative number shown
	// within the quotes " "
	IntegerNumber C = "5678954688709764347890"; // IntegerNumber
	// object C is created and C contains the positive number shown
	// within the quotes " "
	IntegerNumber D(B); // IntegerNumber object D is created and
	//D contains the number that B contains
	IntegerNumber E(B);
	// IntegerNumber object E is created and
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
