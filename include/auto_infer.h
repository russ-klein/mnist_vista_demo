  
void sw_auto_infer(float *memory, int image_offset, float *probabilities) 
{ 
 
   conv2d_sw( 
       memory + 7890,          // offset of input images 
       memory + 0,             // offset of weights 
       memory + 36,            // offset of biases 
       memory + 8674,          // offset of output images 
       1,                      // number of input images 
       4,                      // number of output images 
       28,                     // height 
       28,                     // width 
       3,                      // kernel height 
       3,                      // kernel width 
       1,                      // apply max pooling          
       1,                      // apply relu 
       1);                     // apply bias 
 
   dense_sw( 
       memory + 8674,          // offset of input images 
       memory + 40,            // offset of weights 
       memory + 7880,          // offset of biases 
       memory + 9458,          // offset of output images 
       1,                      // number of rows in input image 
       784,                    // number of cols in input image 
       10,                     // number of output images 
       0,                      // don't apply relu 
       1);                     // apply bias 
 
   softmax(memory + 9458, memory + 9468, 10); 
 
   memcpy(probabilities, memory + 9468, 10 * sizeof(float)); 
} 
 
void hw_auto_infer(cat_memory_type *memory, int image_offset, float *probabilities) 
{ 
 
   conv2d_hw( 
       memory,                                    
       7890,                   // offset of input images  
       0,                      // offset of weights       
       36,                     // offset of biases        
       8674,                   // offset of output images 
       1,                      // number of input images  
       4,                      // number of output images 
       28,                     // height                  
       28,                     // width                   
       3,                      // kernel height           
       3,                      // kernel width            
       1,                      // apply max pooling          
       1,                      // apply relu              
       1);                     // apply bias              
 
   dense_hw( 
       memory,                                           
       8674,                   // offset of input images         
       40,                     // offset of weights              
       7880,                   // offset of biases               
       9458,                   // offset of output images        
       1,                      // number of rows in input images 
       784,                    // number of cols in input images 
       10,                     // number of output images        
       0,                      // don't apply relu        
       1);                     // apply bias              
 
   float softmax_in[10];                        
   float softmax_out[10];                       
 
   copy_from_cat(memory, softmax_in, 9458, 10); 
 
   softmax(softmax_in, softmax_out, 10);         
 
   memcpy(probabilities, softmax_out, 10 * sizeof(float)); 
} 
 
