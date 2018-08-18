#!/usr/bin/env python
# -*- coding: utf-8 -*- #
from __future__ import unicode_literals

AUTHOR = 'Joakim Bech'
SITENAME = 'joakimbech.com - A trash can full of ideas'
SITEURL = ''

PATH = 'content'
STATIC_PATHS = ['images', 'downloads']

TIMEZONE = 'Europe/Paris'

DEFAULT_LANG = 'en'

ARTICLE_URL = 'blog/{date:%Y}/{date:%m}/{date:%d}/{slug}/'
ARTICLE_SAVE_AS = 'blog/{date:%Y}/{date:%m}/{date:%d}/{slug}/index.html'

# Feed generation is usually not desired when developing
FEED_ALL_ATOM = 'feeds/all.atom.xml'
CATEGORY_FEED_ATOM = None
TRANSLATION_FEED_ATOM = None
AUTHOR_FEED_ATOM = 'feeds/%s.rss.xml'
AUTHOR_FEED_RSS = None
RSS_FEED_SUMMARY_ONLY = False

# Blogroll
LINKS = (('Pelican', 'http://getpelican.com'),
         ('Linaro', 'https://linaro.org'),)

# Social widget
SOCIAL = (('Jyxxan @ Facebook', 'https://www.facebook.com/Jyxxan'),
          ('Jyxxan @ Twitter', 'https://twitter.com/Jyxxan'),
          ('Joakim @ LinkedIn', 'https://www.linkedin.com/in/jbech'),
          ('Joakim @ GitHub', 'https://github.com/jbech-linaro'),)

DEFAULT_PAGINATION = 10

# Uncomment following line if you want document-relative URLs when developing
#RELATIVE_URLS = True
THEME = 'pelican-themes/blueidea'

LOAD_CONTENT_CACHE = False


