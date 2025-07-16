#ifndef QTREE_H
#define QTREE_H

#include <stdio.h>
#include <stdlib.h>

#include "image.h"

#define INFO(...) do {fprintf(stderr, "[          ] [ INFO ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); fflush(stderr);} while(0)
#define ERROR(...) do {fprintf(stderr, "[          ] [ ERR  ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); fflush(stderr);} while(0) 

typedef struct QTNode {
    //char placeholder[1];  This is a placeholder. You should not use this struct.   
    //char type_node;
    unsigned char average_Intensity;
    unsigned int start_row;
    unsigned int height;
    unsigned int start_col;
    unsigned int width; 
    struct QTNode *child1;
    struct QTNode *child2;
    struct QTNode *child3;
    struct QTNode *child4;
} QTNode;

QTNode *create_quadtree(Image *image, double max_rmse);
QTNode *create_test_quadtree_TEST();  
QTNode *create_quadtree_helper(Image *image, double max_rsme, int start_row, int start_col, int width, int height);
double calculate_average_intensity(Image *image, int start_row, int start_col, int width, int height);
double calculate_rmse(Image *image, int start_row, int start_col, int width, int height, double average_intensity);
QTNode *get_child1(QTNode *node);
QTNode *get_child2(QTNode *node);
QTNode *get_child3(QTNode *node);
QTNode *get_child4(QTNode *node);
unsigned char get_node_intensity(QTNode *node);
void delete_quadtree(QTNode *root);
void delete_quadtree_helper(QTNode *node);
void save_qtree_as_ppm(QTNode *root, char *filename); 
QTNode *load_preorder_qt(char *filename);
QTNode *load_preorder_qt_helper(FILE *file);
void save_preorder_qt(QTNode *root, char *filename); 
void save_preorder_qt_helper(QTNode *root, FILE *file);

#endif // QTREE_H