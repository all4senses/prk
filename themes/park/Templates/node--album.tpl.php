<?php 

//dpm($node); dpm($content);

//hide($content['body']);
hide($content['field_body_to_gallery']);
hide($content['comments']);
hide($content['links']);

print render($title_prefix); 

if (!$page) {
  echo '<h2 class="title"' , $title_attributes , '><a href="' , $node_url, '" title="' , $title , '">' , $title , '</a></h2>';
}
else {
  echo '<h2 class="title"' , $title_attributes , '>' , $title , '</h2>';
}
print render($title_suffix); 

echo '<div class="meta">';
    if ($display_submitted) {
      echo '<div class="submitted">' , t('!datetime &#151; !username', array('!username' => $name, '!datetime' => $date)) , '</div>';
    }
echo '</div>';

  if (!empty($content['links']['terms'])) {
    echo '<div class="terms>' , render($content['links']['terms']) , '</div>';
  }

echo '<div class="content"' , $content_attributes. '>';

    $show_slideshow = false;
    if(isset($_GET['t']) AND $_GET['t'] == 'full') {
        //echo render($content['body']);
        echo '<div class="mode"><a href="' , $node_url, '" title="' , t('View as slideshow') , '">View as slideshow</a></div>';
    }
    elseif(isset($node->field_body_to_gallery['und']) AND $node->field_body_to_gallery['und'][0]['value']) {
        $show_slideshow = true;
        echo '<div class="mode"><a href="' , $node_url, '?t=full" title="' , t('View in full') , '">View in full</a></div>';
        hide($content['body']);
        echo $node->field_body_to_gallery['und'][0]['value'];

//        drupal_add_js('sites/all/libraries/jquery.plugins/Ad-gallery/jquery.ad-gallery.js');
//        drupal_add_css('sites/all/libraries/jquery.plugins/Ad-gallery/css/jquery.ad-gallery.css', array('preprocess' => FALSE)); // array('group' => CSS_THEME, 'preprocess' => FALSE)
//        
//        //1, 3, 4, 
//        drupal_add_js('sites/all/libraries/jquery.plugins/Colorbox/jquery.colorbox.js');
//        drupal_add_css('sites/all/libraries/jquery.plugins/Colorbox/css4/colorbox.css', array('preprocess' => FALSE)); // array('group' => CSS_THEME, 'preprocess' => FALSE)
//        
//        $path_to_module = drupal_get_path('module', 'park_image');
//        drupal_add_js($path_to_module . '/js/park_add_Colorbox_ToAlbums.js');
//        drupal_add_js($path_to_module . '/js/park_add_Gallery-ad_ToAlbums.js');
//        drupal_add_css($path_to_module . '/css/park_add_Gallery-ad_ToAlbums.css', array('preprocess' => FALSE)); // array('group' => CSS_THEME, 'preprocess' => FALSE)
  
        drupal_add_js(array('park_image' => array('group_' . $node->nid => 1)), 'setting');
    }

    // in teaser somehow direct render($content) doesn't show body
    // so show it another way
    if(!$show_slideshow AND $view_mode == 'teaser') {
      echo $content['body']['#items'][0]['value']; 
    }
    
    print render($content);

echo '</div>';

if ($content['links']) {
  echo '<div class="links">' . render($content['links']) . '</div>';
}

print render($content['comments']);