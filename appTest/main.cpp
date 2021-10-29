#include <iostream>
#include <memory>

#include <morphotree/core/alias.hpp>
#include <morphotree/core/box.hpp>
#include <morphotree/tree/mtree.hpp>
#include <morphotree/adjacency/adjacency.hpp>
#include <morphotree/adjacency/adjacency8c.hpp>
#include <morphotree/core/io.hpp>

#include <QApplication>
#include <QString>
#include <QImage>

#include "mainwindow.hpp"

namespace mt = morphotree;

int main(int argc, char *argv[]) 
{
  using MTree = mt::MorphologicalTree<mt::uint8>;
  using NodePtr = typename MTree::NodePtr;
  using ValueType = typename MTree::TreeWeightType;
  using Image = std::vector<mt::uint8>;

  QApplication app(argc, argv);

  if (argc > 1) {
    QString url{argv[1]};
    QImage img{url, "pgm"};
    mt::Box domain = mt::Box::fromSize(mt::UI32Point{
      static_cast<mt::uint32>(img.width()), static_cast<mt::uint32>(img.height())});
    mt::uint8 *imgdata = img.bits();
    std::vector<mt::uint8> f(imgdata, imgdata + domain.numberOfPoints());

    MainWindow mainWindow{domain, f};
    mainWindow.show();
    return app.exec();
  } 
  else {
    Image f = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 4, 4, 4, 7 ,7, 7, 0, 4, 4, 4, 4, 4, 0, 
      0, 7, 7, 4, 7, 4, 7, 0, 4, 7, 7, 7, 7, 0,
      0, 7, 4, 4, 7, 4, 7, 0, 4, 7, 7, 7, 7, 0,
      0, 4, 4, 4, 7, 4, 7, 0, 4, 7, 7, 7, 7, 0,
      0, 7, 7, 4, 7, 7, 7, 0, 4, 4, 4, 4, 4, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    mt::Box domain = mt::Box::fromSize(mt::UI32Point{14, 7});
    MainWindow mainwindow{domain, f};
    mainwindow.show();
    return app.exec();
  }
  
  std::cout << "Hello World!" << std::endl;
  return 0;
}