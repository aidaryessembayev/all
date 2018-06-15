package csci152.impl;

import csci152.adt.HashTableSet;

public class BSTSetHashTableSet<T extends Comparable> implements HashTableSet<T> {

	BSTSet bucket[];
	int size;
	
	public BSTSetHashTableSet (int k)
	{

		bucket = new BSTSet[k];
		size = 0;
		
		for (int i = 0; i < k; i++)
		{
			bucket[i] = null;
		}
	}
	
	@Override
	public void add(T value) {
		
		int index = Math.abs(value.hashCode()) % bucket.length;
		
		if(bucket[index] == null)
        {
			bucket[index] = new BSTSet();
        }

		 bucket[index].add(value);

       
   }

	@Override
	public boolean contains(T value) {
		
		int index = Math.abs(value.hashCode()) % bucket.length;
		
		if (bucket[index] == null)
		{
			return false;
		}
		
		
        return bucket[index].contains(value);
    }    

	@Override
 public boolean remove(T value) {
        
		int index = Math.abs(value.hashCode()) % bucket.length;
		
		if (bucket[index] == null)
		{
			return false;
		}
		
		return bucket[index].remove(value);
    }

	@Override
	public T removeAny() throws Exception {
		
		int i = 0;
		
		if (size == 0)
		{
			throw new Exception("Set is empty");
		}
		
		while (bucket[i] == null)
		{
			i++;
		}
		
		return (T)bucket[i].removeAny();
		
		

	}

	@Override
	public int getSize() {
		
		return size;
	}

	@Override
	public void clear() {
		bucket = new BSTSet[bucket.length];
		size = 0;
		
		for (int i = 0; i < bucket.length; i++)
			
			
		{
			bucket = null;
		}
		
	}

	@Override
	public int getNumberOfBuckets() {
		// TODO Auto-generated method stub
		return bucket.length;
	}

	@Override
	public int getBucketSize(int index) throws Exception {
		
		return bucket[index].getSize();
	}

	@Override
	public double getLoadFactor() {
			
		return size / bucket.length;
	}

	@Override
	public double getBucketSizeStandardDev() {
		
		int max = 0;
		
		for (int i = 0; i < getNumberOfBuckets(); i++)
		{
			try
			{
				if (getBucketSize(i) > max)
				{
					max = getBucketSize(i);
				}

			}
			catch (Exception e)
			{
				System.out.println(e.getMessage());
			}
		}
		
		int min = max;
		
		for (int i = 0; i < getNumberOfBuckets(); i++)
		{
			try
			{
				if (getBucketSize(i) < max)
				{
					min = getBucketSize(i);
				}

			}
			catch (Exception e)
			{
				System.out.println(e.getMessage());
			}
		}
		
		return max - min;
	}

	@Override
	public String bucketsToString() {
		// TODO Auto-generated method stub
		return null;
	}
	
	

}
