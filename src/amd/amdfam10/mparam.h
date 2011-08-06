/* Generated by MPFR's tuneup.c, 2011-07-31, gcc 4.6.1 */
/* contributed by Jim Cloos <cloos at jhcloos dot com> with GMP 5.0.2 on a
   "2009 or 2010 vintage phenom-II", where __amd64, __amd64__,
   __k8, __k8__, __x86_64 and __x86_64__ are also defined.
*/


#define MPFR_MULHIGH_TAB  \
 -1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,8,9,10,11, \
 12,12,12,14,14,14,16,16,18,18,19,20,18,22,20,20, \
 20,20,20,20,22,22,22,24,28,28,28,28,28,28,32,32, \
 30,32,32,32,32,32,32,38,38,38,38,40,40,40,40,40, \
 40,40,44,44,48,48,44,46,48,48,56,56,56,56,56,56, \
 56,56,56,60,64,60,64,64,64,64,64,64,64,64,64,64, \
 60,64,64,72,64,64,72,72,64,64,64,72,80,72,80,76, \
 76,80,76,80,80,80,80,76,80,79,80,80,80,80,80,80, \
 81,80,86,93,90,87,93,93,93,93,92,93,93,92,93,92, \
 93,93,93,93,102,105,105,104,105,105,105,105,105,105,111,116, \
 111,110,111,117,117,111,114,116,117,117,117,117,117,116,116,117, \
 116,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117, \
 117,117,117,117,117,117,117,117,117,148,148,156,148,148,148,148, \
 148,156,156,156,155,156,156,156,156,156,156,156,156,156,155,156, \
 156,156,156,156,172,156,172,172,172,156,172,156,172,172,172,172, \
 172,172,172,172,172,172,172,180,172,180,172,172,172,188,188,172, \
 188,188,188,188,188,188,179,188,188,188,188,188,188,188,188,188, \
 188,220,220,220,220,188,220,220,220,220,220,220,220,220,220,220, \
 220,220,220,220,220,220,220,220,220,220,220,220,220,219,220,220, \
 220,220,220,220,236,220,220,220,252,252,236,252,252,252,252,236, \
 236,236,252,236,252,252,236,252,236,252,252,252,252,251,250,252, \
 252,252,252,252,252,252,252,252,252,252,252,252,251,252,252,251, \
 252,252,252,252,252,252,252,252,252,252,252,252,252,252,284,284, \
 252,284,284,284,284,284,284,284,284,284,284,284,284,284,283,284, \
 284,283,284,284,300,300,300,284,284,300,284,284,298,300,316,316, \
 300,284,300,316,300,316,300,284,316,316,316,316,300,316,300,316, \
 316,300,316,300,316,316,315,316,316,316,316,316,316,316,316,316, \
 316,316,316,316,313,316,316,316,316,316,316,316,320,316,320,368, \
 316,316,316,368,368,368,367,368,368,368,368,368,368,368,368,368, \
 367,367,368,368,368,368,368,368,368,368,368,368,368,368,368,368, \
 368,368,368,366,368,368,367,368,368,367,368,368,368,368,368,368, \
 367,366,367,368,368,367,368,368,368,368,368,368,368,368,368,368, \
 368,368,368,368,368,368,368,368,416,368,368,368,368,368,368,416, \
 368,416,415,416,416,368,416,416,416,415,415,416,416,416,416,416, \
 416,416,415,416,416,415,416,416,440,416,415,416,416,415,416,415, \
 416,416,416,474,415,416,416,415,416,416,416,416,416,416,474,474, \
 488,474,440,440,488,488,504,473,504,474,504,504,503,503,503,503, \
 503,504,501,504,504,503,474,474,503,504,504,503,504,488,488,488, \
 503,503,504,504,504,504,504,504,501,503,504,503,504,504,499,504, \
 504,503,504,504,504,504,503,504,504,504,488,504,504,504,474,504, \
 501,504,504,501,504,503,504,504,504,504,504,504,504,504,503,504, \
 504,503,504,504,504,504,504,504,504,504,504,504,504,504,504,504, \
 504,504,504,504,504,504,503,568,568,568,504,504,504,504,568,504, \
 568,567,568,568,568,568,567,568,567,568,567,600,568,600,568,568, \
 568,568,568,567,568,568,568,568,568,568,568,568,568,568,568,568, \
 568,568,568,568,568,568,568,567,568,568,568,568,568,568,568,568, \
 568,568,568,632,600,568,568,568,565,568,568,568,632,568,568,600, \
 600,631,600,632,600,632,632,600,600,632,600,600,632,600,600,600, \
 632,616,600,632,600,632,632,600,600,600,600,600,600,632,600,632, \
 632,616,632,632,632,616,632,632,632,627,631,629,632,632,631,632, \
 632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632, \
 632,632,632,632,687,629,688,632,632,632,632,632,632,632,632,632, \
 688,712,632,688,712,688,712,712,688,688,688,711,712,712,680,736, \
 712,712,712,688,688,712,712,712,712,712,712,728,712,736,736,711, \
 733,736,735,711,728,728,736,728,712,736,736,710,734,736,736,712, \
 712,736,712,712,719,728,712,712,712,734,733,726,736,736,736,735, \
 736,736,736,712,736,736,736,736,736,736,727,736,736,736,735,736, \
 731,736,736,736,736,736,736,736,733,712,736,736,736,736,736,712, \
 712,736,736,784,712,712,736,725,760,760,736,727,736,830,736,784, \
 728,736,727,783,832,736,734,830,736,736,831,736,736,830,829,832, \
 832,832,831,736,782,784,832,828,736,824,736,832,832,831,736,824, \
 824,832,832,832,832,832,832,825,832,832,832,824,832,832,832,828, \
 822,824,831,829,832,827,832,832,832,831,832,829,829,832,824,832, \
 830,832,832,832,832,832,830,832,832,832,832,828,855,832,830,830 \
  
#define MPFR_SQRHIGH_TAB  \
 -1,0,0,0,-1,-1,-1,-1,-1,-1,7,8,9,8,9,9, \
 11,11,11,13,13,14,15,16,17,17,19,19,16,19,17,19, \
 19,18,19,19,21,21,21,23,23,25,25,23,25,25,25,25, \
 28,27,27,29,29,28,31,31,34,34,34,34,38,36,38,38, \
 42,42,42,42,42,42,44,46,42,46,44,50,46,50,42,50, \
 44,44,46,50,50,50,50,50,50,50,50,50,50,50,50,50, \
 52,50,54,54,54,54,56,56,56,56,58,56,56,58,58,60, \
 60,62,62,67,62,68,72,68,68,72,68,76,72,72,72,76, \
 76,76,76,76,84,72,84,76,76,76,84,76,76,84,84,84, \
 92,84,84,84,84,84,92,92,92,92,92,92,92,92,92,100, \
 92,92,100,100,92,100,100,100,100,100,100,92,100,100,92,100, \
 100,100,92,92,100,92,100,104,100,108,100,100,100,108,104,100, \
 100,104,100,108,108,108,112,108,112,112,112,123,112,123,112,135, \
 116,123,123,135,123,135,135,135,135,135,135,135,135,135,135,135, \
 135,135,147,135,135,135,135,147,147,147,147,147,147,147,147,147, \
 147,147,147,147,147,147,147,147,147,147,147,159,147,147,147,147, \
 165,147,147,159,153,147,147,147,165,159,147,147,165,153,147,159, \
 165,165,165,165,165,171,171,159,165,159,165,165,165,165,165,165, \
 171,165,171,171,165,177,171,171,189,183,171,165,165,165,183,165, \
 165,165,183,183,186,189,165,189,165,171,165,165,189,165,183,183, \
 183,189,183,201,201,189,189,183,189,183,195,189,189,189,183,213, \
 183,183,195,195,213,189,189,189,201,201,189,195,213,225,225,201, \
 201,213,213,195,213,201,225,225,225,225,225,224,225,225,213,225, \
 225,225,225,225,225,225,225,225,225,225,225,225,225,225,249,225, \
 249,249,248,225,249,249,249,249,249,249,225,249,249,248,249,249, \
 249,249,249,248,249,249,249,249,249,249,249,249,249,249,249,249, \
 249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249, \
 273,273,273,273,273,273,273,273,273,273,273,273,273,273,273,273, \
 273,273,273,273,273,273,273,273,273,273,297,297,297,297,297,296, \
 297,297,297,297,297,297,297,297,297,297,297,297,297,297,297,297, \
 297,297,297,297,297,297,297,297,297,273,273,273,273,273,273,296, \
 273,309,297,321,321,297,297,297,297,297,297,296,297,297,297,296, \
 297,296,297,297,297,297,297,297,297,297,297,297,297,297,309,297, \
 297,297,309,297,297,297,297,297,297,297,321,297,321,333,297,366, \
 333,333,333,366,333,296,333,333,333,297,333,333,333,297,297,321, \
 321,345,402,345,402,402,402,402,402,402,402,402,402,402,402,402, \
 401,401,402,402,402,402,402,402,402,402,402,402,401,402,402,401, \
 402,402,402,402,401,402,402,402,402,402,401,402,402,401,401,402, \
 401,401,393,402,402,438,401,402,402,401,401,402,401,402,402,402, \
 402,401,402,402,402,402,402,402,402,402,402,401,402,401,402,401, \
 402,402,400,402,402,402,402,402,402,402,438,438,438,438,438,438, \
 438,438,402,438,402,402,402,402,438,438,402,438,401,402,438,438, \
 438,438,438,438,438,438,401,437,438,402,401,402,438,401,402,402, \
 402,402,402,402,401,437,438,438,438,437,438,438,401,402,402,438, \
 438,438,402,402,402,402,401,402,402,437,438,438,438,438,438,438, \
 438,438,438,438,437,437,438,438,438,438,438,438,438,437,437,438, \
 437,438,438,438,438,402,438,402,438,438,438,438,438,438,437,438, \
 456,438,438,438,438,437,438,438,438,438,437,438,438,438,437,438, \
 438,438,438,473,437,456,438,438,438,438,438,437,438,438,438,438, \
 438,438,437,438,438,438,438,438,456,474,455,456,456,474,473,492, \
 456,474,456,474,474,474,474,474,536,512,474,512,474,536,474,474, \
 536,474,536,536,474,474,536,536,536,536,536,536,536,536,536,536, \
 536,534,536,536,536,535,536,536,536,536,535,536,536,536,536,536, \
 536,535,536,535,536,536,512,536,536,536,536,536,536,535,536,534, \
 535,584,536,536,536,534,535,536,536,536,536,536,536,536,536,534, \
 536,536,536,536,535,536,584,535,536,584,536,536,536,536,584,584, \
 584,584,536,584,584,584,584,584,584,584,583,584,582,584,584,584, \
 584,584,584,584,584,582,583,584,584,584,584,584,584,584,584,584, \
 584,583,584,584,696,584,584,583,584,584,696,726,696,584,584,584, \
 728,696,696,696,584,728,696,584,696,696,694,696,696,696,727,584, \
 695,694,584,696,696,695,728,696,696,696,696,696,694,696,727,695, \
 696,695,695,696,696,728,696,696,695,696,696,696,696,696,696,696, \
 727,696,696,696,696,695,696,728,727,696,695,727,696,726,727,726, \
 727,728,728,727,694,727,728,728,728,727,727,728,727,728,727,728 \
  
#define MPFR_DIVHIGH_TAB  \
 0,1,2,3,4,5,6,7,8,9,10,11,10,13,14,15, \
 14,15,18,19,18,14,15,18,18,18,19,17,18,19,18,19, \
 22,21,23,21,22,22,23,25,26,27,26,27,27,27,30,30, \
 30,34,30,34,32,33,34,31,30,34,37,34,38,38,38,38, \
 38,38,42,43,42,42,39,38,42,44,43,42,40,45,46,46, \
 46,45,46,43,44,50,48,48,48,46,53,51,50,50,50,50, \
 53,51,53,53,53,53,55,55,55,55,55,55,60,64,60,60, \
 62,63,64,65,60,64,68,72,64,68,68,64,64,68,72,66, \
 67,69,71,72,76,80,71,72,76,74,74,76,76,77,76,80, \
 79,84,84,84,78,84,88,88,92,84,80,92,92,80,88,84, \
 92,88,91,92,92,92,93,95,92,90,92,92,92,92,92,96, \
 96,96,92,92,92,92,96,96,102,96,95,110,96,96,100,100, \
 112,100,100,106,106,110,112,110,110,111,110,120,110,110,112,120, \
 110,120,120,120,112,120,128,128,128,128,124,128,128,120,128,128, \
 127,128,124,128,128,128,128,126,128,128,128,128,136,140,128,128, \
 128,128,136,144,128,128,144,144,128,144,144,144,144,128,152,152, \
 152,152,152,160,160,152,144,144,152,151,144,143,152,144,144,152, \
 152,144,152,152,152,152,151,152,160,158,144,160,160,160,160,160, \
 152,160,152,152,152,160,152,160,160,156,158,160,160,160,160,160, \
 160,160,160,160,168,160,160,160,160,160,159,160,160,160,176,176, \
 180,176,176,184,184,186,184,184,184,184,186,184,186,172,176,192, \
 184,184,184,184,185,176,176,185,184,185,186,183,184,184,181,191, \
 192,184,184,185,192,192,192,186,192,192,192,192,192,191,196,192, \
 192,192,192,192,196,190,192,192,200,192,198,220,222,204,200,222, \
 220,220,222,222,224,222,222,219,222,222,224,224,220,222,220,224, \
 220,221,222,220,232,222,221,232,222,220,224,232,220,232,222,232, \
 224,220,220,222,222,222,221,222,220,220,222,222,224,224,224,222, \
 220,224,224,232,224,222,222,232,224,222,223,224,224,224,231,232, \
 256,232,231,232,239,232,239,234,238,238,239,232,239,232,256,256, \
 288,288,248,256,256,256,256,256,256,239,255,256,256,256,256,256, \
 256,256,256,256,256,256,296,256,254,256,256,272,272,272,256,256, \
 288,272,256,256,280,296,288,280,288,288,296,280,288,288,288,294, \
 296,296,294,304,288,287,288,296,304,304,288,303,304,296,288,312, \
 312,312,312,288,288,312,288,288,312,320,305,288,320,320,288,312, \
 311,312,312,312,304,304,312,304,319,296,288,310,312,288,288,320, \
 304,304,304,288,300,312,309,304,304,311,288,296,296,320,312,311, \
 296,320,312,304,304,312,312,320,296,320,312,296,305,312,304,303, \
 304,312,303,312,304,311,312,312,320,312,311,320,320,320,320,320, \
 312,320,312,312,312,320,312,312,320,320,319,320,320,320,320,320, \
 320,320,320,320,320,320,320,320,320,320,320,320,320,320,352,336, \
 344,352,352,344,360,360,343,336,352,366,370,352,360,368,376,360, \
 360,360,367,368,360,352,371,360,368,368,372,352,352,352,352,352, \
 384,370,360,368,384,372,375,360,368,368,368,368,368,368,384,372, \
 352,372,352,368,366,376,352,367,384,368,360,368,360,384,371,376, \
 360,366,368,368,360,369,371,367,368,369,384,376,368,372,372,384, \
 440,368,376,384,372,376,440,440,376,440,368,369,384,370,440,440, \
 440,392,440,440,384,384,440,440,448,440,440,440,440,440,440,440, \
 440,440,384,440,439,440,384,384,440,440,440,440,440,440,439,448, \
 440,440,440,440,440,440,440,440,440,440,440,440,440,440,440,440, \
 440,440,440,440,440,440,439,440,440,440,440,440,440,440,440,440, \
 440,440,440,440,440,440,440,440,440,440,440,440,440,440,440,480, \
 440,440,440,440,468,480,440,440,440,440,440,464,440,440,440,440, \
 480,440,440,440,440,448,439,440,440,440,440,440,440,448,440,448, \
 512,439,440,448,440,440,440,438,440,440,440,440,496,440,465,440, \
 440,466,440,440,440,440,512,440,440,440,440,464,440,440,448,466, \
 512,496,512,512,512,448,512,447,448,468,472,448,480,464,480,512, \
 466,466,496,468,512,468,496,480,512,512,496,467,472,512,512,512, \
 512,468,512,512,512,512,512,478,512,472,512,512,512,496,512,512, \
 512,512,512,512,496,480,496,496,512,512,512,496,480,512,544,480, \
 576,512,512,576,512,512,512,576,512,512,496,496,512,480,576,576, \
 512,510,496,568,576,576,496,560,576,511,512,576,576,512,512,576, \
 560,496,576,512,512,512,512,512,512,576,576,512,512,576,512,512, \
 512,512,576,512,512,512,508,512,576,512,576,576,512,576,592,512, \
 568,512,576,568,576,576,576,512,576,576,592,576,592,512,608,576 \
  
#define MPFR_MUL_THRESHOLD 17 /* limbs */
#define MPFR_SQR_THRESHOLD 19 /* limbs */
#define MPFR_DIV_THRESHOLD 28 /* limbs */
#define MPFR_EXP_2_THRESHOLD 1031 /* bits */
#define MPFR_EXP_THRESHOLD 10625 /* bits */
#define MPFR_SINCOS_THRESHOLD 26682 /* bits */
#define MPFR_AI_THRESHOLD1 -11328 /* threshold for negative input of mpfr_ai */
#define MPFR_AI_THRESHOLD2 1045
#define MPFR_AI_THRESHOLD3 17871
/* Tuneup completed successfully, took 562 seconds */
