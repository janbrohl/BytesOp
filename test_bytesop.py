import unittest
import bytesop_pure
import bytesop

import os


class TestOps(unittest.TestCase):

    def test_not(self):
        a = os.urandom(1000)
        not_a = bytesop.op_not(a)
        self.assertEqual(not_a, bytesop_pure.op_not(a))

    def test_or(self):
        a = os.urandom(1000)
        b = os.urandom(1000)
        a_or_b = bytesop.op_or(a, b)
        self.assertEqual(a_or_b, bytesop_pure.op_or(a, b))

    def test_xor(self):
        a = os.urandom(1000)
        b = os.urandom(1000)
        a_xor_b = bytesop.op_xor(a, b)
        self.assertEqual(a_xor_b, bytesop_pure.op_xor(a, b))

    def test_and(self):
        a = os.urandom(1000)
        b = os.urandom(1000)
        a_and_b = bytesop.op_and(a, b)
        self.assertEqual(a_and_b, bytesop_pure.op_and(a, b))

    def test_nor(self):
        a = os.urandom(1000)
        b = os.urandom(1000)
        a_nor_b = bytesop.op_nor(a, b)
        self.assertEqual(a_nor_b, bytesop_pure.op_nor(a, b))

    def test_xnor(self):
        a = os.urandom(1000)
        b = os.urandom(1000)
        a_xnor_b = bytesop.op_xnor(a, b)
        self.assertEqual(a_xnor_b,  bytesop_pure.op_xnor(a, b))

    def test_nand(self):
        a = os.urandom(1000)
        b = os.urandom(1000)
        a_nand_b = bytesop.op_nand(a, b)
        self.assertEqual(a_nand_b,  bytesop_pure.op_nand(a, b))


if __name__ == '__main__':
    unittest.main()
