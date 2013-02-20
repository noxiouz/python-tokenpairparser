import _tokenparser as p


t = p.Tokenparser()

t.upTo('FIELD','1')
t.skip('1')
t.skip(' ')
t.parse('DDD1 ')
print t.matches()
t.clearMatches()
t.parse('ZZZ1 ')
print t.matches()
t.clearMatches()
print t.multilinesParse(['DDD1 ',2,'ZZZ1 '])
