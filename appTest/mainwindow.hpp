#include <morphotree/core/box.hpp>
#include <morphotree/core/alias.hpp>

#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"
#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"

#include <QMainWindow>

#include <QLabel>
#include <QSlider>
#include <QLineEdit>

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

  QLayout* createUniHeightControls(float initialUniHeight);

  void visualiseAttributesAct_onTrigger();    
  
  void uniHeightSlider_onSliderMoved(int value);
  void uniHeightLineEdit_onEditingFinishing();


private:
  void applyTreeLayoutChange();

private:
  imt::IcicleMorphotreeWidget *mtreeVis_;

  QLabel *uniHeightLabel_;
  QSlider *uniHeightSlider_;
  QLineEdit *uniHeightLineEdit_;

  imt::ColorBar *colorBar_;

  imt::GNodeStyle gradientNodeStyle_;

  QWidget *widget_;
  QLayout *layout_;
};