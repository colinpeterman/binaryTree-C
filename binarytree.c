/* Colin Peterman */
#include<stdio.h>
#include<stdlib.h>

struct node{
	char input;
	struct node* rightSide;
	struct node* leftSide;
};

/* Inserts the characters into a BST */
struct node* insert(struct node *root, char i){
	if(root == NULL){
		root = malloc(sizeof(struct node));
		root->input = i;
		root->leftSide = NULL;
		root->rightSide = NULL;
	}
	else if(i < root->input){
		root->leftSide = insert(root->leftSide,i);
	}
	else{
		root->rightSide = insert(root->rightSide,i);
	}
	return root;
}

/* Inserts the characters into a Balanced BST */
struct node* insertBalanced(struct node *root, char i){
	 if(root == NULL){
                root = malloc(sizeof(struct node));
                root->input = i;
                root->leftSide = NULL;
                root->rightSide = NULL;
        }
	/* Checks to see how many nodes each side has so it knows where to insert */
	else if(getHeight(root->leftSide,0) == getHeight(root->rightSide,0)){
		if(i < root->input){
                	root->leftSide = insertBalanced(root->leftSide,i);
        	}else{   
                	root->rightSide = insertBalanced(root->rightSide,i);
        	}
	} else if(getHeight(root->leftSide,0) < getHeight(root->rightSide,0)){
		root->leftSide = insertBalanced(root->leftSide,i);
	} else {
		root->rightSide = insertBalanced(root->rightSide,i);
	}
        return root;
}

/* used to balance the tree, it tells how many nodes are below the root */
int getHeight(struct node *root,int counter){
	int totalHeight = 1;
	if (root == NULL){
	}else{
		counter++;
		counter = getHeight(root->leftSide,counter);
		counter = getHeight(root->rightSide,counter);
	}
	return counter; 	
}

/* Prints out the tree in a pleasing manner */
void printTree(struct node *root,int i){
	int n;
	if(root == NULL){
	}
	else {
		i += 7;
		printTree(root->rightSide,i);
		printf("\n");
		for(n = 7;n < i; n++){
			printf("  ");
		}
		printf("%c",root->input);

		printTree(root->leftSide, i);
	}
}

/* Finds the min character */
struct node* min(struct node *root){
	if(root == NULL){
		return NULL;
	}
	else if(root->leftSide != NULL){
        	return min(root->leftSide); 
	}
	return root;
}

/* Deleted the node of the character that is specified */
struct node* delete(struct node *root, char c){
	struct node* holder;
	if(root == NULL){
		return NULL;
	}
	else if(c < root->input){
		root->leftSide = delete(root->leftSide, c);
	}
	else if(c > root->input){
		root->rightSide = delete(root->rightSide, c);
	} else { 
        	if(root->leftSide == NULL && root->rightSide == NULL){
			free(root);
			return NULL;
		} else if(root->leftSide == NULL || root->rightSide == NULL){
			if(root->leftSide ==NULL){
                		holder = root->rightSide;
            		}else{
                		holder = root->leftSide;
            		}
			free(root);
            		return holder;
		} else {
            		holder = min(root->rightSide);
           		root->input = holder->input;
            		root->rightSide = delete(root->rightSide, holder->input);
       		}
    	}
	return root;
}

/* Main program that asks the user for input and calls the other methods */
int main(int argc, char *argv[]){
        /* set up varaibles to use */
	int i = 0, z = 0;
	int counter = 0;
        char c;
	FILE *in_file;
        struct node* root;
	struct node* helper;
	struct node* blank;
	char keepTrack[100];
        root  = NULL;
	helper = NULL;
	blank = NULL;
	
	if(*argv[2] == 'f'){
		in_file  = fopen(argv[3], "r");
		c = getc(in_file);
		while(c != EOF){
			if(argc > 1 && *argv[1] == 'n'){
				root = insert(root,c);
				counter++;
			} else {
				keepTrack[counter] = c;	
				root = insertBalanced(root,c);
				counter++;
			}
			c = getc(in_file);
		}
		fclose(in_file);
	}
	/* Prompts the user to pick an option and repeats until the user picks 4 */
        while(i != 4){
                printf("\n(1) Add a Node \n(2) Remove a Node \n(3) Print the Tree \n(4) Quit");
                printf("\nEnter the number of the option you would like to choose: ");
                scanf("%d",&i);
		/* Defaults to Balanced BST */
                if(i == 1){
                        printf("Enter Character to Add: ");
                        scanf(" %c",&c);
                        if(argc > 1 && *argv[1] == 'n'){
                                root = insert(root,c);
				counter++;
                        } else {
				keepTrack[counter] = c;
                                root = insertBalanced(root,c);
				counter++;
                        }
                }
		/* Defaults to Balanced BST */
                else if(i == 2){
                        printf("Enter Character to Remove: ");
                        scanf(" %c",&c);
			if(argc > 1 && *argv[1] == 'n'){
                        	root = delete(root,c);
			} else {
				for(z = 0; z <= counter; z++){
					if(keepTrack[z] != c && keepTrack[z] != ' '){ 
						helper = insertBalanced(helper,keepTrack[z]);
					} else {
						keepTrack[z] = ' ';
					}
				}
				root = helper; 
				helper = blank; 
			}
                }
                else if(i == 3){
			if(counter == 0){
				printf("No tree to show");
			} else {
                        	printTree(root,0);
			}
                }

        }
}
