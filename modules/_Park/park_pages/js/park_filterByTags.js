(function ($) {

  Drupal.behaviors.park_filterByTags = {
    attach: function (context, settings) {
       
       $(".chzn-select").chosen();
       
       $("#doFilterByTag").click(function(){
         
         tags = jQuery('.chzn-select').val().toString();
         console.log('tags = ' + tags);
         
         //str = ''; jQuery('.chzn-select [selected][disabled]').each(function(){str = str + (str ? ',' : '') + jQuery(this).val()}); console.log(str);
         tagsDisabled = ''; 
         jQuery('.chzn-select [selected][disabled]').each(
            function(){tagsDisabled = tagsDisabled + (tagsDisabled ? ',' : '') + jQuery(this).val()
         }); 
         
         tags = (tags ? (tags + ',') : '') + tagsDisabled;
         
         console.log('tagsDisabled = ' + tagsDisabled);
         console.log('tagsAll = ' + tags);
         //console.log('top.location.href = ' + decodeURIComponent(top.location.href));
         
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

         
         query_opened = false;
         param_string = '';
         for (p in params) {
           if (p != 'tags') {
            param_string = param_string + (param_string ? '&' : '?') + p + '=' + params[p];
           }
           query_opened = true;
         }
         
         //console.log(params);
         console.log('original param_string = ' + param_string);
         
         // 'onChange' => "top.location.href='http://getvoip.com/" . $_GET['q'] . "?provider=' + encodeURIComponent(document.getElementById('select_provider').options[document.getElementById('select_provider').selectedIndex].value) + '$url'"),
         if (tags) {
          if (query_opened) {
            param_string = param_string + '&tags=' + tags;
          }
          else {
            param_string = param_string + '?tags=' + tags;
          }
         }
         
         new_url = location.origin + location.pathname + encodeURIComponent(param_string);
         
         console.log(new_url);
         //console.log('current_url = ' + current_url);
         //top.location.href = new_url;
         
       });
       

    }
  };
  
}(jQuery));