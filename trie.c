///////////////////////////////////////////////////////////////////////
// Desenvolvedor: Douglas Detoni
// Email: ddetoni@inf.ufpel.edu.br
///////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 6000

typedef struct node{
	char c;
	struct node **vector;
	int final;
} node;

node * makeNode(char w){
	node * root = malloc(sizeof(node));
	root->c = w;
	root->vector = malloc(sizeof(node *) * 4);
	
	root->vector[0] = NULL;
	root->vector[1] = NULL;
	root->vector[2] = NULL;
	root->vector[3] = NULL;
	 
	root->final = 0;
	return root;
}

int insertWord(node *root, char word[], int onset){
	int i, k=onset;
	node *auxNode = root;
	int sizeW = strlen(word);
	while(k != sizeW){
		//printf("%c", word[k]);
		for(i=0; i<4; i++){
			if(auxNode->vector[i] == NULL){
				auxNode->vector[i] = makeNode(word[k]);
				auxNode = auxNode->vector[i];
				
				break;
			}else
			{
				if(auxNode->vector[i]->c == word[k]){
					
					auxNode = auxNode->vector[i];
					break;
				}
				
			}
		}
		k++;
	}
	auxNode->final = 1;
	//printf("\n");
	return 1;
}

int searchWord(node *root, char word[]){
	node *auxNode = root;
	int size = strlen(word);
	int i, k=0;
	
	while(k != size){
		
		for(i=0; i<4; i++){
			if(auxNode->vector[i] != NULL){
				if(auxNode->vector[i]->c == word[k]){
					auxNode = auxNode->vector[i];
					break;
				}
			} else
			{
				return 0;
			}
		}
		k++;
	}
	if(auxNode->final == 1)
		return 1;
	else
		return 0;
}

char * searchSubstring(node *root, char *word, int onset){
	node *auxNode = root;
	int size = strlen(word);
	int i, k=onset, counter=0;
	char *substring = malloc(sizeof(char)*SIZE);

	while(k != size){
		
		for(i=0; i<4; i++){
			if(auxNode->vector[i] != NULL){
				
				if(auxNode->vector[i]->c == word[k]){
					auxNode = auxNode->vector[i];
					substring[counter] = word[k];
					counter++;
					break;
				}
			} else
			{
				substring[counter] = '\n';
				return substring;
			}
		}
		k++;
	}
	
	substring[counter] = '\n';
	return substring;
}

int searchBiggerSubstring(node *root, char *word){
	int i, size, sizeSub=0, contWords;
	char *substring=malloc(sizeof(char)*(SIZE/2)), *auxSubstring = malloc(sizeof(char)*(SIZE/2));
	node *trie;
	
	trie = makeNode(' ');
	
	size = strlen(word);
	
	for(i=0; i< size; i++){
		auxSubstring = searchSubstring(root, word, i);
		if(strlen(auxSubstring) > sizeSub){
			strcpy(substring, auxSubstring);
			sizeSub = strlen(substring);
			contWords=1;
			insertWord(trie, auxSubstring, 0);
		} else if(strlen(auxSubstring) == sizeSub){
			if(!searchWord(trie, auxSubstring)){
				insertWord(trie, auxSubstring, 0);
				strcat(substring, auxSubstring);
				contWords++;
			}
		}
	}
	
	for(i=0; i<strlen(substring); i++){
		if((i/contWords)==sizeSub) 
			printf("\n");
		
		printf("%c", substring[i]);
		
	}
	
	return 1;
	
	
}

int main(){
	node *root;
	char word[SIZE], otherWord[SIZE];
	int i;
	
	scanf("%s", word);
	scanf("%s", otherWord);
	
	root = makeNode(' ');
	
	for(i=0; i < strlen(word); i++)
		insertWord(root, word, i);

	searchBiggerSubstring(root, otherWord);
	
	return 0;
}
