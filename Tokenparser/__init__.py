import _tokenparser


class Tokenparser(_tokenparser.Tokenparser, object):
    '''
    Usage::

        import Tokenparser

        p = Tokenparser.Tokenparser()
        p.upTo('FIELD','A')  # DDD
        p.skip('A') #A
        p.fromTo('FIELD2','C','D')  # CEEED
        p.parse("DDDACEEED")
        print(p.matches())  # -> {"FIELD": "DDD", "FIELD2" : "CEEED"}
        print(p.matches())  # -> {"FIELD": "DDD", "FIELD2" : "CEEED"}
        p.clearMatches()
        print(p.matches())  # -> {}
    '''

    def __init__(self):
        super(Tokenparser, self).__init__()

    def skip(self, char):
        '''skip(char)

        :param char: skiping char

        Skip giving symbol
        '''
        return super(Tokenparser, self).skip(char)

    def skipTo(self, char):
        '''skipTo(char)

        :param char: letter to the occurrence of which skipping characters

        Skip all characters until the occurrence of ``char`` (exclude ``char``)
        '''
        return super(Tokenparser, self).skipTo(char)

    def fromTo(self, field, fr, to):
        '''fromTo(field, fr, to)

        :param field: string
        :param from: char
        :param to: char

        Capture all characters from ``from`` to
        ``to`` (include ``to``) into ``field``
        '''
        return super(Tokenparser, self).fromTo(field, fr, to)

    def upTo(self, field, to):
        '''upTo(field, char)

        :param field: field's name
        :param char: letter to the occurrence of which capturing characters

        Capture all characters until
        the occurrence of ``char`` (include ``char``)
        '''
        return super(Tokenparser, self).upTo(field, to)

    def parse(self, input_string):
        '''parse(input) -> bool

        :param input: input string for parsing

        Parse giving input string. In the case of full compliance
        with the rules return ``True``, otherwise - ``False``
        
        You can retrieve the result with `Tokenparser.matches()`
        '''
        return super(Tokenparser, self).parse(input_string)

    def matches(self):
        '''matches() -> dict

        Return dict with field as key, and token as value.
        Don't clean result.
        '''
        return super(Tokenparser, self).matches()

    def clearMatches(self):
        '''clearMatches()

        Clean result of parsing.
        '''
        return super(Tokenparser, self).clearMatches()

    def multilinesParse(self, iterable_input):
        '''multilinesParse(iterable_input) -> list

        :param iterable_input: iterable object of string (tuple, list, etc)

        Return list of dict such as in matches, but only for strings which
        are parsed fully.
        '''
        return super(Tokenparser, self).multilinesParse(iterable_input)
