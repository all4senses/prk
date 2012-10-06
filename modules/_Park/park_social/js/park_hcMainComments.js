(function ($) {

  Drupal.behaviors.park_hcRecentComments = {
    attach: function (context, settings) {

      var _hcp = _hcp || {};
      _hcp.widget_id = 3235;
      _hcp.widget = "Stream"; 
      _hcp.append = "#hypercomments_main";
      
      if (Drupal.settings.park_social.uid) {
        _hcp.auth = Drupal.settings.park_social.auth;
        console.log(Drupal.settings.park_social);
      }
      //console.log('uid = ' + Drupal.settings.park_social.uid);
      //console.log('auth = ' + Drupal.settings.park_social.auth);
      
      //<?php echo ($user->uid ? '_hcp.auth = "' . $auth . '"' : ''); ?>;
    
      (function() { 
      var hcc = document.createElement("script"); hcc.type = "text/javascript"; hcc.async = true;
      hcc.src = ("https:" == document.location.protocol ? "https" : "http")+"://widget.hypercomments.com/apps/js/hc.js";
      var s = document.getElementsByTagName("script")[0]; s.parentNode.insertBefore(hcc, s.nextSibling); 
      })();

    }
  };

}(jQuery));
