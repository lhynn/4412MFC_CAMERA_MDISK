#ifndef MFC_H
#define MFC_H

#include "SsbSipMfcApi.h"
unsigned char header[100];
int headerSize;
void *hOpen;
SSBSIP_MFC_ENC_H264_PARAM *enc_param;
SSBSIP_MFC_ENC_INPUT_INFO input_info_enc;
SSBSIP_MFC_ENC_OUTPUT_INFO output_info_enc;	
int enc_width, enc_height;
SSBSIP_MFC_CODEC_TYPE codec_type;


SSBSIP_MFC_ERROR_CODE initMFC_ENC(int w, int h, int qb);
int getHeader(unsigned char** p);
void getInputBuf(void **Y,void **UV);
int encode(void *input_buf,void **output_buf);
void closeMFC();

#endif // MFC_H
