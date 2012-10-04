<?php 

hide($content['comments']);
hide($content['links']);

dpm($node);

if (!$page) {
  echo '<h2 class="title"' , $title_attributes , '><a href="' , $node_url, '" title="' , $title , '">' , $title , '</a></h2>';
}
else {
  echo '<h2 class="title"' , $title_attributes , '>' , $title , '</h2>';
}

echo '<div class="meta">';
    if ($display_submitted) {
      echo '<div class="submitted">' , t('!datetime &#151; !username', array('!username' => $name, '!datetime' => $date)) , '</div>';
    }
echo '</div>';

  if (!empty($content['links']['terms'])) {
    echo '<div class="terms>' , render($content['links']['terms']) , '</div>';
  }

echo '<div class="content"' , $content_attributes. '>';

    if ($page) {
      hide($content['body']);
      echo $node->main_content;
    }
    print render($content);

echo '</div>';

if ($content['links']) {
  echo '<div class="links">' . render($content['links']) . '</div>';
}

print render($content['comments']);