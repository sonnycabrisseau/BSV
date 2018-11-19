//Animation de transitions des vignettes
/*function click_vignette(numero, buttons)
{

    // On récupère la vignette selectionné
    var vignette = buttons[numero];
    // On crée un tableau avec toutes les valeurs de transform-orign
    var s_origin = ["0 0", "233.5px 0", "0 233.5px", "233.5px 233.5px"];
    //On change le transform-origin en fonction de la vignette
    vignette.style.transformOrigin = s_origin[numero];
    vignette.style.zIndex = 2;
    // L'animation
    anime({
        targets: vignette,
        // Valeur du gros carré divisé par la vignette
        scale: 2.11991435,
        duration: 1000,
        easing: 'linear',
        loop: false
    })
}
*/
//Réécriture du lien
/*function link(href)
{
    window.location = href;
}*/

//Animation d'apparition du texte
function text_fade()
{
    var basicTimeline = anime.timeline();

    basicTimeline
    .add({
        targets: '.vignette',
        opacity: 0,
        translateY: 20,
        easing: 'easeOutExpo',
        duration: 800
    })
    /*.add({
        targets: '#container-page-un',
        opacity: 1,
        easing: 'easeInSine'
    })*/
    .add({
        targets: '.vignette',
        translateY: 0,
        opacity: 1,
        easing: 'easeOutExpo',
        elasticity: 100
    })
    .add({
        targets: 'p, span',
        translateY: 0,
        opacity: 1,
        easing: 'easeOutExpo'
    })
}

window.onload = text_fade();

// On sélectionne toutes les vignettes
var buttons = document.querySelectorAll(".vignette");

/* Pour chaque vignette, on crée un événement au clic qui :

1) Empêche le lien de fonctionner
2) Récupère le numéro de la vignette
3) Déclenche la fonction click_vignette
4) Active le lien après l'animation*/
/*for(var i = 0; i < buttons.length; i++) {
    var button = buttons[i];
    button.addEventListener("click", function(event){
        event.preventDefault();
        var href = this.href;
        var numero = this.getAttribute("data-order") - 1;
        click_vignette(numero, buttons);
        setTimeout(link, 500, href);
    })
}*/
