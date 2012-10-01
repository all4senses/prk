<?php

/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 */
?>
<div class="profile"<?php print $attributes; ?>>
  <?php //print render($user_profile); ?>
  
  <?php //dpm($user_profile); ?>
  
  <?php 
 
    $user_name = $user_profile['field_u_fname'][0]['#markup'] . ' ' . $user_profile['field_u_lname'][0]['#markup'];
    
    echo '<div id="user-caption">Meet: ' , $user_name, '</div>', render($user_profile['user_picture']), render($user_profile['field_u_bio']),  '<div class="bottom-clear"></div>';
    
    $articles = views_embed_view('articles','block_all_by_author');
    if ($articles) {
      echo '<div id="articles-caption">', t('Read some of !author\'s latest articles below:', array('!author' => $user_profile['field_u_fname'][0]['#markup'])), '</div>', $articles;
    }
    /*
    $articles = views_embed_view('articles','block_by_author');
    $blog_posts = views_embed_view('blog','block_by_author');
    $news_posts = views_embed_view('news','block_by_author');
  
  ?>
  <?php if ($articles || $blog_posts || $news_posts): ?>
  
    <?php // Add tabs js.
      $module_path = drupal_get_path('module', 'gv_pages');
      drupal_add_library('system', 'ui.tabs');
      drupal_add_js( $module_path . '/js/gv_provider_tabs.js'); 
    ?>
    <div class="data tabs">

      <ul>
        <?php echo ($articles ? '<li><a href="#tabs-1">' . t('Articles') . '</a></li>' : ''); ?>
        <?php echo ($blog_posts ? '<li><a href="#tabs-2">' . t('Blog posts') . '</a></li>' : ''); ?>
        <?php echo ($news_posts ? '<li><a href="#tabs-3">' . t('News posts') . '</a></li>' : ''); ?>
      </ul>

      <?php if ($articles): ?>
        <div id="tabs-1">
          <?php echo $articles; ?>
          <div class="bottom-clear"></div>
        </div>
      <?php endif; ?>
      
      <?php if ($blog_posts): ?>
        <div id="tabs-2">
          <?php echo $blog_posts; ?>
          <div class="bottom-clear"></div>
        </div>
      <?php endif; ?>
      
      <?php if ($news_posts): ?>
        <div id="tabs-3">
          <?php echo $news_posts; ?>
          <div class="bottom-clear"></div>
        </div>
      <?php endif; ?>

    </div>
  <?php endif; ?>
  <?php */?>
  
  
 </div>
