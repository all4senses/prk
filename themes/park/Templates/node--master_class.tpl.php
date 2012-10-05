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

    if ($page) {
      hide($content['body']);
      echo $node->main_content;
    }
    
    echo render($content);

echo '</div>';

if ($content['links'])
  echo '<div class="links">' . render($content['links']) . '</div>';

//print render($content['comments']);





global $user;
$user = user_load($user->uid);

//dpm($user);
//dpm($_SERVER['SERVER_NAME']);
//dpm(park_misc_getPathFromStreamUri($user->picture->uri));

$jso = '[{"cmd":"streamMessage","stream_id":"506df91b6bf6ab2311003736","widget_id":3235,"text":"Коммент
45","acc_id":31552,"nick":"Park
Boss","id":"1349405543346162","ip":"91.200.156.93","user_id":"1","category":0,"link":"park.all4senses.com\/u\/marliti\/master-classes\/mk-po-pleteniyu-vetochki-sosny"}]';
dpm($jso);
dpm('xxx');
$jso = str_replace('
', '', $jso);
dpm(json_decode($jso));

$user_auth = array(
'nick' => $user->field_first_name['und'][0]['value']  . ' ' . $user->field_last_name['und'][0]['value'],
'avatar' => 'http://' . $_SERVER['SERVER_NAME'] . '/' . park_misc_getPathFromStreamUri($user->picture->uri),
'url' => 'http://park.all4senses.com',
'href' => 'http://park.all4senses.com',
'link' => 'http://park.all4senses.com',
'home' => 'http://park.all4senses.com',
'uri' => 'http://park.all4senses.com',
'id' => $user->uid,
'email' => $user->mail,
);

$time = time();
$secret = "123321";
$user_base64 = base64_encode( json_encode($user_auth) );
$sign = md5($secret . $user_base64 . $time);
$auth = $user_base64 . "_" . $time . "_" . $sign;



?>

<!--
<div id="mc-container"></div>
<script type="text/javascript">
var mcSite = '10053';
(function() {
    var mc = document.createElement('script');
    mc.type = 'text/javascript';
    mc.async = true;
    mc.src = 'http://cackle.me/mc.widget-min.js';
    (document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(mc);
})();
</script>
<a href="http://cackle.me" id="mc-link">система комментирования <b style="color:#4FA3DA">CACKL</b><b style="color:#F65077">E</b></a>
-->

<script type="text/javascript">
var _hcp = _hcp || {};_hcp.widget_id = 3235;_hcp.widget = "Stream"; _hcp.auth = "<?php echo $auth; ?>";
(function() { 
var hcc = document.createElement("script"); hcc.type = "text/javascript"; hcc.async = true;
hcc.src = ("https:" == document.location.protocol ? "https" : "http")+"://widget.hypercomments.com/apps/js/hc.js";
var s = document.getElementsByTagName("script")[0]; s.parentNode.insertBefore(hcc, s.nextSibling); 
})();
</script>
<div id="hypercomments_widget"></div>