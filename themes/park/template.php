<?php
/**
 * Implements hook_html_head_alter().
 * We are overwriting the default meta character type tag with HTML5 version.
 */
function park_html_head_alter(&$head_elements) {
  $head_elements['system_meta_content_type']['#attributes'] = array(
    'charset' => 'utf-8'
  );
}

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
function park_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $heading = '<h3 class="element-invisible">' . t('You are here') . '</h3>';
    // Uncomment to add current page to breadcrumb
	// $breadcrumb[] = drupal_get_title();
    return '<nav class="breadcrumb">' . $heading . implode(' » ', $breadcrumb) . '</nav>';
  }
}

/**
 * Duplicate of theme_menu_local_tasks() but adds clearfix to tabs.
 */
function park_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h3 class="element-invisible">' . t('Primary tabs') . '</h3>';
    $variables['primary']['#prefix'] .= '<ul class="tabs primary clearfix">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h3 class="element-invisible">' . t('Secondary tabs') . '</h3>';
    $variables['secondary']['#prefix'] .= '<ul class="tabs secondary clearfix">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }
  return $output;
}

/**
 * Override or insert variables into the page template.
 */
function park_process_page(&$variables) {
  if(isset($variables['node'])) {
    $variables['theme_hook_suggestions'][] = 'page__' . $variables['node']->type;
  }
}

/**
 * Override or insert variables into the node template.
 */
function park_preprocess_node(&$variables) {
  $variables['submitted'] = t('Published by !username on !datetime', array('!username' => $variables['name'], '!datetime' => $variables['date']));
  if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
    $variables['classes_array'][] = 'node-full';
  }
  if(isset($variables['node'])) {
    
    $use_article_template = array('blog_post', 'master_class', 'album', 'news_post', 'section');
    //if($variables['node']->type == 'blog_post' || $variables['node']->type == 'master_class' || $variables['node']->type == 'album' || $variables['node']->type == 'news_post') {
    if( in_array($variables['node']->type, $use_article_template)) {
      $variables['theme_hook_suggestions'][] = 'node__article';
    }
    elseif($variables['node']->type == 'webform') {
      $variables['theme_hook_suggestions'][] = 'node__admin_page';
    }
    
  }
  
}

/**
 * Preprocess variables for region.tpl.php
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("region" in this case.)
 */
function park_preprocess_region(&$variables, $hook) {
  // Use a bare template for the content region.
  if ($variables['region'] == 'content') {
    $variables['theme_hook_suggestions'][] = 'region__bare';
  }
}

/**
 * Override or insert variables into the block templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function park_preprocess_block(&$variables, $hook) {
  // Use a bare template for the page's main content.
  if ($variables['block_html_id'] == 'block-system-main') {
    $variables['theme_hook_suggestions'][] = 'block__bare';
  }
  $variables['title_attributes_array']['class'][] = 'block-title';
}

/**
 * Override or insert variables into the block templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function park_process_block(&$variables, $hook) {
  // Drupal 7 should use a $title variable instead of $block->subject.
  $variables['title'] = $variables['block']->subject;
}

/**
 * Changes the search form to use the "search" input element of HTML5.
 */
function park_preprocess_search_block_form(&$vars) {
  $vars['search_form'] = str_replace('type="text"', 'type="search"', $vars['search_form']);
}

/**
 * Changes the search button label. Here... because it doesn't work via module hook.
 */
function park_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'search_block_form') {
    
    $form['actions']['submit']['#value'] = '';
    
    // Autohiding hint.
    $default_search_text = t('Search Site Here');
    $form['search_block_form']['#default_value'] = $default_search_text;
    $form['default_text']['#default_value'] = $default_search_text;
    // Cause a fatal error without it for anonymous.
    $form['default_text']['#type'] = 'hidden';
    
    
    // Example! Does NOT work!!! The above one works!
    //$form['search_block_form']['#value'] = t($default_search_text); // Set a default value for the textfield
    
    // Add extra attributes to the text box
    // Without this a hint autohiding will not work for anonymous.
    $form['search_block_form']['#attributes']['onblur'] = "if (this.value == '') {this.value = '$default_search_text';}";
    $form['search_block_form']['#attributes']['onfocus'] = "if (this.value == '$default_search_text') {this.value = '';}";
  }
}


function park_username($object) {
  return str_replace(' ('. t('not verified') .')', '', theme_username($object));
}


/**
* Default theme function for all RSS rows.
*/
function park_preprocess_views_view_rss(&$vars) {
  $namespaces = $vars['view']->style_plugin->namespaces;
  $disabled_namespaces = array('content', 'dc', 'foaf', 'og', 'rdfs', 'sioc', 'sioct', 'skos', 'xsd', 'xmlns:addthis');
  foreach ($disabled_namespaces as $disabled_namespace) {
    if (isset($namespaces[$disabled_namespace])) {
      unset($namespaces[$disabled_namespace]);
    }
  }
  $vars['namespaces'] = '';
  foreach ($namespaces as $key => $value) {
    $vars['namespaces'] .= ' ' . $key . '="' . $value . '"';
  }
}


/**
* Default theme function for all RSS rows.
*/
function park_preprocess_views_view_row_rss(&$vars) {
  
  $node = $vars['view']->style_plugin->row_plugin->nodes[$vars['row']->nid];
  //$vars['description'] = check_plain(htmlspecialchars_decode($node->field_a_teaser['und'][0]['value']));
  if (isset($node->body['und'][0]['value'])) {
    $rss_teaser = park_misc_getArticleTeaserData('all', $node->body['und'][0]['value'], $vars['row']->nid, 400, TRUE);
    // Clear attribute typeof="foaf:Image" from the img tag (which iss added by the core rdf module via hook_preprocess_image).
    $rss_teaser = preg_replace('|typeof="foaf:Image" |', '', $rss_teaser);
    // Convert relative links to absolute.
    $rss_teaser = preg_replace('|href="/|', 'href="http://park.all4senses.com/', $rss_teaser);
    // Restore a normal state of a YouTube url from a token.
    // [video: http://www.youtube.com/watch?v=SoMS77zE7iE]
    $rss_teaser =   preg_replace('|\[video:.*(http.*)\]|', '<a href="$1"> [Watch a video] </a>', $rss_teaser);
    $vars['description'] = check_plain(htmlspecialchars_decode($rss_teaser));
  }
  
  // Replace username with real user name for <dc:creator>
  $vars['item_elements'] = preg_replace('|<dc:creator>.*</dc:creator>|', '<dc:creator>' . park_misc_getUserRealName($node->uid) . '</dc:creator>', $vars['item_elements']);
}


/**
 * Display the simple view of rows one after another
 */
/*
function park_preprocess_views_view_unformatted(&$vars) {
  
  if( ($vars['view']->name == 'blog' || $vars['view']->name == 'news') && $vars['view']->current_display == 'page') {
    $vars['theme_hook_suggestions'][] = 'views-view-unformatted__blog__page';
    $vars['theme_hook_suggestion'] = 'views-view-unformatted__blog__page';
    dpm($vars);
  }
  
  
}
*/


/**
 * Theme function for a CAPTCHA element.
 * 
 * a4s rename CAPTCHA to Captcha
 *
 * Render it in a fieldset if a description of the CAPTCHA
 * is available. Render it as is otherwise.
 */
/*
function park_captcha($variables) {
  $element = $variables['element'];
  if (!empty($element['#description']) && isset($element['captcha_widgets'])) {
    $fieldset = array(
      '#type' => 'fieldset',
      '#title' => t('Captcha'),
      '#description' => $element['#description'],
      '#children' => drupal_render_children($element),
      '#attributes' => array('class' => array('captcha')),
    );
    return theme('fieldset', array('element' => $fieldset));
  }
  else {
    return '<div class="captcha">' . drupal_render_children($element) . '</div>';
  }
}
*/


/**
 * Preprocess the primary theme implementation for a view.
 */
/*
function park_preprocess_views_view(&$vars) {
  
  // I set title for preface (at park_misc_views_pre_render(&$view)) instead of a view itself.
//  if ($vars['view']->current_display == 'page_by_tag') {
//    if (!$vars['title']) {
//      $vars['title'] = '<h1>' . $vars['view']->get_title() . '</h1>'; //str_replace('%1', $vars['view']->build_info['substitutions']['%1'], $vars['view']->build_info['title']); 
//    }  
//  }

  // hasn't worked out to make use one temlate for different views unformatted
  
  if (isset($vars['view']->name) && ($vars['view']->name == 'blog' || $vars['view']->name == 'news') ) {
    $function = 'park_preprocess_views_view_unformatted'; 
    if (function_exists($function)) {
     $function($vars);
    }
  }
  
}
*/


/*
function park_preprocess_html(&$variables) {
  //dpm($variables);
  //global $user;
  //if ($user->uid == 1) {
    foreach ($variables['page']['content']['system_main']['nodes'] as $key => $html) {
      //dpr($html['body']['#object']->rdf_mapping);
      if (isset($variables['page']['content']['system_main']['nodes'][$key]['body']['#object']->rdf_mapping['comment_count']['datatype'])) {
        unset($variables['page']['content']['system_main']['nodes'][$key]['body']['#object']->rdf_mapping['comment_count']['datatype']);
      }
      //dpr($variables['page']['content']['system_main']['nodes'][$key]['body']['#object']->rdf_mapping);
    }
    //die;
  //}

}
 
*/