#include <Python.h>

int
main(int argc, char *argv[])
{
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;
    int i;
    
    /*if (argc < 3) {
        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
        return 1;
    }*/
    
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/Users/jitendersingh/PythonEmbeddingC++')");
    const char* modulName="naya";
    pName = PyString_FromString(modulName);
    /* Error checking of pName left out */
    
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    
    int nargc = 5;
    if (pModule != NULL) {
        const char* funcName="pyfunction";
        pFunc = PyObject_GetAttrString(pModule, funcName);
        /* pFunc is a new reference */
        
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(nargc - 3);
            for (i = 0; i < nargc - 3; ++i) {
                pValue = PyInt_FromLong(4);
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyInt_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            //fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        //fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }
    Py_Finalize();
    return 0;
}
