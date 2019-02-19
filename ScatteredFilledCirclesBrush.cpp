//
// ScatteredFilledCirclesBrush.cpp
//
// The implementation of ScatteredFilledCirclesBrush Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredfilledcirclesbrush.h"
#include <math.h>

extern float frand();

ScatteredFilledCirclesBrush::ScatteredFilledCirclesBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredFilledCirclesBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	//Enable blending for setting the alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize((float)size);

	BrushMove(source, target);
}

void ScatteredFilledCirclesBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredFilledCirclesBrush::BrushMove  document is NULL\n");
		return;
	}

	int radius = pDoc->getSize();

	const int sides = 20;

	float alpha = pDoc->getAlpha();


	//--------------------
	//Begin drawing circles
	//--------------------
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 5; i++)
	{
		//Get two random nums to add to points
		int randX = (rand() % 15) - (15 / 2);
		int randY = (rand() % 15) - (15 / 2);

		Point temp = Point(source.x + randX, source.y + randY);

		SetColor(temp, alpha);

		for (double r = 0; r < radius; r += 0.5) //were drawing non filled circles so this loop draws multiple to fill them in
		{
			for (int a = 0; a < 360; a += 360 / sides)
			{
				double heading = a * M_PI / 180;
				glVertex2d((cos(heading) * (radius - r)) + target.x + randX, (sin(heading) * (radius - r)) + target.y + randY);
			}
		}
	}



	glEnd();
}

void ScatteredFilledCirclesBrush::BrushEnd(const Point source, const Point target)
{
	printf("Running Scattered Filled Circles brush");
}

