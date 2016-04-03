#define PY_SSIZE_T_CLEAN
#include <Python.h>

#if PY_MAJOR_VERSION == 3
#define IN1 "y#"
#define IN2 "y#y#"
#define OUT "y#"
#define PYTHON3
#endif

#if PY_MAJOR_VERSION == 2
#define IN1 "t#"
#define IN2 "t#t#"
#define OUT "s#"
#endif

#define BYBYTESOP_FUNC(NAME,OP) \
static PyObject * NAME(PyObject *self, PyObject *args){ \
	char * a; \
	char * b; \
	Py_ssize_t a_size,b_size,out_size; \
	if (!PyArg_ParseTuple(args, IN2, &a,&a_size,&b,&b_size)) \
        return NULL; \
	if (b_size<a_size){ \
		out_size=b_size; \
			}else{ \
		out_size=a_size; \
			} \
	char * out=(char*)malloc(out_size); \
	for (int i=0;i<out_size;i++){ \
		out[i]=a[i] OP b[i]; \
			} \
	return Py_BuildValue(OUT,out,out_size); \
} \


BYBYTESOP_FUNC(bytesop_op_xor, ^)

BYBYTESOP_FUNC(bytesop_op_or, | )

BYBYTESOP_FUNC(bytesop_op_and, &)


static PyObject * bytesop_op_not(PyObject *self, PyObject *args){
	char * a;
	Py_ssize_t a_size, out_size;
	if (!PyArg_ParseTuple(args, IN1, &a, &a_size))
		return NULL;
	out_size = a_size;
	char * out = (char*)malloc(out_size);
	for (int i = 0; i < out_size; i++){
		out[i] = ~a[i];
	}
	return Py_BuildValue(OUT, out, out_size);
}

static PyMethodDef BytesOpMethods[] =
{
	{ "op_xor", bytesop_op_xor, METH_VARARGS,
	"XOR bytestrings." },
	{ "op_or", bytesop_op_or, METH_VARARGS,
	"OR bytestrings." },
	{ "op_and", bytesop_op_and, METH_VARARGS,
	"AND bytestrings." },
	{ "op_not", bytesop_op_not, METH_VARARGS,
	"NOT a bytestring." },
	{ NULL, NULL, 0, NULL }
};



#if PY_MAJOR_VERSION == 3
static struct PyModuleDef bytesopmodule = {
	PyModuleDef_HEAD_INIT,
	"bytesop",   /* name of module */
	"Bitwise operations on bytestrings...", /* module documentation, may be NULL */
	-1,       /* size of per-interpreter state of the module,
				 or -1 if the module keeps state in global variables. */
				 BytesOpMethods
};

PyMODINIT_FUNC PyInit_bytesop(void)
{
	return PyModule_Create(&bytesopmodule);
}
#endif

#if PY_MAJOR_VERSION == 2
PyMODINIT_FUNC initbytesop(void)
{
	(void)Py_InitModule3("bytesop", BytesOpMethods, "Bitwise operations on bytestrings...");
}

#endif