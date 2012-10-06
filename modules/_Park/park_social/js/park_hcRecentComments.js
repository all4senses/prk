//(function ($) {

  jQuery(document).ready(function() {
  
 
 
 // Drupal.behaviors.park_hcRecentComments = {
 //   attach: function (context, settings) {
       
      var _hcwp = _hcwp || [];
      _hcwp.push({widget_id : 3235, widget : "Mixstream",filter:"last",limit:5, append:"#hypercomments_recent" });
      (function() {
      var hcc = document.createElement("script"); hcc.type = "text/javascript"; hcc.async = true;
      hcc.src = ("https:" == document.location.protocol ? "https" : "http")+"://widget.hypercomments.com/apps/js/hc.dev.js";
      var s = document.getElementsByTagName("script")[0]; s.parentNode.insertBefore(hcc, s.nextSibling);
      })();

//    }
//  };

  });

//}(jQuery));
