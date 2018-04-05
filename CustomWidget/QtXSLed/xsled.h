#ifndef XSLED_H
#define XSLED_H

#include <QWidget>

class XSLed: public QWidget {
    Q_OBJECT
  public:
    XSLed(QWidget *parent = 0);
    void setState(bool state);
    void toggle();
    void setOnColor(QColor onColor);
    void setOffColor(QColor offColor);
    void setOnPattern(Qt::BrushStyle onPattern);
    void setOffPattern(Qt::BrushStyle offPattern);
    void setLedSize(int size);

  public slots:
    void switchXSLed();
  protected:
    void paintEvent(QPaintEvent *);
  private:
    bool lit;
    QColor ledOnColor;
    QColor ledOffColor;
    Qt::BrushStyle ledOnPattern;
    Qt::BrushStyle ledOffPattern;
    int ledSize;
};

#endif
