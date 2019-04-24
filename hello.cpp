#if 0
#include <Python.h>

int
main(int argc, char *argv[])
{
    Py_SetProgramName(argv[0]);  /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
                       "print 'Today is',ctime(time())\n");
    Py_Finalize();
    return 0;
}
#endif

#include <Python.h>
#include <iostream>


int main(int argc, char * argv[])
{
    std::cout<<"RAM"<<std::endl;

    const char* picpath ="/Users/jitendersingh/Downloads/jiten.jpg";
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
    const char* modulName="classify";
    pMod = PyImport_ImportModule(modulName);
    if(!pMod)
    {
        std::cout<<"Import module failed!";
        PyErr_Print();
        return -1;
    }
    const char* funcName="evaluate";
    pFunc = PyObject_GetAttrString(pMod, funcName);
    if(!pFunc)
    {
        std::cout<<"Import function failed!";
        return -2;
    }
    pParm = PyTuple_New(1);
    PyTuple_SetItem(pParm, 0, Py_BuildValue("s",picpath));
    pRetVal = PyEval_CallObject(pFunc, pParm);
    PyArg_Parse(pRetVal, "i", &iRetVal);
    //PyErr_Print();
    std::cout<<iRetVal;
    return iRetVal;
}

