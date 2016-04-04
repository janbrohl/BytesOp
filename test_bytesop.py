import unittest
import bytesop
import operator
import os


def emu(op, *args):
    return bytes(bytearray(i & 0xFF for i in map(op, *map(bytearray, args))))


class TestOps(unittest.TestCase):

    def test_not(self):
        a = os.urandom(1000)
        not_a = bytesop.op_not(a)
        self.assertEqual(not_a, emu(operator.inv, a))

    def test_or(self):
        a = os.urandom(1000)
        b = os.urandom(1000)
        a_or_b = bytesop.op_or(a, b)
        self.assertEqual(a_or_b, emu(operator.or_, a, b))

    def test_xor(self):
        a = os.urandom(1000)
        b = os.urandom(1000)
        a_xor_b = bytesop.op_xor(a, b)
        self.assertEqual(a_xor_b, emu(operator.xor, a, b))

    def test_and(self):
        a = os.urandom(1000)
        b = os.urandom(1000)
        a_and_b = bytesop.op_and(a, b)
        self.assertEqual(a_and_b, emu(operator.and_, a, b))


if __name__ == '__main__':
    unittest.main()
