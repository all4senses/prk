
<?php if (!$page): ?>
  <article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
<?php endif; ?>


    <?php if (!$page): ?>
      <header>
	<?php endif; ?>

      <?php if ($page): ?>
        <h1 <?php print ' ' . /*$title_attributes*/ /*preg_replace('/datatype=".*"/', '', $title_attributes);*/ preg_replace('/datatype=""/', '', $title_attributes); ?>>
        <?php else: ?>
        <h2 <?php print ' ' . /*$title_attributes*/ /*preg_replace('/datatype=".*"/', '', $title_attributes);*/ preg_replace('/datatype=""/', '', $title_attributes); ?>>
      <?php endif; ?>
     
            <?php if (!isset($node->title_no_link) && !$page): ?>
              <a href="<?php print $node_url; ?>">
                <?php print $title; ?>
              </a>
            <?php else: ?>
              <?php print $title; ?>
            <?php endif; ?>

      <?php if ($page): ?>
      </h1>
      <?php else: ?>
      </h2>
      <?php endif; ?> 
  
      <?php if ($display_submitted): ?>
        <span class="submitted"><?php print $submitted; ?></span>
      <?php endif; ?>

    <?php if (!$page): ?>
      </header>
	<?php endif; ?>


  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // Hide comments, tags, and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['field_tags']);
      echo render($content);
      
    ?>
  </div>

  <?php if (!empty($content['field_tags']) || !empty($content['links'])): ?>
    <footer>
      <?php print render($content['field_tags']); ?>
      <?php //print render($content['links']); ?>
    </footer>
  <?php endif; ?>

<?php //hide($content['links']); //print render($content['comments']); ?>

<?php if (!$page): ?>
  </article> <!-- /.node -->
<?php endif; ?>

  
<?php 
  if (isset($node->sectionBlocks)) {
    foreach ($node->sectionBlocks as $sectionBlock) {
      echo $sectionBlock;
    }
  }
?>