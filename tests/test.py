from __future__ import absolute_import

import unittest

import Tokenparser

BULLET = "AccccB"

COMPLEX = "zzzz {AA}Y{BBBC} {f T}"


class Test(unittest.TestCase):

    def setUp(self):
        self.p = Tokenparser.Tokenparser()

    def testSkip(self):
        self.p.skip("A")

        self.assertTrue(self.p.parse("A"))
        self.assertFalse(self.p.parse("AA"))
        self.assertFalse(self.p.parse("B"))

    def testSkipTo(self):
        self.p.skipTo("A")
        self.p.skip("A")

        self.assertTrue(self.p.parse("BA"))
        self.assertTrue(self.p.parse("BBBBBA"))
        self.assertFalse(self.p.parse("AA"))
        self.assertFalse(self.p.parse("CCC"))

    def testFromTo(self):
        self.p.fromTo("TEST", "A", "B")

        self.assertTrue(self.p.parse(BULLET))
        self.assertEqual(self.p.matches().get("TEST", ""), BULLET)
        self.assertNotEqual(self.p.matches().get("TEST", ""), "AXB")

    def testUpTo(self):
        self.p.upTo("TEST", "B")

        self.assertFalse(self.p.parse(BULLET))
        self.assertEqual(self.p.matches().get("TEST", ""), BULLET[:-1])

        self.p.skip("B")
        self.assertTrue(self.p.parse(BULLET))
        self.assertEqual(self.p.matches().get("TEST", ""), BULLET[:-1])

    def testComplex(self):
        self.p.skipTo("{")
        self.p.skip("{")
        self.p.upTo("1", "}")
        self.p.skip("}")
        self.p.skip("Y")
        self.p.skip("{")
        self.p.fromTo("2", "B", "C")
        self.p.skipTo("{")
        self.p.skip("{")
        self.p.upTo("3", "}")

        self.assertFalse(self.p.parse(COMPLEX))

        self.p.skip("}")
        self.assertTrue(self.p.parse(COMPLEX))

        def check(res):
            self.assertTrue(res["1"] == "AA"
                            and res["2"] == "BBBC"
                            and res["3"] == "f T")

        ML = [COMPLEX for _ in xrange(0, 100)]
        count = map(check,
                    self.p.multilinesParse(ML))
        self.assertEqual(len(count), 100)

        ML[50] = "DUMMY"
        count = map(check,
                    self.p.multilinesParse(ML))
        self.assertEqual(len(count), 99)


if __name__ == '__main__':
    unittest.main()
