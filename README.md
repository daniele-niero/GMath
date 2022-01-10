# Overview

**GMath** is a math ~~templated~~ library written in C++ with Python wrappers made with ~~Boost::Python~~ [**SWIG**](http://www.swig.org/).

It has been designed with Computer Graphic technical directors in mind, especially Character TDs.
It's primary goal is not to be super fast (although it's not slow) but to be easy to understand and use.

**GMath** is a small and stright forward library; cpp source files are in ./source and headers are in ./include.
You can simply build your cpp application using them or you can build a library out of them.

## Build

**GMath** uses [**waf**](https://github.com/waf-project/waf) to configure and build.

The only thing you need is to be sure that you have python installed for your system.
Mac and Linux users already have python out of the box, Windows users should install it.
You **don't need to install waf itself**, it is already included in the repo.

### CPP Only  

Building a static and/or shared library is incredibly easy.
From the command line navigate to the folder where you have cloned the repo and input this command:

```bash
./waf -h
```

This will print all the options used to configure and build **GMath**.

```bash
./waf configure
./waf build
```

this will create a shared and a static gmath library.

```
./waf install
```

will install the two libraries into your system. On Mac this will be /usr/local.
If you prefer a different install location, configure gmath specifing the --prefix option:

```bash
./waf configure --prefix=my/installation/path
./waf build
./waf install
```

Finally, if you want to build and install only one specific library (shared or static), specify the target you want to build.
For example:

```
./waf build --targets=gmath-shared
./waf install --targets=gmath-shared 
```

To know all the possible targets available, simply do:

```
./waf list
```


# License

MIT License 

Copyright (c) 2010-2017 Daniele Niero

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.