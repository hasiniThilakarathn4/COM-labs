/*********************************************
 * CO322: Data structures and algorithms
 * Implementation of the hashTable
 *********************************************/

import java.util.LinkedList;
import java.io.*;
import java.util.Iterator;

 class HashTableImp implements HashTable {

    /* Put your code here */
	LinkedList<String>[] node_data;
	int nbuckets;

    public HashTableImp(int buckets) {
	// create a open hash table with given number of buckets 
		nbuckets = buckets;
	
		node_data = new LinkedList[nbuckets];
		
		for(int i=0;i<nbuckets;i++){
			node_data[i] = new LinkedList();
		}
	
    }
	
	//inserting strings to hash table using hash function1
	public void insert1(String s){
		 s= rearranged(s);
		if(s.length()==0)
			return ;
		node_data[hash_function1(s)].push(s);
	}
	
	//inserting strings to hash table using hash function2
	public void insert2(String s){
		 s= rearranged(s);
		if(s.length()==0)
			return ;
		node_data[hash_function2(s)].push(s);
	}
	
	
	
	//linear search for hash function1 
	public int search1(String s){
		 s= rearranged(s);
		Iterator<String> iterator = node_data[hash_function1(s)].iterator();
		int pos=0;
		while(iterator.hasNext())if(iterator.next().equals(s))
			pos++;
        return pos;
	}
	
	//linear search for hash function2
		public int search2(String s){
		 s= rearranged(s);
		Iterator<String> iterator = node_data[hash_function2(s)].iterator();
		int pos=0;
		while(iterator.hasNext())if(iterator.next().equals(s))
			pos++;
        return pos;
	}
	

	
	
	//removing all numbers and symbols and returning the strings with only aplphabetical letters
	public static String rearranged(String s){
        return s.replaceAll("[^a-zA-Z]", "");
    }
	
	//hash function_1
	 public int hash_function1(String s){
        s = rearranged(s);
        int key=0;
        
		key = modVal(s.length());
		
        return key;
    }
	
	
	
	//hash function_2
	public int hash_function2(String s){
		
	     int total=0;
		 int key=0;
            char[] charact = s.toCharArray();
            int i=0;
            for(;i<charact.length;i++){
                total += charact[i];
            }
            key = modVal(total/i);
	
      
        return key;
    
	}
	
	
	//finding (i)modulus(number of buckets)
	  public int modVal(int i){
        return i%nbuckets;
    }
	
//calculating the mean of the entries in the buckets
	 public void mean(){
		 int sum=0;
        for(int i=0;i<nbuckets;i++){
			sum = sum + node_data[i].size();
		}		  
         System.out.println(sum/(1.0f*nbuckets));
    }
	

	//calculating size of a particular bucket
	public int bucketSizes(int i){		
		int	arr = (node_data[i].size());
		return arr;
	}
	
	
	
	//finding the maximum number of entries 
    public void max(){
        int maxNoOfEntries=Integer.MIN_VALUE;
        for(int i=0;i<nbuckets;i++){
			maxNoOfEntries=Math.max(maxNoOfEntries,node_data[i].size());
		}
        System.out.println(maxNoOfEntries);
    }
	
	//finding the maximum number of entries  	
	public void min(){
        int minNoOfEntries=Integer.MAX_VALUE;
        for(int i=0;i<nbuckets;i++){
			minNoOfEntries=Math.min(minNoOfEntries,node_data[i].size());
		}
        System.out.println(minNoOfEntries);
    }

	 
	 //standard deviation
    public void standardDev(){
		float vr = 0;
        float mean;
		 int sum=0;
		 
        for(int i=0;i<nbuckets;i++){
			sum = sum + node_data[i].size();
		}		  
		
		mean = sum/(1.0f*nbuckets);
		
        for(int i=0;i<nbuckets;i++)
			vr +=Math.pow(node_data[i].size()-mean,2);
        vr = vr/(1.0f*nbuckets);
		
        System.out.println((float)Math.pow(vr,0.5f));
    }



}// end HashTableImp 
