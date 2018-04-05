#include "xsled.h"

#include <QPainter>

XSLed::XSLed(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(28, 28);
    lit = false;
    ledOnColor=Qt::green;
    ledOffColor=Qt::red;
    ledOnPattern = Qt::SolidPattern;
    ledOffPattern = Qt::SolidPattern;
    ledSize=20;
}

void XSLed::paintEvent(QPaintEvent *) {
  QPainter p(this);
  lit ?  p.setBrush(QBrush(ledOnColor, ledOnPattern)) : p.setBrush(QBrush(ledOffColor, ledOffPattern));
  p.drawEllipse(0,0,ledSize,ledSize);
}

void XSLed::switchXSLed() {
  lit = ! lit;
  repaint();
}
void XSLed::setState(bool state)
{
    lit = state;
    repaint();
}
void XSLed::toggle()
{
    lit = ! lit;
    repaint();
}

void XSLed::setOnColor(QColor onColor)
{
    ledOnColor=onColor;
    repaint();
}
void XSLed::setOffColor(QColor offColor)
{
    ledOffColor=offColor;
    repaint();
}
void XSLed::setOnPattern(Qt::BrushStyle onPattern)
{
    ledOnPattern=onPattern;
    repaint();
}
void XSLed::setOffPattern(Qt::BrushStyle offPattern)
{
    ledOffPattern=offPattern;
    repaint();
}
void XSLed::setLedSize(int size)
{
    ledSize=size;
    setFixedSize(size+10, size+10);
    repaint();
}
