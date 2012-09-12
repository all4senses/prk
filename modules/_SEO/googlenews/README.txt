-- SUMMARY --

The GoogleNews module generates a Google news compatible sitemap feed from your Drupal 7 site
This module is distributed 'as is' and no warranties or support can be given.

-- INSTALLATION --

* Install by unzipping and copying the files into your sites/all/modules directory
* See http://drupal.org/node/70151 for further information.

-- CONFIGURATION --

* Without any configuration, the module should generate a Google News sitemap feed from the
  following URL:

	http://www.yoursitename.com/googlenews.xml

* By default the module will generate the feed for ALL content types.

* As Google News expects only news articles, you will probably want to choose the content types
  that the feed should use.

* Choose content types by visiting:

  Administer >> Site configuration >> Google News sitemap feed

  You can select one or more content types, then click 'Save Configuration'.

-- USAGE --


* Once installed, you should be able to visit http://www.yoursitename.com/googlenews.xml and see the Google news sitemap feed

* You can now go into Google webmaster tools and add the URL to the sitemap

-- CONTACT --

* Adam: <http://www.webopius.com>  gnews@webopius.com
