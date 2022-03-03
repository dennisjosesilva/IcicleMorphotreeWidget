# IcicleMorphotreeWidget

It is a Qt widget that renders a morphological tree using icicle plots.

### 1. Dependency

It depends on Conan, Qt, and morphotree library. 

The morphotree library is used as Conan package. To install, it needs to be downloaded from [Github repository](https://github.com/dennisjosesilva/morphotree)  and at the root repository run:  

```bash
conan create . morphotree/0.0.1@dennisjosesilva/dev
```

Alternatively, we can also install the morphotree library running the script **create_dependecies_packages.bash** that is available at the directory  **conan_dependencies_script** directory as follows:

```bash
bash create_dependecies_packages.bash
```

### 2. Updating dependency

To update the morphotree library dependency, one should first remove it using the following command:

```bash
conan remove . morphotree/0.0.1@dennisjosesilva/dev
```

Then, installing it back as instructed previously (Section 1). Alternatively, we can also run the script **update_package.bash** available at **conan_dependencies_script** directory as follows: 

```bash
bash update_package.bash
```

After updating morphotree library, we need to reinstall the IcicleMorphotree by removing and resintalling it (Section 3). The example application also need to be fully rebuilt (Section 4).

## 3. Installation

It can be used as a conan package by running the following command

```bash
$ conan create . IcicleMorphotreeWidget/0.0.1@dennisjosesilva/dev
```

#### 3.1 Usage

It can be used as any other Qt Widget. An minimal example would be:

```cpp
namespace icw = IcicleMorphotreeWidget;
namespace mt = morphotree;

std::vector<unsigned char> image = /* define a image */;
mt::Box domain = mt::Box::fromSize(mt::UI32Point{width, height});

icw::IcicleMorphotreeWidget treeWidget = new icw::IcicleMorphotreeWidget;
treeWidget->loadImage(domain, image);
```

## 4. Building and running an example application

An application was developed for debugging and feature checking  purposes. It is  unstable, but it is still can be a started point to know how the widget looks like and how it can be used.  To build this application, we have to create/install the morphotree dependency as described in Section 1. After it, we run the following steps:

```bash
mkdir build
cd build
conan install ..
cmake ..
make
```

After it is built, we can run the executable of the application as follows:

```bash
./bin/appTest
```

We can also render the widget using a pgm greyscale image file as follows:

```bash
./bin/appTest path/to/image.pgm
```
