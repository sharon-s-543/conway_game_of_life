import os
import time

def clear_screen():
    os.system('cls' if os.name=='nt' else 'clear')
# time.sleep(3)

def print_matrix(matrix,dim):
    for i in range(dim):
        for j in range(dim):
            print(matrix[i*dim+j],end=" ")
        print(" ")

def count_alive(row,column):
    alive_count=0
    for i in range(-1,2):
        r=row+i
        for j in range(-1,2):
            c=column+j
            if i==0 and j==0:
                continue
            if 0<=r<dim and 0<=c<dim:
                if matrix[r*dim+c]=='■':
                    alive_count+=1
    return alive_count

def new_gen(matrix,dim):
    new_matrix=matrix.copy()
    
    for i in range(dim):
        for j in range(dim):
            
            cell=matrix[i*dim+j]
            if count_alive(i,j)<2:
                new_matrix[i*dim+j]='.'
            if cell=='■' and (count_alive(i,j)==2 or count_alive(i,j)==3):
                new_matrix[i*dim+j]='■'
            if count_alive(i,j)>3:
                new_matrix[i*dim+j]='.'
            if cell=='.' and count_alive(i,j)==3:
                new_matrix[i*dim+j]='■'

    matrix_updated=new_matrix
    return matrix_updated

# ============================================

dim=int(input("Dimension of the square matrix: "))

gen=int(input("Number of generations: "))

num=int(input("Number of alive cells initially: "))

indices=[]
for i in range(num):
    index=input("Enter indices separated by comma: ").split(",")
    #if index=='run':
        #break
    indices.append(index)

# ============================================

matrix=[]
i=0
while i<dim**2:
    matrix.append('.')
    i+=1

for index in indices:
    i=int(index[0])
    j=int(index[1])
    matrix[i*dim+j]="■"

# matrix[2*dim+0]="■"
# matrix[1*dim+3]="■"

k=0
while k<gen:
    print_matrix(matrix,dim)
    matrix=new_gen(matrix,dim)
    time.sleep(1)
    clear_screen()
    k+=1



