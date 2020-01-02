#include <malloc.h>
#include <math.h>
#include <fstream>
#include<iostream>
#include <string>
#include <assert.h>
#include <glut.h>
#pragma warning(disable : 4996)

using std::fstream;
using std::ios;
using std::string;
using std::cout;
using std::endl;


// ********** mRGBA class **********
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;

class mRGBA { // the name RGBA is already used by Windows

public:

	unsigned char r, g, b, a;
	mRGBA() { r = g = b = 0; a = 255; }
	mRGBA(mRGBA &p) { r = p.r; g = p.g; b = p.b; a = p.a; }
	mRGBA(unsigned char rr, unsigned char gg, unsigned char bb, unsigned char aa)
	{
		r = rr; g = gg; b = bb; a = aa;
	}

	void set(unsigned char rr, unsigned char gg, unsigned char bb, unsigned char aa)
	{
		r = rr; g = gg; b = bb; a = aa;
	}
};

/********** RGBPixmap class ************/

//helper function
unsigned short getShort(FILE *fp)
{
	// BMP format uses little-endian integer types
	// get a 2-byte integer stored in little-endian form

	char ic;
	unsigned short ip;

	ic = fgetc(fp);
	ip = ic;			//first byte is little one 

	ic = fgetc(fp);
	ip |= ((unsigned short)ic << 8);	// or in high order byte

	return ip;

}

//helper function
unsigned long getLong(FILE *fp)
{
	//BMP format uses little-endian integer types
	// get a 4-byte integer stored in little-endian form

	unsigned long ip = 0;
	char ic = 0;
	unsigned char uc = ic;

	ic = fgetc(fp);
	uc = ic; ip = uc;

	ic = fgetc(fp);
	uc = ic;
	ip |= ((unsigned long)uc << 8);

	ic = fgetc(fp);
	uc = ic;
	ip |= ((unsigned long)uc << 16);

	ic = fgetc(fp);
	uc = ic;
	ip |= ((unsigned long)uc << 24);

	return ip;
}

void fskip(FILE *fp, int num_bytes)
{
	int i;
	for (i = 0; i < num_bytes; i++)
		fgetc(fp);
}

class RGBApixmap
{
public:
	mRGBA *pixel;  // array of pixels
	int nRows, nCols;                       // dimensions of pixel map
	RGBApixmap() { nRows = nCols = 0; pixel = 0; }

	RGBApixmap(int rows, int cols)
	{
		nRows = rows;
		nCols = cols;
		pixel = new mRGBA[rows * cols];
	}

	void mDraw()
	{
		if (nRows == 0 || nCols == 0)
			return;
		// tell OpenGL: don't align pixels with 4-byte boundaries in memory
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glDrawPixels(nCols, nRows, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
	}

	// *** read BMP file into this pixel map (see RGBpixmap.cpp)
	int readBMPFile(string fname);
	int changeColor(string fname, mRGBA color);
}; // class RGBApixmap

// *** Read into memory an mRGB image from an uncompressed BMP file
// return 0 on fail, 1 for Ok
int RGBApixmap::readBMPFile(string fname)
{
	FILE *fp;

	//  long index;
	int row, col, numPadBytes, nBytesInRow;

	unsigned long fileSize;
	unsigned short reserved1;		// always 0
	unsigned short reserved2;		// always 0 
	unsigned long offBits;			// offset to image - unreliable
	unsigned long headerSize;		// always 40
	unsigned long numCols;			// number of columns in image
	unsigned long numRows;			// number of rows in image
	unsigned short planes;			// always 1 
	unsigned short bitsPerPixel;    // 8 or 24; allow 24 here
	unsigned long compression;      // must be 0 for uncompressed 
	unsigned long imageSize;		// total bytes in image 
	unsigned long xPels;			// always 0 
	unsigned long yPels;			// always 0 
	unsigned long numLUTentries;    // 256 for 8 bit, otherwise 0 
	unsigned long impColors;		// always 0 

	long count = 0;

	/* open the file */
	if ((fp = fopen(fname.c_str(), "rb")) == NULL)
	{
		printf("Error opening file %s.\n", fname);
		exit(1);
	}

	/* check to see if it is a valid bitmap file */
	if (fgetc(fp) != 'B' || fgetc(fp) != 'M')
	{
		fclose(fp);
		printf("%s is not a bitmap file.\n", fname);
		exit(1);
	}

	fileSize = getLong(fp);
	reserved1 = getShort(fp);	// always 0
	reserved2 = getShort(fp);	// always 0 
	offBits = getLong(fp);	// offset to image - unreliable
	headerSize = getLong(fp);	// always 40
	numCols = getLong(fp);	// number of columns in image
	numRows = getLong(fp);	// number of rows in image
	planes = getShort(fp);	// always 1 
	bitsPerPixel = getShort(fp);	//8 or 24; allow 24 here
	compression = getLong(fp);	// must be 0 for uncompressed 
	imageSize = getLong(fp);	// total bytes in image 
	xPels = getLong(fp);	// always 0 
	yPels = getLong(fp);	// always 0 
	numLUTentries = getLong(fp);	// 256 for 8 bit, otherwise 0 
	impColors = getLong(fp);	// always 0 

	if (bitsPerPixel != 24)
	{
		// error - must be a 24 bit uncompressed image
		printf("Error bitsperpixel not 24\n");
		exit(1);
	}

	// add bytes at end of each row so total # is a multiple of 4
	// round up 3 * numCols to next mult. of 4

	nBytesInRow = ((3 * numCols + 3) / 4) * 4;
	numPadBytes = nBytesInRow - 3 * numCols;		// need this many

	this->nRows = numRows;		// set class's data members
	this->nCols = numCols;
	this->pixel = new mRGBA[nRows * nCols];	// make space for array

	if (!this->pixel) return 0; // out of memory!
	count = 0;

	//dum;
	for (row = 0; row < numRows; row++) // read pixel values
	{
		for (col = 0; col < numCols; col++)
		{
			int r, g, b;
			b = fgetc(fp);
			g = fgetc(fp);
			r = fgetc(fp);			// read bytes

			pixel[count].r = r;	// place them in colors
			pixel[count].g = g;
			pixel[count].b = b;
			pixel[count++].a = 255;
		}
		fskip(fp, numPadBytes);
	}
	fclose(fp);
	return 1;
} // end of readBMPFile