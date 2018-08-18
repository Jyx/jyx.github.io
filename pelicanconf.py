#!/usr/bin/env python
# -*- coding: utf-8 -*- #
from __future__ import unicode_literals

AUTHOR = 'Joakim Bech'
SITENAME = 'joakimbech.com'
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
#SOCIAL = (('Jyxxan @ Facebook', 'https://www.facebook.com/Jyxxan'),
#          ('Jyxxan @ Twitter', 'https://twitter.com/Jyxxan'),
#          ('Joakim @ LinkedIn', 'https://www.linkedin.com/in/jbech'),
#          ('Joakim @ GitHub', 'https://github.com/jbech-linaro'),)

DEFAULT_PAGINATION = 10

# Uncomment following line if you want document-relative URLs when developing
#RELATIVE_URLS = True
THEME = 'pelican-themes/blueidea'
DISPLAY_CATEGORIES_ON_MENU = False
DISPLAY_CATEGORIES_ON_SUBMENU = True
DISPLAY_AUTHOR_ON_POSTINFO = True
DISPLAY_CATEGORIES_ON_POSTINFO = True
DISPLAY_PAGES_ON_MENU = False
DISPLAY_SEARCH_FORM = False

#THEME = 'pelican-themes/Just-Read/'
#THEME = 'pelican-themes/nice-blog/'
#THEME = 'pelican-themes/Nuja/'

#THEME = 'pelican-themes/pelican-blue/'
SOCIAL = (('linkedin', 'https://www.linkedin.com/in/jbech'),
          ('github', 'https://github.com/jbech-linaro'),
          ('twitter', 'https://twitter.com/Jyxxan'),
          ('facebook', 'https://www.facebook.com/Jyxxan'),
          )

#THEME = 'pelican-themes/storm'
#THEME = 'pelican-themes/sundown'

#LOAD_CONTENT_CACHE = False
DISPLAY_PAGES_ON_MENU = True
SUMMARY_MAX_LENGTH = 80

PLUGIN_PATHS = ['pelican-plugins']
PLUGINS = ['assets']
