/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QApplication>
#include <QMainWindow>
#include <QLineSeries>

#include <QValuesAxis>

#include "chart.h"
#include "chartview.h"

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLineSeries* series = new QLineSeries();

    series->append(0, 6);
    series->append(1, 3);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 13);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    Chart* chart = new Chart(0, 0, series);
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Drag'n drop to move data points");

    QValuesAxis *axisX = new QValuesAxis();
    chart->setAxisX(axisX, series);
    axisX->setRange(0, 20);

    QValuesAxis *axisY = new QValuesAxis();
    chart->setAxisY(axisY, series);
    axisY->setRange(0, 13);

    QObject::connect(series, SIGNAL(clicked(QPointF)), chart, SLOT(clickPoint(QPointF)));

    ChartView* chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}