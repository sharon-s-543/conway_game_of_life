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

# num=int(input("Number of alive cells initially: "))

#indices=[]
#i=0
#while i<dim**2:
#    index=input("Enter indices separated by comma: ").split(",")
#    if index==['run']:
#        break
#    indices.append(index)
#    i+=1

# ===========================================
# Comment out the input block and uncomment
# the hardcoded values.

# Cool pattern I found online.
# Use 15×15 matrix

#indices = [
#        [3,3],[3,4],[3,5],[3,6],[3,7],[3,8],
#        [4,3],[4,4],[4,5],[4,6],[4,7],[4,8],
#        [3,10],[3,11],[4,10],[4,11],[5,10],
#        [5,11],[6,10],[6,11],[7,10],[7,11],
#        [8,10],[8,11],[6,3],[6,4],[7,3],[7,4],
#        [8,3],[8,4],[9,3],[9,4],[10,3],[10,4],
#        [11,3],[11,4],[10,6],[10,7],[10,8],
#        [10,9],[10,10],[10,11],[11,6],[11,7],
#        [11,8],[11,9],[11,10],[11,11]
#            ]

# --------------------------------------------

### === OSCILLATORS === 20×20

# Blinker

# indices=[[10,9],[10,10],[10,11]]
# --------------------------------------------

# Toad
#indices=[# top row
#        [9,10],[9,11],[9,12],
#        # bottom row
#        [10,9],[10,10],[10,11]
#        ]

# Beacon
#indices=[
#    # top-left block
#    [8,8],[8,9],
#    [9,8],[9,9],
#    # bottom-right block
#    [10,10],[10,11],
#    [11,10],[11,11],
#]

# Pulsar

#indices=[
#        # Top bar (row 3)
#        [3,5],[3,6],[3,7],[3,11],[3,12],[3,13],
#        # Upper-left/upper-right verticals (rows 5-7)
#        [5,3],[5,8],[5,10],[5,15],
#        [6,3],[6,8],[6,10],[6,15],
#        [7,3],[7,8],[7,10],[7,15],
#
#       # Upper-mid bar (row 8)
#       [8,5],[8,6],[8,7],[8,11],[8,12],[8,13],
#
#                                            # Lower-mid bar (row 10)
#                                                [10,5],[10,6],[10,7],[10,11],[10,12],[10,13],
#
#                                                    # Lower-left/lower-right verticals (rows 11-13)
#                                                        [11,3],[11,8],[11,10],[11,15],
#                                                            [12,3],[12,8],[12,10],[12,15],
#                                                                [13,3],[13,8],[13,10],[13,15],
#
#                                                                    # Bottom bar (row 15)
#                                                                        [15,5],[15,6],[15,7],[15,11],[15,12],[15,13],
#                                                                        ]
#
# -------------------------------------------
# Gosper Glider Gun
# 36 dim 90 gen

#indices=[
#    # Left square block (stable)
#    [4,0],[4,1],
#    [5,0],[5,1],
#
#    # Left structure
#    [4,10],[5,10],[6,10],
#    [3,11],[7,11],
#    [2,12],[8,12],
#    [2,13],[8,13],
#    [5,14],
#    [3,15],[7,15],
#    [4,16],[5,16],[6,16],
#    [5,17],
#
#    # Right structure
#    [2,20],[3,20],[4,20],
#    [2,21],[3,21],[4,21],
#    [1,22],[5,22],
#    [0,24],[1,24],[5,24],[6,24],
#
#    # Right square block (stable)
#    [2,34],[3,34],
#    [2,35],[3,35],
#]

### === SPACESHIPS ===

# Middleweight Spaceship

indices=[
    [2,4],
    [3,2],[3,6],
    [4,7],
    [5,2],[5,7],
    [6,3],[6,4],[6,5],[6,6],[6,7]
]

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
    time.sleep(0.3)
    clear_screen()
    k+=1



