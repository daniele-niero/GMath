#include "gmMatrix4.h"
#include "gmQuaternion.h"

using namespace std;


namespace gmath
{
    /*------ Constructors ------*/

    Matrix4::Matrix4()
    {
        _data[0]=1.0;  _data[1]=0.0;  _data[2]=0.0;  _data[3]=0.0;
        _data[4]=0.0;  _data[5]=1.0;  _data[6]=0.0;  _data[7]=0.0;
        _data[8]=0.0;  _data[9]=0.0; _data[10]=1.0; _data[11]=0.0;
        _data[12]=0.0; _data[13]=0.0; _data[14]=0.0; _data[15]=1.0;
    }

    Matrix4::Matrix4(
        double xx, double xy, double xz, double xw,
        double yx, double yy, double yz, double yw,
        double zx, double zy, double zz, double zw,
        double px, double py, double pz, double pw)
    {
        _data[0]=xx;  _data[1]=xy;  _data[2]=xz;  _data[3]=xw;
        _data[4]=yx;  _data[5]=yy;  _data[6]=yz;  _data[7]=yw;
        _data[8]=zx;  _data[9]=zy;  _data[10]=zz; _data[11]=zw;
        _data[12]=px; _data[13]=py; _data[14]=pz; _data[15]=pw;
    }

    Matrix4::Matrix4(const Matrix4 & other)
    {
        memcpy(_data, other._data, 16*sizeof(double));
    }

    Matrix4::Matrix4(
        const Vector4 &row0,
        const Vector4 &row1,
        const Vector4 &row2,
        const Vector4 &row3)
    {
        memcpy(&_data[0],  row0.data(), 4*sizeof(double));
        memcpy(&_data[4],  row1.data(), 4*sizeof(double));
        memcpy(&_data[8],  row2.data(), 4*sizeof(double));
        memcpy(&_data[12], row3.data(), 4*sizeof(double));
    }

    Matrix4::Matrix4(
        const Vector3 &row0,
        const Vector3 &row1,
        const Vector3 &row2,
        const Vector3 &row3)
    {
        memcpy(&_data[0],  row0.data(), 3*sizeof(double));
        memcpy(&_data[4],  row1.data(), 3*sizeof(double));
        memcpy(&_data[8],  row2.data(), 3*sizeof(double));
        memcpy(&_data[12], row3.data(), 3*sizeof(double));
        _data[3]=0.0; _data[7]=0.0; _data[11]=0.0; _data[15]=1.0;
    }

    Matrix4::Matrix4(
        const Vector3 &row0,
        const Vector3 &row1,
        const Vector3 &row2)
    {
        memcpy(&_data[0],  row0.data(), 3*sizeof(double));
        memcpy(&_data[4],  row1.data(), 3*sizeof(double));
        memcpy(&_data[8],  row2.data(), 3*sizeof(double));
        _data[3]=0.0; _data[7]=0.0; _data[11]=0.0;
        _data[12]=0.0; _data[13]=0.0; _data[14]=0.0; _data[15]=1.0;
    }

    Matrix4::Matrix4(const Quaternion &quat)
    {
        quat.setMatrix4((*this));
    }

    Matrix4::Matrix4(const Quaternion &quat, const Vector3 &pos)
    {
        quat.setMatrix4((*this));
        this->setPosition(pos);
    }

    Matrix4::Matrix4(const double* values)
    {
        set(values);
    }

    Matrix4::Matrix4(const std::vector<double>& values)
    {
        set(values);
    }

    /*------ Coordinates access ------*/

    double* Matrix4::data()
    {
        return &_data[0];
    }

    const double* Matrix4::data() const
    {
        return &_data[0];
    }

    double Matrix4::operator[] (int i) const
    {
        if (i>=0 && i<16)
        {
            return this->_data[i];
        }
        else {
            throw out_of_range("gmath::Matrix3: index out of range");
        }
    }

    double& Matrix4::operator[] (int i)
    {
        if (i>=0 && i<16)
        {
            return this->_data[i];
        }
        else {
            throw out_of_range("gmath::Vector4: index out of range");
        }
    }

    double Matrix4::operator() (int row, int col) const
    {
        if (row>=0 && row<4 && col>=0 && col<4)
        {
            return this->_data[row*4+col];
        }
        else
        {
            throw out_of_range("gmath::Matrix4: row or column index out of range");
        }
    }

    double &Matrix4::operator() (int row, int col)
    {
        if (row>=0 && row<4 && col>=0 && col<4)
        {
            return this->_data[row*4+col];
        }
        else
        {
            throw out_of_range("gmath::Matrix4: row or column index out of range");
        }
    }

    /*------ Arithmetic operations ------*/

    Matrix4 Matrix4::operator + (const double &value) const
    {
        Matrix4 retMatrix(
            _data[0]+value,  _data[1]+value,  _data[2]+value,  _data[3]+value,
            _data[4]+value,  _data[5]+value,  _data[6]+value,  _data[7]+value,
            _data[8]+value,  _data[9]+value,  _data[10]+value, _data[11]+value,
            _data[12]+value, _data[13]+value, _data[14]+value, _data[15]+value
            );
        return retMatrix;
    }

    Matrix4 Matrix4::operator + (const Matrix4 &other) const
    {
        const double* b = other.data();
        Matrix4 retMatrix(
            _data[0]+b[0],   _data[1]+b[1],   _data[2]+b[2],   _data[3]+b[3],
            _data[4]+b[4],   _data[5]+b[5],   _data[6]+b[6],   _data[7]+b[7],
            _data[8]+b[8],   _data[9]+b[9],   _data[10]+b[10], _data[11]+b[11],
            _data[12]+b[12], _data[13]+b[13], _data[14]+b[14], _data[15]+b[15]
            );
        return retMatrix;
    }

    Matrix4 Matrix4::operator - (const double &value) const
    {
        Matrix4 retMatrix(
            _data[0]-value,  _data[1]-value,  _data[2]-value,  _data[3]-value,
            _data[4]-value,  _data[5]-value,  _data[6]-value,  _data[7]-value,
            _data[8]-value,  _data[9]-value,  _data[10]-value, _data[11]-value,
            _data[12]-value, _data[13]-value, _data[14]-value, _data[15]-value
            );
        return retMatrix;
    }

    Matrix4 Matrix4::operator - (const Matrix4 &other) const
    {
        const double* b = other.data();
        Matrix4 retMatrix(
            _data[0]-b[0],   _data[1]-b[1],   _data[2]-b[2],   _data[3]-b[3],
            _data[4]-b[4],   _data[5]-b[5],   _data[6]-b[6],   _data[7]-b[7],
            _data[8]-b[8],   _data[9]-b[9],   _data[10]-b[10], _data[11]-b[11],
            _data[12]-b[12], _data[13]-b[13], _data[14]-b[14], _data[15]-b[15]
            );
        return retMatrix;
    }

    Matrix4 Matrix4::operator / (const double &value) const
    {
        Matrix4 retMatrix(
            _data[0]/value,  _data[1]/value,  _data[2]/value,  _data[3]/value,
            _data[4]/value,  _data[5]/value,  _data[6]/value,  _data[7]/value,
            _data[8]/value,  _data[9]/value,  _data[10]/value, _data[11]/value,
            _data[12]/value, _data[13]/value, _data[14]/value, _data[15]/value
            );
        return retMatrix;
    }

    Matrix4 Matrix4::operator * (const double &value) const
    {
        Matrix4 retMatrix(
            _data[0]*value,  _data[1]*value,  _data[2]*value,  _data[3]*value,
            _data[4]*value,  _data[5]*value,  _data[6]*value,  _data[7]*value,
            _data[8]*value,  _data[9]*value,  _data[10]*value, _data[11]*value,
            _data[12]*value, _data[13]*value, _data[14]*value, _data[15]*value
            );
        return retMatrix;
    }

    Matrix4 Matrix4::operator * (const Matrix4 &other) const
    {
        const double* b = other.data();
        Matrix4 retMatrix(
            _data[0]*b[0] + _data[1]*b[4] + _data[2]*b[8]  + _data[3]*b[12],
            _data[0]*b[1] + _data[1]*b[5] + _data[2]*b[9]  + _data[3]*b[13],
            _data[0]*b[2] + _data[1]*b[6] + _data[2]*b[10] + _data[3]*b[14],
            _data[0]*b[3] + _data[1]*b[7] + _data[2]*b[11] + _data[3]*b[15],

            _data[4]*b[0] + _data[5]*b[4] + _data[6]*b[8]  + _data[7]*b[12],
            _data[4]*b[1] + _data[5]*b[5] + _data[6]*b[9]  + _data[7]*b[13],
            _data[4]*b[2] + _data[5]*b[6] + _data[6]*b[10] + _data[7]*b[14],
            _data[4]*b[3] + _data[5]*b[7] + _data[6]*b[11] + _data[7]*b[15],

            _data[8]*b[0] + _data[9]*b[4] + _data[10]*b[8]  + _data[11]*b[12],
            _data[8]*b[1] + _data[9]*b[5] + _data[10]*b[9]  + _data[11]*b[13],
            _data[8]*b[2] + _data[9]*b[6] + _data[10]*b[10] + _data[11]*b[14],
            _data[8]*b[3] + _data[9]*b[7] + _data[10]*b[11] + _data[11]*b[15],

            _data[12]*b[0] + _data[13]*b[4] + _data[14]*b[8]  + _data[15]*b[12],
            _data[12]*b[1] + _data[13]*b[5] + _data[14]*b[9]  + _data[15]*b[13],
            _data[12]*b[2] + _data[13]*b[6] + _data[14]*b[10] + _data[15]*b[14],
            _data[12]*b[3] + _data[13]*b[7] + _data[14]*b[11] + _data[15]*b[15]
            );
        return retMatrix;
    }

    /*------ Arithmetic updates ------*/

    Matrix4& Matrix4::operator += (const double &value)
    {
         _data[0]+=value;  _data[1]+=value;  _data[2]+=value;  _data[3]+=value;
         _data[4]+=value;  _data[5]+=value;  _data[6]+=value;  _data[7]+=value;
         _data[8]+=value;  _data[9]+=value; _data[10]+=value; _data[11]+=value;
        _data[12]+=value; _data[13]+=value; _data[14]+=value; _data[15]+=value;
        return *this;
    }

    Matrix4& Matrix4::operator += (const Matrix4 &other)
    {
        const double* b = other.data();

         _data[0]+=b[0];   _data[1]+=b[1];   _data[2]+=b[2];   _data[3]+=b[3];
         _data[4]+=b[4];   _data[5]+=b[5];   _data[6]+=b[6];   _data[7]+=b[7];
         _data[8]+=b[8];   _data[9]+=b[9];  _data[10]+=b[10]; _data[11]+=b[11];
        _data[12]+=b[12]; _data[13]+=b[13]; _data[14]+=b[14]; _data[15]+=b[15];
        return *this;
    }

    Matrix4& Matrix4::operator -= (const double &value)
    {
         _data[0]-=value;  _data[1]-=value;  _data[2]-=value;  _data[3]-=value;
         _data[4]-=value;  _data[5]-=value;  _data[6]-=value;  _data[7]-=value;
         _data[8]-=value;  _data[9]-=value; _data[10]-=value; _data[11]-=value;
        _data[12]-=value; _data[13]-=value; _data[14]-=value; _data[15]-=value;
        return *this;
    }

    Matrix4& Matrix4::operator -= (const Matrix4 &other)
    {
        const double* b = other.data();

         _data[0]-=b[0];   _data[1]-=b[1];   _data[2]-=b[2];   _data[3]-=b[3];
         _data[4]-=b[4];   _data[5]-=b[5];   _data[6]-=b[6];   _data[7]-=b[7];
         _data[8]-=b[8];   _data[9]-=b[9];  _data[10]-=b[10]; _data[11]-=b[11];
        _data[12]-=b[12]; _data[13]-=b[13]; _data[14]-=b[14]; _data[15]-=b[15];
        return *this;
    }

    Matrix4& Matrix4::operator /= (const double &value)
    {
         _data[0]/=value;  _data[1]/=value;  _data[2]/=value;  _data[3]/=value;
         _data[4]/=value;  _data[5]/=value;  _data[6]/=value;  _data[7]/=value;
         _data[8]/=value;  _data[9]/=value; _data[10]/=value; _data[11]/=value;
        _data[12]/=value; _data[13]/=value; _data[14]/=value; _data[15]/=value;
        return *this;
    }

    Matrix4& Matrix4::operator *= (const double &value)
    {
         _data[0]*=value;  _data[1]*=value;  _data[2]*=value;  _data[3]*=value;
         _data[4]*=value;  _data[5]*=value;  _data[6]*=value;  _data[7]*=value;
         _data[8]*=value;  _data[9]*=value; _data[10]*=value; _data[11]*=value;
        _data[12]*=value; _data[13]*=value; _data[14]*=value; _data[15]*=value;
        return *this;
    }

    Matrix4& Matrix4::operator *= (const Matrix4 &other)
    {
        const double* b = other.data();
        set(
            _data[0]*b[0] + _data[1]*b[4] + _data[2]*b[8]  + _data[3]*b[12],
            _data[0]*b[1] + _data[1]*b[5] + _data[2]*b[9]  + _data[3]*b[13],
            _data[0]*b[2] + _data[1]*b[6] + _data[2]*b[10] + _data[3]*b[14],
            _data[0]*b[3] + _data[1]*b[7] + _data[2]*b[11] + _data[3]*b[15],

            _data[4]*b[0] + _data[5]*b[4] + _data[6]*b[8]  + _data[7]*b[12],
            _data[4]*b[1] + _data[5]*b[5] + _data[6]*b[9]  + _data[7]*b[13],
            _data[4]*b[2] + _data[5]*b[6] + _data[6]*b[10] + _data[7]*b[14],
            _data[4]*b[3] + _data[5]*b[7] + _data[6]*b[11] + _data[7]*b[15],

            _data[8]*b[0] + _data[9]*b[4] + _data[10]*b[8]  + _data[11]*b[12],
            _data[8]*b[1] + _data[9]*b[5] + _data[10]*b[9]  +  _data[11]*b[13],
            _data[8]*b[2] + _data[9]*b[6] + _data[10]*b[10] + _data[11]*b[14],
            _data[8]*b[3] + _data[9]*b[7] + _data[10]*b[11] + _data[11]*b[15],

            _data[12]*b[0] + _data[13]*b[4] + _data[14]*b[8]  + _data[15]*b[12],
            _data[12]*b[1] + _data[13]*b[5] + _data[14]*b[9]  + _data[15]*b[13],
            _data[12]*b[2] + _data[13]*b[6] + _data[14]*b[10] + _data[15]*b[14],
            _data[12]*b[3] + _data[13]*b[7] + _data[14]*b[11] + _data[15]*b[15]
            );
        return *this;
    }

    /*------ Comparisons ------*/

    bool Matrix4::operator == (const Matrix4 &other) const
    {
        const double* b = &other._data[0];
        double e = gmath::EPSILON;
        return (fabs(_data[0]-b[0])<e && fabs(_data[1]-b[1])<e && fabs(_data[2]-b[2])<e && fabs(_data[3]-b[3])<e && 
                fabs(_data[4]-b[4])<e && fabs(_data[5]-b[5])<e && fabs(_data[6]-b[6])<e && fabs(_data[7]-b[7])<e && 
                fabs(_data[8]-b[8])<e && fabs(_data[9]-b[9])<e && fabs(_data[10]-b[10])<e && fabs(_data[11]-b[11])<e &&
                fabs(_data[12]-b[12])<e && fabs(_data[13]-b[13])<e && fabs(_data[14]-b[14])<e && fabs(_data[15]-b[15])<e);
    }

    bool Matrix4::operator != (const Matrix4 &other) const
    {
        const double* b = &other._data[0];
        double e = gmath::EPSILON;
        return (fabs(_data[0]-b[0])>e || fabs(_data[1]-b[1])>e || fabs(_data[2]-b[2])>e || fabs(_data[3]-b[3])>e ||
                fabs(_data[4]-b[4])>e || fabs(_data[5]-b[5])>e || fabs(_data[6]-b[6])>e || fabs(_data[7]-b[7])>e || 
                fabs(_data[8]-b[8])>e || fabs(_data[9]-b[9])>e || fabs(_data[10]-b[10])>e || fabs(_data[11]-b[11])>e ||
                fabs(_data[12]-b[12])>e || fabs(_data[13]-b[13])>e || fabs(_data[14]-b[14])>e || fabs(_data[15]-b[15])>e);
    }

    /*------ Assignment ------*/

    void Matrix4::operator = (const Matrix4 &other)
    {
        _data[ 0] = other._data[0];
        _data[ 1] = other._data[1];
        _data[ 2] = other._data[2];
        _data[ 3] = other._data[3];
        _data[ 4] = other._data[4];
        _data[ 5] = other._data[5];
        _data[ 6] = other._data[6];
        _data[ 7] = other._data[7];
        _data[ 8] = other._data[8];
        _data[ 9] = other._data[9];
        _data[10] = other._data[10];
        _data[11] = other._data[11];
        _data[12] = other._data[12];
        _data[13] = other._data[13];
        _data[14] = other._data[14];
        _data[15] = other._data[15];
    }
    /*------ Methods ------*/

    void Matrix4::setToIdentity()
    {
        _data[0] =1;  _data[1]=0;  _data[2]=0;  _data[3]=0;
        _data[4] =0;  _data[5]=1;  _data[6]=0;  _data[7]=0;
        _data[8] =0;  _data[9]=0; _data[10]=1; _data[11]=0;
        _data[12]=0; _data[13]=0; _data[14]=0; _data[15]=1;
    }

    void Matrix4::set(
        double xx, double xy, double xz, double xw,
        double yx, double yy, double yz, double yw,
        double zx, double zy, double zz, double zw,
        double px, double py, double pz, double pw)
    {
        _data[0]=xx;  _data[1]=xy;  _data[2]=xz;  _data[3]=xw;
        _data[4]=yx;  _data[5]=yy;  _data[6]=yz;  _data[7]=yw;
        _data[8]=zx;  _data[9]=zy;  _data[10]=zz; _data[11]=zw;
        _data[12]=px; _data[13]=py; _data[14]=pz; _data[15]=pw;
    }

    void Matrix4::set(const double* values)
    {
        memcpy(_data, values, 16*sizeof(double));
    }

    void Matrix4::set(const std::vector<double>& values)
    {
        if (values.size()!=16) {
            throw out_of_range("gmath::Matrix4: values must be of 16 elments");
        }

        memcpy(_data, values.data(), 16*sizeof(double));
    }

    Vector3 Matrix4::getRow(unsigned int i) const
    {
        if (i>3)
        {
            throw out_of_range("gmath::Matrix4: index out of range");
        }
        return Vector3( _data[i*4], _data[i*4+1], _data[i*4+2] );
    }

    Vector4 Matrix4::getRow2(unsigned int i) const
    {
        if (i>3)
        {
            throw out_of_range("gmath::Matrix4: index out of range");
        }
        return Vector4( _data[i*4], _data[i*4+1], _data[i*4+2], _data[i*4+3] );
    }

    void Matrix4::setRow(unsigned int i, const Vector3 &vec)
    {
        if (i>3)
        {
            throw out_of_range("gmath::Matrix4: index out of range");
        }
        _data[i*4]   = vec.x;
        _data[i*4+1] = vec.y;
        _data[i*4+2] = vec.z;
    }

    void Matrix4::setRow(unsigned int i, const Vector4 &vec)
    {
        if (i>4)
        {
            throw out_of_range("gmath::Matrix4: index out of range");
        }
        _data[i*4]   = vec.x;
        _data[i*4+1] = vec.y;
        _data[i*4+2] = vec.z;
        _data[i*4+3] = vec.w;
    }

    Vector3 Matrix4::getAxisX() const
    {
        return getRow(0);
    }

    Vector3 Matrix4::getAxisY() const
    {
        return getRow(1);
    }

    Vector3 Matrix4::getAxisZ() const
    {
        return getRow(2);
    }

    void Matrix4::setAxisX(const Vector3 &vec)
    {
        setRow(0, vec);
    }

    void Matrix4::setAxisY(const Vector3 &vec)
    {
        setRow(1, vec);
    }

    void Matrix4::setAxisZ(const Vector3 &vec)
    {
        setRow(2, vec);
    }

    void Matrix4::setPosition(const Vector3 &pos)
    {
        _data[12] = pos.x;
        _data[13] = pos.y;
        _data[14] = pos.z;
    }

    void Matrix4::setPosition(double inX, double inY, double inZ)
    {
        _data[12] = inX;
        _data[13] = inY;
        _data[14] = inZ;
    }

    void Matrix4::addPosition(const Vector3 &pos)
    {
        _data[12] += pos.x;
        _data[13] += pos.y;
        _data[14] += pos.z;
    }

    void Matrix4::addPosition(double inX, double inY, double inZ)
    {
        _data[12] += inX;
        _data[13] += inY;
        _data[14] += inZ;
    }

    void Matrix4::translate (const Vector3 &pos)
    {
        _data[12] += pos.x * _data[0] + pos.y * _data[4] + pos.z * _data[8];
        _data[13] += pos.x * _data[1] + pos.y * _data[5] + pos.z * _data[9];
        _data[14] += pos.x * _data[2] + pos.y * _data[6] + pos.z * _data[10];
    }

    void Matrix4::translate(double inX, double inY, double inZ)
    {
        _data[12] += inX * _data[0] + inY * _data[4] + inZ * _data[8];
        _data[13] += inX * _data[1] + inY * _data[5] + inZ * _data[9];
        _data[14] += inX * _data[2] + inY * _data[6] + inZ * _data[10];
    }

    Vector3 Matrix4::getPosition() const
    {
        return Vector3( _data[12], _data[13], _data[14] );
    }

    void Matrix4::setRotation(const Matrix3& rotationMatrix)
    {
        const double* rot = &rotationMatrix.data()[0];
        _data[0]=rot[0];  _data[1]=rot[1];  _data[2]=rot[2];  
        _data[4]=rot[3];  _data[5]=rot[4];  _data[6]=rot[5];
        _data[8]=rot[6];  _data[9]=rot[7];  _data[10]=rot[8];
    }

    void Matrix4::setRotation(const Quaternion& rotationQuat)
    {
        double xx = 2.0 * rotationQuat.x * rotationQuat.x;
        double yy = 2.0 * rotationQuat.y * rotationQuat.y;
        double zz = 2.0 * rotationQuat.z * rotationQuat.z;
        double xy = 2.0 * rotationQuat.x * rotationQuat.y;
        double zw = 2.0 * rotationQuat.z * rotationQuat.w;
        double xz = 2.0 * rotationQuat.x * rotationQuat.z;
        double yw = 2.0 * rotationQuat.y * rotationQuat.w;
        double yz = 2.0 * rotationQuat.y * rotationQuat.z;
        double xw = 2.0 * rotationQuat.x * rotationQuat.w;
        
        _data[0]=1.0-yy-zz; _data[1]=xy+zw;     _data[2]=xz-yw;
        _data[4]=xy-zw;     _data[5]=1.0-xx-zz; _data[6]=yz+xw;
        _data[8]=xz+yw;     _data[9]=yz-xw;     _data[10]=1.0-xx-yy;

    }

    void Matrix4::setRotation(double angleX, double angleY, double angleZ, RotationOrder order)
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
            this->setRotation( XMat*(YMat*ZMat) );
            break;
        case RotationOrder::XZY :
            this->setRotation( XMat*(ZMat*YMat) );
            break;
        case RotationOrder::YXZ :
            this->setRotation( YMat*(XMat*ZMat) );
            break;
        case RotationOrder::YZX :
            this->setRotation( YMat*(ZMat*XMat) );
            break;
        case RotationOrder::ZXY :
            this->setRotation( ZMat*(XMat*YMat) );
            break;
        case RotationOrder::ZYX :
            this->setRotation( ZMat*(YMat*XMat) );
            break;
        }
    }

    void Matrix4::setRotation(const Euler &rotation, RotationOrder order)
    {
        // ensure euler is radians
        Euler r = rotation.toRadians();
        this->setRotation(r.x, r.y, r.z, order);
    }

    Vector3 Matrix4::getScale() const
    {
        Vector3 x(_data[0], _data[1], _data[2]);
        Vector3 y(_data[4], _data[5], _data[6]);
        Vector3 z(_data[8], _data[9], _data[10]);

        return Vector3(x.length(), y.length(), z.length());
    }

    void Matrix4::setScale(const Vector3 &scale)
    {
        Vector3 x(_data[0], _data[1], _data[2]);
        Vector3 y(_data[4], _data[5], _data[6]);
        Vector3 z(_data[8], _data[9], _data[10]);
        x.normalizeInPlace();
        y.normalizeInPlace();
        z.normalizeInPlace();
        x *= scale.x;
        y *= scale.y;
        z *= scale.z;

        _data[0]=x.x; _data[1]=x.y; _data[2]=x.z;
        _data[4]=y.x; _data[5]=y.y; _data[6]=y.z;
        _data[8]=z.x; _data[9]=z.y; _data[10]=z.z;
    }

    void Matrix4::setScale(double sX, double sY, double sZ)
    {
        Vector3 x(_data[0], _data[1], _data[2]);
        Vector3 y(_data[4], _data[5], _data[6]);
        Vector3 z(_data[8], _data[9], _data[10]);
        x.normalizeInPlace();
        y.normalizeInPlace();
        z.normalizeInPlace();
        x *= sX;
        y *= sY;
        z *= sZ;

        _data[0]=x.x; _data[1]=x.y; _data[2]=x.z;
        _data[4]=y.x; _data[5]=y.y; _data[6]=y.z;
        _data[8]=z.x; _data[9]=z.y; _data[10]=z.z;
    }

    void Matrix4::addScale(const Vector3 &scale)
    {

        _data[0]+=scale.x; _data[1]+=scale.x; _data[2]+=scale.x;
        _data[4]+=scale.y; _data[5]+=scale.y; _data[6]+=scale.y;
        _data[8]+=scale.z; _data[9]+=scale.z; _data[10]+=scale.z;
    }

    void Matrix4::addScale(double sX, double sY, double sZ)
    {
        _data[0]+=sX; _data[1]+=sX; _data[2]+=sX;
        _data[4]+=sY; _data[5]+=sY; _data[6]+=sY;
        _data[8]+=sZ; _data[9]+=sZ; _data[10]+=sZ;
    }

    Matrix3 Matrix4::toMatrix3() const
    {
        Matrix3 rot(
            _data[0],  _data[1],  _data[2],  
            _data[4],  _data[5],  _data[6],
            _data[8],  _data[9],  _data[10]);
        return rot;
    }

    Quaternion Matrix4::toQuaternion() const
    {
        Quaternion quat;
        quat.fromMatrix4( (*this) );
        return quat;
    }

    Euler Matrix4::toEuler(RotationOrder order) const
    {
        Euler retEuler(Unit::radians);
        this->toEuler(retEuler, order);
        return retEuler;
    }

    void Matrix4::toMatrix3(Matrix3 &outMatrix3) const
    {
        outMatrix3.set(
            _data[0], _data[1], _data[2],  
            _data[4], _data[5], _data[6],
            _data[8], _data[9], _data[10]);
    }

    void Matrix4::toQuaternion(Quaternion &outQuaternion) const
    {
        outQuaternion.fromMatrix4( (*this) );
    }

    void Matrix4::toEuler(Euler& eulerAngles, RotationOrder order) const
    {
        this->toMatrix3().toEuler(eulerAngles, order);
    }

    void Matrix4::fromMatrix3(const Matrix3 &inMat3)
    {
        memcpy(&_data[0],  &inMat3.data()[0], 3*sizeof(double));
        memcpy(&_data[4],  &inMat3.data()[3], 3*sizeof(double));
        memcpy(&_data[8],  &inMat3.data()[6], 3*sizeof(double));
    }

    void Matrix4::fromQuaternion(const Quaternion &inQuat)
    {
        *this = inQuat.toMatrix4();
    }

    void Matrix4::fromEuler(const double &angleX, const double &angleY, const double &angleZ, RotationOrder order)
    {
        Matrix3 rotationMat;
        rotationMat.fromEuler(angleX, angleY, angleZ, order);
        this->fromMatrix3(rotationMat);
    }

    void Matrix4::fromEuler(const Euler &rotation, RotationOrder order)
    {
        // ensure euler is radians
        Euler r = rotation.toRadians();
        fromEuler(r.x, r.y, r.z, order);
    }

    Vector3 Matrix4::rotateVector(const Vector3 &vec) const
    {
        Vector3 retVec(
            _data[0] * vec.x + _data[1] * vec.y + _data[2]  * vec.z,
            _data[4] * vec.x + _data[5] * vec.y + _data[6]  * vec.z,
            _data[8] * vec.x + _data[9] * vec.y + _data[10] * vec.z
            );
        return retVec;
    }

    Matrix4 Matrix4::transpose() const
    {
        return Matrix4(
            _data[0], _data[4], _data[ 8], _data[12],
            _data[1], _data[5], _data[ 9], _data[13],
            _data[2], _data[6], _data[10], _data[14],
            _data[3], _data[7], _data[11], _data[15] );
    }

    void Matrix4::transposeInPlace()
    {
        set(
            _data[0], _data[4], _data[ 8], _data[12],
            _data[1], _data[5], _data[ 9], _data[13],
            _data[2], _data[6], _data[10], _data[14],
            _data[3], _data[7], _data[11], _data[15] );
    }

    double Matrix4::determinant() const
    {
        double a0 = _data[ 0]*_data[ 5] - _data[ 1]*_data[ 4];
        double a1 = _data[ 0]*_data[ 6] - _data[ 2]*_data[ 4];
        double a2 = _data[ 0]*_data[ 7] - _data[ 3]*_data[ 4];
        double a3 = _data[ 1]*_data[ 6] - _data[ 2]*_data[ 5];
        double a4 = _data[ 1]*_data[ 7] - _data[ 3]*_data[ 5];
        double a5 = _data[ 2]*_data[ 7] - _data[ 3]*_data[ 6];
        double b0 = _data[ 8]*_data[13] - _data[ 9]*_data[12];
        double b1 = _data[ 8]*_data[14] - _data[10]*_data[12];
        double b2 = _data[ 8]*_data[15] - _data[11]*_data[12];
        double b3 = _data[ 9]*_data[14] - _data[10]*_data[13];
        double b4 = _data[ 9]*_data[15] - _data[11]*_data[13];
        double b5 = _data[10]*_data[15] - _data[11]*_data[14];
        double det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
        return det;
    }

    Matrix4 Matrix4::inverse() const
    {
        Matrix4 inverseMat;

        double a0 = _data[ 0]*_data[ 5] - _data[ 1]*_data[ 4];
        double a1 = _data[ 0]*_data[ 6] - _data[ 2]*_data[ 4];
        double a2 = _data[ 0]*_data[ 7] - _data[ 3]*_data[ 4];
        double a3 = _data[ 1]*_data[ 6] - _data[ 2]*_data[ 5];
        double a4 = _data[ 1]*_data[ 7] - _data[ 3]*_data[ 5];
        double a5 = _data[ 2]*_data[ 7] - _data[ 3]*_data[ 6];
        double b0 = _data[ 8]*_data[13] - _data[ 9]*_data[12];
        double b1 = _data[ 8]*_data[14] - _data[10]*_data[12];
        double b2 = _data[ 8]*_data[15] - _data[11]*_data[12];
        double b3 = _data[ 9]*_data[14] - _data[10]*_data[13];
        double b4 = _data[ 9]*_data[15] - _data[11]*_data[13];
        double b5 = _data[10]*_data[15] - _data[11]*_data[14];
        double det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;

        if (fabs(det) > gmath::EPSILON)
        {
            inverseMat._data[ 0] = + _data[ 5]*b5 - _data[ 6]*b4 + _data[ 7]*b3;
            inverseMat._data[ 4] = - _data[ 4]*b5 + _data[ 6]*b2 - _data[ 7]*b1;
            inverseMat._data[ 8] = + _data[ 4]*b4 - _data[ 5]*b2 + _data[ 7]*b0;
            inverseMat._data[12] = - _data[ 4]*b3 + _data[ 5]*b1 - _data[ 6]*b0;
            inverseMat._data[ 1] = - _data[ 1]*b5 + _data[ 2]*b4 - _data[ 3]*b3;
            inverseMat._data[ 5] = + _data[ 0]*b5 - _data[ 2]*b2 + _data[ 3]*b1;
            inverseMat._data[ 9] = - _data[ 0]*b4 + _data[ 1]*b2 - _data[ 3]*b0;
            inverseMat._data[13] = + _data[ 0]*b3 - _data[ 1]*b1 + _data[ 2]*b0;
            inverseMat._data[ 2] = + _data[13]*a5 - _data[14]*a4 + _data[15]*a3;
            inverseMat._data[ 6] = - _data[12]*a5 + _data[14]*a2 - _data[15]*a1;
            inverseMat._data[10] = + _data[12]*a4 - _data[13]*a2 + _data[15]*a0;
            inverseMat._data[14] = - _data[12]*a3 + _data[13]*a1 - _data[14]*a0;
            inverseMat._data[ 3] = - _data[ 9]*a5 + _data[10]*a4 - _data[11]*a3;
            inverseMat._data[ 7] = + _data[ 8]*a5 - _data[10]*a2 + _data[11]*a1;
            inverseMat._data[11] = - _data[ 8]*a4 + _data[ 9]*a2 - _data[11]*a0;
            inverseMat._data[15] = + _data[ 8]*a3 - _data[ 9]*a1 + _data[10]*a0;

            double invDet = (1)/det;
            inverseMat._data[ 0] *= invDet;
            inverseMat._data[ 1] *= invDet;
            inverseMat._data[ 2] *= invDet;
            inverseMat._data[ 3] *= invDet;
            inverseMat._data[ 4] *= invDet;
            inverseMat._data[ 5] *= invDet;
            inverseMat._data[ 6] *= invDet;
            inverseMat._data[ 7] *= invDet;
            inverseMat._data[ 8] *= invDet;
            inverseMat._data[ 9] *= invDet;
            inverseMat._data[10] *= invDet;
            inverseMat._data[11] *= invDet;
            inverseMat._data[12] *= invDet;
            inverseMat._data[13] *= invDet;
            inverseMat._data[14] *= invDet;
            inverseMat._data[15] *= invDet;
        }
        else
        {
            inverseMat.set(
                    0, 0, 0, 0,
                    0, 0, 0, 0,
                    0, 0, 0, 0,
                    0, 0, 0, 0 );
        }

        return inverseMat;
    }

    Matrix4 Matrix4::orthogonal() const
    {
        Matrix4 m(*this);
        m.orthogonalInPlace();
        return m;
    }

    void Matrix4::orthogonalInPlace() //primaryAxis, secondaryAxis)
    {
        // Code take it from WildMagig 5  -  www.geometrictools.com  -  here the matrix is transpose
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
        double invLength = 1 / sqrt(_data[0]*_data[0] +
            _data[1]*_data[1] + _data[2]*_data[2]);

        _data[0] *= invLength;
        _data[1] *= invLength;
        _data[2] *= invLength;

        // Compute q1.
        double dot0 = _data[0]*_data[4] + _data[1]*_data[5] +
            _data[2]*_data[6];

        _data[4] -= dot0*_data[0];
        _data[5] -= dot0*_data[1];
        _data[6] -= dot0*_data[2];

        invLength = 1 / sqrt(_data[4]*_data[4] +
            _data[5]*_data[5] + _data[6]*_data[6]);

        _data[4] *= invLength;
        _data[5] *= invLength;
        _data[6] *= invLength;

        // compute q2
        double dot1 = _data[4]*_data[8] + _data[5]*_data[9] +
            _data[6]*_data[10];

        dot0 = _data[0]*_data[8] + _data[1]*_data[9] +
            _data[2]*_data[10];

        _data[8]  -= dot0*_data[0] + dot1*_data[4];
        _data[9]  -= dot0*_data[1] + dot1*_data[5];
        _data[10] -= dot0*_data[2] + dot1*_data[6];

        invLength = 1 / sqrt(_data[8]*_data[8] +
            _data[9]*_data[9] + _data[10]*_data[10]);

        _data[8]  *= invLength;
        _data[9]  *= invLength;
        _data[10] *= invLength;
    }

    void Matrix4::inverseInPlace()
    {
        double value[16];

        double a0 = _data[ 0]*_data[ 5] - _data[ 1]*_data[ 4];
        double a1 = _data[ 0]*_data[ 6] - _data[ 2]*_data[ 4];
        double a2 = _data[ 0]*_data[ 7] - _data[ 3]*_data[ 4];
        double a3 = _data[ 1]*_data[ 6] - _data[ 2]*_data[ 5];
        double a4 = _data[ 1]*_data[ 7] - _data[ 3]*_data[ 5];
        double a5 = _data[ 2]*_data[ 7] - _data[ 3]*_data[ 6];
        double b0 = _data[ 8]*_data[13] - _data[ 9]*_data[12];
        double b1 = _data[ 8]*_data[14] - _data[10]*_data[12];
        double b2 = _data[ 8]*_data[15] - _data[11]*_data[12];
        double b3 = _data[ 9]*_data[14] - _data[10]*_data[13];
        double b4 = _data[ 9]*_data[15] - _data[11]*_data[13];
        double b5 = _data[10]*_data[15] - _data[11]*_data[14];
        double det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;

        if (fabs(det) > gmath::EPSILON)
        {
            value[ 0] = + _data[ 5]*b5 - _data[ 6]*b4 + _data[ 7]*b3;
            value[ 4] = - _data[ 4]*b5 + _data[ 6]*b2 - _data[ 7]*b1;
            value[ 8] = + _data[ 4]*b4 - _data[ 5]*b2 + _data[ 7]*b0;
            value[12] = - _data[ 4]*b3 + _data[ 5]*b1 - _data[ 6]*b0;
            value[ 1] = - _data[ 1]*b5 + _data[ 2]*b4 - _data[ 3]*b3;
            value[ 5] = + _data[ 0]*b5 - _data[ 2]*b2 + _data[ 3]*b1;
            value[ 9] = - _data[ 0]*b4 + _data[ 1]*b2 - _data[ 3]*b0;
            value[13] = + _data[ 0]*b3 - _data[ 1]*b1 + _data[ 2]*b0;
            value[ 2] = + _data[13]*a5 - _data[14]*a4 + _data[15]*a3;
            value[ 6] = - _data[12]*a5 + _data[14]*a2 - _data[15]*a1;
            value[10] = + _data[12]*a4 - _data[13]*a2 + _data[15]*a0;
            value[14] = - _data[12]*a3 + _data[13]*a1 - _data[14]*a0;
            value[ 3] = - _data[ 9]*a5 + _data[10]*a4 - _data[11]*a3;
            value[ 7] = + _data[ 8]*a5 - _data[10]*a2 + _data[11]*a1;
            value[11] = - _data[ 8]*a4 + _data[ 9]*a2 - _data[11]*a0;
            value[15] = + _data[ 8]*a3 - _data[ 9]*a1 + _data[10]*a0;

            double invDet = (1)/det;
            value[ 0] *= invDet;
            value[ 1] *= invDet;
            value[ 2] *= invDet;
            value[ 3] *= invDet;
            value[ 4] *= invDet;
            value[ 5] *= invDet;
            value[ 6] *= invDet;
            value[ 7] *= invDet;
            value[ 8] *= invDet;
            value[ 9] *= invDet;
            value[10] *= invDet;
            value[11] *= invDet;
            value[12] *= invDet;
            value[13] *= invDet;
            value[14] *= invDet;
            value[15] *= invDet;

            memcpy(_data, value, 16*sizeof(double));
        }
       else
       {
        set(
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0 );
       }
    }

    void Matrix4::fromVectorToVector(const Vector3 &fromVec, const Vector3 &toVec)
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
                    this->_data[i*4+j] =  - c1*uvals[i]*uvals[j] - c2*vvals[i]*vvals[j] + c3*vvals[i]*uvals[j];
                }
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

            this->_data[4] = hvxy + v.z;
            this->_data[5] = e + h*v.y*v.y;
            this->_data[6] = hvyz - v.x;

            this->_data[8] = hvxz - v.y;
            this->_data[9] = hvyz + v.x;
            this->_data[10] = e + hvz*v.z;
        }
    }

    void Matrix4::lookAt(const Vector3 &pointAt, const Vector3 &normal, Axis primaryAxis, Axis secondaryAxis)
    {
        this->lookAt(this->getPosition(), pointAt, normal, primaryAxis, secondaryAxis);
    }

    void Matrix4::lookAt(const Vector3 &pos, const Vector3 &pointAt, const Vector3 &normal, Axis primaryAxis, Axis secondaryAxis)
    {
        Vector3 primary, secondary, terziary;
        
        primary = pointAt - pos;
        secondary = normal - pos;
        primary.normalizeInPlace();
        secondary.normalizeInPlace();

        /*
        double f = fabs( primary.dot(secondary) );
        if (f > 1.0-gmath::EPSILON)
            throw GMathError("Matrix4:\n\ttarget vector and up vector are perpendicular, impossible to create a matrix out of them."); */
        
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

        this->setPosition(pos);
    }

    Matrix4 Matrix4::createLookAt(const Vector3 &pos, const Vector3 &pointAt, const Vector3 &normal, Axis primaryAxis, Axis secondaryAxis)
    {
        Matrix4 mat;
        mat.lookAt(pos, pointAt, normal, primaryAxis, secondaryAxis);
        return mat;
    }

    void Matrix4::fromAxisAngle(const Vector3 &axis, double angle)
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
        _data[4] = k1ab-k3c;    _data[5] = k1*sqr_b+k2; _data[6] = k1bc+k3a;
        _data[8] = k1ac+k3b;    _data[9] = k1bc-k3a;    _data[10] = k1*sqr_c+k2;
    }

    std::string Matrix4::toString() const
    {
        std::stringstream oss;
        oss << "gmath::Matrix4(" << _data[ 0] << ", " << _data[ 1] << ", " << _data[ 2] << ", " << _data[ 3] << std::endl;
        oss << "               " << _data[ 4] << ", " << _data[ 5] << ", " << _data[ 6] << ", " << _data[ 7] << std::endl;
        oss << "               " << _data[ 8] << ", " << _data[ 9] << ", " << _data[10] << ", " << _data[11] << std::endl;
        oss << "               " << _data[12] << ", " << _data[13] << ", " << _data[14] << ", " << _data[15] << ");";

        return oss.str();
    }


    const Matrix4 Matrix4::IDENTITY = Matrix4(1.0, 0.0, 0.0, 0.0,
                                              0.0, 1.0, 0.0, 0.0,
                                              0.0, 0.0, 1.0, 0.0,
                                              0.0, 0.0, 0.0, 1.0);


    #ifdef CMAYA
    
        void Matrix4::fromMayaMatrix(const MMatrix &mmatrix)
        {
            setRow(0, Vector4(mmatrix[0]));
            setRow(1, Vector4(mmatrix[1]));
            setRow(2, Vector4(mmatrix[2]));
            setRow(3, Vector4(mmatrix[3]));
        }

        MMatrix Matrix4::toMayaMatrix() const
        {   
            double (*value)[4] = (double(*)[4])&_data[0];
            return MMatrix(value);
        }

        /*------------------ Free functions ------------------*/

        MDagPath mpathFromString(const std::string &dagName)
        {
            MSelectionList sl;
            sl.add(MString(dagName.data()));
            MDagPath path;
            sl.getDagPath(0, path);
            return path;
        }
        
        Matrix4 getGlobalMatrix(const MDagPath &path)
        {
            Matrix4 gmatrix;
            gmatrix.fromMayaMatrix(path.inclusiveMatrix());
            return gmatrix;
        }

        Matrix4 getGlobalMatrix(const std::string &dagName)
        {
            return getGlobalMatrix(mpathFromString(dagName));
        }

        void setGlobalMatrix(MDagPath &path, const Matrix4 &gmatrix)
        {
            MMatrix localMatrix = gmatrix.toMayaMatrix() * path.exclusiveMatrixInverse();

            MTransformationMatrix mtmatrix(localMatrix);

            MFnTransform mfnTransform(path);
            mfnTransform.set(mtmatrix);
        }

        void setGlobalMatrix(const std::string &dagName, const Matrix4 &gmatrix)
        {
            MDagPath path = mpathFromString(dagName);
            setGlobalMatrix(path, gmatrix);
        }

        Matrix4 getLocalMatrix(const MDagPath &path)
        {
            MMatrix matrix = path.inclusiveMatrix() * path.exclusiveMatrixInverse();
            Matrix4 gmatrix;
            gmatrix.fromMayaMatrix(matrix);
            return gmatrix;
        }

        Matrix4 getLocalMatrix(const std::string &dagName)
        {
            return getLocalMatrix(mpathFromString(dagName));
        }
        
        void setLocalMatrix(MDagPath &path, const Matrix4 &gmatrix)
        {
            MTransformationMatrix mtmatrix(gmatrix.toMayaMatrix());

            MFnTransform mfnTransform(path);
            mfnTransform.set(mtmatrix);
        }

        void setLocalMatrix(const std::string &dagName, const Matrix4 &gmatrix)
        {
            MDagPath path = mpathFromString(dagName);
            setLocalMatrix(path, gmatrix);
        }

    #endif
}

