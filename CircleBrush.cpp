//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "circlebrush.h"
#include <math.h>

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
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

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}


	int radius = pDoc->getSize();

	const int sides = 100;

	float alpha = pDoc->getAlpha();


	//--------------------
	//Begin drawing circles
	//--------------------
	glBegin(GL_LINE_LOOP);
	SetColor(source, alpha);

	for (double r = 0; r < radius; r+=0.5)
	{
		for (int a = 0; a < 360; a += 360 / sides)
		{
			double heading = a * M_PI / 180;
			glVertex2d((cos(heading) * (radius-r)) + target.x, (sin(heading) * (radius-r)) + target.y);
		}
	}

	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	printf("Running Circles brush\n");
	printf("size %d, thickness %d, angle %d\n", pDoc->getSize(), pDoc->getThickness(), pDoc->getAngle());
}

