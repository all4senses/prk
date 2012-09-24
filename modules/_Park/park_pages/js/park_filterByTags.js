(function ($) {

  Drupal.behaviors.park_filterByTags = {
    attach: function (context, settings) {
       
       //console.log(Drupal.settings.park_image);
       $(".chzn-select").chosen();
       
       $("#doFilterByTag").click(function(){
         console.log($("#contentUrl").val());
         console.log($("#contentOpened_query").val());
         
         tags = jQuery('.chzn-select').val().toString();
         console.log('tags = ' + tags);
         
         //str = ''; jQuery('.chzn-select [selected][disabled]').each(function(){str = str + (str ? ',' : '') + jQuery(this).val()}); console.log(str);
         tagsDisabled = ''; 
         jQuery('.chzn-select [selected][disabled]').each(
          function(){tagsDisabled = tagsDisabled + (tagsDisabled ? ',' : '') + jQuery(this).val()
         }); 
         console.log('tagsDisabled = ' + tagsDisabled);
         
         tags = (tags ? ',' : '') + tagsDisabled;
         
         console.log('tagsAll = ' + tags);
         
         if (tags) {
          if ($("#contentOpened_query").val()) {
            //top.location.href = $("#contentUrl").val() + '&tags=' + tags;
            console.log('Url 1 = ' + $("#contentUrl").val() + '&tags=' + tags);
          }
          else {
            //top.location.href = $("#contentUrl").val() + '?tags=' + tags;
            console.log('Url 2 = ' + $("#contentUrl").val() + '?tags=' + tags);
          }
         }
         
       });
       

    }
  };
  
}(jQuery));