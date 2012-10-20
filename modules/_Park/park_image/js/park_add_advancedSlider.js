(function ($) {
  Drupal.behaviors.park_add_advancedSlider = {
    attach: function (context, settings) {

               var sl;
               var current_slide_index = 0;
               
               console.log('start 1');
               
               sl = $('#responsive-slider').advancedSlider({
                        //width: '80%',
												//height: '70%',
                        
                        width: '900',
                        height: '80%',
                        scaleType: 'exactFit',//'insideFit',
                        
												//scaleType: 'proportionalFit', //'insideFit',
                        
                        skin:'glossy-curved-rounded-violet', //minimal-small', // 'glossy-square-blue',
                        //scrollbarSkin:'scrollbar-3-light', 
                        thumbnailsType:'navigation', 
                        thumbnailScrollbar:true,
                        
                        captionToggle: true,
                        
												effectType: 'slice',//'swipe',
												pauseSlideshowOnHover: true,
												swipeThreshold: 50,
                        
                        lightbox: true,
                        //shadow: false,
                        
                        //slideButtons: false,
												//thumbnailType: 'scroller',
												//thumbnailButtons: true,
												thumbnailScrollerResponsive: true,
												minimumVisibleThumbnails: 2,
                        
												slideArrowsToggle: false,
												slideProperties:{
													0:{captionSize: 35, captionHideEffect: 'slide'},
													1:{captionPosition: 'custom', captionShowEffect: 'fade', captionHeight: 160, captionLeft: 70, slideshowDelay: 10000},
													3:{captionSize: 40},
													5:{captionPosition: 'left', captionSize: 150, captionHideEffect: 'slide'},
													7:{captionPosition: 'right', captionSize: 150, captionHideEffect: 'slide'}
												},
                        
                        transitionStart: startTransition,
                        transitionComplete: completeTransition
            		});

                var total_slides = sl.totalSlides();

                // set the initial height of the slider to 50% from the width
                $('#responsive-slider').css('height', $('#responsive-slider').width() * 0.50);
                $('#responsive-slider').advancedSlider().doSliderLayout();

                // as the window resizes, maintain the slider's height at 50% from the width
                $(window).resize(function() {
                  $('#responsive-slider').css('height', $('#responsive-slider').width() * 0.50);
                });
      
      
      
                function completeTransition(event) {
                 
                  current_slide = sl.getSlideAt(event.index);
                 
                  $(current_slide.html).addClass('in');
                  current_slide_index = event.index;

                  // Doesn't work
                  /*
                  current_slide.html.each(function(){
                    $(this).addClass('in');
                  });
                  */
                }
                
                
                function startTransition(event) {
                 
                  previous_slide_index = current_slide_index;
                  
                  if (sl) {
                    previous_slide = sl.getSlideAt(previous_slide_index);
                 
                    $(previous_slide.html).removeClass('in');
                  }
                 
                }
                        
        
    }
  };
  
}(jQuery));