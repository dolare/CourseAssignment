import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Scanner;

public class ASpeicalCaseOfSubsetSum {
	public static void main(String[] args){
		LinkedList<Integer> linkedlist = new LinkedList<Integer>();
		HashSet<Integer> set = new HashSet<Integer>();
		Scanner input1;
		Scanner input2;
		int n = 0;
		int sumOfList = 0;
		int sumOfSet = 0;
		int temp = 0;
		int count = 0;
			
		input1 = new Scanner(System.in);
		System.out.print("Please enter the value of n(which is the largest number of set) : \n");
		
		n = Integer.parseInt(input1.next());
		sumOfSet = n*(n+1)/2;
		
		for(int i = 0;i <= n; i++){
			set.add(i);
		}
		System.out.println(set);
	
			input2 = new Scanner(System.in);
			
		
		System.out.print("Please enter the linkedlist(elements are selected from set) you want to test :"
					+ "\n" + "(You need enter n numbers from 0 to n-1,no duplicates,and divide by space) \n");
			
		for(int i = 0;i < n;i++){
			try{
			 temp = Integer.parseInt(input2.next());
			 if(temp > n || temp < 0){
				 throw new Exception();	 
			 }
			 linkedlist.add(temp);
			 
			}catch(Exception e){
				linkedlist.clear();
				i = -1;
				System.out.println("Error input,please enter again. ");
			}
		}
		Iterator<Integer> it = linkedlist.iterator();
		while(it.hasNext()){
			sumOfList = sumOfList + (int)(it.next());
		}
		
		//print the result of missing items
		
		System.out.print("The missing item is :" + (sumOfSet - sumOfList) );
		
		input1.close();
		input2.close();
	}
}
