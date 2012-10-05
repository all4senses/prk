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

$jso = 'HC notify data:data===[{"cmd":"streamMessage","stream_id":"506df91b6bf6ab2311003736","widget_id":3235,"text":"Коммент59","acc_id":31552,"nick":"ParkBoss","id":"1349412545670099","ip":"91.200.156.93","user_id":"1","category":0,"link":"park.all4senses.com\/u\/marliti\/master-classes\/mk-po-pleteniyu-vetochki-sosny"}]time===1349412545signature===09706eca39e6a67314b8230142c223a1';

//dpm($jso);
//dpm('xxx');
//$jso = str_replace('
//', '', $jso);
//dpm($jso);


//preg_match('/.*(\[.*\]).*/i', $jso, $match);
//dpm($match);

//$res = preg_replace('/.*(\[.*\]).*/i', '$1', $jso);
//dpm($res);


$json = '"cmd":"streamMessage","stream_id":"506df91b6bf6ab2311003736","widget_id":3235,"text":"Коммент59","acc_id":31552,"nick":"ParkBoss","id":"1349412545670099","ip":"91.200.156.93","user_id":"1","category":0,"link":"park.all4senses.com\/u\/marliti\/master-classes\/mk-po-pleteniyu-vetochki-sosny"';

$json_data = array();
$json = explode(',"', $json);
foreach ($json as $pair) {
  $pair = explode('":', $pair);
  $key = trim($pair[0], '"');
  $value = trim($pair[1], '"');
  $json_data[$key] = $value;
}

dpm($json_data);
dpm(serialize($json_data));


//$a = 'a:11:{s:3:"cmd";s:13:"streamMessage";s:9:"stream_id";s:24:"506df91b6bf6ab2311003736";s:9:"widget_id";s:4:"3235";s:4:"text";s:11:"Comment 100";s:6:"acc_id";s:5:"31552";s:4:"nick";s:9:"Park Boss";s:2:"id";s:16:"1349434032747332";s:2:"ip";s:13:"91.200.156.93";s:7:"user_id";s:1:"1";s:8:"category";s:1:"0";s:4:"link";s:79:"park.all4senses.com\/u\/marliti\/master-classes\/mk-po-pleteniyu-vetochki-sosny";}';
$a = 'a:3:{s:4:"data";a:1:{i:0;O:8:"stdClass":11:{s:3:"cmd";s:13:"streamMessage";s:9:"stream_id";s:24:"506df91b6bf6ab2311003736";s:9:"widget_id";i:3235;s:4:"text";s:11:"comment 102";s:6:"acc_id";i:31552;s:4:"nick";s:9:"Park Boss";s:2:"id";s:16:"1349435462471789";s:2:"ip";s:13:"91.200.156.93";s:7:"user_id";s:1:"1";s:8:"category";i:0;s:4:"link";s:75:"park.all4senses.com/u/marliti/master-classes/mk-po-pleteniyu-vetochki-sosny";}}s:4:"time";s:10:"1349435462";s:9:"signature";s:32:"cfe9e368ac350bf0b82007c44fa00c2b";}';
dpm($a);
dpm(unserialize($a));


//dpm(json_decode($jso));

$user_auth = array(
  'nick' => $user->field_first_name['und'][0]['value']  . ' ' . $user->field_last_name['und'][0]['value'],
  'avatar' => isset($user->picture->uri) ? 'http://' . $_SERVER['SERVER_NAME'] . '/' . park_misc_getPathFromStreamUri($user->picture->uri) : '',
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