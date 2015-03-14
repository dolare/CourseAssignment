/* CS590

Assignment 4

Roy Vaccaro

 */
package test1;

import java.util.*;
import java.lang.*;


public class IntegerNumber {

    public int[] intNum;
    public int sign = 1;


    public IntegerNumber() //Default constructor
    {

        intNum = new int[]{0};

    }

    public IntegerNumber(String a) // String assignment
    {
        /* Check if the first character of the string is a - sign.   If so make sure we make the 0 element of intNum negative */


        if (String.valueOf(a.charAt(0)).matches("-")) {

            sign = -1;
            a = a.substring(1);

        }

        intNum = new int[a.length()]; // initialize array to length of string


        for (int i = 0; i < a.length(); i++) {
            try {
                intNum[i] = Integer.parseInt(String.valueOf(a.charAt(i)));
            } catch (NumberFormatException nfe) {
            }
            ;
        }

        //intNum[0] = intNum[0] * sign; //Set the sign


    }

    public IntegerNumber(IntegerNumber b) //Copy constructor
    {

        intNum = new int[b.intNum.length];

        System.arraycopy((Object) b.intNum, 0, (Object) intNum, 0, b.intNum.length);


    }

    /* This function returns a NEW IntegerNumber that represents this + other*/
    public IntegerNumber add(IntegerNumber other) {

        IntegerNumber result = new IntegerNumber();
        int carry = 0;
        int i, j;
        int newSize = Math.max(intNum.length, other.intNum.length) + 1;  //Get the new size with room for carry;
        result.resize(newSize);

        for (i = Math.max(intNum.length, other.intNum.length) - 1, j = 0; (i >= 0 && j < newSize); i--, j++) {

            int res = getValAtIndex(intNum, i) + other.getValAtIndex(other.intNum, i) + carry;
            carry = res / 10; //Get the next carry;
            result.intNum[j] = res % 10; //The digit will be the result mod 10

        }

        result.intNum[j] = carry;
        if (!isPositive() && !other.isPositive()) {
            result.sign = -1;
        }


        return result;

    }


    /*Will get the value at the index or return 0  Used for math operations when we can go out of bounds*/
    public int getValAtIndex(int[] inArr, int index) {
        if (index < inArr.length) {
            return inArr[index];
        } else {
            return 0;
        }
    }

    public void setValAtIndex(int index, int val) {
        if (index > intNum.length) {
            resize(index + 1);

            intNum[index] = val;
        }
    }

    /* This function returns a NEW integer number that represents this - other*/
    public IntegerNumber sub(IntegerNumber other) {

        IntegerNumber result = new IntegerNumber();
        int carry = 0;
        int i, j;
        int newSize = Math.max(intNum.length, other.intNum.length) + 1;  //Get the new size with room for carry;
        result.resize(newSize);


        /*Subtraction case 1 both positive*/
        if ((isPositive() && other.isPositive()) || (!isPositive() && !other.isPositive())) {
            if (geq(other)) {

                result.intNum = arrSub(revArray(intNum), revArray(other.intNum));

            } else {

                result.intNum = arrSub(revArray(other.intNum), revArray(intNum));
                result.sign = -1;

            }
        } else if (isPositive() && !other.isPositive()) {//1 pos 1 neg becomes addition
            result = add(other);

        } else if (!isPositive() && other.isPositive()) {//negative on top
            result = add(other);
            result.sign = -1;
        } else {
        }

        return result;
    }

    /* Reverses the integer array */
    public int[] revArray(int[] inArr) {
        int[] reverse = new int[inArr.length];
        int i, j;
        for (i = 0, j = inArr.length - 1; (i < inArr.length && j >= 0); i++, j--) {
            reverse[j] = inArr[i];
        }

        return reverse;
    }


    public int[] arrSub(int[] big, int[] small) {
        int i, j;
        int borrow;
        int[] result = new int[big.length];

        for (i = 0, j = big.length - 1; (i < big.length && j >= 0); i++, j--) {
            if (getValAtIndex(big, i) < getValAtIndex(small, i)) {
                big[i] += 10;//Handle borrow
                big[i + 1] -= 1;
                result[j] = getValAtIndex(big, i) - getValAtIndex(small, i);
            } else {
                result[j] = getValAtIndex(big, i) - getValAtIndex(small, i);
            }
        }
        return result;
    }


    /* This function replaces this with this+other */
    public void plusEquals(IntegerNumber other) {
        IntegerNumber result = add(other);
        intNum = result.intNum;
        sign = result.sign;

    }

    /* This function replaces this with this-other*/
    public void minusEquals(IntegerNumber other) {
        IntegerNumber result = sub(other);
        intNum = result.intNum;
        sign = result.sign;
    }

    /*This function returns true iff this < other*/
    public boolean lessThan(IntegerNumber other) {

        //Check Equality first
        if (equals(other)) {
            return false;
        }
        // Check positive and negative.    Can short circuit here.
        if (!isPositive() && other.isPositive()) {
            return true;
        }
        if (isPositive() && !other.isPositive()) {
            return false;
        }

        // Signs are the same so now checking length
        if (intNum.length < other.intNum.length) {
            return true;
        }

        if (intNum.length > other.intNum.length) {
            return false;
        }

        //Same Length Same sign.   Need to traverse until we find a difference
        for (int i = 0; i < other.intNum.length; i++) {
            if (intNum[i] < other.intNum[i]) {
                return true;
            } else if (intNum[i] > other.intNum[i]) {
                return false;
            } else {
            }
        }

        return false;
    }

    /*THis function returns true iff this > other*/
    public boolean greaterThan(IntegerNumber other) {

        //Check Equality first
        if (equals(other)) {
            return false;
        }
        // Check positive and negative.    Can short circuit here.
        if (isPositive() && !other.isPositive()) {
            return true;
        }
        if (!isPositive() && other.isPositive()) {
            return false;
        }

        // Signs are the same so now checking length
        if (intNum.length > other.intNum.length) {
            return true;
        }

        if (intNum.length < other.intNum.length) {
            return false;
        }

        //Same Length Same sign.   Need to traverse until we find a difference
        for (int i = 0; i < intNum.length; i++) {
            if (intNum[i] > other.intNum[i]) {
                return true;
            } else if (intNum[i] < other.intNum[i]) {
                return false;
            } else {
            }
        }

        return false;
    }


    /*This function returns true iff this >= other*/
    public boolean geq(IntegerNumber other) {
        if ((equals(other)) || (greaterThan(other))) {
            return true;
        }

        return false;

    }

    /*This function returns true iff this <= other */
    public boolean leq(IntegerNumber other) {
        if ((equals(other)) || (lessThan(other))) {
            return true;
        }

        return false;

    }

    /*This function returns true iff this == other */
    public boolean equals(IntegerNumber other) {

        // Check positive and negative.    Can short circut here.
        if (!isPositive() && other.isPositive()) {
            return false;
        }
        if (isPositive() && !other.isPositive()) {
            return false;
        }

        // Signs are the same so now checking length
        if (intNum.length < other.intNum.length) {
            return false;
        }

        if (intNum.length > other.intNum.length) {
            return false;
        }

        //Same Length Same sign.   Need to traverse until we find a difference
        for (int i = 0; i < intNum.length; i++) {
            if (intNum[i] != other.intNum[i]) {
                return false;
            }
        }
        return true;

    }

    /*This function returns true iff this != other*/
    public boolean notEquals(IntegerNumber other) {
        // Check positive and negative.    Can short circut here.
        if (!isPositive() && other.isPositive()) {
            return true;
        }
        if (isPositive() && !other.isPositive()) {
            return true;
        }

        // Signs are the same so now checking length
        if (intNum.length < other.intNum.length) {
            return true;
        }

        if (intNum.length > other.intNum.length) {
            return true;
        }

        //Same Length Same sign.   Need to traverse until we find a difference
        for (int i = 0; i < intNum.length; i++) {
            if (intNum[i] != other.intNum[i]) {
                return true;
            }
        }
        return false;

    }

    /* This function prints the current IntegerNumber*/
    public void print() {
        intNum[0] = intNum[0] * sign;
        for (int i = 0; i < intNum.length; i++) {
            System.out.print(intNum[i]);
        }

    }


    /* Convenience function to check sign */
    public boolean isPositive() {

        if (sign >= 0) {
            return true;
        }
        return false;

    }

    public void resize(int newSize) {

        int[] tIntNum = new int[newSize];
        for (int i = 0; i < Math.min(newSize, intNum.length); i++) {
            tIntNum[i] = intNum[i];
        }
        intNum = tIntNum;

    }

}

