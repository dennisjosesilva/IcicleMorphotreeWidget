#include "IcicleMorphotreeWidget/Graphics/ColorBar.hpp"

#include <QPainter>
#include <cmath>
#include <QFontMetrics>

#include <QDebug>

namespace IcicleMorphotreeWidget
{
  ColorBar::ColorBar(ColorMap *colorMap, QWidget *parent)
    :QWidget{parent}, showNumbers_{false}
  {
    for (float u = 0.0f; u <= 1.0f; u += 0.05f)
      gradient_.setColorAt(u, colorMap->color(u));
  }

  VColorBar::VColorBar(ColorMap *colorMap, QWidget *parent)
    :ColorBar(colorMap, parent)
  {
    setMinimumWidth(60);
  }

  void VColorBar::paintEvent(QPaintEvent *event)
  {
    const QRect &wrect = rect();

    QRect crect{ wrect.x() + 50, wrect.y(), wrect.width(), wrect.height() };

    gradient_.setStart(0, height());
    gradient_.setFinalStop(0, 0);
    QPainter painter{this};
    painter.setOpacity(0.9);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.fillRect(crect, gradient_);

    if (showNumbers_) {
      QFont font;
      font.setPointSize(8);
      painter.setFont(font);

      int topMargin = 10;
      int textHeight = 15;
      int vspace = 15;
      const int x = crect.x() - 50;

      int nsteps = height() / (textHeight + vspace);
      float vstep = (maxValue_ - minValue_) / float(nsteps);

      for (int step = 0; step <= nsteps; step++) {
        float voffset = vstep * step;
        int y = topMargin + ((textHeight + vspace) * step);
        painter.drawText(x, y, QString::number(maxValue_ - voffset, 'E', 2));
      }
    }
  }

  HColorBar::HColorBar(ColorMap *colorMap, QWidget *parent)
    :ColorBar{colorMap, parent}
  {
    setMinimumHeight(25);
  }

  void HColorBar::paintEvent(QPaintEvent *event)
  {
    const QRect &wrect = rect();

    gradient_.setStart(0, 0);
    QPainter painter{this};
    painter.setOpacity(0.9);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    if (showNumbers_) {
      QFont font;
      font.setPointSize(8);
      painter.setFont(font);

      QString minValueStr = QString::number(minValue_, 'E', 4);
      QString maxValueStr = QString::number(maxValue_, 'E', 4);

      QFontMetrics fm{font};
      int minValueStrWidth = fm.horizontalAdvance(minValueStr);
      int maxValueStrWidth = fm.horizontalAdvance(maxValueStr);
      int leftMargin = minValueStrWidth / 2;
      int rightMargin = maxValueStrWidth / 2;

      QRect gradRect { wrect.x() + leftMargin, wrect.y(), 
        wrect.width() - maxValueStrWidth, wrect.height() - 15 };

      gradient_.setFinalStop(gradRect.width(), 0);

      int y = gradRect.height() + 15;
      painter.drawText(0, y, minValueStr);
      painter.drawText(wrect.width() - maxValueStrWidth, y, maxValueStr);

      painter.fillRect(gradRect, gradient_);
    }
    else {
      QRect crect { wrect.x(), wrect.y(), wrect.width(), wrect.height()-15};
      gradient_.setFinalStop(crect.width(), 0);
      painter.fillRect(crect, gradient_);
    }
  }
}