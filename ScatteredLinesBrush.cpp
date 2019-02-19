//
// ScatteredLinesBrush.cpp
//
// The implementation of ScatteredLinesBrush Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredlinesbrush.h"
#include <math.h>


extern float frand();

ScatteredLinesBrush::ScatteredLinesBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredLinesBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	//Enable blending for setting the alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glLineWidth((float)size); //add slider for line width

	BrushMove(source, target);
}

void ScatteredLinesBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int radius = pDoc->getSize();
	int size = pDoc->getSize();
	int thickness = pDoc->getThickness();
	int angle = pDoc->getAngle();
	double angleRadians = (M_PI / 180.0) * angle;

	//Set line width
	glLineWidth(thickness);

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	float alpha = pDoc->getAlpha();

	//--------------------
	//Begin drawing lines
	//--------------------
	for (int i = 0; i < 5; i++)
	{

		glBegin(GL_LINES);

		//Get two random nums to add to points
		int randX = (rand() % radius) - (radius / 2);
		int randY = (rand() % radius) - (radius / 2);

		Point temp = Point(source.x + randX, source.y + randY);

		SetColor(temp, alpha);

		glVertex2d(target.x + randX, target.y + randY);
		glVertex2d(target.x + randX + cos(angleRadians)*size, target.y + randY + sin(angleRadians)*size); //Affected by size slider

		glEnd();

	}
}

void ScatteredLinesBrush::BrushEnd(const Point source, const Point target)
{
	printf("Running Scattered Lines brush");
}

