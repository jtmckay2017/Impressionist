//
// ScatteredFilledCirclesBrush.h
//
// The header file for Line Brush. 
//

#ifndef SCATTEREDFILLEDCIRCLESBRUSH_H
#define SCATTEREDFILLEDCIRCLESBRUSH_H

#include "ImpBrush.h"

class ScatteredFilledCirclesBrush : public ImpBrush
{
public:
	ScatteredFilledCirclesBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif
