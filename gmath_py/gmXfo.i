

%module gmath
%{
#include "gmXfo.h"
%}

//%ignore gmath::Matrix4::operator()(int,int);


#ifdef CMAYA 
    // only if gmath is build against  maya
    // ignore the c++ functions and re-implement them in python
    // this bypass the compatibility problem between swig and whatever maya's return in python.
    %ignore gmath::Xfo::fromMayaMatrix;
    %ignore gmath::Xfo::toMayaMatrix;
#endif


%include "gmXfo.h"

// extending Xfo
namespace gmath{
    %extend Xfo {
        std::string __str__() { // this is convenient in python
            return $self->toString();
        }

        %pythoncode {
            def __reduce__(self):
                ''' provides pickle support '''
                return self.__class__, (self.ori, self.tr, self.sc)
        }

        #if defined(CMAYA) || defined(PYMAYA)

            %pythoncode {
                def toMayaMatrix(self):
                    return self.toMatrix4().toMayaMatrix()

                def fromMayaMatrix(self, mayaMat):
                    gmat = Matrix4()
                    gmat.fromMayaMatrix(mayaMat)
                    self.fromMatrix4(gmat)
            }
            
        #endif
    }


    #if !defined(CMAYA) && defined(PYMAYA) 

        %pythoncode {
            def getGlobalXfo(mayaObj):
                return Xfo(getGlobalMatrix(mayaObj))

            def getLocalXfo(mayaObj):
                return Xfo(getLocalMatrix(mayaObj))

            def setGlobalXfo(mayaObj, xfo, withUndo=False):
                '''
                Args:
                    mayaObj (str|MDagPath|PyObject): The target object
                    xfo (GMath.Xfo): The source Xfo
                    withUndo (bool): if True this function will use Maya's commands instead of Maya's API.
                        This allows an undo/redo pipeline but it can be slower.
                        APIs should be in general faster but they come with no undo/redo pipeline (default: {False})
                '''
                setGlobalMatrix(mayaObj, xfo.toMatrix4(), withUndo)

            def setLocalXfo(mayaObj, xfo, withUndo=False):
                '''
                Args:
                    mayaObj (str|MDagPath|PyObject): The target object
                    xfo (GMath.Xfo): The source Xfo
                    withUndo (bool): if True this function will use Maya's commands instead of Maya's API.
                        This allows an undo/redo pipeline but it can be slower.
                        APIs should be in general faster but they come with no undo/redo pipeline (default: {False})
                '''
                setLocalMatrix(mayaObj, xfo.toMatrix4(), withUndo)
        }

    #endif

}