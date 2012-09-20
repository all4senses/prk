(function ($) {

  Drupal.behaviors.park_addColorboxToAlbums = {
    attach: function (context, settings) {
       
       console.log(Drupal.settings.park_image);
       for (x in Drupal.settings.park_image) {
         console.log(x);
        //txt=txt + person[x];
       }

    }
  };
  
}(jQuery));