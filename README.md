TokenPairParser
===============


example: Let's parse string like "DDDACEEED"

```python
import _tokenparser as pars

p = pars.Parser()
p.upTo('FIELD','A') #DDD
p.skip('A') #A
p.fromTo('FIELD2','C','D') #CEEED
p.Parse("DDDACEEED")
print p.matches() # return dict like {"FIELD": "DDD", "FIELD2" : "CEEED"}
```
