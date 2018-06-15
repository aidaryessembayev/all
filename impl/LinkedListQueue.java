package csci152.impl;
import csci152.adt.*;

public class LinkedListQueue<T> implements Queue<T> {

    private Node<T> front;
    private Node<T> back;
    int size;
    
    public LinkedListQueue(){
        front=null;
        back=null;
        size=0;
    }
    @Override
    public void enqueue(T value) {
        Node<T> temp = new Node(value);
        
        if(size == 0){
            front = temp;
            back = temp;
        }
        else{
            back.setLink(temp);
            back = temp;
        }   
        size++;
    }

    @Override
    public T dequeue() throws Exception {
        if(size==0){
            throw new Exception("Queue is empty");
        }
        
        T value=front.getValue();
        front = front.getLink();
        size--;
            
        if(size==0){
            front=null;
            back=null;
        }
            return value;
    }

    @Override
    public int getSize() {
        return size;
    }

    @Override
    public void clear() {
        front=null;
        back=null;
        size=0;        
    }
    
    public String toString(){
        String toReturn = "";
        Node<T> clone = front;
        while(clone!=null){
            toReturn+=clone.toString() + " ";
            clone=clone.getLink();
        }

        return "back--> " + toReturn + "<--front             ";
    }
    
}
