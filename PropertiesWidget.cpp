/*
 * PropertiesWidget.cpp
 *
 *  Created on: Jul 4, 2012
 *      Author: kindov
 */

#include "PropertiesWidget.h"

PropertiesWidget::PropertiesWidget(QWidget* parent, const char* name) : QWidget(parent)
	, mpSegLabel(NULL)
	, mpSegSlider(NULL)
	, mpLayout(NULL)
{
	setObjectName(name);

	mpLayout = new QHBoxLayout();
	setLayout(mpLayout);

	mpSegLabel = new QLabel(tr("Number of segments: "), this);
	mpLayout->addWidget(mpSegLabel, 0);

	mpSegSlider = new QSlider(this);
	mpSegSlider->setOrientation(Qt::Horizontal);
	mpSegSlider->setMinimum(1);
	mpSegSlider->setMaximum(50);
	mpSegSlider->setValue(5);
	mpLayout->addWidget(mpSegSlider, 1);
	connect(mpSegSlider, SIGNAL(valueChanged(int)), this, SIGNAL(subSegmentsNumberChanged(int)));
}

PropertiesWidget::~PropertiesWidget() {
	if(NULL != mpSegLabel){
		delete mpSegLabel;
		mpSegLabel = NULL;
	}
	if(NULL != mpSegSlider){
		delete mpSegSlider;
		mpSegSlider = NULL;
	}
	if(NULL != mpLayout){
		delete mpLayout;
		mpLayout = NULL;
	}
}
