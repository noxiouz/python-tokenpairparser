#! /usr/bin/env python

import Tokenparser


def create_obejct(meth_and_args):
    p = Tokenparser.Tokenparser()
    for meth, args in meth_and_args.iteritems():
        getattr(p,meth)(*args)
    return p

def create_parser_from_YAML(path="test.yaml"):
    import yaml
    return create_obejct(yaml.load(open(path))['PARSER OBJECT'])

def create_parser_from_JSON(path="test.json"):
    import json
    return create_obejct(json.load(open(path))['PARSER OBJECT'])

if __name__ == "__main__":
    f = create_parser_from_YAML()
    print f.parse("DDDACEEED")
    f = create_parser_from_JSON()
    print f.parse("DDDACEEED")
