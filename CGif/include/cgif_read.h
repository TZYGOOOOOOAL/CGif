#ifndef __CGIF_READ_H__
#define __CGIF_READ_H__

#include "cgif_main.h"

status_t read_gif(int8_t* gif_path, CGif* p_cgif);
static status_t convert_gct_info(uint8_t gct_info, ColorTable* p_ct);

#endif
