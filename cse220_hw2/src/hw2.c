#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hw2.h"

void print_packet(unsigned int packet[])
{   

    unsigned int packet_type = (packet[0] >> 30) & 0xF;
    unsigned int length = packet[0] &  0x3FF;
    unsigned int requester_id = (packet[1]>>16) & 0xFFFF;
    unsigned int tag = (packet[1]>>8) & 0xFF;
    unsigned int last_be = (packet[1]>>4) & 0xF;
    unsigned int first_be = packet[1] & 0xF;
    unsigned int address = packet[2];
    
    if (packet_type==1){
        printf("Packet Type: Write\n");
    }
    else{
        printf("Packet Type: Read\n");
    }

    printf("Address: %i\n", address);
    printf("Length: %i\n", length);
    printf("Requester ID: %i\n", requester_id);
    printf("Tag: %i\n", tag);
    printf("Last BE: %i\n", last_be);
    printf("1st BE: %i\n", first_be);
   
    printf("Data: ");
   
    if (packet_type==1){
        for (unsigned int i=3;i<3 + length;i++){
            printf("%d ", (int) packet[i]);
        }
        printf("\n");
        
    } else{
        printf("\n");
    }
       
}


void store_values(unsigned int packets[], char *memory)
{

    //for (int i=0;i<sizeof(packets);i++){
    
    int i=0;
    int is_valid = 1;
    while (is_valid){

        unsigned int packet_type = (packets[i] >> 30) & 0x3;
        unsigned int length = packets[i] &  0x3FF;
        unsigned int last_be = (packets[i+1]>>4) & 0xF;
        unsigned int first_be = packets[i+1] & 0xF;
        unsigned int address = packets[i+2];

        if (packet_type!=1){
            is_valid=0;
            break;
        }

        if (address+length*4>=0x100000){
            is_valid=0;
            break;
        }

        for (unsigned int j=0;j<length;j++){
            unsigned int data = packets[i+3+j];
            if (j==0){
                for (int c=0;c<4;c++){
                    //Shift the data and care about last 4 bits
                    if ((first_be>>c)&1){
                        memory[address]=(data>>(8*c))&0xFF;
                    } 
                    address++;
                }
            
            }       
            else if (j==length-1){
                for (int c=0;c<4;c++){
                    if ((last_be>>c)&1){
                        memory[address]=(data>>(8*c))&0xFF;
                    }
                    address++;
                }
            } 
            else {
                for (int c=0;c<4;c++){
                    memory[address]=(data >> (8*c))&0xFF;
                    address++;
                }
            }
        }
        i+=3+length; //Move to next packet

       
               
    //(void)packets;
    //(void)memory;
    }
}

// unsigned int* create_completion(unsigned int packets[], const char *memory)
// {
    //(void)packets;
    //(void)memory;
	//return NULL;

    // int i=0;
    // int is_valid = 1;
    // while (is_valid){
    //     unsigned int packet_type = (packets[0] >> 30) & 0x3;
    //     unsigned int length = packets[0] &  0x3FF;
    //     unsigned int requester_id = (packets[1]>>16) & 0xFFFF;
    //     unsigned int tag = (packets[1]>>8) & 0xFF;
    //     unsigned int last_be = (packets[1]>>4) & 0xF;
    //     unsigned int first_be = packets[1] & 0xF;
    //     unsigned int address = packets[2];

    //     unsigned int j=0;
    //      for (unsigned int j=0;j<length;j++){
    //         //unsigned int data = packets[i+3+j];
    //         if (j==0){
    //             for (int c=0;c<4;c++){
    //                 //Shift the data and care about last 4 bits
    //                 if ((first_be>>c)&1){
    //                     memory[address]=(data>>(8*c))&0xFF;
    //                 } 
    //                 address++;
    //             }
            
    //         }       
    //         else if (j==length-1){
    //             for (int c=0;c<4;c++){
    //                 if ((last_be>>c)&1){
    //                     memory[address]=(data>>(8*c))&0xFF;
    //                 }
    //                 address++;
    //             }
    //         } 
    //         else {
    //             for (int c=0;c<4;c++){
    //                 memory[address]=(data >> (8*c))&0xFF;
    //                 address++;
    //             }
    //         }
    //     }
    //     i+=3; //Move to next packet


    // }







    //unsigned int* ret = (unsigned int*)malloc(i*4*j[N+3]);















    //Memory contains data
    //Packet contain Read Requests (int[0,1,2]), memory given to you
    //Parsing out like Part2
    //Read the contents from the memory based on whatever I have parsed out int the header
    //Create completion packet which contains the information
    //Malloc memory to write the information
    //no memory read may cross a 0x4000 address boundary.

    //Malloc
    //return type: unsigned integer array
    //4*int[N+3] one packet
    //Mod length and get remainder

    //Malloc 4*(3k*length)
    

// }


//GOOD ONE

// unsigned int* create_completion(unsigned int packets[], const char *memory)
// {
//     //(void)packets;
//     //(void)memory;
// 	//return NULL;

//     unsigned int* result =malloc(10000*sizeof(unsigned int));
    
//     int completion_index=0;
//     int i=0; //run through packets
//     int is_valid = 1; //check validity
//     while (is_valid){
//         //Extract header values from each individual packet
//         unsigned int packet_type = packets[i] & 0xFFFFFC00;
//        //unsigned int full_packet_type = (packets[i]>>10)&0x3FFFFF;
//         unsigned int length = packets[i] &  0x3FF;
//         unsigned int requester_id = (packets[i+1]>>16) & 0xFFFF;
//         unsigned int tag = (packets[i+1]>>8) & 0xFF;
//         unsigned int last_be = (packets[i+1]>>4) & 0xF;
//         unsigned int first_be = packets[i+1] & 0xF;
//         unsigned int address = packets[i+2];

//         if (packet_type!=0){
//             is_valid=0;
//             break;
//         }

//         if (address+length*4>=0x100000){
//             is_valid=0;
//             break;
//         }

//         unsigned int bytes_remaining = length*4;
//         unsigned int original_length = bytes_remaining;
//         unsigned int completer_id = 220;
//         unsigned int num_completion;
//         unsigned int byte_count;

//         while (bytes_remaining>0){
//             num_completion=0;

           
//              //How much data included in each completion

//             //bytes before the limit
//             int boundary = 0x4000-(address&0x3FF);
//             if (boundary<0){
//                 boundary=0;
//             }
//             if ((bytes_remaining> (unsigned int) boundary)&&(boundary>0)){
//                 num_completion = boundary/4;
//                 //byte_count=boundary;
//             }
//             else{
//                 num_completion = bytes_remaining/4;
//                 //byte_count=bytes_remaining;
//             }

//             unsigned int lower_address = address&0x7F;
//             //printf("%u", lower_address);
//             byte_count = original_length;
//             //unsigned int byte_count = original_length;

//             //Store headers in completion packet
//             result[completion_index++]=(0x25<<25)|num_completion;
//             //printf("%x\n", result[completion_index]);
//             result[completion_index++]=(completer_id<<16)|(byte_count); //Byte count supposed to be 12?
//              //printf("%x\n", result[completion_index]);
//             result[completion_index++]=(requester_id<<16)|(tag<<8)|lower_address; 
//              //printf("%x\n", result[completion_index]);


//             for (unsigned int j=0;j<num_completion;j++){
//                 unsigned int data = 0;

//                 if (j==0){
//                     for (int c=0;c<4;c++){
//                         if ((first_be>>c)&1){
//                             data|=((memory[address+c]&0xFF)<<(8*c));
//                         } 
//                     }
                
//                 }       
//                 else if (j==num_completion-1){
//                     for (int c=0;c<4;c++){
//                         if ((last_be>>c)&1){
//                         data|=((memory[address+c]&0xFF)<<(8*c));
//                         }
//                     }
//                 } 
//                 else {
//                     for (int c=0;c<4;c++){
//                         data|=((memory[address+c]&0xFF)<<(8*c));
//                     }
//                 }

             

//                 result[completion_index++]=data;
//                  //printf("%x\n", result[completion_index]);
                
//                 address+=4;

//             }

//             bytes_remaining -=num_completion*4;

//             // if(completion_index>=100){
//             //     result=realloc(result,(completion_index+100)*sizeof(unsigned int));
//             // }
                 
//         }
    
//         i+=3; //Move to next packet


//     }

//    // unsigned int* final_result = realloc(result, (completion_index)*sizeof(unsigned int));
  
//     return result;
//     free(result);


// }

unsigned int* create_completion(unsigned int packets[], const char *memory)
{
    //(void)packets;
    //(void)memory;
	//return NULL;

    unsigned int* result =malloc(100000*sizeof(unsigned int));
    printf("START HEREEEEEEE\n");
    int completion_index=0;
    int i=0; //run through packets
    int is_valid = 1; //check validity
    while (is_valid){
        //Extract header values from each individual packet
        unsigned int packet_type = packets[i] & 0xFFFFFC00;
       //unsigned int full_packet_type = (packets[i]>>10)&0x3FFFFF;
        unsigned int length = packets[i] &  0x3FF;
        unsigned int requester_id = (packets[i+1]>>16) & 0xFFFF;
        unsigned int tag = (packets[i+1]>>8) & 0xFF;
        unsigned int last_be = (packets[i+1]>>4) & 0xF;
        unsigned int first_be = packets[i+1] & 0xF;
        unsigned int address = packets[i+2];

        if (packet_type!=0){
            is_valid=0;
            break;
        }

        if (address+length*4>=0x100000){
            is_valid=0;
            break;
        }

        unsigned int bytes_remaining = length*4;
        printf("length: %d\n", length);
       // unsigned int original_length = bytes_remaining;
        unsigned int completer_id = 220;
        unsigned int num_completion=0;
        unsigned int byte_count = length*4;

        //int count=0;

        while (bytes_remaining>0){
            //num_completion=0;
            printf("BYTES REMAINING:%d\n",bytes_remaining);


            printf("ADDRESS:%d\n", address);
             //How much data included in each completion

            //bytes before the limit
            int boundary = 0x4000-(address&0x3FFF);
            //int boundary = 0x4000-(address);
            printf("BOUNDARY:%d\n", boundary);
            if (boundary<0){
                boundary=0;
            }

            
            if ((bytes_remaining> (unsigned int) boundary)&&(boundary>0)){
                num_completion = boundary/4;
                
                //num_completion=boundary/4;
                byte_count=bytes_remaining;
                //byte_count=num_completion*4;
                
                printf("ANOTHER PACKET\n");
            }
            else{
                num_completion=bytes_remaining/4;
;
                byte_count=bytes_remaining;
                printf("STAY IN PACKET\n");
            }


            // if (boundary==4){
            //     byte_count=16;
            // }
            // if (bytes_remaining==4){
            //     byte_count=16;
            // }
            // if (num_completion == 0) {
            //     break; 
            // }

            
            //printf("%d\n",bytes_remaining);

              printf("BYTECOUNT%d\n",byte_count);

            unsigned int lower_address = address&0x7F;

            //printf("%u", lower_address);
            //byte_count = num_completion*4;
            //byte_count = original_length;
            //unsigned int byte_count = original_length;

            //Store headers in completion packet

           
            
            printf("NUMCOMPLETE GOING IN COMPLETION INDEX: %d\n",num_completion);
            result[completion_index++]=(0x25<<25)|num_completion;
            //printf("%x\n", result[completion_index]);


            result[completion_index++]=(completer_id<<16)|(byte_count); //Byte count supposed to be 12?

            printf("Completion: %d\n", completer_id<<16);
            printf("Int[2]: %d\n", result[completion_index-1]);
            
             //printf("%x\n", result[completion_index]);
            result[completion_index++]=(requester_id<<16)|(tag<<8)|lower_address; 
             //printf("%x\n", result[completion_index]);


            for (unsigned int j=0;j<num_completion;j++){
                unsigned int data = 0;

                if (j==0){
                    for (int c=0;c<4;c++){
                        if ((first_be>>c)&1){
                            data|=((memory[address+c]&0xFF)<<(8*c));
                        } 
                    }
                
                }       
                else if (j==num_completion-1){
                    for (int c=0;c<4;c++){
                        if ((last_be>>c)&1){
                        data|=((memory[address+c]&0xFF)<<(8*c));
                        }
                    }
                } 
                else {
                    for (int c=0;c<4;c++){
                        data|=((memory[address+c]&0xFF)<<(8*c));
                    }
                }

             

                result[completion_index++]=data;
                 //printf("%x\n", result[completion_index]);
                
                address+=4;

            }

            bytes_remaining -=(num_completion*4);
            
            
            //printf("%d\n",bytes_remaining);
             //printf("NUMCOMPLETE%d\n",num_completion);

            // if(completion_index>=100){
            //     result=realloc(result,(completion_index+100)*sizeof(unsigned int));
            // }
            //fix num_completion
        }
    
        i+=3; //Move to next packet


    }

   // unsigned int* final_result = realloc(result, (completion_index)*sizeof(unsigned int));
  
    return result;
    free(result);


}
