  
void sw_auto_infer(float *memory, int image_offset, float *probabilities) 
{ 
 
   conv2d_sw( 
       memory + 23808,         // offset of input images 
       memory + 0,             // offset of weights 
       memory + 0,             // offset of biases 
       memory + 24592,         // offset of output images 
       1,                      // number of input images 
       8,                      // number of output images 
       28,                     // height 
       28,                     // width 
       3,                      // kernel height 
       3,                      // kernel width 
       1,                      // apply relu 
       0);                     // don't apply bias 
 
   conv2d_sw( 
       memory + 24592,         // offset of input images 
       memory + 72,            // offset of weights 
       memory + 0,             // offset of biases 
       memory + 30864,         // offset of output images 
       8,                      // number of input images 
       3,                      // number of output images 
       28,                     // height 
       28,                     // width 
       3,                      // kernel height 
       3,                      // kernel width 
       1,                      // apply relu 
       0);                     // don't apply bias 
 
   dense_sw( 
       memory + 30864,         // offset of input images 
       memory + 288,           // offset of weights 
       memory + 0,             // offset of biases 
       memory + 33216,         // offset of output images 
       1,                      // number of rows in input image 
       2352,                   // number of cols in input image 
       10,                     // number of output images 
       0,                      // don't apply relu 
       0);                     // don't apply_bias 
 
   softmax(memory + 33216, memory + 33226, 10); 
 
   memcpy(probabilities, memory + 33226, 10 * sizeof(float)); 
} 
 
void hw_auto_infer(cat_memory_type *memory, int image_offset, float *probabilities) 
{ 
 
   conv2d_hw( 
       memory,                                    
       23808,                  // offset of input images  
       0,                      // offset of weights       
       0,                      // offset of biases        
       24592,                  // offset of output images 
       1,                      // number of input images  
       8,                      // number of output images 
       28,                     // height                  
       28,                     // width                   
       3,                      // kernel height           
       3,                      // kernel width            
       1,                      // apply relu              
       0);                     // don't apply bias        
 
   conv2d_hw( 
       memory,                                    
       24592,                  // offset of input images  
       72,                     // offset of weights       
       0,                      // offset of biases        
       30864,                  // offset of output images 
       8,                      // number of input images  
       3,                      // number of output images 
       28,                     // height                  
       28,                     // width                   
       3,                      // kernel height           
       3,                      // kernel width            
       1,                      // apply relu              
       0);                     // don't apply bias        
 
   dense_hw( 
       memory,                                           
       30864,                  // offset of input images         
       288,                    // offset of weights              
       0,                      // offset of biases               
       33216,                  // offset of output images        
       1,                      // number of rows in input images 
       2352,                   // number of cols in input images 
       10,                     // number of output images        
       0,                      // don't apply relu        
       0);                     // don't apply_bias        
 
   float softmax_in[10];                        
   float softmax_out[10];                       
 
   copy_from_cat(memory, softmax_in, 33216, 10); 
 
   softmax(softmax_in, softmax_out, 10);         
 
   memcpy(probabilities, softmax_out, 10 * sizeof(float)); 
} 
 
