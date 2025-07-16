#include "image.h"
#include "string.h"



Image *load_image(char *filename) { 
    //Image a;   
    // (void)filename;
    // return NULL;
    char format[3]="P3";
    unsigned int width=0;;
    unsigned int height=0;
    unsigned int maxIntensity = 255;
    
   
    FILE *file = fopen(filename,"r");

    //Check to see if file is valid
    if (file==NULL){
        return NULL;
    }
   
    Image *a = (Image *) malloc (sizeof(Image));
    if (a==NULL){
        //printf("A IS NULL");
        fclose(file);
        free(a->pixels);
        free(a);
        return NULL;
    }

    fscanf(file, "%s", format);
    strcpy(a->format, format);
    a->format[2]='\0';

    //Skipping single line comments
    //fgetc is used to read characters from a file until the end of the file is reached
    //ungetc is used to pushback or unread a character to a file stream
    //EOF is end of file
    char ch;
    while ((ch=fgetc(file))!=EOF){
        //printf("%i\n",ch);
        if (ch=='#'){
            while((ch=fgetc(file))!=EOF && ch!='\n'){
                
            }  
        }
        else if (ch=='\n'||ch==' '|| ch=='\t'){
            continue;
        }
        else{
            ungetc(ch, file);
            break;
        }
    }    

    //Scan file and store values
    
    fscanf(file,"%u %u",&width, &height);
    fscanf(file, "%u", &maxIntensity);

    // printf("FORMAT: %s\n", format);
    // printf("WIDTH: %\n", width);
    // printf("HEIGHT: %i\n", height);
    // printf("INTENSITY: %i\n", maxIntensity);

    //Malloc space for struct
    
    strcpy(a->format,format);
    a->width = width;
    a->height = height;
    a->maxIntensity = maxIntensity;

    a->pixels = (unsigned char*) malloc (width*height*3*sizeof(unsigned char));
    if (a->pixels==NULL){
        //printf("A->PIXELS IS NULL");
        free(a->pixels);
        free(a);
        fclose(file);
        return NULL;
    }

    for (unsigned int i=0;i<width*height;i++){
        int r,g,b;
        fscanf(file, "%i %i %i", &r,&g, &b);
        a->pixels[i]=(unsigned char)r;
        a->pixels[i+1]=(unsigned char)g;
        a->pixels[i+2]= (unsigned char)b;
    }


    
    printf("Format: %s\n", a->format);
    printf("Width: %u\n", a->width);
    printf("Height: %u\n", a->height);
    printf("Maximum: %u\n", a->maxIntensity);


    fclose(file);
    
    return a;

}

void delete_image(Image *image) {
    //(void)image;
   if (image!=NULL){
        if (image->pixels!=NULL){
            free(image->pixels);
        }
        free(image);
   }
}

unsigned short get_image_width(Image *image) {
    // (void)image;
    // return 0;
    return image->width;
}

unsigned short get_image_height(Image *image) {
    // (void)image;
    // return 0;
    return image->height;
}

unsigned char get_image_intensity(Image *image, unsigned int row, unsigned int col) {
    // (void)image;
    // (void)row;
    // (void)col;
    //return 0;

    unsigned int index = row*image->width+col;
    return image->pixels[index];
}


unsigned int hide_message(char *message, char *input_filename, char *output_filename) {
    // (void)message;
    // (void)input_filename;
    // (void)output_filename;
    //return 0;
    FILE *input_file = fopen(input_filename, "r");
    if (input_file==NULL){
        fclose(input_file);
        return 0;
    }
    FILE *output_file= fopen(output_filename, "w");
    if (output_file==NULL){
        fclose(output_file);
        return 0;
    }

    Image *a = load_image(input_filename);
    if (a==NULL){
        fclose(input_file);
        fclose(output_file);
        return 0;
    }

    
    fprintf(output_file, "%s\n", a->format);
    fprintf(output_file, "%u %u\n", a->width, a->height);
    fprintf(output_file, "%u\n", a->maxIntensity);

    int size = strlen(message);
    int max_characters = (a->width*a->height)/8-1;
    int encode=0;
    


    if (size<max_characters){
        encode = size;
    }
    else{
        encode = max_characters;
    }

    unsigned int pixel_index=0;


    //Go through the characters in the message and store it in the pixels
    for (int i=0;i<encode;i++){
        unsigned char c = message[i];
        for (int j=0;j<8;j++){
            pixel_index = (i*8+j);
            unsigned int b = (unsigned int)a->pixels[pixel_index];
            if (((unsigned int)c>>(7-j))&0x1){
                b|=0x1;
            }
            else{
                b&=0xFE;
            }
            fprintf(output_file, "%u %u %u\n", b, b, b);
        }
    }
   
    //Put null character at the end of last 8 pixels
    for (unsigned int j=0;j<8;j++){
        pixel_index++;
        unsigned int b = (unsigned int)a->pixels[pixel_index];
        b&=0xFE;
        fprintf(output_file, "%u %u %u\n", b,b, b);    
        
    }
    for (unsigned int i=pixel_index+1;i<(a->width*a->height);i++){
       unsigned int b = (unsigned int)(a->pixels[i]);
       fprintf(output_file, "%u %u %u\n", b, b, b);
    }
    
    delete_image(a);
    fclose(input_file);
    fclose(output_file);

    return encode;

}




char *reveal_message(char *input_filename) {
    // (void)input_filename;
    // return NULL;

    //Opens a file of the given filename
    //Extracts the message hidden in the image
    //Returns a new string containing the message
    //Assume that only printable characters (and spaces) are hidden in the message and that the message is terminated with a null character
    
    FILE *file = fopen(input_filename, "r");

    if (file == NULL){
        fclose(file);
        return NULL;
    }
    Image *a = load_image(input_filename);
    if (a==NULL){
        fclose(file);
        return NULL;
    }

    int max_characters = (a->width * a->height *3)/8;

    //unsigned char *pixel_values = a->pixels;
    char* reveal_messages =(char *)malloc(max_characters+1);
    if (reveal_messages==NULL){
        free(a->pixels);
        free(a);
        fclose(file);
        return NULL;
    }

    for (int i=0;i<max_characters;i++){
        //Set message values
        unsigned char c = 0;
        for (int j=0;j<8;j++){
            unsigned int pixel_index = (i*8)+j; //row major order
            c = (c<<1)|(a->pixels[pixel_index]&0x1);
        }
       reveal_messages[i]=c;

       //Null Terminator
       if (c=='\0'){
            break;
       }
        
    }
    
    reveal_messages[max_characters]='\0';

    delete_image(a);
    fclose(file);



    return reveal_messages;

    

}

unsigned int hide_image(char *secret_image_filename, char *input_filename, char *output_filename) {
    // (void)secret_image_filename;
    // (void)input_filename;
    // (void)output_filename;
    // return 10;

    FILE *input_file = fopen(input_filename, "r");
    if (input_file==NULL){
        fclose(input_file);
        return 0;
    }

    FILE *secret_image_file = fopen(secret_image_filename, "r");
    if (secret_image_file==NULL){
        fclose(input_file);
        fclose(secret_image_file);
        return 0;
    }
    
    FILE *output_file= fopen(output_filename, "w");
    if (output_file==NULL){
        fclose(input_file);
        fclose(secret_image_file);
        fclose(output_file);
        return 0;
    }

    Image *a = load_image(input_filename);
    Image *secret = load_image(secret_image_filename);

    if (a==NULL){
        fclose(input_file);
        fclose(output_file);
        fclose(secret_image_file);
        delete_image(a);
        delete_image(secret);
        return 0;
    }
    if (secret==NULL){
        fclose(input_file);
        fclose(output_file);
        fclose(secret_image_file);
        delete_image(a);
        delete_image(secret);
        return 0;
    }


    fprintf(output_file, "%s\n", a->format);
    fprintf(output_file, "%u %u\n", a->width, a->height);
    fprintf(output_file, "%u\n", a->maxIntensity);

    int total_pixels = (a->width * a->height);
    int num_pixels = (secret->width * secret->height);

    if (total_pixels<16 + (num_pixels*8)){
        free(a->pixels);
        free(a);
        free(secret->pixels);
        free(secret);
        fclose(input_file);
        fclose(output_file);
        fclose(secret_image_file);
        return 0;
    }
   
    unsigned int pixel_index = 0;
    
    unsigned char secret_width = (unsigned char)secret->width;
    unsigned char secret_height = (unsigned char)secret->height;

    //Putting the width
    for (int i=0;i<8;i++){
        
        unsigned int b = (unsigned int)a->pixels[pixel_index];
        if (((secret_width>>(7-i))&0x1)==1){
            b|=0x1;
        } else{
            b&=0xFE;
        }
        fprintf(output_file, "%u %u %u\n", b, b, b);
        pixel_index++;
    }

    //Putting the height

    for (int i=0;i<8;i++){
        unsigned int b = (unsigned int)a->pixels[pixel_index];
        if (((secret_height>>(7-i))&0x1)==1){
            b|=0x1;
        } else{
            b&=0xFE;
        }
        fprintf(output_file, "%u %u %u\n", b, b, b);
        pixel_index++;
    }


    //Pixels of secret image

    for (int i=0;i<num_pixels;i++){
       unsigned char c = secret->pixels[i];
        for (int j=0;j<8;j++){
            unsigned int b = (unsigned int)a->pixels[pixel_index];
            if ((((unsigned int)c>>(7-j))&0x1)==1){
                b|=0x1;
            }
            else{
                b&=0xFE;
            }

            fprintf(output_file, "%u %u %u\n", b,b,b);
            pixel_index++;
      }
       
    }
    
    for (int i=pixel_index;i<total_pixels;i++){
       unsigned int b = (unsigned int)(a->pixels[i]);
       fprintf(output_file, "%u %u %u\n", b, b, b);
    }
    
    delete_image(a);
    delete_image(secret);
    fclose(input_file);
    fclose(output_file);
    fclose(secret_image_file);

    return 1;

}



void reveal_image(char *input_filename, char *output_filename) {
    // (void)input_filename;
    // (void)output_filename;
    FILE *input_file = fopen(input_filename, "r");
    if (input_file==NULL){
        //fclose(input_file);
        return;
    }
    FILE *output_file = fopen(output_filename, "w");
    if (output_file==NULL){
        fclose(output_file);
        return;
    }
    Image *a = load_image(input_filename);
    if (a==NULL){
        fclose(input_file);
        fclose(output_file);
        return;
    }
    
    if (a->width * a->height<16){
        free(a->pixels);
        free(a);
        fclose(input_file);
        fclose(output_file);
        return;
    }
    // In the output image, first store the 8-bit width (W) and 8-bit height (H) values of the secret image in the first 16 pixels of the output image. 

    unsigned char width[8];
    unsigned char height[8];

    for (unsigned int i=0;i<8;i++){
        width[i]=(a->pixels[i]&0x1);
    }
    for (unsigned int j=0;j<8;j++){
        height[j]=(a->pixels[(8+j)]&0x1);
    }

    unsigned int w = 0;
    unsigned int h = 0;
    for (unsigned int i=0;i<8;i++){
        w = (w<<1)|width[i];
        h = (h<<1)|height[i];
    }

    if (w*h>(a->width * a->height - 16)/8){
        free(a->pixels);
        free(a);
        fclose(input_file);
        fclose(output_file);
    }

    unsigned char *reveal_images = malloc(w*h);
    if (reveal_images == NULL){
        free(a->pixels);
        free(a);
        fclose(input_file);
        fclose(output_file);
        return;
    }

    for (unsigned int i=0;i<w*h;i++){
        //Set message values
        unsigned char c = 0;
        for (int j=0;j<8;j++){
            unsigned int pixel_index = (16+(i*8)+j); //row major order
            if (pixel_index>=a->width*a->height){
                free(reveal_images);
                free(a->pixels);
                free(a);
                fclose(input_file);
                fclose(output_file);
                return;
            }
            c = (c<<1)|(a->pixels[pixel_index]&0x1);
        }
        reveal_images[i] = c;
       

       //Null Terminator
    //    if (c=='\0'){
    //         break;
    //    }
        
    }

    char format[3] = "P3";
    unsigned int max_intensity = 255;
    
    fprintf(output_file, "%s\n", format);
    fprintf(output_file, "%u %u\n", w, h);
    fprintf(output_file,"%u\n", max_intensity);

    for (unsigned int i=0;i<w*h;i++){
        fprintf(output_file, "%u %u %u\n", reveal_images[i], reveal_images[i],  reveal_images[i]);
    }


    free(reveal_images);
    free (a->pixels);
    free(a);
    fclose(input_file);
    fclose(output_file);
   

}



