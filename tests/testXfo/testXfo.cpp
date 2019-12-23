#include "gmXfo.h"

using namespace gmath;

int main(int argc, char const *argv[])
{
	
	Xfo x1 = Xfo();
	Vector3 t(1.0, 2.0, 3.0);
	t.x = 100.0;

	cout << "beginning" << endl;
	cout << x1.toString() << endl;
	cout << t.toString() << endl;


	cout << "assign xfo.tr to vector and change vector" << endl;
	
	*x1.tr = t;
	t.x = 500.0;

	cout << x1.toString() << endl;
	cout << t.toString() << endl;


	cout << "v = xfo.tr and then change xfo.tr" << endl;
	
	Vector3 xt = *x1.tr;
	xt.x = 210.0;

	cout << x1.toString() << endl;
	cout << t.toString() << endl;
	cout << xt.toString() << endl;


	cout << "shared ptr v = xfo.tr and then both" << endl;

	shared_ptr<Vector3> xt2 = x1.tr;

	x1.tr->y = 123.0;
	xt2->z = 321.0;

	cout << x1.toString() << endl;
	cout << xt2->toString() << endl;

	return 0;
}