(function ($) {

  Drupal.behaviors.park_makeImagesZoomable = {
    attach: function (context, settings) {
       
       //$(".full-content img").colorbox({iframe:true, innerWidth:425, innerHeight:344});
       //$(".full-content img").colorbox({rel:"gallery"});
       $(".full-content img").colorbox({href: this.src});
       console.log('full content!');
       
    }
  };

}(jQuery));
