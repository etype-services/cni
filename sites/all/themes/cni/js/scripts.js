(function ($) {
    function mobile_menu(w) {
        var wrapper = $('#mobile-menu-wrapper');
        if (w > 767) {
            if ( wrapper.length > 0 ) {
                wrapper.remove();
            }
        } else {
            if ( wrapper.length === 0 ) {
                $('.region-user-menu').prepend('<div id="mobile-menu-wrapper"><div id="mobile-menu-control"></div><ul id="mobile-menu" class="menu"></ul></div>');
                var search = $('#search-control');
                var searchForm = $('#search-block-form');
                if ( search.length === 0 ) {
                    $('#block-search-form .content').append('<div id="search-control"></div>');
                }
                $('#superfish-1 li').clone().appendTo($('#mobile-menu'));
                $('#block-system-user-menu ul.menu li').clone().appendTo($('#mobile-menu'));
                $('#mobile-menu li ul').remove();
                $('#mobile-menu-control').click(function(){$('#mobile-menu').toggle()});
                $(search).click(function(){
                    searchForm.toggle();
                    if(searchForm.is(':visible')) {
                        $('#edit-search-block-form--2').focus();
                    }
                });
            }
        }
    };

    var w = $(window).width();
    mobile_menu(w);

    $(window).resize(function () {
        var w = $(window).width();
        mobile_menu(w);
    });
})(jQuery);
