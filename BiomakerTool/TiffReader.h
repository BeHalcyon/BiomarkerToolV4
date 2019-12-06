#pragma once
#include <QString>
#include <tiffio.h>
#include <iostream>
#include <QImage>

class TiffReader
{
public:
	TiffReader(QString filename);
	~TiffReader();
	uint32* getRawData();
	uint32 getWidth();
	uint32 getHeight();
	uint32* getNavigationData(float navigationWidth, float navigationHeight, int xblocklen, int yblocklen);
	void saveTiffFile(const QString& file_name, uint32* image_data);
	uint32* getLocalImage(QPointF startPoint, int sceneHeight, int sceneWidth);
	uint32* getGlobalGraphicsImage();
	uint32* getGlobalGraphicsImage(int sceneHeight, int sceneWidth);
	//Debug 20190728
	double getGlobalFactor() const { return global_factor; }

	
	double getGlobalWidthFactor() const { return global_width_factor; }
	
	double getGlobalHeightFactor() const { return global_height_factor; }
private:
	TIFF* tif;
	uint32 imageWidth, imageLength, TileWidth, TileLength, imageRowsPerStrip;
	uint16 imageCompression, imageSamplePerPixel;
	uint16 imagePlanarConfig, imagePhotoMetric, ResolutUnit, Orientation;
	uint16 bps;
	float X_Resolut, Y_Resolut;
	unsigned char *buf;
	tstrip_t strip;
	uint32* raster;
	uint32* navigationData;
	uint32* imageData;
	uint32* global_graphics_data;
	int stripnumber;
	long long stripeSize;
	//Debug 20190728
	double global_factor;
	double global_width_factor; double global_height_factor;
};

