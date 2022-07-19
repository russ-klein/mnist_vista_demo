  
void sw_auto_infer(float *memory, int image_offset, float *probabilities) 
{ 
 
   conv2d_sw( 
       memory + 17360,         // offset of input images 
       memory + 0,             // offset of weights 
       memory + 375,           // offset of biases 
       memory + 18144,         // offset of output images 
       1,                      // number of input images 
       15,                     // number of output images 
       28,                     // height 
       28,                     // width 
       5,                      // kernel height 
       5,                      // kernel width 
       1,                      // apply max pooling          
       1,                      // apply relu 
       1);                     // apply bias 
 
   conv2d_sw( 
       memory + 18144,         // offset of input images 
       memory + 390,           // offset of weights 
       memory + 2415,          // offset of biases 
       memory + 21084,         // offset of output images 
       15,                     // number of input images 
       15,                     // number of output images 
       14,                     // height 
       14,                     // width 
       3,                      // kernel height 
       3,                      // kernel width 
       1,                      // apply max pooling          
       1,                      // apply relu 
       1);                     // apply bias 
 
   dense_sw( 
       memory + 21084,         // offset of input images 
       memory + 2430,          // offset of weights 
       memory + 17130,         // offset of biases 
       memory + 21819,         // offset of output images 
       1,                      // number of rows in input image 
       735,                    // number of cols in input image 
       20,                     // number of output images 
       0,                      // don't apply relu 
       1);                     // apply bias 
 
   dense_sw( 
       memory + 21819,         // offset of input images 
       memory + 17150,         // offset of weights 
       memory + 17350,         // offset of biases 
       memory + 21839,         // offset of output images 
       1,                      // number of rows in input image 
       20,                     // number of cols in input image 
       10,                     // number of output images 
       0,                      // don't apply relu 
       1);                     // apply bias 
 
   softmax(memory + 21839, memory + 21849, 10); 
 
   memcpy(probabilities, memory + 21849, 10 * sizeof(float)); 
} 
 
void hw_auto_infer(cat_memory_type *memory, int image_offset, float *probabilities) 
{ 
 
   conv2d_hw( 
       memory,                                    
       17360,                  // offset of input images  
       0,                      // offset of weights       
       375,                    // offset of biases        
       18144,                  // offset of output images 
       1,                      // number of input images  
       15,                     // number of output images 
       28,                     // height                  
       28,                     // width                   
       5,                      // kernel height           
       5,                      // kernel width            
       1,                      // apply max pooling          
       1,                      // apply relu              
       1);                     // apply bias              
 
   conv2d_hw( 
       memory,                                    
       18144,                  // offset of input images  
       390,                    // offset of weights       
       2415,                   // offset of biases        
       21084,                  // offset of output images 
       15,                     // number of input images  
       15,                     // number of output images 
       14,                     // height                  
       14,                     // width                   
       3,                      // kernel height           
       3,                      // kernel width            
       1,                      // apply max pooling          
       1,                      // apply relu              
       1);                     // apply bias              
 
   dense_hw( 
       memory,                                           
       21084,                  // offset of input images         
       2430,                   // offset of weights              
       17130,                  // offset of biases               
       21819,                  // offset of output images        
       1,                      // number of rows in input images 
       735,                    // number of cols in input images 
       20,                     // number of output images        
       0,                      // don't apply relu        
       1);                     // apply bias              
 
   dense_hw( 
       memory,                                           
       21819,                  // offset of input images         
       17150,                  // offset of weights              
       17350,                  // offset of biases               
       21839,                  // offset of output images        
       1,                      // number of rows in input images 
       20,                     // number of cols in input images 
       10,                     // number of output images        
       0,                      // don't apply relu        
       1);                     // apply bias              
 
   float softmax_in[10];                        
   float softmax_out[10];                       
 
   copy_from_cat(memory, softmax_in, 21839, 10); 
 
   softmax(softmax_in, softmax_out, 10);         
 
   memcpy(probabilities, softmax_out, 10 * sizeof(float)); 
} 
 
