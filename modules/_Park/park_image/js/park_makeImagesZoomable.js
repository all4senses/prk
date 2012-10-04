(function ($) {

  Drupal.behaviors.park_makeImagesZoomable = {
    attach: function (context, settings) {
       
       //$(".full-content img").colorbox({iframe:true, innerWidth:425, innerHeight:344});
       //$(".full-content img").colorbox({rel:"gallery"});
       //$(".full-content img").css({'cursor' : 'pointer', 'cursor' : '-webkit-zoom-in', 'cursor' : '-moz-zoom-in'});
       $(".full-content img").css('cursor', 'pointer').css('cursor', '-webkit-zoom-in').css('cursor', '-webkit-zoom-in').colorbox({
         //href: this.src
         width:"80%", 
         height:"80%",
         href: function() {
           console.log(this.src);
           return this.src;
         }
       });
       console.log('full content!');
       
    }
  };

}(jQuery));
