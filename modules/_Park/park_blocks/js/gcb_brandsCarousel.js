(function ($) {

  Drupal.behaviors.gcb_brandsCarousel = {
    attach: function (context, settings) {
       
        jQuery("#mycarousel").jcarousel({
            wrap: "circular" // wrap: 'last',
            
            // Autoscrolling
            //auto: 2,
            //initCallback: mycarousel_initCallback
        });

    }
  };
  
  
  // Comment for now because we don't use here autoscrolling
  /*
  function mycarousel_initCallback(carousel)
  {
      // Disable autoscrolling if the user clicks the prev or next button.
      carousel.buttonNext.bind('click', function() {
          carousel.startAuto(0);
      });

      carousel.buttonPrev.bind('click', function() {
          carousel.startAuto(0);
      });

      // Pause autoscrolling if the user moves with the cursor over the clip.
      carousel.clip.hover(function() {
          carousel.stopAuto();
      }, function() {
          carousel.startAuto();
      });
  };
  */
}(jQuery));