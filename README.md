# Tokenparser
[![Code Health](https://landscape.io/github/noxiouz/python-Tokenpair-parser-on-C-API/master/landscape.png)](https://landscape.io/github/noxiouz/python-Tokenpair-parser-on-C-API/master)
[![Status](https://travis-ci.org/noxiouz/python-tokenpairparser.svg)](https://travis-ci.org/noxiouz/python-tokenpairparser)

## Example
Let's parse string like "DDDACEEED"

```python
import Tokenparser

p = Tokenparser.Tokenparser()
p.upTo('FIELD','A') #DDD
p.skip('A') #A
p.fromTo('FIELD2','C','D') #CEEED
p.parse("DDDACEEED")
print p.matches() # return dict like {"FIELD": "DDD", "FIELD2" : "CEEED"}
```

# Generating parser by parser_creator.py

Write config like (see examples/exaple-config.py):
```yaml
#2013:12:57:45 +0400] my.host.some.net ::ffff:1.1.1.1 "GET /someurl/someurl2/orig HTTP/1.1" 200 "http://tv.yandex.ru/12424/" "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.31 (KHTML, like Gecko) Chrome/26.0.1410.64 Safari/537.31" "-" 0.000 HIT 1908 "-" "/get-tv-FFFZZFWF/FFFF/orig" "-" -
- TIME: "2013:12:57:45 +0400"
- HOST: my.host.some.net
- IP: ::ffff:1.1.1.1
- METHOD: GET
- URL: /someurl/someurl2/orig
- HTTP_METHOD: HTTP/1.1
- CODE: "200"
- REF: http://tv.yandex.ru/12424/
- UA: "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.31 (KHTML, like Gecko) Chrome/26.0.1410.64 Safari/537.31"
- CACHE: HIT
- ANOTHER_URI: /get-tv-FFFZZFWF/FFFF/orig
- SMT: "-"
- END: "-"
```

Start script:
```
python -m Tokenparser.parser_creator.py examples/example.log my_parser.py examples/example-config.yaml&& python my_parser.py
```
And you see:
```json
{
"ANOTHER_URI": "/get-tv-FFFZZFWF/FFFF/orig",
"CACHE": "HIT",
"CODE": "200",
"END": "-",
"HOST": "my.host.some.net",
"HTTP_METHOD": "HTTP/1.1",
"IP": "::ffff:1.1.1.1",
"METHOD": "GET",
"REF": "http://tv.yandex.ru/12424/",
"SMT": "-",
"TIME": "2013:12:57:45 +0400",
"UA": "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.31 (KHTML, like Gecko) Chrome/26.0.1410.64 Safari/537.31",
"URL": "/someurl/someurl2/orig"
}
```
