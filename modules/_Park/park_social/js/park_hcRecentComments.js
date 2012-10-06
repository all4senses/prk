//(function ($) {

 // Drupal.behaviors.park_hcRecentComments = {
 //   attach: function (context, settings) {

function hcLaunch() {
      var _hcwp = _hcwp || [];
      _hcwp.push({widget_id : 3235, widget : "Mixstream",filter:"last",limit:5, append:"#hypercomments_recent" });
      (function() {
      var hcc = document.createElement("script"); hcc.type = "text/javascript"; hcc.async = true;
      hcc.src = ("https:" == document.location.protocol ? "https" : "http")+"://widget.hypercomments.com/apps/js/hc.dev.js";
      var s = document.getElementsByTagName("script")[0]; s.parentNode.insertBefore(hcc, s.nextSibling);
      })();
}


if (window.addEventListener)
  window.addEventListener("load", hcLaunch, false);
else if (window.attachEvent)
  window.attachEvent("onload", hcLaunch);
else 
  window.onload = hcLaunch;


//    }
//  };

//}(jQuery));
