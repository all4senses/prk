(function ($) {
  Drupal.behaviors.park_add_sequenceSlideshow = {
    attach: function (context, settings) {

        var options = {
          nextButton: true,
          prevButton: true,
          animateStartingFrameIn: true,
          transitionThreshold: 250,
          preloadTheseFrames: [1],
          preloadTheseImages: [
            "images/tn-model1.png",
            "images/tn-model2.png",
            "images/tn-model3.png"
          ]
        };

        var sequence = $("#sequence").sequence(options).data("sequence");

        sequence.afterLoaded = function(){
          $("#nav").fadeIn(100);
          $("#nav li:nth-child("+(sequence.settings.startingFrameID)+") img").addClass("active");
        }

        sequence.beforeNextFrameAnimatesIn = function(){
          $("#nav li:not(:nth-child("+(sequence.nextFrameID)+")) img").removeClass("active");
          $("#nav li:nth-child("+(sequence.nextFrameID)+") img").addClass("active");
        }

        $("#nav li").click(function(){
          if(!sequence.active){
            $(this).children("img").removeClass("active").children("img").addClass("active");
            sequence.nextFrameID = $(this).index()+1;
            sequence.goTo(sequence.nextFrameID);
          }
        });
        
        console.log('in park_add_sequenceSlideshow...');
       
       
//       for (group_class in Drupal.settings.park_image) {
//         
//          //console.log(group_class);
//
//       }

    }
  };
  
}(jQuery));