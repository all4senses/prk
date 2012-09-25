(function ($) {

  Drupal.behaviors.park_filterByTags = {
    attach: function (context, settings) {
       
      $(".chzn-select").chosen();
       
       
       
      query_opened = false;
      source_param_string = '';
      var params = {};
      
      current_url = location.search;
      console.log('current_url = ' + current_url);
      
      if (current_url) {
          var parts = current_url.substring(1).split('&');

          for (var i = 0; i < parts.length; i++) {
              var nv = parts[i].split('=');
              if (!nv[0]) continue;
              params[nv[0]] = nv[1] || true;
          }
      }

      
      for (p in params) {
        if (p != 'tags') {
        source_param_string = source_param_string + (source_param_string ? '&' : '?') + p + '=' + params[p];
        }
        query_opened = true;
      }

      //console.log(params);
      console.log('source param_string = ' + source_param_string);

       
       
      $("#doFilterByTag").click(function(){
        
        param_string = source_param_string;
        tags = '';
        tagsDisabled = ''; 
        
        if (jQuery('.chzn-select').val()) {
        tags = jQuery('.chzn-select').val().toString();
        }
        console.log('tags = ' + tags);

        //str = ''; jQuery('.chzn-select [selected][disabled]').each(function(){str = str + (str ? ',' : '') + jQuery(this).val()}); console.log(str);
        
        jQuery('.chzn-select [selected][disabled]').each(
          function(){tagsDisabled = tagsDisabled + (tagsDisabled ? ',' : '') + jQuery(this).val()
        }); 

        tags = (tags ? (tags + (tagsDisabled ? ',' : '')) : '') + tagsDisabled;

        console.log('tagsDisabled = ' + tagsDisabled);
        console.log('tagsAll = ' + tags);
        //console.log('top.location.href = ' + decodeURIComponent(top.location.href));


        // 'onChange' => "top.location.href='http://getvoip.com/" . $_GET['q'] . "?provider=' + encodeURIComponent(document.getElementById('select_provider').options[document.getElementById('select_provider').selectedIndex].value) + '$url'"),
        tags = encodeURIComponent(tags);
        if (tags) {
          if (query_opened) {
            param_string = param_string + '&tags=' + tags;
          }
          else {
            param_string = param_string + '?tags=' + tags;
          }
        }

        new_url = location.origin + location.pathname + param_string;

        console.log(new_url);
        
        ////top.location.href = new_url;

      });
       

    }
  };
  
}(jQuery));