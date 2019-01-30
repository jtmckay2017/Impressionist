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



	glPointSize((float)size);

	BrushMove(source, target);
}

void ScatteredPointsBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POINTS);
	SetColor(source);

	glVertex2d(target.x, target.y);

	glEnd();
}

void ScatteredPointsBrush::BrushEnd(const Point source, const Point target)
{
	printf("Running Scattered Points Brush brush");
}

