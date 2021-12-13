
%module gmath
%{
#include "gmMatrix4.h"
%}


namespace gmath {
    class Matrix4;
    %typemap(out) double* data %{
        $result = PyTuple_New(16); // use however you know the size here
        for (int i = 0; i < 16; ++i) {
            PyTuple_SetItem($result, i, PyFloat_FromDouble($1[i]));
        }
    %}
}

%ignore gmath::Matrix4::operator()(int,int);

#ifdef CMAYA
    // ignore these c++ functions and re-implement them in python
    // this bypass essentially 2 problems:the compatibility problem between swig and whatever maya's return in python.
    %ignore gmath::Matrix4::fromMayaMatrix;
    %ignore gmath::Matrix4::toMayaMatrix;

    // let's inject some code in these function to handle pymel objects

    %pythonprepend getGlobalMatrix(const std::string &) %{  
        try:
            return _gmath.getGlobalMatrix(args[0].__apimdagpath__())
        except:
            pass %} 

    %pythonprepend getLocalMatrix(const std::string &) %{
        try:
            return _gmath.getLocalMatrix(args[0].__apimdagpath__())
        except:
            pass %} 

    %pythonprepend setGlobalMatrix(const std::string &, const Matrix4 &) %{
        try:
            return _gmath.setGlobalMatrix(args[0].__apimdagpath__(), args[1])
        except:
            pass %} 

    %pythonprepend setLocalMatrix(const std::string &, const Matrix4 &) %{
        try:
            return _gmath.setLocalMatrix(args[0].__apimdagpath__(), args[1])
        except:
            pass %} 
#endif


%include "gmMatrix4.h"


// extending Matrix4
namespace gmath {

    %extend Matrix4 {

        const double& __getitem__(int i) {
            return (*$self)[i];
        }

        void __setitem__(int i, double value) {
            (*$self)[i] = value;
        }

        std::string __str__() { // this is convenient in python
            return $self->toString();
        }

        // pure python extension
        %pythoncode {
            def __reduce__(self):
                ''' provides pickle support '''
                return self.__class__, self.data()

            def __eq__(self, other):
                if type(other) == type(self):
                    for i in range(0, 16):
                        if self[i]!=other[i]:
                            return False
                    return True
                else:
                    return False
        }


        #if defined(CMAYA) || defined(PYMAYA)

        %pythoncode {
            def toMayaMatrix(self):
                mayaMat = OpenMaya.MMatrix()
                OpenMaya.MScriptUtil.createMatrixFromList(self.data(), mayaMat) 
                return mayaMat

            def toMaya2Matrix(self):
                return OpenMaya2.MMatrix(self.data())

            def fromMayaMatrix(self, mayaMat):
                self.set(getMMatrixData(mayaMat))
        }
        
        #endif
    }

    #if !defined(CMAYA) && defined(PYMAYA) 

        %pythoncode {
            def getGlobalMatrix(mayaObj):
                path = getMDagPath(mayaObj)
                gmatrix = Matrix4()
                gmatrix.fromMayaMatrix(path.inclusiveMatrix())
                return gmatrix

            def getLocalMatrix(mayaObj):
                path = getMDagPath(mayaObj)
                matrix = path.inclusiveMatrix() * path.exclusiveMatrixInverse()
                gmatrix = Matrix4()
                gmatrix.fromMayaMatrix(matrix)
                return gmatrix

            def setGlobalMatrix(mayaObj, gmatrix, withUndo=False):
                '''
                Args:
                    mayaObj (str|MDagPath|PyObject): The target object
                    gmatrix (GMath.Matrix4): The source Matrix
                    withUndo (bool): if True this function will use Maya's commands instead of Maya's API.
                        This allows an undo/redo pipeline but it can be slower.
                        APIs should be in general faster but they come with no undo/redo pipeline (default: {False})
                '''
                path = getMDagPath(mayaObj)
                if isinstance(path, OpenMaya.MDagPath):
                    om = OpenMaya
                    mmatrix = gmatrix.toMayaMatrix()
                else:
                    om = OpenMaya2
                    mmatrix = gmatrix.toMaya2Matrix()

                if withUndo:
                    parentGMatrix = Matrix4()
                    parentGMatrix.fromMayaMatrix()
                    localMatrix = mmatrix * path.exclusiveMatrixInverse()

                    objFullName = path.fullPathName()

                    cmds.undoInfo(chunkName='GMathGlobalMatrixSet', openChunk=True)

                    if path.apiType() == om.MFn.kJoint:
                        cmds.setAttr(objFullName+'.jointOrient', 0,0,0)
                    cmds.xform(objFullName, matrix=getMMatrixData(localMatrix))

                    cmds.undoInfo(chunkName='GMathGlobalMatrixSet', closeChunk=True)
                else:
                    localMatrix = mmatrix * path.exclusiveMatrixInverse()
                    mtmatrix = om.MTransformationMatrix(localMatrix)
                    mfnTransform = om.MFnTransform(path)
                    setMFnTransform(mfnTransform, mtmatrix)


            def setLocalMatrix(mayaObj, gmatrix, withUndo=False):
                '''
                Args:
                    mayaObj (str|MDagPath|PyObject): The target object
                    gmatrix (GMath.Matrix4): The source Matrix
                    withUndo (bool): if True this function will use Maya's commands instead of Maya's API.
                        This allows an undo/redo pipeline but it can be slower.
                        APIs should be in general faster but they come with no undo/redo pipeline (default: {False})
                '''
                path = getMDagPath(mayaObj)
                if isinstance(path, OpenMaya.MDagPath):
                    om = OpenMaya
                    mmatrix = gmatrix.toMayaMatrix()
                else:
                    om = OpenMaya2
                    mmatrix = gmatrix.toMaya2Matrix()

                if withUndo:
                    objFullName = path.fullPathName()

                    cmds.undoInfo(chunkName='GMathGlobalMatrixSet', openChunk=True)

                    if path.apiType() == om.MFn.kJoint:
                        cmds.setAttr(objFullName+'.jointOrient', 0,0,0)
                    cmds.xform(objFullName, matrix=getMMatrixData(mmatrix))

                    cmds.undoInfo(chunkName='GMathGlobalMatrixSet', closeChunk=True)
                else:
                    mtmatrix = om.MTransformationMatrix(mmatrix)
                    mfnTransform = om.MFnTransform(path)
                    setMFnTransform(mfnTransform, mtmatrix)
        }

    #endif

}
     
