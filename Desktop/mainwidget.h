/*
    "Vypaluvach" - is control program for CNC wood burner "CNC Vypaluvach"
    Copyright (C) 2017 Volodymyr Stadnyk
    e-mail: Wladymyr1996@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>
*/

#ifndef MYWIDGET_H
#define MYWIDGET_H

#define PROGRESSBAR_WIDTH 20

#include "cnc.h"
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QRgb>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    void setPicture(QString filename);
    void setScale();
    void setLine(int y);
    int getCurrentLine();
    int getCountLines();
    int getProgress();
    QList<QList<ColorLine *> *> *getLines();

    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    void paintEvent(QPaintEvent *);void onMaxCountStepsChanget(int);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QList<QList<ColorLine*>*> *lines;
    QList<QList<ColorLine*>*> *emptyLines;
    qreal scale;
    QSize ImgSize;
    QSizeF ImgScaledSize;
    QPointF ImgPos;
    QPixmap *canvas, *pxmpMarker, *pxmpMarkerRotated;
    QPointF HeadPos;
    int currentLine;

private slots:
    void newPos(int x, int y);
    void newY(int yp);
    void printingEnd(bool error);

signals:
    void NewLineSet();
};

#endif // MYWIDGET_H
