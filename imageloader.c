/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
    FILE *fp= fopen(filename,"r");
    if(fp==NULL){
        return NULL;
    }
    Image *image=(Image *) malloc(sizeof(Image));
    fscanf(fp,"%u",&image->rows);
    fscanf(fp,"%u",&image->cols);
    int sum=image->cols*image->rows;
    for(int i=0;i<sum;i++){
        *(image->image+i)=(Color *) malloc(sizeof(Color));
        Color *Pixel=*(image->image+i);
        fscanf(fp,"%hhu %hhu %hhu",&Pixel->R,&Pixel->G,&Pixel->B);
    }
    fclose(fp);
    return image;

}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
    printf("P3\n%d %d\n255\n", image->cols, image->rows);
    Color** p = image->image;
    for (int i = 0; i < image->rows; i++) {
        for (int j = 0; j < image->cols - 1; j++) {
            printf("%3hhu %3hhu %3hhu   ", (*p)->R, (*p)->G, (*p)->B);
            p++;
        }
        printf("%3hhu %3hhu %3hhu\n", (*p)->R, (*p)->G, (*p)->B);
        p++;
    }

}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
    int sum=image->cols*image->rows;
    for(int i=0;i<sum;i++){
        free(*(image->image+i));
    }
    free(image->image);
    free(image);

}