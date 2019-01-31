//
// ScatteredPointsBrush.cpp
//
// The implementation of ScatteredPointsBrush Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredpointsbrush.h"

extern float frand();

ScatteredPointsBrush::ScatteredPointsBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredPointsBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize((float)1);

	BrushMove(source, target);
}

void ScatteredPointsBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int radius = pDoc->getSize();

	if (pDoc == NULL) {
		printf("ScatteredPointsBrush::BrushMove  document is NULL\n");
		return;
	}

	for (int i = 0; i < radius; i++)
	{
		glBegin(GL_POINTS);

		//Get two random nums to add to points
		int randX = (rand() % radius) - (radius / 2);
		int randY = (rand() % radius) - (radius / 2);

		SetColor(source.x + randX, source.y + randY); 
		glVertex2d(target.x + randX, target.y + randY);



		glEnd();

	}

}

void ScatteredPointsBrush::BrushEnd(const Point source, const Point target)
{
	printf("Running Scattered Points Brush brush");
}

