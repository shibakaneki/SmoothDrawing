/*
 * DrawingSurface.h
 *
 *  Created on: Jul 4, 2012
 *      Author: kindov
 */

#ifndef DRAWINGSURFACE_H_
#define DRAWINGSURFACE_H_

#include <QWidget>
#include <QMouseEvent>
#include <QTabletEvent>
#include <QPaintEvent>
#include <QPen>
#include <QPoint>
#include <QVector>
#include <QBrush>

#include "SCubicPolynomial.h"

class DrawingSurface : public QWidget{
	Q_OBJECT
public:
	DrawingSurface(QWidget* parent=0, const char* name="DrawingSurface");
	virtual ~DrawingSurface();

public slots:
	void onSubSegmentsNumberChanged(int v);

protected:
	void mousePressEvent(QMouseEvent* ev);
	void mouseMoveEvent(QMouseEvent* ev);
	void mouseReleaseEvent(QMouseEvent* ev);
	void tabletEvent(QTabletEvent* ev);
	void paintEvent(QPaintEvent* ev);

private:
	void handlePressEvent(QPoint p);
	void handleMoveEvent(QPoint p);
	void handleReleaseEvent(QPoint p);
	void generateAllSegments();
	QVector<SCubicPolynomial> generateXPolynomials();
	QVector<SCubicPolynomial> generateYPolynomials();

	QPen mPen;
	QBrush mBrush;
	bool mDrawingInProgress;
	QVector<QPoint> mSampledPoints;
	int mNbSegments;
	QVector<QPoint> mSegmentsPoints;
};

#endif /* DRAWINGSURFACE_H_ */
