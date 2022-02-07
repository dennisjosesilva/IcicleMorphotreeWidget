# IcicleMorphotreeWidget

It is a Qt widget that renders a morphological tree using icicle plots.

### Dependency

It depends on Conan, Qt, and morphotree library. 



The morphotree library is used as Conan package. To install, it needs to be downloaded from [Github repository](https://github.com/dennisjosesilva/morphotree)  and at the root repository run:  

```bash
conan create . morphotree/0.0.1@dennisjosesilva/dev
```

## installation

It can be used as a conan package by running the following command

```bash
$ conan create . IcicleMorphotreeWidget/0.0.1@dennisjosesilva/dev
```

### Usage

It can be used as any other Qt Widget. An minimal example would be:

```cpp
namespace icw = IcicleMorphotreeWidget;
namespace mt = morphotree;

std::vector<unsigned char> image = /* define a image */;
mt::Box domain = mt::Box::fromSize(mt::UI32Point{width, height});

icw::IcicleMorphotreeWidget treeWidget = new icw::IcicleMorphotreeWidget;
treeWidget->loadImage(domain, image);
```
