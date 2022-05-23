  
void sw_auto_infer(float *memory, int image_offset, float *probabilities) 
{ 
 
   conv2d_sw( 
       memory + 23880,         // offset of input images 
       memory + 0,             // offset of weights 
       memory + 0,             // offset of biases 
       memory + 24664,         // offset of output images 
       1,                      // number of input images 
       10,                     // number of output images 
       28,                     // height 
       28,                     // width 
       3,                      // kernel height 
       3,                      // kernel width 
       1,                      // apply relu 
       0);                     // don't apply bias 
 
   conv2d_sw( 
       memory + 24664,         // offset of input images 
       memory + 90,            // offset of weights 
       memory + 0,             // offset of biases 
       memory + 32504,         // offset of output images 
       10,                     // number of input images 
       3,                      // number of output images 
       28,                     // height 
       28,                     // width 
       3,                      // kernel height 
       3,                      // kernel width 
       1,                      // apply relu 
       0);                     // don't apply bias 
 
   dense_sw( 
       memory + 32504,         // offset of input images 
       memory + 360,           // offset of weights 
       memory + 0,             // offset of biases 
       memory + 34856,         // offset of output images 
       1,                      // number of rows in input image 
       2352,                   // number of cols in input image 
       10,                     // number of output images 
       0,                      // don't apply relu 
       0);                     // don't apply_bias 
 
   softmax(memory + 34856, memory + 34866, 10); 
 
   memcpy(probabilities, memory + 34866, 10 * sizeof(float)); 
} 
 
void hw_auto_infer(cat_memory_type *memory, int image_offset, float *probabilities) 
{ 
 
   conv2d_hw( 
       memory,                                    
       23880,                  // offset of input images  
       0,                      // offset of weights       
       0,                      // offset of biases        
       24664,                  // offset of output images 
       1,                      // number of input images  
       10,                     // number of output images 
       28,                     // height                  
       28,                     // width                   
       3,                      // kernel height           
       3,                      // kernel width            
       1,                      // apply relu              
       0);                     // don't apply bias        
 
   conv2d_hw( 
       memory,                                    
       24664,                  // offset of input images  
       90,                     // offset of weights       
       0,                      // offset of biases        
       32504,                  // offset of output images 
       10,                     // number of input images  
       3,                      // number of output images 
       28,                     // height                  
       28,                     // width                   
       3,                      // kernel height           
       3,                      // kernel width            
       1,                      // apply relu              
       0);                     // don't apply bias        
 
   dense_hw( 
       memory,                                           
       32504,                  // offset of input images         
       360,                    // offset of weights              
       0,                      // offset of biases               
       34856,                  // offset of output images        
       1,                      // number of rows in input images 
       2352,                   // number of cols in input images 
       10,                     // number of output images        
       0,                      // don't apply relu        
       0);                     // don't apply_bias        
 
   float softmax_in[10];                        
   float softmax_out[10];                       
 
   copy_from_cat(memory, softmax_in, 34856, 10); 
 
   softmax(softmax_in, softmax_out, 10);         
 
   memcpy(probabilities, softmax_out, 10 * sizeof(float)); 
} 
 
