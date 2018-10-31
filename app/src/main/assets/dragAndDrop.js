$( function() {

    $( "#drag" ).draggable({ revert: "invalid" });

    $( "#drop" ).droppable({
         accept : ".unactivated",
         drop: function( event, ui ) {

        $( "#drag" ).offset({ top: 242, left: 413 });
        $( "#drag" ).removeClass("unactivated");
        $( "#drag" ).addClass("activated");
        $( ".bloc" ).removeClass( "show" );
        $( ".bloc_deux" ).removeClass( "hide" );
        $( ".bloc" ).addClass( "hide" );
        $( ".bloc_deux" ).addClass( "show" );
            /* special ilot*/
        $( ".blocs" ).removeClass( "show" );
        $( ".blocs_deux" ).removeClass( "hide" );
        $( ".blocs" ).addClass( "hide" );
        $( ".blocs_deux" ).addClass( "show" );

        $( ".button_sur_bloc" ).removeClass( "hide" );
        $( ".button_sur_bloc" ).addClass( "show" );
            /* fin special ilot*/
        $( ".background" ).addClass( "background-avec-batterie" )
        $( ".background" ).removeClass( "background" )
        $(".text-batterie").removeClass("hide")
        $(".text-batterie").addClass("show")
        $(".bloc-image-fleche").removeClass("show")
        $(".bloc-image-fleche").addClass("hide")
        var class_grad = $( "#drag" ).attr('class')
        console.log(class_grad)

         }
     })
    $( ".bloc-image-batterie" ).droppable({
       accept : ".activated",
       drop: function( event, ui ) {
            $( "#drag" ).offset({ top: 234, left: 136 });
            $( "#drag" ).removeClass("activated");
            $( "#drag" ).addClass("unactivated");
            $( ".bloc_deux" ).removeClass( "show" );
            $( ".bloc" ).removeClass( "hide" );
            $( ".bloc_deux" ).addClass( "hide" );
            $( ".bloc" ).addClass( "show" );
                /* special ilot*/
            $( ".blocs_deux" ).removeClass( "show" );
            $( ".blocs" ).removeClass( "hide" );
            $( ".blocs_deux" ).addClass( "hide" );
            $( ".blocs" ).addClass( "show" );

                /*fin ilot */
            $( ".background-avec-batterie" ).addClass( "background" )
            $( ".background-avec-batterie" ).removeClass( "background-avec-batterie" )
            $(".text-batterie").removeClass("show")
            $(".text-batterie").addClass("hide")
                    $( ".button_sur_bloc" ).addClass( "hide" );
                    $( ".button_sur_bloc" ).removeClass( "show" );



            $(".bloc-image-fleche").removeClass("hide")
            $(".bloc-image-fleche").addClass("show")
            class_grad = $( "#drag" ).attr('class')
            console.log(class_grad)

       }
    })

});