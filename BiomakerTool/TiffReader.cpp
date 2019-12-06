#include "TiffReader.h"
#include "tiffio.h"
#include "QDebug"

#include <stdio.h>
#include <string.h>


TiffReader::TiffReader(QString filename)
{
	tif = TIFFOpen(filename.toStdString().c_str(), "r");
	
	navigationData = nullptr;
	imageData = nullptr;
	if (tif) {
		TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &imageWidth);
		TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &imageLength);
		//qDebug() << "Image width and length" << imageWidth << imageLength;
		TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bps);
		TIFFGetField(tif, TIFFTAG_COMPRESSION, &imageCompression);
		TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &imagePhotoMetric);

		TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &imageSamplePerPixel);
		TIFFGetField(tif, TIFFTAG_ROWSPERSTRIP, &imageRowsPerStrip);
		if (imageRowsPerStrip != 1)
		{
			qDebug("Rows Each Strip Is Not 1!");
			//return;
		}

		TIFFGetField(tif, TIFFTAG_XRESOLUTION, &X_Resolut);
		TIFFGetField(tif, TIFFTAG_YRESOLUTION, &Y_Resolut);
		TIFFGetField(tif, TIFFTAG_RESOLUTIONUNIT, &ResolutUnit);

		TIFFGetField(tif, TIFFTAG_PLANARCONFIG, &imagePlanarConfig);
		TIFFGetField(tif, TIFFTAG_ORIENTATION, &Orientation);

		long long stripSize = TIFFStripSize(tif);
		long long StripsNumber = TIFFNumberOfStrips(tif);

		qDebug() << "Image width and length" << imageWidth << imageLength;
		qDebug() << "bps" << bps;
		qDebug() << "imageCompression" << imageCompression;
		qDebug() << "imagePhotoMetric" << imagePhotoMetric;
		qDebug() << "imageSamplePerPixel" << imageSamplePerPixel;
		qDebug() << "imageRowsPerStrip" << imageRowsPerStrip;
		qDebug() << "X_Resolut" << X_Resolut;
		qDebug() << "Y_Resolut" << Y_Resolut;
		qDebug() << "ResolutUnit" << ResolutUnit;
		qDebug() << "imagePlanarConfig" << imagePlanarConfig;
		qDebug() << "Orientation" << Orientation;
		qDebug() << "stripSize" << stripSize;
		qDebug() << "StripsNumber" << StripsNumber;



		raster = (uint32*)_TIFFmalloc(imageWidth*imageLength * sizeof(uint32)); // 分配适当格式的内存
		if (raster != NULL) {
			qDebug() << "Get image end.";
			//if (TIFFReadRGBAImage(tif, imageWidth, imageLength, raster, 0)) { // 读入图像数据
			//	qDebug() << "Get tiff image successfully.";
			//}
			//else {
			//	qDebug() << "Error: copy data";
			//}
			//_TIFFfree(raster); // 释放内存
		}
	}
	
}
TiffReader::~TiffReader() {
	//_TIFFfree(raster);
	//delete tif;
	TIFFClose(tif);
}
uint32* TiffReader::getRawData() {
	return this->raster;
}
uint32 TiffReader::getWidth() {
	return this->imageWidth;
}
uint32 TiffReader::getHeight() {
	return this->imageLength;
}
uint32* TiffReader::getLocalImage(QPointF startPoint, int sceneHeight, int sceneWidth) {

	if (imageData) {
		free(imageData);
	}
	imageData = (uint32*)malloc((int)sceneHeight*(int)sceneWidth* sizeof(uint32));

	//1. find the row range from start to end
	int realStartRow = 0, realEndRow = 0;
	startPoint.setY(imageLength - startPoint.y()- sceneHeight);
	//startPoint.setY(imageLength - startPoint.y());
	realStartRow = startPoint.y();
	realEndRow = startPoint.y() + sceneHeight;
	int realStripStart = realStartRow / imageRowsPerStrip;
	int realStripEnd = realEndRow / imageRowsPerStrip;

	int startStripRow = realStartRow%imageRowsPerStrip;
	int endStripRow = realEndRow%imageRowsPerStrip;

	//if (buf) {
	//	free(buf);
	//}

	

	int localStartRow = 0, localEndRow = 0;
	int curIndex = sceneHeight-1;
	for (strip = realStripStart; strip <= realStripEnd; strip++) {
		buf = (unsigned char *)malloc(stripeSize);
		TIFFReadEncodedStrip(tif, strip, buf, (tsize_t)-1);
		if (strip == realStripStart) {
			localStartRow = startStripRow;
		}
		else {
			localStartRow = 0;
		}
		if (strip == realStripEnd) {
			localEndRow = endStripRow;
		}
		else {
			localEndRow = imageRowsPerStrip-1;
		}
		for (int i = localStartRow; i <=localEndRow; i++) {
			if (curIndex < 0) {
				free(buf);
				return imageData;
			}
			for (int j = 0; j < sceneWidth; j++) {
				imageData[curIndex*sceneWidth + j] = 0xff000000;
				imageData[curIndex*sceneWidth + j] += (buf[3 * (i*imageWidth + (int)(startPoint.x()) + j)] & 0xff);
				imageData[curIndex*sceneWidth + j] += (buf[3 * (i*imageWidth + (int)(startPoint.x()) + j) + 1] & 0xff) << 8;
				imageData[curIndex*sceneWidth + j] += (buf[3 * (i*imageWidth + (int)(startPoint.x()) + j) + 2] & 0xff) << 16;
			}
			curIndex--;
		}
		free(buf);
	}
	
	return imageData;

}

uint32* TiffReader::getGlobalGraphicsImage()
{
	if(raster == NULL)
	{
		raster = (uint32*)_TIFFmalloc(imageWidth*imageLength * sizeof(uint32)); // 分配适当格式的内存
	}
	
	if (raster != NULL) {
		qDebug() << "Get image end.";
		if (TIFFReadRGBAImage(tif, imageWidth, imageLength, raster, 0)) { // 读入图像数据
			qDebug() << "Get tiff image successfully.";
		}
		else {
			qDebug() << "Error: copy data";
		}
		//_TIFFfree(raster); // 释放内存
	}
	return raster;
}

uint32* TiffReader::getGlobalGraphicsImage(int sceneHeight, int sceneWidth)
{
	global_graphics_data = (uint32*)malloc((int)sceneHeight*(int)sceneWidth* sizeof(uint32));

	stripeSize = TIFFStripSize(tif);
	buf = (unsigned char *)malloc(stripeSize);

	stripnumber = TIFFNumberOfStrips(tif);

	std::cout << "stripSize : " << TIFFStripSize(tif) << std::endl;
	std::cout << "strip number : " << stripnumber << std::endl;
	//Debug 20190727
	double xblocklen = imageWidth / sceneWidth;
	//global_factor = xblocklen;
	global_factor = (1.f*imageWidth) / (1.f*sceneWidth);
	global_height_factor = imageLength * 1.f / sceneHeight;
	global_width_factor = (1.f*imageWidth) / (1.f*sceneWidth);

	double yblocklen = imageLength / sceneHeight;

	xblocklen = global_width_factor;
	yblocklen = global_height_factor;

	qDebug() << "xblocklen and yblocklen: " << xblocklen << yblocklen<<" "<< global_width_factor <<" "<< global_height_factor;

	QVector<QVector<int>> sampleLine;
	sampleLine.resize(stripnumber);
	double cur = 0;
	int last = 0;
	for (int i = 0; i < sampleLine.size(); i++) {
		while (cur < imageRowsPerStrip) {
			sampleLine[i].push_back(static_cast<int>(cur));
			cur += yblocklen;
		}
		cur -= imageRowsPerStrip;
	}
	uint32* rowData = (uint32*)malloc(imageWidth* sizeof(uint32));
	int tempIndex = (int)sceneHeight - 1;
	// de-order
	for (strip = 0; strip < stripnumber; strip++) {
		if (sampleLine[strip].size() == 0) continue;
		TIFFReadEncodedStrip(tif, strip, buf, (tsize_t)-1);
		//find corresponding row and save
		for (int i = 0; i < sampleLine[strip].size(); i++) {
			if (tempIndex <= 0) break;
			int curCol = sampleLine[strip][i];

			for (int j = 0; j < imageWidth; j++) {
				rowData[j] = 0xff000000;
				rowData[j] += (buf[3 * (curCol*imageWidth + j)] & 0xff);
				rowData[j] += (buf[3 * (curCol*imageWidth + j) + 1] & 0xff) << 8;
				rowData[j] += (buf[3 * (curCol*imageWidth + j) + 2] & 0xff) << 16;
			}
			for (int j = 0; j < (int)sceneWidth; j++) {
				global_graphics_data[tempIndex*((int)sceneWidth) + j] = rowData[int(j*xblocklen)];
			}
			tempIndex--;
		}
	}
	sampleLine.clear();
	qDebug() << "index range is :" << tempIndex;
	free(buf);
	free(rowData);
	return global_graphics_data;
}

uint32* TiffReader::getNavigationData(float navigationWidth, float navigationHeight,int xblocklen, int yblocklen) {
	if (navigationData) {
		std::cout << "Navigation Image has been loaded." << std::endl;
		return navigationData;
	}

	navigationData = (uint32*)malloc((int)navigationWidth*(int)navigationHeight* sizeof(uint32));
	//_TIFFmemset(navigationData, 0xff000000, (int)navigationHeight*(int)navigationHeight* sizeof(uint32));
	//int xblocklen = imageWidth / navigationWidth;
	//int yblocklen = imageLength / navigationHeight;

	uint16 nsamples;
	TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &nsamples);

	uint32 tileWidth, tileLength;
	TIFFGetField(tif, TIFFTAG_TILEWIDTH, &tileWidth);
	TIFFGetField(tif, TIFFTAG_TILELENGTH, &tileLength);

	std::cout << "NSamlpes : " << nsamples << std::endl;
	std::cout << "TIFFScanlineSize : " << TIFFScanlineSize(tif) << std::endl;
	std::cout << "tileWidth and tileLength: " << tileWidth << " " << tileLength << std::endl;


	//uint32* rowPoint2Src = count + (height - 1)*width;
	stripeSize = TIFFStripSize(tif);
	buf = (unsigned char *)malloc(stripeSize);
	//uint32* pRow = navigationData;
	long long calcRow = 0;
	int tempRow = 0;



	tdata_t buf2;
	uint32 row;

	int config;
	TIFFGetField(tif, TIFFTAG_PLANARCONFIG, &config);

	std::cout << "TIFFTAG_PLANARCONFIG : " << config << std::endl;


	int tileSize = TIFFTileSize(tif);

	stripnumber = TIFFNumberOfStrips(tif);

	std::cout << "stripSize : " << TIFFStripSize(tif) << std::endl;
	std::cout << "strip number : " << stripnumber << std::endl;

	

	uint32* testData = (uint32*)malloc(imageWidth*imageRowsPerStrip* sizeof(uint32));
	
	int curIndex = 0;
	int lastCol = 0;
	qDebug() << "xblocklen and yblocklen: " << xblocklen << yblocklen;
	qDebug() << "navigationview width and height: " << navigationWidth << navigationHeight << (int)navigationWidth* (int)navigationHeight;

	QVector<QVector<int>> sampleLine;
	sampleLine.resize(stripnumber);
	int cur=0;
	int last = 0;
	for (int i = 0; i < sampleLine.size(); i++) {
		while (cur < imageRowsPerStrip) {
			sampleLine[i].push_back(cur);
			cur += yblocklen;
		}
		cur -= imageRowsPerStrip;
	}
	uint32* rowData = (uint32*)malloc(imageWidth* sizeof(uint32));
	int tempIndex = (int)navigationHeight-1;
	// de-order
	for (strip = 0; strip < stripnumber; strip++) {

		if (sampleLine[strip].size() == 0) continue;
		
		TIFFReadEncodedStrip(tif, strip, buf, (tsize_t)-1);

		//find corresponding row and save
		for (int i = 0; i < sampleLine[strip].size(); i++) {
			if (tempIndex <=0) break;
			int curCol = sampleLine[strip][i];

			for (int j = 0; j < imageWidth; j++) {
				rowData[j] = 0xff000000;
				rowData[j] += (buf[3 * (curCol*imageWidth + j)] & 0xff);
				rowData[j] += (buf[3 * (curCol*imageWidth + j) + 1] & 0xff) << 8;
				rowData[j] += (buf[3 * (curCol*imageWidth + j) + 2] & 0xff) << 16;

			}
			for (int j = 0; j < (int)navigationWidth; j++) {
				navigationData[tempIndex*((int)navigationWidth) + j] = rowData[j*xblocklen];
			}
			tempIndex--;
			
		}
	}
	sampleLine.clear();
	qDebug()<<"index range is :" << tempIndex;
	free(buf);
	free(rowData);
	return navigationData;


	tempIndex = 0;
	// order
	for (strip = 0; strip < stripnumber; strip++) {

		if (sampleLine[strip].size() == 0) continue;

		TIFFReadEncodedStrip(tif, strip, buf, (tsize_t)-1);

		//find corresponding row and save
		for (int i = 0; i < sampleLine[strip].size(); i++) {
			if (tempIndex >= (int)navigationHeight) break;
			int curCol = sampleLine[strip][i];

			for (int j = 0; j < imageWidth; j++) {
				rowData[j] = 0xff000000;
				rowData[j] += (buf[3 * (curCol*imageWidth + j)] & 0xff);
				rowData[j] += (buf[3 * (curCol*imageWidth + j) + 1] & 0xff) << 8;
				rowData[j] += (buf[3 * (curCol*imageWidth + j) + 2] & 0xff) << 16;

			}
			//for (tstrip_t j = 0; j < imageWidth; j += xblocklen) {
			//	navigationData[tempIndex*((int)navigationWidth) + j / xblocklen] = rowData[j];
			//}
			for (int j = 0; j < (int)navigationWidth; j++) {
				navigationData[tempIndex*((int)navigationWidth) + j] = rowData[j*xblocklen];
			}
			tempIndex++;

			//qDebug() << "range :" <<(tempIndex)*((int)navigationWidth);
		}
	}
	qDebug() << "index range is :" << tempIndex;
	free(buf);
	free(rowData);
	return navigationData;



	for (strip = 0; strip < TIFFNumberOfStrips(tif); strip++) {
		//qDebug() << "Last col before: " << lastCol;
		if (lastCol != 0) {
			int aaa = lastCol-imageRowsPerStrip;
			lastCol = aaa;
		}
		//qDebug() << "Last col end: " << lastCol;

		TIFFReadEncodedStrip(tif, strip, buf, (tsize_t)-1);
		//_TIFFmemset(testData, 0xff000000, imageWidth*imageRowsPerStrip* sizeof(uint32));
		//qDebug() << TIFFStripSize(tif) / 3 << "\n";
		for (int i = 0; i < TIFFStripSize(tif) / 3; i++) {
			testData[i] = 0xff000000;
			testData[i] += (buf[3 * (i)] & 0xff);
			testData[i] += (buf[3 * (i) + 1] & 0xff) << 8;
			testData[i] += (buf[3 * (i) + 2] & 0xff) << 16;
		}


		for (tstrip_t i = lastCol; i < imageRowsPerStrip; i += yblocklen) {
			for (tstrip_t j = 0; j < imageWidth; j+=xblocklen) {
				navigationData[(curIndex / yblocklen)*((int)navigationWidth)+j / xblocklen] = testData[i*imageWidth + j];
			}
			curIndex+= yblocklen;
			lastCol += yblocklen;
			if (lastCol >= imageRowsPerStrip) break;
		}
		_TIFFmemset(testData, 0, imageWidth*imageRowsPerStrip* sizeof(uint32));
		
	}
	//testImage->save("test.bmp");
	_TIFFfree(testData);
	//delete testImage;
	return navigationData;
	
	return this->navigationData;
}

void TiffReader::saveTiffFile(const QString & file_name, uint32* image_data)
{
	TIFF *image;
	if ((image = TIFFOpen(file_name.toStdString().c_str(), "w")) == NULL)
	{
		std::cout << "can not open the " << file_name.toStdString() << " to write." << endl;
		exit(-1);
	}

	// We need to set some values for basic tags before we can add any data
	TIFFSetField(image, TIFFTAG_IMAGEWIDTH, imageWidth);//set the width
	TIFFSetField(image, TIFFTAG_IMAGELENGTH, imageLength);//set the height
	TIFFSetField(image, TIFFTAG_BITSPERSAMPLE, bps);//set the size of the channels
	TIFFSetField(image, TIFFTAG_SAMPLESPERPIXEL, imageSamplePerPixel);//set number of channels per pixel
	TIFFSetField(image, TIFFTAG_ROWSPERSTRIP, imageLength);
	TIFFSetField(image, TIFFTAG_COMPRESSION, imageCompression);
	TIFFSetField(image, TIFFTAG_PHOTOMETRIC, imagePhotoMetric);
	TIFFSetField(image, TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
	TIFFSetField(image, TIFFTAG_PLANARCONFIG, imagePlanarConfig);
	TIFFSetField(image, TIFFTAG_ORIENTATION, Orientation);
	TIFFSetField(image, TIFFTAG_XRESOLUTION, X_Resolut);
	TIFFSetField(image, TIFFTAG_YRESOLUTION, Y_Resolut);
	TIFFSetField(image, TIFFTAG_RESOLUTIONUNIT, ResolutUnit);

	TIFFWriteEncodedStrip(image,0, image_data , imageLength*imageWidth*imageSamplePerPixel);

	// for (int n = 0; n < stripnumber; n++)
	// {
	// 	TIFFWriteEncodedStrip(image, n, image_data + n*stripeSize, stripeSize);
	// 	//TIFFWriteScanline(image, &array[n * image_width], n, 0);
	// }
	TIFFClose(image);// Close the file
}
