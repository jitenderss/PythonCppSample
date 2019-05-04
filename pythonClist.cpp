#include <Python.h>
#include <iostream>
#include <vector>

using namespace std;

vector<float> listTupleToVector_Float(PyObject* incoming) {
    vector<float> data;
    if (PyTuple_Check(incoming)) {
        for(Py_ssize_t i = 0; i < PyTuple_Size(incoming); i++) {
            PyObject *value = PyTuple_GetItem(incoming, i);
            data.push_back( PyFloat_AsDouble(value) );
        }
    } else {
        if (PyList_Check(incoming)) {
            for(Py_ssize_t i = 0; i < PyList_Size(incoming); i++) {
                PyObject *value = PyList_GetItem(incoming, i);
                data.push_back( PyFloat_AsDouble(value) );
            }
        } else {
            throw logic_error("Passed PyObject pointer was not a list or tuple!");
        }
    }
    return data;
}


int main(int argc, char * argv[])
{
    std::cout<<"Cpp to python list test started"<<std::endl;
    
    Py_Initialize();
    if ( !Py_IsInitialized() ) {
        std::cout<<"Py_IsInitialized failed!!!!!"<<std::endl;
        return -1;
    }
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyString_FromString("."));
    
    // Build the name object
    PyObject *pName = PyString_FromString("pyClist");
    
    // Load the module object
    PyObject *pModule = PyImport_Import(pName);
    
    // pDict is a borrowed reference
    PyObject *pDict = PyModule_GetDict(pModule);
    
    // pFunc is also a borrowed reference
    PyObject *pFunc = PyObject_GetAttrString(pModule, "mysolve");
    
    if (!PyCallable_Check(pFunc))
        PyErr_Print();
    int xvarcount = 10;
    PyObject *l = PyList_New(xvarcount);
    for(size_t i=0; i<xvarcount; i++){
        PyObject *pValue = PyInt_FromLong(i+10);
        PyList_SetItem(l, i, pValue);
    }
    
    PyObject *arglist = Py_BuildValue("(O)", l);
    PyObject *pValue = PyObject_CallObject(pFunc, arglist);
    
    vector<float> data = listTupleToVector_Float(pValue);
    std::cout<<"Vector size :" << data.size() << std::endl;
    
    for (int i = 0; i < data.size(); ++i)
        cout << data.at(i) << " ";
    
    std::cout<<"Finished!!!"<<std::endl;
    Py_Finalize();
    

}



