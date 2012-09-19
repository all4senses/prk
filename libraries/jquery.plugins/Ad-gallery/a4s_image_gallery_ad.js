/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */



jQuery(document).ready(function($) {



        $(function() {
            /*
            $('#gallery_0 img.image1').data('ad-desc', 'Whoa! This description is set through elm.data("ad-desc") instead of using the longdesc attribute.<br>And it contains <strong>H</strong>ow <strong>T</strong>o <strong>M</strong>eet <strong>L</strong>adies... <em>What?</em> That aint what HTML stands for? Man...');
            $('#gallery_0 img.image1').data('ad-title', 'Title through $.data');
            $('#gallery_0 img.image4').data('ad-desc', 'This image is wider than the wrapper, so it has been scaled down');
            $('#gallery_0 img.image5').data('ad-desc', 'This image is higher than the wrapper, so it has been scaled down');
            */
         
            var g = new Array(); 
            $('.ad-gallery').each(function(i) {
                            var current = $(this).attr('id');
                            // for some browsers (firefox, chrome) there should be set sizes explicitly 
                            // for '<div class="ad-image-wrapper" style="width:600px; height:400px;"></div>' in template
			    galleries = $(this).adGallery(
                                                            {
                                                                callbacks:
                                                                        {
                                                                            afterImageVisible: function()
                                                                                                {
                                                                                                    //console.log(this.current_image[0].baseURI);
                                                                                                    //console.log(this.current_image[0].attributes);
                                                                                                    //console.log(this.current_image[0].childNodes[0].src);
                                                                                                    $('#'+current+ ' .full').attr('href', this.current_image[0].childNodes[0].src);
                                                                                                    //console.log(this);
                                                                                                    //console.log($(this).parent());
                                                                                                    //console.log($(this).parent().parent().attr('class'));
                                                                                                    
                                                                                                }
                                                                        }
                                                            }
                                                        ); 
			    // or set it here via paremeters
			    //galleries = $(this).adGallery({width:600, height:400}); 
			    
                            g[i] = galleries;
                    
                            //$('#' + $(this).parent().attr('id') + ' #switch-effect').change( //$('#switch-effect').change(
                            $('#' + $(this).parent().attr('id') + ' .switch-effect').change( //$('#switch-effect').change(
                              function() {
                                var t = g[i];
                                t[0].settings.effect = $(this).val(); //galleries[i].settings.effect = $(this).val();
                                return false;
                              }
                            );

                            //$('#' + $(this).parent().attr('id') + ' #toggle-slideshow').click(
                            $('#' + $(this).parent().attr('id') + ' .toggle-slideshow').click(
                              function() {
                                var t = g[i];
                                t[0].slideshow.toggle(); //galleries[i].slideshow.toggle();
                                return false;
                              }
                            );

                            //$('#' + $(this).parent().attr('id') + ' #toggle-description').click(
                            $('#' + $(this).parent().attr('id') + ' .toggle-description').click(
                              function() {
                                var t = g[i];
                                if(!t[0].settings.description_wrapper) { //galleries[i]
                                  t[0].settings.description_wrapper = $('#' + $(this).parent().parent().attr('id') + ' #descriptions'); //galleries[i].settings.description_wrapper = $('#descriptions');
                                } else {
                                  t[0].settings.description_wrapper = false;
                                }
                                return false;
                              }
                            );

                
                    }); // end of  $('.ad-gallery').each(function() {

       
                
                
                
        }); // end of $(function() {

}); // end of jQuery(document).ready(function($) {
