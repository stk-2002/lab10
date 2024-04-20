#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int endWord; //0 not end, 1 is end
    char *children[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    for(int i=0; i<strlen(word); i++)
    {
        int charIndex = word[i] - 'a';
        //if the current character is not present
        if(pTrie->children[charIndex] == NULL)
        {
            //set the character as a new trie node
            pTrie->children[charIndex] = createTrie();
        }
        //advance to the next node
        pTrie = pTrie->children[charIndex];
    }

    //done inserting, set end word flag
    pTrie->endWord = 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    //not sure
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for(int i=0; i<26; i++)
    {
        if(pTrie->children[i] != NULL)
        {
            //recursively free all of the current node's children
            deallocateTrie(pTrie->(children[i]));
        }
    }

    //free the current node
    free(pTrie);
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* myTrie = malloc(sizeof(struct Trie));
    //the root is not the end of a word
    myTrie->endWord = 0;

    //set each child pointer to null
    for (int i=0; i<25; i++)
    {
        myTrie->children[i] = NULL;
    }

    return myTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    //open file
    FILE *fp = fopen(filename, "r");
    //make sure file exists
    if(fp == NULL)
    {
        printf("error opening file\n");
        return -1;
    }
    
    //read the number of words in the input file
    int i, numWords;
    fscanf(fp, "%d", &numWords);

    //read each word and insert it
    for (i=0; i<numWords; i++)
    {
        char word[100];
        fscanf(fp, "%s", &word);
        //allocate memory to the current pInWords element
        pInWords[i] = (char*)malloc(strlen(word)*sizeof(char));
        //copy our word to pInWords
        strcpy(pInWords[i], word);
    }

    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}