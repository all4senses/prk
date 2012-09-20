(function ($) {

  Drupal.behaviors.park_addColorboxToAlbums = {
    attach: function (context, settings) {
       
       console.log(Drupal.settings.park_image);
       for (group_class in Drupal.settings.park_image) {
         console.log(group_class);
          //Assign the ColorBox event to elements
          jQuery('.' + group_class).colorbox({transition:"fade", slideshow:true, slideshowAuto: false, rel:"group_' . $node->nid . '", width:"95%", height:"95%"});

          //$(".group2").colorbox({rel:"group2", transition:"fade"});
          //$(".group3").colorbox({rel:"group3", transition:"none", width:"75%", height:"75%"});
          //$(".group4").colorbox({rel:"group4", slideshow:true});
       }

    }
  };
  
}(jQuery));