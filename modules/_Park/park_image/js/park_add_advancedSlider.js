(function ($) {
  Drupal.behaviors.park_add_advancedSlider = {
    attach: function (context, settings) {


                $('#responsive-slider').advancedSlider({width: '80%',
												height: '70%',
												scaleType: 'outsideFit',
												skin: 'glossy-square-gray',
												effectType: 'swipe',
												pauseSlideshowOnHover: true,
												swipeThreshold: 50,
												slideButtons: false,
												thumbnailType: 'scroller',
												thumbnailButtons: true,
												thumbnailScrollerResponsive: true,
												minimumVisibleThumbnails: 2,
											    slideProperties:{
													0:{captionSize: 35, captionHideEffect: 'slide'},
													1:{captionPosition: 'custom', captionShowEffect: 'fade', captionHeight: 160, captionLeft: 70, slideshowDelay: 10000},
													3:{captionSize: 40},
													5:{captionPosition: 'left', captionSize: 150, captionHideEffect: 'slide'},
													7:{captionPosition: 'right', captionSize: 150, captionHideEffect: 'slide'}
												}
                });

        
        console.log('in park_add_advancedSlider...');
       
       
//       for (group_class in Drupal.settings.park_image) {
//         
//          //console.log(group_class);
//
//       }

    }
  };
  
}(jQuery));