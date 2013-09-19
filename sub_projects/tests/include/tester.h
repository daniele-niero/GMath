/* Copyright (c) 2010-13, Daniele Niero
All rights reserved.

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
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#ifndef TESTER_H
#define TESTER_H

#include <stdio.h>
#include <iostream>
#include <exception>


class TestFail : public std::exception
{
private:
	std::string message;

public:
	explicit TestFail( const std::string& m ) { message = m; }
	virtual ~TestFail() throw() {};

	virtual const char* what()  const throw()
	{
		return message.c_str();
	}
};


#define ASSERT(x) \
	if (! (x)) \
	{ \
		char lineNumber[4]; std::sprintf(lineNumber, "%d", __LINE__); \
		std::string message; \
		message += "FAILED!  with code: "; \
		message += #x; \
		message += ", on line: "; \
		message += lineNumber; \
		message += ", in file: "; \
		message += __FILE__; \
		throw TestFail(message); \
	}


#define RUNTIME_ERROR(x) \
	char lineNumber[4]; std::sprintf(lineNumber, "%d", __LINE__); \
	std::string message; \
	message += "RUNTIME_ERROR!  with message: "; \
	message += #x; \
	message += ", on line "; \
	message += lineNumber; \
	message += ", in file "; \
	message += __FILE__; \
	throw TestFail(message);


#define TEST_CHECK(x) \
	try \
	{ \
		x(); \
		printf("%s... OK!\n", #x); \
	} \
	catch( std::exception& e ) \
	{ \
		fprintf(stderr, "%s... %s\n", #x, e.what()); \
	}


#endif
