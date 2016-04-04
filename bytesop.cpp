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
	Py_buffer ab,bb; \
	char * a; \
	char * b; \
	char * out; \
	Py_ssize_t out_size; \
	if (!PyArg_ParseTuple(args, "s*s*", &ab,&bb)) \
        return NULL; \
	if (ab.suboffsets!=NULL||ab.strides!=NULL){ \
		PyBuffer_Release(&ab); \
		PyBuffer_Release(&bb); \
		PyErr_SetString(PyExc_ValueError,"First argument must export buffer as PyBUF_CONTIG_RO"); \
		return NULL; \
	} \
	if (bb.suboffsets!=NULL||ab.strides!=NULL){ \
		PyBuffer_Release(&ab); \
		PyBuffer_Release(&bb); \
		PyErr_SetString(PyExc_ValueError,"First argument must export buffer as PyBUF_CONTIG_RO"); \
		return NULL; \
	} \
	Py_BEGIN_ALLOW_THREADS \
	if (bb.len<ab.len){ \
		out_size=bb.len; \
	}else{ \
		out_size=ab.len; \
	} \
	a=(char*)ab.buf; \
	b=(char*)bb.buf; \
	out=(char*)malloc(out_size); \
	for (int i=0;i<out_size;i++){ \
		out[i]=a[i] OP b[i]; \
	} \
	PyBuffer_Release(&ab); \
	PyBuffer_Release(&bb); \
	Py_END_ALLOW_THREADS \
	return Py_BuildValue(BO_OUT,out,out_size); \
} \


#define BYBYTESOP_N_FUNC(NAME,OP) \
static PyObject * NAME(PyObject *self, PyObject *args){ \
	Py_buffer ab,bb; \
	char * a; \
	char * b; \
	char * out; \
	Py_ssize_t out_size; \
	if (!PyArg_ParseTuple(args, "s*s*", &ab,&bb)) \
        return NULL; \
	if (ab.suboffsets!=NULL||ab.strides!=NULL){ \
		PyBuffer_Release(&ab); \
		PyBuffer_Release(&bb); \
		PyErr_SetString(PyExc_ValueError,"First argument must export buffer as PyBUF_CONTIG_RO"); \
		return NULL; \
	} \
	if (bb.suboffsets!=NULL||ab.strides!=NULL){ \
		PyBuffer_Release(&ab); \
		PyBuffer_Release(&bb); \
		PyErr_SetString(PyExc_ValueError,"First argument must export buffer as PyBUF_CONTIG_RO"); \
		return NULL; \
	} \
	Py_BEGIN_ALLOW_THREADS \
	if (bb.len<ab.len){ \
		out_size=bb.len; \
	}else{ \
		out_size=ab.len; \
	} \
	a=(char*)ab.buf; \
	b=(char*)bb.buf; \
	out=(char*)malloc(out_size); \
	for (int i=0;i<out_size;i++){ \
		out[i]=~(a[i] OP b[i]); \
	} \
	PyBuffer_Release(&ab); \
	PyBuffer_Release(&bb); \
	Py_END_ALLOW_THREADS \
	return Py_BuildValue(BO_OUT,out,out_size); \
} \


BYBYTESOP_FUNC(bytesop_op_xor, ^)

BYBYTESOP_FUNC(bytesop_op_or, | )

BYBYTESOP_FUNC(bytesop_op_and, &)

BYBYTESOP_N_FUNC(bytesop_op_xnor, ^)

BYBYTESOP_N_FUNC(bytesop_op_nor, | )

BYBYTESOP_N_FUNC(bytesop_op_nand, &)


static PyObject * bytesop_op_not(PyObject *self, PyObject *args){
	Py_buffer b;
	char * a;
	char * out;
	Py_ssize_t out_size;
	if (!PyArg_ParseTuple(args, "s*", &b))
		return NULL;
	if (b.suboffsets!=NULL||b.strides!=NULL){
		PyBuffer_Release(&b);
		PyErr_SetString(PyExc_ValueError,"Argument must export buffer as PyBUF_CONTIG_RO");
		return NULL;
	}
	Py_BEGIN_ALLOW_THREADS 
	a=(char*)b.buf;
	out_size = b.len;
	out = (char*)malloc(out_size);
	for (int i = 0; i < out_size; i++){
		out[i] = ~a[i];
	}
	PyBuffer_Release(&b);
	Py_END_ALLOW_THREADS
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