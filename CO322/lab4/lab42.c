#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>

#define SIZE 52  //for storing characters in nodes

typedef struct linkedStr
{
	char charIn;
	struct linkedStr *next;
}linkedStr;


typedef struct trieNode
{
    struct trieNode* children[SIZE];
    linkedStr* linkedStr;
    bool isEndOfWord;
}trieNode;

//create new node for trie
trieNode* createTrieNode()
{
    trieNode* node = (trieNode*)malloc(sizeof(trieNode));

    
    node->isEndOfWord = false;
    node->linkedStr = NULL;

    int i;
    for (i=0;i<SIZE;i++)
    {
    	node->children[i] = NULL;
    }
    return node;
}


//create linked structure for strings 
linkedStr* createStr(char newCharIn)
{
    linkedStr* string = (linkedStr*) malloc(sizeof(linkedStr));

    string -> next = NULL;
    string -> charIn = newCharIn;
    
    return string;
}


trieNode* searchNodes(trieNode* root,char* string, int stringSize)
{
    int currIndex=0,index;
    trieNode* currNode = root;
    linkedStr* currCharacter = currNode->linkedStr;

    while(currIndex<stringSize)
    {
    	if (string[currIndex] >= 'A' && string[currIndex] <= 'Z')
  		index = string[currIndex] - 'A';
	else if (string[currIndex] >= 'a' && string[currIndex] <= 'z')
  		index = string[currIndex] - 'a';
	else
		index = 26+currIndex;


    	if(currCharacter == NULL)
        {
            currNode = currNode->children[index];
    		currCharacter = currNode->linkedStr->next;
    	}
        else
        {
    		currCharacter = currCharacter->next;
    	}
        currIndex++;
    }

    while(currCharacter != NULL)
    {
    	string[stringSize] = currCharacter->charIn;
    	currCharacter = currCharacter->next;
    	stringSize++;
    }
    string[stringSize] = '\0';
    return currNode;
}



//add the strings in a linked structure 
linkedStr* addStr(char* string,int firstIndex)
{
    int stringSize = strlen(string)-1 , i, begin = firstIndex + 1;

    linkedStr* currStr = createStr(string[firstIndex]);
    linkedStr* newStr = NULL;
    linkedStr* stringOut = currStr;

    for(i=begin;i<stringSize;i++)
    {
        newStr = createStr(string[i]);
        currStr->next = newStr;
        currStr = currStr->next;
    }
    currStr = NULL;
    return stringOut;
}

trieNode* breakStr(trieNode* currNode, trieNode* preNode, linkedStr* pausedString)
{
    
    linkedStr* newStr = pausedString->next;
    trieNode* newTrieNode = createTrieNode();
    pausedString->next = NULL;
    int index,i=0 ;
	//converting the character to index 
	if ((newStr->charIn) >= 'A' && (newStr->charIn) <= 'Z')
  		index = (newStr->charIn) - 'A';
	else if ((newStr->charIn) >= 'a' && (newStr->charIn) <= 'z')
  		index = (newStr->charIn) - 'a';
	else
		index = 26+i;
	

    newTrieNode->linkedStr = currNode->linkedStr;
    currNode->linkedStr = newStr;
    newTrieNode->children[index] = currNode;

	if ((newTrieNode->linkedStr->charIn) >= 'A' && (newTrieNode->linkedStr->charIn) <= 'Z')
  		index = (newTrieNode->linkedStr->charIn) - 'A';
	else if ((newTrieNode->linkedStr->charIn) >= 'a' && (newTrieNode->linkedStr->charIn) <= 'z')
  		index = (newTrieNode->linkedStr->charIn) - 'a';
	else
		index = 26+i; 

    preNode->children[index] = newTrieNode;

    return newTrieNode;
}

//defining the nodes and linking characters
void insertNode1(trieNode* node,trieNode* currNode, char* string, int currIndex, int index){
	node = createTrieNode();
  
	node->isEndOfWord = true;
    	node->linkedStr = addStr(string,currIndex);
                	
    	currNode->children[index] = node;


}

int noOfNodes=0;

//inserting nodes in the trie structure
void insertNode(trieNode* root,char* string, int stringSize)
{
    
    int currIndex=0,index;


    trieNode* node = NULL;
    trieNode* currNode = root, *preNode = NULL;
    

    linkedStr* currCharacter, *preCharacter = NULL;
    currCharacter = currNode->linkedStr;

    while(currIndex<stringSize-1)
    {
	//converting the character to index 
    	if (string[currIndex] >= 'A' && string[currIndex] <= 'Z')
  		index = string[currIndex] - 'A';
	else if (string[currIndex] >= 'a' && string[currIndex] <= 'z')
  		index = string[currIndex] - 'a';
	else
		index = currIndex; 

    	if(currCharacter != NULL)
        {

	if (currCharacter->charIn == string[currIndex])
    		{
			preCharacter = currCharacter;
    			currCharacter = currCharacter->next;

    		}
            else
            {
			currNode = breakStr(currNode, preNode, preCharacter); 			
			insertNode1(node, currNode, string, currIndex, index); 
    			break;
                
    	   }


    	}
        else
        { 
    		if(currNode->children[index] == NULL)
    		{
			insertNode1(node, currNode, string, currIndex, index);
			noOfNodes++;
    			
    			break;
    		}
    		else
            {
                preNode = currNode;
                currNode = currNode->children[index];
                preCharacter = currNode->linkedStr;
    			currCharacter = currNode->linkedStr->next;
    		}

    	}
    	currIndex++;
    }
}



//printing the suggested strings for a given input prefix
void printSuggestions(trieNode* pausedNode,char string[],int stringSize)
{
    trieNode* currNode = pausedNode;
    int currIndex,newStringSize;

//if the checking node is the end of the word print the word
    if(currNode->isEndOfWord)
    {
        for (currIndex=0;currIndex<stringSize;currIndex++)
        {
            printf("%c",string[currIndex]);
        }
        printf("\n");
    }

    for (currIndex=0;currIndex<SIZE;currIndex++)
    {
        if(currNode->children[currIndex]!=NULL)
        {
		newStringSize = stringSize;

		linkedStr* currCharacter = currNode->children[currIndex]->linkedStr;

   		 while (currCharacter != NULL)
    		{		
       			 string[newStringSize] = currCharacter->charIn;
       			 newStringSize++;
      			  currCharacter = currCharacter->next;
   		 }
    		string[newStringSize] = '\0';
		newStringSize = newStringSize - 1; //new size of the string to fit into the linked structure of characters

		//recurring until the end of a word is met to print a suggesting word
            printSuggestions(currNode->children[currIndex],string,newStringSize+1);
        }
    }
}



// check current node for a child or NULL 
bool isLastNode(trieNode* root) 
{ 
	int i;

    for (i = 0; i < SIZE; i++) 
        if (root->children[i]) 
            return 0; 
    return 1; 
} 



// print suggestions for theinput prefix or
//return -1 if there are no other words from the input prefix
//return 0 if there are no words for the input prefix at all  
int print_Suggestions(trieNode* root, trieNode* pausedNode, char string[]) 
{ 
	int stringSize = strlen(string);
   	struct trieNode* currNode = root; 
  
    // Check if prefix is present and find the 
    // the node (of last level) with last character 
    // of given string. 
    int nodeLevel; 
   
    for (nodeLevel = 0; nodeLevel < stringSize; nodeLevel++) 
    { 
	int index;

	if (string[nodeLevel] >= 'A' && string[nodeLevel] <= 'Z')
  		index = string[nodeLevel] - 'A';
	else if (string[nodeLevel] >= 'a' && string[nodeLevel] <= 'z')
  		index = string[nodeLevel] - 'a';
	else
		index = nodeLevel; 

         
  
        // no string found for this prefix in the trie 
        if (!currNode->children[nodeLevel]) 
            return 0; 
  
        currNode = currNode->children[nodeLevel]; 
    } 
  
    // prefix is present as a whole string. 
    bool isString = (currNode->isEndOfWord == true); 
  
    // prefix is the last node of the trie 
    bool isLast = isLastNode(currNode); 
  
    // prefix is present as a string and there is no other strings starting 
    //with this prefix
    if (isString && isLast)   
        return -1; 
 
  	//printing the suggested strings for the given input prefix
        printSuggestions(pausedNode, string, stringSize); 
	return 1;
        
} 



int main()
{
     char input[100];
    char string[100];
    
    //read the text file
    FILE *file = fopen("wordlist70000.txt","r");
    if (file == NULL)
    {
        printf("No existing file\n");
	return 0;
    }

	//creating root node
    trieNode* root = createTrieNode();
    
    clock_t beginInsert = clock(); //get the begining time of the insersion
    

     //developing the trie node by inserting nodes with strings read from the text file
    while(!(feof(file)))
    {
        fgets(string,100,file);
        insertNode(root,string,strlen(string));
    }
    clock_t endInsert = clock(); //get the ending time of the insersion
    
    fclose(file);


        printf("Enter the word: ");

        scanf("%s",input);
        
        trieNode* pausedNode = searchNodes(root,input,strlen(input));
      
        printf("\n");

        clock_t beginPrinting = clock(); //get the begining time of the elapsing process 

        int prefixFound;
	prefixFound = print_Suggestions(root,pausedNode,input);

	if (prefixFound == -1)
        printf("No other words with this prefix is found\n"); 
  
     	else if (prefixFound == 0)
        printf("No words with this prefix is found\n"); 


        clock_t endPrinting = clock();	//get the ending time of the elapsing process 

	
	double timeForInsersion,timeForPrinting;
	long unsigned int memSpace;

	memSpace = sizeof(*(root))*noOfNodes;
        printf("\nMemory space usage: %ld Bytes\n",memSpace);


	timeForInsersion = (double)(endInsert-beginInsert)/CLOCKS_PER_SEC;
    	printf("\nTime taken to store the dictionary: %f s\n",timeForInsersion);

        timeForPrinting = (double)(endPrinting-beginPrinting)/CLOCKS_PER_SEC;
        printf("\nTime taken for printing a list of suggestions for a given prefix: %f s\n",timeForPrinting);


	
        return 0;
}