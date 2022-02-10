#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int order;
void matrix_print(int **M, int order);


/******** input **********/
void order_input(){
    int flag = 0;

    while(order < 1){
        printf("Inserire l'ordine della matrice (interi > 1): ");
        scanf("%d", &order);
        if (flag)
            printf("Attenzione: il valore inserito non è valido.\n");
        flag = 1;
    }

    printf("Ordine inserito: %d\n", order);
}

void matrix_input(int ***M){
    int i, j;
    *M = (int **) malloc(order * sizeof(int *));

    for (i = 0; i < order; i++){
        (*M)[i] = (int *) malloc(order * sizeof(int));
        for (j = 0; j < order; j++){
            printf("Inserire valore %d,%d-esimo: ", i+1, j+1);
            scanf("%d", &(*M)[i][j]);
        }
        printf("\n");
    }
}
/*************************/

/********** determinant stuff **********/
void create_submatrix(int **M, int **submatrix, int dimension, int position){   //creates submatrix, position is the column to be excluded
    int i, j, J;

    for (i = 1; i < dimension; i++){    //iterates rows: starts from the second
        for (j = 0, J = 0; j < dimension; j++, J++){    //iterates columns
                if (!(j == position)){                  
                    submatrix[i - 1][J] = M[i][j];
                    }
                else
                    J--;                                //is j == column, set back 1 J so that element is not copied
        }
    }
}

int determinant(int **M, int dimension){
    /*
    iterates through first row: multiplies the element by -1 if i+j is odd then multiplies the result by the determinant
    of the submatrix calculated by excluding the first row and the first column. Repeats for every element of the row.
    */
    int i, j, det = 0;

    //allocate submatrix
    int **submatrix = malloc((dimension - 1) * sizeof(int *));  //allocates submatrix
    for (i = 0; i < dimension - 1; i++)
        submatrix[i] = malloc((dimension - 1) * sizeof(int));
    //end


    if (dimension == 1)
        return M[0][0];

    else if (dimension == 2)
        return (M[0][0] * M[1][1]) - (M[0][1] * M[1][0]);   //2x2 matrix: det = ad - bc

    else{
        for (i = 0; i < dimension; i++){    //scorre le righe della matrice M
            for (j = 0; j < dimension; j++){ //scorre le colonne
                create_submatrix(M, submatrix, dimension, j);   //crea una sottomatrice
                det += M[i][j] * pow(-1, j) * determinant(submatrix, dimension - 1);
            }
        }
    }
    free(submatrix);
    return det;   
}
/***************************************/

/*********** printing functions *******/
void print_matrix(int **M, int order){  //simple format version
    int i, j;

    for (i = 0; i < order; i++){
        for (j = 0; j < order; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }
    printf("\n");
}

void matrix_print(int **M, int order){  //cuter format
    int i, j, t, sum, max = 0, space;

    //allocates array that will contain every elemnts length (as in  digits), has form array[rows][columns]
    int **array = malloc((order + 1) * sizeof(int *));
    for (i = 0; i < order + 1; i++){
        array[i] = malloc((order) * sizeof(int));    //element with most digits has its length stored in last block, used later for spacing, hence the order + 1
        if (i == order)
            for (j = 0; j < order; j++)
                array[order][j] = 0;                     //setting element with most digits to 0
    }


    //calculates all elements length and stores them in allocated matrix, then stores longest of column in last block
    for (i = 0; i < order; i++){
        for (j = 0; j < order; j++){
            sum = 0;
            t = M[j][i];
            if (t <= 0){
                t = -t;
                sum++;
            }
            while (t > 0){
                t /= 10;
                sum++;
            }
            array[j][i] = sum;  //sum is number of element's digit
            if (sum > array[order][i])
                array[order][i] = sum;
        }
        max += array[order][i];
    }

    printf(" _ ");
    printf("%*s", max+order, "");   //prints max+order spaces
    printf("_\n");
    for (i = 0; i < order; i++){
        if (i != order -1) printf("| ");
        else printf("|_");
        for (j = 0; j < order; j++){
            space = array[order][j] - array[i][j];  //adds space such that all digits of a column are spaced as the longest + 1
            printf(" %d", M[i][j]);
            printf("%*s", space, "");
            
            
            if (i == order - 1 && j == order - 1){
                
            }
        }
        if (i != order - 1 && j != order - 1) printf("  |");
        else printf(" _|\n");
        printf("\n");
    }
}

int main(){
    int det, **M;

    order_input();
    matrix_input(&M);
    //print_matrix(M, order);
    matrix_print(M, order);
    det = determinant(M, order);
    printf("Determinant of input matrix is: %d\n\n", det);

    free(M);
    return 0;
}