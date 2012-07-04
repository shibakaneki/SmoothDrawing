/*
 * DrawingSurface.cpp
 *
 *  Created on: Jul 4, 2012
 *      Author: kindov
 */

#include <QPainter>
#include <QStyleOption>
#include <math.h>
#include "DrawingSurface.h"

//#define FAKE_POINTS		1

DrawingSurface::DrawingSurface(QWidget* parent, const char* name):QWidget(parent){
	setObjectName(name);
	resize(1024, 768);
	setStyleSheet("background:black;");
	mBrush.setColor(Qt::black);
	mDrawingInProgress = false;
	mPen.setWidth(5);
	mPen.setCapStyle(Qt::RoundCap);
	mPen.setJoinStyle(Qt::RoundJoin);
	mNbSegments = 5;

#ifdef FAKE_POINTS
	mSampledPoints << QPoint(100, 100);
	mSampledPoints << QPoint(200, 400);
	mSampledPoints << QPoint(500, 500);
	mSampledPoints << QPoint(600, 300);
	mSampledPoints << QPoint(900, 100);
	onSubSegmentsNumberChanged(mNbSegments);
#endif
}

DrawingSurface::~DrawingSurface() {

}

void DrawingSurface::onSubSegmentsNumberChanged(int v){
	mNbSegments = v;
	if(mSampledPoints.size() > 1){
		generateAllSegments();
	}
	update();
}

void DrawingSurface::mousePressEvent(QMouseEvent* ev){
	handlePressEvent(ev->pos());
}

void DrawingSurface::mouseMoveEvent(QMouseEvent* ev){
	handleMoveEvent(ev->pos());
}

void DrawingSurface::mouseReleaseEvent(QMouseEvent* ev){
	handleReleaseEvent(ev->pos());
}

void DrawingSurface::tabletEvent(QTabletEvent* ev){
	QEvent::Type t = ev->type();
	switch(t){
	case QEvent::TabletPress:
		handlePressEvent(ev->pos());
		break;
	case QEvent::TabletMove:
		handleMoveEvent(ev->pos());
		break;
	case QEvent::TabletRelease:
		handleReleaseEvent(ev->pos());
		break;
	default:
		break;
	}
}

void DrawingSurface::handlePressEvent(QPoint p){
#ifndef FAKE_POINTS
	mSampledPoints.clear();
	mSegmentsPoints.clear();
	mDrawingInProgress = true;
	mSampledPoints << p;
	onSubSegmentsNumberChanged(mNbSegments);
#else
	Q_UNUSED(p);
#endif
}

void DrawingSurface::handleMoveEvent(QPoint p){
#ifndef FAKE_POINTS
	if(mDrawingInProgress){
		mSampledPoints << p;
		onSubSegmentsNumberChanged(mNbSegments);
	}
#else
	Q_UNUSED(p);
#endif
}

void DrawingSurface::handleReleaseEvent(QPoint p){
#ifndef FAKE_POINTS
	mSampledPoints << p;
	mDrawingInProgress = false;
	onSubSegmentsNumberChanged(mNbSegments);
#else
	Q_UNUSED(p);
#endif
}

void DrawingSurface::paintEvent(QPaintEvent* ev){
	Q_UNUSED(ev);
	QStyleOption opt;
	opt.init(this);

	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	mPen.setColor(Qt::green);
	p.setPen(mPen);
	p.setRenderHint(QPainter::Antialiasing, true);

	if(mSampledPoints.size() > 1 && mSegmentsPoints.size() > 1){
		// Draw the not-interpolated lines
		for(int i=1; i<mSampledPoints.size(); i++){
			p.drawLine(mSampledPoints.at(i-1), mSampledPoints.at(i));
		}

		// Draw the interpolated lines
		mPen.setColor(QColor(255, 0, 0, 125));
		p.setPen(mPen);
		for(int j=1; j<mSegmentsPoints.size(); j++){
			p.drawLine(mSegmentsPoints.at(j-1), mSegmentsPoints.at(j));
		}
	}
}

QVector<SCubicPolynomial> DrawingSurface::generateXPolynomials(){
	QVector<SCubicPolynomial> pts;

	int n = mSampledPoints.size() - 1;

	float gamma[n+1];
	float delta[n+1];
	float D[n+1];
	int i;

	gamma[0] = 1.0f/2.0f;
	for(i=1; i<n; i++){
		gamma[i] = 1/(4-gamma[i-1]);
	}
	gamma[n] = 1/(2-gamma[n-1]);

	delta[0] = 3*(mSampledPoints.at(1).x()-mSampledPoints.at(0).x())*gamma[0];
	for(i=1; i<n; i++){
		delta[i] = (3*(mSampledPoints.at(i+1).x()-mSampledPoints.at(i-1).x())-delta[i-1])*gamma[i];
	}
	delta[n] = (3*(mSampledPoints.at(n).x()-mSampledPoints.at(n-1).x())-delta[n-1])*gamma[n];

	D[n] = delta[n];
	for(i=n-1; i>=0; i--){
		D[i] = delta[i] - gamma[i]*D[i+1];
	}

	// now compute the coefficients of the cubics
	for(i=0; i < n; i++){
		SCubicPolynomial polyn = SCubicPolynomial((float)mSampledPoints.at(i).x(), D[i], 3*(mSampledPoints.at(i+1).x() - mSampledPoints.at(i).x()) - 2*D[i] - D[i+1], 2*(mSampledPoints.at(i).x() - mSampledPoints.at(i+1).x()) + D[i] + D[i+1]);
		pts << polyn;
	}

	return pts;
}

QVector<SCubicPolynomial> DrawingSurface::generateYPolynomials(){
	QVector<SCubicPolynomial> pts;

	int n = mSampledPoints.size() - 1;

	float gamma[n+1];
	float delta[n+1];
	float D[n+1];
	int i;

	gamma[0] = 1.0f/2.0f;
	for(i=1; i<n; i++){
		gamma[i] = 1/(4-gamma[i-1]);
	}
	gamma[n] = 1/(2-gamma[n-1]);

	delta[0] = 3*(mSampledPoints.at(1).y()-mSampledPoints.at(0).y())*gamma[0];
	for(i=1; i<n; i++){
		delta[i] = (3*(mSampledPoints.at(i+1).y()-mSampledPoints.at(i-1).y())-delta[i-1])*gamma[i];
	}
	delta[n] = (3*(mSampledPoints.at(n).y()-mSampledPoints.at(n-1).y())-delta[n-1])*gamma[n];

	D[n] = delta[n];
	for(i=n-1; i>=0; i--){
		D[i] = delta[i] - gamma[i]*D[i+1];
	}

	// now compute the coefficients of the cubics
	for(i=0; i < n; i++){
		SCubicPolynomial polyn = SCubicPolynomial((float)mSampledPoints.at(i).y(), D[i], 3*(mSampledPoints.at(i+1).y() - mSampledPoints.at(i).y()) - 2*D[i] - D[i+1], 2*(mSampledPoints.at(i).y() - mSampledPoints.at(i+1).y()) + D[i] + D[i+1]);
		pts << polyn;
	}

	return pts;
}

void DrawingSurface::generateAllSegments(){
	mSegmentsPoints.clear();
	const QVector<SCubicPolynomial> xPol = generateXPolynomials();
	const QVector<SCubicPolynomial> yPol = generateYPolynomials();

	SCubicPolynomial scpX = xPol.at(0);
	SCubicPolynomial scpY = yPol.at(0);
	QPoint origin;
	QPoint dest;
	origin.setX(roundf(scpX.eval(0)));
	origin.setY(roundf(scpX.eval(0)));
	mSegmentsPoints << origin;
	for(int i=0; i<xPol.size(); i++) {
		for(int j=1; j<=mNbSegments; j++){
		  float u = j / (float) mNbSegments;
		  SCubicPolynomial scpXU = xPol.at(i);
		  SCubicPolynomial scpYU = yPol.at(i);
		  dest.setX(roundf(scpXU.eval(u)));
		  dest.setY(roundf(scpYU.eval(u)));

		  mSegmentsPoints << dest;
		  origin = dest;
		}
	}
}
