/*
A math library for 3D graphic.
Copyright (C) 2010-2012 Daniele Niero

Author contact: daniele . niero @ gmail . com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

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
