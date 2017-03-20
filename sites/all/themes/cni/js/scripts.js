(function ($) {
    Drupal.behaviors.superfish = {
        attach: function (context) {

            var w = $(window).width();
            if (w > 767) {
            } else {
                // $('#block-system-user-menu ul.menu').prepend($('#superfish-1 li'));
                $('#superfish-1 li').each(function(i){
                    $(this).addClass('added').prependTo('#block-system-user-menu ul.menu');
                });
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
                    $('#block-system-user-menu ul.menu li.added').remove();
                    $('#superfish-1').show();
                    $('#superfish-1 li.sf-depth-1:not(:first-child)').css("display", "list-item").show();
                } else {
                    $('#superfish-1 li.sf-depth-1:first-child a').text('Show Menu');
                    $('#superfish-1 li.sf-depth-1:not(:first-child)').hide();
                    $('#superfish-1 li.sf-depth-1 ul').hide();
                }
            });
        }
    };
})(jQuery);
