/*
 * MainWnd.cpp
 *
 *  Created on: Jul 4, 2012
 *      Author: kindov
 */

#include "MainWnd.h"

MainWnd::MainWnd(QWidget* parent, const char* name):QWidget(parent)
	, mpLayout(NULL)
	, mpSurface(NULL)
	, mpProperties(NULL)
{
	setObjectName(name);
	mpLayout = new QVBoxLayout();
	setLayout(mpLayout);

	mpProperties = new PropertiesWidget(this);
	mpLayout->addWidget(mpProperties, 0);

	mpSurface = new DrawingSurface(this);
	mpLayout->addWidget(mpSurface, 1);

	connect(mpProperties, SIGNAL(subSegmentsNumberChanged(int)), mpSurface, SLOT(onSubSegmentsNumberChanged(int)));
}

MainWnd::~MainWnd() {
	if(NULL != mpProperties){
		delete mpProperties;
		mpProperties = NULL;
	}
	if(NULL != mpSurface){
		delete mpSurface;
		mpSurface = NULL;
	}
	if(NULL != mpLayout){
		delete mpLayout;
		mpLayout = NULL;
	}
}
