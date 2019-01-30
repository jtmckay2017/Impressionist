//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "circlebrush.h"

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



	//glLineWidth((float)size); //add slider for line width

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
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

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	printf("Running Circles brush\n");
	printf("size %d, thickness %d, angle %d\n", pDoc->getSize(), pDoc->getThickness(), pDoc->getAngle());
}

