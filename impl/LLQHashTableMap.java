package csci152.impl;
import csci152.adt.*;
import csci152.impl.*;

public class LLQHashTableMap<K extends Comparable, V> implements HashTableMap<K, V> {
	
	Queue<KeyValuePair<K, V>>[] bucket;
	int size;
	
	public LLQHashTableMap(int k)
	{
		bucket = new LinkedListQueue[k];
		size = 0;
		
		for(int i = 0; i < k; i++)
		{
			bucket[i] = null;
		}
	}

	@Override
	public void define(K key, V value) {
		
		
		
		if (getValue(key) != null)
		{
			remove(key);
		}
			
			
			
			int index = Math.abs(key.hashCode()) % bucket.length;
			if(bucket[index] == null)
			{
				bucket[index] = new LinkedListQueue();
			}
			
			bucket[index].enqueue(new KeyValuePair<K, V>(key, value)); 
			size++;

			
		

		
		
	}

	@Override
	public V getValue(K key) {
		
		int index = Math.abs(key.hashCode()) % bucket.length;
		
		if (bucket[index] == null)
		{
			return null;
		}
		
		for (int i = 0; i < bucket[index].getSize(); i++)
		{
			KeyValuePair<K, V> temp = null;
			try {
				temp = bucket[index].dequeue();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				System.out.println(e.getMessage());
			}
			bucket[index].enqueue(temp);
			
			if (key.compareTo(temp.getKey()) == 0)
			{
				return temp.getValue();
			}
			
		}
		
		return null;
	}

	@Override
	public V remove(K key) {

		int index = Math.abs(key.hashCode()) % bucket.length;
		
		if (bucket[index] == null)
		{
			return null;
		}
		
		for (int i = 0; i < bucket[index].getSize(); i++)
		{
			KeyValuePair<K, V> temp = null;
			try {
				temp = bucket[index].dequeue();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			
			if (key.compareTo(temp.getKey()) == 0)
			{
				size--;
				return temp.getValue();
			}
			
			bucket[index].enqueue(temp);
			
		}
		
		return null;
	}

	@Override
	public KeyValuePair<K, V> removeAny() throws Exception {
		
		if (size == 0)
		{
			throw new Exception("Map is empty");
		}
		
		int i = 0;
		KeyValuePair<K, V> toReturn = null;
		
		while (i < bucket.length)
		{
			if (bucket[i] == null || bucket[i].getSize() == 0)
			{
				i++;
				continue;
			}
			
			toReturn =  bucket[i].dequeue();
			break;
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
		if (bucket.length == 0 || (index < 0 && index >= bucket.length))
		{
			throw new Exception("Index is out of bounds");
		}
		
		return bucket[index].getSize();
	}

	@Override
	public double getLoadFactor() {
		return size / bucket.length;
	}

	@Override
	public double getBucketSizeStandardDev() {
		
		
		double mean = 0;
		double stDev = 0;
		
		//mean
		for (int i = 0; i < bucket.length; i++)
		{
			if (bucket[i] != null)
			mean += bucket[i].getSize();
		}
		
		mean = mean / bucket.length;
		
		for (int i = 0; i < bucket.length; i++)
		{
			if (bucket[i] != null)
			stDev += Math.pow(bucket[i].getSize() - mean, 2);
		}
		
		stDev = Math.sqrt(stDev / bucket.length);
		
		return stDev;
	}

	@Override
	public String bucketsToString() {
		String toStr = "";
		
		for (int i = 0; i < bucket.length; i++)
		{
			if (bucket[i] != null)
				toStr += "bucket " + (i + 1) + ": " + bucket[i].toString() + "\n";
			else
				toStr += "bucket " + (i + 1) + ": " + "\n";
		}
		
		return toStr;
	}
}
