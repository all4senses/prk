(function ($) {

  Drupal.behaviors.park_sectionFilter = {
    attach: function (context, settings) {
       
      $("#select-tags.chzn-select").chosen();
       
      refineTagsExcludedStatus();
      
      
      
      
      query_opened = false;
      source_param_string = '';
      final_param_string = '';
      var params = {};
      
      current_query = location.search;
      //console.log('current_query = ' + current_query);
      
      if (current_query) {
          var parts = current_query.substring(1).split('&');

          for (var i = 0; i < parts.length; i++) {
              var nv = parts[i].split('=');
              if (!nv[0]) continue;
              params[nv[0]] = nv[1] || true;
          }
      }

      
      for (p in params) {
        // Take out 'tags' params from a query.
        if (p != 'tags-exclude') {
          source_param_string = source_param_string + (source_param_string ? '&' : '?') + p + '=' + params[p];
        }
        query_opened = true;
      }

      //console.log(params);
      //console.log('source query (without "tags-exclude" params) = ' + source_param_string);

       
      
      
      
      function doFilter() {
        
        var final_param_string = source_param_string;
        
        if (!jQuery("#select-tags.chzn-select").val()) {
          alert(Drupal.t('Set at least one tag to filter.'));
          return;
        }
        
        final_param_string = addParamToQuery(final_param_string, getTagsQueryPart());

        final_url = location.origin + location.pathname + final_param_string;
        
        //console.log('final url with selected tags-exclude (if selected) = ' + final_url);
        
        top.location.href = final_url;
      }
      
      
      $("#select-tags.chzn-select").change(function(){
        refineTagsExcludedStatus();
      });
      
      
      $("#doFilter").click(function(){
        doFilter();
      });
      
      
      function addParamToQuery(currentQuery, newParam) {
        if (newParam) {
          return currentQuery + (currentQuery ? '&' : '?') + newParam;
        }
        else {
          return currentQuery;
        }
      }
      
      
      
      function getTagsQueryPart() {
        
        tags = '';
        //tagsDisabled = ''; 
        
        if (jQuery("#select-tags.chzn-select").find(':not(:selected)[value!=""]')) {
          jQuery("#select-tags.chzn-select").find(':not(:selected)[value!=""]').each(function(){
            tags = tags + (tags ? ',' : '') + jQuery(this).val();
          })
        }
        //console.log(tags);
        /*
        if (jQuery('#select-tags.chzn-select').val()) {
          tags = jQuery('#select-tags.chzn-select').val().toString();
        }

        jQuery('#select-tags.chzn-select [selected][disabled]').each(
          function(){tagsDisabled = tagsDisabled + (tagsDisabled ? ',' : '') + jQuery(this).val()
        }); 

        tags = (tags ? (tags + (tagsDisabled ? ',' : '')) : '') + tagsDisabled;
        */
        console.log('current not selected tags = ' + tags);
        //console.log('among them -> tagsDisabled = ' + tagsDisabled);
        
        if (tags) {
          tagsQueryPart = 'tags-exclude=' + encodeURIComponent(tags);
          //console.log('tagsQueryPart = ' + tagsQueryPart);
          return tagsQueryPart;
        }
        
        //console.log('tagsQueryPart = -----');
        return false;
      }
      
      
      
      
      
      function refineTagsExcludedStatus() {
        if (getTagsQueryPart()) {
          $("#sectionIsFiltered").show();
        }
        else {
          $("#sectionIsFiltered").hide();
        }
      }
      
      
       

    }
  };
  
}(jQuery));