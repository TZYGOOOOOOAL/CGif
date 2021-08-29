#include <stdio.h>
#include <string.h>
#include "include/cgif_read.h"


status_t read_gif(int8_t* gif_path, CGif* p_cgif)
{
	printf("Read gif file from %s\r\n", gif_path);
	FILE* fp = NULL;
	fp = fopen(gif_path, "rb");

	if (fp == NULL)
		RETURN_ERROR_WITH_INFO("Open file failed !!!");

	/**** READ GIF HEAD ****/
	// gif format tag
	uint8_t gif_tag[CGIF_HEAD_TAG_LEN] = {0};
	fread(gif_tag, 1, CGIF_HEAD_TAG_LEN, fp);
	if (!memcmp(gif_tag, CGIF_TAG_87a, CGIF_HEAD_TAG_LEN))		// fmt is GIF87a	
		p_cgif->gif_fmt = CGIF_87a;
	else if (!memcmp(gif_tag, CGIF_TAG_89a, CGIF_HEAD_TAG_LEN))	// fmt is GIF89a
		p_cgif->gif_fmt = CGIF_89a;
	else
		RETURN_ERROR_WITH_INFO("Unknown gif format !!!");

	// screen height and width
	/*相当于画布大小，与实际图像尺寸无关，
	测试发现若大于图像会出现黑边，若小于不影响*/
	fread(&(p_cgif->screen_width), 2, 1, fp);		
	fread(&(p_cgif->screen_height), 2, 1, fp);

	// global colortable info 
	uint8_t gct_info;
	fread(&gct_info, 1, 1, fp);
	convert_gct_info(gct_info, &(p_cgif->GCT));

	// background color index
	fread(&(p_cgif->bkg_color_idx), 1, 1, fp);

	// aspect ratio  测试发现只影响缩略图显示，不影响实际显示
	fread(&(p_cgif->aspect_ratio), 1, 1, fp);

	// global colortable data
	p_cgif->GCT.data = (uint8_t*)malloc(p_cgif->GCT.table_len);
	fread(p_cgif->GCT.data, 1, p_cgif->GCT.table_len, fp);

	return STA_OK;
}


static status_t convert_gct_info(uint8_t gct_info, ColorTable* p_ct)
{
	/*
	Global Color Table Flag       1 Bit
	Color Resolution              3 Bits	// 一般无用
	Sort Flag                     1 Bit
	Size of Global Color Table    3 Bits
	*/
	p_ct->enable = ((gct_info & 0x80)>>7);
	p_ct->sorted = ((gct_info & 0x08)>>4);
	uint16_t size_info = gct_info & 0x07;
	p_ct->pixel_size = size_info + 1;
	p_ct->color_num = (1 << p_ct->pixel_size);
	p_ct->table_len = p_ct->color_num * 3;		// 表长 rgb三字节*颜色数
	p_ct->interlaced = 0;
	p_ct->data = NULL;
	return STA_OK;
}