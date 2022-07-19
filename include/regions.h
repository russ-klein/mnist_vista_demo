#ifndef REGIONS_H_INCLUDED 
#define REGIONS_H_INCLUDED 


static unsigned int region_map[][2] = { 
  {          0,        375 },  // conv2d weights 
  {        375,         15 },  // conv2d biases 
  {        390,       2025 },  // conv2d_1 weights 
  {       2415,         15 },  // conv2d_1 biases 
  {       2430,      14700 },  // dense weights 
  {      17130,         20 },  // dense biases 
  {      17150,        200 },  // dense_1 weights 
  {      17350,         10 },  // dense_1 biases 
  {      17360,        784 },  // input_image 
  {      18144,       2940 },  // conv2d outputs 
  {      21084,        735 },  // conv2d_1 outputs 
  {      21819,         20 },  // dense outputs 
  {      21839,         10 },  // dense_1 outputs 
  {      21849, 4294967295 }   // out of bounds 
}; 
 
 
static char region_names[][40] = { 
  { "conv2d weights" }, 
  { "conv2d biases " }, 
  { "conv2d_1 weights" }, 
  { "conv2d_1 biases " }, 
  { "dense weights" }, 
  { "dense biases " }, 
  { "dense_1 weights" }, 
  { "dense_1 biases " }, 
  { "input image " }, 
  { "conv2d outputs " }, 
  { "conv2d_1 outputs " }, 
  { "dense outputs " }, 
  { "dense_1 outputs " }, 
  { "out of bounds " } 
}; 

#endif 
