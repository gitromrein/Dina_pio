if (navigator.userAgent.indexOf("Firefox") != -1)  //If the browser is Firefox
{ 
    if (document.addEventListener)     //for Firefox 
    {
        document.addEventListener("DOMContentLoaded", init, false)
    }
} 
else 
{
    // For other browsers
    window.onload = init();
}

function init() 
{

}

document.getElementById("Canframes").onmouseover = function() {
    document.getElementById("Index").style.backgroundColor = "#60c2e6";
    document.getElementById("index-btn").className = "btn-left-hover"
};

document.getElementById("Canframes").onmouseout = function() {
    document.getElementById("Index").style.backgroundColor = "#309dc6";
    document.getElementById("index-btn").className = "btn";
};

document.getElementById("Index").onmouseover = function() {
    document.getElementById("can-frames-btn").className = "btn-left-right-hover"
    document.getElementById("Canframes").style.background = "linear-gradient(0.25turn, #60c2e6, #FFFF00)";
    document.getElementById("nav-left-border").className = "btns-border-left-active"
    document.getElementById("dummy-left").style.backgroundColor = "#60c2e6";
};

document.getElementById("Index").onmouseout = function() {
    document.getElementById("can-frames-btn").className = "btn-left";
    document.getElementById("Canframes").style.backgroundColor = "#309dc6";
    document.getElementById("nav-left-border").className = "btns-border-left"
    document.getElementById("dummy-left").style.backgroundColor = "#309dc6";
};

/* OTHER THINGS */

/* Prevent dialog from closing if escape button is pressed */
window.onkeydown = function (event) {
    if (event.keyCode === 27) {
        event.preventDefault();
    }
}

/*JavaScript keep scroll position after refresh */
document.addEventListener("DOMContentLoaded", function(event) 
{ 
    var scrollpos = localStorage.getItem('scrollpos');
    if (scrollpos) window.scrollTo(0, scrollpos);
});

window.onbeforeunload = function(e) 
{
    localStorage.setItem('scrollpos', window.scrollY);
}

/* Sticky Navigation Bar */
window.onscroll = function() 
{
    console.log(window.scrollY);
    myFunction();
}

var navbar = document.getElementById("navibar");
var sticky = navbar.offsetTop;

console.log(navbar.offsetTop);

function myFunction() 
{
    if (window.scrollY >= sticky) 
    {
        navbar.classList.add("sticky");
    } 
    else 
    {
        navbar.classList.remove("sticky");
    }
}