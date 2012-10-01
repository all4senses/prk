<?php
/**
 * @file views-view-rss.tpl.php
 * Default template for feed displays that use the RSS style.
 *
 * @ingroup views_templates
 */
?>
<?php print "<?xml"; ?> version="1.0" encoding="utf-8" <?php print "?>"; ?>
<rss version="2.0" xmlns:atom="http://www.w3.org/2005/Atom" xml:base="<?php print $link; ?>"<?php print $namespaces; ?>>
  <channel>
    <atom:link href="<?php print 'http://gocloudbackup.com' . $_SERVER['REQUEST_URI']; ?>" rel="self" type="application/rss+xml" />
    <title><?php print $title; ?></title>
    <link><?php print $link; ?></link>
    <description><?php print $description; ?></description>
    <language><?php print $langcode; ?></language>
    <?php print $channel_elements; ?>
    <?php print $items; ?>
  </channel>
</rss>