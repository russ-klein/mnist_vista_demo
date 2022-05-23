#ifndef WEIGHTS_H_INCLUDED 
#define WEIGHTS_H_INCLUDED 


      
   //=======layer 1 - convolution===============================   
      
   static const int layer1_input_images       = 1;  
   static const int layer1_output_images      = 10;  
   static const int layer1_weights_rows       = 3;  
   static const int layer1_weights_cols       = 3;  
      
   static const int layer1_num_weights        = 90;  
      
   static const int layer1_weight_offset      = 0;  
   static const int layer1_out_size           = 7840;  
      
      
   //=======layer 2 - convolution===============================   
      
   static const int layer2_input_images       = 10;  
   static const int layer2_output_images      = 3;  
   static const int layer2_weights_rows       = 3;  
   static const int layer2_weights_cols       = 3;  
      
   static const int layer2_num_weights        = 270;  
      
   static const int layer2_weight_offset      = 90;  
   static const int layer2_out_size           = 2352;  
      
      
   //=======layer 3 - dense=====================================   
      
   static const int layer3_weights_rows       = 10; 
   static const int layer3_weights_cols       = 2352; 
      
   static const int layer3_num_weights        = 23520;  
      
   static const int layer3_weight_offset      = 360;  
   static const int layer3_out_size           = 10;  
      
      
 
   //=======End of layers==========================================   
 
 
   static int const image_height              = 28; 
   static int const image_width               = 28; 
   static int const image_size                = 784; 
   static int const num_images                = 1; 
 
   static int const size_of_weights           = 23880; 
   static int const size_of_outputs           = 34866; 
 
 
#endif 
 
