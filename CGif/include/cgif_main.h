#ifndef __CGIF_MAIN_H__
#define __CGIF_MAIN_H__

#include <stdlib.h>

// type
typedef unsigned char	uint8_t;
typedef char			int8_t;
typedef short			int16_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;
typedef int				int32_t;
typedef long long		int64_t;
typedef unsigned long long uint64_t;

// return status ����״̬
typedef enum 
{
	STA_OK = 0,
	STA_ERROR
} status_t;


// gif format struct
#define CGIF_HEAD_TAG_LEN 6
#define CGIF_TAG_87a "GIF87a"
#define CGIF_TAG_89a "GIF89a"
typedef enum gif_fmt_tt
{
	CGIF_87a = 0,
	CGIF_89a
} gif_fmt_t;

typedef struct
{
	uint8_t  enable;		// �Ƿ���Ч
	uint16_t color_num;		// ����ʾ��ɫ����
	uint16_t table_len;		// �����ֽ�����
	uint16_t pixel_size;	// ÿ����������������
	uint8_t  sorted;		// �Ƿ�Ƶ����������
	uint8_t  interlaced;	// �Ų���ʽ�Ƿ�Ϊ����
	uint8_t* data;			// ������
} ColorTable;

typedef struct
{
	gif_fmt_t  gif_fmt;
	uint16_t   screen_width;
	uint16_t   screen_height;
	ColorTable GCT;				// global color table
	uint8_t    bkg_color_idx;	// background color index
	uint8_t    aspect_ratio;
	uint8_t* data;
} CGif;



//typedef struct GifHead_t
//{
//	gif_fmt_t  gif_fmt;		
//	uint16_t screen_width;
//	uint16_t screen_height;
//	uint8_t  GCT_info;			
//	uint8_t  background_color;
//	uint8_t  aspect_ratio;
//}GifHead;


// 
#define RETURN_ERROR_WITH_INFO(info) do{ \
		printf("ERROR: %s,line %d : %s\r\n", __FILE__, __LINE__, info);	\
		return STA_ERROR;                \
	}while (0)

#endif