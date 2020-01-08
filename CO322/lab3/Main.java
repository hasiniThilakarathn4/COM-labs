import java.io.*; 
import java.io.IOException;
import java.nio.file.*;


public class Main{
	
	
	public static void main(String args[]){
		
		        String fileName=args[0];
				File file=new File(fileName);
				int nbuckets = Integer.parseInt(args[1]);
				
		
		//hash tables to use for different hash functions
		HashTableImp hashTable1 = new HashTableImp(nbuckets);
		HashTableImp hashTable2 = new HashTableImp(nbuckets);
		
        try {
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);

            while(br.ready()){
                String[] ar=br.readLine().split(" ");
              
			  //inserting the Strings in the text files into the hash tables
                 for(int i=0;i<ar.length;i++){
					 hashTable1.insert1(ar[i]);
                }
				
				for(int j=0;j<ar.length;j++){
					 hashTable2.insert2(ar[j]);
                }
				
				
            }
		
			
			final Object[][] table = new String[nbuckets+1][];
						
			
			table[0] = new String[] { "Bucket Number", "Hash_function1" ,"Hash_function2"};
			
			for(int i=0;i<nbuckets;i++){
            
            table[i+1] = new String[] {  Integer.toString(i+1),  Integer.toString(hashTable1.bucketSizes(i)) , Integer.toString(hashTable2.bucketSizes(i))};
            
			}
			
			 System.out.println("Bucket sizes:");
			
			 for (final Object[] row : table) {

            System.out.format("%15s%15s%15s\n", row);
			}
			
			
			System.out.println("\n\nwhen hash function1 is used:");
            System.out.println("\n\nstandard Deviation");       
                hashTable1.standardDev();
			System.out.println("\n\nMaximum number entries");
                hashTable1.max();
			System.out.println("\n\nMinimum number entries");
                hashTable1.min();	
				
			System.out.println("\n\nwhen hash function2 is used:");
			System.out.println("\n\nstandard Deviation"); 	
				hashTable2.standardDev();
			System.out.println("\n\nMaximum number entries");
                hashTable2.max();
			System.out.println("\n\nMinimum number entries");
                hashTable2.min();	

			
			
			}

        catch (FileNotFoundException e){
            System.out.println("File not found!");
            return;
        }
        catch (IOException e){
            System.out.println("Error reading file");
            return;
        }
	

	} 
		

}