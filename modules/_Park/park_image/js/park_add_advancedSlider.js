(function ($) {
  Drupal.behaviors.park_add_advancedSlider = {
    attach: function (context, settings) {

                var sl;
               sl = $('#responsive-slider').advancedSlider({width: '80%',
												height: '60%',
												scaleType: 'proportionalFit', //'insideFit',
                        
                        skin:'glossy-curved-rounded-violet', //minimal-small', // 'glossy-square-blue',
                        //scrollbarSkin:'scrollbar-3-light', 
                        thumbnailsType:'navigation', 
                        thumbnailScrollbar:true,
                        
                        
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
                        
                        transitionStart: function(event){
                          console.log('start', event);
                          if (event.index == 0) {
                            previous_slide_index = total_slides - 1;
                          }
                          else {
                            previous_slide_index = event.index - 1;
                          }
                          console.log('previous_slide_index = ' + previous_slide_index);
                          previous_slide = sl.getSlideAt(previous_slide_index);
                          console.log('previous_slide', previous_slide);
                          
                          previous_slide.html.each(function(){
                            $(this).removeClass('in');
                            console.log('in previous', this);
                          });
                          /*
                          if (event.index == 2) {
                            $('.content-box .title').removeClass('in');
                          }
                          */
                        },
                        transitionComplete: function(event){
                          console.log('completed', event);
                          current_slide = sl.getSlideAt(event.index);
                          console.log('current_slide', current_slide);
                          
                          current_slide.html.each(function(){
                            $(this).addClass('in');
                            console.log('in current', this);
                          });
                            
                          /*
                          if (event.index == 1) {
                            
                            $('.content-box .title').addClass('in');
                            event.data.html.each(function(){
                              console.log(this);
                            });
                          }
                          */
                          
                        }
            		});

                var total_slides = sl.totalSlides();
                console.log('total_slides = ', total_slides);
                
                console.log('sl = ', sl);


                // set the initial height of the slider to 50% from the width
                $('#responsive-slider').css('height', $('#responsive-slider').width() * 0.50);
                $('#responsive-slider').advancedSlider().doSliderLayout();

                // as the window resizes, maintain the slider's height at 50% from the width
                $(window).resize(function() {
                  $('#responsive-slider').css('height', $('#responsive-slider').width() * 0.50);
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