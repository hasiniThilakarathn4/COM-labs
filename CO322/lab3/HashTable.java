/********************************************
 * CO322: Data structures and algorithms
 * Interface for the HashTable
 ********************************************
 */
interface HashTable {
    /* insert the given key to a open hash tabled.
     * With each key you have a count of how many times it 
     * was inserted 
     */
    public void insert1(String key);
	
	public void insert2(String key);
	
    /* given the key return the number of times it was inserted 
     * to the table 
     */
    public int search1(String key);
	
	public int search2(String key);
	

}

    
