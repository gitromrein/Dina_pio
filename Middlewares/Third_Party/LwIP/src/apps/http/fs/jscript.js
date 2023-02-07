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
    _ajaxGetCxWLiveData();
}

document.getElementById("Canframes").onmouseover = function() {
    document.getElementById("settings-btn").className = "btn-right-hover"
    document.getElementById("Settings").style.backgroundColor = "#60c2e6";
};

document.getElementById("Canframes").onmouseout = function() {
    document.getElementById("settings-btn").className = "btn";
    document.getElementById("Settings").style.backgroundColor = "#309dc6";
};

document.getElementById("Settings").onmouseover = function() {
    document.getElementById("can-frames-btn").className = "btn-left-right-hover"
    document.getElementById("Canframes").style.background = "linear-gradient(0.25turn, #FFFF00, #60c2e6)";
    document.getElementById("nav-right-border").className = "btns-border-right-active"
    document.getElementById("dummy-right").style.backgroundColor = "#60c2e6";
};

document.getElementById("Settings").onmouseout = function() {
    document.getElementById("can-frames-btn").className = "btn-right";
    document.getElementById("Canframes").style.backgroundColor = "#309dc6";
    document.getElementById("nav-right-border").className = "btns-border-right"
    document.getElementById("dummy-right").style.backgroundColor = "#309dc6";
};

function _ajaxGetCxWLiveData() 
{
    if (window.XMLHttpRequest) 
    {
        var httpRequest = new XMLHttpRequest();
    } 
    else if (window.ActiveXObject) 
    {
        try 
        {
            var httpRequest = new ActiveXObject("Msxml2.XMLHTTP");
        } 
        catch (otherMS) 
        {
            try 
            {
                var httpRequest = new ActiveXObject("Microsoft.XMLHTTP");
            } 
            catch (failed) 
            {
                var httpRequest = null;
            }
        }
    }

    httpRequest.onreadystatechange = function () 
    {   
        if (this.readyState == 4) 
        {
            if (this.status == 200) 
            {
                var json = JSON.parse(this.responseText);
                console.log(json);
                document.getElementById("addr_lju").innerHTML   = json[0]; //json[0][1];
                document.getElementById("addr_dina").innerHTML  = json[1]; //json[1][1];
                document.getElementById("msg_id").innerHTML     = json[2]; //json[2][1];
                document.getElementById("msg_cnt").innerHTML    = json[3]; //json[3][1];
                document.getElementById("status").innerHTML     = json[4];
                document.getElementById("err_status").innerHTML = json[5];
                document.getElementById("err_nr").innerHTML     = json[6];

                document.getElementById("enco_1_pos").innerHTML       = json[7];
                document.getElementById("enco_1_speed").innerHTML     = json[8];
                document.getElementById("enco_1_status_1").innerHTML  = json[9];
                document.getElementById("enco_1_status_2").innerHTML  = json[10];
                document.getElementById("enco_1_status_3").innerHTML  = json[11];
                document.getElementById("enco_1_status_4").innerHTML  = json[12];
                document.getElementById("enco_1_status_5").innerHTML  = json[13];

                document.getElementById("enco_2_pos").innerHTML       = json[14];
                document.getElementById("enco_2_speed").innerHTML     = json[15];
                document.getElementById("enco_2_status_1").innerHTML  = json[16];
                document.getElementById("enco_2_status_2").innerHTML  = json[17];
                document.getElementById("enco_2_status_3").innerHTML  = json[18];
                document.getElementById("enco_2_status_4").innerHTML  = json[19];
                document.getElementById("enco_2_status_5").innerHTML  = json[20];

                document.getElementById("enco_3_pos").innerHTML       = json[21];
                document.getElementById("enco_3_speed").innerHTML     = json[22];
                document.getElementById("enco_3_status_1").innerHTML  = json[23];
                document.getElementById("enco_3_status_2").innerHTML  = json[24];
                document.getElementById("enco_3_status_3").innerHTML  = json[25];
                document.getElementById("enco_3_status_4").innerHTML  = json[26];
                document.getElementById("enco_3_status_5").innerHTML  = json[27];

                document.getElementById("enco_4_pos").innerHTML       = json[28];
                document.getElementById("enco_4_speed").innerHTML     = json[29];
                document.getElementById("enco_4_status_1").innerHTML  = json[30];
                document.getElementById("enco_4_status_2").innerHTML  = json[31];
                document.getElementById("enco_4_status_3").innerHTML  = json[32];
                document.getElementById("enco_4_status_4").innerHTML  = json[33];
                document.getElementById("enco_4_status_5").innerHTML  = json[34];

                document.getElementById("enco_5_pos").innerHTML       = json[35];
                document.getElementById("enco_5_speed").innerHTML     = json[36];
                document.getElementById("enco_5_status_1").innerHTML  = json[37];
                document.getElementById("enco_5_status_2").innerHTML  = json[38];
                document.getElementById("enco_5_status_3").innerHTML  = json[39];
                document.getElementById("enco_5_status_4").innerHTML  = json[40];
                document.getElementById("enco_5_status_5").innerHTML  = json[41];

                document.getElementById("enco_6_pos").innerHTML       = json[42];
                document.getElementById("enco_6_speed").innerHTML     = json[43];
                document.getElementById("enco_6_status_1").innerHTML  = json[44];
                document.getElementById("enco_6_status_2").innerHTML  = json[45];
                document.getElementById("enco_6_status_3").innerHTML  = json[46];
                document.getElementById("enco_6_status_4").innerHTML  = json[47];
                document.getElementById("enco_6_status_5").innerHTML  = json[48];
            }
        }
    }

    httpRequest.open("GET", "getCxWdata", true);
    httpRequest.send();
    setTimeout(_ajaxGetCxWLiveData, 300);
}


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