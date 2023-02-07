var can1Timout;
var can2Timout;


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
    _ajaxGetCAN1LiveData();
    _ajaxGetCAN2LiveData();

    _ajaxGetFBVBytes();
}

document.getElementById("Settings").onmouseover = function() {
    document.getElementById("nav-right-border").className = "btns-border-right-active"
    document.getElementById("dummy-right").style.backgroundColor = "#60c2e6";
};

document.getElementById("Settings").onmouseout = function() {
    document.getElementById("nav-right-border").className = "btns-border-right"
    document.getElementById("dummy-right").style.backgroundColor = "#309dc6";
};

document.getElementById("Index").onmouseover = function() {
    document.getElementById("nav-left-border").className = "btns-border-left-active"
    document.getElementById("dummy-left").style.backgroundColor = "#60c2e6";
};

document.getElementById("Index").onmouseout = function() {
    document.getElementById("nav-left-border").className = "btns-border-left"
    document.getElementById("dummy-left").style.backgroundColor = "#309dc6";
};


function _ajaxGetCAN1LiveData() 
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
                document.getElementById("dsgn_1_byte_0").innerHTML    = json[0];
                document.getElementById("dsgn_1_byte_1").innerHTML    = json[1];
                document.getElementById("dsgn_1_byte_2").innerHTML    = json[2];
                document.getElementById("dsgn_1_byte_3").innerHTML    = json[3];
                document.getElementById("dsgn_1_byte_4").innerHTML    = json[4];
                document.getElementById("dsgn_1_byte_5").innerHTML    = json[5];
                document.getElementById("dsgn_1_byte_6").innerHTML    = json[6];
                document.getElementById("dsgn_1_byte_7").innerHTML    = json[7];

                document.getElementById("erro_1_byte_0").innerHTML    = json[8];
                document.getElementById("erro_1_byte_1").innerHTML    = json[9];
                document.getElementById("erro_1_byte_2").innerHTML    = json[10];
                document.getElementById("erro_1_byte_3").innerHTML    = json[11];
                document.getElementById("erro_1_byte_4").innerHTML    = json[12];
                document.getElementById("erro_1_byte_5").innerHTML    = json[13];
                document.getElementById("erro_1_byte_6").innerHTML    = json[14];
                document.getElementById("erro_1_byte_7").innerHTML    = json[15];

                document.getElementById("encoder_11_byte_0").innerHTML    = json[16];
                document.getElementById("encoder_11_byte_1").innerHTML    = json[17];
                document.getElementById("encoder_11_byte_2").innerHTML    = json[18];
                document.getElementById("encoder_11_byte_3").innerHTML    = json[19];
                document.getElementById("encoder_11_byte_4").innerHTML    = json[20];
                document.getElementById("encoder_11_byte_5").innerHTML    = json[21];
                document.getElementById("encoder_11_byte_6").innerHTML    = json[22];
                document.getElementById("encoder_11_byte_7").innerHTML    = json[23];

                document.getElementById("encoder_12_byte_0").innerHTML    = json[24];
                document.getElementById("encoder_12_byte_1").innerHTML    = json[25];
                document.getElementById("encoder_12_byte_2").innerHTML    = json[26];
                document.getElementById("encoder_12_byte_3").innerHTML    = json[27];
                document.getElementById("encoder_12_byte_4").innerHTML    = json[28];
                document.getElementById("encoder_12_byte_5").innerHTML    = json[29];
                document.getElementById("encoder_12_byte_6").innerHTML    = json[30];
                document.getElementById("encoder_12_byte_7").innerHTML    = json[31];

                document.getElementById("encoder_13_byte_0").innerHTML    = json[32];
                document.getElementById("encoder_13_byte_1").innerHTML    = json[33];
                document.getElementById("encoder_13_byte_2").innerHTML    = json[34];
                document.getElementById("encoder_13_byte_3").innerHTML    = json[35];
                document.getElementById("encoder_13_byte_4").innerHTML    = json[36];
                document.getElementById("encoder_13_byte_5").innerHTML    = json[37];
                document.getElementById("encoder_13_byte_6").innerHTML    = json[38];
                document.getElementById("encoder_13_byte_7").innerHTML    = json[39];

                document.getElementById("encoder_14_byte_0").innerHTML    = json[40];
                document.getElementById("encoder_14_byte_1").innerHTML    = json[41];
                document.getElementById("encoder_14_byte_2").innerHTML    = json[42];
                document.getElementById("encoder_14_byte_3").innerHTML    = json[43];
                document.getElementById("encoder_14_byte_4").innerHTML    = json[44];
                document.getElementById("encoder_14_byte_5").innerHTML    = json[45];
                document.getElementById("encoder_14_byte_6").innerHTML    = json[46];
                document.getElementById("encoder_14_byte_7").innerHTML    = json[47];

                document.getElementById("encoder_15_byte_0").innerHTML    = json[48];
                document.getElementById("encoder_15_byte_1").innerHTML    = json[49];
                document.getElementById("encoder_15_byte_2").innerHTML    = json[50];
                document.getElementById("encoder_15_byte_3").innerHTML    = json[51];
                document.getElementById("encoder_15_byte_4").innerHTML    = json[52];
                document.getElementById("encoder_15_byte_5").innerHTML    = json[53];
                document.getElementById("encoder_15_byte_6").innerHTML    = json[54];
                document.getElementById("encoder_15_byte_7").innerHTML    = json[55];

                document.getElementById("encoder_16_byte_0").innerHTML    = json[56];
                document.getElementById("encoder_16_byte_1").innerHTML    = json[57];
                document.getElementById("encoder_16_byte_2").innerHTML    = json[58];
                document.getElementById("encoder_16_byte_3").innerHTML    = json[59];
                document.getElementById("encoder_16_byte_4").innerHTML    = json[60];
                document.getElementById("encoder_16_byte_5").innerHTML    = json[61];
                document.getElementById("encoder_16_byte_6").innerHTML    = json[62];
                document.getElementById("encoder_16_byte_7").innerHTML    = json[63];

                document.getElementById("encoder_11_pos").innerHTML       = json[64];
                document.getElementById("encoder_11_speed").innerHTML     = json[65];
                document.getElementById("encoder_11_status_1").innerHTML  = json[66];
                document.getElementById("encoder_11_status_2").innerHTML  = json[67];

                document.getElementById("encoder_12_pos").innerHTML       = json[68];
                document.getElementById("encoder_12_speed").innerHTML     = json[69];
                document.getElementById("encoder_12_status_1").innerHTML  = json[70];
                document.getElementById("encoder_12_status_2").innerHTML  = json[71];

                document.getElementById("encoder_13_pos").innerHTML       = json[72];
                document.getElementById("encoder_13_speed").innerHTML     = json[73];
                document.getElementById("encoder_13_status_1").innerHTML  = json[74];
                document.getElementById("encoder_13_status_2").innerHTML  = json[75];

                document.getElementById("encoder_14_pos").innerHTML       = json[76];
                document.getElementById("encoder_14_speed").innerHTML     = json[77];
                document.getElementById("encoder_14_status_1").innerHTML  = json[78];
                document.getElementById("encoder_14_status_2").innerHTML  = json[79];

                document.getElementById("encoder_15_pos").innerHTML       = json[80];
                document.getElementById("encoder_15_speed").innerHTML     = json[81];
                document.getElementById("encoder_15_status_1").innerHTML  = json[82];
                document.getElementById("encoder_15_status_2").innerHTML  = json[83];

                document.getElementById("encoder_16_pos").innerHTML       = json[84];
                document.getElementById("encoder_16_speed").innerHTML     = json[85];
                document.getElementById("encoder_16_status_1").innerHTML  = json[86];
                document.getElementById("encoder_16_status_2").innerHTML  = json[87];

                document.getElementById("dsgn_2_byte_7_tx").innerHTML = document.getElementById("dsgn_1_byte_7_tx").innerHTML = json[88];
                document.getElementById("dsgn_2_byte_6_tx").innerHTML = document.getElementById("dsgn_1_byte_6_tx").innerHTML = json[89];
                document.getElementById("dsgn_2_byte_5_tx").innerHTML = document.getElementById("dsgn_1_byte_5_tx").innerHTML = json[90];
                document.getElementById("dsgn_2_byte_4_tx").innerHTML = document.getElementById("dsgn_1_byte_4_tx").innerHTML = json[91];
                document.getElementById("dsgn_2_byte_3_tx").innerHTML = document.getElementById("dsgn_1_byte_3_tx").innerHTML = json[92];
                document.getElementById("dsgn_2_byte_2_tx").innerHTML = document.getElementById("dsgn_1_byte_2_tx").innerHTML = json[93];
                document.getElementById("dsgn_2_byte_1_tx").innerHTML = document.getElementById("dsgn_1_byte_1_tx").innerHTML = json[94];
                document.getElementById("dsgn_2_byte_0_tx").innerHTML = document.getElementById("dsgn_1_byte_0_tx").innerHTML = json[95];
                
                /*
                let fbvByte_0 = parseInt(document.getElementById("dsgn_1_byte_7_tx").innerText, 10);
                console.log(fbvByte_0);
                console.log(fbvByte_0 & 0x01);
                console.log(fbvByte_0 & 0x02);
                console.log(fbvByte_0 & 0x04);
                console.log(fbvByte_0 & 0x08);
                if (fbvByte_0 & 0x01) document.getElementById("fbv-in-bit_0").checked = true; else document.getElementById("fbv-in-bit_0").checked = false;
                if (fbvByte_0 & 0x02) document.getElementById("fbv-in-bit_1").checked = true; else document.getElementById("fbv-in-bit_1").checked = false;
                */
            }
        }
    }

    httpRequest.open("GET", "getCAN1data", true);
    httpRequest.send();
    clearTimeout(can1Timout);
    can2Timout = setTimeout(_ajaxGetCAN2LiveData, 200);
}

function _ajaxGetCAN2LiveData() 
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
                document.getElementById("dsgn_2_byte_0").innerHTML    = json[0];
                document.getElementById("dsgn_2_byte_1").innerHTML    = json[1];
                document.getElementById("dsgn_2_byte_2").innerHTML    = json[2];
                document.getElementById("dsgn_2_byte_3").innerHTML    = json[3];
                document.getElementById("dsgn_2_byte_4").innerHTML    = json[4];
                document.getElementById("dsgn_2_byte_5").innerHTML    = json[5];
                document.getElementById("dsgn_2_byte_6").innerHTML    = json[6];
                document.getElementById("dsgn_2_byte_7").innerHTML    = json[7];

                document.getElementById("erro_2_byte_0").innerHTML    = json[8];
                document.getElementById("erro_2_byte_1").innerHTML    = json[9];
                document.getElementById("erro_2_byte_2").innerHTML    = json[10];
                document.getElementById("erro_2_byte_3").innerHTML    = json[11];
                document.getElementById("erro_2_byte_4").innerHTML    = json[12];
                document.getElementById("erro_2_byte_5").innerHTML    = json[13];
                document.getElementById("erro_2_byte_6").innerHTML    = json[14];
                document.getElementById("erro_2_byte_7").innerHTML    = json[15];

                document.getElementById("encoder_21_byte_0").innerHTML    = json[16];
                document.getElementById("encoder_21_byte_1").innerHTML    = json[17];
                document.getElementById("encoder_21_byte_2").innerHTML    = json[18];
                document.getElementById("encoder_21_byte_3").innerHTML    = json[19];
                document.getElementById("encoder_21_byte_4").innerHTML    = json[20];
                document.getElementById("encoder_21_byte_5").innerHTML    = json[21];
                document.getElementById("encoder_21_byte_6").innerHTML    = json[22];
                document.getElementById("encoder_21_byte_7").innerHTML    = json[23];

                document.getElementById("encoder_22_byte_0").innerHTML    = json[24];
                document.getElementById("encoder_22_byte_1").innerHTML    = json[25];
                document.getElementById("encoder_22_byte_2").innerHTML    = json[26];
                document.getElementById("encoder_22_byte_3").innerHTML    = json[27];
                document.getElementById("encoder_22_byte_4").innerHTML    = json[28];
                document.getElementById("encoder_22_byte_5").innerHTML    = json[29];
                document.getElementById("encoder_22_byte_6").innerHTML    = json[30];
                document.getElementById("encoder_22_byte_7").innerHTML    = json[31];

                document.getElementById("encoder_23_byte_0").innerHTML    = json[32];
                document.getElementById("encoder_23_byte_1").innerHTML    = json[33];
                document.getElementById("encoder_23_byte_2").innerHTML    = json[34];
                document.getElementById("encoder_23_byte_3").innerHTML    = json[35];
                document.getElementById("encoder_23_byte_4").innerHTML    = json[36];
                document.getElementById("encoder_23_byte_5").innerHTML    = json[37];
                document.getElementById("encoder_23_byte_6").innerHTML    = json[38];
                document.getElementById("encoder_23_byte_7").innerHTML    = json[39];

                document.getElementById("encoder_24_byte_0").innerHTML    = json[40];
                document.getElementById("encoder_24_byte_1").innerHTML    = json[41];
                document.getElementById("encoder_24_byte_2").innerHTML    = json[42];
                document.getElementById("encoder_24_byte_3").innerHTML    = json[43];
                document.getElementById("encoder_24_byte_4").innerHTML    = json[44];
                document.getElementById("encoder_24_byte_5").innerHTML    = json[45];
                document.getElementById("encoder_24_byte_6").innerHTML    = json[46];
                document.getElementById("encoder_24_byte_7").innerHTML    = json[47];

                document.getElementById("encoder_25_byte_0").innerHTML    = json[48];
                document.getElementById("encoder_25_byte_1").innerHTML    = json[49];
                document.getElementById("encoder_25_byte_2").innerHTML    = json[50];
                document.getElementById("encoder_25_byte_3").innerHTML    = json[51];
                document.getElementById("encoder_25_byte_4").innerHTML    = json[52];
                document.getElementById("encoder_25_byte_5").innerHTML    = json[53];
                document.getElementById("encoder_25_byte_6").innerHTML    = json[54];
                document.getElementById("encoder_25_byte_7").innerHTML    = json[55];

                document.getElementById("encoder_26_byte_0").innerHTML    = json[56];
                document.getElementById("encoder_26_byte_1").innerHTML    = json[57];
                document.getElementById("encoder_26_byte_2").innerHTML    = json[58];
                document.getElementById("encoder_26_byte_3").innerHTML    = json[59];
                document.getElementById("encoder_26_byte_4").innerHTML    = json[60];
                document.getElementById("encoder_26_byte_5").innerHTML    = json[61];
                document.getElementById("encoder_26_byte_6").innerHTML    = json[62];
                document.getElementById("encoder_26_byte_7").innerHTML    = json[63];

                document.getElementById("encoder_21_pos").innerHTML       = json[64];
                document.getElementById("encoder_21_speed").innerHTML     = json[65];
                document.getElementById("encoder_21_status_1").innerHTML  = json[66];
                document.getElementById("encoder_21_status_2").innerHTML  = json[67];

                document.getElementById("encoder_22_pos").innerHTML       = json[68];
                document.getElementById("encoder_22_speed").innerHTML     = json[69];
                document.getElementById("encoder_22_status_1").innerHTML  = json[70];
                document.getElementById("encoder_22_status_2").innerHTML  = json[71];

                document.getElementById("encoder_23_pos").innerHTML       = json[72];
                document.getElementById("encoder_23_speed").innerHTML     = json[73];
                document.getElementById("encoder_23_status_1").innerHTML  = json[74];
                document.getElementById("encoder_23_status_2").innerHTML  = json[75];

                document.getElementById("encoder_24_pos").innerHTML       = json[76];
                document.getElementById("encoder_24_speed").innerHTML     = json[77];
                document.getElementById("encoder_24_status_1").innerHTML  = json[78];
                document.getElementById("encoder_24_status_2").innerHTML  = json[79];

                document.getElementById("encoder_25_pos").innerHTML       = json[80];
                document.getElementById("encoder_25_speed").innerHTML     = json[81];
                document.getElementById("encoder_25_status_1").innerHTML  = json[82];
                document.getElementById("encoder_25_status_2").innerHTML  = json[83];

                document.getElementById("encoder_26_pos").innerHTML       = json[84];
                document.getElementById("encoder_26_speed").innerHTML     = json[85];
                document.getElementById("encoder_26_status_1").innerHTML  = json[86];
                document.getElementById("encoder_26_status_2").innerHTML  = json[87];
            }
        }
    }

    httpRequest.open("GET", "getCAN2data", true);
    httpRequest.send();
    clearTimeout(can2Timout);
    can1Timout = setTimeout(_ajaxGetCAN1LiveData, 200);
}

/* FBV ZOMBIE */
function _ajaxSendFBVBytes() {
    var FBVZombieBytes = "zombieFBV";
    
    if (window.XMLHttpRequest) 
    {
        var fbvXhr = new XMLHttpRequest();
    } 
    else if (window.ActiveXObject) 
    {
        try 
        {
            var fbvXhr = new ActiveXObject("Msxml2.XMLHTTP");
        } 
        catch (otherMS) 
        {
            try 
            {
                var fbvXhr = new ActiveXObject("Microsoft.XMLHTTP");
            } 
            catch (failed) 
            {
                var fbvXhr = null;
            }
        }
    }

    if (document.getElementById("fbv-in-bit_0").checked) FBVZombieBytes += "1"; else FBVZombieBytes += "0" ;
    if (document.getElementById("fbv-in-bit_1").checked) FBVZombieBytes += "1"; else FBVZombieBytes += "0" ;
    if (document.getElementById("fbv-in-bit_2").checked) FBVZombieBytes += "1"; else FBVZombieBytes += "0" ;
    if (document.getElementById("fbv-in-bit_3").checked) FBVZombieBytes += "1"; else FBVZombieBytes += "0" ;
    if (document.getElementById("fbv-in-bit_4").checked) FBVZombieBytes += "1"; else FBVZombieBytes += "0" ;
    if (document.getElementById("fbv-in-bit_5").checked) FBVZombieBytes += "1"; else FBVZombieBytes += "0" ;
    if (document.getElementById("fbv-in-bit_6").checked) FBVZombieBytes += "1"; else FBVZombieBytes += "0" ;
    if (document.getElementById("fbv-in-bit_7").checked) FBVZombieBytes += "1"; else FBVZombieBytes += "0" ;
    
    fbvXhr.open("GET", FBVZombieBytes, true),
    fbvXhr.send(null);

    /*return false;*/
}

function _ajaxGetFBVBytes() {

    if (window.XMLHttpRequest) 
    {
        var fbvXhr = new XMLHttpRequest();
    } 
    else if (window.ActiveXObject) 
    {
        try 
        {
            var fbvXhr = new ActiveXObject("Msxml2.XMLHTTP");
        } 
        catch (otherMS) 
        {
            try 
            {
                var fbvXhr = new ActiveXObject("Microsoft.XMLHTTP");
            } 
            catch (failed) 
            {
                var fbvXhr = null;
            }
        }
    }

    fbvXhr.onreadystatechange = function () 
    {   
        if (this.readyState == 4) 
        {
            if (this.status == 200) 
            {
                var json = JSON.parse(this.responseText);
                if (json[0]) document.getElementById("fbv-in-bit_0").checked = true; else document.getElementById("fbv-in-bit_0").checked = false;
                if (json[1]) document.getElementById("fbv-in-bit_1").checked = true; else document.getElementById("fbv-in-bit_1").checked = false;
                if (json[2]) document.getElementById("fbv-in-bit_2").checked = true; else document.getElementById("fbv-in-bit_2").checked = false;
                if (json[3]) document.getElementById("fbv-in-bit_3").checked = true; else document.getElementById("fbv-in-bit_3").checked = false;
                if (json[4]) document.getElementById("fbv-in-bit_4").checked = true; else document.getElementById("fbv-in-bit_4").checked = false;
                if (json[5]) document.getElementById("fbv-in-bit_5").checked = true; else document.getElementById("fbv-in-bit_5").checked = false;
                if (json[6]) document.getElementById("fbv-in-bit_6").checked = true; else document.getElementById("fbv-in-bit_6").checked = false;
                if (json[7]) document.getElementById("fbv-in-bit_7").checked = true; else document.getElementById("fbv-in-bit_7").checked = false;
            }
        }
    }

    fbvXhr.open("GET", "getFBVBytes", true),
    fbvXhr.send();
}

/* END FBV ZOMBIE */

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