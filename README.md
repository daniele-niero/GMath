# Overview

**GMath** is a math ~~templated~~ library written in C++ with Python wrappers made with ~~Boost::Python~~ [**SWIG**](http://www.swig.org/).

It has been designed with Computer Graphic technical directors in mind, especially Character TDs.
It's primary goal is not to be super fast (although it's not slow) but to be easy to understand and use.

**GMath** is a small and stright forward library; cpp source files are in ./source and headers are in ./include.
You can simply build your cpp application using them or you can build a library out of them.

## Buil

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
  
*copyright* **2010-17, Daniele Niero**

Redistribution and use in source and binary forms, with or without  
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this   
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,  
   this list of conditions and the following disclaimer in the documentation  
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND  
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,  
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,  
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)  
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,  
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,  
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE  