

%module gmath

%include <std_shared_ptr.i>

%shared_ptr(gmath::Vector3)

%inline %{

#include <memory>

class Pippo {
public:
    Pippo() {
        tr = std::make_shared<gmath::Vector3>();
    }

    ~Pippo() {
    }

    std::shared_ptr<gmath::Vector3> tr;
};

%}


