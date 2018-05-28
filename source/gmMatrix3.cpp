#include "gmMatrix3.h"
#include "gmQuaternion.h"

using namespace std;

namespace gmath
{
    /*------ constructors ------*/

    Matrix3::Matrix3()
    {
        _data[0]=1.0; _data[1]=0.0; _data[2]=0.0;
        _data[3]=0.0; _data[4]=1.0; _data[5]=0.0;
        _data[6]=0.0; _data[7]=0.0; _data[8]=1.0;
    }

    Matrix3::Matrix3(
        double xx, double xy, double xz,
        double yx, double yy, double yz,
        double zx, double zy, double zz)
    {
        _data[0]=xx; _data[1]=xy; _data[2]=xz;
        _data[3]=yx; _data[4]=yy; _data[5]=yz;
        _data[6]=zx; _data[7]=zy; _data[8]=zz;
    }

    Matrix3::Matrix3(const Matrix3 & other)
    {
        memcpy(_data, other._data, 9*sizeof(double));
    }

    Matrix3::Matrix3(
            const Vector3 &axisX,
            const Vector3 &axisY,
            const Vector3 &axisZ)
    {
        memcpy(&_data[0], axisX.data(), 3*sizeof(double));
        memcpy(&_data[3], axisY.data(), 3*sizeof(double));
        memcpy(&_data[6], axisZ.data(), 3*sizeof(double));
    }

    Matrix3::Matrix3(const Quaternion& quat)
    {
        this->fromQuaternion(quat);
    }

    Matrix3::Matrix3(const double* values)
    {
        set(values);
    }

    Matrix3::Matrix3(const std::vector<double>& values)
    {
        set(values);
    }   

    /*------ Data access ------*/

    double* Matrix3::data()
    {
        return &_data[0];
    }

    const double* Matrix3::data() const
    {
        return &_data[0];
    }

    /*------ Coordinates access ------*/
    
    double Matrix3::operator[] (int i) const
    {
        if (i>=0 && i<9)
        {
            return this->_data[i];
        }
        else {
            throw out_of_range("gmath::Matrix3: index out of range");
        }
    }

    double& Matrix3::operator[] (int i)
    {
        if (i>=0 && i<9)
        {
            return this->_data[i];
        }
        else {
            throw out_of_range("gmath::Matrix3: index out of range");
        }
    }

    double Matrix3::operator() (int row, int col) const
    {
        if (row>=0 && row<3 && col>=0 && col<3)
        {
            return this->_data[row*3+col];
        }
        else
        {
            throw out_of_range("gmath::Matrix3: row or column index out of range");
        }
    }

    double &Matrix3::operator() (int row, int col)
    {
        if (row>=0 && row<3 && col>=0 && col<3)
        {
            return this->_data[row*3+col];
        }
        else
        {
            throw out_of_range("gmath::Matrix3: row or column index out of range");
        }
    }

    /*------ Arithmetic operations ------*/

    Matrix3 Matrix3::operator + (double value) const
    {
        Matrix3 retMatrix(
            _data[0]+value, _data[1]+value, _data[2]+value,
            _data[3]+value, _data[4]+value, _data[5]+value,
            _data[6]+value, _data[7]+value, _data[8]+value
            );
        return retMatrix;
    }

    Matrix3 Matrix3::operator + (const Matrix3 &other) const
    {
        
        const double* b = other.data();
        Matrix3 retMatrix(
            _data[0]+b[0], _data[1]+b[1], _data[2]+b[2],
            _data[3]+b[3], _data[4]+b[4], _data[5]+b[5],
            _data[6]+b[6], _data[7]+b[7], _data[8]+b[8]
            );
        return retMatrix;
    }

    Matrix3 Matrix3::operator - (double value) const
    {
        Matrix3 retMatrix(
            _data[0]-value, _data[1]-value, _data[2]-value,
            _data[3]-value, _data[4]-value, _data[5]-value,
            _data[6]-value, _data[7]-value, _data[8]-value
            );
        return retMatrix;
    }

    Matrix3 Matrix3::operator - () const
    {
        Matrix3 newMatrix3((*this).inverse());
        return newMatrix3;
    }

    Matrix3 Matrix3::operator - (const Matrix3 &other) const
    {
        
        const double* b = other.data();
        Matrix3 retMatrix(
            _data[0]-b[0], _data[1]-b[1], _data[2]-b[2],
            _data[3]-b[3], _data[4]-b[4], _data[5]-b[5],
            _data[6]-b[6], _data[7]-b[7], _data[8]-b[8]
            );
        return retMatrix;
    }

    Matrix3 Matrix3::operator / (double value) const
    {
        Matrix3 retMatrix(
            _data[0]/value, _data[1]/value, _data[2]/value,
            _data[3]/value, _data[4]/value, _data[5]/value,
            _data[6]/value, _data[7]/value, _data[8]/value
            );

        return retMatrix;
    }

    Matrix3 Matrix3::operator * (double value) const
    {
        Matrix3 retMatrix(
            _data[0]*value, _data[1]*value, _data[2]*value,
            _data[3]*value, _data[4]*value, _data[5]*value,
            _data[6]*value, _data[7]*value, _data[8]*value
            );

        return retMatrix;
    }

    Matrix3 Matrix3::operator * (const Matrix3 &other) const
    {
        const double* b = other.data();
        Matrix3 retMatrix(
            _data[0]*b[0] + _data[1]*b[3] + _data[2]*b[6],
            _data[0]*b[1] + _data[1]*b[4] + _data[2]*b[7],
            _data[0]*b[2] + _data[1]*b[5] + _data[2]*b[8],

            _data[3]*b[0] + _data[4]*b[3] + _data[5]*b[6],
            _data[3]*b[1] + _data[4]*b[4] + _data[5]*b[7],
            _data[3]*b[2] + _data[4]*b[5] + _data[5]*b[8],

            _data[6]*b[0] + _data[7]*b[3] + _data[8]*b[6],
            _data[6]*b[1] + _data[7]*b[4] + _data[8]*b[7],
            _data[6]*b[2] + _data[7]*b[5] + _data[8]*b[8]
            );
        return retMatrix;
    }

    /*------ Arithmetic updates ------*/

    Matrix3& Matrix3::operator += (double value)
    {
        _data[0]+=value; _data[1]+=value; _data[2]+=value;
        _data[3]+=value; _data[4]+=value; _data[5]+=value;
        _data[6]+=value; _data[7]+=value; _data[8]+=value;
        return *this;
    }

    Matrix3& Matrix3::operator += (const Matrix3 &other)
    {
        double* a = data();
        const double* b = other.data();
        _data[0]+=b[0]; _data[1]+=b[1]; _data[2]+=b[2];
        _data[3]+=b[3]; _data[4]+=b[4]; _data[5]+=b[5];
        _data[6]+=b[6]; _data[7]+=b[7]; _data[8]+=b[8];
        return *this;
    }

    Matrix3& Matrix3::operator -= (double value)
    {
        _data[0]-=value; _data[1]-=value; _data[2]-=value;
        _data[3]-=value; _data[4]-=value; _data[5]-=value;
        _data[6]-=value; _data[7]-=value; _data[8]-=value;
        return *this;
    }

    Matrix3& Matrix3::operator -= (const Matrix3 &other)
    {
        double* a = data();
        const double* b = other.data();

        _data[0]-=b[0]; _data[1]-=b[1]; _data[2]-=b[2];
        _data[3]-=b[3]; _data[4]-=b[4]; _data[5]-=b[5];
        _data[6]-=b[6]; _data[7]-=b[7]; _data[8]-=b[8];
        return *this;
    }

    Matrix3& Matrix3::operator /= (double value)
    {
        _data[0]/=value; _data[1]/=value; _data[2]/=value;
        _data[3]/=value; _data[4]/=value; _data[5]/=value;
        _data[6]/=value; _data[7]/=value; _data[8]/=value;
        return *this;
    }

    Matrix3& Matrix3::operator *= (double value)
    {
        _data[0]*=value; _data[1]*=value; _data[2]*=value;
        _data[3]*=value; _data[4]*=value; _data[5]*=value;
        _data[6]*=value; _data[7]*=value; _data[8]*=value;
        return *this;
    }

    Matrix3& Matrix3::operator *= (const Matrix3 &other)
    {
        const double* a = &_data[0];
        const double* b = &other._data[0];
        double c[9];

        c[0] = _data[0]*b[0] + _data[1]*b[3] + _data[2]*b[6];
        c[1] = _data[0]*b[1] + _data[1]*b[4] + _data[2]*b[7];
        c[2] = _data[0]*b[2] + _data[1]*b[5] + _data[2]*b[8];
        c[3] = _data[3]*b[0] + _data[4]*b[3] + _data[5]*b[6];
        c[4] = _data[3]*b[1] + _data[4]*b[4] + _data[5]*b[7];
        c[5] = _data[3]*b[2] + _data[4]*b[5] + _data[5]*b[8];
        c[6] = _data[6]*b[0] + _data[7]*b[3] + _data[8]*b[6];
        c[7] = _data[6]*b[1] + _data[7]*b[4] + _data[8]*b[7];
        c[8] = _data[6]*b[2] + _data[7]*b[5] + _data[8]*b[8];

        memcpy(_data, c, 9*sizeof(double));
        return *this;
    }

    /*------ Comparisons ------*/

    bool Matrix3::operator == (const Matrix3 &other) const
    {
        const double* b = &other._data[0];
        double e = gmath::EPSILON;
        return (fabs(_data[0]-b[0])<e && fabs(_data[1]-b[1])<e && fabs(_data[2]-b[2])<e &&
                fabs(_data[3]-b[3])<e && fabs(_data[4]-b[4])<e && fabs(_data[5]-b[5])<e &&
                fabs(_data[6]-b[6])<e && fabs(_data[7]-b[7])<e && fabs(_data[8]-b[8])<e);
    }

    bool Matrix3::operator != (const Matrix3 &other) const
    {
        const double* b = &other._data[0];
        double e = gmath::EPSILON;
        return (fabs(_data[0]-b[0])>e || fabs(_data[1]-b[1])>e || fabs(_data[2]-b[3])>e ||
                fabs(_data[3]-b[3])>e || fabs(_data[0]-b[0])>e || fabs(_data[0]-b[0])>e ||
                fabs(_data[0]-b[0])>e || fabs(_data[0]-b[0])>e || fabs(_data[0]-b[0])>e);
    }

    /*------ Assignment ------*/

    void Matrix3::operator = (const Matrix3 &other)
    {
        memcpy(_data, other._data, 9*sizeof(double));
    }

    /*------ methods ------*/

    void Matrix3::setToIdentity()
    {
        _data[0]=1.0; _data[1]=0.0; _data[2]=0.0;
        _data[3]=0.0; _data[4]=1.0; _data[5]=0.0;
        _data[6]=0.0; _data[7]=0.0; _data[8]=1.0;
    }

    void Matrix3::set(
        double xx, double xy, double xz,
        double yx, double yy, double yz,
        double zx, double zy, double zz)
    {
        _data[0]=xx; _data[1]=xy; _data[2]=xz;
        _data[3]=yx; _data[4]=yy; _data[5]=yz;
        _data[6]=zx; _data[7]=zy; _data[8]=zz;
    }

    void Matrix3::set(const double* values)
    {
        memcpy(_data, values, 9*sizeof(double));
    }

    void Matrix3::set(const std::vector<double>& values)
    {
        if (values.size()!=9) {
            throw out_of_range("gmath::Matrix3: values must be of 9 elments");
        }

        memcpy(_data, values.data(), 9*sizeof(double));
    }

    Vector3 Matrix3::getRow(unsigned int i) const
    {
        if (i>2)
        {
            throw out_of_range("gmath::Matrix3: index out of range");
        }
        return Vector3( _data[i*3], _data[i*3+1], _data[i*3+2] );
    }

    void Matrix3::setRow(unsigned int i, const Vector3 &vec)
    {
        if (i>2)
        {
            throw out_of_range("gmath::Matrix3: index out of range");
        }
        _data[i*3]   = vec.x;
        _data[i*3+1] = vec.y;
        _data[i*3+2] = vec.z;
    }

    Vector3 Matrix3::getAxisX() const
    {
        return getRow(0);
    }

    Vector3 Matrix3::getAxisY() const
    {
        return getRow(1);
    }

    Vector3 Matrix3::getAxisZ() const
    {
        return getRow(2);
    }

    void Matrix3::setAxisX(const Vector3& vec)
    {
        setRow(0, vec);
    }

    void Matrix3::setAxisY(const Vector3& vec)
    {
        setRow(1, vec);
    }

    void Matrix3::setAxisZ(const Vector3& vec)
    {
        setRow(2, vec);
    }

    Matrix3 Matrix3::transpose() const
    {
        return Matrix3(
                _data[0], _data[3], _data[6],
                _data[1], _data[4], _data[7],
                _data[2], _data[5], _data[8] );
    }

    void Matrix3::transposeInPlace()
    {
        this->set(
            _data[0], _data[3], _data[6],
            _data[1], _data[4], _data[7],
            _data[2], _data[5], _data[8] );
    }

    double Matrix3::determinant() const
    {
        double det;
        det = _data[0] * ( _data[4]*_data[8] - _data[7]*_data[5] )
            - _data[1] * ( _data[3]*_data[8] - _data[6]*_data[5] )
            + _data[2] * ( _data[3]*_data[7] - _data[6]*_data[4] );
        return det;
    }

    Matrix3 Matrix3::inverse() const
    {
        Matrix3 retMatrix;
        double invDet = 1/determinant();

        if ( invDet < gmath::EPSILON )
        {
            retMatrix = *this;
            retMatrix.setToIdentity();
        }
        else
        {
            retMatrix._data[0] =   _data[4]*_data[8] - _data[5]*_data[7]  / invDet;
            retMatrix._data[1] = -(_data[1]*_data[8] - _data[7]*_data[2]) / invDet;
            retMatrix._data[2] =   _data[1]*_data[5] - _data[4]*_data[2]  / invDet;

            retMatrix._data[3] = -(_data[3]*_data[8] - _data[5]*_data[6]) / invDet;
            retMatrix._data[4] =   _data[0]*_data[8] - _data[6]*_data[2]  / invDet;
            retMatrix._data[5] = -(_data[0]*_data[5] - _data[3]*_data[2]) / invDet;

            retMatrix._data[6] =   _data[3]*_data[7] - _data[6]*_data[4]  / invDet;
            retMatrix._data[7] = -(_data[0]*_data[7] - _data[6]*_data[1]) / invDet;
            retMatrix._data[8] =   _data[0]*_data[4] - _data[1]*_data[3]  / invDet;
        }

        return retMatrix;
    }

    void Matrix3::inverseInPlace()
    {
        double m[9];
        double invDet = 1/determinant();

        if ( invDet < gmath::EPSILON )
        {
            this->setToIdentity();
        }
        else
        {
            m[0] =   _data[4]*_data[8] - _data[5]*_data[7]  / invDet;
            m[1] = -(_data[1]*_data[8] - _data[7]*_data[2]) / invDet;
            m[2] =   _data[1]*_data[5] - _data[4]*_data[2]  / invDet;

            m[3] = -(_data[3]*_data[8] - _data[5]*_data[6]) / invDet;
            m[4] =   _data[0]*_data[8] - _data[6]*_data[2]  / invDet;
            m[5] = -(_data[0]*_data[5] - _data[3]*_data[2]) / invDet;

            m[6] =   _data[3]*_data[7] - _data[6]*_data[4]  / invDet;
            m[7] = -(_data[0]*_data[7] - _data[6]*_data[1]) / invDet;
            m[8] =   _data[0]*_data[4] - _data[1]*_data[3]  / invDet;

            memcpy(_data, m, 9*sizeof(double));
        }
    }

    Matrix3 Matrix3::orthogonal() const
    {
        Matrix3 m(*this);
        m.orthogonalInPlace();
        return m;
    }

    void Matrix3::orthogonalInPlace() //primaryAxis, secondaryAxis)
    {
        // Code take it from WildMagic 5  -  www.geometrictools.com  -  here the matrix is transpose
        // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
        // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
        //
        //   q0 = m0/|m0|
        //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
        //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
        //
        // where |V| indicates length of vector V and A*B indicates dot
        // product of vectors A and B.

        // Compute q0. length xAxis
        double invLength = (1.0 / sqrt(_data[0]*_data[0] + _data[1]*_data[1] + _data[2]*_data[2]));

        _data[0] *= invLength;
        _data[1] *= invLength;
        _data[2] *= invLength;

        // Compute q1.
        double dot0 = _data[0]*_data[3] + _data[1]*_data[4] +
            _data[2]*_data[5];

        _data[3] -= dot0*_data[0];
        _data[4] -= dot0*_data[1];
        _data[5] -= dot0*_data[2];

        invLength = (1.0 / sqrt(_data[3]*_data[3] + _data[4]*_data[4] + _data[5]*_data[5]));

        _data[3] *= invLength;
        _data[4] *= invLength;
        _data[5] *= invLength;

        // compute q2
        double dot1 = _data[3]*_data[6] + _data[4]*_data[7] +
            _data[5]*_data[8];

        dot0 = _data[0]*_data[6] + _data[1]*_data[7] +
            _data[2]*_data[8];

        _data[6] -= dot0*_data[0] + dot1*_data[3];
        _data[7] -= dot0*_data[1] + dot1*_data[4];
        _data[8] -= dot0*_data[2] + dot1*_data[5];

        invLength = (1.0 / sqrt(_data[6]*_data[6] + _data[7]*_data[7] + _data[8]*_data[8]));

        _data[6] *= invLength;
        _data[7] *= invLength;
        _data[8] *= invLength;
    }

    void Matrix3::setScale(const Vector3 &scale)
    {
        Vector3 x(_data[0], _data[1], _data[2]);
        Vector3 y(_data[3], _data[4], _data[5]);
        Vector3 z(_data[6], _data[7], _data[8]);
        x.normalizeInPlace();
        y.normalizeInPlace();
        z.normalizeInPlace();
        x *= scale.x;
        y *= scale.y;
        z *= scale.z;

        this->set(
            x.x, x.y, x.z,
            y.x, y.y, y.z,
            z.x, z.y, z.z );
    }

    void Matrix3::setScale(double sX, double sY, double sZ)
    {
        Vector3 x(_data[0], _data[1], _data[2]);
        Vector3 y(_data[3], _data[4], _data[5]);
        Vector3 z(_data[6], _data[7], _data[8]);
        x.normalizeInPlace();
        y.normalizeInPlace();
        z.normalizeInPlace();
        x *= sX;
        y *= sY;
        z *= sZ;

        this->set(
            x.x, x.y, x.z,
            y.x, y.y, y.z,
            z.x, z.y, z.z );
    }

    void Matrix3::addScale(const Vector3 &scale)
    {
        _data[0]+=scale.x; _data[1]+=scale.x; _data[2]+=scale.x;
        _data[3]+=scale.y; _data[4]+=scale.y; _data[5]+=scale.y;
        _data[6]+=scale.z; _data[7]+=scale.z; _data[8]+=scale.z;
    }

    void Matrix3::addScale(double sX, double sY, double sZ)
    {
        _data[0]+=sX; _data[1]+=sX; _data[2]+=sX;
        _data[3]+=sY; _data[4]+=sY; _data[5]+=sY;
        _data[6]+=sZ; _data[7]+=sZ; _data[8]+=sZ;
    }

    Vector3 Matrix3::getScale() const
    {
        Vector3 x(_data[0], _data[1], _data[2]);
        Vector3 y(_data[3], _data[4], _data[5]);
        Vector3 z(_data[6], _data[7], _data[8]);

        return Vector3(x.length(), y.length(), z.length());
    }

    void Matrix3::fromQuaternion(const Quaternion& rotationQuat)
    {
        *this = rotationQuat.toMatrix3();
    }

    Quaternion Matrix3::toQuaternion() const
    {
        Quaternion quat;
        quat.fromMatrix3( (*this) );
        return quat;
    }

    void Matrix3::toQuaternion(Quaternion &outQuaternion) const
    {
        outQuaternion.fromMatrix3( (*this) );
    }

    void Matrix3::fromEuler(const double& angleX, const double& angleY, const double& angleZ, RotationOrder order)
    {
        double cx, sx, cy, sy, cz, sz;

        cx = cos(angleX);
        sx = sin(angleX);
        cy = cos(angleY);
        sy = sin(angleY);
        cz = cos(angleZ);
        sz = sin(angleZ);


        Matrix3 XMat(
            1.0, 0.0, 0.0,
            0.0,  cx,  sx,
            0.0, -sx,  cx);

        Matrix3 YMat(
             cy, 0.0, -sy,
            0.0, 1.0, 0.0,
             sy, 0.0,  cy);

        Matrix3 ZMat(
             cz,  sz, 0.0,
            -sz,  cz, 0.0,
            0.0, 0.0, 1.0);

        switch (order)
        {
        case RotationOrder::XYZ :
            *this = XMat*(YMat*ZMat);
            break;
        case RotationOrder::XZY :
            *this = XMat*(ZMat*YMat);
            break;
        case RotationOrder::YXZ :
            *this = YMat*(XMat*ZMat);
            break;
        case RotationOrder::YZX :
            *this = YMat*(ZMat*XMat);
            break;
        case RotationOrder::ZXY :
            *this = ZMat*(XMat*YMat);
            break;
        case RotationOrder::ZYX : 
            *this = ZMat*(YMat*XMat);
            break;
        }
    }

    void Matrix3::fromEuler(const Euler &rotation, RotationOrder order)
    {   
        // ensure euler is radians
        Euler r = rotation.toRadians();
        fromEuler(r.x, r.y, r.z, order);
    }

    Euler Matrix3::toEuler(RotationOrder order) const
    {
        // ensure euler is radians
        Euler retAngles(Unit::radians);
        toEuler(retAngles, order);
        return retAngles;
    }

    void Matrix3::toEuler(Euler& euler, RotationOrder order) const
    {   
        // ensure euler is radians
        euler.setUnit(Unit::radians);

        switch (order)
        {
        case RotationOrder::XYZ :
            if (_data[6] < 1)
            {
                if (_data[6] > -1)
                {
                    // y_angle = gmath::asin(r02)
                    // x_angle = atan2(-r12,r22)
                    // z_angle = atan2(-r01,r00)
                    euler.y = gmath::asin(_data[6]);
                    euler.x = atan2(-_data[7], _data[8]);
                    euler.z = atan2(-_data[3], _data[0]);
                }
                else
                {
                    // y_angle = -gmath::PI/2
                    // z_angle - x_angle = atan2(r10,r11)
                    // WARNING.  The solution is not unique.  Choosing z_angle = 0.
                    euler.y = -gmath::HALFPI;
                    euler.x = -atan2(_data[1], _data[4]);
                    euler.z = 0;
                }
            }
            else
            {
                // y_angle = +gmath::PI/2
                // z_angle + x_angle = atan2(r10,r11)
                // WARNING.  The solutions is not unique.  Choosing z_angle = 0.
                euler.y = gmath::HALFPI;
                euler.x = atan2(_data[1], _data[4]);
                euler.z = 0;
            }

        case RotationOrder::XZY :
            if (_data[3] < 1)
            {
                if (_data[3] > -1)
                {
                    // z_angle = gmath::asin(-r01)
                    // x_angle = atan2(r21,r11)
                    // y_angle = atan2(r02,r00)
                    euler.z = gmath::asin(-_data[3]);
                    euler.x = atan2(_data[5], _data[4]);
                    euler.y = atan2(_data[6], _data[0]);
                }
                else
                {
                    // z_angle = +gmath::PI/2
                    // y_angle - x_angle = atan2(-r20,r22)
                    // WARNING.  The solution is not unique.  Choosing y_angle = 0.
                    euler.z = gmath::HALFPI;
                    euler.x = -atan2(-_data[2], _data[8]);
                    euler.y = 0;
                }
            }
            else
            {
                // z_angle = -gmath::PI/2
                // y_angle + x_angle = atan2(-r20,r22)
                // WARNING.  The solution is not unique.  Choosing y_angle = 0.
                euler.z = -gmath::HALFPI;
                euler.x = atan2(-_data[2], _data[8]);
                euler.y = 0;
            }

        case RotationOrder::YXZ :
            if (_data[7] < 1)
            {
                if (_data[7] > -1)
                {
                    // x_angle = gmath::asin(-r12)
                    // y_angle = atan2(r02,r22)
                    // z_angle = atan2(r10,r11)
                    euler.x = gmath::asin(-_data[7]);
                    euler.y = atan2(_data[2], _data[8]);
                    euler.z = atan2(_data[1], _data[4]);
                }
                else
                {
                    // x_angle = +gmath::PI/2
                    // z_angle - y_angle = atan2(-r01,r00)
                    // WARNING.  The solution is not unique.  Choosing z_angle = 0.
                    euler.x = gmath::HALFPI;
                    euler.y = -atan2(-_data[3], _data[0]);
                    euler.z = 0;
                }
            }
            else
            {
                // x_angle = -gmath::PI/2
                // z_angle + y_angle = atan2(-r01,r00)
                // WARNING.  The solution is not unique.  Choosing z_angle = 0.
                euler.x = -gmath::HALFPI;
                euler.y = atan2(-_data[3], _data[0]);
                euler.z = 0;
            }

        case RotationOrder::YZX :
            if (_data[1] < 1)
            {
                if (_data[1] > -1)
                {
                    // z_angle = gmath::asin(r10)
                    // y_angle = atan2(-r20,r00)
                    // x_angle = atan2(-r12,r11)
                    euler.z = gmath::asin(_data[1]);
                    euler.y = atan2(-_data[2], _data[0]);
                    euler.x = atan2(-_data[7], _data[4]);
                }
                else
                {
                    // z_angle = -gmath::PI/2
                    // x_angle - y_angle = atan2(r21,r22)
                    // WARNING.  The solution is not unique.  Choosing x_angle = 0.
                    euler.z = -gmath::HALFPI;
                    euler.y = -atan2(_data[5], _data[8]);
                    euler.x = 0;
                }
            }
            else
            {
                // z_angle = +gmath::PI/2
                // x_angle + y_angle = atan2(r21,r22)
                // WARNING.  The solution is not unique.  Choosing x_angle = 0.
                euler.z = gmath::HALFPI;
                euler.y = atan2(_data[5], _data[8]);
                euler.x = 0;
            }

        case RotationOrder::ZXY :
            if (_data[5] < 1)
            {
                if (_data[5] > -1)
                {
                    // x_angle = gmath::asin(r21)
                    // z_angle = atan2(-r01,r11)
                    // y_angle = atan2(-r20,r22)
                    euler.x = gmath::asin(_data[5]);
                    euler.z = atan2(-_data[3], _data[4]);
                    euler.y = atan2(-_data[2], _data[8]);
                }
                else
                {
                    // x_angle = -gmath::PI/2
                    // y_angle - z_angle = atan2(r02,r00)
                    // WARNING.  The solution is not unique.  Choosing y_angle = 0.
                    euler.x = -gmath::HALFPI;
                    euler.z = -atan2(_data[6], _data[0]);
                    euler.y = 0;
                }
            }
            else
            {
                // x_angle = +gmath::PI/2
                // y_angle + z_angle = atan2(r02,r00)
                // WARNING.  The solution is not unique.  Choosing y_angle = 0.
                euler.x = gmath::HALFPI;
                euler.z = atan2(_data[6], _data[0]);
                euler.y = 0;
            }

        case RotationOrder::ZYX :
            if (_data[2] < 1)
            {
                if (_data[2] > -1)
                {
                    // y_angle = gmath::asin(-r20)
                    // z_angle = atan2(r10,r00)
                    // x_angle = atan2(r21,r22)
                    euler.y = gmath::asin(-_data[2]);
                    euler.z = atan2(_data[1], _data[0]);
                    euler.x = atan2(_data[5], _data[8]);
                }
                else
                {
                    // y_angle = +gmath::PI/2
                    // x_angle - z_angle = atan2(r01,r02)
                    // WARNING.  The solution is not unique.  Choosing x_angle = 0.
                    euler.y = gmath::HALFPI;
                    euler.z = -atan2(_data[3], _data[6]);
                    euler.x = 0;
                }
            }
            else
            {
                // y_angle = -gmath::PI/2
                // x_angle + z_angle = atan2(-r01,-r02)
                // WARNING.  The solution is not unique.  Choosing x_angle = 0;
                euler.y = -gmath::HALFPI;
                euler.z = atan2(-_data[3], -_data[6]);
                euler.x = 0;
            }
        }
    }

    void Matrix3::fromVectorToVector(const Vector3 &fromVec, const Vector3 &toVec)
    {
        Vector3 x, u, v;
        double e = fromVec.dot(toVec);
        double f = fabs(e);

        if (f > 1.0-gmath::EPSILON) // "from" and "to" vectors parallel or almost parallel
        {
            double fx = fabs(fromVec.x);
            double fy = fabs(fromVec.y);
            double fz = fabs(fromVec.z);

            if (fx<fy)
            {
                if (fx<fz) {
                    x.set(1.0, 0.0, 0.0);
                }
                else {
                    x.set(0.0, 0.0, 1.0);
                }
            }
            else
            {
                if (fy<fz) {
                    x.set(0.0, 1.0, 0.0);
                }
                else {
                    x.set(0.0, 0.0, 1.0);
                }
            }

            u = x - fromVec;
            v = x - toVec;

            double c1 = 2.0/(u.dot(u));
            double c2 = 2.0/(v.dot(v));
            double c3 = v.dot(u*(c1*c2));

            double uvals[3];
            double vvals[3];
            uvals[0]=u.x; uvals[1]=u.y; uvals[2]=u.z;
            vvals[0]=v.x; vvals[1]=v.y; vvals[2]=v.z;
            for (unsigned int i=0; i<3; i++)
            {
                for (unsigned int j=0; j<3; j++)
                {
                    this->_data[i*3+j] =  - c1*uvals[i]*uvals[j] - c2*vvals[i]*vvals[j] + c3*vvals[i]*uvals[j];
                }
                this->_data[i*4] += 1.0;
            }
        }
        else  // the most common case, unless "from"="to", or "from"=-"to"
        {
            v = fromVec.cross(toVec);
            double h = 1.0/(1.0 + e);    // optimization by Gottfried Chen
            double hvx = h*v.x;
            double hvz = h*v.z;
            double hvxy = hvx*v.y;
            double hvxz = hvx*v.z;
            double hvyz = hvz*v.y;


            this->_data[0] = e + hvx*v.x;
            this->_data[1] = hvxy - v.z;
            this->_data[2] = hvxz + v.y;

            this->_data[3] = hvxy + v.z;
            this->_data[4] = e + h*v.y*v.y;
            this->_data[5] = hvyz - v.x;

            this->_data[6] = hvxz - v.y;
            this->_data[7] = hvyz + v.x;
            this->_data[8] = e + hvz*v.z;
        }
    }

    void Matrix3::lookAt(const Vector3 &pointAt, const Vector3 &normal, Axis primaryAxis, Axis secondaryAxis)
    {
        Vector3 primary, secondary, terziary;
        
        primary = pointAt;
        secondary = normal;
        primary.normalizeInPlace();
        secondary.normalizeInPlace();

        /*
        double f = fabs( primary.dot(secondary) );
        if (f > 1.0-gmath::EPSILON)
            throw GMathError("gMatrix4:\n\ttarget vector and up vector are perpendicular, impossible to create a matrix out of them.");
        */
        
        terziary = secondary.crossNormalize(primary);
        secondary = primary.crossNormalize(terziary);


        if ( ((int)primaryAxis<0) && ((int)secondaryAxis>0) ) 
        {
            primary  *= -1.0;
            terziary *= -1.0;
        }
        else if ( ((int)primaryAxis>0) && ((int)secondaryAxis<0) ) 
        {
            secondary *= -1.0;
            terziary  *= -1.0;
        }
        else if ( ((int)primaryAxis<0) && ((int)secondaryAxis<0) )
        {
            primary   *= -1.0;
            secondary *= -1.0;
        } 

        if (primaryAxis == Axis::POSX || primaryAxis == Axis::NEGX)
        {
            if (secondaryAxis == Axis::POSY || secondaryAxis == Axis::NEGY)
            {
                this->setAxisX(primary);
                this->setAxisY(secondary);
                this->setAxisZ(-terziary);
            }
            else if (secondaryAxis == Axis::POSZ || secondaryAxis == Axis::NEGZ)
            {
                this->setAxisX(primary);
                this->setAxisY(terziary);
                this->setAxisZ(secondary);
            }
        }
        else if (primaryAxis == Axis::POSY || primaryAxis == Axis::NEGY)
        {
            if (secondaryAxis == Axis::POSX || secondaryAxis == Axis::NEGX)
            {
                this->setAxisX(secondary);
                this->setAxisY(primary);
                this->setAxisZ(terziary);
            }
            else if (secondaryAxis == Axis::POSZ || secondaryAxis == Axis::NEGZ)
            {
                this->setAxisX(-terziary);
                this->setAxisY(primary);
                this->setAxisZ(secondary);
            }
        }
        else if (primaryAxis == Axis::POSZ || primaryAxis == Axis::NEGZ)
        {
            if (secondaryAxis == Axis::POSX || secondaryAxis == Axis::NEGX)
            {
                this->setAxisX(secondary);
                this->setAxisY(-terziary);
                this->setAxisZ(primary);
            }
            else if (secondaryAxis == Axis::POSY || secondaryAxis == Axis::NEGY)
            {
                this->setAxisX(terziary);
                this->setAxisY(secondary);
                this->setAxisZ(primary);
            }
        }
    }

    Matrix3 Matrix3::createLookAt(const Vector3 &pointAt, const Vector3 &normal, Axis primaryAxis, Axis secondaryAxis)
    {
        Matrix3 mat;
        mat.lookAt(pointAt, normal, primaryAxis, secondaryAxis);
        return mat;
    }

    void Matrix3::fromAxisAngle(const Vector3 &axis, double angle)
    {
        double sqr_a = axis.x*axis.x;
        double sqr_b = axis.y*axis.y;
        double sqr_c = axis.z*axis.z;
        double len2  = sqr_a+sqr_b+sqr_c;

        double k2    = cos(angle);
        double k1    = (1.0-k2)/len2;
        double k3    = sin(angle)/sqrt(len2);
        double k1ab  = k1*axis.x*axis.y;
        double k1ac  = k1*axis.x*axis.z;
        double k1bc  = k1*axis.y*axis.z;
        double k3a   = k3*axis.x;
        double k3b   = k3*axis.y;
        double k3c   = k3*axis.z;

        _data[0] = k1*sqr_a+k2; _data[1] = k1ab+k3c;    _data[2] = k1ac-k3b;
        _data[3] = k1ab-k3c;    _data[4] = k1*sqr_b+k2; _data[5] = k1bc+k3a;
        _data[6] = k1ac+k3b;    _data[7] = k1bc-k3a;    _data[8] = k1*sqr_c+k2;
    }

    std::string Matrix3::toString() const
    {
        std::stringstream oss;
        oss << "gmath::Matrix3(" << _data[0] << ", " << _data[1] << ", " << _data[2] << std::endl;
        oss << "               " << _data[3] << ", " << _data[4] << ", " << _data[5] << std::endl;
        oss << "               " << _data[6] << ", " << _data[7] << ", " << _data[8] << ");";

        return oss.str();
    }


    const Matrix3 Matrix3::IDENTITY = Matrix3(1.0, 0.0, 0.0,
                                              0.0, 1.0, 0.0,
                                              0.0, 0.0, 1.0);
}
