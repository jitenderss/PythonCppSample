#include <Python.h>
#include <iostream>


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
    
    
    std::cout<<"Finished!!!"<<std::endl;
    Py_Finalize();
    
    
    
    
#if 0
    
    Py_Initialize();
    //PySys_SetArgv(argc, argv);
    //PyRun_SimpleString("import sys\nprint sys.argv");
    if ( !Py_IsInitialized() ) {
        return -1;
    }
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/Users/jitendersingh/PythonEmbeddingC++')");
    PyObject* pMod = NULL;
    PyObject* pFunc = NULL;
    PyObject* pParm = NULL;
    PyObject* pRetVal = NULL;
    int iRetVal = -999;
    const char* modulName="naya";
    
    /* Error checking of pName left out */
    
    pMod = PyImport_ImportModule(modulName);
    
    if(!pMod)
    {
        std::cout<<"Import module failed!";
        PyErr_Print();
        return -1;
    }
    const char* funcName="pyfunction";
    pFunc = PyObject_GetAttrString(pMod, funcName);
    if(!pFunc)
    {
        std::cout<<"Import function failed!";
        return -2;
    }
    
    std::cout<<"Generated pylist"<<std::endl;
    if(!PyCallable_Check(pFunc))
    {
        std::cout<<"Funcn not callable"<<std::endl;
        return -1;
    }
    
    int tuple_length = 4;
    /*
     PyObject *args = PyTuple_New(1);
     PyTuple_SetItem(args, 0, PyInt_FromLong(42L));*/
    PyObject *the_tuple = PyTuple_New(tuple_length);
    PyObject *the_object;
    
    for(int i = 0; i < tuple_length; i++) {
        the_object = PyInt_FromLong(5);//PyLong_FromSsize_t(i * tuple_length + j);
        if(the_object == NULL) {
            std::cout<<"PyLong_FromSsize_t failed"<<std::endl;
            PyErr_Print();
            return -1;
        }
        
        PyTuple_SET_ITEM(the_tuple, i, the_object);
    }
    
    std::cout<<"jjjjjjjjjjj"<<std::endl;
    //pRetVal = PyEval_CallObject(pFunc, the_tuple);
    
    pRetVal = PyObject_CallObject(pFunc, the_tuple);
    PyArg_Parse(pRetVal, "i", &iRetVal);
    //PyErr_Print();
    std::cout<<"kkkkkkkkkk"<<std::endl;
    std::cout<<iRetVal<<std::endl;
    Py_Finalize();
    return iRetVal;
#endif
}



