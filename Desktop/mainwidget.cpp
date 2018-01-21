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

#include "mainwidget.h"
#include <QTimer>
#include <QMessageBox>
#include "alldata.h"

void MainWidget::setPicture(QString filename)
{
    if ((AllData->getMaxSpeedPerX()<=0) ||
            (AllData->getMinSpeedPerX()<=0) ||
            (AllData->getMaxSpeedPerX()<=AllData->getMinSpeedPerX()) ||
            (AllData->getSkippedLines()<=0) ||
            (AllData->getSkippedYSteps()<=0)) {

        QMessageBox::warning(this, QString(tr("Error") + " - " + APPNAME), tr("You don't setting the app or wrong settings"));
    }
    else {
        if (lines==NULL) {
            delete lines;
            lines = NULL;
        }
        lines = new QList<QList<ColorLine*>*>;
        QImage img(filename);
        char current, next;
        QPoint beginPoint, endPoint;

        ImgSize=img.size();

        if ((AllData->getMaxCountStepsX()<ImgSize.width()) || (AllData->getMaxCountStepsY()<(ImgSize.height()*AllData->getSkippedYSteps())/AllData->getSkippedLines()))
            QMessageBox::information(this, tr("Warning") + " - " + APPNAME, tr("Your Image is too large for your settings."));
        int r, g, b;
        for (int y=0; y<img.height(); y++) {
            beginPoint=QPoint(0, y);
            lines->push_back(new QList<ColorLine*>());
            QColor(img.pixel(0, y)).getRgb(&r, &g, &b);\
            current = qRound(static_cast<qreal>(r+g+b)/(768.00f/static_cast<qreal>(AllData->getCColors())));
            for (int x=0; x<img.width(); x++) {
                QColor(img.pixel(x, y)).getRgb(&r, &g, &b);
                next = qRound(static_cast<qreal>(r+g+b)/(768.00f/static_cast<qreal>(AllData->getCColors())));
                if (current!=next) {
                    endPoint=QPoint(x, y);
                    if (beginPoint.x()<endPoint.x())
                        lines->at(y)->push_back(new ColorLine(beginPoint, endPoint, current));
                    current=next;
                    beginPoint=QPoint(x, y);
                }
            }
            endPoint=QPoint(img.width()-1, y);
            lines->at(y)->push_back(new ColorLine(beginPoint, endPoint, current));
        }

        if (canvas!=NULL) delete canvas;
        canvas = new QPixmap(ImgSize.width(), ImgSize.height());
        QPainter painter(canvas);
        for (int y=0; y<lines->count(); y++) {
            for (int x=0; x<lines->at(y)->count(); x++) {
                painter.setPen(QPen(QColor(lines->at(y)->at(x)->getRGBColor())));
                painter.drawLine(QLine((static_cast<qreal>(lines->at(y)->at(x)->line.x1())),
                                       (static_cast<qreal>(lines->at(y)->at(x)->line.y1())),
                                       (static_cast<qreal>(lines->at(y)->at(x)->line.x2())),
                                       (static_cast<qreal>(lines->at(y)->at(x)->line.y2()))));
            }
        }
        currentLine=0;
        emit NewLineSet();
        setScale();
    }
}

void MainWidget::setScale()
{
    int newWidth=width()-PROGRESSBAR_WIDTH, newHeight=height();
    if ((ImgSize.width())*newHeight>ImgSize.height()*newWidth) {
        scale=static_cast<qreal>(newWidth-2)/static_cast<qreal>(ImgSize.width());
    } else scale=static_cast<qreal>(newHeight-2)/static_cast<qreal>(ImgSize.height());
    repaint();
}

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    emptyLines = new QList<QList<ColorLine*>*>;

    lines = NULL;
    canvas = NULL;
    pxmpMarker = new QPixmap(":/img/marker.png");
    QMatrix mat;
    mat.rotate(180.0f);
    pxmpMarkerRotated = new QPixmap();
    *pxmpMarkerRotated = pxmpMarker->transformed(mat);

    setCursor(Qt::CrossCursor);

    connect(cnc, SIGNAL(newPosition(int,int)),
            SLOT(newPos(int,int)));
    connect(cnc, SIGNAL(newY(int)),
            SLOT(newY(int)));
    connect(cnc, SIGNAL(endPrint(bool)),
            SLOT(printingEnd(bool)));
}

MainWidget::~MainWidget()
{
    if (canvas!=NULL) delete canvas;
    if (lines!=NULL) delete lines;
    delete emptyLines;
    delete pxmpMarker;
    delete pxmpMarkerRotated;
}

void MainWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this); //Створюємо полотно

    //Фон
    painter.setBrush(QBrush(Qt::gray));
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.drawRect(QRectF(0, 0, width()-1, height()-1));
    setFocus();

    //Зображення
    if (lines==NULL) {
        //Якщо зображення нема
        painter.setRenderHint(QPainter::Antialiasing); //задля красивих діагональних ліній

        //Діагональні лінії
        painter.drawLine(0,0,width(),height());
        painter.drawLine(width(),0,0,height());
        painter.setPen(Qt::white);
        //Текст "Зображення відсутнє"
        painter.drawText(0, 0, width(), height(), Qt::AlignCenter|Qt::AlignHCenter, tr("No image"));
    } else {//Зображення завантажене

        //Розрахунок положення і розміру зображення на QPainter
        ImgPos.setX((width()-PROGRESSBAR_WIDTH-(ImgSize.width()*scale)-1.0)/2);
        ImgPos.setY((height()-(ImgSize.height()*scale)-1.0)/2+1.0);
        ImgScaledSize.setWidth(static_cast<qreal>(ImgSize.width())*scale);
        ImgScaledSize.setHeight(static_cast<qreal>(ImgSize.height())*scale);

        //МАлюємо зображення
        painter.setPen(Qt::black);
        painter.drawLine(0, ImgPos.y()-1, width(), ImgPos.y()-1);
        painter.drawLine(0, ImgPos.y()+ImgScaledSize.height()+0.5, width(), ImgPos.y()+ImgScaledSize.height()+0.5);
        painter.drawPixmap(QRectF(ImgPos.x(), ImgPos.y(), ImgScaledSize.width(), ImgScaledSize.height()),
                           *canvas,
                           QRectF(0.0f, 0.0f, ImgSize.width(), ImgSize.height()));
        if (AllData->getGetPosEnabled()) {
            //Пололоження голівки випалювача
            int x = qRound(HeadPos.x()*scale+scale/2);
            int y = qRound(HeadPos.y()*scale+scale/2);

            switch (AllData->getMarker()) {
            case 0:
                //Малюємо вказівник як на мапі
                if (y-32+ImgPos.y()<0)
                    painter.drawPixmap(x-16+ImgPos.x(), y+ImgPos.y(), 32, 32, *pxmpMarkerRotated);
                else
                    painter.drawPixmap(x-16+ImgPos.x(), y-32+ImgPos.y(), 32, 32, *pxmpMarker);
                break;
            case 1:
                //Звичайний вказівник
                painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine));
                painter.drawLine(QPointF(x+ImgPos.x()-7, y+ImgPos.y()-7),
                                 QPointF(x+ImgPos.x()+7, y+ImgPos.y()+7));
                painter.drawLine(QPointF(x+ImgPos.x()+7, y+ImgPos.y()-7),
                                 QPointF(x+ImgPos.x()-7, y+ImgPos.y()+7));
                break;
            }
        }
    }

    //Панель прогресу
    if (lines!=NULL) {

        //Білий прямокутник прогресу
        painter.setBrush(QBrush(Qt::white));
        painter.setPen(Qt::white);
        painter.drawRect(QRectF(width()-PROGRESSBAR_WIDTH,
                                ImgPos.y(),
                                PROGRESSBAR_WIDTH,
                                static_cast<qreal>(currentLine)*scale));
        //Темносірий прямокутник
        painter.setBrush(QBrush(QColor(100, 100, 100, 255)));
        painter.setPen(Qt::black);
        painter.drawRect(QRectF(width()-PROGRESSBAR_WIDTH-1.0f,
                                static_cast<qreal>(currentLine)*scale+ImgPos.y()+scale/2,
                                PROGRESSBAR_WIDTH,
                                static_cast<qreal>(lines->count()*scale-static_cast<qreal>(currentLine)*scale-0.5f-scale/2)));
        //Окантовка
        painter.setBrush(QBrush(QColor(0, 0, 0, 0)));
        painter.setPen(Qt::black);
        painter.drawRect(QRectF(width()-PROGRESSBAR_WIDTH-1.0f,
                                ImgPos.y(),
                                PROGRESSBAR_WIDTH,
                                static_cast<qreal>(lines->count()*scale-0.5f)));
        //Червона лінія прогресу
        painter.setPen(Qt::red);
        painter.drawLine(1,
                         static_cast<qreal>(currentLine)*scale+ImgPos.y()+scale/2,
                         width()-PROGRESSBAR_WIDTH-1.0f,
                         static_cast<qreal>(currentLine)*scale+ImgPos.y()+scale/2);
        //Виділення оранжевим частини зображення яке вже обролено.
        painter.setBrush(QColor(150, 100, 0, 50));
        painter.setPen(QColor(150, 100, 0, 50));
        painter.drawRect(QRectF(1.0f,
                                1.0f,
                                width()-PROGRESSBAR_WIDTH-1.0f,
                                static_cast<qreal>(currentLine)*scale+ImgPos.y()+scale/2));
    }
}

void MainWidget::setLine(int y)
{
    //Встановлення червоної лінії прогресу за координатою y
    if (lines!=NULL) {
        int maxLine = lines->count()-1;
        if (y>ImgScaledSize.height()+ImgPos.y()) currentLine=maxLine;
        else if (y<ImgPos.y()) currentLine=0;
        else
            currentLine = static_cast<qreal>(y-ImgPos.y()+0.5f)/scale-0.5f;
        emit NewLineSet();
        repaint();
    }
}

int MainWidget::getCurrentLine()
{
    //Поточна обрана лнія
    return currentLine+1;
}

int MainWidget::getCountLines()
{
    if (lines!=NULL) return lines->count();
    return 0;
}

int MainWidget::getProgress()
{
    if (lines==NULL) return 0;
    qreal answer = lines->count();
    answer=100/answer;
    answer*=static_cast<qreal>(getCurrentLine());
    return answer;
}

QList<QList<ColorLine *> *> *MainWidget::getLines()
{
    return lines;
}

void MainWidget::resizeEvent(QResizeEvent *)
{
    if (canvas!=NULL) setScale();
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if (!cnc->isBusy())
        setLine(event->pos().y());
}

void MainWidget::newPos(int x, int y)
{
    if (lines!=NULL) {
        HeadPos.setX(x);
        y=(y*AllData->getSkippedLines())/AllData->getSkippedYSteps();
        HeadPos.setY(-y);
        repaint();
    }
}

void MainWidget::newY(int yp)
{
    currentLine = yp * AllData->getSkippedLines();
    emit NewLineSet();
    repaint();
}

void MainWidget::printingEnd(bool error)
{
    if (!error) currentLine = lines->count()-1;
    emit NewLineSet();
    repaint();
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    if ((!event->isAutoRepeat()) && (!cnc->isBusy())) {
        switch (event->key()) {
        case Qt::Key_Left:
            cnc->move(cncleft);
            break;
        case Qt::Key_Right:
            cnc->move(cncright);
            break;
        case Qt::Key_Up:
            cnc->move(cncup);
            break;
        case Qt::Key_Down:
            cnc->move(cncdown);
            break;
        default:
            break;
        }
    }
    if (event->key() == Qt::Key_Space) cnc->stop();
}

void MainWidget::keyReleaseEvent(QKeyEvent *event)
{
    if ((!event->isAutoRepeat()) && (!cnc->isBusy()) && ((
                event->key()==Qt::Key_Left) || (
                event->key()==Qt::Key_Up) || (
                event->key()==Qt::Key_Down) || (
                event->key()==Qt::Key_Right) || (
                event->key()==Qt::Key_Space))) {
        if (event->key()==Qt::Key_Space) cnc->stop();
        else cnc->move(cncendmove);
    }
}
