import operator
import sys

if sys.version_info >= (3, 0):
    imap = map
else:
    from itertools import imap


def to_bytes(it):
    return bytes(bytearray(i & 0xFF for i in it))


def emu1(op, b):
    return to_bytes(imap(op, bytearray(b))))

def emu2(op, a, b):
    return to_bytes(imap(op, bytearray(a), bytearray(b))))


def op_not(b):
    return emu1(operator.inv, b)

def op_xor(a, b):
    return emu2(operator.xor, a, b)

def op_xnor(a, b):
    return op_not(emu2(operator.xor, a, b))

def op_or(a, b):
    return emu2(operator.or_, a, b)

def op_nor(a, b):
    return op_not(emu2(operator.or_, a, b))

def op_and(a, b):
    return emu2(operator.and_, a, b)

def op_nand(a, b):
    return op_not(emu2(operator.and_, a, b))
