// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>
#include <math.h>
#include <cmath>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "LineBrush.h"
#include "ScatteredLinesBrush.h"
#include "ScatteredPointsBrush.h"
#include "CircleBrush.h"
#include "ScatteredFilledCirclesBrush.h"


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;


	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatteredPointsBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatteredLinesBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatteredFilledCirclesBrush( this, "Scattered Circles" );

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];
}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];

	// Lets disable or enable settings based on brush
	if (m_pCurrentBrush == ImpBrush::c_pBrushes[1] || m_pCurrentBrush == ImpBrush::c_pBrushes[4])
	{
		m_pUI->enableLineSettings();
	}
	else {
		m_pUI->disableLineSettings();
	}	
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

//---------------------------------------------------------
// Returns the thickness of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getThickness()
{
	return m_pUI->getThickness();
}

//---------------------------------------------------------
// Set the angle of the brush.
//---------------------------------------------------------
void ImpressionistDoc::setAngle(int angle)
{
	m_pUI->setAngle(angle);
}

//---------------------------------------------------------
// Returns the angle of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getAngle()
{
	return m_pUI->getAngle();
}

//---------------------------------------------------------
// Return the alpha of the brush
//---------------------------------------------------------
float ImpressionistDoc::getAlpha()
{
	return m_pUI->getAlpha();
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;

	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();

	unsigned char* temp = m_ucPainting;

	return 1;
}


//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImageWithArray(unsigned char *blurredImg)
{


	// release old storage
	if (m_ucBitmap) delete[] m_ucBitmap;
	if (m_ucPainting) delete[] m_ucPainting;

	m_ucBitmap = blurredImg;



	// allocate space for draw view
	m_ucPainting = new unsigned char[m_nWidth*m_nHeight * 3];
	memset(m_ucPainting, 0, m_nWidth*m_nHeight * 3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(),
		m_pUI->m_mainWindow->y(),
		m_nWidth * 2,
		m_nHeight + 25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_paintView->refresh();

	return 1;
}

//----------------------------------------------------------------
// Load a Blurred image.
// Take original bitmap image and send
// it to program blurred.
//---------------------------------------------------------------
int ImpressionistDoc::loadImageBlurred(char *iname)
{
	//setup kernal
	const int kHeight = 5;
	const int kWidth = 5;
	unsigned char kernal[kHeight][kWidth] = {	
												{ 1, 4, 7, 4, 1 }, 
												{ 4, 16, 26, 16, 4 }, 
												{ 7, 26, 41, 26, 7 },
												{ 4, 16, 26, 16, 4 },
												{ 1, 4, 7, 4, 1 }				
											};


	// allocate space for new blurred image view
	unsigned char* m_ucBlurredBitmap = new unsigned char[m_nWidth*m_nHeight * 3];
	memset(m_ucBlurredBitmap, 0, m_nWidth*m_nHeight * 3);

	printf("load a blurred image: %s", iname);

	int currentLoad = 0;
	int divideBy = 273;

	unsigned char* temp = m_ucBitmap;


	for (int d = 0; d < 3; d++) //Loop through three times for each color value
	{
		for (int i = 0; i < m_nWidth; i++) //go through x values
		{
			for (int j = 0; j < m_nHeight; j++)  //go through y values
			{
				for (int w = i; w < i + kWidth; w++) //loop through kernal height
				{
					for (int h = j; h < j + kHeight; h++) //loop through kernal width
					{
						currentLoad += (GetOriginalPixel(w-2, h-2)[d] * kernal[h-j][w-i]); //Do computation with kernal then add to payload
					}
				}
				
				*((m_ucBlurredBitmap + 3 * (j*m_nWidth + i)) + d) = (currentLoad / divideBy); //Calculate center pixel and set it

				currentLoad = 0;  //Reset payload
			}
		}
	}
	
	loadImageWithArray(m_ucBlurredBitmap);
	return 1;
}

//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}

//-----------------------------------------------------------------
// Handle changing the line angle.  Get start and end point
// then do the calculations.
//-----------------------------------------------------------------
void ImpressionistDoc::LineBegin(const Point target)
{
	glLineWidth(1.0);
	angleLineStart = target;
	LineMove(target);
}


void ImpressionistDoc::LineMove(const Point target)
{

	glBegin(GL_LINES);
	glColor3f(255, 0, 0);
	glVertex2d(target.x, target.y);
	glVertex2d(angleLineStart.x, angleLineStart.y);
	glEnd();
	glFlush();
	LineEnd(target);
}

void ImpressionistDoc::LineEnd(const Point target)
{
	angleLineEnd = target;

	// Calculate angle and set it.
	double angle = atan2(angleLineStart.y - angleLineEnd.y, angleLineEnd.x - angleLineStart.x) * 180 / M_PI;
	if (angle < 0) {
		angle += 360;
	}
	angle -= 360;
	angle = abs(angle);
	setAngle(angle);
}