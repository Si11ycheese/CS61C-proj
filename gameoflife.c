/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//x,y position
int px[8]={-1,0,1,-1,1,-1,0,1};
int py[8]={1,1,1,0,0,-1,-1,-1};
//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
    Color *nextState=(Color *) malloc(sizeof(Color));
    int isAliveR,isAliveG,isAliveB;//check if it is alive or not.
    int neighNumR=0,neighNumG=0,neighNumB=0;//count num of neighbors
    isAliveR=(*(image->image+row*image->cols+col))->R==255;
    isAliveG=(*(image->image+row*image->cols+col))->G==255;
    isAliveB=(*(image->image+row*image->cols+col))->B==255;
    for(int i=0;i<8;i++){
        int dx=(row+px[i])%(image->rows);
        int dy=(col+py[i])%(image->cols);
        if((*(image->image+dx*image->cols+dy)   )->R==255){
            neighNumR++;
        }
        if((*(image->image+dx*image->cols+dy))->G==255){
            neighNumG++;
        }
        if((*(image->image+dx*image->cols+dy))->B==255){
            neighNumB++;
        }
    }
    int moveStepR=9*isAliveR+neighNumR;
    int moveStepG=9*isAliveG+neighNumG;
    int moveStepB=9*isAliveB+neighNumB;
    if(rule&(1<<moveStepR)){
        nextState->R=255;

    }else{
        nextState->R=0;
    }
    if(rule&(1<<moveStepG)){
        nextState->G=255;

    }else{
        nextState->G=0;
    }
    if(rule&(1<<moveStepB)){
        nextState->B=255;

    }else{
        nextState->B=0;
    }
    return nextState;

}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
    Image *newImage=(Image *)malloc(sizeof(Image));
    newImage->rows=image->rows;
    newImage->cols=image->cols;
    newImage->image=(Color**)malloc(sizeof(Color *)*(image->rows)*(image->cols));
    Color **p=newImage->image;
    for(int i=0;i<newImage->rows;i++){
        for(int j=0;j<newImage->cols;j++){
            *p= evaluateOneCell(image,i,j,rule);
            p++;
        }
    }
    return newImage;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
    if(argc!=3){
        printf("usage: ./gameOfLife filename rule\n"
               "    filename is an ASCII PPM file (type P3) with maximum value 255.\n"
               "    rule is a hex number beginning with 0x; Life is 0x1808.");
        return -1;
    }
    Image *image= readData(argv[1]);
     uint32_t rule=strtol(argv[2],NULL,16);
     Image *nextImage=life(image,rule);
    writeData(nextImage);
    freeImage(image);
    freeImage(nextImage);
    return 0;
}
