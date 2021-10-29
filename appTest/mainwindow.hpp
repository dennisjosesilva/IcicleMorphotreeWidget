#include <morphotree/core/box.hpp>
#include <morphotree/core/alias.hpp>

#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"
#include "IcicleMorphotreeWidget/Graphics/GNode.hpp"
#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"

#include <QMainWindow>

#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace imt = IcicleMorphotreeWidget;
namespace mt = morphotree;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
  MainWindow(mt::Box domain, const std::vector<mt::uint8> &f);
  void nodeMousePress(imt::GNode *node, QGraphicsSceneMouseEvent *e);


private:
  imt::IcicleMorphotreeWidget *mtreeVis_;

  QWidget *widget_;
  QLayout *layout_;
};