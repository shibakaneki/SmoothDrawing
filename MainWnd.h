/*
 * MainWnd.h
 *
 *  Created on: Jul 4, 2012
 *      Author: kindov
 */

#ifndef MAINWND_H_
#define MAINWND_H_

#include <QVBoxLayout>

#include "DrawingSurface.h"
#include "PropertiesWidget.h"

class MainWnd : public QWidget{
	Q_OBJECT
public:
	MainWnd(QWidget* parent=0, const char* name="MainWnd");
	virtual ~MainWnd();

private:
	QVBoxLayout* mpLayout;
	DrawingSurface* mpSurface;
	PropertiesWidget* mpProperties;
};

#endif /* MAINWND_H_ */
