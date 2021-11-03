#include "IcicleMorphotreeWidget/Graphics/ColorMap.hpp"
#include "IcicleMorphotreeWidget/Graphics/ColorBar.hpp"

#include <QPainter>
#include <cmath>

#include <QDebug>

namespace IcicleMorphotreeWidget
{
  VColorBar *ColorMap::createVColorBar(QWidget *parent)
  {
    return new VColorBar{this, parent};
  }

  HColorBar *ColorMap::createHColorBar(QWidget *parent)
  {
    return new HColorBar{this, parent};
  }

  RainbowColorMap::RainbowColorMap(float dx)
    :ColorMap{},
     dx_{dx}
  {}

  // Function based on the prof. Alex Telea
  // Data Visualisation Principles and Practice 2nd edition
  // page: 152
  QColor RainbowColorMap::color(float u) const
  {
    u = (u < 0) ? 0 : ( u > 1) ? 1 : u; // camp u in [0, 1]
    float g = (6 - 2*dx_) * u + dx_;   // scale u to [dx, 6-dx]
    return QColor{
      static_cast<int>(255 * std::fmax(0.f, (3.f - std::fabs(g-4.f) - std::fabs(g-5.f))/2.f)),
      static_cast<int>(255 * std::fmax(0.f, (4.f - std::fabs(g-2.f) - std::fabs(g-4.f))/2.f)),
      static_cast<int>(255 * std::fmax(0.f, (3.f - std::fabs(g-1.f) - std::fabs(g-2.f))/2.f))
    };
  }
}
