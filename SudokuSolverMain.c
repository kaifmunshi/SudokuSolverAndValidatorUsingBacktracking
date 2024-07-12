#include<stdio.h>
#include<stdlib.h>
#define N 9 // ROW AND COLUMN SIZE OF MATRIX
// Board Matrix 
int board[N][N];


void printBoard(){
    int i,j;
    for(i=0; i<N; i++){

        if(i % 3 == 0 && i != 0 ){
                printf("---------------------------\n");        // For horizontal lines
        }


        for(j=0; j<N; j++){
            
            if(j % 3 == 0 && j != 0 ){          // As we need vertical lines 
                printf(" | ");
            }
            printf("%d ", board[i][j]);
        }

        
        printf("\n");
    }
}



int getLen(char x[]){
    int count=0;
    while(x[count] != '\0'){
        count++;
    }
    return count;
}


void getPuzzle(){
     // Get sudoku matrix from th user.  
            
    printf("Enter the sudoku puzzle\n use '0' to indicate empty element\n");
    printf("A to I indicates the columns\n");
    printf("ABCDEFGHI\n");
    
    char row[9];
    int i;
    int br=0, bc=0; // Board row and column indexes
    
    for(i=0;i<9;i++){
        scanf("%s", row);
        if(getLen(row) != N){
            printf("Invalid Input, enter correct row data again.\n");
            while(1){
                scanf("%s" , row);
                
                if(getLen(row) == 9){
                    break;
                }
                printf("Invalid Input, enter correct row data again.\n");
            }
        }

        // check if only numbers are present.. 
        int z;
        for(z=0; z<9; z++){
            
            if(!(row[z] >= 48  && row[z] <=57)){
                
                printf("Invalid Input, Only numbers are allowed. Enter row data again.\n");
                while(1){
                scanf("%s" , row);
                if(getLen(row) == 9){
                    break;
                }
                printf("Invalid Input, Only numbers are allowed. Enter row data again.\n");
            }

            }
        }

        // now convert and store data.
        int t;  
        int itRow;
        itRow = atoi(row);
        bc = 8;
        for(t=0; t<9; t++){ 

            board[br][bc] = itRow % 10; // last digit
            itRow /= 10;
            bc--; 
        }

        br++;
        
    }
}   


int isSafeAfterEntry(int row, int col, int number){
    int i;

    if(number == 0){
        return 1;  // Dont check as it needs to be solved ... therefore assume it to be correct.
    }
    for(i=0; i<9; i++){
        if((board[row][i] == number && col != i) || (board[i][col] == number && row != i)){
            return 0;
        }

        // Check in the same 3*3 matrix..
        int r = 3*(row/3) + i/3;
        int c = 3*(col/3) + i%3;
        if(board[r][c] == number && (r!= row && c!= col)){
            return 0;
        }
    }

    return 1;
}

int validateInput(){
    int i,j;
    // for each element of the row
    for(i=0; i<9; i++){
        for(j=0;j<9;j++){
            if(!(isSafeAfterEntry(i, j, board[i][j]))){
                printf("Invalid Element --> %d at row: %d column: %d\n", board[i][j], i, j);
                return 0;
            }
        }
    }

    return 1;
}

int isSafe(int row, int col, int number){
    int i;
    for(i=0; i<9; i++){
        // check for row and column 
        if(board[row][i] == number || board[i][col] == number){
            return 0;
        }

        // Check in the same 3*3 matrix..
        if(board[3*(row/3) + i/3][3*(col/3) + i%3] == number){
            return 0;
        }
    } 

    return 1;
}




int solve(){

    int n = 9;
    int row, col;
    for(row=0; row<n; row++){
        for(col=0; col<n; col++){
            
            // Find empty cell 
            if(board[row][col] == 0){
                int val;
                for(val=1; val<=9; val++){
                    if(isSafe(row, col, val)){
                        board[row][col] = val;

                        // Recursive call
                        if(solve()){    // if solution found return true --> 1 
                            return 1;
                        } else{
                            // No futher solution found,, therefore backtracking.
                            board[row][col] = 0;
                            // printf("BAck Tracking: \n");
                            // printBoard();
                        }
                    }
                }

                return 0;
            }
        }
    }
    return 1; // Solution found
}



void main(){

     // Driver code
    char exit = '0';
    while(exit!='f'){
        
        
        printf("[1] Generate solution for sodoku puzzle\n");
        printf("[2] Validate your solution\n");
        printf("[3]Exit\n");
        printf("Enter a choice: ");
        int choice;
        scanf("%c", &choice);
        
        // Check user input..
        if(choice == '1'){

            getPuzzle();
            printf("You have entered:\n");
            printBoard();

            if(!(validateInput())){
                printf("Puzzle is not valid.Please enter correct puzzle\n");
                continue;
            }
            solve();
            printf("\nSolution\n");
            printBoard();
            
        }
        else if(choice == '2'){
            getPuzzle();
            printf("You have entered:\n");
            printBoard();

            if(!(validateInput())){
                printf("Your Solution is not valid\n");
                continue;
            }

            printf("Your solution is valid!\n");
        }
        else if(choice=='3')
        {
            exit = 'f';
            
        }
        else
        {
            printf("Invalid input!\n");
        }
    }   
}