import Tokenparser

t = Tokenparser.Tokenparser()

t.upTo('FIELD','1')
t.skip('1')
t.skip(' ')

if t.parse('DDD1 '):  # True
	print(t.matches())
	t.clearMatches()

if t.parse('ZZZ1A'):  # False
	print(t.matches())
	t.clearMatches()

print(t.multilinesParse(['DDD1 ',2,'ZZZ1 ']))
