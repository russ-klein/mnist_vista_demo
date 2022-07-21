#ifndef WEIGHTS_H_INCLUDED 
#define WEIGHTS_H_INCLUDED 


      
   //=======layer 1 - convolution===============================   
      
   static const int layer1_input_images       = 1;  
   static const int layer1_output_images      = 4;  
   static const int layer1_weights_rows       = 3;  
   static const int layer1_weights_cols       = 3;  
      
   static const int layer1_num_weights        = 36;  
      
   static const int layer1_weight_offset      = 0;  
   static const int layer1_out_size           = 784;  
      
      
   static const int layer1_num_bias_values    = 4;  
   static const int layer1_bias_offset        = 36;  
      
      
      
   //=======layer 2 - dense=====================================   
      
   static const int layer2_weights_rows       = 10; 
   static const int layer2_weights_cols       = 784; 
      
   static const int layer2_num_weights        = 7840;  
      
   static const int layer2_weight_offset      = 40;  
   static const int layer2_out_size           = 10;  
      
      
      
   static const int layer2_num_bias_values    = 10;  
   static const int layer2_bias_offset        = 7880;  
      
      
 
   //=======End of layers==========================================   
 
 
   static int const image_height              = 28; 
   static int const image_width               = 28; 
   static int const image_size                = 784; 
   static int const num_images                = 1; 
 
   static int const size_of_weights           = 7890; 
   static int const size_of_outputs           = 9468; 
 
 
#endif 
 
