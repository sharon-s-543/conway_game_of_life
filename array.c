#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_matrix(int matrix[],int dim);
int count_alive(int matrix[],int dim,int row,int column);
int* new_gen(int matrix[],int new_matrix[],int dim);

int main(){

	int dim,n_cells;
	printf("Enter the dimesion of the square matrix: ");
	if(scanf("%d", &dim) != 1){
		fprintf(stderr,"Invalid input.\n");
		return 1;
	}


	printf("Number of cells to be alive: ");
	if(scanf("%d", &n_cells) != 1){
		fprintf(stderr,"Invalid input.\n");
		return 1;
	}
	if(n_cells>dim*dim){
		printf("Number of cells out of bounds.\n");
		return 1;
	}


// ==========================================
// --------- Collecting the indices. --------
// ==========================================

	int *cells=malloc(n_cells*sizeof(int));
	if(cells==NULL){
		printf("Memory allocation failed.");
		return 1;
	}

	int x=0; int y=0;
	for(int i=0;i<2*n_cells;i+=2){
		printf("Enter cell index (comma separated): ");
		// scanf(" %d, %d",&x,&y);
		if(scanf(" %d, %d",&x,&y)!=2){
			fprintf(stderr,"Invalid input.\n");
			return 1;
		} 
		
		if(x>=0 && x<dim && y>=0 && y<dim){
			cells[i]=x;
			cells[i+1]=y;
		}else{
			printf("Index out of bounds.\n");
			i-=2;
		}
	}
	printf("\n");


// ==========================================
// ---------- Building the matrix. ----------
// ==========================================

	int *matrix=calloc(dim*dim,sizeof(int));

	if(matrix==NULL){
		printf("Memory allocation failed.\n");
		return 1;
	}



// ==========================================
// --- Adding the number 1 to the indices ---
// ==========================================

	int a,b;
	for(int i=0;i<2*n_cells;i+=2){
		a=cells[i];
		b=cells[i+1];
		matrix[a*dim+b]=1;
	}

	free(cells);
	cells=NULL;

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// PRINTING THE MATRIX

	/*
	for(int i=0;i<dim;i++){
	for(int j=0;j<dim;j++){
		printf("%d ",matrix[i*dim+j]);		}
		printf("\n");              
	}                        
	printf("\n");
	*/

	print_matrix(matrix,dim);
	printf("================\n");

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


	int *new_matrix=malloc(dim*dim*sizeof(int));
	
	if(new_matrix==NULL){
		printf("Memory allocation failed.\n");
		return 1;
	}

	//[: new_gen() function :]
	
	// matrix
	// new_matrix
	
	print_matrix(matrix,dim);

	/*
	int k=0;
	while(k<5){
		print_matrix(new_gen(matrix,new_matrix,dim),dim);	
		k++;
	} */

	int k=0;
	while(k<5){
		new_gen(matrix,new_matrix,dim);
		print_matrix(new_matrix,dim);

		int *temp=matrix;
		matrix=new_matrix;
		new_matrix=temp;

		k++;
	}

	free(new_matrix);
	new_matrix=NULL;

// ============ TEST CASES ============

/*	
[[0. 0. 0. 0. 0. 0. 0. 0.]
 [1. 1. 0. 0. 0. 0. 0. 0.]
 [0. 1. 1. 0. 0. 0. 0. 0.]
 [0. 0. 0. 1. 1. 0. 0. 0.]
 [0. 0. 0. 0. 1. 0. 0. 0.]
 [0. 0. 0. 0. 1. 0. 1. 0.]
 [0. 1. 0. 0. 0. 0. 0. 0.]
 [1. 0. 0. 0. 0. 0. 0. 0.]] */
   
/*

matrix[5*dim+6]=1;
matrix[7*dim+0]=1;
matrix[6*dim+1]=1;
matrix[1*dim+0]=1;
matrix[1*dim+1]=1;
matrix[2*dim+1]=1;
matrix[2*dim+2]=1;
matrix[3*dim+3]=1;
matrix[3*dim+4]=1;
matrix[4*dim+4]=1;
matrix[5*dim+4]=1;

*/

int state=0;

state=count_alive(matrix,dim,0,6);
printf("0,6: 0\n");
printf("%d\n",state);

state=count_alive(matrix,dim,6,7);
printf("6,7: 1\n");
printf("%d\n",state);

state=count_alive(matrix,dim,4,3);
printf("4,3: 4\n");
printf("%d\n",state);

state=count_alive(matrix,dim,5,6);
printf("5,6: 0\n");
printf("%d\n",state);

state=count_alive(matrix,dim,7,0);
printf("7,0: 1\n");
printf("%d\n",state);

state=count_alive(matrix,dim,2,2);
printf("2,2: 3\n");
printf("%d\n",state);

state=count_alive(matrix,dim,5,2);
printf("5,2: 1\n");
printf("%d\n",state);

// =====================================
	free(matrix);
	matrix=NULL;
	return 0;
}


// ==========================================
// ----------- Other functions. -------------
// ==========================================

// A function to print matrices.

void print_matrix(int matrix[],int dim){
	for(int i=0;i<dim;i++){
	for(int j=0;j<dim;j++){
		printf("%d ",matrix[i*dim+j]);
	}
		printf("\n");
	}
	printf("\n");
}


// A function to count the neighbours of a cell.


int count_alive(int matrix[],int dim,int row,int column){

	int alive_counter=0;

	for(int i=-1;i<=1;i++){
	for(int j=-1;j<=1;j++){
		int r=row+i;
		int c=column+j;

		if(i==0 && j==0){
			continue;
		}
		if(0<=r && r<dim && 0<=c && c<dim){
			if(matrix[r*dim+c]==1){
				alive_counter++;
			}
		}
	}
	}
	return alive_counter;
}

// OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
// 
// What next?
// Have to add the rules of the game.


/*
 * Underpopulation: Any live cell with fewer than two live neighbors dies.
 *
 * Survival: Any live cell with two or three live neighbors stays alive.
 *
 * Overcrowding: Any live cell with more than three live neighbors dies.
 *
 * Reproduction: Any dead cell with exactly three live neighbors becomes a live cell.
 *
 */

// int count_alive(int matrix[],int dim,int row,int column)

// A function to create the next generation.

int* new_gen(int matrix[],int new_matrix[],int dim){


/*
 * Here, we are copying our matrix into a new
 * matrix to prevent corruption of the original
 * matrix while applying the game rules.
 */


	for(int i=0;i<dim;i++){
	for(int j=0;j<dim;j++){
		new_matrix[i*dim+j]=matrix[i*dim+j];
	}
	}
	
	
// Writing the game rules.
// ------------------------

	for(int i=0;i<dim;i++){
	for(int j=0;j<dim;j++){
		int cell=matrix[i*dim+j];
		
		/*
		int *pNew_cell=NULL;
		*pNew_cell=new_matrix[i*dim+j];
		*/

		int neighbors=count_alive(matrix,dim,i,j);

		if(neighbors<2){
			new_matrix[i*dim+j]=0;
		}
		if((neighbors==2 || neighbors==3) && cell==1){
			new_matrix[i*dim+j]=1;
		}
		if(neighbors>3){
			new_matrix[i*dim+j]=0;
		}
		if(neighbors==3 && cell==0){
			new_matrix[i*dim+j]=1;
		}
	}
	}
	int* matrix_updated=new_matrix;

	return matrix_updated;
}
