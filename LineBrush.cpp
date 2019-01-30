//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "linebrush.h"
#include <math.h>

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();



	//glLineWidth((float)size); //add slider for line width

	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int thickness = pDoc->getThickness();
	int angle = pDoc->getAngle();
	double angleRadians = (M_PI / 180.0) * angle;

	//Set line width
	glLineWidth(thickness);

	//--------------------
	//Begin drawing lines
	//--------------------
	glBegin(GL_LINES);
		SetColor(source);

		glVertex2d(target.x, target.y);
		glVertex2d(target.x+cos(angleRadians)*size, target.y+sin(angleRadians)*size); //Affected by size slider
	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	printf("Running Line brush");
}

