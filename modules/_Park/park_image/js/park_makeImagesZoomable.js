(function ($) {

  Drupal.behaviors.park_makeImagesZoomable = {
    attach: function (context, settings) {
       
       $(".full-content img").colorbox({iframe:true, innerWidth:425, innerHeight:344});
       console.log('full content!');
       
    }
  };

}(jQuery));
