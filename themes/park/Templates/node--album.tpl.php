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

        drupal_add_css("sites/all/modules/_JS/Ad-gallery/css/jquery.ad-gallery.css", array('preprocess' => FALSE)); // array('group' => CSS_THEME, 'preprocess' => FALSE)
        drupal_add_css("sites/all/modules/_JS/Ad-gallery/css/jquery.ad-gallery_custom.css", array('preprocess' => FALSE)); // array('group' => CSS_THEME, 'preprocess' => FALSE)

        drupal_add_js('sites/all/modules/_JS/Ad-gallery/a4s_image_gallery_ad.js');
        drupal_add_js('sites/all/modules/_JS/Ad-gallery/jquery.ad-gallery.js');
        
        //1, 3, 4, 
        drupal_add_css("sites/all/modules/_JS/Colorbox/css4/colorbox.css", array('preprocess' => FALSE)); // array('group' => CSS_THEME, 'preprocess' => FALSE)
        drupal_add_js('sites/all/modules/_JS/Colorbox/jquery.colorbox.js');
        
        drupal_add_js('
            
                    jQuery(document).ready(function(){
                            //Examples of how to assign the ColorBox event to elements
                            jQuery(".group_' . $node->nid .'").colorbox({transition:"fade", slideshow:true, slideshowAuto: false, rel:"group_' . $node->nid . '", width:"95%", height:"95%"});

                            //$(".group2").colorbox({rel:"group2", transition:"fade"});
                            //$(".group3").colorbox({rel:"group3", transition:"none", width:"75%", height:"75%"});
                            //$(".group4").colorbox({rel:"group4", slideshow:true});
                    });

                ', 'inline');
        
        
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