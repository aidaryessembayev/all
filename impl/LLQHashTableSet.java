package csci152.impl;
import csci152.adt.*;

public class LLQHashTableSet<T> implements HashTableSet<T> {
	
	Queue<T> bucket[];
	int size;
	
	public LLQHashTableSet(int k)
	{
		bucket = new LinkedListQueue[k];
		size = 0;
		
		for(int i = 0; i < k; i++)
		{
			bucket[i] = null;
		}
	}
	
	@Override
	public void add(T value) {
		
		if(contains(value))
		{
			return;
		}
		
		int index = Math.abs(value.hashCode()) % bucket.length;
		
		if(bucket[index] == null)
		{
			bucket[index] = new LinkedListQueue();
		}
		
		bucket[index].enqueue(value); 
		size++;
	}

	@Override
	public boolean contains(T value) {
		
		int index = Math.abs(value.hashCode()) % bucket.length;
		
		if(bucket[index] == null)
		{
			return false;
		}
		
		for(int i = 0; i < bucket[index].getSize(); i++)
		{
			try
			{
				T temp = bucket[index].dequeue();
				bucket[index].enqueue(temp);
				if (temp.equals(value))
				{
					return true;
				}
			}
			catch(Exception e)
			{
				System.out.println(e.getMessage());
			}	
		}
		
		return false;
	}

	@Override
	public boolean remove(T value) {
		
		if(contains(value))
		{
			int index = Math.abs(value.hashCode()) % bucket.length;
			
			for(int i = 0; i < bucket[index].getSize(); i++)
			{
				try
				{
					T temp = bucket[index].dequeue();
					if (temp.equals(value))
					{
						size--;
						return true;
					}
					bucket[index].enqueue(temp);
				}
				catch(Exception e)
				{
					System.out.println(e.getMessage());
				}	
			}
		}
		
		return false;
	}

	@Override
	public T removeAny() throws Exception {
		
		if(getSize() == 0)
		{
			throw new Exception("Set is empty");
		}
		
		T toReturn = null;
		
		for (int i = 0; i < bucket.length; i++)
		{
			if(bucket[i].getSize() != 0)
			{
				toReturn = bucket[i].dequeue();
				break;
			}
		}
		
		size--;
		return toReturn;
	}

	@Override
	public int getSize() {
		
		return size;
	}

	@Override
	public void clear() {
		
		bucket = new LinkedListQueue[bucket.length];
		size = 0;
		
		for(int i = 0; i < bucket.length; i++)
		{
			bucket[i] = null;
		}
		
	}
	
	public String toString()
	{
		String result = "";
		
		for (int i = 0; i < bucket.length; i++)
		{
			if (bucket[i] != null)
			{
				result += bucket[i].toString() + "\n";
			}
		}
		
		return result;
	}

	@Override
	public int getNumberOfBuckets() {
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
