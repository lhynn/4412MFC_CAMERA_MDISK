#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include "camera.h"
#include "mfc.h"
#define DEV_NAME_LENGTH         50
#define NUM_FRAM                200

int main() {
	char *dev_name = NULL;
	FILE *outf = 0;
	unsigned int image_size;
	int ouput_buf_size;
	int i;
	void *ouput_buf;

	int camera_type = 0;//0:ITU, 1:UVC  
	int width=544;
	int height=480;

	dev_name = (char *)malloc(sizeof(char) * DEV_NAME_LENGTH);
	if(!dev_name)
	{
		printf("malloc mem error\n");
		return -1;
	}
	memset(dev_name, 0, sizeof(char) * DEV_NAME_LENGTH);
	strcpy(dev_name,"/dev/video0");
	outf = fopen("out.h264", "wb");
	unsigned char image[width*height*2];
	clock_t starttime, endtime;
	double totaltime;
	unsigned int writesize=0;
	Camera(dev_name,width,height, camera_type);
	if(!OpenDevice()){
		printf("OpenDevice failed\n");
		return -1;
	}
	image_size= getImageSize();
	starttime = clock();
	//int frames=50;
	writesize=0;
	//--------------------------MFC---------------------------------------//
	SSBSIP_MFC_ERROR_CODE ret;
	unsigned char *header;

	ret=initMFC_ENC(width,height,28);
	if(ret<0){
		printf("init mfc failed !!\n");
	}
	      int headerSize=getHeader(&header);
	      fwrite(header,1,headerSize,outf);
	for( i=0;i< NUM_FRAM;i++){
		if(!GetBuffer(image)){  //NV12
			printf("fun:%s, line = %d\n", __FUNCTION__, __LINE__);
			break;
		}
		      ouput_buf_size=encode(image,&ouput_buf);                

		      writesize=fwrite(ouput_buf,1, ouput_buf_size,outf);
		//writesize=fwrite(image,1, image_size,outf);

		//fflush(outf);
		printf("frame:%d,writesize:%d\n",i,writesize);
	}

	endtime = clock();
	totaltime = (double)( (endtime - starttime)/(double)CLOCKS_PER_SEC );
	printf("time :%f, rate :%f\n",totaltime,NUM_FRAM/totaltime);
	CloseDevice();
	fclose(outf);
	return 0;
}



