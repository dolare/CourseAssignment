
import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.Stack;

public class StackingTheQueue {
	public static void main(String[] args){
		Queues<String> queue = new Queues<String>();
		Stack<String> stack = new Stack<String>();
		Scanner input = new Scanner(System.in);
		String temp = null;
		int length = 0;
		System.out.print("Please enter the queue you want : (finish you use by 'done') "
					+ "\n" + "(Enter items one by one and divide by space"
							+ " \n eg:Hello 2 3 4 world ! done) \n");

		while(true){
			temp = input.next();
			if(temp.equals("done"))break;
			queue.enQueue(temp); 
		}
		
		System.out.println("The queue you entered is:" +  queue + "\n");
		length = queue.size();
		
		System.out.println("The first step from queue to stack: " );
		for (int i = 0; i < length; i++) // first move from Q to S
		{
			stack.push(queue.front());
			queue. deQueue();
			System.out.println("The stack now: " + stack);
		}
		System.out.println();
		
		System.out.println("The second step from queue to stack:" );
		for (int i = 0; i < length; i++) 
		{
			queue. enQueue(stack.pop());
			System.out.println("The stack now: " + stack);	
		}
		System.out.println();
		
		System.out.println("The third step from queue to stack:" );
		for (int i = 0; i < length; i++) 
		{
			stack.push(queue.front());
			queue. deQueue();
			System.out.println("The stack now: " + stack);
		}	
		System.out.println();
		input.close();
	}
}

 class Queues<T extends Comparable<T>> {
    
    private ArrayList<T> items;
     
    public Queues() {
        items = new ArrayList<T>();
    }
    
    public T front(){
    	return items.get(0);
    }
    
    public void enQueue(T item) {
        items.add(item);
    }
       
    public T deQueue() 
    throws NoSuchElementException {
        if (items.size() == 0) {
            throw new NoSuchElementException();
        }
        if (items.size() == 1) {
            return items.remove(0);
        }
        T hold = items.get(0);
        items.remove(0);
        return hold;
    }
 
    public int size() {
        return items.size();
    }
     
    public boolean isEmpty() {
        return items.isEmpty();
         
    }
     
    public String toString() {
        return items.toString();
    }
}