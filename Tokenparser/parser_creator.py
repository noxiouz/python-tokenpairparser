#! /usr/bin/env python
#
# Copyright (c) 2014 Tyurin Anton noxiouz@yandex.ru
#
# This file is part of Tokenparser for Python.
#
# Tokenparser for Python is free software;
# you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# Tokenparser for Python is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#

import yaml
import sys

try:
    INPUT_FILE = sys.argv[1]
    OUTPUT_FILE = sys.argv[2]
    CONFIG_FILE = sys.argv[3]
except Exception as err:
    print "Usage: prog_name my_log.log output.py config"
    exit(1)

with open(INPUT_FILE) as f:
    s = f.readline()

cfg = yaml.load(open(CONFIG_FILE))


class Generator(object):

    def __init__(self, example, config):
        self._cfg = config
        self.example = example
        self._source = list()
        self._source.append("import Tokenparser")
        self._source.append("from pprint import pprint")
        self._source.append("p = Tokenparser.Tokenparser()")
        self._source.append("example = \"\"\"%s\"\"\"" % example)

    def get_borders(self, target):
        print "Find %s" % target
        begin = self.example.find(target)
        if begin == -1:
            print "Unabel to find %s. Please, verify your config" % target
            exit(1)
        end = begin + len(target)
        return begin, end

    def generate(self):
        for k, v in (next(item.iteritems()) for item in self._cfg):
            b, e = self.get_borders(v)
            self.generate_command(b, e, k)
            self.example = self.example[e:]
        self._source.append("p.parse(example)")
        self._source.append("pprint(p.matches())")
        return '\n'.join(self._source)

    def generate_command(self, begin, end, field):
        if begin == 0:
            code = "p.upTo('%s','%s')" % (field, self.example[end])
            self._source.append(code)
        else:
            for i in xrange(begin):
                self._source.append("p.skip('%s')" % self.example[i])
            code = "p.upTo('%s', '%s')" % (field,
                                           self.example[end].replace('\n',
                                                                     r'\n'))
            self._source.append(code)

if __name__ == "__main__":
    f = open(OUTPUT_FILE, "w")
    G = Generator(s, cfg)
    source = G.generate()
    f.write(source)
    f.close()
