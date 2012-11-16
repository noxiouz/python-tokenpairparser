import Tokenparser

p = Tokenparser.Tokenparser()
p.upTo('FIELD','A') #DDD
p.skip('A') #A
p.fromTo('FIELD2','C','D') #CEEED
p.parse("DDDACEEED")
print p.matches() # return dict like {"FIELD": "DDD", "FIELD2" : "CEEED"}
print p.matches() # return dict like {"FIELD": "DDD", "FIELD2" : "CEEED"}
p.clearMatches()
print p.matches() # return dict like {"FIELD": "DDD", "FIELD2" : "CEEED"}

