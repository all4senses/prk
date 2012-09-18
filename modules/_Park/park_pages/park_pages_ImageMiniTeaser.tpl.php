<?php

//dpm(get_defined_vars());
//dpr($node);

echo '<h2 class="title"><a href="/' , $node->node_url, '" title="' , $node->title , '">' , $node->title , '</a></h2>';

echo '<div class="meta">';
    //if ($display_submitted)
        echo '<div class="submitted">' , t('!datetime &#151; !username', array('!username' => $node->name, '!datetime' => $node->date)) , '</div>';
echo '</div>';

if($node->main_image)
{
    $image = unserialize($node->main_image);
    dpm($image);
    if(!isset($image['thumb']))
    {
        $image_title = isset($image['tiltle'])?'" title="' . $image['tiltle'] . '"':'';
        $image_alt = isset($image['alt'])?'" alt="' . $image['alt'] . '"':'';
        echo '<div class="main_image"><img src="' . $image['src'] . '"' . $image_title . $image_alt . '" /></div>';
    }
    else
        echo $image['thumb'];
    
}







