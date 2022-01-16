#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int wordcount=0;

typedef struct Dictionary
{
    char word[100];
    struct Dictionary *left, *right;
}Dict; 

Dict *root=NULL;

Dict* InsertWords(Dict *root, char *word)
{
    Dict *newWord=(Dict *)malloc(sizeof(Dict));
    strcpy(newWord->word, word);
    newWord->left = NULL;
    newWord->right = NULL;
        
    if (root == NULL)
    {
        root = newWord;
    }
    else if(strcmp(root->word, word) > 0)
    {
    	root->left = InsertWords(root->left, word);
    }
    else
    {
	root->right = InsertWords(root->right, word);
    }
    return root;
}

void DisplayDictionary(Dict *root)
{
    if (root)
    {
        DisplayDictionary(root->left);
        printf("\n%s", root->word);
        DisplayDictionary(root->right);
    }
}

void SuggestWords(Dict *root, char *word) 
{
	int i,misMatch=0;
	
	//To reach to node with the matching intial character
	while(root != NULL)
    	{
    		if (root->word[0] == word[0])
           	 	break;
        	else if (root->word[0] < word[0])
            		root=root->right;
       		else    
            		root=root->left;
    	}
		 
    	if(root != NULL)
    	{
        	if (strlen(root->word) == strlen(word) && root->word[0]==word[0])
        	{
                	for(i=0;word[i]!='\0';i++)
                	{
                    		if(word[i]!='_' && word[i]!=root->word[i])  
                    		{
                    			misMatch=1;
                    			break;
  				}
                	}
                	if(misMatch==0)   //Word does not Match
			{
                		wordcount++;
               			if(wordcount==1)
               			{
               				printf("\nSuggested Words :- %s\t",root->word);
			   	}
			   	if(wordcount>1)
			   	{
			   		printf("%s\t",root->word);
			   	}
			}
		}
	    	SuggestWords(root->left,word);  //Search In Left Child
        	SuggestWords(root->right,word); //Search In Right Child
   	}
}

int main()
{
	int i;
	char crossword[20]="";
	
	char dictionary[][15]={"start","smooth","slow","about","boxing","adcdet","alout","accet","abbbt","tantrums","india",
	"jafer","drama","queen","yacht","zebra","accent","accept","expect","except","average","random","forest",
	"crossword","joker","ravi"};
	
	for(i=0;i<26;i++)
	{
		root=InsertWords(root,dictionary[i]);
	}
    	printf("\nWords Stored in Dictionary are:\n ");
    	DisplayDictionary(root);
    
    	while(1)
    	{
    		printf("\n\n============================================================================================");
    		printf("\nEnter the Word(In Format: 'k_k__k' i.e k for known and _ for unknown)\n(Enter q for Quitting!!)");
    		printf("\n\nEnter the Crossword: ");
        	scanf("%s",crossword);
        
       		if(crossword[0]=='_')
        	{
        		printf("\nEnter String having initial Character!!!");
        		continue;
		}
        
		if(strcmp(crossword,"q") == 0)
        		break;
        
		wordcount=0;
       		SuggestWords(root, crossword);
      		if(wordcount==0)
        	{
        		printf("\nNo Suggestions!!!");
		}
   	}
   	return 0;
}
