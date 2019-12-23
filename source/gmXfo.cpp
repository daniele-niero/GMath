#include "gmRoot.h"
#include "gmXfo.h"

using namespace std;

namespace gmath
{
    /*------ Constructors ------*/
    Xfo::Xfo()
    {
        ori = make_shared<Quaternion>();
        tr  = make_shared<Vector3>();
        sc  = make_shared<Vector3>(1.0, 1.0, 1.0);
    }

    Xfo::Xfo(const Xfo& other) 
    {
        ori = other.ori;
        tr  = other.tr;
        sc  = other.sc;
    }

    Xfo::Xfo(const Vector3 & tr)
    {
        this->ori = make_shared<Quaternion>();
        this->tr  = make_shared<Vector3>(tr);
        this->sc  = make_shared<Vector3>(1.0, 1.0, 1.0);
    }

    Xfo::Xfo(const Quaternion & ori)
    {
        this->ori = make_shared<Quaternion>(ori);
        this->tr  = make_shared<Vector3>();
        this->sc  = make_shared<Vector3>(1.0, 1.0, 1.0);
    }

    Xfo::Xfo(const Vector3 & tr, const Quaternion & ori)
    {
        this->ori = make_shared<Quaternion>(ori);
        this->tr  = make_shared<Vector3>(tr);
        this->sc  = make_shared<Vector3>(1.0, 1.0, 1.0);
    }

    Xfo::Xfo(const Quaternion & ori, const Vector3 & tr, const Vector3 & sc)
    {
        this->ori = make_shared<Quaternion>(ori);
        this->tr  = make_shared<Vector3>(tr);
        this->sc  = make_shared<Vector3>(sc);
    }

    Xfo::Xfo(const Matrix4 & mat)
    {
        ori = make_shared<Quaternion>(mat.toQuaternion());
        tr  = make_shared<Vector3>(mat.getPosition());
        sc  = make_shared<Vector3>(mat.getScale());
    }

    Xfo::Xfo(const double & eulerX, const double & eulerY, const double & eulerZ, 
             const double & trX, const double & trY, const double & trZ,
             const double & scX, const double & scY, const double & scZ)
    {
        ori = make_shared<Quaternion>(eulerX, eulerY, eulerZ);
        tr  = make_shared<Vector3>(trX, trY, trZ);
        sc  = make_shared<Vector3>(scX, scY, scZ);
    }

    /*------ Arithmetic operations ------*/
    Xfo Xfo::operator * (const Xfo & other) const
    {
        Xfo result(*this);
        return result *= other;
    }

    /*------ Arithmetic updates ------*/
    Xfo& Xfo::operator *= (const Xfo & other)
    {
        if(this->sc->x != this->sc->y || this->sc->x != this->sc->z)
        {
            double relativePrecision = abs(this->sc->x)*EPSILON*10.0;
            if( abs(this->sc->x - this->sc->y) > relativePrecision || abs(this->sc->x - this->sc->z) > relativePrecision ) 
                throw GMathError("Xfo operator *: Cannot multiply to xfos when having non-uniform scaling without causing shearing. Use Matrix4s instead.");
        }

        Vector3 tr = *other.tr + other.ori->rotateVector(*this->tr * *other.sc);
        Vector3 sc = *this->sc * *other.sc;
        Quaternion ori = *this->ori * *other.ori;

        this->tr->set(tr.x, tr.y, tr.z);
        this->ori->set(ori.x, ori.y, ori.z, ori.w);
        this->ori->normalizeInPlace();
        this->sc->set(sc.x, sc.y, sc.z);

        return *this;
    }

    /*------ Arithmetic comparisons ------*/
    bool Xfo::operator == (const Xfo & other) const
    {
        return (*ori == *other.ori && *tr == *other.tr && *sc == *other.sc);
    }

    bool Xfo::operator != (const Xfo & other) const
    {
        return (*ori != *other.ori && *tr != *other.tr && *sc != *other.sc);
    }

    /*------ Arithmetic assignment ------*/
    void Xfo::operator = (const Xfo & other) 
    {
        *ori = *other.ori;
        *tr =  *other.tr;
        *sc =  *other.sc;
    }

    /*------ methods ------*/
    Xfo Xfo::clone() const {
        return Xfo(*this);
    }
    
    void Xfo::setToIdentity()
    {
        ori->set(0.0, 0.0, 0.0, 1.0);
        tr->set(0.0, 0.0, 0.0);
        sc->set(1.0, 1.0, 1.0);
    }

    void Xfo::fromMatrix4(const Matrix4 & mat)
    {
        *ori = mat.toQuaternion();
        *tr  = mat.getPosition();
        *sc  = mat.getScale();
    }

    Matrix4 Xfo::toMatrix4() const
    {
        Matrix4 result(*ori, *tr);
        result.setScale(*sc);
        return result;
    }

    Vector3 Xfo::transformVector(const Vector3 & vec) const
    {
        return ori->rotateVector(vec * *sc) + *tr;
    }

    Xfo Xfo::inverse() const
    {
        if(this->sc->x != this->sc->y || this->sc->x != this->sc->z)
        {
            double relativePrecision = abs(this->sc->x)*EPSILON*10.0;
            if( abs(this->sc->x - this->sc->y) > relativePrecision || abs(this->sc->x - this->sc->z) > relativePrecision ) 
                throw GMathError("Xfo.inverse: Cannot invert xfo with non-uniform scaling without causing shearing. Try using inverseTransformVector, use Mat44s instead");
        }

        Xfo result(*this);
        result.inverseInPlace();
        return result;
    }

    Xfo& Xfo::inverseInPlace()
    {
        if(this->sc->x != this->sc->y || this->sc->x != this->sc->z)
        {
            double relativePrecision = abs(this->sc->x)*EPSILON*10.0;
            if( abs(this->sc->x - this->sc->y) > relativePrecision || abs(this->sc->x - this->sc->z) > relativePrecision ) 
                throw GMathError("Xfo.inverse: Cannot invert xfo with non-uniform scaling without causing shearing. Try using inverseTransformVector, use Mat44s instead");
        }

        Quaternion inverseOri = ori->inverse();

        ori->inverseInPlace();
        sc->inverseInPlace();
        *tr = ori->rotateVector(tr->negate() * *sc);
        return *this;
    }

    Vector3 Xfo::inverseTransformVector(const Vector3 & vec) const
    {
        return this->inverse().transformVector(vec);
    }

    Xfo Xfo::slerp(const Xfo & other, const double & t) const
    {
        Xfo result(*this);
        result.slerpInPlace(other, t);
        return result;
    }

    Xfo& Xfo::slerpInPlace(const Xfo & other, const double & t)
    {
        Xfo result;
        ori->slerpInPlace(*other.ori, t);
        tr->linearInterpolateInPlace(*other.tr, t);
        sc->linearInterpolateInPlace(*other.sc, t);
        return *this;
    }

    double Xfo::distanceTo(const Xfo & other) const
    {
        return tr->distance(*other.tr);
    }

    Xfo Xfo::mirror(const Vector3& center, const Vector3& normal, Axis primary, Axis secondary) const
    {
        Xfo result(*this);
        result.mirrorInPlace(center, normal, primary, secondary);
        return result;
    }

    Xfo& Xfo::mirrorInPlace(const Vector3& center, const Vector3& normal, Axis primary, Axis secondary)
    {   
        *tr = (*tr-center).mirror(normal)+center;
        ori->mirrorInPlace(normal, primary, secondary);

        return *this;
    }

    Xfo Xfo::mirror(CartesianPlane plane) const
    {
        Vector3 normal;
        Axis primary, secondary;
        switch(plane) {
            case CartesianPlane::XY: 
                normal = Vector3::ZAXIS;
                primary = Axis::POSX;
                secondary = Axis::POSY;
                break;
            case CartesianPlane::YZ: 
                normal = Vector3::XAXIS;
                primary = Axis::POSY;
                secondary = Axis::POSZ;
                break;
            case CartesianPlane::ZX: 
                normal = Vector3::YAXIS;
                primary = Axis::POSZ;
                secondary = Axis::POSX;
                break; 
        }
        Xfo result;
        result.tr->mirrorInPlace(normal);
        result.ori->mirrorInPlace(normal, primary, secondary);
        *result.sc = *sc;
        return result;
    }

    Xfo& Xfo::mirrorInPlace(CartesianPlane plane)
    {
        Vector3 normal;
        Axis primary, secondary;
        switch(plane) {
            case CartesianPlane::XY: 
                normal = Vector3::ZAXIS;
                primary = Axis::POSX;
                secondary = Axis::POSY;
                break;
            case CartesianPlane::YZ: 
                normal = Vector3::XAXIS;
                primary = Axis::POSY;
                secondary = Axis::POSZ;
                break;
            case CartesianPlane::ZX: 
                normal = Vector3::YAXIS;
                primary = Axis::POSZ;
                secondary = Axis::POSX;
                break; 
        }
        tr->mirrorInPlace(normal);
        ori->mirrorInPlace(normal, primary, secondary);
        return *this;
    }

    std::string Xfo::toString() const
    {
        std::stringstream oss;
        oss << "gmath::Xfo(ori:" << ori->x << ", " << ori->y << ", " << ori->z << ", " << ori->w << std::endl;
        oss << "           tr :" << tr->x  << ", " << tr->y  << ", " << tr->z  << std::endl;
        oss << "           sc :" << sc->x  << ", " << sc->y  << ", " << sc->z  << ");";

        return oss.str();
    }

    #ifdef CMAYA
        void Xfo::fromMayaMatrix(const MMatrix mmatrix)
        {
            Matrix4 matrix;
            matrix.fromMayaMatrix(mmatrix);
            this->fromMatrix4(matrix);
        }

        MMatrix Xfo::toMayaMatrix() const
        {
            return this->toMatrix4().toMayaMatrix();
        }

        /*------------- free functions ---------------*/

        Xfo getGlobalXfo(const MDagPath &path)
        {
            return Xfo(getGlobalMatrix(path));
        }

        Xfo getGlobalXfo(const std::string &dagName)
        {
            return Xfo(getGlobalMatrix(dagName));
        }

        void setGlobalXfo(MDagPath &path, const Xfo &xfo)
        {
            setGlobalMatrix(path, xfo.toMatrix4());
        }

        void setGlobalXfo(const std::string &dagName, const Xfo &xfo)
        {
            setGlobalMatrix(dagName, xfo.toMatrix4());
        }

        Xfo getLocalXfo(const MDagPath &path)
        {
            return Xfo(getLocalMatrix(path));   
        }

        Xfo getLocalXfo(const std::string &dagName)
        {
            return Xfo(getLocalMatrix(dagName));
        }
        
        void setLocalXfo(MDagPath &path, const Xfo &xfo)
        {
            setLocalMatrix(path, xfo.toMatrix4());
        }

        void setLocalXfo(const std::string &dagName, const Xfo &xfo)
        {
            setLocalMatrix(dagName, xfo.toMatrix4());
        }
    #endif
}