$('#container-page-deux').smoothState({
    onStart: {
        duration: 1000,
        render: function($container) {
            $container.addClass('loading');
        }
    },
    onAfter: function ($container, $newContent) {
        $container.removeClass('loading');
    },
    prefetch: true;
});
$('#container-page-un').smoothState({
    onStart: {
        duration: 1000,
        render: function($container) {
            $container.addClass('loading');
        }
    },
    onAfter: function ($container, $newContent) {
        $container.removeClass('loading');
    },
    prefetch: true;
});