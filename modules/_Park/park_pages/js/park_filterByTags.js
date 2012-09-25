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
      console.log('source query (without "tags" and "author" params) = ' + source_param_string);

       
      
      
      
      function doFilter() {
        
        var final_param_string = source_param_string;
        
        final_param_string = addParamToQuery(final_param_string, getTagsQueryPart());
        final_param_string = addParamToQuery(final_param_string, getAuthorQueryPart());

        final_url = location.origin + location.pathname + final_param_string;
        
        console.log('final url with selected tags (if selected) and author (if selected) = ' + final_url);
        
        ////top.location.href = new_url;
      }
      
      
      
      $("#doFilter").click(function(){
        doFilter();
      });
      
      
      $("#authors").change(function(){
        doFilter();
      });
      
      
      $("#goToAuthorPage").click(function(){
        var author = $("#authors").val();
        console.log('author = ' + author);
        if (author) {
          //top.location.href = location.origin;
        }
      });
      


      
      function addParamToQuery(currentQuery, newParam) {
        if (newParam) {
          return currentQuery + (currentQuery ? '&' : '?') + newParam;
        }
        else {
          return currentQuery;
        }
      }
      
      
      
      
      function getAuthorQueryPart() {
        
        authorQueryPart = '';
        var author = $("#authors").val();
        
        if (author) {
          authorQueryPart = 'author=' + author;
        }
        console.log('authorQueryPart = ' + authorQueryPart);
        return authorQueryPart;
      }



      
      function getTagsQueryPart() {
        
        param_string = source_param_string;
        tags = '';
        tagsDisabled = ''; 
        
        if (jQuery('.chzn-select').val()) {
          tags = jQuery('.chzn-select').val().toString();
        }

        jQuery('.chzn-select [selected][disabled]').each(
          function(){tagsDisabled = tagsDisabled + (tagsDisabled ? ',' : '') + jQuery(this).val()
        }); 

        tags = (tags ? (tags + (tagsDisabled ? ',' : '')) : '') + tagsDisabled;

        console.log('current selected tags (with disabled) = ' + tags);
        console.log('among them -> tagsDisabled = ' + tagsDisabled);
        
        if (tags) {
          tagsQueryPart = 'tags=' + encodeURIComponent(tags);
          console.log('tagsQueryPart = ' + tagsQueryPart);
          return tagsQueryPart;
        }
        
        console.log('tagsQueryPart = -----');
        return false;
      }
      
      
       

    }
  };
  
}(jQuery));