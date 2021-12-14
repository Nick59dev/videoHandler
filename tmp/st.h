#ifndef ST_H00
#define ST_H00


typedef struct __attribute__((__packed__)){
	unsigned char fMar1;
	unsigned char fMar2; 
	unsigned int bfSize;
  uint16_t unused1;
	uint16_t unused2;
	unsigned int imageDataOffset;
} FHDER;

typedef struct __attribute__((__packed__)) {
	unsigned int bSize;
	int width;
	int height;
	uint16_t planes;
	uint16_t bitPix;
	unsigned int Compression;
	unsigned int bSizeImage;
	int piXPerMeter;
	int piYPerMeter;
	unsigned int Used;
	unsigned int Importannt;
} INFO;

typedef struct __attribute__((__packed__)){
	unsigned char b;
	unsigned char g;
	unsigned char r;
} IMAGE;


#endif
