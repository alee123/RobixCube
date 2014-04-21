/* Example code for Software Systems at Olin College.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

EDITED BY Amanda Lee
Quiz 4, Question 1
March 2014

Filled in insert_by_index 

*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct cube {
    int ** F;
    int ** B;
    int ** U;
    int ** D;
    int ** L;
    int ** R;
} Cube;


void print_cube(Cube *cube) {
    int i,j,k,l,m;
    for (i=0;i<3;i++){ 
        printf("      ");
        for(j=0;j<3;j++){
            printf("%d ",cube->U[i][j]);
        }
        printf("\n");
    }
    for (i=0;i<3;i++){ 
        for(j=0;j<3;j++){
            printf("%d ",cube->L[i][j]);
        }
        for(k=0;k<3;k++){
            printf("%d ",cube->F[i][k]);
        }
        for(l=0;l<3;l++){
            printf("%d ",cube->R[i][l]);
        }
        for(m=0;m<3;m++){
            printf("%d ",cube->B[i][m]);
        }
        printf("\n");
    }
    for (i=0;i<3;i++){ 
        printf("      ");
        for(j=0;j<3;j++){
            printf("%d ",cube->D[i][j]);
        }
        printf("\n");
    }
}

int **init_face(int val){
    int **face = (int **) malloc(sizeof(int *) * 3);
    int x, y;

    for (x = 0; x<3; x++) {
        face[x] = malloc(3 * sizeof(int));
        for (y=0; y<3; y++) {
            face[x][y] = val;
        }
    }
    
    return face;
}

Cube *init_cube(){
    Cube *cube = malloc(sizeof(Cube));
    cube->F = init_face(1);
    cube->B = init_face(4);
    cube->L = init_face(2);
    cube->R = init_face(3);
    cube->U = init_face(5);
    cube->D = init_face(6);
    
    return cube;
}

void rotate_face(int ***face, char dir[]){
    int **temp = *face;
    int i,j;

    for(i=0; i<3; i++) {
        for(j=i; j<3; j++) {
            if(i!=j) {
                temp[i][j]^=temp[j][i];
                temp[j][i]^=temp[i][j];
                temp[i][j]^=temp[j][i];
            }
        }
    }

    if (!strcmp(dir,"C")){
        for(i=0; i<3/2; i++) {
            for(j=0; j<3; j++) {
                temp[j][i]^=temp[j][2-i];
                temp[j][2-i]^=temp[j][i];
                temp[j][i]^=temp[j][2-i];
            }
        }
    }
    else if(!strcmp(dir,"CC")) {
        for(i=0; i<3/2; i++) {
            for(j=0; j<3; j++) {
                temp[i][j]^=temp[2-i][j];
                temp[2-i][j]^=temp[i][j];
                temp[i][j]^=temp[2-i][j];
            }
        }    
    }
    else{
        rotate_face(&temp, "C");  
        rotate_face(&temp, "C");   
    }
}   


void rotate_edges(int ***one, int ***two, int ***three, int ***four, char dir[]){
    int **t1 = *one;
    int **t2 = *two;
    int **t3 = *three;
    int **t4 = *four;

    rotate_face(&t4,"C");
    rotate_face(&t2,"CC");
    rotate_face(&t3,"180");

    int i,j;
    int temp;
    for(i=0;i<3;i++){
        temp = t1[2][i];
        if (!strcmp(dir,"C")){
            t1[2][i] = t4[2][i];
            t4[2][i] = t3[2][i];
            t3[2][i] = t2[2][i];
            t2[2][i] = temp;
        }
        else{
            t1[2][i] = t2[2][i];
            t2[2][i] = t3[2][i];
            t3[2][i] = t4[2][i];
            t4[2][i] = temp;    
        }
    }

    rotate_face(&t4,"CC");
    rotate_face(&t2, "C");
    rotate_face(&t3, "180");
}

void rotate_cube(Cube **cube, char face[],char dir[]){
    Cube *temp = *cube;
    int **toRotate;
    int **one; 
    int **two;
    int **three; 
    int **four;

    switch(face[0]) {
        case 'F': 
            toRotate = temp->F;
            rotate_edges(&(temp->U), &temp->R, &temp->D, &temp->L, dir);    
            break;
        case 'B':
            toRotate = temp->B;
            rotate_face(&temp->U,"180");
            rotate_face(&temp->D,"180");
            rotate_edges(&(temp->U), &temp->L, &temp->D, &temp->R, dir);
            rotate_face(&temp->U,"180");
            rotate_face(&temp->D,"180");
            break;
        case 'U':
            rotate_face(&temp->R,"CC");
            rotate_face(&temp->L, "C");
            rotate_face(&temp->B,"180");
            toRotate = temp->U;
            rotate_edges(&(temp->B), &temp->R, &temp->F, &temp->L, dir);
            rotate_face(&temp->R,"C");
            rotate_face(&temp->L, "CC");
            rotate_face(&temp->B,"180");
            break;
        case 'D':
            toRotate = temp->D;
            rotate_face(&temp->R,"C");
            rotate_face(&temp->L, "CC");
            rotate_face(&temp->B,"180");
            rotate_edges(&(temp->F), &temp->R, &temp->B, &temp->L, dir);
            rotate_face(&temp->R,"CC");
            rotate_face(&temp->L, "C");
            rotate_face(&temp->B,"180");
            break;
        case 'L':
            toRotate = temp->L;
            rotate_face(&temp->U, "CC");
            rotate_face(&temp->D,"C");
            rotate_edges(&(temp->U), &temp->F, &temp->D, &temp->B, dir);
            rotate_face(&temp->U, "C");
            rotate_face(&temp->D,"CC");
            break;
        case 'R':
            toRotate = temp->R;
            rotate_face(&temp->U, "C");
            rotate_face(&temp->D,"CC");
            rotate_edges(&(temp->U), &temp->B, &temp->D, &temp->F, dir);
            rotate_face(&temp->U, "CC");
            rotate_face(&temp->D,"C");
            break;
    }
    rotate_face(&toRotate, dir);
}

void final_cube(Cube *cube){
    int i,j;
    for (i=0;i<3;i++){ 
        for(j=0;j<3;j++){
            printf("%d",cube->U[i][j]);
        }
    }
    for (i=0;i<3;i++){ 
        for(j=0;j<3;j++){
            printf("%d",cube->L[i][j]);
        }
    }
    for (i=0;i<3;i++){ 
        for(j=0;j<3;j++){
            printf("%d",cube->F[i][j]);
        }
    }
    for (i=0;i<3;i++){ 
        for(j=0;j<3;j++){
            printf("%d",cube->R[i][j]);
        }
    }
    for (i=0;i<3;i++){ 
        for(j=0;j<3;j++){
            printf("%d",cube->B[i][j]);
        }
    }
    for (i=0;i<3;i++){ 
        for(j=0;j<3;j++){
            printf("%d",cube->D[i][j]);
        }
    }
    printf ("\n");
}

int main() {
    Cube *test_cube = init_cube();
    
    rotate_cube(&test_cube,"F", "C");
    rotate_cube(&test_cube,"R", "C");
    rotate_cube(&test_cube,"L", "CC");
    rotate_cube(&test_cube,"B", "C");
    rotate_cube(&test_cube,"B", "C");
    rotate_cube(&test_cube,"D", "C");

    print_cube(test_cube);

    //final_cube(test_cube);
}
