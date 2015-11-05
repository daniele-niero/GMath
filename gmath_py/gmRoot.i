
%module gmath

%feature("autodoc", 1);

%include "exception.i"
%include "std_except.i"
%include "std_string.i"
// %include "std_vector.i"

%{
#define SWIG_FILE_WITH_INIT
#include "gmRoot.h"

// #include <array>
// #include <vector>
// class Axis;
%}


// %typemap(in) std::vector<double> %{
// 	$1.resize(PyList_Size($input));
// 	for (int i = 0; i < PyList_Size($input); ++i)
// 	{
// 		$1[i] = PyFloat_AsDouble(PyList_GetItem($input, i));
// 	} 
// %}

// %typemap(out) std::vector<double> %{
// 	$result = PyList_New($1.size());
// 	for (int i = 0; i < $1.size(); ++i) {
// 		PyList_SetItem($result, i, PyFloat_FromDouble($1[i]));
// 	}
// %}

// %inline %{
// class Axis{
// public:
// 	Axis();
// 	std::vector<double> get();
// 	void set(std::vector<double>);
	
// 	std::vector<double> arr;
// };

// Axis::Axis()
// {
// 	arr = {0.0, 1.0, 2.0, 3.0};
// }

// std::vector<double> Axis::get()
// { 
// 	return arr;
// }

// void Axis::set(std::vector<double> invalue)
// {
// 	for (unsigned int i=0; i<4; i++)
// 	{
// 		arr[i] = invalue[i];
// 	}
// }
// %}


#ifdef MAYA
    %pythoncode {
    	from maya import OpenMaya
    	import pymel.core.datatypes as pmdt
    }
#endif

%exception {
	try {
		$action
	} catch (const std::exception& e) {
		SWIG_exception(SWIG_RuntimeError, e.what());
	}
}

// handler for std::out_of_range thrown by the extended 
// __getitem__ implmented in each class' wrapper
%exception __getitem__ {
	try {
		$action
	} catch (std::out_of_range &e) {
		SWIG_exception(SWIG_IndexError, const_cast<char*>(e.what()));
		return NULL;
	}
}

// __setitem__ implmented in each class' wrapper
%exception __setitem__ {
	try {
		$action
	} catch (std::out_of_range &e) {
		SWIG_exception(SWIG_IndexError, const_cast<char*>(e.what()));
		return NULL;
	}
}

%ignore *::operator[](int i);
%ignore *::operator[](int i) const;
%ignore *::operator=;
%ignore *::operator==;
%ignore *::operator!=;
%ignore GMathError;


%include "gmRoot.h"
%include "gmVector3.i"
%include "gmVector4.i"
%include "gmEuler.i"
%include "gmQuaternion.i"
%include "gmMatrix3.i"
%include "gmMatrix4.i"

