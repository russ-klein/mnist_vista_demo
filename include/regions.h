#ifndef REGIONS_H_INCLUDED 
#define REGIONS_H_INCLUDED 


static unsigned int region_map[][2] = { 
  {          0,         36 },  // conv2d weights 
  {         36,          4 },  // conv2d biases 
  {         40,       7840 },  // dense weights 
  {       7880,         10 },  // dense biases 
  {       7890,        784 },  // input_image 
  {       8674,        784 },  // conv2d outputs 
  {       9458,         10 },  // dense outputs 
  {       9468, 4294967295 }   // out of bounds 
}; 
 
 
static char region_names[][40] = { 
  { "conv2d weights" }, 
  { "conv2d biases " }, 
  { "dense weights" }, 
  { "dense biases " }, 
  { "input image " }, 
  { "conv2d outputs " }, 
  { "dense outputs " }, 
  { "out of bounds " } 
}; 

#endif 
