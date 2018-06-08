![Raptor Logo](./Engine/Assets/Icons/raptor-logo.png "Raptor Game Engine")

# Raptor

Scary-efficient game engine for VR platforms, targeting PC and console.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

In order to begin hacking on the engine, you'll first need to set up your development enviroment with all the shiny new features of the modern digital world.  On linux systems, some quick `apt` magic should do the trick:

```
$ sudo apt-get update
$ sudo apt-get install build-essential software-properties-common -y
$ sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
$ sudo apt-get update
$ sudo apt-get install g++-8 cmake
```

### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
$ ./Engine/Build/build.sh
```

And that's it!  If you find that you've messed something up, or your binaries have turned into doc-eating monsters of doom, don't panic.  Removing all bins, libs and temporaries are as simple as cleaning for a fresh build, like so:

```
$ ./Engine/Build/clean.sh
```

**Be warned**: this will clear all your build caches (for the engine source *and* all dependancies!), so running `clean` will require a full rebuild.

## Deployment

To get this working on your system, just navigate to Raptor's root directory and enter:

```
$ ./Engine/Binaries/Raptor
```

This will launch the engine in its entirety (i.e. editor, build tools, project management, etc).

## Built With

* [CMake](https://cmake.org/) - Automated build tool
* [GLFW](http://www.glfw.org/) - Dependency Management
* [Love](http://spongebob.wikia.com/wiki/Neptune%27s_Spatula) - Perfect patties are made with love, not magic

## Contributing

There currently is no code of conduct, and there isn't an official contributing markdown page either :P If you still consider your soul worthy of helping out on the project, don't hesitate to email us at `hybridalpaca[at]gmail[dot]com`.  Please, use common sense when copying that email address.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/HybridAlpaca/Raptor/tags).

## Authors

* **Seth Traman** - *Lead Developer* - [cellman123](https://github.com/cellman123)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* Thanks to all the folks over at GitHub who made open-source code sharing possible

* Special thanks to [PurpleBooth](https://github.com/PurpleBooth) for this snazzy Markdown template
