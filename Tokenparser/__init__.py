import _tokenparser


class Tokenparser(_tokenparser.Tokenparser, object):

    def __init__(self):
        super(Tokenparser, self).__init__()

    def skip(self, char):
        '''skip(char)

        Skip giving symbol

        :param char: skiping char
        '''
        return super(Tokenparser, self).skip(char)

    def skipTo(self, char):
        '''skipTo(char)

        Skip all characters until the occurrence of ``char`` (exclude ``char``)

        :param char: letter to the occurrence of which skipping characters
        '''
        return super(Tokenparser, self).skipTo(char)

    def fromTo(self, field, fr, to):
        '''fromTo(field, fr, to)

        Capture all characters from ``from`` to
        ``to`` (include ``to``) into ``field``

        :param field: string
        :param from: char
        :param to: char
        '''
        return super(Tokenparser, self).fromTo(field, fr, to)

    def upTo(self, field, to):
        '''upTo(field, char)

        Capture all characters until
        the occurrence of ``char`` (include ``char``)

        :param field: field's name
        :param char: letter to the occurrence of which capturing characters'''
        return super(Tokenparser, self).upTo(field, to)
