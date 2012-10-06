<?php

/*
 * Class for social actions.
 */

/*
function park_social_menu() {
    
  $items = array();
        
  $items['user/%user/social'] = array( 
      'title' => t('Social connect'),
      'page callback' => 'drupal_get_form',
      'page arguments' => array('park_social_socialPageForm', 1),
      ////'page callback' => 'park_social_socialPageShow', 
      //'page arguments' => array(1, 'album', 'album', 'albums', array('t','mini'), 'park_pages_buildMiniTeasersSet'),
      ////'page arguments' => array(1),
      
      'access arguments' => array('access content'),
      'type' => MENU_LOCAL_TASK,
    );  

  $items['authsub'] = array (
    'page callback' => 'park_social_authsub_redirect',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
  );
  
  return $items;
}
*/


/*
function park_social_socialPageShow($user)
{
    return drupal_get_form('park_social_socialPageForm', $user);
}
*/

function park_social_socialPageForm($arg1, $arg2)
{
    //dpm(get_defined_vars());

    $user_url = $arg2['build_info']['args'][0];
     
    /*
    //dpr($user);
    $results = db_query("SELECT * FROM {field_data_field_u_social} WHERE entity_id = :uid", array('uid' => $user_uid));
    if($results->rowCount())
        foreach($results as $result)
            $connected[] = $result;
    */
    
    //$user_url->field_u_social = array(0 => array('name' => 'picasa', 'data' => 'picasa data'), 1 => array('name' => 'facebook', 'data' => 'facebook data') );
 /*
    $user_url->field_u_social = array(
               md5('facebook_423434') => array(
                                'service' => 'facebook', 
                                'service_id' => 1, 
                                'user_uid' => 1,
                                'id' => '423434',
                                'nick' => 'some nick',
                                'access_token' => '34234234234',
                                'account_key' => md5('facebook_423434'),
                                
                                'data' => array('data 1' => 'some data 1'), // or stdClass
                              ),
               md5('picasa_dsfsdfsdf') => array(
                                'service' => 'picasa', 
                                'service_id' => 3, 
                                'user_uid' => 1,
                                'id' => 'dsfsdfsdf',
                                'nick' => 'some nick 2',
                                'access_token' => 'ljhlfjhlfkj',
                                'account_key' => md5('picasa_dsfsdfsdf'),
                                
                                'data' => array('data 2' => 'some data 2'), // or stdClass
                              ),
            
                    );
   */
    
                
    $connected_accounts = (isset($user_url->field_u_social['und'])?unserialize($user_url->field_u_social['und'][0]['value']):null);
    //dpr($connected_accounts);
    $socialInit = new SocialInit($user_url->uid, $connected_accounts, array('disable_same_service_accounts' => false));
  
    $socialInit->connectNewAccount_fromUrlToken();
    /*
    if(isset($_SESSION['connect_to']) AND (isset($_GET['token']) OR isset($_GET['code']) ))
    {
        $newService = $_SESSION['connect_to'];
        unset($_SESSION['connect_to']);
        if(isset($_SESSION['state'])) unset($_SESSION['state']); // only for Facebook accounts
        
        $socialInit->connectAccount($user_url->uid, $newService, $_GET, $currentUrl);
    }
    */
   
    $socialInit->unconnectAccount_fromUrl();
    
    
    
    $form = array();
    
    // show connected accounts form section
    $socialInit->addToForm_connectedAccountsData_section($form);
    /*
    if(!empty($user_url->field_u_social))
    {
        $has_connections = true;
        
        $form['connectedAccounts'] = array(
            '#type' => 'fieldset',
            '#title' => 'Connected Social Networks Accounts',
            '#collapsible' => true,
            '#collapsed' => false,
           );
        
        foreach($user_url->field_u_social as $account_key => $connectedAccount)
        {
            $form['connectedAccounts'][$account_key] = array(
               '#markup' => '<div>' . $connectedAccount['name'] . ' => '  . $connectedAccount['data'] . '</div>',
               );
            
            // disable connect several accounts of the same service
            // unset($socialInit->connect_to[$network['name']]);
        }
    }
    */
    
    // connect new account form section
    $socialInit->addToForm_connectNewAccount_section($form);
    /*
    if(!empty($socialInit->connect_to))
    {
        $currentUrl = $socialInit->getCurrentUrl();
        // connect new account block
        $form['connectNew'] = array(
            '#type' => 'fieldset',
            '#title' => t('Connect your ' . ($has_connections?'another ':'') . 'account'),
            '#collapsible' => true,
        );

        $form['connectNew']['service'] = array(
            '#type' => 'select',
            '#title' => t('Choose a service/social network'),
            '#default_value' => 0, //$_GET['service']?$_GET['service']:0,
            '#options' => array(0=>'- select type -') + $socialInit->getNetworks(),
            '#description' => t('Choose the type one of a service to connect'),
            //'#attributes' => array('onchange' => 'javascript:window.location.href = "' . $currentUrl .  '?type=' . (isset($_GET['type'])?$_GET['type']:'photo-album') . '&service="+' . 'this.value'),
            '#attributes' => array('onchange' => 'javascript:window.location.href = "' . $currentUrl .  '?service="+' . 'this.value'),
        );
    }
    */
  
    
    $socialInit->sendUserToConnectAccount_orShowLink_fromUrl($form, 'just_show_link'); // 'send_user_to_url'
    /*
    if(isset($_GET['service']) AND isset($socialInit->connect_to[$_GET['service']]))
    {
        $_SESSION['connect_to'] = $_GET['service'];

        if($oauth_link = $socialInit->getOauthLink($_GET['service'], $currentUrl))
        {
            $form['connectNew']['auth'] = array(
                '#type' => 'item',
                '#title' => t('Authorization on ') . $socialInit->connect_to[$_GET['service']]['title'],
                '#markup' => 'Please, <a href="' . $oauth_link . '">authorize on ' . $socialInit->connect_to[$_GET['service']]['title'] . '</a> to grant our site the access to your ' . ($has_other_connections?'another ':'') . 'account data.',
                //'#description' => t(''),
            );
            
            // OR...
            // header( 'Location: ' . $oauth_link );
         }
    }
    */
    
    $socialInit->addToForm_accountAlbums_fromUrl($form);

    
    
    $form['text'] = array(
           '#type' => 'textfield',
           '#default_value' => 'Some text field',
           );
    
    return $form;
}

/*
function park_social_theme($existing, $type, $theme, $path) {
  return array(
    'park_social_socialPageForm' => array(
      'path' => path_to_theme() . '/templates',
      'template' => 'park_socialPage',
      'render element' => 'form',
    ),  
            
  );
}
*/



class SocialInit{
   
    // site api credentials for domMoejMechty.com.ua
    var $user_uid, $currentUrl = false, $connectedAccounts = false, $disable_same_service_accounts = false, $has_other_connections = false;
    
    var $connect_to = array(
        'picasa' => array(
                        // all4senses@gmail.com
                        'title' => 'Picasa',
                        ),
        'facebook' => array(
                        // kamchatka.pushistaya@gmail.com
                        'title' => 'Facebook',
                        'client_id' => 138241656284512, //170848282985782,
                        'client_secret' => '99ebdb160b628174358c38d29d2af3cf', //'814c6f051addd0369e55d83ae22b805c',
                       ),
        'vkontakte.ru' => array(
                        // deepsaeon@gmail.com                        
                        'title' => 'Vkontakte.ru',
                        'client_id' => 2706510, // 2421528,
                        'client_secret' => 'uZ69MqrM3Pm3dLkEWDM9', // 'Uyp3IwG9EsDfNgRhUgyF',
                       ),
        'mail.ru' => array(
                        // alexxhome@mail.ru
                        'title' => 'Mail.ru',
                        'client_id' => 655252,
                        'client_secret' => '8b2317b11afd968e3764d1b5e7222a13',
                        'client_private' => 'fdebb1370a19d2f5e7df41ba4495c8b9',
                       ),
        );
    
    
    function __construct($user_uid = null, $connectedAccounts = null, $data = null) 
    { 
        $this->user_uid = $user_uid;
        $this->connectedAccounts = $connectedAccounts;
        $this->currentUrl = $this->getCurrentUrl();
        if(isset($data['disable_same_service_accounts']) AND $data['disable_same_service_accounts'])
            $this->disable_same_service_accounts = true;
    }
    
    
    public function connectNewAccount_fromUrlToken($get = null)
    {
        if(!$get)
            $get = $_GET;
        
        if(isset($_SESSION['connect_to']) AND (isset($get['token']) OR isset($get['code']) ))
        {
            $newService = $_SESSION['connect_to'];
            unset($_SESSION['connect_to']);
            
            if(isset($_SESSION['state'])) unset($_SESSION['state']); // only for Facebook accounts

            return $this->connectAccount($newService, $get);
        }
        
    }
    
    
    public function unconnectAccount_fromUrl($get = null)
    {
        if(!$get)
            $get = $_GET;
        
        if(isset($get['op']) AND $get['op'] == 'unconnect' AND isset($get['accid']) AND $get['accid'])
        {
            global $user;
            // if a current user is the admin or the owner of the current account
            if($this->user_uid == $user->uid OR $user->uid == 1)
            {
                $accountToUnconnect = new SocialConnect($this->user_uid, $this->connectedAccounts, $this->currentUrl, $this->connectedAccounts[$get['accid']]['service'], $this->connectedAccounts[$get['accid']]);
                $accountToUnconnect->unconnectAccount();
            }
            else
            {
                drupal_add_js('alert("Sorry, You have no rights to control this account.");' 
                        . ' window.location.href = "' . $this->currentUrl . '"'
                        , 'inline');
            }
           
        }
        
    } // end of public function unconnectAccount_fromUrl()
    
    public function sendUserToConnectAccount_orShowLink_fromUrl(&$form, $op = 'just_show_link', $get = null)  
    {
        if(!$get)
            $get = $_GET;
        
        if(isset($get['service']) AND isset($this->connect_to[$get['service']]))
        {
            $_SESSION['connect_to'] = $get['service'];

            if($oauth_link = $this->getOauthLink($get['service'], $this->currentUrl))
            {
                if($op == 'just_show_link') //'just_show_link' or 'send_user_to_url'
                {
                    $form['connectNew']['auth'] = array(
                        '#type' => 'item',
                        '#title' => t('Authorization on ') . $this->connect_to[$get['service']]['title'],
                        '#markup' => 'Please, <a href="' . $oauth_link . '">authorize on ' . $this->connect_to[$get['service']]['title'] . '</a> to grant our site the access to your ' . ($this->has_other_connections?'another ':'') . 'account data.',
                        //'#description' => t(''),
                    );
                }
                else // 'send_user_to_url'
                    header( 'Location: ' . $oauth_link );

            }

        }
        
    }
    
    
    public function addToForm_connectedAccountsData_section(&$form)
    {
        if($this->connectedAccounts AND !empty($this->connectedAccounts))
        {
            /*
            $user_url->field_u_social = array(
               md5('facebook_423434') => array(
                                'service' => 'facebook', 
                                'service_id' => 1, 
                                'user_uid' => 1,
                                'id' => '423434',
                                'nick' => 'some nick',
                                'access_token' => '34234234234',
                                'account_key' => md5('facebook_423434'),
                                
                                'data' => array('data 1' => 'some data 1'), // or stdClass
                              ),
               md5('picasa_dsfsdfsdf') => array(
                                'service' => 'picasa', 
                                'service_id' => 3, 
                                'user_uid' => 1,
                                'id' => 'dsfsdfsdf',
                                'nick' => 'some nick 2',
                                'access_token' => 'ljhlfjhlfkj',
                                'account_key' => md5('picasa_dsfsdfsdf'),
                                
                                'data' => array('data 2' => 'some data 2'), // or stdClass
                              ),
            
                    );
            */
             
            $this->has_other_connections = true;

            $form['connectedAccounts'] = array(
                '#type' => 'fieldset',
                '#title' => 'Connected Social networks Accounts',
                '#collapsible' => true,
                '#collapsed' => false,
               );

            foreach($this->connectedAccounts as $account_key => $connectedAccount)
            {
                $form['connectedAccounts'][$account_key] = array(
                    '#type' => 'fieldset',
                    '#title' => ucfirst($connectedAccount['service']) . ' ' . ($connectedAccount['nick']?$connectedAccount['nick']:$connectedAccount['id']),
                    '#collapsible' => true,
                    '#collapsed' => true,
                   );
                $form['connectedAccounts'][$account_key]['data'] = array(
                    '#type' => 'fieldset',
                    '#title' => 'Account data',
                    '#collapsible' => true,
                    '#collapsed' => true,
                   );
                $form['connectedAccounts'][$account_key]['data']['all'] = array(
                    '#markup' => '<div><PRE>' . print_r($connectedAccount['data'], true) . '</PRE></div>'
                   );
                $form['connectedAccounts'][$account_key]['info'] = array(
                   '#markup' => '<div>Account key: ' . $account_key . '</div>'
                              . '<div>Service: ' . $connectedAccount['service'] . '</div>'
                              . '<div>Account Id: ' . $connectedAccount['id'] . '</div>'
                              . ($connectedAccount['nick']?'<div>Nick: ' . $connectedAccount['nick'] . '</div>':'')
                              . '<div>Access token: ' . $connectedAccount['access_token'] . '</div>'
                              . '<div><a href="' . $this->currentUrl . '?op=unconnect&accid=' . $connectedAccount['account_key'] . '">Unconnect this account from our site</a></div>'
                              . '<div><a href="' . $this->currentUrl . '?op=showAlbums&accid=' . $connectedAccount['account_key'] . '">Show this account\'s albums</a></div>',
                   );

                // disable connect several accounts of the same service
                if($this->disable_same_service_accounts)
                    unset($this->connect_to[$connectedAccount['service']]);
            }
            
            
        } // end of if(!empty($connectedAccounts))
        
        return $this->has_other_connections;
        
    } // end of public function addToForm_connectedAccountsData_section(&$form, $connectedAccounts)
    
    
    public function addToForm_connectNewAccount_section(&$form)
    {
        // connect new account form
        if(!empty($this->connect_to))
        {
            if(!$this->currentUrl)
                $this->currentUrl = $this->getCurrentUrl();
            
            // connect new account block
            $form['connectNew'] = array(
                '#type' => 'fieldset',
                '#title' => t('Connect your ' . ($this->has_other_connections?'another ':'') . 'account'),
                '#collapsible' => true,
            );

            $form['connectNew']['service'] = array(
                '#type' => 'select',
                '#title' => t('Choose a service/social network'),
                '#default_value' => 0, //$_GET['service']?$_GET['service']:0,
                '#options' => array(0=>'- select type -') + $this->getNetworks(),
                '#description' => t('Choose the type one of a service to connect'),
                //'#attributes' => array('onchange' => 'javascript:window.location.href = "' . $currentUrl .  '?type=' . (isset($_GET['type'])?$_GET['type']:'photo-album') . '&service="+' . 'this.value'),
                '#attributes' => array('onchange' => 'javascript:window.location.href = "' . $this->currentUrl .  '?service="+' . 'this.value'),
            );
        }
        
    }
    
    
    
    public function getCurrentUrl()
    {
        $url = explode('?', $_SERVER['REQUEST_URI']);
        $url = $url[0];
        $url = "http://".$_SERVER['SERVER_NAME'].$url;
        return $url;
    }

    
    public function connectAccount($service, $get = null)
    {
        /*
        $accountObject = null;
        if(isset($get['token']))
        {
            switch($service)
            {
                case 'picasa':
                    $accountObject = new SocialConnectGoogle($this->user_uid, $this->connectedAccounts, $this->currentUrl, 'picasa');
                    break;
            }
            
        }// end of if(isset($get['token']))
        elseif(isset($get['code']))
        {
            switch($service)
            {
                case 'mail.ru':
                    $accountObject = new SocialConnectMailRu($this->user_uid, $this->connectedAccounts, $this->currentUrl);
                    break;
                case 'vkontakte.ru':
                    $accountObject = new SocialConnectVkontakte($this->user_uid, $this->connectedAccounts, $this->currentUrl);
                    break;
                case 'facebook':
                    $accountObject = new SocialConnectFacebook($this->user_uid, $this->connectedAccounts, $this->currentUrl);
                    break;
            }
            
        } // end of elseif(isset($get['code']))
        */
        
        if(!$get)
            $get = $_GET;
        
        $accountObject = $this->getAccountObjectByServiceName(null, null, null, $service);
        
        if($accountObject)
            $accountObject->connectAccount($get);
        return $accountObject;
                
    } // end of public function connectNewNetwork($get, $network)
    
    
    public function getNetworks()
    {
        //$keys = array_keys($this->connect_to);
        foreach($this->connect_to as $key => $value)
            $networks[$key] = $key;
        
        return $networks;
    }
    
    public function getOauthLink($service, $redirect_url)
    {
        $oauthLink = null;
        
        switch($service)
        {
            case 'picasa':
                $oauthLink = SocialConnectGoogle::getOauthLink($service);
                break;
            case 'facebook':
                $oauthLink = SocialConnectFacebook::getOauthLink($this->connect_to[$service], $redirect_url);
                break;
            case 'vkontakte.ru':
                $oauthLink = SocialConnectVkontakte::getOauthLink($this->connect_to[$service], $redirect_url);
                break;
            case 'mail.ru':
                $oauthLink = SocialConnectMailRu::getOauthLink($this->connect_to[$service], $redirect_url);
                break;
        }
        
        return $oauthLink;
    } // end of public function getOauthLink($service, $redirect_url)
    
    
    public function getAccountObjectByServiceName($user_uid = null, $connectedAccounts = null, $redirect_url = null, $service, $account = null)
    {
        if(!$user_uid)
            $user_uid = $this->user_uid;
        if(!$connectedAccounts)
            $connectedAccounts = $this->connectedAccounts;
        if(!$redirect_url)
            $redirect_url = $this->currentUrl;
        
        switch($service)
        {
            case 'facebook': 
                $accountObject = new SocialConnectFacebook($user_uid, $connectedAccounts, $redirect_url, $service, $account);
                break;
            case 'picasa':
                $accountObject = new SocialConnectGooglePicasa($user_uid, $connectedAccounts, $redirect_url, $service, $account);
                break;
            case 'mail.ru':
                $accountObject = new SocialConnectMailRu($user_uid, $connectedAccounts, $redirect_url, $service, $account);
                break;
            case 'vkontakte.ru':
                $accountObject = new SocialConnectVkontakte($user_uid, $connectedAccounts, $redirect_url, $service, $account);
                break;
            default:
                $accountObject = null;
        }
        return $accountObject;
        
    } // end of public function getSocialObjectByServiceName($service, $user_uid = null, $connectedAccounts = null, $redirect_url = null, $account = null)
    
    
    
    public function dpr($data, $return = true)
    {
        $out = '<PRE>' . print_r($data, $return) . '</PRE>';
        if($return)
            return $out;
        else
            echo $out;
        
    } // end of public function dpr($data, $return = true)
    
    
    public function addToForm_accountAlbums_fromUrl(&$form, $get = null)
    {
        if(!$get)
            $get = $_GET;
        
        if(isset($get['op']) AND $get['op'] == 'showAlbums' AND isset($get['accid']) AND $get['accid'])
        {
            global $user;
            // if a current user is the admin or the owner of the current account
            if($this->user_uid == $user->uid OR $user->uid == 1)
            {
                if(!$this->connectedAccounts[$get['accid']])
                {
                    drupal_add_js('alert("Sorry, No such account connected to this user.");' 
                        . ' window.location.href = "' . $this->currentUrl . '"'
                        , 'inline');
                }
                else
                {
                    $accountObject = $this->getAccountObjectByServiceName(null, null, null, $this->connectedAccounts[$get['accid']]['service'], $this->connectedAccounts[$get['accid']]);
                    
                    $accountObject->addToForm_accountAlbums($form, (isset($get['albid']) AND $get['albid'])?$get['albid']:null );
                    
                    /*
                    $albums = null;
                    
                    $form['albums'] = array(
                        '#type' => 'fieldset',
                        '#title' => t('Albums of ') . $this->connectedAccounts[$_GET['aid']]['service'] . ' - ' . $this->connectedAccounts[$_GET['aid']]['id'],
                        '#collapsible' => true,
                        '#collapsed' => true,
                    );
                    
                    if($errorMessage = $accountObject->getUserAlbums($albums))
                    {
                        $form['albums']['data'] = array(
                            '#markup' => '<div>' . $errorMessage . '</div>',
                        );
                        
                    }
                    elseif(!is_array($albums))
                    {
                        $form['albums']['data'] = array(
                            '#markup' => '<div>This account doesn\'t contain any albums.</div>',
                        );
                    }
                    else
                    {
                         $form['albums']['data'] = array(
                            '#markup' => '<div>' . $this->dpr($albums) . '</div>',
                        );
                        
                    }
                    */
                    
                } // end of else of if(!$this->connectedAccounts[$_GET['aid']])
                
            } // end of if($this->user_uid == $user->uid OR $user->uid == 1)
            else
            {
                drupal_add_js('alert("Sorry, You have no rights to control this account.");' 
                        . ' window.location.href = "' . $this->currentUrl . '"'
                        , 'inline');
            }
            


        }
        
    } // end of public function addToForm_getAccountAlbums_fromUrl(&$form)
    
    
    
} // end of class SocialInit




class SocialConnect{
    
    var $user_uid, $siteCreds, $redirect_url, $service, $service_id, $existing_account = null, $connectedAccounts, $access_token = null, $albums = null;
    
    function __construct($user_uid, $connectedAccounts, $redirect_url, $service, $account = null) 
    { 
        $this->user_uid = $user_uid;
        $this->connectedAccounts = $connectedAccounts;
        $this->redirect_url = $redirect_url;
        $this->service = $service;
        $this->service_id = $this->getServiceId();
        if($account)
        {
            $this->existing_account = $account;
            $this->access_token = $account['access_token'];
        }
        
        
        $socialInit = new SocialInit;
        $this->siteCreds = $socialInit->connect_to[$this->service];
    }

    protected function getServiceId()
    {
        $services_ids = variable_get('park_services_ids', array('facebook'=>1, 'google'=>2, 'picasa'=>3, 'mail.ru'=>4, 'vkontakte.ru'=>4));
        return $services_ids[$this->service];
    }
    
    
    protected function processCurl($remote_url, $return_type = 'string', $result_local_file_url = null, $method = 'GET', $post_fields = null)
    {
        switch($return_type)
        {
            case 'file':
                $out = fopen($result_local_file_url, 'wb');
                if ($out == FALSE)
                {
                    $result['ok'] = false;
                    $result['message'] = "Error opening destination file";
                    return $result;
                }

                $ch = curl_init();
                curl_setopt($ch, CURLOPT_FILE, $out);

                break;

            case 'string':
                $ch = curl_init();
                curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

                if($method == 'POST')
                {
                    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
                    curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; (R1 1.5))");
                    curl_setopt($ch, CURLOPT_TIMEOUT, 30); // works but what for? :)
                    curl_setopt($ch, CURLOPT_POST, 1);
                    curl_setopt($ch, CURLOPT_POSTFIELDS, $post_fields);
                }
                break;
        }

        curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_URL, $remote_url);

        if(!$curl_result = curl_exec($ch))
        {
            $result['ok'] = false;
            $result['message'] = "<br>An error with getting a remote file: " . curl_error($ch);
        }
        else
        {
            $result['ok'] = true;
            $result['result'] = $curl_result;
        }

        curl_close($ch);

        return $result;
        
    } // end of public function processCurl($remote_url, $return_type = 'string', $result_local_file_url = null, $method = 'GET', $post_fields = null)
 
    
    
    protected function getRestSignature($request_params) 
    {
        $params = '';
        foreach ($request_params as $key => $value)
            $params .= "$key=$value";
        return md5($params . $this->siteCreds['client_secret']);
    }
    
    
    protected function saveAccount($reload_page_and_show_message = true)
    {
        /*
        
        // example of the array structure
        
        $this->connectedAccounts = array(
               'lkfjgldkfjglkj' => array(
                                'service' => 'facebook', 
                                'service_id' => 1, 
                                'user_uid' => 1,
                                'id' => '423434',
                                'nick' => 'some nick',
                                'access_token' => '34234234234',
                                'account_key' => 'lkfjgldkfjglkj',
                                
                                'data' => array(), // or stdClass
                              ),
               'kjkhjglfkkjlkg' => array(
                                'service' => 'picasa', 
                                'service_id' => 3, 
                                'user_uid' => 1,
                                'id' => 'dsfsdfsdf',
                                'nick' => 'some nick 2',
                                'access_token' => 'ljhlfjhlfkj',
                                'account_key' => 'kjkhjglfkkjlkg',
                                
                                'data' => array(), // or stdClass
                              ),
            
                    );
        */
        
        //$this->existing_account['account_key'] = $this->service . '_' . $this->existing_account['id'];
        $this->existing_account['account_key'] = md5($this->service . '_' . $this->existing_account['id']);
        
        $account_to_save = $this->existing_account 
                           + array(
                                'service' => $this->service,
                                'service_id' => $this->service_id, 
                                'user_uid' => $this->user_uid,
                                'access_token' => $this->access_token,
                            );
        
        $account_index = false;
        if($this->connectedAccounts)
        {
            foreach($this->connectedAccounts as $key => $connectedAccount)
            {
                if($connectedAccount['service'] == $this->service AND $connectedAccount['id'] == $this->existing_account['id'])
                {
                    $account_index = $key;
                    break;
                }
            }
            
            // if account is already connected
            if($account_index)
                $this->connectedAccounts[$account_index] = $account_to_save;
            else
                $this->connectedAccounts[$this->existing_account['account_key']] = $account_to_save;
              
            $this->updateAccountInDB($this->connectedAccounts);
        }
        else
        {
            $this->connectedAccounts[$this->existing_account['account_key']] = $account_to_save;
            $this->insertAccountToDB($this->connectedAccounts);
        }

        if($reload_page_and_show_message)
            drupal_add_js('alert("Your rights for the ' . ucfirst($this->service) . ' account ~' . ($this->existing_account['nick']?$this->existing_account['nick']:$this->existing_account['id']) . '~ have been approved and ' . ($account_index?'reconnected again':'connected') . ' to our site.");' 
                        . ' window.location.href = "' . $this->redirect_url . '"'
                        , 'inline');
        
    } // end of public function saveAccount($reload_page_and_show_message = true)
    
    
    
    public function unconnectAccount($reload_page_and_show_message = true)
    {
        
        $account_index = false;
        if($this->connectedAccounts)
        {
            foreach($this->connectedAccounts as $key => $connectedAccount)
            {
                if($connectedAccount['service'] == $this->service AND $connectedAccount['id'] == $this->existing_account['id'])
                {
                    $account_index = $key;
                    break;
                }
            }
            
            // if account is already connected
            if($account_index)
                unset($this->connectedAccounts[$account_index]);
        }
        
        // if no such account exists
        if(!$this->connectedAccounts AND !$account_index)
        {
            if($reload_page_and_show_message)
                drupal_add_js('alert("No such account was connected to our site, so there is nothing to disconnect.");' 
                        . ' window.location.href = "' . $this->redirect_url . '"'
                        , 'inline');
        }
        else
        {
            // account exists
            if(count($this->connectedAccounts))
                $this->updateAccountInDB($this->connectedAccounts);
            else
                $this->deleteAllAccountsFromDB();
            
            if($reload_page_and_show_message)
                drupal_add_js('alert("Your account ~' . ($this->existing_account['nick']?$this->existing_account['nick']:$this->existing_account['id']) . '~ at ' . ucfirst($this->service) . '  have been successfully disconnected from our site.");' 
                        . ' window.location.href = "' . $this->redirect_url . '"'
                        , 'inline');
        }

        
    } // end of public function unconnectAccount($reload_page_and_show_message = true)
    
    
    
    
    protected function deleteAllAccountsFromDB($user_uid = null, $field = 'field_u_social')
    {
        if(!$user_uid)
            $user_uid = $this->user_uid;
        
        db_delete('field_data_' . $field) 
          ->condition('entity_id', $user_uid)
          ->execute();

        db_delete('field_revision_' . $field) 
          ->condition('entity_id', $user_uid)
          ->execute();

        field_cache_clear();
    }
    
    
    
    protected function insertAccountToDB($data, $user_uid = null, $field = 'field_u_social')
    {
        if(!$user_uid)
            $user_uid = $this->user_uid;
        
        db_insert('field_data_' . $field)
          ->fields(array(
          'entity_type'=> 'user',
          'bundle'=> 'user',
          'deleted'=> 0,                
          'entity_id' => $user_uid,
          'delta' => 0,  
          'revision_id'=> $user_uid,  
          'language'=> 'und',  
          $field . '_value' => serialize($data),
          ))
          ->execute();

        db_insert('field_revision_' . $field) 
          ->fields(array(
         'entity_type'=> 'user',
          'bundle'=> 'user',
          'deleted'=> 0,                
          'entity_id' => $user_uid,
          'delta' => 0,  
          'revision_id'=> $user_uid,  
          'language'=> 'und',  
          $field . '_value' => serialize($data),
          ))
          ->execute();

        field_cache_clear();
    }
    
    
    protected function updateAccountInDB($data, $user_uid = null, $field = 'field_u_social')
    {
        if(!$user_uid)
            $user_uid = $this->user_uid;
        
        db_update('field_data_' . $field) 
          ->fields(array(
          'entity_id' => $user_uid,
          'delta' => 0,  
          'revision_id'=> $user_uid,    
          $field . '_value' => serialize($data),
          ))
          ->condition('entity_id', $user_uid)
          ->execute();

        db_update('field_revision_' . $field) 
          ->fields(array(
          'entity_id' => $user_uid,
          'delta' => 0,  
          'revision_id'=> $user_uid,     
          $field . '_value' => serialize($data),
          ))
          ->condition('entity_id', $user_uid)
          ->execute();

        field_cache_clear(); 
        
    } // end of public function insertAccountToDB($data, $user_uid = null)
    
    
    
    public function dpr($data, $return = true)
    {
        $out = '<PRE>' . print_r($data, $return) . '</PRE>';
        if($return)
            return $out;
        else
            echo $out;
        
    } // end of public function dpr($data, $return = true)
    
    
    // tries to get user albums from local db 
    // or if $update = true OR it's not in local db - get from remote service, write(update if $update = true) to db and
    // 
    // after getting albums put it to $this object, 
    public function getUserAlbums($aid = null, $update = false)
    {
        if($update OR !$this->getUserAlbums_fromDB($aid))
        {
            if($error_message = $this->getUserAlbums_fromRemote($aid))
                return $error_message;
            
            $this->saveUserAlbums_toDB($aid);
        }
    }
    
    
    
    protected function getUserAlbums_fromDB($aid = null)
    {
        if($aid)
            $albums = db_query("SELECT * FROM {park_users_albums} WHERE uid = $this->user_uid AND service_id = $this->service_id AND aid = '$aid'");
        else
            $albums = db_query("SELECT * FROM {park_users_albums} WHERE uid = $this->user_uid AND service_id = $this->service_id");
        
        if(!$albums->rowCount())
            return false;
        
        foreach($albums as $album)
        {
            $this->albums[$album->aid]['updated'] = $album->updated;
            
            $album_info = unserialize($album->album_info);
            $this->albums[$album->aid]['th'][0] = array(
                            'img_src' => isset($album_info['ir']['t'])?$album_info['ir']['t']:null,
                            'url' => isset($album_info['ir']['i'])?$album_info['ir']['i']:null,
                );
            $this->albums[$album->aid]['th_local'][0] = array(
                            'img_src' => isset($album_info['il']['t'])?$album_info['il']['t']:null,
                            'url' => isset($album_info['il']['i'])?$album_info['il']['i']:null,
                );
            unset($album_info['il'], $album_info['ir']);
            $this->albums[$album->aid]['info'] = $album_info;
            
            if($album->album_info_raw)
                $this->albums[$album->aid]['data'] = unserialize ($album->album_info_raw);
            
            if($album->photos_max)
                $photos_max = unserialize($album->photos_max);
            $photos_min = unserialize($album->photos_min);
            foreach($photos_min as $pid => $photo)
            {
                
                $this->albums[$album->aid]['photos'][$pid] = $photo;
                $this->albums[$album->aid]['photos'][$pid]['th'][0] = array(
                                'img_src' => $photo['ir']['t'],
                                'url' => $photo['ir']['i'],
                            );
                $this->albums[$album->aid]['photos'][$pid]['th_local'][0] = array(
                                'img_src' => $photo['il']['t'],
                                'url' => $photo['il']['i'],
                            );
                if(isset($photos_max[$pid]))
                    $this->albums[$album->aid]['photos'][$pid]['data'] = $photos_max[$pid];
                
                unset($photo['ir'],$photo['il']);
                $this->albums[$album->aid]['photos'][$pid]['info'] = $photo;
            }
            
        } // end of foreach($albums as $album)
        
        //return false;
        return true;
    }
    
    
    
    protected function saveUserAlbums_toDB($aid = null, $save_raw_data = false)
    {
        dpm($this->albums);
        
        $albums_updated = 0;
        foreach($this->albums as $aid => $album)
        {
            if(isset($album['th'][0]['img_src']))
            {
                $album['info']['ir']['t'] = $album['th'][0]['img_src'];
                $album['info']['il']['t'] = null;
            }
            if(isset($album['th'][0]['url']))
            {
                $album['info']['ir']['i'] = $album['th'][0]['url'];
                $album['info']['il']['i'] = null;
            }
            
            
            
            $photos_min = array();
            if(!isset($album['photos']))
                $album['photos'] = array();
            
            foreach($album['photos'] as $pid => $photo)
            {
                $photos_min[$pid] = $photo['info'];
                $photos_min[$pid]['ir'] = array(
                            't' => $photo['th'][0]['img_src'],
                            'i' => $photo['th'][0]['url'],
                        );
                $photos_min[$pid]['il'] = null;
            }
            
            
            if(db_query("SELECT aid FROM {park_users_albums} WHERE uid = $this->user_uid AND service_id = $this->service_id AND aid = '$aid'")->fetchField())
            {
                $albums_updated += db_update('park_users_albums')
                  ->fields(array(
                  'album_info' => serialize($album['info']),
                  'album_info_raw' => $save_raw_data?serialize($album['data']):null, 
                  'photos_min' => serialize($photos_min),
                  'photos_max'=> $save_raw_data?serialize($album['photos']):null,
                  'updated' => time(),
                  ))
                  ->condition('uid', $this->user_uid)
                  ->condition('service_id', $this->service_id)
                  ->condition('aid', $aid)
                  ->execute();
            }
            else
            {
                $albums_updated += db_insert('park_users_albums') 
                  ->fields(array(
                  'uid' => $this->user_uid,
                  'service_id' => $this->service_id,
                  'aid' => $aid,
                  'album_info' => serialize($album['info']),
                  'album_info_raw' => $save_raw_data?serialize($album['data']):null,
                  'photos_min' => serialize($photos_min),
                  'photos_max'=> $save_raw_data?serialize($album['photos']):null,
                  'updated' => time(),
                  ))
                  ->execute();
            }
            
            
        } // end of foreach($this->albums as $aid => $album)
        
        return $albums_updated;
        
    } // end of function saveUserAlbums_toDB($aid = null)
    
    
    
    
    public function addToForm_accountAlbums(&$form, $aid = null) // $target = null - all albums
    {
        $form['albums'] = array(
                '#type' => 'fieldset',
                '#title' => t('Albums of ') . $this->existing_account['service'] . ' - ' . ($this->existing_account['nick']?$this->existing_account['nick']:$this->existing_account['id']),
                '#collapsible' => true,
                '#collapsed' => false, // the slideshow will not work within any collapsed fieldset (nested level doesn't matter)
            );

        if($errorMessage = $this->getUserAlbums($aid))
        {
            $form['albums']['data'] = array(
                '#markup' => '<div>' . $errorMessage . '</div>',
            );

        }
        elseif(!is_array($this->albums))
        {
            $form['albums']['data'] = array(
                '#markup' => '<div>This account doesn\'t contain any albums.</div>',
            );
        }
        else
        {
            $sectionsToShow = array('cover', 'photos', 'info', 'data', 'photos-raw-data');
            
            if($aid)
            {
                if(!isset($this->albums[$aid]))
                {
                    drupal_add_js('alert("No album with the id ~' . $aid . '~ presents in the account ~' . $this->existing_account['id'] . '~ on ' . ucfirst($this->existing_account['service']) . '.");' 
                        . ' window.location.href = "' . $this->redirect_url . '"'
                        , 'inline');
                    
                }
                else
                    $form['albums'][$aid] = $this->getAccountAlbumForm($this->albums[$aid], $sectionsToShow);
            }
            else
                foreach($this->albums as $aid => $album)
                    $form['albums'][$aid] = $this->getAccountAlbumForm($album, $sectionsToShow);
        }
        
    } // end of function addToForm_accountAlbums(&$form)
    
    
    
    public function getAccountAlbumForm($albumObject, $sections = array('photos'))
    {
        $albumForm = array(
                    '#type' => 'fieldset',
                    '#title' => $albumObject['info']['title'],
                    '#collapsible' => true,
                    '#collapsed' => false, // the slideshow will not work within any collapsed fieldset (nested level doesn't matter)
                );
        
        foreach($sections as $section)
        {
            switch($section)
            {
                case 'cover':
                
                    if(!isset($albumForm['info']))
                        $albumForm['info'] = array(
                            '#type' => 'fieldset',
                            '#title' => 'Album info',
                            '#collapsible' => true,
                            '#collapsed' => true,
                        );

                    if(isset($albumObject['th'][0]['url']))
                    {
                        $albumForm['info']['th'] = array(
                            '#type' => 'fieldset',
                            '#title' => 'Album cover',
                            '#collapsible' => true,
                            '#collapsed' => false,
                        );
                        $albumForm['info']['th'][0] = array(
                            '#markup' => '<a href="' . $albumObject['th'][0]['url'] . '"><img src="' . $albumObject['th'][0]['img_src'] . '" /></a>',
                        );
                    }
                    else
                    {
                        $albumForm['info']['th'] = array(
                            '#type' => 'fieldset',
                            '#title' => 'Album cover',
                            '#collapsible' => true,
                            '#collapsed' => true,
                        );
                        $albumForm['info']['th'][0] = array(
                            '#markup' => '<div>' . $this->dpr($albumObject['th'][0]) . '</div>',
                        );
                    }
                    
                    break;
                    
                case 'info':
                    if(!isset($albumForm['info']))
                        $albumForm['info'] = array(
                            '#type' => 'fieldset',
                            '#title' => 'Album info',
                            '#collapsible' => true,
                            '#collapsed' => true,
                        );

                    $albumForm['info']['basic'] = array(
                        '#type' => 'fieldset',
                        '#title' => 'Basic info',
                        '#collapsible' => true,
                        '#collapsed' => true,
                    );

                    $albumForm['info']['basic']['raw'] = array(
                        '#markup' => '<div>' . $this->dpr($albumObject['info']) . '</div>',
                    );
                    
                    break;
                    
                case 'data':  
                    
                    if(!isset($albumForm['info']))
                        $albumForm['info'] = array(
                            '#type' => 'fieldset',
                            '#title' => 'Album info',
                            '#collapsible' => true,
                            '#collapsed' => true,
                        );
                    
                    $albumForm['info']['data'] = array(
                        '#type' => 'fieldset',
                        '#title' => 'Raw data',
                        '#collapsible' => true,
                        '#collapsed' => true,
                    );
                    $albumForm['info']['data']['raw'] = array(
                        '#markup' => '<div>' . (isset($albumObject['data'])?$this->dpr($albumObject['data']):'not saved') . '</div>',
                    );  
                    
                    break;

                    
                case 'photos-raw-data':
                    if(isset($albumObject['photos']))
                    {
                        $albumForm['info']['photos-raw-data'] = array(
                            '#type' => 'fieldset',
                            '#title' => 'Photos raw data',
                            '#collapsible' => true,
                            '#collapsed' => true,
                        );
                        $albumForm['info']['photos-raw-data']['raw'] = array(
                            '#markup' => '<div>' . $this->dpr($albumObject['photos']) . '</div>',
                        );  
                    }
                    
                    break;
                    
                case 'photos':
                    
                    if(isset($albumObject['photos']))
                        $albumForm['photos'] = $this->getAccountAlbumPhotosForm($albumObject['info']['aid'], $albumObject['photos'], array('style' => 'slideshow'));
                    
                    break;
                    
            } // end of switch($section)
            
        } // end of foreach($sections as $section)
        
        return $albumForm;
    }
    
    
    public function getAccountAlbumPhotosForm($albumId, $photosObject, $options = array('style' => 'simple'))
    {
        $photosForm = array(
                '#type' => 'fieldset',
                '#title' => 'Photos',
                '#collapsible' => true,
                '#collapsed' => false, // the slideshow will not work within any collapsed fieldset (nested level doesn't matter)
            );
        switch($options['style'])
        {
            case 'simple':
                
                foreach($photosObject as $pid => $photo)
                {
                    $photosForm[$pid] = array(
                        '#markup' => '<a href="' . $photo['th'][0]['url'] . '"><img src="' . $photo['th'][0]['img_src'] . '" /></a>',
                    );
                }
                
                break;
                
                
            case 'slideshow':
                
                $photosForm['slideshow'] = array(
                        '#markup' => $this->getAccountAlbumPhotos_themedToSlideshow( $albumId, $photosObject),
                    );
                
                break;
        }
        

        return $photosForm;
        
    } // end of public function getAccountAlbumPhotosForm($photosObject)
    
    
    
    public function getAccountAlbumPhotos_themedToSlideshow($albumId, $photosObject, $thumbs_height = '70px')
    {
        
        drupal_add_css("sites/all/libraries/jquery.plugins/Ad-gallery/css/jquery.ad-gallery.css", array('preprocess' => FALSE)); // array('group' => CSS_THEME, 'preprocess' => FALSE)
        drupal_add_css("sites/all/libraries/jquery.plugins/Ad-gallery/css/jquery.ad-gallery_custom.css", array('preprocess' => FALSE)); // array('group' => CSS_THEME, 'preprocess' => FALSE)

        drupal_add_js('sites/all/libraries/jquery.plugins/Ad-gallery/park_image_gallery_ad.js');
        drupal_add_js('sites/all/libraries/jquery.plugins/Ad-gallery/jquery.ad-gallery.js');
        
        //1, 3, 4, 
        drupal_add_css("sites/all/libraries/jquery.plugins/Colorbox/css4/colorbox.css", array('preprocess' => FALSE)); // array('group' => CSS_THEME, 'preprocess' => FALSE)
        drupal_add_js('sites/all/libraries/jquery.plugins/Colorbox/jquery.colorbox.js');
        
        drupal_add_js('
            
                    jQuery(document).ready(function(){
                            //Examples of how to assign the ColorBox event to elements
                            jQuery(".group_' . $albumId .'").colorbox({transition:"fade", slideshow:true, slideshowAuto: false, rel:"group_' . $albumId . '", width:"95%", height:"95%"});

                            //$(".group2").colorbox({rel:"group2", transition:"fade"});
                            //$(".group3").colorbox({rel:"group3", transition:"none", width:"75%", height:"75%"});
                            //$(".group4").colorbox({rel:"group4", slideshow:true});
                    });

                ', 'inline');
        
        //$links_collection_for_colobox = '';
        $body_to_slideshow =  
            '<div id="gallery_wrapper_' . $albumId . '">'
                    //.'<div id="gallery_' . $key . '" class="ad-gallery">'
                    .'<div id="adg'. $albumId . '" class="ad-gallery">'
                        .'<div class="ad-image-wrapper" style="width:600px;height:400px;"></div>'
                        .'<div class="ad-controls"></div>'

                        // my button for full screen in ColorBox
                        // set up in park_image_gallery_ad.js
                        . '<div class="full_screen_btn"><a class="full group_' . $albumId . '" href="">Full screen</a></div>'

                        .'<div class="ad-nav">'
                            .'<div class="ad-thumbs">'
                                .'<ul class="ad-thumb-list">';

                                    $default_file_path = variable_get('file_public_path', conf_path() . '/files');
                                    foreach($photosObject as $image)
                                    {
                                        $attributes = array();
                                        $image_data = array();

                                        if(isset($image['longdesc']))
                                                $attributes['longdesc'] = $image['longdesc'];
                                        
                                        //if(isset($image['class']))
                                        //        $attributes['class'] = $image['class'];

                                        
                                        ////$image_data['path'] = str_replace('/' .$default_file_path . '/', 'public://', $image['src']);
                                        $image_data['path'] = $image['th'][0]['url'];

                                        ////$image_data['style_name'] = 'gallery_thumb_w-75';

                                        if(isset($image['info']['alt']))
                                                $image_data['alt'] = $image['info']['alt'];
                                        if(isset($image['info']['title']))
                                                $image_data['title'] = $image['info']['title'];

                                        $image_data['attributes'] = $attributes;
                                        //$links_collection_for_colobox .= '<a style="display:none;" class="' . $image['class'] . '" href="' . $image['src'] . '">Full screen</a>';
                                        $body_to_slideshow .= '<li>'
                                                //.'<a href="' . $image['src'] . '">'
                                                .'<a class="group_' . $albumId . '" href="' . $image['th'][0]['url'] . '">'
                                                    //.'<img src="' . $image['thumb'] . '"' . (isset($image['title'])?' title="' . $image['title'] . '"':'') . (isset($image['alt'])?' alt="' . $image['alt'] . '"':'') . (isset($image['longdesc'])?' longdesc="' . $image['longdesc'] . '"':'') . ' class="image' . $key2 . '">'
                                                    ////. theme('image_style', $image_data)
                                                    .'<img height="' . $thumbs_height . '" src="' . $image['th'][0]['img_src'] . '"' . (isset($image['info']['title'])?' title="' . $image['info']['title'] . '"':'') . (isset($image['info']['alt'])?' alt="' . $image['info']['alt'] . '"':(isset($image['info']['title'])?' alt="' . $image['info']['title'] . '"':'')) . (isset($image['info']['longdesc'])?' longdesc="' . $image['info']['longdesc'] . '"':'') . ' class="image' . $image['info']['pid'] . '"/>'
                                                    
                                               .'</a>'
                                            .'</li>';
                                    }
                            $body_to_slideshow .= '</ul>'
                            .'</div>'
                        .'</div>'
                    .'</div>'

                    .'<div id="descriptions"></div>'

                    .'<p>'
                        .'Examples of how you can alter the behaviour on the fly;'
                        .'Effect: <select class="switch-effect">'
                                    .'<option value="slide-hori">Slide horizontal</option>'
                                    .'<option value="slide-vert">Slide vertical</option>'
                                    .'<option value="resize">Shrink/grow</option>'
                                    .'<option value="fade">Fade</option>'
                                    //.'<option value="">None</option>'
                                .'</select><br>'

                        .'<a href="#" class="toggle-slideshow">Toggle slideshow</a> |'
                        .'<a href="#" class="toggle-description">Toggle having description outside of image</a>'
                    .'</p>'

            .'</div>'; // end of echo '<div id="gallery_wrapper_' . $key . '">'
                        
       //$body_to_slideshow .= $links_collection_for_colobox;
       return $body_to_slideshow;
       
    } // end of public function getAccountAlbumPhotos_themedToSlideshow($albumId, $photosObject)
    
    
} // end of class SocialConnect{



class SocialConnectFacebook extends SocialConnect
{
   
    function __construct($user_uid, $connectedAccounts, $redirect_url, $service = null, $account = null) 
    { 
        parent::__construct($user_uid, $connectedAccounts, $redirect_url, 'facebook', $account);
    }
    
    
    public function connectAccount($get)
    {
        $token_url = 'https://graph.facebook.com/oauth/access_token?';
        $token_url_params = 'client_id=' . $this->siteCreds['client_id'] 
                          . '&redirect_uri=' . urlencode($this->redirect_url) 
                          . '&client_secret=' . $this->siteCreds['client_secret'] . '&code=' . $get['code']; 

        $result = $this->processCurl($token_url . $token_url_params, 'string');

        if(!$result['ok'])
        {
            drupal_add_js('alert("Authentication error. Try again."); window.location.href = "' . $this->redirect_url . ($get['type']?'?type=' . $get['type']:'') .'"', 'inline');
            return;
        }

        $this->access_token = str_replace('access_token=', '', $result['result']);

        $url = "https://graph.facebook.com/me?access_token=" 
           . $this->access_token;

        $result = $this->processCurl($url, 'string');
        
        $result = json_decode($result['result']);

        $account_id = $result->id;
        //unset($result->id);

        $this->existing_account['data'] = $result;
        $this->existing_account['id'] = $result->id;
        $this->existing_account['nick'] = $result->name; // is it correct?
            
        // add creds to the db
        $this->saveAccount();
        
    } // end of public function connectAccount($get)
    
    
    
    public function getOauthLink($siteCreds, $redirect_url)
    {
        $_SESSION['state'] = md5(uniqid(rand(), TRUE)); //CSRF protection
        return 'http://www.facebook.com/dialog/oauth'
                . '?client_id=' . $siteCreds['client_id']
                . '&scope=publish_stream, offline_access, user_about_me, user_birthday, user_hometown, user_likes, user_photos, user_videos, read_stream, manage_pages'
                . '&redirect_uri=' . urlencode($redirect_url);
    }

        
    private function fbOpenGraph($object, $options = null)
    {
        if(!$object)
            $object = $this->existing_account['id'];
        
        $url = 'https://graph.facebook.com/' 
        . ($object?$object . '/':'')
        . $options['connection']
        //. '?access_token=' . $user_account->auth_key;
        . '?access_token=' . $this->access_token;

        $result = $this->processCurl($url, 'string');
        
        if(!$result['ok'])
            return null;

        return json_decode($result['result']);
    }
    
    
    protected function getUserAlbums_fromRemote($aid = null)
    {
        if(!$albums_object = $this->fbOpenGraph(null, array('connection'=>'albums')))
            return 'Error: reading fbOpenGraph';
        
        foreach ($albums_object->data as $key1 => $albumEntry) 
        {
            //dpm($albumEntry);
            $aid = $albumEntry->id;
            $this->albums[$aid]['info']['title'] = $albumEntry->name;
            $this->albums[$aid]['info']['aid'] = $aid;
            $this->albums[$aid]['info']['published'] = strtotime($albumEntry->created_time);

            $this->albums[$aid]['data'][0] = $this->dpr($albumEntry);
            $this->albums[$aid]['th'][0]['data'] = isset($albumEntry->cover_photo)?$albumEntry->cover_photo:null;

            if($albumPhotos = $this->fbOpenGraph($albumEntry->id, array('connection'=>'photos')))
            {
                //$albums[$key1]['photos']['title'] = $albumEntry->name;
                
                foreach ($albumPhotos->data as $key3 => $photoEntry) 
                {
                    $pid = $photoEntry->id;
                    $this->albums[$aid]['photos'][$pid]['info']['title'] = t('Photo [' . $key3 .']' . (isset($photoEntry->name)?': ' . $photoEntry->name:''));
                    $this->albums[$aid]['photos'][$pid]['info']['pid'] = $pid;
                    $this->albums[$aid]['photos'][$pid]['info']['published'] = strtotime($photoEntry->created_time);
                    
                    $this->albums[$aid]['photos'][$pid]['data'] = $this->dpr($photoEntry);

                    //$this->albums[$aid]['photos'][$pid]['th'][0]['url'] = $photoEntry->images[0]->source;
                    $this->albums[$aid]['photos'][$pid]['th'][0]['url'] = $photoEntry->source;
                    $this->albums[$aid]['photos'][$pid]['th'][0]['img_src'] = isset($photoEntry->images[4])?$photoEntry->images[4]->source:$photoEntry->images[3]->source; // sometimes there isn't a smallest thumb... so we take a bit larger one
                    // it works, too, but has a bit larger size
                    //$this->albums[$aid]['photos'][$pid]['th'][0]['img_src'] = $photoEntry->picture;
                }   

            } // end of if($albumPhotos = $this->fbOpenGraph($user_account, $albumEntry->id, array('connection'=>'photos')))

        } // end of foreach ($albums_object->data as $key1 => $albumEntry) 

        //dpm($albums);
        return null; // success
        
    } // end of public function getUserAlbums(&$albums)
    
    

} // end of class SocialConnectFacebook extends SocialConnect




class SocialConnectVkontakte extends SocialConnect
{
    function __construct($user_uid, $connectedAccounts, $redirect_url, $service = null, $account = null) 
    { 
        parent::__construct($user_uid, $connectedAccounts, $redirect_url, 'vkontakte.ru', $account);
    }
    
    
    // pass arguments here, not using $this->... to have possibility to use just a function without an object, like SocialConnectVkontakte::getOauthLink(...)
    public function getOauthLink($siteCreds, $redirect_url)
    {
        return 'http://api.vkontakte.ru/oauth/authorize'
               . '?client_id=' . $siteCreds['client_id']
               . '&scope=offline photos video wall docs notify audio'
               . '&response_type=code'
               . '&redirect_uri=' . $redirect_url;
    }
    
    
    public function processRest($function, $ext_params = null)
    {
        $base_url = 'http://api.vkontakte.ru/api.php';

        $base_params = array(
            'api_id' => $this->siteCreds['client_id'],
            'method' => $function,
            //'session_key' => $this->existing_account->auth_key,
            'session_key' => $this->existing_account['access_token'],
            'format' => 'json',
            'timestamp' => time(),
            'random' => time()/2,
            );

        if($ext_params)
            $base_params = array_merge($base_params, $ext_params);

        ksort($base_params);
        
        $base_params_str = null;
        
        foreach($base_params as $key => $value)
        {
            if(!$base_params_str)
                $base_params_str .= "?$key=$value";
            else
                $base_params_str .= "&$key=$value";
        }

        $sig = $this->getRestSignature($base_params, $this->siteCreds['client_secret']);
        $full_params = $base_params_str . '&sig=' . $sig; //. '&ext_perm=widget'; 
        $url = $base_url . $full_params;
        $result = $this->processCurl($url, 'string');
        
        if($result['ok'])
        {
            $result = json_decode($result['result']);
            if(!isset($result->error))
                return $result->response;
            else
                return $result;
        }

        return null;
    }
    
    
    public function connectAccount($get)
    {
        $token_url = 'https://api.vkontakte.ru/oauth/access_token?';
        $token_url_params = 'client_id=' . $this->siteCreds['client_id'] . '&client_secret=' . $this->siteCreds['client_secret'] . '&code=' . $get['code']; 

        $result = $this->processCurl($token_url, 'string', null, 'POST', $token_url_params);
        
        //dpr($result);
        
        if(!$result['ok'])
        {
            drupal_add_js('alert("Authentication error. Try again."); window.location.href = "' . $this->redirect_url . ($get['type']?'?type=' . $get['type']:'') .'"', 'inline');
            return;
        }

        $result = json_decode($result['result']);

        //dpr($result);
        //die;
        
        $this->access_token = $result->access_token;
        unset($result->access_token);

        $this->existing_account['data'] = $result;
        $this->existing_account['id'] = $result->user_id;
        
        if($user_object = $this->processRest('getProfiles', array('uids' => $this->existing_account['id'], 'fields' => 'nickname,screen_name,sex,birthdate,city,country,timezone,photo,photo_medium,photo_big,has_mobile,rate,contacts,education,online,counters'))) //'nickname, screen_name, sex, birthdate, city, country, timezone, photo, photo_medium, photo_big, has_mobile, rate, contacts, education, online, counters'
        {
            $this->existing_account['data']->user = $user_object[0]->user;
            
            if($user_object[0]->user->nickname)
                $this->existing_account['nick'] = $user_object[0]->user->nickname;
            else
                $this->existing_account['nick'] = $user_object[0]->user->first_name . ' ' . $user_object[0]->user->last_name;
        }
        else
            $this->existing_account['nick'] = null;
        
        // add creds to the db
        $this->saveAccount();
        
    } // end of public function connectAccount($get)
    
    
    protected function getUserAlbums_fromRemote($aid = null)
    {
        if(!$albums_object = $this->processRest('photos.getAlbums', array('uid' => $this->existing_account['id'])))
            return 'Error: reading vkontakte REST photos.getAlbums';
                
        foreach ($albums_object as $key1 => $albumEntry) 
        {
            /*
            $albums[$key1]['title'] = $albumEntry->title->text;
            $albums[$key1]['info']['thumbs'][$key0]['data']['url'] = $album['mediaGroup']['content'][0]['url'];
            $albums[$key1]['info']['thumbs'][$key0]['data']['img_src'] = $value['url'];
            $albums[$key1]['info'][$key2]['data'] = $this->dpr($albumData);
            $albums[$key1]['photos']['title'] = $albumEntry->title->text;
                    
            $albums[$key1]['photos']['photo_' . $key3]['title'] = $photoEntry->title->text;
                    
            $albums[$key1]['photos']['photo_' . $key3]['thumbs']['url'] = $photo['mediaGroup']['content'][0]['url'];
            $albums[$key1]['photos']['photo_' . $key3]['thumbs']['img_src'] = $value['url'];
            $albums[$key1]['photos']['photo_' . $key3][$key4]['title'] = $key4;
            $albums[$key1]['photos']['photo_' . $key3][$key4]['data'] = $this->dpr($value);
            */

            $aid = $albumEntry->album->aid;
                    
            $this->albums[$aid]['info']['title'] = $albumEntry->album->title;
            $this->albums[$aid]['info']['aid'] = $aid;
            $this->albums[$aid]['info']['published'] = $albumEntry->album->created;
            
            $this->albums[$aid]['data'][0] = $this->dpr($albumEntry->album);

            $this->albums[$aid]['th'][0]['data'] = $albumEntry->album->thumb_id;

            if($albumPhotos = $this->processRest('photos.get', array('uid' => $this->existing_account['id'], 'aid' => $albumEntry->album->aid)))
            {
                //$this->albums[$key1]['photos']['title'] = $albumEntry->album->title;

                foreach ($albumPhotos as $key3 => $photoEntry) 
                {
                    $pid = $photoEntry->photo->pid;
                    $this->albums[$aid]['photos'][$pid]['info']['title'] = t('Photo [' . $key3 .']' . (isset($photoEntry->photo->title)?': ' . $photoEntry->photo->title:''));
                    $this->albums[$aid]['photos'][$pid]['info']['pid'] = $pid;
                    $this->albums[$aid]['photos'][$pid]['info']['published'] = $photoEntry->photo->created;
                    
                    $this->albums[$aid]['photos'][$pid]['data'] = $this->dpr($photoEntry->photo);

                    $this->albums[$aid]['photos'][$pid]['th'][0]['url'] = $photoEntry->photo->src_big;
                    $this->albums[$aid]['photos'][$pid]['th'][0]['img_src'] = $photoEntry->photo->src;
                }

            }

        } // end of foreach ($albums_object as $key1 => $albumEntry) 
        
        return null; // success
    }


} // end of cclass SocialConnectVkontakte extends SocialConnect



class SocialConnectMailRu extends SocialConnect
{
    
    function __construct($user_uid, $connectedAccounts, $redirect_url, $service = null, $account = null) 
    { 
        parent::__construct($user_uid, $connectedAccounts, $redirect_url, 'mail.ru', $account);
    }
    
    
    // pass arguments here, not using $this->... to have possibility to use just a function without an object, like SocialConnectMailRu::getOauthLink(...)
    public function getOauthLink($siteCreds, $redirect_url)
    {
        return 'https://connect.mail.ru/oauth/authorize'
               . '?client_id=' . $siteCreds['client_id']
               . '&scope=photos guestbook stream events' //  widget causes the error
               . '&response_type=code'
               . '&redirect_uri=' . $redirect_url;
    }
    
    
    public function processRest($function, $ext_params = null)
    {
        // check token freshness
        if($this->existing_account['data']->token_updated + $this->existing_account['data']->expires_in < time())
        {
            if(!$this->connectAccount())
                return null;
        }

        $base_url = 'http://www.appsmail.ru/platform/api';

        $base_params = array(
            'app_id' => $this->siteCreds['client_id'],
            'method' => $function,
            'secure' => 1,
            'session_key' => $this->access_token,
            );

        if($ext_params)
            $base_params = array_merge($base_params, $ext_params);

        ksort($base_params);

        $base_params_str = null;
        foreach($base_params as $key => $value)
        {
            if(!$base_params_str)
                $base_params_str .= "?$key=$value";
            else
                $base_params_str .= "&$key=$value";
        }

        $sig = $this->getRestSignature($base_params, $this->siteCreds['client_secret']);
        $full_params = $base_params_str . '&sig=' . $sig; //. '&ext_perm=widget'; 
        $url = $base_url . $full_params;

        $result = $this->processCurl($url, 'string');
        if($result['ok'])
            return json_decode($result['result']);
        else
            return null;
        
    }
    
    
    public function connectAccount($get = null)
    {
        $token_url = 'https://connect.mail.ru/oauth/token';

        if(!$this->existing_account)
            $token_url_params = 'client_id=' . $this->siteCreds['client_id'] . '&client_secret=' . $this->siteCreds['client_secret'] . '&grant_type=authorization_code&code=' . $get['code'] . '&redirect_uri=' . $this->redirect_url;  // . '?service=' . $_GET['service'] //. '&type=' . ($_GET['type']?$_GET['type']:'photo-album')
        else
            $token_url_params = 'client_id=' . $this->siteCreds['client_id'] . '&client_secret=' . $this->siteCreds['client_secret'] . '&grant_type=refresh_token&refresh_token=' . $this->existing_account['data']->refresh_token . '&redirect_uri=' . $this->redirect_url; 

        $result = $this->processCurl($token_url, 'string', null, 'POST', $token_url_params);

        if(!$result['ok'])
        {
            drupal_add_js('alert("Authentication error. Try again."); window.location.href = "' . $this->redirect_url . ($get['type']?'?type=' . $get['type']:'') .'"', 'inline');
            return;
        }

        $result = json_decode($result['result']);
        
        
        $this->access_token = $result->access_token;
        //$this->access_token = $result->refresh_token;
        //unset($result->access_token);

        $result->token_updated = time();
        $result->redirect_uri = $this->redirect_url;

        
        if(!$this->existing_account)
        {
            //$this->existing_account = (object) array('auth_key' => $this->access_token, 'data'=> (array) $result);
            $this->existing_account['data'] = $result;
            $this->existing_account['id'] = $result->x_mailru_vid;
            $user_data = $this->processRest('users.getInfo');
            $this->existing_account['nick'] = $user_data[0]->nick;
            $this->existing_account['data']->user_data = $user_data[0];
            
            // add creds to the db
            $this->saveAccount();
        }
        else
        {
            /*
            if(!$this->existing_account->id)
                $this->existing_account->id = $result->x_mailru_vid;
            if(!$this->existing_account->nick)
                $this->existing_account->nick = $result->nick;
            */
            
            // update creds in the db
            $this->saveAccount(false); // default: saveAccount($reload_page_and_show_message = true)
            return $this->access_token;
        }
    } // end of public function connectAccount($get, $redirect_url, $siteCreds)
    
   
    
    protected function getUserAlbums_fromRemote($aid = null)
    {
        if(!$albums_object = $this->processRest('photos.getAlbums'))
            return 'Error: reading mail.ru REST photos.getAlbums';
        
        //park_misc_dpr(park_google_mailru_rest($user_account, 'photos.get', array('aid' => 'beauty')));
        //'#value' => '<div>' . park_misc_dpr(park_google_mailru_rest($user_account, 'photos.getAlbums')) . '</div>',
        //'#value' => '<div>' . park_misc_dpr(park_google_mailru_rest($user_account, 'users.getInfo')) . '</div>',

        foreach ($albums_object as $key1 => $albumEntry) 
        {
            /*
            $albums[$key1]['title'] = $albumEntry->title->text;
            $albums[$key1]['info']['thumbs'][$key0]['data']['url'] = $album['mediaGroup']['content'][0]['url'];
            $albums[$key1]['info']['thumbs'][$key0]['data']['img_src'] = $value['url'];
            $albums[$key1]['info'][$key2]['data'] = $this->dpr($albumData);
            $albums[$key1]['photos']['title'] = $albumEntry->title->text;
                    
            $albums[$key1]['photos']['photo_' . $key3]['title'] = $photoEntry->title->text;
                    
            $albums[$key1]['photos']['photo_' . $key3]['thumbs']['url'] = $photo['mediaGroup']['content'][0]['url'];
            $albums[$key1]['photos']['photo_' . $key3]['thumbs']['img_src'] = $value['url'];
            $albums[$key1]['photos']['photo_' . $key3][$key4]['title'] = $key4;
            $albums[$key1]['photos']['photo_' . $key3][$key4]['data'] = $this->dpr($value);
            */
            
            $aid = $albumEntry->aid;
            
            $this->albums[$aid]['info']['title'] = $albumEntry->title;
            $this->albums[$aid]['info']['aid'] = $aid;
            $this->albums[$aid]['info']['published'] = $albumEntry->created;
            
            $this->albums[$aid]['data'][0] = $this->dpr($albumEntry);
            
            $this->albums[$aid]['th'][0]['url'] = $albumEntry->link;
            $this->albums[$aid]['th'][0]['img_src'] = $albumEntry->cover_url; 

            if($albumPhotos = $this->processRest('photos.get', array('aid' => $albumEntry->aid)))
            {
                //$this->albums[$key1]['photos']['title'] = $albumEntry->title;

                foreach ($albumPhotos as $key3 => $photoEntry) 
                {
                    $pid = $photoEntry->pid;
                    $this->albums[$aid]['photos'][$pid]['info']['title'] = t('Photo [' . $key3 .']' . ($photoEntry->title?': ' . $photoEntry->title:''));

                    $this->albums[$aid]['photos'][$pid]['info']['pid'] = $pid;
                    $this->albums[$aid]['photos'][$pid]['info']['published'] = $photoEntry->created;
                    
                    $this->albums[$aid]['photos'][$pid]['data'] = $this->dpr($photoEntry);
                            
                    $this->albums[$aid]['photos'][$pid]['th'][0]['url'] = $photoEntry->src;
                    $this->albums[$aid]['photos'][$pid]['th'][0]['img_src'] = $photoEntry->src_small;
                }

            }

        } // end of foreach ($albums_object as $key1 => $albumEntry) 
        
        return null; // success

    } // end of public function getUserAlbums(&$albums)
    
    
} // end of cclass SocialConnectMailRu extends SocialConnect

    



class SocialConnectGoogle extends SocialConnect
{
    var $gd = null;
    
    function __construct($user_uid, $connectedAccounts, $redirect_url, $service = null, $account = null) 
    { 
        parent::__construct($user_uid, $connectedAccounts, $redirect_url, $service, $account);
    }
    
    // pass service name here, not using $this->service to have possibility to use just a function without an object, like SocialConnectGoogle::getOauthLink($service)
    public function getOauthLink($service)
    {
        $oauthLink = null;
        switch($service)
        {
            case 'picasa':
                //$oauthLink = $this->gdata_getAuthSubUrl($service, 'https://picasaweb.google.com/data', null, 'photo-album');
                $oauthLink = SocialConnectGoogle::gdata_getAuthSubUrl($service, 'https://picasaweb.google.com/data', null, 'photo-album');
                break;
        }
        return $oauthLink;
    }

    
    // GDATA API helper functions for working with Youtube, Blogger/Blogspot and other Google applicatons
    // pass service name here, not using $this->service, etc, to have possibility to use just a function without an object, like SocialConnectGoogle::gdata_getAuthSubUrl($service, $remote_url, $return_path, $type)
    protected function gdata_getAuthSubUrl($service, $remote_url, $return_path = null, $type = null)
    {
            // init GData library
            $developerKey = '';
            //$this->gdata_init_ZendGdata_library($developerKey, $service);
            SocialConnectGoogle::gdata_init_ZendGdata_library($developerKey, $service);
            
            $next = "http://".$_SERVER['SERVER_NAME'] . '/authsub?';
            /*
            switch($app)
            {
                case 'YouTube':
                    $next .= 'type=youtube&';
                    break;
                case 'Blogger':
                case 'Blogspot':
                    // type=blogger is already in the url
                    break;
            }
            */

            //$next .= str_replace('q=', 'redirect=', $current_query . '&type=' . $type . '&service=' . $service);
            // clear dublicate of a substring like '$service=picasa'
            
            $current_query = explode('?', $_SERVER['REQUEST_URI']);
            $current_query = 'redirect=' . $current_query[0] . ($current_query[1]?'&' . $current_query[1]:'');
            $current_query = str_replace('&service=' . $service, '', $current_query);
            
            $next .= $current_query . '&type=' . $type . '&service=' . $service;

            $scope = $remote_url;
            $secure = 0;
            $session = 1;
            return Zend_Gdata_AuthSub::getAuthSubTokenUri($next, $scope, $secure, $session);
            
    } // end of private function gdata_getAuthSubUrl($app, $remote_url, $return_path = null, $type = null)

    // pass service name here, not using $this->service, etc, to have possibility to use just a function without an object, like SocialConnectGoogle::gdata_init_ZendGdata_library($developerKey, $service)
    protected function gdata_init_ZendGdata_library(&$developerKey, $service = null)
    {

        if(!$developerKey) $developerKey = 'AI39si5O_4mNbrRlCmpiDAMCoyTSD190tBKxEl76A9dXGzq0P3fQL7OQiexI_qelTS-1P0tCO6S1TIJlXyoc8Y_GKnIcJxqmgw';

        $path_to_zend = realpath('.') . "/sites/all/libraries";
        //$path_to_zend = realpath('.') . "/includes";

        set_include_path(get_include_path() . PATH_SEPARATOR . $path_to_zend);
        //echo get_include_path();

        require_once 'Zend/Loader.php'; // the Zend dir must be in your include_path

        Zend_Loader::loadClass('Zend_Gdata_AuthSub');
        //Zend_Loader::loadClass('Zend_Gdata_ClientLogin');    

        Zend_Loader::loadClass('Zend_Gdata_Query');

        if(!$service)
            $service = $this->service;
        
        switch($service)
        {
            case 'picasa':
                Zend_Loader::loadClass('Zend_Gdata_Photos');
                Zend_Loader::loadClass('Zend_Gdata_Media_Extension_MediaKeywords');
                break;

            case 'youtube':
                Zend_Loader::loadClass('Zend_Gdata_YouTube');
                break;

            case 'blogger':

                break;
        }

    } // end of private function gdata_init_ZendGdata_library($app, &$developerKey = NULL)
    
   
} // end of class SocialConnectGoogle extends SocialConnect





class SocialConnectGooglePicasa extends SocialConnectGoogle
{
    function __construct($user_uid, $connectedAccounts, $redirect_url, $service = null, $account = null) 
    { 
        parent::__construct($user_uid, $connectedAccounts, $redirect_url, $service, $account);
    }
    
  
    public function connectAccount($get)
    {
        // init GData library
        $developerKey = '';
        $this->gdata_init_ZendGdata_library($developerKey);

        try
        {
            $this->access_token = trim(Zend_Gdata_AuthSub::getAuthSubSessionToken(trim($get['token'])));
        }
        catch(Exception $e)
        {
            // perhaps it was a try to obtain $sessionToken twice by the same token+
            drupal_add_js('alert("It seems that you\'re trying to use unique link from the ' . ucfirst($this->service) . ' twice. Just authorize again and get a new link."); window.location.href = "' . $this->redirect_url . ($get['type']?'?type=' . $get['type']:'') .'"', 'inline');
            return;
        }
        
        $userData = $this->getUserData();

        // add creds to the db
        $this->existing_account['data'] = $userData;
        $this->existing_account['id'] = $userData['gphotoUser'];
        $this->existing_account['nick'] = $userData['gphotoNickname'];
        
        $this->saveAccount();

    } // end of public function connectAccount($get, $redirect_url, $account_type)

    
    
    protected function getUserData($gd = null)
    {
        
        if(!$gd)
        {
            if(!$this->gd)
            {
                $client = Zend_Gdata_AuthSub::getHttpClient($this->access_token);
                //$gdClient = new Zend_Gdata($client);
                $this->gd = new Zend_Gdata_Photos($client); 
            }
        }
        else
            $this->gd = $gd;

        $userFeed = $this->gd->getUserFeed("default");

        $data['gphotoUser'] = $userFeed[0]->gphotoUser->text;
        $data['gphotoNickname'] = $userFeed[0]->gphotoNickname->text;

        
        foreach($userFeed[0]->author as $key => $author)
        {
            $data['author'][$key]['name'] = $author->name->text;
            $data['author'][$key]['email'] = $author->email->text;
            $data['author'][$key]['uri'] = $author->uri->text;
        }
        

        return $data;
    }
    
    
    
    protected function getPhotoData($entry, $album, $gd = null)
    {
        $data['generalInfo']['title'] = $entry->title->text;
        //$data['generalInfo']['gphotoName'] = $entry->gphotoName->text;

        $data['generalInfo']['id'] = $entry->id->text;
        $data['generalInfo']['gphotoId'] = $entry->gphotoId->text;
        $data['generalInfo']['gphotoAlbumId'] = $entry->gphotoAlbumId->text;
        $data['generalInfo']['gphotoVersion'] = $entry->gphotoVersion->text;

        if(isset($entry->rights->text))
            $data['generalInfo']['rights'] = $entry->rights->text;

        $data['generalInfo']['gphotoWidth'] = $entry->gphotoWidth->text;
        $data['generalInfo']['gphotoHeight'] = $entry->gphotoHeight->text;
        $data['generalInfo']['gphotoSize'] = $entry->gphotoSize->text;

        $data['generalInfo']['gphotoClient'] = $entry->gphotoClient->text;

        $data['generalInfo']['gphotoTimestamp'] = $entry->gphotoTimestamp->text;
        $data['generalInfo']['published'] = $entry->published->text;
        $data['generalInfo']['updated'] = $entry->updated->text;

        $data['generalInfo']['gphotoCommentCount'] = $entry->gphotoCommentCount->text;
        $data['generalInfo']['gphotoCommentingEnabled'] = $entry->gphotoCommentingEnabled->text;

        // we can get all the exif info on the current photo
        //$data['exifTags'][''] = $entry->exifTags->    ;

        if(isset($entry->geoRssWhere->point))
            $data['generalInfo']['geoRssWhere'] = $entry->geoRssWhere->point->pos->text;

        $data['generalInfo']['content'] = $entry->content->src;
        $data['generalInfo']['content type'] = $entry->content->type;


        $data['generalInfo']['summary'] = $entry->summary->text;
        $data['generalInfo']['summary type'] = $entry->summary->type;

        foreach($entry->mediaGroup->content as $key => $media)
        {
            $data['mediaGroup']['content'][$key]['url'] = $media->url;
            $data['mediaGroup']['content'][$key]['medium'] = $media->medium;
            $data['mediaGroup']['content'][$key]['width'] = $media->width;
            $data['mediaGroup']['content'][$key]['height'] = $media->height;
        }

        foreach($entry->mediaGroup->credit as $key => $credit)
            $data['mediaGroup']['credit'][$key] = $credit->text;

        $data['mediaGroup']['description'] = $entry->mediaGroup->description->text;
        $data['mediaGroup']['keywords'] = $entry->mediaGroup->keywords->text;

        foreach($entry->mediaGroup->thumbnail as $key => $thumbnail)
        {
            $data['mediaGroup']['thumbnail'][$key]['url'] = $thumbnail->url;
            $data['mediaGroup']['thumbnail'][$key]['width'] = $thumbnail->width;
            $data['mediaGroup']['thumbnail'][$key]['height'] = $thumbnail->height;
            $data['mediaGroup']['thumbnail'][$key]['text'] = $thumbnail->text;
        }

        $data['mediaGroup']['description'] = $entry->mediaGroup->description->text;
        $data['mediaGroup']['keywords'] = $entry->mediaGroup->keywords->text;

        foreach($entry->category as $key => $category)
            $data['category'][$key] = $category->text;

        foreach($entry->link as $key => $link)
        {
            $data['link'][$key]['href'] = $link->href;
            $data['link'][$key]['rel'] = $link->rel;
        }

        //$data['user']['gphotoUser'] = $entry->gphotoUser->text;
        //$data['user']['gphotoNickname'] = $entry->gphotoNickname->text;

        foreach($entry->author as $key => $author)
        {
            $data['user']['author'][$key]['name'] = $author->name->text;
            $data['user']['author'][$key]['email'] = $author->email->text;
            $data['user']['author'][$key]['uri'] = $author->uri->text;
        }

        // get comments
        $this->getPhotoComments($data, $album, $gd);

        return $data;
        
    } // end of private function picasa_getPhotoData($gd, $entry, $album)
    
        
    
    protected function getPhotoComments(&$photo, $album, $gd = null)
    {
        if(!$gd)
        {
            if(!$this->gd)
            {
                $client = Zend_Gdata_AuthSub::getHttpClient($this->access_token);
                //$gdClient = new Zend_Gdata($client);
                $this->gd = new Zend_Gdata_Photos($client); 
            }
        }
        else
            $this->gd = $gd;
        
        // Create a Zend_Gdata_Photos_PhotoQuery
        $query = $this->gd->newPhotoQuery();

        $username = "default";
        $photoid = $photo['generalInfo']['gphotoId']; //"12345";
        $albumname = $album['generalInfo']['gphotoName']; //"sample.albumname";

        // indicate the user's data to retrieve
        $query->setUser($username);
        $query->setAlbumName($albumname);
        $query->setPhotoId($photoid);

        // set to only return comments 
        $query->setKind("comment");
        //$query->setMaxResults("10");

        $photoFeed = $this->gd->getPhotoFeed($query);

        // because we specified 'comment' for the kind, only CommentEntry objects 
        // will be contained in the UserFeed
        foreach ($photoFeed as $key => $commentEntry) 
        {
            $photo['comments'][$key] = $this->getCommentData($commentEntry);
            //$photo['comments'][$key]['raw'] = park_misc_dpr($commentEntry);
        }

    } // end of private function picasa_getPhotoComments($gd, &$photo, $album)
    
    
        
    protected function getCommentData($entry)
    {
        $data['title'] = $entry->title->text;
    
        $data['id'] = $entry->id->text;
        $data['gphotoId'] = $entry->gphotoId->text;
        $data['gphotoPhotoId'] = $entry->id->text;

        $data['content'] = $entry->content->text;

        $data['published'] = $entry->published->text;
        $data['updated'] = $entry->updated->text;

        foreach($entry->author as $key => $author)
        {
            $data['author'][$key]['name'] = $author->name->text;
            if(isset($author->email))
                $data['author'][$key]['email'] = $author->email->text;
            if(isset($author->uri))
                $data['author'][$key]['uri'] = $author->uri->text;

            foreach($author->extensionElements as $key2 => $ext)
                    $data['author'][$key][$ext->rootElement] = $ext->text;
        }    

        foreach($entry->category as $key => $category)
            $data['category'][$key] = $category->text;

        foreach($entry->link as $key => $link)
        {
            $data['link'][$key]['href'] = $link->href;
            $data['link'][$key]['rel'] = $link->rel;
        }

        if(isset($entry->rights))
            $data['rights'] = $entry->rights->text;

        if(isset($entry->summary))
        {
            $data['summary'] = $entry->summary->text;
            $data['summary type'] = $entry->summary->type;
        }
        
        return $data;
        
    } // end of private function picasa_getCommentData($entry)
    
    
    
    protected function getAlbumData($entry)
    {
        $data['generalInfo']['title'] =  $entry->title->text;
        $data['generalInfo']['gphotoName'] = $entry->gphotoName->text;

        $data['generalInfo']['gphotoId'] = $entry->gphotoId->text;
        $data['generalInfo']['id'] = $entry->id->text;

        $data['generalInfo']['gphotoAccess'] = $entry->gphotoAccess->text;
        $data['generalInfo']['rights'] = $entry->rights->text;

        $data['generalInfo']['gphotoLocation'] = $entry->gphotoLocation->text;

        $data['generalInfo']['gphotoTimestamp'] = $entry->gphotoTimestamp->text;
        $data['generalInfo']['published'] = $entry->published->text;
        $data['generalInfo']['updated'] = $entry->updated->text;

        $data['generalInfo']['gphotoNumPhotos'] = $entry->gphotoNumPhotos->text;
        $data['generalInfo']['gphotoCommentCount'] = $entry->gphotoCommentCount->text;
        $data['generalInfo']['gphotoCommentingEnabled'] = $entry->gphotoCommentingEnabled->text;

        $data['generalInfo']['summary'] = $entry->summary->text;
        $data['generalInfo']['summary type'] = $entry->summary->type;

        foreach($entry->mediaGroup->content as $key => $media)
        {
            $data['mediaGroup']['content'][$key]['url'] = $media->url;
            $data['mediaGroup']['content'][$key]['medium'] = $media->medium;
            $data['mediaGroup']['content'][$key]['width'] = $media->width;
            $data['mediaGroup']['content'][$key]['height'] = $media->height;
        }

        foreach($entry->mediaGroup->credit as $key => $credit)
            $data['mediaGroup']['credit'][$key] = $credit->text;

        $data['mediaGroup']['description'] = $entry->mediaGroup->description->text;
        $data['mediaGroup']['keywords'] = $entry->mediaGroup->keywords->text;

        foreach($entry->mediaGroup->thumbnail as $key => $thumbnail)
        {
            $data['mediaGroup']['thumbnail'][$key]['url'] = $thumbnail->url;
            $data['mediaGroup']['thumbnail'][$key]['width'] = $thumbnail->width;
            $data['mediaGroup']['thumbnail'][$key]['height'] = $thumbnail->height;
            $data['mediaGroup']['thumbnail'][$key]['text'] = $thumbnail->text;
        }

        $data['user']['gphotoUser'] = $entry->gphotoUser->text;
        $data['user']['gphotoNickname'] = $entry->gphotoNickname->text;

        /*
        foreach($entry->author as $key => $author)
        {
            $data['user']['author'][$key]['name'] = $author->name->text;
            $data['user']['author'][$key]['email'] = $author->email->text;
            $data['user']['author'][$key]['uri'] = $author->uri->text;
        }
        */
        foreach($entry->category as $key => $category)
            $data['category'][$key] = $category->text;

        foreach($entry->link as $key => $link)
        {
            $data['link'][$key]['href'] = $link->href;
            $data['link'][$key]['rel'] = $link->rel;
        }

        return $data;
        
    } // end of private function picasa_getAlbumData($entry)
    

    protected function getUserAlbums_fromRemote($aid = null, $gd = null)
    {
        // init GData library
        $developerKey = '';
        $this->gdata_init_ZendGdata_library($developerKey, 'picasa');

        
        if(!$gd)
        {
            if(!$this->gd)
            {
                if($this->existing_account['access_token'])
                {
                    //$gdClient = new Zend_Gdata($client); // example for youtube
                    $this->gd = new Zend_Gdata_Photos(Zend_Gdata_AuthSub::getHttpClient($this->existing_account['access_token']));
                }
                else 
                    return 'Error: no access token provided!';
            }
        }
        else
            $this->gd = $gd;
        
       
        
        try {
                $userFeed = $this->gd->getUserFeed("default");

                foreach ($userFeed as $key1 => $albumEntry) 
                {
                    $album = $this->getAlbumData($albumEntry);
                    
                    $aid = $albumEntry->gphotoId->text;
                            
                    $this->albums[$aid]['info']['title'] = $albumEntry->title->text;
                    $this->albums[$aid]['info']['aid'] = $albumEntry->gphotoId->text;
                    $this->albums[$aid]['info']['published'] = strtotime($albumEntry->published->text);
                   
                    foreach($album['mediaGroup']['thumbnail'] as $key0 => $value)
                    {
                        $this->albums[$aid]['th'][$key0]['url'] = $album['mediaGroup']['content'][0]['url'];
                        $this->albums[$aid]['th'][$key0]['img_src'] = $value['url'];
                    }
                        
                    foreach($album as $key2 => $albumData)
                       $this->albums[$aid]['data'][$key2] = $this->dpr($albumData);

                    
                    // from example
                    /*
                    $query = new Zend_Gdata_Photos_AlbumQuery();
                    $query->setUser($user);
                    $query->setAlbumId($albumId);
                    $albumFeed = $photos->getAlbumFeed($query);
                    */
                    
                    // Creates a Zend_Gdata_Photos_AlbumQuery
                    $query = $this->gd->newAlbumQuery();
                    $query->setUser("default");
                    $query->setAlbumId($albumEntry->gphotoId->text);
                    $albumFeed = $this->gd->getAlbumFeed($query);

                    //$this->albums[$key1]['photos']['title'] = $albumEntry->title->text;
                    
                    foreach ($albumFeed as $key3 => $photoEntry) 
                    {
                        $photo = $this->getPhotoData($photoEntry, $album);

                        $pid = $photo['generalInfo']['gphotoId'];
                        
                        $this->albums[$aid]['photos'][$pid]['info']['title'] = $photoEntry->title->text;
                        $this->albums[$aid]['photos'][$pid]['info']['pid'] = $pid;
                        $this->albums[$aid]['photos'][$pid]['info']['published'] = strtotime($photo['generalInfo']['published']);
                                
                        foreach($photo['mediaGroup']['thumbnail'] as $key5 => $value)
                        {
                            $this->albums[$aid]['photos'][$pid]['th'][$key5]['url'] = $photo['mediaGroup']['content'][0]['url'];
                            $this->albums[$aid]['photos'][$pid]['th'][$key5]['img_src'] = $value['url'];
                        }
                        // override the smallest thumb to show a bit larger one
                        $this->albums[$aid]['photos'][$pid]['th'][0]['img_src'] = $photo['mediaGroup']['thumbnail'] [1]['url'];
                        
                        foreach($photo as $key4 => $value)
                        {
                            //$this->albums[$key1]['photos']['photo_' . $key3][$key4]['title'] = $key4;
                            ////$this->albums[$key1]['photos']['photo_' . $key3][$key4]['data'] = $this->dpr($value);
                            $this->albums[$aid]['photos'][$pid]['data'][$key4] = $this->dpr($value);
                        }
                    } // end of foreach ($albumFeed as $key3 => $photoEntry) 

                } // end of foreach ($userFeed as $key1 => $albumEntry) 
                
                return null; // success
                
            } // end of try {
            catch (Zend_Gdata_App_HttpException $e) 
            {
                $error_message = 'Error: ' . $e->getMessage() . '<br>';
                if ($e->getResponse() != null) 
                    $error_message .= 'Error body: ' . $e->getResponse()->getBody() . '<br>'; 

                // In new versions of Zend Framework, you also have the option
                // to print out the request that was made.  As the request
                // includes Auth credentials, it's not advised to print out
                // this data unless doing debugging
                // echo "Request: <br />\n" . $e->getRequest() . "<br />\n";
                
                return $error_message;
            } 


    }
    
} // end of 
