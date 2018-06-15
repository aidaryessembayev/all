package csci152.impl;

import csci152.adt.KeyValuePair;
import csci152.adt.Map;

public class BSTMap<K extends Comparable, V> implements Map<K, V> {

	private TreeNode<KeyValuePair<K,V>> root;
	private int size;
	
	public BSTMap() {
		root = null;
		size = 0;
	}
	
	@Override
	public void define(K key, V value)
	{
		if(size == 0)
	    {
	        root = new TreeNode(new KeyValuePair(key, value));
	        size++;
	        return;
	    }
		addHelper(root, key, value);
}

private void addHelper(TreeNode<KeyValuePair<K,V>> node, K key, V value)
{
   
   
	if (key.compareTo(node.getValue().getKey()) == 0)
	{
		node.getValue().setValue(value);
	}
	else if (key.compareTo(node.getValue().getKey())<0 && node.getLeft() == null){
	   TreeNode<KeyValuePair<K,V>> tauka = new TreeNode(new KeyValuePair(key, value));
       node.setLeft(tauka);
       size++;
   }
   else if (key.compareTo(node.getValue().getKey())>0 && node.getRight() == null)
   {
	   TreeNode<KeyValuePair<K,V>> tauka = new TreeNode(new KeyValuePair(key, value));
       node.setRight(tauka);
       size++;
   }
   else if(key.compareTo(node.getValue().getKey())<0){
       node=node.getLeft(); 
       addHelper(node, key, value);
   }
   else{
       node=node.getRight();
       addHelper(node, key, value);
   } 
}

	@Override
	public V getValue(K key) {
        return containsHelper(root, key);     
    }
    
    private V containsHelper (TreeNode<KeyValuePair<K,V>> node, K key)
    {
        if (node == null)
        {
            return null;
        }
        
        if(key.compareTo(node.getValue().getKey())==0){
        	V val = node.getValue().getValue();
            return val;
        }
        else if(key.compareTo(node.getValue().getKey())<0){
            node=node.getLeft(); 
            return containsHelper(node, key);
        }
        else{
            node=node.getRight();
            return containsHelper(node, key);
        }  
    }

	@Override

	
	public V remove(K key) {
	        
	        
	            
	        	TreeNode<KeyValuePair<K,V>> node = root;
	        	TreeNode<KeyValuePair<K,V>> parent = root;
	            boolean nodeIsRight = false;
	            V val = null;
	            
	            while (true)
	            {
	            	
	            	if (node == null)
	            	{
	            		return val;
	            	}
	            
	            	
	                if(key.compareTo(node.getValue().getKey()) == 0){
	                    
	                    val = node.getValue().getValue();
	                    
	                    //has no children
	                    if (node.getRight() == null && node.getLeft() == null)
	                    {
	                        if(nodeIsRight)
	                        {
	                            parent.setRight(null);
	                            break;
	                        }
	                        else
	                        {
	                            parent.setLeft(null);
	                            break;
	                        }
	                    }
	                    
	                    //has one child
	                    else if ((node.getRight() != null && node.getLeft() == null) || (node.getRight() == null && node.getLeft() != null))
	                    {
	                    	if (parent == node)
	                    	{
	                    		if (node.getRight() != null)
	                            {
	                                root = node.getRight();
	                                break;
	                            }
	                            else
	                            {
	                                root = node.getLeft();
	                                break;
	                            }
	                    	}
	                    	else if(nodeIsRight)
	                        {
	                            if (node.getRight() != null)
	                            {
	                                parent.setRight(parent.getRight().getRight());
	                                break;
	                            }
	                            else
	                            {
	                                parent.setRight(parent.getRight().getLeft());
	                                break;
	                            }
	                        }
	                        else
	                        {
	                            if (node.getRight() != null)
	                            {
	                                parent.setLeft(parent.getLeft().getRight());
	                                break;
	                            }
	                            else
	                            {
	                                parent.setLeft(parent.getLeft().getLeft());
	                                break;
	                            }
	                        }
	                    }
	                    
	                    //has two children
	                    else
	                    {
	                    	TreeNode<KeyValuePair<K,V>> smallestInRightParent = node;
	                        KeyValuePair<K,V> substVal = node.getValue();
	                        
	                        if (smallestInRightParent.getRight().getLeft() != null)
	                        {
	                        	smallestInRightParent = smallestInRightParent.getRight();
	                        	
	                        	while(smallestInRightParent.getLeft().getLeft() != null)
	                        	{
	                        		smallestInRightParent = smallestInRightParent.getLeft();
	                        	}
	                        }
	
	                        
	                        //has no children
	                        if (smallestInRightParent.getLeft().getRight() == null)
	                        {
	                            substVal = smallestInRightParent.getLeft().getValue();
	                            smallestInRightParent.setLeft(null);
	                        }
	
	                        //has one child
	                        else
	                        {
	                            substVal = smallestInRightParent.getLeft().getValue();
	                            smallestInRightParent.setLeft(smallestInRightParent.getLeft().getRight());
	                        }
	                        
	                        node.setValue(substVal);
	                        break;
	                    }
	                }
	                else if(key.compareTo(node.getValue().getKey())<0){
	                    parent = node; 
	                    node = node.getLeft();
	                    nodeIsRight = false;
	                     
	               
	                }
	                else{
	                    parent = node;
	                    node=node.getRight();
	                    nodeIsRight = true;
	                    
	                }  
	            }
	            size--;
	            return val;
	        }     
	    

	@Override
	public KeyValuePair<K, V> removeAny() throws Exception {
		
		if (size == 0)
		{
			throw new Exception("Size of map is zero");
		}
		
		KeyValuePair<K, V> toReturn = root.getValue();
		 remove(root.getValue().getKey());
		 return toReturn;
		
	}

	@Override
	public int getSize() {
		return size;
	}

	@Override
	public void clear() {
		root = null;
		size = 0;
	}

    @Override
    public String toString(){
        return toStringHelper(root);
    }
    
    private String toStringHelper(TreeNode<KeyValuePair<K, V>> node){
        if(node==null){
            return "";
        }
        return toStringHelper(node.getLeft()) + " " +node.getValue().toString() + " "+toStringHelper(node.getRight());
    }
}