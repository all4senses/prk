(function ($) {

  Drupal.behaviors.park_filterByTags = {
    attach: function (context, settings) {
       
      $(".chzn-select").chosen();
       
       
       
      query_opened = false;
      source_param_string = '';
      final_param_string = '';
      var params = {};
      
      // console.log('top.location.href = ' + decodeURIComponent(top.location.href));
      // 'onChange' => "top.location.href='http://getvoip.com/" . $_GET['q'] . "?provider=' + encodeURIComponent(document.getElementById('select_provider').options[document.getElementById('select_provider').selectedIndex].value) + '$url'"),

      current_query = location.search;
      console.log('current_query = ' + current_query);
      
      if (current_query) {
          var parts = current_query.substring(1).split('&');

          for (var i = 0; i < parts.length; i++) {
              var nv = parts[i].split('=');
              if (!nv[0]) continue;
              params[nv[0]] = nv[1] || true;
          }
      }

      
      for (p in params) {
        // Take out 'tags' and 'author' params from a query.
        if (p != 'tags' && p != 'author') {
          source_param_string = source_param_string + (source_param_string ? '&' : '?') + p + '=' + params[p];
        }
        query_opened = true;
      }

      //console.log(params);
      console.log('source param_string = ' + source_param_string);

       
      
      
      
      
      
      
      
      $("#doFilterByTag").click(function(){
        
        tagsQueryPart = getTagsQueryPart();
        authorQueryPart = getAuthorQueryPart();
        
        console.log('tagsQueryPart = ' + tagsQueryPart);
        
        if (tagsQueryPart) {
          final_param_string = final_param_string + (final_param_string ? '&' : '?') + tagsQueryPart;
        }
        if (authorQueryPart) {
          final_param_string = final_param_string + (final_param_string ? '&' : '?') + authorQueryPart;
        }
        
        final_url = location.origin + location.pathname + final_param_string;

        console.log('final url with selected tags' + final_url);
        
        ////top.location.href = new_url;

      });
      
      
      
      
      
      function getAuthorQueryPart() {
        authorQueryPart = 'author=aaaaaaa';
        return authorQueryPart;
      }



      
      function getTagsQueryPart() {
        
        param_string = source_param_string;
        tags = '';
        tagsDisabled = ''; 
        
        if (jQuery('.chzn-select').val()) {
          tags = jQuery('.chzn-select').val().toString();
        }
        console.log('tags = ' + tags);

        jQuery('.chzn-select [selected][disabled]').each(
          function(){tagsDisabled = tagsDisabled + (tagsDisabled ? ',' : '') + jQuery(this).val()
        }); 

        tags = (tags ? (tags + (tagsDisabled ? ',' : '')) : '') + tagsDisabled;

        console.log('tagsDisabled = ' + tagsDisabled);
        console.log('tagsAll = ' + tags);
        
        if (tags) {
          return 'tags=' + encodeURIComponent(tags);
        }
        
        return false;
      }
      
      
       

    }
  };
  
}(jQuery));