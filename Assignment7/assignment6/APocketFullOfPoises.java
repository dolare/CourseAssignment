import java.util.ArrayList;
import java.util.Scanner;

public class APocketFullOfPoises{
	public static void main(String[] args){
		int n = 0;
		int k = 0;
		int index = 0;
		boolean bool = true;
		int[] array = null;
		Scanner input = new Scanner(System.in);
		while(bool){
			try{
				System.out.println("Please enter the size of array:");
				n = Integer.parseInt(input.next());
				if(n <= 0){
					throw new Exception();
				}
				array = new int[n];
				for(int i = 0 ; i < n;i++){
				array[i] = i;
				}
				bool = false;
			}catch(Exception e){
				System.out.println("Error input,please input again(n must be positive number) ");
				e.printStackTrace();
			}	
		}
		
		while(!bool){
			try{
				input = new Scanner(System.in);
				System.out.println("Please enter the value of k you want to test(0-n): ");
				k = Integer.parseInt(input.next());
				if(k < 0 || k > n)throw new Exception();
				bool = true;
			}catch(Exception e){
					System.out.println("Error input,please input again:(k must be numbers from 0-n)");
			}
		}
		
		index = n;
		System.out.print( "The array before shift : \n");
		for(int i :array){
			System.out.print( i + " ");
		}
		
		while((index - 1 - k) > 0){
			array[index - 1]= array[index - 1] + array[index - 1 - k];
			array[index - 1 - k] = array[index - 1] - array[index - 1 - k];
			array[index - 1] = array[index - 1] - array[index - 1 - k];
			index--;
		}
		
		System.out.println();
		System.out.print( "The array after shift : \n");
		for(int i :array){
			System.out.print( i + " ");
		}
		input.close();
	}
	
}
		
		
