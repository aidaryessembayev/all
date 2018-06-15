package csci152.impl;

import csci152.adt.*;

public class LinkedListStack<T> implements Stack<T>{
		
	private Node<T> top;
	private int size;
	
	public LinkedListStack() {
		top = null;
		size = 0;
	}
	
	@Override
	public void push(T value) {
		
		Node<T> item = new Node(value);
		
		if (top == null)
		{
			top = item;
		}
		else
		{
			item.setLink(top);
			top = item;
		}

		size++;
		
		
	}

	@Override
	public T pop() throws Exception {
		
		if (size == 0)
		{
			throw new Exception("Stack is empty, you, dumbass");
		}
		
		T toReturn = top.getValue();
		
		top = top.getLink();
		
		size--;
		
		return toReturn;
	}

	@Override
	public int getSize() {
		
		return size;
	}

	@Override
	public void clear() {
		top = null;
		size = 0;
		
	}
	
	public String toString()
	{
		String m = "";
		
		//String s = top.getValue().toString();
		if (top != null)
		{
		m = "";
		
		Node<T> clone = new Node<T>(top.getValue());
		clone.setLink(top.getLink());
		

				while (top != null)
				{
					Node<T> temp = top;
					
					m += temp.getValue().toString() + " ";
					top = top.getLink();
				}
				
		top = clone;
		}
		else
		{
			m = "";
		}
		//s += new StringBuilder(m).reverse().toString();
		return "front-->" + m + "<--back";//new StringBuilder(s).reverse().toString();
	}

}
