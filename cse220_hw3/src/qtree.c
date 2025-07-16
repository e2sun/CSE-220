#include "qtree.h"
#include <math.h>

QTNode *create_quadtree(Image *image, double max_rmse) {
    // (void)image;
    // (void)max_rmse;
    // return NULL;
    if (image==NULL){
        return NULL;
    }
    return create_quadtree_helper(image, max_rmse, 0, 0, image->width, image->height);
}
//Helper function
QTNode *create_quadtree_helper(Image *image, double max_rmse, int start_row, int start_col, int width, int height){
    if (image==NULL){
        return NULL;
    }
    double average_intensity = calculate_average_intensity(image, start_row, start_col, width, height);
    double rmse = calculate_rmse(image, start_row, start_col, width, height, average_intensity);

    QTNode *node = (QTNode *)malloc(sizeof(QTNode));
    node->child1 = NULL;
    node->child2 = NULL;
    node->child3 = NULL;
    node->child4 = NULL;
    if (node==NULL){
        return NULL;
    }
    
    node->average_Intensity = (unsigned char)(average_intensity);
    node->start_row = start_row;
    node->height = height;
    node->start_col = start_col;
    node-> width = width;

    if (rmse<=max_rmse){
        node->child1 = NULL;
        node->child2 = NULL;
        node->child3 = NULL;
        node->child4 = NULL;
        return node;
    }
    int half_width = width/2;
    int half_height = height/2;
   

    if (width==1){
        node->child1 = create_quadtree_helper(image, max_rmse, start_row, start_col, width, half_height);
        node->child2 = NULL;
        node->child3 = create_quadtree_helper(image, max_rmse, start_row+half_height, start_col, width, height-half_height);
        node->child4 = NULL;
    }
    else if (height==1){
        node->child1 = create_quadtree_helper(image, max_rmse, start_row, start_col, half_width, height);
        node-> child2 = create_quadtree_helper(image, max_rmse, start_row,start_col+half_width,width-half_width, height);
        node->child3 = NULL;
        node->child4 = NULL;
    }
    else{
        node->child1 = create_quadtree_helper(image, max_rmse, start_row, start_col,half_width, half_height);
        node->child2 = create_quadtree_helper(image, max_rmse, start_row, start_col+half_width,width-half_width,half_height);
        node->child3 = create_quadtree_helper(image, max_rmse, start_row+half_height, start_col,half_width,height-half_height);
        node->child4 = create_quadtree_helper(image, max_rmse, start_row+half_height, start_col+half_width,width-half_width,height-half_height);

    }
    return node;
    
}

double calculate_average_intensity(Image *image, int start_row, int start_col, int width, int height){
    if (image==NULL){
        return 0;
    }
    double sum=0.0;
    int num_pixel=width*height;
    //int pixel_index=0;

    //Looping through each pixel
    for (int row = start_row;row<start_row+height;row++){
        for (int col=start_col;col<start_col+width;col++){
            //2D array convert to 1D array
            int pixel_index = (row*image->width+col);
            unsigned char intensity = image->pixels[pixel_index];
            sum+=intensity;

        }
    }
    return sum/num_pixel;
}
double calculate_rmse(Image *image, int start_row, int start_col, int width, int height, double average_intensity){
    if (image==NULL){
        return 0;
    }
    double rmse=0.0;
    //int pixel_index=0;
    int num_pixels=width*height;
    for (int row = start_row;row<start_row+height;row++){
        for (int col=start_col;col<start_col+width;col++){
            int pixel_index=row*image->width+col;
            unsigned char currentIntensity = (image->pixels[pixel_index]);
            double difference = (double)currentIntensity-average_intensity;
            rmse+=difference*difference;
        }
         
    }
    return sqrt(rmse/num_pixels);
    
}

QTNode *get_child1(QTNode *node) {
    // (void)node;
    // return NULL;
    if (node==NULL){
        return NULL;
    }
    return node->child1;  
}

QTNode *get_child2(QTNode *node) {
    // (void)node;
    // return NULL
    if (node==NULL){
        return NULL;
    }
    return node->child2;
}

QTNode *get_child3(QTNode *node) {
    // (void)node;
    // return NULL;
    if (node==NULL){
        return NULL;
    }
    return node->child3;
}

QTNode *get_child4(QTNode *node) {
    // (void)node;
    // return NULL;
    if (node==NULL){
        return NULL;
    }
    return node->child4;
}

unsigned char get_node_intensity(QTNode *node) {
    // (void)node;
    // return 0;
    if (node==NULL){
        return 0;
    }
    return node->average_Intensity;
}

void delete_quadtree(QTNode *root) {
    //(void)root;
    if (root!=NULL){
        delete_quadtree_helper(root);
    }  
    //free(root); 
}
//Free memory recursively 

void delete_quadtree_helper(QTNode *node){
    if (node==NULL){
        return;
    }
    delete_quadtree_helper(node->child1);
    delete_quadtree_helper(node->child2);
    delete_quadtree_helper(node->child3);
    delete_quadtree_helper(node->child4);

    free(node);

}


// void save_qtree_as_ppm(QTNode *root, char *filename) {
//     // (void)root;
//     // (void)filename;
//     if (root==NULL){
//         return;
//     }
//     FILE *file = fopen(filename, "w");
//     if (file==NULL){
//         fclose(file);
//         return;
//     }
//     //Write to file
//     char format[3] = "P3";
//     unsigned int max_intensity=255;
//     // unsigned int width = root->width;
//     // unsigned int height = root->height;
//     fprintf(file, "%s\n", format);
//     //fprintf(file, "P3\n");
//     fprintf(file, "%u %u\n", root->width, root->height);
//     fprintf(file, "%u\n", max_intensity);


//     unsigned char *pixels = (unsigned char *)malloc(root->width*root->height*3);
//     if (pixels==NULL){
//         fclose(file);
//         return;
//     }

//     for (unsigned int r=0;r<root->height;r++){
//         for (unsigned int c=0;c<root->width;c++){

//             QTNode *node = root;
//             if (node==NULL){
//                 delete_quadtree(node);
                
//             }
//             unsigned int start_row=0;
//             unsigned int start_col=0;
//             unsigned int w= root->width;
//             unsigned int h = root->height;
        

//             while(node!=NULL && node->child1!=NULL){
//                 unsigned int half_width=w/2;
//                 unsigned int half_height = h/2;
//                 //Upper left, Upper right, Lower left, Lower right respectively
//                 if (r<start_row+half_height&&c<start_col+half_width){
//                     node=node->child1;
//                 } else if (r<start_row+half_height&&c>=start_col+half_width){
//                     node=node->child2;
//                     start_col+=half_width;
//                 }
//                 else if (r>=start_row+half_height&&c<start_col+half_width){
//                     node=node->child3;
//                     start_row+=half_height;
//                 }
//                 else{
//                     node=node->child4;
//                     start_row+=half_height;
//                     start_col+=half_width;
//                 }
//                 w = half_width;
//                 h = half_height;
//             }
//             if (node!=NULL){
//                 unsigned char average_Intensity = node->average_Intensity;
//                 int pixel_index = (r*root->width+c)*3;
//                 pixels[pixel_index]=average_Intensity;
//                 pixels[pixel_index+1]=average_Intensity;
//                 pixels[pixel_index+2]=average_Intensity;

//             }
            
//         }
//     }
//     //Putting it in the file
//     for (unsigned int i=0;i<root->width*root->height*3;i+=3){
//         fprintf(file, "%hhu %hhu %hhu ", pixels[i],pixels[i+1], pixels[i+2]);
//     }


//     free(pixels);
//     fclose(file);
// }

void save_qtree_as_ppm(QTNode *root, char *filename) {
    // (void)root;
    // (void)filename;
    if (root==NULL){
        return;
    }
    FILE *file = fopen(filename, "w");
    if (file==NULL){
        fclose(file);
        return;
    }
    //Write to file
    char format[3] = "P3";
    unsigned int max_intensity=255;
    // unsigned int width = root->width;
    // unsigned int height = root->height;
    fprintf(file, "%s\n", format);
    //fprintf(file, "P3\n");
    fprintf(file, "%u %u\n", root->width, root->height);
    fprintf(file, "%u\n", max_intensity);


    unsigned char *pixels = (unsigned char *)malloc(root->width*root->height*3);
    if (pixels==NULL){
        fclose(file);
        return;
    }

    //Initialize pixel values? 
    for (unsigned int i =0; i<root->width * root->height *3; i++){
        pixels[i]=0;
    }

    for (unsigned int r=0;r<root->height;r++){
        for (unsigned int c=0;c<root->width;c++){

            QTNode *node = root;
        
            unsigned int start_row=0;
            unsigned int start_col=0;
            unsigned int w= root->width;
            unsigned int h = root->height;
        

            while(node!=NULL && node->child1!=NULL){
                unsigned int half_width=w/2;
                unsigned int half_height = h/2;
                //Upper left, Upper right, Lower left, Lower right respectively
                if (r<start_row+half_height&&c<start_col+half_width){
                    node=node->child1;
                } else if (r<start_row+half_height&&c>=start_col+half_width){
                    node=node->child2;
                    start_col+=half_width;
                }
                else if (r>=start_row+half_height&&c<start_col+half_width){
                    node=node->child3;
                    start_row+=half_height;
                }
                else{
                    node=node->child4;
                    start_row+=half_height;
                    start_col+=half_width;
                }
                w = half_width;
                h = half_height;
            }
            if (node!=NULL){
                unsigned char average_Intensity = node->average_Intensity;
                int pixel_index = (r*root->width+c)*3;
                pixels[pixel_index]=average_Intensity;
                pixels[pixel_index+1]=average_Intensity;
                pixels[pixel_index+2]=average_Intensity;

            }
            
        }
    }
    //Putting it in the file
    for (unsigned int i=0;i<root->width*root->height*3;i+=3){
        fprintf(file, "%hhu %hhu %hhu ", pixels[i],pixels[i+1], pixels[i+2]);
    }


    free(pixels);
    fclose(file);
}




QTNode *load_preorder_qt(char *filename){
    // (void)filename;
    // return NULL;
    FILE *file = fopen(filename,"r");
    if (file==NULL){
        return NULL;
    }

    //Check to see if file is valid
    if (file==NULL){
        return NULL;
    }
    QTNode *root = load_preorder_qt_helper(file);
    if (root==NULL){
        return root;
    }
    fclose(file);
    return root;
}

QTNode *load_preorder_qt_helper(FILE *file) {
    
    //Read the data from the file which is organized using a preorder traversal
    //You first get the information for the current node and then the information for its children
    //As function reads data, it creates a new QTNode for each node in the quadtree and fills the properties of each node (intensity value and ref to children)
    //Once function reads all data and builds entire quadtree structure in memory, returns a pointer to the root fo the quadtree

    char type;
    if (fscanf(file, " %c", &type)!=1){\
        return NULL;
    }


    QTNode *node = (QTNode *)malloc(sizeof(QTNode));
    node->child1=NULL;
    node->child2=NULL;
    node->child3=NULL;
    node->child4=NULL;
    if (node==NULL){
        return NULL;
    }
    //Try deleting the arguments one by one and seeing if it fails
    //unsigned char intensity;
    unsigned int intensity,start_row, height,start_col, width;
    if (fscanf(file, "%u %u %u %u %u\n", &intensity, &start_row, &height, &start_col, &width)!=5){
        //printf("READING NODE FAILED");
        //free(node);
        delete_quadtree(node);
        return NULL;
    }
    
    // printf("Intensity: %u\n", intensity);
    // printf("Start Row: %u\n", start_row);
    // printf("Height: %u\n", height);
    // printf("Start Col: %u\n", start_col);
    // printf("Width: %u\n", width);
    
    node->average_Intensity = intensity;
    node->start_row = start_row;
    node->height = height;
    node->start_col = start_col;
    node->width = width;

    //printf("TYPE: %c\n", type);

    if (type=='L'){
        //Making a leaf node
        //printf("MADE IT IN LEAF NODE\n");
        node->child1 = NULL;
        node->child2 = NULL;
        node->child3 = NULL;
        node->child4 = NULL;
       
    } else if (type=='N'){
        //Making an internal node
        //printf("MADE IT IN INTERNAL NODE\n");
        if (node->width==1){
            node->child1 = load_preorder_qt_helper(file);
            node->child2 = NULL;
            node->child3 = load_preorder_qt_helper(file);
            node->child4 = NULL;
        }
        else if (node->height==1){
            node->child1 = load_preorder_qt_helper(file);
            node->child2 = load_preorder_qt_helper(file);
            node->child3 = NULL;
            node->child4 = NULL;

        }
        else{
            node->child1 = load_preorder_qt_helper(file);
            node->child2 = load_preorder_qt_helper(file);
            node->child3 = load_preorder_qt_helper(file);
            node->child4 = load_preorder_qt_helper(file);

        }
       
    }
    else{
        //printf("IN ELSE STATEMENT");
        //free(node);
        delete_quadtree(node);
        return NULL;

    }
    return node;
    
}


void save_preorder_qt(QTNode *root, char *filename) {
    if (root==NULL){
        return;
    }
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return; 
    }
    save_preorder_qt_helper(root, file);
    fclose(file);
}

void save_preorder_qt_helper(QTNode *root, FILE *file) {
    if (root == NULL) {
        return; 
    }

    if (root->child1 == NULL && root->child2 == NULL && root->child3 == NULL && root->child4 == NULL) {
        //Leaf Node
        fprintf(file, "L %u %u %u %u %u\n", root->average_Intensity, root->start_row, root->height, root->start_col, root->width); 
    } else {
        //Internal Nodes
        fprintf(file, "N %u %u %u %u %u\n", root->average_Intensity, root->start_row, root->height, root->start_col, root->width); 
        save_preorder_qt_helper(root->child1, file);
        save_preorder_qt_helper(root->child2, file);
        save_preorder_qt_helper(root->child3, file);
        save_preorder_qt_helper(root->child4, file);
    }
}



