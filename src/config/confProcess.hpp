#include "conf.hpp"

#define frametime 1000000 / target_fps

#define xcellsize screen_size_x / x_size
#define ycellsize screen_size_y / y_size
#if ycellsize > xcellsize
    #define cellsize xcellsize
#else
    #define cellsize ycellsize
#endif
/*
#undef xcellsize
#undef ycellsize
*/

#define cell_count x_size * y_size
