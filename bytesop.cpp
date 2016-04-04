#define PY_SSIZE_T_CLEAN
#include <Python.h>

#if PY_MAJOR_VERSION == 3
#define BO_OUT "y#"
#endif

#if PY_MAJOR_VERSION == 2
#define BO_OUT "s#"
#endif



#define BYBYTESOP_FUNC(NAME,OP) \
static PyObject * NAME(PyObject *self, PyObject *args){ \
	char * a; \
	char * b; \
	Py_ssize_t a_size,b_size,out_size; \
	if (!PyArg_ParseTuple(args, "s#s#", &a,&a_size,&b,&b_size)) \
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
	return Py_BuildValue(BO_OUT,out,out_size); \
} \


#define BYBYTESOP_N_FUNC(NAME,OP) \
static PyObject * NAME(PyObject *self, PyObject *args){ \
	char * a; \
	char * b; \
	Py_ssize_t a_size,b_size,out_size; \
	if (!PyArg_ParseTuple(args, "s#s#", &a,&a_size,&b,&b_size)) \
        return NULL; \
	if (b_size<a_size){ \
		out_size=b_size; \
			}else{ \
		out_size=a_size; \
			} \
	char * out=(char*)malloc(out_size); \
	for (int i=0;i<out_size;i++){ \
		out[i]=~(a[i] OP b[i]); \
			} \
	return Py_BuildValue(BO_OUT,out,out_size); \
} \


BYBYTESOP_FUNC(bytesop_op_xor, ^)

BYBYTESOP_FUNC(bytesop_op_or, | )

BYBYTESOP_FUNC(bytesop_op_and, &)

BYBYTESOP_N_FUNC(bytesop_op_xnor, ^)

BYBYTESOP_N_FUNC(bytesop_op_nor, | )

BYBYTESOP_N_FUNC(bytesop_op_nand, &)


static PyObject * bytesop_op_not(PyObject *self, PyObject *args){
	char * a;
	Py_ssize_t a_size, out_size;
	if (!PyArg_ParseTuple(args, "s#", &a, &a_size))
		return NULL;
	out_size = a_size;
	char * out = (char*)malloc(out_size);
	for (int i = 0; i < out_size; i++){
		out[i] = ~a[i];
	}
	return Py_BuildValue(BO_OUT, out, out_size);
}

static PyMethodDef BytesOpMethods[] =
{
	{ "op_xor", bytesop_op_xor, METH_VARARGS,
	"XOR two bytestrings." },
	{ "op_or", bytesop_op_or, METH_VARARGS,
	"OR two bytestrings." },
	{ "op_and", bytesop_op_and, METH_VARARGS,
	"AND two bytestrings." },
	{ "op_xnor", bytesop_op_xnor, METH_VARARGS,
	"XNOR (NXOR) two bytestrings." },
	{ "op_nor", bytesop_op_nor, METH_VARARGS,
	"NOR two bytestrings." },
	{ "op_nand", bytesop_op_nand, METH_VARARGS,
	"NAND two bytestrings." },
	{ "op_not", bytesop_op_not, METH_VARARGS,
	"NOT a bytestring." },
	{ NULL, NULL, 0, NULL }
};

#define BO_N "bytesop"
#define BO_DOC "Bitwise operations on bytestrings"

#if PY_MAJOR_VERSION == 3
static struct PyModuleDef bytesopmodule = {
	PyModuleDef_HEAD_INIT,
	BO_N,   /* name of module */
	BO_DOC, /* module documentation, may be NULL */
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
	(void)Py_InitModule3(BO_N, BytesOpMethods, BO_DOC);
}

#endif