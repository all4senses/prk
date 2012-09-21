<?php 

hide($content['comments']);
hide($content['links']);


if (!$page)
    echo '<h2 class="title"' , $title_attributes , '><a href="' , $node_url, '" title="' , $title , '">' , $title , '</a></h2>';
else
    echo '<h2 class="title"' , $title_attributes , '>' , $title , '</h2>';

echo '<div class="meta">';
    if ($display_submitted)
        echo '<div class="submitted">' , t('!datetime &#151; !username', array('!username' => $name, '!datetime' => $date)) , '</div>';
echo '</div>';

  if (!empty($content['links']['terms']))
    echo '<div class="terms>' , render($content['links']['terms']) , '</div>';

echo '<div class="content"' , $content_attributes. '>';

    
    if(!isset($_GET['t']) || $_GET['t'] == 'full') {
        $show_slideshow = false;
        //echo render($content['body']);
        echo '<div class="mode"><a href="' , $node_url, '?t=slideshow" title="' , t('View as slideshow') , '">View as slideshow</a></div>';
    }
    elseif(isset($node->field_body_to_gallery['und']) AND $node->field_body_to_gallery['und'][0]['value']) {
        $show_slideshow = true;
        echo '<div class="mode"><a href="' , $node_url, '" title="' , t('View in full') , '">View in full</a></div>';
        echo $node->field_body_to_gallery['und'][0]['value'];
        drupal_add_js(array('park_image' => array('group_' . $node->nid => 1)), 'setting');
        
        hide($content['body']);
    }

    // in teaser somehow direct render($content) doesn't show body
    // so show it another way
    if(!$show_slideshow AND $view_mode == 'teaser') {
      echo $content['body']['#items'][0]['value']; 
    }
    
    echo render($content);

echo '</div>';

if ($content['links'])
  echo '<div class="links">' . render($content['links']) . '</div>';

print render($content['comments']);