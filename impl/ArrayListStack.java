package csci152.impl;
import csci152.adt.*;
import java.util.ArrayList;

public class ArrayListStack<T> implements Stack<T> {
	
	private ArrayList<T> aidar;
	
	public ArrayListStack()
	{
		aidar = new ArrayList<T>();
	}

	@Override
	public void push(T value) {
		aidar.add(value);
		
	}

	@Override
	public T pop() throws Exception {
		if (aidar.size() == 0)
		{
			throw new Exception("Stack is empty");
		}
		
		return aidar.remove(aidar.size() - 1);
	}

	@Override
	public int getSize() {
		return aidar.size();
	}

	@Override
	public void clear() {
		aidar.clear();
		
	}
	
	public String toString()
	{
		return aidar.toString();
	}
	
	

}
