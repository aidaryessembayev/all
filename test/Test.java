package csci152.test;

import csci152.adt.Stack;
import csci152.impl.ArrayListStack;

public class Test {

	public static void main(String[] args) {
		
		Stack<Integer> exp1 = new ArrayListStack<Integer>();
	    
		try
		{
		    exp1.pop();
		}
		catch(Exception e)
		{
		    System.out.println(e.getMessage());
		}
		
		for (int i = 0; i < 12; i++)
		{
		    exp1.push(i);
		}
		
		System.out.println(exp1);
		System.out.println("Size of stack " +  exp1.getSize());
		
		for (int i = 0; i < 3; i++)
		{
		    try {
				exp1.pop();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				System.out.println(e.getMessage());
			}
		}
		
		System.out.println(exp1);
		System.out.println("Size of stack " +  exp1.getSize());
		
		exp1.clear();
		System.out.println(exp1);
		System.out.println("Size of stack " +  exp1.getSize());
		
		for (int i = 0; i < 22; i++)
		{
		    exp1.push(i);
		}
		
		System.out.println(exp1);
		System.out.println("Size of stack " +  exp1.getSize());

	}

}
