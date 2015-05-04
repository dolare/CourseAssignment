
public class LinkedListReverse {
     
    public static void main(String args[]) {
            
       LinkedList linkedList = new LinkedList(0);
       linkedList.add(1).add(2).add(3).add(4).add(5).add(6).add(7);
       
       System.out.println("Linked List: " + linkedList.toString());
       
       linkedList = recursiveReverse(linkedList);
       System.out.println("Recursively : "
                + linkedList.toString());
       
       linkedList = iterativeReverse(linkedList);
       System.out.println("Iteratively : "
                + linkedList.toString());
    }
 
    public static LinkedList recursiveReverse(LinkedList linkedList) {

        if (linkedList == null || linkedList.next == null) {
            return linkedList;
        }
 
        LinkedList reverse = recursiveReverse(linkedList.next);
        
        LinkedList current = reverse;
        while (current.next != null) {
            current = current.next;
        }
        
        current.next = linkedList;
        linkedList.next = null;
 
        return reverse;
    }
 
    public static LinkedList iterativeReverse(LinkedList linkedList) {
 
        if (linkedList == null || linkedList.next == null) {
            return linkedList;
        }
 
        LinkedList prev, curr, next;
        prev = null;
        next = null;
        
        curr = linkedList;
        while (curr != null) {
            next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }
        
        return prev;
    }
 
}

class LinkedList {
    public LinkedList next;
    public int value;
 
    public LinkedList(int value) {
        this.value = value;
        this.next = null;
    }
    
    public LinkedList add(int value){
    	LinkedList temp = new LinkedList(value);
    	this.next = temp;
    	temp.next = null;
    	return temp;
    }
 
    public String toString() {
 
        String valueString = "";
        LinkedList current = this;
        do {
            valueString += current.value + " ";
            current = current.next;
        } while (current != null);
 
        return valueString;
    }
}