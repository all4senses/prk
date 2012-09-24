(function ($) {

  Drupal.behaviors.park_filterByTags = {
    attach: function (context, settings) {
       
       //console.log(Drupal.settings.park_image);
       $(".chzn-select").chosen();
       $("#doFilterByTag").click(function(){
         console.log($("#contentUrl").val());
         console.log($("#contentOpened_query").val());
         var tags = jQuery('.chzn-select').val().toString();
         if (tags) {
          if ($("#contentOpened_query").val()) {
            top.location.href = $("#contentUrl").val() + '&tags=' + tags;
          }
          else {
            top.location.href = $("#contentUrl").val() + '?tags=' + tags;
          }
         }
         
       });
       

    }
  };
  
}(jQuery));