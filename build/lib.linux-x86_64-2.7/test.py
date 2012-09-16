#! /usr/bin/env python

import _tokenparser

p = _tokenparser.TokenParser()
p.upTo('sssss','s')
#p.skip('s')
p.Parse('eeeees')
p.Parse('s')
#print p.Parse('dddddddds')
#print p.Parse('ds')


