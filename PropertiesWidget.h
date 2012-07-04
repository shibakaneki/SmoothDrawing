/*
 * PropertiesWidget.h
 *
 *  Created on: Jul 4, 2012
 *      Author: kindov
 */

#ifndef PROPERTIESWIDGET_H_
#define PROPERTIESWIDGET_H_

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QHBoxLayout>

class PropertiesWidget : public QWidget{
	Q_OBJECT
public:
	PropertiesWidget(QWidget* parent=0, const char* name="PropertiesWidget");
	virtual ~PropertiesWidget();

signals:
	void subSegmentsNumberChanged(int nb);

private:
	QLabel* mpSegLabel;
	QSlider* mpSegSlider;
	QHBoxLayout* mpLayout;
};

#endif /* PROPERTIESWIDGET_H_ */
