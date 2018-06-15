package csci152.impl;
import csci152.adt.*;

public class BSTSet<T extends Comparable> implements Set<T> {
    
    private TreeNode<T> root;
    private int size;
    
    public BSTSet(){
        root=null;
        size=0;
    }

    @Override
    public void add(T value) {
        if(size == 0)
         {
             root = new TreeNode(value);
             size++;
             return;
         }
        addHelper(root, value);
    }
    
    private void addHelper(TreeNode<T> node, T value)
    {
        
        if(contains(value)){
            return;
        }
         
        if (value.compareTo(node.getValue())<0 && node.getLeft() == null){
            TreeNode<T> tauka = new TreeNode(value);
            node.setLeft(tauka);
            size++;
        }
        else if (value.compareTo(node.getValue())>0 && node.getRight() == null)
        {
            TreeNode<T> tauka = new TreeNode(value);
            node.setRight(tauka);
            size++;
        }
        else if(value.compareTo(node.getValue())<0){
            node=node.getLeft(); 
            addHelper(node, value);
        }
        else{
            node=node.getRight();
            addHelper(node, value);
        } 
    }

    @Override
    public boolean contains(T value) {
        return containsHelper(root, value);     
    }
    
    private boolean containsHelper (TreeNode<T> node, T value)
    {
        if (node == null)
        {
            return false;
        }
        
        if(value.compareTo(node.getValue())==0){
            return true;
        }
        else if(value.compareTo(node.getValue())<0){
            node=node.getLeft(); 
            return containsHelper(node, value);
        }
        else{
            node=node.getRight();
            return containsHelper(node, value);
        }  
    }

    @Override
    public boolean remove(T value) {
        
        if(!contains(value)){
            return false;
        }
        else{
            
            TreeNode<T> node = root;
            TreeNode<T> parent = root;
            boolean nodeIsRight = false;
            
            while (true)
            {
                if(value.compareTo(node.getValue()) == 0){
                    
                    
//                    if (value.compareTo(pare.getRight().getValue()) == 0)
//                    {
//                        nodeIsRight = true;
//                        node = node.getRight();
//                    }
//                    else
//                    {
//                         nodeIsRight = false;
//                         node = node.getLeft();
//                    }
                    
                    
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
                        TreeNode<T> smallestInRightParent = node;
                        T substVal = node.getValue();
                        
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
                else if(value.compareTo(node.getValue())<0){
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
            
            
            //TreeNode<T> aidar = new TreeNode(value);
            size--;
            return true;
        }     
    }

    @Override
    public T removeAny() throws Exception {
    	
    	if (size == 0)
    	{
    		throw new Exception("Size is zero");
    	}
    	
        T toReturn = root.getValue();
        remove(toReturn);
        return toReturn;
    }

    @Override
    public int getSize() {
        return size;
    }

    @Override
    public void clear() {
        root=null;
        size=0;
    }
    
    public String toString(){
        return toStringHelper(root);
    }
    
    private String toStringHelper(TreeNode<T> node){
        if(node==null){
            return "";
        }
        return toStringHelper(node.getLeft()) + " " +node.getValue() + " "+toStringHelper(node.getRight());
    }
}
