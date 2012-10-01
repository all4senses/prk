<?php
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>
  
  <?php if ($id == 2) { echo gcb_pages_getTopProvidersBlocksForArticlesDirectory(); } ?>
  
  <div class="<?php print $classes_array[$id]; ?>">
    <?php print $row; ?>
  </div>
<?php endforeach; ?>
