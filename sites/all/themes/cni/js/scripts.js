(function ($) {
    Drupal.behaviors.superfish = {
        attach: function (context) {



            var w = $(window).width();
            if (w > 767) {
                $('#mobile-menu-wrapper').remove();
            } else {
                $('.region-user-menu').prepend('<div id="mobile-menu-wrapper"><div id="mobile-menu-control"></div><ul id="mobile-menu" class="menu"></ul></div>');
                $('#superfish-1 li').clone().appendTo($('#mobile-menu'));
                $('#block-system-user-menu ul.menu li').clone().appendTo($('#mobile-menu'));
                $('#mobile-menu-control').click(function(){$('#mobile-menu').toggle()});
            }

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
                if (w > 767) {

                } else {

                }
            });
        }
    };
})(jQuery);
