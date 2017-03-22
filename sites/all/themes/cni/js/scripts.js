(function ($) {
    Drupal.behaviors.superfish = {
        attach: function (context) {

            function mobile_menu(w) {
                var wrapper = $('#mobile-menu-wrapper');
                if (w > 767) {
                    if ( wrapper.length > 0 ) {
                        wrapper.remove();
                        $('#search-block-form').show();
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
                            alert('clicked');
                            if(searchForm.is(':visible')) {
                                searchForm.hide();
                            } else {
                                searchForm.show();
                                $('#edit-search-block-form--2').focus();
                            }
                        });
                    }
                }
            };

            var w = $(window).width();
            mobile_menu(w);
            var obj = $('#superfish li.sf-depth-1:first-child a');
            obj.click(function (e) {
                var text = $(this).text();
                e.preventDefault();
                $('#block-superfish-1 ul li.sf-depth-1:not(:first-child)').toggle();
                if (text == 'Show Menu') {
                    $(this).text('Hide Menu');
                } else {
                    $(this).text('Show Menu');
                }
            });

            $(window).resize(function () {
                var w = $(window).width();
                mobile_menu(w);
            });
        }
    };
})(jQuery);
