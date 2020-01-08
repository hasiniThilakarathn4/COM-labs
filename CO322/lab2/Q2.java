class Q2 {
    static int [][] cost = {{0, 3, 12, 23, 41}, // cost from 0 
			    {0, 0,  2,  4, 34}, // cost from 1 
			    {0, 0,  0,  12, 3}, // cost from 2 
			    {0, 0,  0,  0, 12}, // cost from 3 
			    {0, 0,  0,  0,  0}  // cost from 4 
    };

    static int iMax = 5;
    static int jMax = 5;

    // Just for testing, min cost from 0 to 4 should be 8.
    static int answer = 8; 

    public static int minCost(int i, int j) {
	  
	int min_cost ; 
	int cost_1 ;
	
	 min_cost = cost[i][j]; //initializing minimum cost from i to j as the cost stored in the array;directly from i to j	
	 
	
	//when destination and source dtations are the same and when destination is the next station from source
	if(i==j || j==i+1){   
		return min_cost;
	}
	
	//for calculating cost in all routes from i to j
	for(int k=i+1;k<j;k++){
		
		 cost_1 = minCost(i,k) + minCost(k,j);  //recursive calculations
		 
		if(cost_1<min_cost)  //checking if the cost calculated for each route is less than the previosly calculated cost
			min_cost = cost_1;	 //upadating the minimum cost whle going through every path	
		}
	
		return min_cost; //returning minimum cost from i to j
	}
    

    public static void main(String [] args) {
	int r = minCost(0,4); 
	if(r == answer)
	    System.out.println("Your implementation might be correct");
	else
	    System.out.println("Too bad. Try again (" + r + ")");
    }
}