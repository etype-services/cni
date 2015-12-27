(function ($) {
    Drupal.behaviors.usermenu = {
        attach: function (context) {
            $('#block-system-user-menu ul li').each(function(index) {
                console.log( index + ": " + $( this ).text() );
            })
        }
    };
})(jQuery);