//
// ScatteredLinesBrush.cpp
//
// The implementation of ScatteredLinesBrush Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredlinesbrush.h"

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



	//glLineWidth((float)size); //add slider for line width

	BrushMove(source, target);
}

void ScatteredLinesBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();

	//--------------------
	//Begin drawing lines
	//--------------------
	glBegin(GL_LINES);
	SetColor(source);

	glVertex2d(target.x, target.y);
	glVertex2d(target.x + size, target.y + size); //Affected by size slider
	glEnd();
}

void ScatteredLinesBrush::BrushEnd(const Point source, const Point target)
{
	printf("Running Scattered Lines Circles brush");
}

