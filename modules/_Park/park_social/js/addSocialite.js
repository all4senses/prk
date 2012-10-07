(function ($) {

  Drupal.behaviors.park_addSocialite = {
    attach: function (context, settings) {
       
       var buttonLoaded = false;

       $('#header').one('mouseenter', function() {
          if (!buttonLoaded) {
            buttonLoaded = true;            
            Socialite.load('.social-buttons');
          }
        });
       $('.content.page').one('mouseenter', function() {
          if (!buttonLoaded) {
            buttonLoaded = true;            
            Socialite.load('.social-buttons');
          }
        });
        
        $('.share').one('mouseenter', function() {
          if (!buttonLoaded) {
            buttonLoaded = true;            
            Socialite.load('.social-buttons');
          }
        });

       
    }
  };

}(jQuery));
