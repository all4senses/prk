/*!
 * Socialite v2.0 - Mail.ru Extension
 * http://socialitejs.com
 * Copyright (c) 2011 David Bushell
 * Dual-licensed under the BSD or MIT licenses: http://socialitejs.com/license.txt
 */
(function(window, document, Socialite, undefined)
{
    // External documentation URLs

    // add required default settings
    /*
    Socialite.setup({
        'mailru': {
            lang: 'ru'
        }
    });
    */
   
    /**
     * One network can cater for multiple widgets
     * Check the extensions repository to make sure it doesn't already exist
     * The script object is optional for extentions that require simple images or iframes
     */
    Socialite.network('mailru', {
        script: {
            src     : '//cdn.connect.mail.ru/js/loader.js',
            charset : 'utf-8'
        }
        
    });

    /**
     * Add a unique widget to the network
     * Socialite will activate elements with a class name of `network_name-widget_name`, e.g. `twitter-share`
     */
    Socialite.widget('mailru', 'like', {
        reappend: null,
        init: function(instance)
        {
            var el = document.createElement('a');
            el.className = 'mailru-like';
            Socialite.copyDataAttributes(instance.el, el);
            el.setAttribute('href', instance.el.getAttribute('data-href'));
            instance.el.appendChild(el);
        },
        activate: function(instance)
        {
            var w = instance.widget,
                n = w.network.name;
            if (Socialite.networkReady(n)) {
                if (w.reappend) {
                    clearTimeout(w.reappend);
                }
                w.reappend = setTimeout(function() {
                    Socialite.reloadNetwork(n);
                }, 50);
            }
        }
    });

})(window, window.document, window.Socialite);
