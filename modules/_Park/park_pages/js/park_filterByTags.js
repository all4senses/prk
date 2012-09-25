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
         
         tags = (tags ? (tags + ',') : '') + tagsDisabled;
         
         console.log('tagsAll = ' + tags);
         console.log('top.location.href = ' + decodeURIComponent(top.location.href));
         
         new_url = location.origin + location.pathname;
         
         var params = {};
         current_url = decodeURIComponent(location.search);
         
         if (current_url) {
              var parts = current_url.substring(1).split('&');

              for (var i = 0; i < parts.length; i++) {
                  var nv = parts[i].split('=');
                  if (!nv[0]) continue;
                  params[nv[0]] = nv[1] || true;
              }
         }

         
         //console.log(params);
         
         param_string = '';
         for (p in params) {
           if (p != 'tags') {
            param_string = param_string + (param_string ? '&' : '?') + p + '=' + params[p];
           }
         }
         console.log(param_string);
         
         if (tags) {
           tags = encodeURIComponent(tags);
          // 'onChange' => "top.location.href='http://getvoip.com/" . $_GET['q'] . "?provider=' + encodeURIComponent(document.getElementById('select_provider').options[document.getElementById('select_provider').selectedIndex].value) + '$url'"),
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