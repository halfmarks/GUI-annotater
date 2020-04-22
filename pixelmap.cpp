#include "pixelmap.h"
#include "mainwindow.h"
#include <iostream>
using namespace std;

pixelmap::pixelmap(QObject *parent)
{
    /* connect the point together */
    connect(this, SIGNAL(drawLines(QPointF, QPointF)), parent, SLOT(drawLines(QPointF,QPointF)));
    connect(this, SIGNAL(drawPolygon(QPolygonF)), parent, SLOT(drawPolygon(QPolygonF)));
}

/* loads image */
void pixelmap::loadImg(QGraphicsScene *scene)
{

    QImage image(filename);


    if (true)
    {
        /* load image onto pixmap (canvas) */
        QPixmap *p = new QPixmap(QPixmap::fromImage(image));

        /* update pixmap */
        setPixmap(*p);
    }

}


void pixelmap::mousePressEvent(QGraphicsSceneMouseEvent * event){

    if(PolygonOn == 1){

        /* getting postions and updating/storing the coordinates into the vector */
        xyPress.push_back(event->pos());

        /* after second point is clicked */
        if(xyPress.size() > 1)
        {
            /* drawline */
            emit drawLines(xyPress.back(), xyPress.at(xyPress.size()-2));

            polygonSide++;

        }
    }
}

void pixelmap::clearVectors(){

    xyPress.clear();
    lineV.clear();
    polygonSide = 1;
}


/* end drawing */
void pixelmap::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* ){

    if(PolygonOn == 1){
        /* draws line from first and last point */
        emit drawLines(xyPress.back(), xyPress.at(xyPress.size()-2));

        cout << polygonSide << endl;

        QPolygonF newPoly(xyPress);

        emit drawPolygon(newPoly);


        clearVectors();
    }
}

