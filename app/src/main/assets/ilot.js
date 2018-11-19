function nuages()
{
	console.log("tessss");
	anime({
	  targets: ".nuage-foreground", 
	  translateX: [
	  	{ value: 0, duration: 800 },
	    { value: -140, duration: 5000 }
	  ],
	  easing : 'linear'
	});
	anime({
	  targets: ".nuage-background",
	  translateX: [
	  	{ value: 0, duration: 800 },
	    { value: -40, duration: 5000 }
	  ],
	  easing : 'linear'
	});
}

window.onload = nuages();