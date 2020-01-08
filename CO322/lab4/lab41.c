#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>

#define SIZE 57	//for string characters in nodes


//trieNode structure
typedef struct trieNode
{
    struct trieNode *children[SIZE];
    char charIn;
    bool isEndOfWord;
}trieNode;

//create new trie Node
trieNode* createTrieNode()
{
    trieNode* newtrieNode = (trieNode*)malloc(sizeof(trieNode));
    
    newtrieNode->isEndOfWord = false;
    int i;
    for (i = 0; i<SIZE; i++)
    {
    	newtrieNode->children[i] = NULL;
    }
    return newtrieNode;
}

int noOfNodes=0;

//insert a new Node to the trie
void insertNode(trieNode* root,char* string, int stringSize)
{
    int i,index, loopSize = stringSize -1;
    
	noOfNodes++;
    for(i=0;i<loopSize;i++)
    {
	//get an index number for characters
	if (string[i] >= 'A' && string[i] <= 'Z')
  		index = string[i] - 'A';
	else if (string[i] >= 'a' && string[i] <= 'z')
  		index = string[i] - 'a';
	else
		index = i + 26;//non alphabetical characters

         
        if(!(root->children[index]))
        {
            root->children[index] = createTrieNode();
            root->children[index]->charIn = string[i];

        }
        root = root->children[index];
    }
    root->isEndOfWord = true;
    
}


//search nodes
trieNode* searchNodes(trieNode* root,char* string)
{
    int i,index;
    trieNode* currNode = root;
    for(i=0;i<strlen(string);i++)
    {
	//index number for characters
        if (string[i] >= 'A' && string[i] <= 'Z')
  		index = string[i] - 'A';
	else if (string[i] >= 'a' && string[i] <= 'z')
  		index = string[i] - 'a';
	else
		index = i +26;
	

        currNode =currNode->children[index];
    }
    return currNode;
}


void printSuggestions(trieNode* pausedNode,char string[],int stringSize)
{
    int i,index;
    if(pausedNode->isEndOfWord)
    {
        for(i=0;i<stringSize;i++)
        {
            printf("%c",string[i]);
        }
        printf("\n");
    }
    for(i=0;i<SIZE;i++)
    {
        if(pausedNode->children[i]!=NULL)
        {
            string[stringSize] = pausedNode->children[i]->charIn;
            printSuggestions(pausedNode->children[i],string, stringSize+1);
        }
    }
}


// Returns 0 if current node has a child 
// If all children are NULL, return 1. 
bool isLastNode(trieNode* root) 
{ 
    for (int i = 0; i < SIZE; i++) 
        if (root->children[i]) 
            return 0; 
    return 1; 
} 



// print suggestions for given query prefix. 
int print_Suggestions(trieNode* root, trieNode* pausedNode, char string[]) 
{ 
	int stringSize = strlen(string);
    struct trieNode* currNode = root; 
  
    // Check if prefix is present and find the 
    // the node (of last level) with last character 
    // of given string. 
    int nodelevel; 
   
    for (nodelevel = 0; nodelevel < stringSize; nodelevel++) 
    { 
	int index;

	if (string[nodelevel] >= 'A' && string[nodelevel] <= 'Z')
  		index = string[nodelevel] - 'A';
	else if (string[nodelevel] >= 'a' && string[nodelevel] <= 'z')
  		index = string[nodelevel] - 'a';
	else
		index = nodelevel + 26;
         
  
        // no string in the Trie has this prefix 
        if (!currNode->children[index]) 
            return 0; 
  
        currNode = currNode->children[index]; 
    } 
  
    /// If prefix is present as a word. 
    bool hasWord = (currNode->isEndOfWord == true); 
  
    // If prefix is last node of tree (has no 
    // children) 
    bool isLast = isLastNode(currNode); 
  
    // If prefix is present as a word, but 
    // there is no subtree below the last 
    // matching node. 
    if (hasWord && isLast)   
        return -1; 
 
  
        printSuggestions(pausedNode, string, stringSize); 
	return 1;
        
} 




int main()
{
    char input[100];
    char string[10000];
    

    FILE *file = fopen("wordlist70000.txt","r");
    if (file == 0)
    {
        printf("No existing file\n");
	return 0;
    }

    trieNode* root = createTrieNode();
    
    clock_t beginInsert = clock(); //get the begining time of the insersion

    //developing the trie node by inserting nodes with strings read from the text file
    while(!(feof(file)))
    {
        fgets(string,10000,file);
        insertNode(root,string, strlen(string));
        
    }
    clock_t endInsert = clock(); //get the ending time of the insersion
    
    fclose(file);


        printf("Enter the word: ");

        scanf("%s",input);
        
        trieNode* pausedNode = searchNodes(root,input); //searching for the input prefix or word
      
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
    	printf("\nTime taken to store the dictionary: %f s\n",(double)(endInsert-beginInsert)/CLOCKS_PER_SEC);

        timeForPrinting = (double)(endPrinting-beginPrinting)/CLOCKS_PER_SEC;
        printf("\nTime taken for printing a list of suggestions for a given prefix: %f s\n",timeForPrinting);


    return 0;
}