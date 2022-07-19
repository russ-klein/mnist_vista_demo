#ifndef WEIGHTS_H_INCLUDED 
#define WEIGHTS_H_INCLUDED 


      
   //=======layer 1 - convolution===============================   
      
   static const int layer1_input_images       = 1;  
   static const int layer1_output_images      = 15;  
   static const int layer1_weights_rows       = 5;  
   static const int layer1_weights_cols       = 5;  
      
   static const int layer1_num_weights        = 375;  
      
   static const int layer1_weight_offset      = 0;  
   static const int layer1_out_size           = 2940;  
      
      
   static const int layer1_num_bias_values    = 15;  
   static const int layer1_bias_offset        = 375;  
      
      
      
   //=======layer 2 - convolution===============================   
      
   static const int layer2_input_images       = 15;  
   static const int layer2_output_images      = 15;  
   static const int layer2_weights_rows       = 3;  
   static const int layer2_weights_cols       = 3;  
      
   static const int layer2_num_weights        = 2025;  
      
   static const int layer2_weight_offset      = 390;  
   static const int layer2_out_size           = 735;  
      
      
   static const int layer2_num_bias_values    = 15;  
   static const int layer2_bias_offset        = 2415;  
      
      
      
   //=======layer 3 - dense=====================================   
      
   static const int layer3_weights_rows       = 20; 
   static const int layer3_weights_cols       = 735; 
      
   static const int layer3_num_weights        = 14700;  
      
   static const int layer3_weight_offset      = 2430;  
   static const int layer3_out_size           = 20;  
      
      
      
   static const int layer3_num_bias_values    = 20;  
   static const int layer3_bias_offset        = 17130;  
      
      
      
   //=======layer 4 - dense=====================================   
      
   static const int layer4_weights_rows       = 10; 
   static const int layer4_weights_cols       = 20; 
      
   static const int layer4_num_weights        = 200;  
      
   static const int layer4_weight_offset      = 17150;  
   static const int layer4_out_size           = 10;  
      
      
      
   static const int layer4_num_bias_values    = 10;  
   static const int layer4_bias_offset        = 17350;  
      
      
 
   //=======End of layers==========================================   
 
 
   static int const image_height              = 28; 
   static int const image_width               = 28; 
   static int const image_size                = 784; 
   static int const num_images                = 1; 
 
   static int const size_of_weights           = 17360; 
   static int const size_of_outputs           = 21849; 
 
 
#endif 
 
